#include "TruthTable.h"
#include <cmath>
#include <iostream>

TruthTable::TruthTable(std::vector<std::string> aClauses, std::vector<std::string> aQuery)
{
	fClauses = aClauses;
	fQuery = aQuery;
	GenerateTable(fClauses.size());
}

void TruthTable::GenerateTable(int aNumberOfClauses)
{
	int lNumberOfOptions = pow(2, aNumberOfClauses);

	for (int i = 0; i < lNumberOfOptions; i++)
	{
		for (int j = 0; j < aNumberOfClauses; j++)
		{
			int v = i & 1 << aNumberOfClauses - 1 - j;

			fGrid[i][j] = (v == 0 ? true : false);

			std::cout << (v == 0 ? "T" : "F");
		}
		std::cout << "\n";
	}
}

void TruthTable::SolveTable(std::string aQuery)
{
	for (std::string& s : fClauses)
	{
		if (s.find(aQuery))	// find the query within all the clauses
		{
			std::cout << s << std::endl;
		}
	}
}
