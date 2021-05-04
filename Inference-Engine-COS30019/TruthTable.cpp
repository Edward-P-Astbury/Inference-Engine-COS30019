#include "TruthTable.h"
#include <cmath>
#include <iostream>

struct sLogicalConnectives
{
	std::string implication = "=>";
}; sLogicalConnectives sLogicConnective;

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
	std::string lQuery = GetQuery(fQuery[0]);
	int lIndex = lQuery.find(sLogicConnective.implication);

	std::string lPremise;
	std::string lConclusion;

	if (lQuery.find(sLogicConnective.implication))
	{
		std::cout << "Implication check" << std::endl;

		lPremise = lQuery.substr(0, lIndex);
		lConclusion = lQuery.substr(lIndex + sLogicConnective.implication.length(), lQuery.length());

		std::cout << "Premise: " << lPremise << " Conclusion: " << lConclusion << std::endl;
	}

	int lTempCount = 1;

	if (lPremise.length() > 2)
	{
		lTempCount++;
	}

	int lNumberOfSymbols = lTempCount + lConclusion.length();

	GenerateTable(lNumberOfSymbols);
}

bool TruthTable::Implication(bool aLHS, bool aRHS)
{
	if (aLHS == true && aRHS == true)
		return true;
	if (aLHS == true && aRHS == false)
		return false;
	if (aLHS == false && aRHS == true)
		return true;
	if (aLHS == false && aRHS == false)
		return true;
}

std::string TruthTable::GetQuery(std::string aQuery)
{
	for (std::string& s : fClauses)
	{
		if (s.find(aQuery) != std::string::npos)
		{
			//std::cout << s << std::endl;
			return s;
		}
	}
}
