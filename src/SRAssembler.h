/*
 * SRAssembler.h
 *
 *  Created on: Oct 12, 2011
 *     Authors: Hsien-chao Chou (first version); Thomas McCarthy and Volker Brendel (modifications)
 */

#ifndef SRASSEMBLER_H_
#define SRASSEMBLER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include "Version.h"
#include "Utility.h"
#include "Const.h"
#include "Library.h"
#include "Aligner.h"
#include "Assembler.h"
#include "SplicedAligner.h"
#include "GeneFinder.h"
#include "MPIWrapper.h"
#include "Logger.h"
#include <boost/unordered_set.hpp>

using namespace std;

typedef struct {
	int total_contig;
	int n50;
	int n90;
	unsigned int longest_contig;
} Assembly_stats;

class SRAssembler {
public:
	SRAssembler();
	virtual ~SRAssembler();
	virtual int init(int argc, char * argv[], int rank, int mpiSize);
	virtual void do_preprocessing()=0;
	virtual void remove_taboo_reads()=0;
	virtual void do_walking()=0;
	virtual void show_usage()=0;
	virtual void show_extended_usage()=0;
	virtual void print_message(const std::string&)=0;
	static SRAssembler* getInstance(int pid);
	Logger* get_logger();
protected:
	int do_alignment(int round, int lib_idx, int idx);
	void do_spliced_alignment();
	string_map do_spliced_alignment(int);
	int do_spliced_alignment(int round, int k);
	void do_gene_finding();
	void do_assembly(int, int, int threads);
	void create_index(int round);
	std::string get_contigs_index_name(int round);
	std::string get_query_fasta_file_name(int round);
	void mask_contigs(int round);
	std::string get_query_fasta_file_name_masked(int round);
	std::string get_contig_file_name(int round);
	std::string get_matched_reads_file_name(int round);
	std::string get_vmatch_output_filename(int round, int lib_idx, int idx);
	std::string get_type(int round);
	int get_match_length(int round);
	int get_mismatch_allowed(int round);
	std::string get_assembly_file_name(int round, int k);
	std::string get_assembled_scaffold_file_name(int round, int k);
	std::string get_spliced_alignment_file_name(int round, int k);
	void do_split_files(string read_file);
	void preprocess_read_chunk(int lib_idx, int file_chunk);
	int get_file_count(std::string);
	void merge_mapped_files(int round);
	Assembly_stats get_assembly_stats(int round, int k);
	void save_found_reads(int round);
	void load_found_reads(int round);
	void remove_unmapped_reads(unsigned int lib_idx, int round);
	void keep_long_contigs(string in_file, string out_file, unsigned int min_length);
	long get_total_read_count(int round);
	void send_code(const int& to, const int& action, const int& value1, const int& value2, const int& value3);
	void broadcast_code(const int& action, const int& value1, const int& value2, const int& value3);
	Aligner* get_aligner(int round);
	Assembler* get_assembler();
	SplicedAligner* get_spliced_aligner();
	GeneFinder* get_gene_finder();
	boost::unordered_map<std::string,Params> read_param_file();
	Params get_parameters(string program_name);
	std::string probe_file="", species, probe_type, out_dir;
	std::string taboo_file, taboo_type;
	int init_match_length;
	int recur_match_length;
	int mismatch_allowed;
	int num_rounds;
	bool verbose;
	bool preprocessing_only;
	int assembly_round;
	int clean_round;
	int extra_rounds;
	int contig_limit;
	bool over_write;
	bool check_gene_assembled;
	int reads_per_file;
	int start_k;
	int end_k;
	int step_k;
	int mpiSize;
	int rank;
	int fastq_format;
	int start_round;
	int spliced_alignment_program;
	int gene_finding_program;
	int assembler_program;
	int masking_round;
	int end_search_length;
	int end_search_round;
	double min_score;
	double min_coverage;
	// A dictionary for tracking the best contigs found between rounds.
	tuple_map best_hits;
	unsigned int query_contig_min;
	unsigned int min_contig_lgth;
	unsigned int max_contig_lgth;
	bool preprocessed_exist;
	bool ignore_contig_explosion;
	std::string library_file;
	std::string aux_dir;
	std::string tmp_dir;
	std::string tmp_loc;
	std::string intermediate_dir;
	std::string data_dir;
	std::string log_file;
	std::string param_file;
	std::string spliced_alignment_output_file;
	std::string gene_finding_output_file;
	std::string gene_finding_output_protein_file;
	std::string usage;
	std::string extended_usage;
	std::string final_scaf_file;
	std::string final_contigs_file;
	std::string hit_contigs_file;
	std::string final_long_contig_file;
	std::string summary_file;
	std::string mapped_readnumbers_file;
	boost::unordered_set<std::string> found_reads;
	std::vector<Library> libraries;
	Logger* logger;
	boost::unordered_map<std::string,Params> parameters_dict;
private:
	static SRAssembler* _srassembler;
	bool read_library_file();
};


#endif /* SRASSEMBLER_H_ */
