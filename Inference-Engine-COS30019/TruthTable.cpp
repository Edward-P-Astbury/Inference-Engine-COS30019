#include "TruthTable.h"
#include <cmath>
#include <iostream>

struct sLogicalConnectives
{
	std::string IMPLICATION = "=>";
	std::string AND = "&";
}; sLogicalConnectives sLogicConnective;

TruthTable::TruthTable(std::vector<std::string> aClauses, std::vector<std::string> aQuery)
{
	fClauses = aClauses;
	fQuery = aQuery;
	GenerateTable(fClauses.size());
	GetQuery(fQuery[0]);
	SolveTable();
	AddVariables();
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
	int lIndex = lQuery.find(sLogicConnective.IMPLICATION);

	std::string lPremise;
	std::string lConclusion;

	if (lQuery.find(sLogicConnective.IMPLICATION))
	{
		std::cout << "Implication check" << std::endl;

		lPremise = lQuery.substr(0, lIndex);
		lConclusion = lQuery.substr(lIndex + sLogicConnective.IMPLICATION.length(), lQuery.length());

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

void TruthTable::AddVariables()
{
	for (std::string& s : fClauses)
	{
		if (s.find(sLogicConnective.AND) != std::string::npos)
		{
			// split the string up so we can get the variable before and after the '&' and '=>'
			std::string lVariableLeftOfAnd;
			std::string lVariableRightOfAnd;
			std::string lVariableAfterImplication;
			int lIndex = s.find(sLogicConnective.AND);

			lVariableLeftOfAnd = s.substr(0, lIndex);

			std::string lTemp = s.substr(lIndex + 1); // e.g. p3=>c or g=>h

			lVariableRightOfAnd = lTemp.substr(0, lTemp.find(sLogicConnective.IMPLICATION));

			lVariableAfterImplication = lTemp.substr(lTemp.find(sLogicConnective.IMPLICATION) + sLogicConnective.IMPLICATION.length(), lTemp.length());

			std::cout << "Left side of &: " << lVariableLeftOfAnd << "\t" << " Right side of &: " << lVariableRightOfAnd << "\t" << " After => " << lVariableAfterImplication << std::endl;

			// push back element into vector after extracting variables
		}
		else if (s.find(sLogicConnective.IMPLICATION) != std::string::npos)
		{
			// logic
		}
		else
		{
			// logic for single variable with no symbol
		}
	}
}
