#pragma once
#include <string>
#include <vector>

class BackwardChaining
{
private:
	std::vector<std::string> fClauses;
	std::string fQuery;
	std::vector<std::string> fResultFacts;
	std::vector<std::string> fFacts;
	std::vector<std::string> fHornClause;
	std::vector<std::string> fClausesLoop;

public:
	BackwardChaining(std::vector<std::string> aClauses, std::string aQuery);
	std::string FactOutput(); // Prints the resulting facts
	bool FactValidation(); // Core algorithm
	void AddFactsAndHornClauses(); // Seperates the facts and clauses from the text file
};
