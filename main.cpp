#include "solution_tree.h"
#include "input_output_class.h"

int main() {
    auto debugStart = inputOutputClass::getQueens(8);
    cout << "Start state: " << '\n';
    inputOutputClass::outputList(debugStart);

    auto debugRoot = new solutionNode(debugStart);
    auto debugTree = new solutionTree(debugRoot);

    bool methodChoice;
    cout << "Input 0 for non-informative and 1 for informative search: "; cin >> methodChoice;
    vector<pair<short, short>> result;
    if(methodChoice){
        result = debugTree->findSolutionRBFS();
    }
    else{
        result = debugTree->findSolutionIDS();
    }

    cout << "Result state: " << '\n';
    inputOutputClass::outputList(result);
    inputOutputClass::outputTable(result);
    return 0;
}
