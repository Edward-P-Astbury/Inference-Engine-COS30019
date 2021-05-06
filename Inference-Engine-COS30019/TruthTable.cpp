#include "TruthTable.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct sLogicalConnectives
{
	string IMPLICATION = "=>";
	string AND = "&";
}; sLogicalConnectives sLogicConnective;

TruthTable::TruthTable(vector<string> aClauses, vector<string> aQuery)
{
	fClauses = aClauses;
	fQuery = aQuery;
	GetQuery(fQuery[0]);
	SolveTable();
	AddVariables();
	Sort();
	GenerateTable(pow(2, fVariables.size()), fVariables.size());
	PrintTTVar();
}

void TruthTable::GenerateTable(int aNumberOfOptions, int aSize)
{
	int count = 0;

	for (int i = 0; i < aNumberOfOptions; i++)
	{
		vector<bool> lVar = {};

		for (int j = 0; j < aSize; j++)
		{
			int v = i & 1 << aSize - 1 - j;

			if (v == 0)
			{
				lVar.push_back(false);
			}
			else
			{
				lVar.push_back(true);
			}
		}

		fTTvariables.push_back(lVar);
		count++;
	}
	cout << count << endl;
}

void TruthTable::SolveTable()
{
	// begin by extracting the string that matches the query
	string lQuery = GetQuery(fQuery[0]);
	int lIndex = lQuery.find(sLogicConnective.IMPLICATION);

	string lPremise;
	string lConclusion;

	if (lQuery.find(sLogicConnective.IMPLICATION))
	{
		cout << "Implication check" << endl;

		lPremise = lQuery.substr(0, lIndex);
		lConclusion = lQuery.substr(lIndex + sLogicConnective.IMPLICATION.length(), lQuery.length());

		cout << "Premise: " << lPremise << " Conclusion: " << lConclusion << endl;
	}

	int lTempCount = 1;

	if (lPremise.length() > 2)
	{
		lTempCount++;
	}

	int lNumberOfSymbols = lTempCount + lConclusion.length();

	//GenerateTable();
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

string TruthTable::GetQuery(string aQuery)
{
	for (string& s : fClauses)
	{
		if (s.find(aQuery) != string::npos)
		{
			//std::cout << s << endl;
			return s;
		}
	}
}

void TruthTable::AddVariables()
{
	for (string& s : fClauses)
	{
		bool complete = false;
		string var = s;

		while (!complete)
		{
			var = CheckAmpersand(var);
			var = CheckImplication(var);
			if (CheckAmpersand(var) == CheckImplication(var))
			{
				fVariables.push_back(var);
				complete = true;
			}
		}
	}
}

string TruthTable::CheckAmpersand(string& aString)
{
	string var = aString;

	if (aString.find(sLogicConnective.AND) != string::npos)
	{
		size_t lIndex = aString.find(sLogicConnective.AND);
		var = aString.substr(0, lIndex);
		fVariables.push_back(var);
		var = aString.substr(lIndex + 1);
	}

	return var;
}

string TruthTable::CheckImplication(string& aString)
{
	string var = aString;

	if (aString.find(sLogicConnective.IMPLICATION) != string::npos)
	{
		size_t lIndex = aString.find(sLogicConnective.IMPLICATION);	
		var = aString.substr(0, lIndex);
		fVariables.push_back(var);
		var = aString.substr(lIndex + 2);
	}

	return var;
}

void TruthTable::Sort()
{
	//delete multiple elements of the same type in fVariables
	for (int i = 0; i < fVariables.size(); i++)
	{
		for (int j = 1 + i; j < fVariables.size(); j++)
		{
			if (fVariables[i] == fVariables[j])
			{
				fVariables.erase(fVariables.begin() + j);
			}
		}
	}
}

void TruthTable::PrintVar()
{
	for (string& s : fVariables)
	{
		cout << s << endl;
	}
}

void TruthTable::PrintTTVar()
{
	for (int i = 0; i < pow(2, fVariables.size()); i++)
	{
		for (int j = 0; j < fVariables.size(); j++)
		{
			cout << fTTvariables[i][j];
		}
		cout << "\n";
	}
}

void TruthTable::DevelopKnowledgeBase()
{
	//map fTTVariable wit fSubclauses to the fVariable order

}
