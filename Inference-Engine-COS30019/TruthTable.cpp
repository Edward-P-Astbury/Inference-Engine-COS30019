#include "TruthTable.h"
#include <cmath>
#include <iostream>

TruthTable::TruthTable(std::vector<std::string> aClauses, std::vector<std::string> aQuery)
{
	fClauses = aClauses;
	fQuery = aQuery;
	GenerateTable(fClauses.size());
	GetQuery(fQuery[0]);
	SolveTable();
}

void TruthTable::GenerateTable(int aNumberOfClauses)
{
	int lNumberOfOptions = pow(2, aNumberOfClauses);

	for (int i = 0; i < lNumberOfOptions; i++)
	{
		for (int j = 0; j < aNumberOfClauses; j++)
		{
			int v = i & 1 << aNumberOfClauses - 1 - j;

			std::cout << (v == 0 ? "T" : "F");
		}
		std::cout << "\n";
	}
}

void TruthTable::SolveTable()
{
	// begin by extracting the string that matches the query
}

std::string TruthTable::GetQuery(std::string aQuery)
{
	for (std::string& s : fClauses)
	{
		if (s.find(aQuery))	// find the query within all the clauses
		{
			std::cout << aQuery << std::endl;
			return aQuery;
		}
	}
}
