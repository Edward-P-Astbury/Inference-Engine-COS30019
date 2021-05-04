#pragma once
#include <string>
#include <vector>

class TruthTable
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;

public:
	TruthTable(std::vector<std::string> aClauses, std::vector<std::string> aQuery);
	void GenerateTable(int aNumberOfClauses);
	void SolveTable();
	std::string GetQuery(std::string aQuery);
};

