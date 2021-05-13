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
		//lPrintResult = "NO: " + fQuery[0] + " could not be proven.";
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
					size_t lIndexAnd = fHornClause[i].find(sLogicConnectiveFC.AND);

					string lTemp = fHornClause[i].substr(lIndexAnd + 1);

					size_t lIndexImplication = lTemp.find(sLogicConnectiveFC.IMPLICATION);

					lTemp = lTemp.substr(0, lIndexImplication);

					// say we have the string 'b&e=>f', it has now been trimmed to the value after the '&', in this case 'e'
					// 
					// need to check whether the value after the '&', in this case 'e' is part of the current facts. 
					// If it is, then we can push back 'f', the value after the implication into the list of facts.
					// We are then done with that particular horn clause (it has been checked) therefore we can erase it
					for (int j = 0; j < fFacts.size(); j++)
					{
						if (fFacts[j] == lTemp)
						{
							string lTempImplication;

							size_t lIndex = fHornClause[i].find(sLogicConnectiveFC.IMPLICATION);
							lTempImplication = fHornClause[i].substr(lIndex + 2); // value after the implication

							fHornClause.erase(fHornClause.begin() + i);
							fFacts.push_back(lTempImplication);
						}
					}
				}
				else
				{
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

						//cout << "Value added: " << lTemp << endl;

						fFacts.push_back(lTemp);
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
