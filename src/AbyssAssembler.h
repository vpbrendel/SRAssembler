/*
 * AbyssAssembler.h
 *
 *  Created on: Oct 15, 2011
 *     Authors: Hsien-chao Chou (first version); Thomas McCarthy and Volker Brendel (modifications)
 */

#ifndef ABYSSASSEMBLER_H_
#define ABYSSASSEMBLER_H_

#include "Assembler.h"

class AbyssAssembler: public Assembler {
public:
	AbyssAssembler(int, string);
	void do_assembly(int kmer, const vector<Library>& libraries, const string& output_file, int threads, boost::unordered_map<std::string,Params> parameters_dict);
	bool is_available();
	void clean_files(const string& dir);
	string get_output_contig_file_name(string prefix);
	string get_output_scaffold_file_name(string prefix);
	virtual ~AbyssAssembler();
};

#endif /* ABYSSASSEMBLER_H_ */
