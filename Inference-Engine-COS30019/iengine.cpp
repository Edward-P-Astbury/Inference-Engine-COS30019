#include <iostream>
#include "LoadFile.h"
//#include "TruthTable.h"
#include "ForwardChaining.h"
#include "BackwardChaining.h"
#include "TruthTable.h"

/*
    Authors: Lane Macdonald (101614172) & Edward Astbury (102579434)

    We would like to acknowledge the COS30019 teaching staff for their support throughout
    the duration of the project. All of our external sources/acknowledgements have been appropriately
    listed in the report section of this assignment.
*/

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cerr << "Arguments missing." << endl;
        cerr << "iengine <method> <filename>" << endl;

        return 1;
    }

    string lMethod = argv[1];   // method
    string lFileName = argv[2]; // program file name 
    LoadFile lFile(lFileName);  // load file into program

    lFile.ReadFile();
    lFile.Set();

    // testing implementation
    if (lMethod == "TT")
    {
        TruthTable TT(lFile.GetClauses(), lFile.GetQuery(), lFile.GetSymbols(), lFile.GetSubClauses());
    }
    else if (lMethod == "FC")
    {
        ForwardChaining FC(lFile.GetClauses(), lFile.GetQuery());
    }
    else if (lMethod == "BC")
    {
        BackwardChaining BC(lFile.GetClauses(), lFile.GetQuery());
    }

    return 0;
}