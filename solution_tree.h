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
    explicit solutionNode(vector<pair<short, short>> &startState) {
        this->state = startState;
        this->depth = 0;
        this->parentNode = nullptr;
    }

    solutionNode(solutionNode &parentNode) {
        this->state = parentNode.state;
        this->depth = parentNode.depth + 1;
        this->parentNode = &parentNode;
    }

    void generateChildrenNodes() {
        for (auto queenNum = 0; queenNum < state.size(); queenNum++) {
            for (auto x = 0; x < state.size(); x++) {
                //Horizontal movement (Changing first coordinate)
                if (x == state[queenNum].first) {
                    //Skipping the parent state
                    continue;
                }
                auto newChild = new solutionNode(*this);
                newChild->state[queenNum].first = x;
                this->childrenNodes.push_back(newChild);
            }
        }
    }

    int heuristicCalc() {
        int pairsInConflict = 0;
        for (auto queenNum = 0; queenNum < state.size(); ++queenNum) {
            for (auto queenNext = queenNum + 1; queenNext < state.size(); ++queenNext) {
                bool notInConflict = true;
                //Checking vertical conflict
                notInConflict &= state[queenNum].first != state[queenNext].first;
                //Checking diagonal conflict
                notInConflict &= (state[queenNum].first - state[queenNext].first) ==
                                 (state[queenNum].second - state[queenNext].second);
                pairsInConflict += notInConflict;
            }
        }
        return pairsInConflict;
    }
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
