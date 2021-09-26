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
    this->childrenNodes.clear();
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
            notInConflict &= abs(state[queenNum].first - state[queenNext].first) !=
                             abs(state[queenNum].second - state[queenNext].second);
            pairsInConflict += !notInConflict;
        }
    }
    this->heuristicRBFS = pairsInConflict + depth;
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

int solutionNode::getHeuristicRBFS() const {
    return heuristicRBFS;
}

void solutionNode::setHeuristicRBFS(int heuristicRbfs) {
    heuristicRBFS = heuristicRbfs;
}

void solutionNode::clearChildrenVector() {
    childrenNodes.clear();
}

vector<pair<short, short>> solutionTree::findSolutionDLS(int depthLimit) {
    //Statistics
    stats.iterations++;
    if (rootNode->isSolved()) {
        return rootNode->getState();
    } else {
        if (rootNode->getDepth() < depthLimit) {
            rootNode->generateChildrenNodes();
            //Statistics
            stats.totalStates += rootNode->getState().size() * (rootNode->getState().size() - 1);
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
    //Statistics
    stats.iterations++;
    if (curNode->isSolved()) {
        return curNode->getState();
    } else {
        if (curNode->getDepth() < depthLimit) {
            curNode->generateChildrenNodes();
            //Statistics
            stats.totalStates += rootNode->getState().size() * (rootNode->getState().size() - 1);
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
    this->stats = Stats{0, 0, 1, 1};
}

vector<pair<short, short>> solutionTree::findSolutionIDS() {
    for (int depthLimit = 0; depthLimit < INT_MAX; depthLimit++) {
        auto solution = findSolutionDLS(depthLimit);
        if (!solution.empty()) {
            return solution;
        }
        stats.memoryStates = 1;
    }
}

void solutionTree::deleteSubTree(solutionNode *curNode) {
    for (auto node : curNode->getChildrenNodes()) {
        deleteSubTree(node);
    }
    delete curNode;
}

vector<pair<short, short>> solutionTree::recursiveRBFS(solutionNode *curNode, int fLimit) {
    stats.iterations++;
    if (curNode->isSolved()) {
        return curNode->getState();
    }
    if (curNode->getChildrenNodes().empty()) {
        curNode->generateChildrenNodes();
        for (auto node : curNode->getChildrenNodes()) {
            node->heuristicCalc();
            stats.totalStates++;
        }
    }
    auto tempChildren = curNode->getChildrenNodes();
    vector<pair<short, short>> solution;
    while (true) {
        sort(tempChildren.begin(), tempChildren.end(), [](solutionNode *&a, solutionNode *&b) {
            return a->getHeuristicRBFS() < b->getHeuristicRBFS();
        });
        solutionNode *bestNode = tempChildren[0];
        auto alternativeLimit = tempChildren[1]->getHeuristicRBFS();
        if (bestNode->getHeuristicRBFS() > fLimit) {
            stats.deadEnds++;
            curNode->setHeuristicRBFS(bestNode->getHeuristicRBFS());
            for (auto node : curNode->getChildrenNodes()) {
                deleteSubTree(node);
            }
            curNode->clearChildrenVector();
            vector<pair<short, short>> noSolution;
            return noSolution;
        }
        solution = recursiveRBFS(bestNode, min(fLimit, alternativeLimit));
        if (!solution.empty()) {
            return solution;
        }
    }
}

vector<pair<short, short>> solutionTree::findSolutionRBFS() {
    stats.iterations++;
    if (rootNode->isSolved()) {
        return rootNode->getState();
    }
    if (rootNode->getChildrenNodes().empty()) {
        rootNode->generateChildrenNodes();
        for (auto node : rootNode->getChildrenNodes()) {
            node->heuristicCalc();
            stats.totalStates++;
        }
    }
    auto tempChildren = rootNode->getChildrenNodes();
    vector<pair<short, short>> solution;
    while (true) {
        sort(tempChildren.begin(), tempChildren.end(), [](solutionNode *&a, solutionNode *&b) {
            return a->getHeuristicRBFS() < b->getHeuristicRBFS();
        });
        solutionNode *bestNode = tempChildren[0];
        auto alternativeLimit = tempChildren[1]->getHeuristicRBFS();
        solution = recursiveRBFS(bestNode, alternativeLimit);
        if (!solution.empty()) {
            return solution;
        }
    }
}

void solutionTree::countNodesInTree(solutionNode *curNode, int &counter) {
    counter++;
    for (auto node : curNode->getChildrenNodes()) {
        countNodesInTree(node, counter);
    }
}

void solutionTree::showStats() {
    int counter = 0;
    countNodesInTree(rootNode, counter);
    stats.memoryStates = counter;
    cout << "Iterations: " << stats.iterations << '\n';
    cout << "Dead-ends (for RBFS): " << stats.deadEnds << '\n';
    cout << "Total states: " << stats.totalStates << '\n';
    cout << "States in memory: " << stats.memoryStates << '\n';
}
