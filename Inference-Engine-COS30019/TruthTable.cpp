#include "TruthTable.h"
#include <cmath>
#include <iostream>

using namespace std;

struct sLogicalConnective
{
	string IMPLICATION = "=>";
	string AND = "&";
}; sLogicalConnective sLogicConnective;

TruthTable::TruthTable(std::vector<std::string> aClauses, std::string aQuery, std::vector<std::string> aSymbols, std::vector<std::string> aSubClause)
{
	fClauses = aClauses;
	fQuery = aQuery;
	fSymbols = aSymbols;
	fSubClauses = aSubClause;
	TestTT();
}

void TruthTable::TestTT()
{
	DevelopTT();				//Develop full TT from symbols
	DevelopKnowledgeBase();		//Develop the KB from the clauses
	EntailKB();					//Final Entailment solution
}

void TruthTable::DevelopTT()
{
	//generate full Truthtable
	for (int i = 0; i < pow(2, fSymbols.size()); i++)
	{
		vector<bool> lVar = {};

		for (int j = 0; j < fSymbols.size(); j++)
		{
			int v = i & 1 << fSymbols.size() - 1 - j;

			if (v == 0)
			{
				lVar.push_back(false);
			}
			else
			{
				lVar.push_back(true);
			}
		}

		fModels.push_back(lVar);
	}
}

void TruthTable::DevelopKnowledgeBase()
{
	int lFlag;	//Flag for & and => ie a&b=>c;  splits to put into sub KB variable
	//map fClauses with fSymbols TT of fModels to fKB
	for (size_t i = 0; i < fSubClauses.size(); i++)
	{

		//map values to KB
		lFlag = 0;
		vector<bool> lVar = {};
		string lLHS = "";						//left variable from clause
		string lRHS = "";						//right variable from clause
		string lClauseVar = fSubClauses[i];		//Sub clause
		int lLocationLeft = 0;					//location of lLHS in TT developed
		int lLocationRight = 0;					//location of lRHS in TT developed
		int lSingleLocation = 0;				//location of a single variable

		if (lClauseVar.find(sLogicConnective.IMPLICATION) != string::npos)
		{
			size_t lIndex = lClauseVar.find(sLogicConnective.IMPLICATION);
			lLHS = lClauseVar.substr(0, lIndex);
			lRHS = lClauseVar.substr(lIndex + 2);
		}
		else if (lClauseVar.find(sLogicConnective.AND) != string::npos)
		{
			lFlag = 1;
			size_t lIndex = lClauseVar.find(sLogicConnective.AND);
			lLHS = lClauseVar.substr(0, lIndex);
			lRHS = lClauseVar.substr(lIndex + 1);
		}

		//Mapping location finding for left and right variables
		if (lLHS != "" && lRHS != "")
		{
			for (int t = 0; t < fSymbols.size(); t++)
			{
				if (fSymbols[t] == lLHS)
				{
					lLocationLeft = t;
				}
				if (fSymbols[t] == lRHS)
				{
					lLocationRight = t;
				}
			}
		}
		//mapping for a single variable loaction
		else
		{
			for (int t = 0; t < fSymbols.size(); t++)
			{
				if (lClauseVar == fSymbols[t])
				{
					lSingleLocation = t;
				}
			}
		}

		//Main algorithm to develop KB
		for (int j = 0; j < pow(2, fSymbols.size()); j++)
		{
			if (lLHS != "" && lRHS != "")
			{
				if (lClauseVar.find(sLogicConnective.AND) != string::npos)
				{
					string varTemp = lClauseVar;
					size_t lIndex = varTemp.find(sLogicConnective.AND);
					varTemp = lClauseVar.substr(lIndex + 1);

					//if a&b=>c
					if (varTemp.find(sLogicConnective.IMPLICATION) != string::npos)
					{
						lVar.push_back(Implication(fSubKB[i - 1][j], fModels[j][lLocationRight]));
					}
					//a&b
					else
					{
						lVar.push_back(Amp(fModels[j][lLocationLeft], fModels[j][lLocationRight]));
					}
				}
				else if (lClauseVar.find(sLogicConnective.IMPLICATION) != string::npos)
				{
					lVar.push_back(Implication(fModels[j][lLocationLeft], fModels[j][lLocationRight]));
				}
			}
			else
			{
				lVar.push_back(fModels[j][lSingleLocation]);
			}
		}
		if (lFlag == 0)
		{
			fKB.push_back(lVar);
		}
		fSubKB.push_back(lVar);
	}
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

void TruthTable::EntailKB()
{
	int count = 0;
	int lQueryLocation = 0;

	//Locate query position
	for (int i = 0; i < fSymbols.size(); i++)
	{
		if (fQuery == fSymbols[i])
		{
			lQueryLocation = i;
		}
	}

	//Run through KB and determine entailment
	for (int i = 0; i < pow(2, fModels[0].size()); i++)
	{
		bool infer{};
		infer = fKB[0][i];
		for (int j = 1; j <= fKB.size() - 1; j++)
		{
			infer = Amp(infer, fKB[j][i]);
		}

		if (infer == true)
		{
			if (fModels[i][lQueryLocation] == true)
			{
				count++;		//Count how many entail clauses
			}
		}
	}

	if (count > 0)
	{
		cout << "YES:\t" << count << "\n\n";
	}
	else
	{
		cout << "No:\n\n";
	}
}