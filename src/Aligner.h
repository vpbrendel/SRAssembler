/*
 * Aligner.h
 *
 *  Created on: Oct 15, 2011
 *     Authors: Hsien-chao Chou (first version); Thomas McCarthy and Volker Brendel (modifications)
 */

#ifndef ALIGNER_H_
#define ALIGNER_H_
#include <string>
#include <iostream>
#include <fstream>
#include <boost/unordered_set.hpp>
#include "Utility.h"
#include "Logger.h"
#include "Const.h"

using namespace boost;

class Aligner {
public:
	Aligner(int, string);
	virtual void create_index(const string& index_name, const string& db_type, const string& fasta_file)=0;
	virtual void do_alignment(const string& index_name, const string& alignment_type, int match_length, int mismatch_allowed, const string& reads_file, const Params& params, const string& output_file)=0;
	virtual int parse_output(const string& output_file, unordered_set<string>& found_reads, const int lib_idx, const int read_chunk, const string& left_read_index, const string& right_read_index, const string& out_left_read, const string& out_right_read)=0;
	virtual int ignore_output(const string& output_file, unordered_set<string>& found_reads, const int lib_idx, const int read_chunk)=0;
	virtual void align_long_contigs(const string& long_contig_candidate_file, const string& aux_dir, const string& contig_file, const int max_contig_size, unordered_set<string>& candidate_ids, unordered_set<string>& long_contig_ids)=0;
	virtual bool is_available()=0;
	virtual string get_program_name()=0;
	virtual int get_format()=0;
	virtual ~Aligner();
	static const int PROTEIN_ALIGNER = 0;
	static const int DNA_ALIGNER = 1;
	static Aligner* getInstance(int, int, string);
protected:
	Logger* logger;
private:
	static Aligner* protein_aligner;
	static Aligner* dna_aligner;
};

#endif /* ALIGNER_H_ */
