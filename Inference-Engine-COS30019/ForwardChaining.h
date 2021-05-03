#pragma once
#include <string>
#include <vector>

class ForwardChaining
{
private:
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;

public:
	ForwardChaining(std::vector<std::string> aClauses, std::vector<std::string> aQuery);
};

