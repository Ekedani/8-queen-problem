#include "solution_tree.h"
#include "iostream"

int main() {
    vector<pair<short, short>> debugSolution;
    vector<pair<short, short>> debugStart{{1, 0},
                                          {2, 1},
                                          {0, 2},
                                          {2, 3}};
    auto debugRoot = new solutionNode(debugStart);
    std::cout << debugRoot->isSolved() << '\n';
    auto debugTree = new solutionTree(debugRoot);
    auto debugResult = debugTree->findSolutionDLS(1000);
    cout << debugResult.size();
    return 0;
}
