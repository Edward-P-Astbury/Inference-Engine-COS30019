#include "BackwardChaining.h"
#include <iostream>
#include "LogicalConnectives.h"

static sLogicalConnectives sLogicalConnective;

using namespace std;

BackwardChaining::BackwardChaining(std::vector<std::string> aClauses, std::string aQuery)
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

		// reverse the vector for printing
		reverse(fResultFacts.begin(), fResultFacts.end());

		for (int i = 0; i < fResultFacts.size(); i++)
		{
			lPrintResult += fResultFacts[i];

			if (i < fResultFacts.size() - 1)
			{
				lPrintResult += ", ";
			}
		}
	}
	else
	{
		lPrintResult = "NO: " + fQuery + " could not be proven.";
	}

	return lPrintResult;
}

bool BackwardChaining::FactValidation()
{
	// if there is no facts then we cannot initiate the BC algorithm, therefore we return false
	if (fFacts.empty() == true)
	{
		return false;
	}

	string lInitialQuery;

	for (int i = 0; i < fHornClause.size(); i++)
	{
		string lTempImplication;

		size_t lIndex = fHornClause[i].find(sLogicalConnective.IMPLICATION);
		lTempImplication = fHornClause[i].substr(lIndex + 2); // value after the implication

		if (lTempImplication.find(fQuery) != string::npos)
		{
			lInitialQuery = fHornClause[i];
		}
	}

	// we need to initially check whether or not the list of clauses contains the query we wish to prove
	// if it does not then there is no way to satisfy the remaining clauses, so we return false
	// otherwise we can enter the core loop and proceed with the algorithm
	if (find(fHornClause.begin(), fHornClause.end(), lInitialQuery) != fHornClause.end())
	{
		// element is found, no need to return false
	}
	else
	{
		return false;
	}

	// place the initial query into the list
	fClausesLoop.insert(fClausesLoop.begin(), fQuery);

	for (string& s : fFacts)
	{
		if (s.find(fQuery) != string::npos)
		{
			fResultFacts.push_back(fQuery);
			return true;
		}
	}

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

			size_t lIndex = fHornClause[i].find(sLogicalConnective.IMPLICATION);
			lTempImplication = fHornClause[i].substr(lIndex + 2); // value after the implication

			if (lTempImplication.find(lQuery) != string::npos)
			{
				if (fHornClause[i].find(sLogicalConnective.AND) != string::npos)
				{
					size_t lIndexAnd = fHornClause[i].find(sLogicalConnective.AND);

					string lTempValueAfterAnd = fHornClause[i].substr(lIndexAnd + 1);

					size_t lIndexImplication = lTempValueAfterAnd.find(sLogicalConnective.IMPLICATION);

					lTempValueAfterAnd = lTempValueAfterAnd.substr(0, lIndexImplication);

					string lTempValueBeforeAnd = fHornClause[i].substr(0, lIndexAnd);

					for (int j = 0; j < fFacts.size(); j++)
					{
						if (lTempValueAfterAnd == fFacts[j] && lTempValueBeforeAnd != fFacts[j])
						{
							// push on the value before
							fHornClause.erase(fHornClause.begin() + i);

							fClausesLoop.insert(fClausesLoop.begin(), lTempValueBeforeAnd);

							break; // we can now break once we have added the value
						}
						if (lTempValueBeforeAnd == fFacts[j] && lTempValueAfterAnd != fFacts[j]) // check for the other condition
						{
							fHornClause.erase(fHornClause.begin() + i);

							fClausesLoop.insert(fClausesLoop.begin(), lTempValueAfterAnd);

							break;
						}
						if (lTempValueBeforeAnd != fFacts[j] && lTempValueAfterAnd != fFacts[j])
						{
							// we will begin with iterating down the value before the '&', thus we will push it on first
							fHornClause.erase(fHornClause.begin() + i);

							fClausesLoop.insert(fClausesLoop.begin(), lTempValueAfterAnd);
							fClausesLoop.insert(fClausesLoop.begin(), lTempValueBeforeAnd);

							break;
						}
					}
				}
				else
				{
					// now we need to extract the value before the implication and then we can delete that element from the list of clauses

					size_t lIndex = fHornClause[i].find(sLogicalConnective.IMPLICATION);

					// ensure the value being checked occurs before the implication
					string lClauseBeforeImplication = fHornClause[i].substr(0, lIndex);

					fHornClause.erase(fHornClause.begin() + i); // erase element from the vector of clauses once it has been checked

					fClausesLoop.insert(fClausesLoop.begin(), lClauseBeforeImplication); // add the newly acquired value
				}
			}
		}
	}

	// Clear duplicate values, this prevents the algorithm from searching for any more facts that have already been explored
	for (int i = 0; i < fResultFacts.size(); i++)
	{
		for (int j = i + 1; j < fResultFacts.size(); j++)
		{
			if (fResultFacts[i] == fResultFacts[j])
			{
				fResultFacts.erase(fResultFacts.begin() + j);
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
		if (s.find(sLogicalConnective.IMPLICATION) != string::npos)
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
