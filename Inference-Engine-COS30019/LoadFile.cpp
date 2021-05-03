#include "LoadFile.h"
#include <iostream>
#include <fstream>

using namespace std;

LoadFile::LoadFile(std::string aFileName)
{
	fFileName = aFileName;
}

void LoadFile::ReadFile()
{
	string lClause, lTempClause, lTell;
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
		cout << lClause << endl;
		fClauses.push_back(lClause);
	}

	while (!lInFile.eof())
	{
		lInFile >> lTell;
		fQuery.push_back(lTell);
		cout << "\nTell\t" << lTell << endl;
	}
}

std::vector<std::string> LoadFile::GetClauses()
{
	return fClauses;
}

std::vector<std::string> LoadFile::GetQuery()
{
	return fQuery;
}
