#include "solution_tree.h"
#include "input_output_class.h"

int main() {
    vector<pair<short, short>> debugSolution;
    vector<pair<short, short>> debugStart{{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}};
    auto debugRoot = new solutionNode(debugStart);
    debugRoot->heuristicCalc();
    auto debugTree = new solutionTree(debugRoot);
    auto result = debugTree->findSolutionRBFS();
    
    return 0;
}
