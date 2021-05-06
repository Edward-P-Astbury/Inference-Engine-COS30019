#pragma once
#include <string>
#include <vector>

class TruthTable
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;
	std::vector<std::string> fVariables;
	std::vector<std::string> fSubClauses;

public:
	TruthTable(std::vector<std::string> aClauses, std::vector<std::string> aQuery);
	void GenerateTable();
	void SolveTable();
	bool Implication(bool aLHS, bool aRHS);
	std::string GetQuery(std::string aQuery);
	void AddVariables();
	std::string CheckAmpersand(std::string& aString);
	std::string CheckImplication(std::string& aString);
	std::string GetAndSubClause(std::string& aString);
	void Sort();
	void PrintVar();
	void PrintAndSubClause();
};

