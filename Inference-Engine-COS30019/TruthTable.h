#pragma once
#include <string>
#include <vector>

class TruthTable
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;
	bool fGrid[0][1];

public:
	TruthTable(std::vector<std::string> aClauses, std::vector<std::string> aQuery);
	void GenerateTable(int aNumberOfClauses);
	void SolveTable(std::string aQuery);
};

