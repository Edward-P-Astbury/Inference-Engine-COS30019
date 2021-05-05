#pragma once
#include <string>
#include <vector>

class TruthTable
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;
	std::vector<std::string> fVariables;

public:
	TruthTable(std::vector<std::string> aClauses, std::vector<std::string> aQuery);
	void GenerateTable(int aNumberOfClauses);
	void SolveTable();
	bool Implication(bool aLHS, bool aRHS);
	std::string GetQuery(std::string aQuery);
	void AddVariables();
};

