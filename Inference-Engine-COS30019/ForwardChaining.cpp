#include "ForwardChaining.h"
#include <iostream>

using namespace std;

struct sLogicalConnectives
{
	string IMPLICATION = "=>";
	string AND = "&";
}; sLogicalConnectives sLogicConnectiveFC;

ForwardChaining::ForwardChaining(std::vector<std::string> aClauses, std::string aQuery)
{
	fClauses = aClauses;
	fQuery = aQuery;

	AddFactsAndHornClauses();
	cout << FactOutput();
}

std::string ForwardChaining::FactOutput()
{
	string lPrintResult;

	if (FactValidation() == true)
	{
		lPrintResult = "> YES: ";

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

bool ForwardChaining::FactValidation()
{
	// keep looping until the vector is empty
	while (fFacts.size() != 0)
	{
		// assign local variable then pop off the first variable from vector
		string lFact = fFacts.front();
		fFacts.erase(fFacts.begin());

		// add the variable to the result vector if it is true
		fResultFacts.push_back(lFact);

		// return true if the current variable matches the query
		if (lFact == fQuery)
		{
			//cout << "Variable matches query" << endl;
			return true;
		}

		for (int i = 0; i < fHornClause.size(); i++)
		{
			if(fHornClause[i].find(lFact) != string::npos)
			{
				if(fHornClause[i].find(sLogicConnectiveFC.AND) != string::npos)
				{
					// if the clause we are checking already has facts which are part of the list of facts there is no need to extend down this path
					// therefore we can delete the clause from the list of clauses
					string lTempCheck;

					size_t lIndexCheck = fHornClause[i].find(sLogicConnectiveFC.IMPLICATION);
					lTempCheck = fHornClause[i].substr(lIndexCheck + 2); // value after implication

					for (int j = 0; j < fResultFacts.size(); j++)
					{
						if (fResultFacts[j] == lTempCheck)
						{
							fHornClause.erase(fHornClause.begin() + i);
							break; ///// this break may not be necessary, need to conduct more tests...
						}
					}

					size_t lIndexAnd = fHornClause[i].find(sLogicConnectiveFC.AND);

					string lTempValueAfterAnd = fHornClause[i].substr(lIndexAnd + 1);

					size_t lIndexImplication = lTempValueAfterAnd.find(sLogicConnectiveFC.IMPLICATION);

					lTempValueAfterAnd = lTempValueAfterAnd.substr(0, lIndexImplication);

					string lTempValueBeforeAnd = fHornClause[i].substr(0, lIndexAnd);

					// say we have the string 'b&e=>f', it has now been trimmed to the value after the '&', in this case 'e'
					// 
					// need to check whether the value after the '&', in this case 'e' is part of the current facts. 
					// If it is, then we can push back 'f', the value after the implication into the list of facts.
					// We are then done with that particular horn clause (it has been checked) therefore we can erase it.
					// This logic also applies for the value prior to the '&'.
					for (int j = 0; j < fResultFacts.size(); j++)
					{
						if (fResultFacts[j] == lTempValueAfterAnd)
						{
							for (int k = 0; k < fResultFacts.size(); k++)
							{
								if (fResultFacts[k] == lTempValueBeforeAnd)
								{
									string lTempImplication;

									size_t lIndex = fHornClause[i].find(sLogicConnectiveFC.IMPLICATION);
									lTempImplication = fHornClause[i].substr(lIndex + 2); // value after the implication

									fHornClause.erase(fHornClause.begin() + i);
									fFacts.push_back(lTempImplication);

									break;
								}
							}
						}
					}
				}
				else
				{
					// if the clause we are checking already has facts which are part of the list of facts there is no need to extend down this path
					// therefore we can delete the clause from the list of clauses
					string lTempCheck;

					size_t lIndexCheck = fHornClause[i].find(sLogicConnectiveFC.IMPLICATION);
					lTempCheck = fHornClause[i].substr(lIndexCheck + 2); // value after implication

					for (int j = 0; j < fResultFacts.size(); j++)
					{
						if (fResultFacts[j] == lTempCheck)
						{
							fHornClause.erase(fHornClause.begin() + i);
							break; ///// this break may not be necessary, need to conduct more tests...
						}
					}

					size_t lIndex = fHornClause[i].find(sLogicConnectiveFC.IMPLICATION);

					// ensure the value being checked occurs before the implication
					string lClauseBeforeImplication = fHornClause[i].substr(0, lIndex);

					if (lFact == lClauseBeforeImplication)
					{
						string lTemp;

						size_t lIndex = fHornClause[i].find(sLogicConnectiveFC.IMPLICATION);
						lTemp = fHornClause[i].substr(lIndex + 2); // value after implication

						// delete clause from vector once we satisfy it
						fHornClause.erase(fHornClause.begin() + i);

						fFacts.push_back(lTemp);

						break;
					}
				}
			}
		}
	}
	return false;
}

void ForwardChaining::AddFactsAndHornClauses()
{
	for (string& s : fClauses)
	{
		if (s.find(sLogicConnectiveFC.IMPLICATION) != string::npos)
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
