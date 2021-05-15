#pragma once
#include <string>
#include <vector>

class LoadFile
{
private:
	std::string fFileName;
	std::vector<std::string> fClauses;
	std::vector<std::string> fSubClauses;
	std::vector<std::string> fSymbols;
	std::string fQuery;

public:

	LoadFile(std::string aFileName);
	void ReadFile();										//Read in Text File
	void Set();												//Setup LoadFile after reading in File
	std::vector<std::string> GetClauses();					//Clauses
	std::vector<std::string> GetSubClauses();				//Sub Clauses ie b&e, b&e=>f, etc
	std::vector<std::string> GetSymbols();					//Symbols from clauses
	std::string GetQuery();									//Ask query
	void AddVariables();									//Find symbols from clauses
	std::string CheckAmpersand(std::string& aString);		//Check for & in clauses
	std::string CheckImplication(std::string& aString);		//Check for => in clauses
	std::string GetAndSubClause(std::string& aString);		//save before & and after ie a&b=>c: saves a and save b=>c
	void Sort();											//Delete double ups in symbols vector
};

