#include <vector>
#include <utility>
#include "iostream"

using namespace std;

class solutionNode {
private:
    vector<pair<short, short>> state;
    int depth;
    solutionNode *parentNode;
    vector<solutionNode *> childrenNodes;
    //Possible to add "action" attribute for more obvious path

public:
    explicit solutionNode(vector<pair<short, short>> &startState);

    solutionNode(solutionNode &parentNode);

    void generateChildrenNodes();

    int heuristicCalc();

    bool isSolved();

    [[nodiscard]] int getDepth() const;

    [[nodiscard]] solutionNode *getParentNode() const;

    [[nodiscard]] vector<pair<short, short>> getState() const;

    [[nodiscard]] vector<solutionNode *> getChildrenNodes() const;

    void debugStateOut() {
        for (auto queen : state) {
            cout << '{' << queen.first << ',' << queen.second << "}, ";
        }
        cout << '\n';
    };
};

class solutionTree {
private:
    solutionNode *rootNode;
    short queenAmount;

    //Methods for IDS
public:
    vector<pair<short, short>> findSolutionDLS(int depthLimit);

    vector<pair<short, short>> recursiveDLS(int depthLimit, solutionNode *curNode);

public:
    explicit solutionTree(solutionNode *rootNode);

    vector<pair<short, short>> findSolutionIDS();

    vector<pair<short, short>> findSolutionRBFS() {

    }
};
