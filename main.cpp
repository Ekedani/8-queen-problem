#include "solution_tree.h"
#include "input_output_class.h"

int main() {
    auto startSet = inputOutputClass::getQueens(8);
    cout << "Start state: " << '\n';
    inputOutputClass::outputList(startSet);

    auto rootNode = new solutionNode(startSet);
    auto resultTree = new solutionTree(rootNode);

    bool methodChoice;
    cout << "Input 0 for non-informative and 1 for informative search: ";
    cin >> methodChoice;
    vector<pair<short, short>> resultState;
    if (methodChoice) {
        resultState = resultTree->findSolutionRBFS();
    } else {
        resultState = resultTree->findSolutionIDS();
    }

    cout << "Result state: " << '\n';
    inputOutputClass::outputList(resultState);
    inputOutputClass::outputTable(resultState);
    resultTree->showStats();
    return 0;
}
