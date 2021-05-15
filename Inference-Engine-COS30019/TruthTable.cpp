#include "TruthTable.h"
#include <cmath>
#include <iostream>
#include <vector>

/*
using namespace std;

TruthTable::TruthTable(vector<string> aClauses, vector<string> aQuery)
{
	fClauses = aClauses;
	fQuery = aQuery;
	GetQuery(fQuery[0]);
	SolveTable();
	AddVariables();
	Sort();
	GenerateTable(pow(2, fVariables.size()), fVariables.size());
	//PrintTTVar();
	PrintVar();
	//PrintClauses();
	PrintAndSubClause();
	DevelopKnowledgeBase();
	PrintKB();
	Query();
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

bool TruthTable::Amp(bool aLHS, bool aRHS)
{
	if (aLHS == true && aRHS == true)
		return true;
	else
		return false;
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
		string subVar = s;

		//GetAndSubClause(s);
		subVar = GetAndSubClause(subVar);

		if (subVar != "")
		{
			fSubClauses.push_back(subVar);
		}

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

		fSubClauses.push_back(s);
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

std::string TruthTable::GetAndSubClause(std::string& aString)
{
	string var = aString;

	// if the string contains a '&' then we want the entire string prior to the '=>'
	if (aString.find(sLogicConnective.AND) != string::npos)
	{
		size_t lIndex = aString.find(sLogicConnective.IMPLICATION);
		var = aString.substr(0, lIndex);

		return var;
	}

	return "";
}

void TruthTable::Sort()
{
	// delete multiple elements of the same type in fVariables
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
	cout << "\n\nfVariables\n";
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
	//map fTTVariable with fSubclauses to the fVariable order
	for (size_t i = 0; i < fSubClauses.size(); i++)
	{
		//map values to KB
		vector<bool> lVar = {};
		string lLHS = "";
		string lRHS = "";
		string var = &fSubClauses[i][0];
		int lLocationLeft = 0;
		int lLocationRight = 0;
		int lSingleLocation = 0;

		if (var.find(sLogicConnective.IMPLICATION) != string::npos)
		{
			size_t lIndex = var.find(sLogicConnective.IMPLICATION);
			lLHS = var.substr(0, lIndex);
			lRHS = var.substr(lIndex + 2);
		}
		else if (var.find(sLogicConnective.AND) != string::npos)
		{
			size_t lIndex = var.find(sLogicConnective.AND);
			lLHS = var.substr(0, lIndex);
			lRHS = var.substr(lIndex + 1);
		}
		else
		{
			cout << var << endl;
		}
		if (lLHS != "" && lRHS != "")
		{
			for (int t = 0; t < fVariables.size(); t++)
			{
				if (fVariables[t] == lLHS)
				{
					lLocationLeft = t;
				}
				if (fVariables[t] == lRHS)
				{
					lLocationRight = t;
				}
			}
		}
		else
		{
			for (int t = 0; t < fVariables.size(); t++)
			{
				if (var == fVariables[t])
				{
					lSingleLocation = t;
				}
			}
		}

		for (size_t j = 0; j < pow(2, fVariables.size()); j++)
		{
			if (lLHS != "" && lRHS != "")
			{
				if (var.find(sLogicConnective.AND) != string::npos)
				{
					string varTemp = var;
					size_t lIndex = varTemp.find(sLogicConnective.AND);
					varTemp = var.substr(lIndex + 1);

					//if a&b=>c
					if (varTemp.find(sLogicConnective.IMPLICATION) != string::npos)
					{
						lVar.push_back(Implication(fKB[i - 1][j], fTTvariables[j][lLocationRight]));
					}
					//a&b
					else
					{
						lVar.push_back(Amp(fTTvariables[j][lLocationLeft], fTTvariables[j][lLocationRight]));
					}
				}
				else if (var.find(sLogicConnective.IMPLICATION) != string::npos)
				{
					lVar.push_back(Implication(fTTvariables[j][lLocationLeft], fTTvariables[j][lLocationRight]));
				}
			}
			else
			{
				lVar.push_back(fTTvariables[j][lSingleLocation]);
			}
		}
			fKB.push_back(lVar);
	}
}

void TruthTable::PrintAndSubClause()
{
	cout << "\n\nsubclauses\n";
	for (string& s : fSubClauses)
	{
		cout << "Sub clauses including AND part of string in loop " << s << endl;
	}
}

void TruthTable::PrintClauses()
{
	cout << "clauses\n";
	for (int i = 0; i < fClauses.size(); i++)
	{
		cout << fClauses[i] << "  ";
	}
	cout << "\n\n";
}

void TruthTable::PrintKB()
{
	int count = 0;
	cout << "KB size: " << fKB.size() << "\tfVariables size: " << pow(2, fVariables.size()) << "\n\n\n";
	cout << "KB\t\t\tTT\n\n";
	
	for (int i = 0; i < pow(2, fVariables.size()); i++)
	{
		for (int j = 0; j < fSubClauses.size(); j++)
		{
			cout << fKB[j][i];
		}
		cout << "\t\t";
		for (int j = 0; j < fVariables.size(); j++)
		{
			cout << fTTvariables[i][j];
		}
		cout << "\n";
		count++;
	}
	cout << "count:\t" << count << endl;
}

void TruthTable::Query()
{
	string lQuery = fQuery[0];

	cout << "Query\t" << lQuery << endl;
	int lLocation = 0;
	for (int i = 0; i < fVariables.size(); i++)
	{
		if (lQuery == fVariables[i])
		{
			lLocation = i;
			cout << "i\t" << i << " " << fVariables[i] << endl;
		}
	}
	int count = 0;
	bool lQ;
	lLocation = 7;	//*******************
	for (int j = 0; j < fVariables.size(); j++)
	{
		if (fSubClauses[j] == fQuery[0])
		{
			lLocation = 7;	//*******************
			cout << "loc = " << j << endl;
		}
	}

	for (int i = 0; i < pow(2, fVariables.size()); i++)
	{
		//MANUALLY ENTERED POSITION INSTEAD OF SEARCHED!!!!!!!!!!!
		lQ = fKB[lLocation][i];	//d = 7
		
		if (lQ)
		{
			count++;
		}
		
	}
	cout << count << "\tYES:\t" << count / (pow(2,9)) << endl;
}
*/