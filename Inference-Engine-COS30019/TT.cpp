#include "TT.h"
#include <cmath>
#include <iostream>

using namespace std;

struct sLogicalConnective
{
	string IMPLICATION = "=>";
	string AND = "&";
}; sLogicalConnective sLogicConnective;

TT::TT(std::vector<std::string> aClauses, std::string aQuery, std::vector<std::string> aSymbols, std::vector<std::string> aSubClause)
{
	fClauses = aClauses;
	fQuery = aQuery;
	fSymbols = aSymbols;
	fSubClauses = aSubClause;
	TestTT();
}

void TT::TestTT()
{			
	DevelopTT();
	cout << "Sub clauses\n\n";
	for (int i = 0; i < fSubClauses.size(); i++)
	{
		cout << fSubClauses[i] << " ";
	}
	cout << "\n\n";

	/*for (int i = 0; i < fModels.size(); i++)
	{
		for (int j = 0; j < fModels[i].size(); j++)
		{
			cout << fModels[i][j] << " ";
		}
		cout << "\n";

	}*/
	cout << "\n\n";
	DevelopKnowledgeBase();

	cout << "\n\nClauses results\t\t\tTT Results\n\n";

	for (int i = 0; i < pow(2, fModels[0].size()); i++)
	{
		for (int j = 0; j < fClauses.size(); j++)
		{
			cout << fKB[j][i] << " ";
		}
		cout << "\t\t";
		for (int j = 0; j < fModels[i].size(); j++)
		{
			cout << fModels[i][j] << " ";
		}
		cout << "\n";

	}
	cout << fModels.size() << "\n\n\n";
	cout << fKB.size() << "\n\n\n";
	cout << "fClauses\n" << endl;
	for (int i = 0; i < fClauses.size(); i++)
	{
		cout << fClauses[i] << " ";
	}
	cout << "\n\nfSymbols\n\n\t\t\t\t";
	for (int i = 0; i < fSymbols.size(); i++)
	{
		cout << fSymbols[i] << " ";
	}

	
	/*
	cout << "\n\size\t" << fKB.size() << "\n\n";
	
	cout << "size\t" << fSubKB[0].size() << endl;
	for (int i = 0; i < fSubKB.size(); i++)
	{
		for (int j = 0; j < fSubKB[i].size(); j++)
		{
			cout << fSubKB[i][j] << " ";
		}
		cout << "\n";
	}*/


	DevelopKB();

}

void TT::DevelopTT()
{
	//generate Truth table
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

void TT::DevelopKB()
{
	cout << "ANSWERS???\n\n";
	int count = 0;
	int lineCount = 0;
/*	for (int i = 0; i < pow(2, fModels[0].size()); i++)
	{
		lineCount = 0;
		for (int j = 0; j < fKB.size(); j++)
		{
			if (fKB[j][i] == true)
			{
				lineCount++;
			}
			if (lineCount == fKB.size())
			{
				count++;
			}
		}	
	}	
	cout << "copunt\t" << count << "\n\n";
	*/
	int lQueryLocation = 0;
	for (int i = 0; i < fSymbols.size(); i++)
	{
		if (fQuery == fSymbols[i])
		{
			lQueryLocation = i;
			cout << "location\t" << lQueryLocation << endl;
		}
	}

	for (int i = 0; i < pow(2, fModels[0].size()); i++)
	{
		bool infer{};
		infer = fKB[0][i];
		for (int j = 1; j <= fKB.size() - 1; j++)
		{
			infer = Amp(infer,fKB[j][i]);
		}

		if (infer == true)
		{
			if (fModels[i][lQueryLocation] == true)
			{
				count++;
			}	
		}
	}

	cout << "COUNT\t\t" << count << "\n\n";
}

bool TT::Implication(bool aLHS, bool aRHS)
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

bool TT::Amp(bool aLHS, bool aRHS)
{
	if (aLHS == true && aRHS == true)
		return true;
	else
		return false;
}

void TT::DevelopKnowledgeBase()
{
	int flag;
	//map fClauses with fSymbols TT of fModels to fKB
	for (size_t i = 0; i < fSubClauses.size(); i++)
	{
		
		//map values to KB
		flag = 0;
		vector<bool> lVar = {};
		string lLHS = "";
		string lRHS = "";
		string var = fSubClauses[i];
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
			flag = 1;
			size_t lIndex = var.find(sLogicConnective.AND);
			lLHS = var.substr(0, lIndex);
			lRHS = var.substr(lIndex + 1);
		}


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
		else
		{
			for (int t = 0; t < fSymbols.size(); t++)
			{
				if (var == fSymbols[t])
				{
					lSingleLocation = t;
				}
			}
		}


		for (int j = 0; j < pow(2, fSymbols.size()); j++)
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
						lVar.push_back(Implication(fSubKB[i - 1][j], fModels[j][lLocationRight]));
					}
					//a&b
					else
					{
						lVar.push_back(Amp(fModels[j][lLocationLeft], fModels[j][lLocationRight]));
					}
				}
				else if (var.find(sLogicConnective.IMPLICATION) != string::npos)
				{
					lVar.push_back(Implication(fModels[j][lLocationLeft], fModels[j][lLocationRight]));
				}
			}
			else
			{
				lVar.push_back(fModels[j][lSingleLocation]);
			}
		}
		if (flag == 0)
		{
			fKB.push_back(lVar);
		}
		fSubKB.push_back(lVar);
	}
}