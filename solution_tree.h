#include <vector>
#include <utility>

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

    //TODO: Implement bool method isSolved for increasing efficiency
};

class solutionTree {
private:
    solutionNode *rootNode;
    const short QUEEN_AMOUNT;
public:
    vector<pair<short, short>> findSolutionIDS() {

    }

    vector<pair<short, short>> findSolutionRBFS() {

    }
};
