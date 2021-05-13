#include "TT.h"
#include <cmath>
#include <iostream>

using namespace std;

TT::TT(std::vector<std::string> aClauses, std::string aQuery, std::vector<std::string> aSymbols)
{
	fClauses = aClauses;
	fQuery = aQuery;
	fSymbols = aSymbols;
}

bool TT::TTEntails(std::vector<std::vector<bool>> aKB, std::vector<std::string> aAlpha)
{
	return false;
}

bool TT::TTCheckAll(std::vector<std::vector<bool>> aKB, std::vector<std::string> aAlpha, std::vector<std::string> aSymbols, std::vector<std::vector<bool>> aModels)
{
	return false;
}

bool TT::Implication(bool aLHS, bool aRHS)
{
	if (aLHS == true && aRHS == true)
		return true;
	if (aLHS == true && aRHS == false)
		return false;
	if (aLHS == false && aRHS == true)
		return true;
	if (aLHS == false && aRHS == false)
		return true;
}

bool TT::Amp(bool aLHS, bool aRHS)
{
	if (aLHS == true && aRHS == true)
		return true;
	else
		return false;
}