//
// Created by User on 20.09.2021.
//

#include "input_output_class.h"

void inputOutputClass::outputTable(const vector<pair<short, short>> &result) {
    char **boardVisualization = new char*[result.size()];
    for (int i = 0; i < result.size(); ++i) {
        boardVisualization[i] = new char[result.size()];
        for (int j = 0; j < result.size(); ++j) {
            boardVisualization[i][j] = '.';
        }
    }
    for (auto queen : result) {
        boardVisualization[queen.first][queen.second] = 'X';
    }
    for (int i = 0; i < result.size(); ++i) {
        for (int j = 0; j < result.size(); ++j) {
            cout << boardVisualization[i][j] << ' ';
        }
        cout << '\n';
    }
}

vector<pair<short, short>> inputOutputClass::generateRandomQueens(short numOfQueens) {
    srand(time(nullptr));
    vector<pair<short, short>> result;
    for (int i = 0; i < numOfQueens; ++i) {
        pair<short, short> tmpPair {(rand() % numOfQueens), i};
        result.push_back(tmpPair);
    }
}

vector<pair<short, short>> inputOutputClass::userInputQueens(short numOfQueens) {
    vector<pair<short, short>> result;
    for (int i = 0; i < numOfQueens; ++i) {
        short inputTmp;
        cout << "Input horizontal coordinate for queen on vertical number " << i << ":";
        cin >> inputTmp;
        pair<short, short> tmpPair {(inputTmp % numOfQueens), i};
        result.push_back(tmpPair);
    }
}

void inputOutputClass::outputList(const vector<pair<short, short>> & result) {
    for(auto queen : result){
        cout << '{' << queen.first << ',' << queen.second << '}' << "   ";
    }
    cout << '\n';
}
