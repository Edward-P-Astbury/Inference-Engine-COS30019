#pragma once
#include <string>
#include <vector>

class BackwardChaining
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;

public:
	BackwardChaining(std::vector<std::string> aClauses, std::vector<std::string> aQuery);
};

