#pragma once
#include <string>
#include <vector>

class ForwardChaining
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;
	std::vector<std::string> fVariables;
	std::vector<std::string> fResultFacts;
	std::vector<std::string> fFacts;
	std::vector<std::string> fHornClause;

public:
	ForwardChaining(std::vector<std::string> aClauses, std::vector<std::string> aQuery);
	std::string FactOutput();
	bool FactValidation();
	void AddFactsAndHornClauses();
};

