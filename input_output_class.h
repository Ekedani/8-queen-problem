#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

class inputOutputClass {
public:
    //Used to generate random queen sets
    static vector<pair<short, short>> generateRandomQueens(short numOfQueens);

    static vector<pair<short, short>> userInputQueens(short numOfQueens);

    static void outputTable(const vector<pair<short, short>> &result);

    static void outputList(const vector<pair<short, short>> &result);
};
