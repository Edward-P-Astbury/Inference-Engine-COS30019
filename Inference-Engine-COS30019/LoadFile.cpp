#include "LoadFile.h"
#include <iostream>
#include <fstream>
#include "LogicalConnectives.h"

static sLogicalConnectives sLogicalConnective;

using namespace std;

LoadFile::LoadFile(std::string aFileName)
{
	fFileName = aFileName;
}

void LoadFile::ReadFile()
{
	string lClause, lTempClause, lTell, lQuery;
	ifstream lInFile;
	lInFile.open(fFileName);

	if (lInFile.fail())
	{
		std::cerr << "Cannot open input file " << fFileName << std::endl;
		exit(1);
	}

	lInFile >> lTell;

	while (!lInFile.eof())
	{
		lInFile >> lClause;
		if (lClause == "ASK")
		{
			break;
		}

		while (lClause.substr(lClause.length() - 1, lClause.length()) != ";")
		{
			lInFile >> lTempClause;
			lClause += lTempClause;
		}

		lClause = lClause.substr(0, lClause.length() - 1);
		fClauses.push_back(lClause);
	}

	while (!lInFile.eof())
	{
		lInFile >> lQuery;
		fQuery = lQuery;
	}
}

void LoadFile::Set()
{
	AddVariables();
	fSymbols.push_back(fQuery);	//add query to the list of symbols
	Sort();
	Sort();
}

vector<string> LoadFile::GetClauses()
{
	return fClauses;
}

string LoadFile::GetQuery()
{
	return fQuery;
}

vector<string> LoadFile::GetSubClauses()
{
	return fSubClauses;
}

std::vector<std::string> LoadFile::GetSymbols()
{
	return fSymbols;
}

void LoadFile::AddVariables()
{
	for (string& s : fClauses)
	{
		bool complete = false;
		string lvar = s;
		string lSubVar = s;

		lSubVar = GetAndSubClause(lSubVar);

		if (lSubVar != "" && lSubVar != s)
		{
			//check for multiple &'s
			while (lSubVar.find(sLogicalConnective.AND) != string::npos)
			{
				//Trim each statement before &
				lSubVar = CheckAmpersand(lSubVar);
			}
			fSymbols.push_back(lSubVar);
		}

		lvar = CheckImplication(lvar);
		fSymbols.push_back(lvar);

		fSubClauses.push_back(s);
	}
}

string LoadFile::CheckAmpersand(string& aString)
{
	string var = aString;

	if (aString.find(sLogicalConnective.AND) != string::npos)
	{
		size_t lIndex = aString.find(sLogicalConnective.AND);
		var = aString.substr(0, lIndex);
		fSymbols.push_back(var);
		var = aString.substr(lIndex + 1);
	}

	return var;
}

string LoadFile::CheckImplication(string& aString)
{
	string var = aString;

	if (aString.find(sLogicalConnective.IMPLICATION) != string::npos)
	{
		size_t lIndex = aString.find(sLogicalConnective.IMPLICATION);
		var = aString.substr(lIndex + 2);
	}

	return var;
}

std::string LoadFile::GetAndSubClause(std::string& aString)
{
	string var = aString;

	// if the string contains a '&' then we want the entire string prior to the '=>'
	if (aString.find(sLogicalConnective.AND) != string::npos)
	{
		size_t lIndex = aString.find(sLogicalConnective.IMPLICATION);
		var = aString.substr(0, lIndex);
		fSubClauses.push_back(var);

		return var;
	}

	return "";
}

void LoadFile::Sort()
{
	// delete multiple elements of the same type in fVariables
	for (int i = 0; i < fSymbols.size(); i++)
	{
		for (int j = 1 + i; j < fSymbols.size(); j++)
		{
			if (fSymbols[i] == fSymbols[j])
			{
				fSymbols.erase(fSymbols.begin() + j);
			}
		}
	}
}