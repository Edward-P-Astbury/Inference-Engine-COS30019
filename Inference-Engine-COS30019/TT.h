#pragma once
#include <vector>
#include <string>

class TT
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fSubClauses;
	std::vector<std::string> fSymbols;
	std::vector<std::string> fRest;
	std::vector<bool> fP1;
	std::vector<bool> fP2;
	std::vector<bool> fModel;
	std::vector<std::vector<bool>> fKB;
	std::vector<std::vector<bool>> fSubKB;
	std::vector<std::vector<bool>> fModels;
	std::vector<std::vector<bool>> fTTvariables;
	std::string fQuery;

public:
	TT(std::vector<std::string> aClauses, std::string aQuery, std::vector<std::string> aSymbols, std::vector<std::string> aSubClause);
	void TestTT();
	void DevelopTT();
	void DevelopKB();
	void DevelopKnowledgeBase();
	bool TTEntails(std::vector<std::vector<bool>> aKB, std::vector<std::string> aAlpha);	//returns True or False
	bool TTCheckAll(std::vector<std::vector<bool>> aKB, std::vector<std::string> aAlpha,
		std::vector<std::string> &aSymbols, std::vector<bool> aPnModel);	//returns true or false
	bool Implication(bool aLHS, bool aRHS);	//check implication and return result
	bool Amp(bool aLHS, bool aRHS);	//check & and return result
};

