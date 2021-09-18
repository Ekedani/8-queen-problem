#include <vector>
#include <utility>

using namespace std;

class solutionNode {
    vector<pair<short, short>> state;
    int depth;
    solutionNode *parentNode;
    vector<solutionNode *> childrenNodes;
    //Possible to add "action" attribute for more obvious path

public:
    solutionNode(solutionNode &parentNode) {

    }

    int heuristicCalc() {

    };
};

class solutionTree {
private:
    solutionNode *rootNode;
    const short QUEEN_AMOUNT;
public:
    vector<pair<short, short>> findSolutionIDS() {

    }


};
