#include "BackwardChaining.h"
#include <iostream>

using namespace std;

struct sLogicalConnectives
{
	string IMPLICATION = "=>";
	string AND = "&";
}; sLogicalConnectives sLogicConnectiveBC;

BackwardChaining::BackwardChaining(std::vector<std::string> aClauses, std::vector<std::string> aQuery)
{
	fClauses = aClauses;
	fQuery = aQuery;

	AddFactsAndHornClauses();

	cout << FactOutput();
}

std::string BackwardChaining::FactOutput()
{
	string lPrintResult;

	if (FactValidation() == true)
	{
		lPrintResult = "> YES: ";

		// traverse vector backwards
		for (int i = fResultFacts.size() - 1; i >= 0; i--)
		{
			lPrintResult += fResultFacts[i];

			if (i != 0)
				lPrintResult += ", ";
		}
	}
	else
	{
		lPrintResult = "NO: " + fQuery[0] + " could not be proven.";
	}

	return lPrintResult;
}

bool BackwardChaining::FactValidation()
{
	string lInitialQuery;

	for (int i = 0; i < fHornClause.size(); i++)
	{
		string lTempImplication;

		size_t lIndex = fHornClause[i].find(sLogicConnectiveBC.IMPLICATION);
		lTempImplication = fHornClause[i].substr(lIndex + 2); // value after the implication

		if (lTempImplication.find(fQuery[0]) != string::npos)
		{
			lInitialQuery = fHornClause[i];
		}
	}

	// we need to initially check whether or not the list of clauses contains the query we wish to prove
	// if it does not then there is no way to satisfy the remaining clauses, so we return false
	// otherwise we can enter the core loop and proceed with the algorithm
	if (find(fHornClause.begin(), fHornClause.end(), lInitialQuery) != fHornClause.end())
	{
		//cout << "found element" << endl;
	}
	else
	{
		//cout << "cannot find element" << endl;
		return false;
	}

	// place the initial query into the list
	fClausesLoop.insert(fClausesLoop.begin(), fQuery[0]);

	while (fClausesLoop.size() != 0)
	{
		// assign local variable then pop off the first variable from vector
		string lQuery = fClausesLoop.front();
		fClausesLoop.erase(fClausesLoop.begin());

		// add the variable to the result vector if it is true
		fResultFacts.push_back(lQuery);

		for (int i = 0; i < fHornClause.size(); i++)
		{
			string lTempImplication;

			size_t lIndex = fHornClause[i].find(sLogicConnectiveBC.IMPLICATION);
			lTempImplication = fHornClause[i].substr(lIndex + 2); // value after the implication

			if (lTempImplication.find(lQuery) != string::npos)
			{
				// now we need to extract the value before the implication and then we can delete that element from the list of clauses

				size_t lIndex = fHornClause[i].find(sLogicConnectiveBC.IMPLICATION);

				// ensure the value being checked occurs before the implication
				string lClauseBeforeImplication = fHornClause[i].substr(0, lIndex);

				fHornClause.erase(fHornClause.begin() + i); // erase element from the vector of clauses once it has been checked 

				fClausesLoop.insert(fClausesLoop.begin(), lClauseBeforeImplication); // add the newly acquired value
			}
		}
	}

	// we can return true because the size of the vector is 0, therefore proving there is no more clauses to satisfy
	return true;
}

void BackwardChaining::AddFactsAndHornClauses()
{
	for (string& s : fClauses)
	{
		if (s.find(sLogicConnectiveBC.IMPLICATION) != string::npos)
		{
			// horn clause
			fHornClause.push_back(s);
		}
		else
		{
			// fact
			fFacts.push_back(s);
		}
	}
}
