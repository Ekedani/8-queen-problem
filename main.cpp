#include "solution_tree.h"
#include "iostream"

int main() {
    vector<pair<short, short>> debugSolution;
    vector<pair<short, short>> debugStart{{1, 0},
                                          {1, 1},
                                          {1, 2},
                                          {1, 3}};
    auto debugRoot = new solutionNode(debugStart);
    std::cout << debugRoot->isSolved() << '\n';
    auto debugTree = new solutionTree(debugRoot);
    auto debugResult = debugTree->findSolutionIDS();
    cout << debugResult.size();
    cout << '\n';
    for(auto queen : debugResult){
        cout << queen.first << "-" << queen.second << ',';
    }
    cout << '\n';
    return 0;
}
