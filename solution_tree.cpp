#include "solution_tree.h"

solutionNode::solutionNode(vector<pair<short, short>> &startState) {
    this->state = startState;
    this->depth = 0;
    this->parentNode = nullptr;
}

solutionNode::solutionNode(solutionNode &parentNode) {
    this->state = parentNode.state;
    this->depth = parentNode.depth + 1;
    this->parentNode = &parentNode;
}

void solutionNode::generateChildrenNodes() {
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

int solutionNode::heuristicCalc() {
    int pairsInConflict = 0;
    for (auto queenNum = 0; queenNum < state.size(); ++queenNum) {
        for (auto queenNext = queenNum + 1; queenNext < state.size(); ++queenNext) {
            bool notInConflict = true;
            //Checking vertical conflict
            notInConflict &= state[queenNum].first != state[queenNext].first;
            //Checking diagonal conflict
            notInConflict &= abs(state[queenNum].first - state[queenNext].first) ==
                             abs(state[queenNum].second - state[queenNext].second);
            pairsInConflict += notInConflict;
        }
    }
    return pairsInConflict;
}

bool solutionNode::isSolved() {
    bool noConflicts = true;
    for (auto queenNum = 0; queenNum < state.size() && noConflicts; ++queenNum) {
        for (auto queenNext = queenNum + 1; queenNext < state.size() && noConflicts; ++queenNext) {
            //Checking vertical conflict
            noConflicts &= state[queenNum].first != state[queenNext].first;
            //Checking diagonal conflict
            noConflicts &= abs(state[queenNum].first - state[queenNext].first) !=
                           abs(state[queenNum].second - state[queenNext].second);
        }
    }
    return noConflicts;
}

int solutionNode::getDepth() const {
    return depth;
}

solutionNode *solutionNode::getParentNode() const {
    return parentNode;
}

vector<pair<short, short>> solutionNode::getState() const {
    return state;
}

vector<solutionNode *> solutionNode::getChildrenNodes() const {
    return childrenNodes;
}

vector<pair<short, short>> solutionTree::findSolutionDLS(int depthLimit) {
    if (rootNode->isSolved()) {
        return rootNode->getState();
    } else {
        if (rootNode->getDepth() < depthLimit) {
            rootNode->generateChildrenNodes();
            vector<solutionNode *> curChildren = rootNode->getChildrenNodes();
            for (auto node : curChildren) {
                vector<pair<short, short>> solution = recursiveDLS(depthLimit, node);
                if (!solution.empty()) {
                    return solution;
                }
            }
        }
        vector<pair<short, short>> noSolution;
        return noSolution;
    }
}

vector<pair<short, short>> solutionTree::recursiveDLS(int depthLimit, solutionNode *curNode) {
    if (curNode->isSolved()) {
        return curNode->getState();
    } else {
        if (curNode->getDepth() < depthLimit) {
            curNode->generateChildrenNodes();
            vector<solutionNode *> curChildren = curNode->getChildrenNodes();
            for (auto node : curChildren) {
                vector<pair<short, short>> solution = recursiveDLS(depthLimit, node);
                if (!solution.empty()) {
                    return solution;
                }
            }
        }
        vector<pair<short, short>> noSolution;
        return noSolution;
    }
}

solutionTree::solutionTree(solutionNode *rootNode) {
    this->rootNode = rootNode;
    this->queenAmount = rootNode->getState().size();
}
