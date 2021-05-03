#pragma once
#include <string>
#include <vector>

class LoadFile
{
private:
	std::string fFileName;
	std::vector<std::string> fClauses;
	std::vector<std::string> fQuery;
public:

	LoadFile(std::string aFileName);
	void ReadFile();
	std::vector<std::string> GetClauses();
	std::vector<std::string> GetQuery();
};

