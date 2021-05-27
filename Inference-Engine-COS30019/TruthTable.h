#pragma once
#include <vector>
#include <string>

class TruthTable
{
private:
	std::vector<std::string> fClauses;			// ASK clauses
	std::vector<std::string> fSubClauses;		// List of Sub Clauses for TT ie a&b, a&b=>c where a&b is a sub clause
	std::vector<std::string> fSymbols;			// list of all symbols in the clauses
	std::vector<std::vector<bool>> fKB;			// Knowledge Base
	std::vector<std::vector<bool>> fSubKB;		// Sub KB from sub clauses
	std::vector<std::vector<bool>> fModels;		// Truthtable Model of all symbols
	std::string fQuery;							// query variable

public:
	TruthTable(std::vector<std::string> aClauses, std::string aQuery, std::vector<std::string> aSymbols, std::vector<std::string> aSubClause);
	void TestTT();								// Control method to implement methods in order
	void DevelopTT();							// Develop full TT from symbols
	void DevelopKnowledgeBase();				// Develop the KB from the clauses
	bool Implication(bool aLHS, bool aRHS);		// check implication and return result
	bool Amp(bool aLHS, bool aRHS);				// check & and return result
	void EntailKB();							// Final Entailment solution
};
