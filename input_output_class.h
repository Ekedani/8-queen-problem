#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

class inputOutputClass {
public:
    static vector<pair<short, short>> getQueens(short numOfQueens) {
        short choiceVar;
        vector<pair<short, short>> queens;
        cout << "Select method of creating queen set: " << '\n' << "0 for random generation" << '\n'
             << "1 for user input" << '\n' << "2 for preset list" << '\n';
        cin >> choiceVar;
        choiceVar %= 3;
        switch (choiceVar) {
            case 0:
                queens = generateRandomQueens(numOfQueens);
                break;
            case 1:
                queens = userInputQueens(numOfQueens);
                break;
            case 2:
                queens = {{0, 0},
                          {0, 1},
                          {0, 2},
                          {0, 3},
                          {0, 4},
                          {0, 5},
                          {0, 6},
                          {0, 7}};
                break;
            default:
                queens = generateRandomQueens(numOfQueens);
        }
        return queens;
    }

    static vector<pair<short, short>> generateRandomQueens(short numOfQueens);

    static vector<pair<short, short>> userInputQueens(short numOfQueens);

    static void outputTable(const vector<pair<short, short>> &result);

    static void outputList(const vector<pair<short, short>> &result);
};
