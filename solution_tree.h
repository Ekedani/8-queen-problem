#include <vector>
#include <utility>
#include "iostream"
#include <algorithm>

using namespace std;

class solutionNode {
private:
    vector<pair<short, short>> state;
    int depth;
    int heuristicRBFS;
public:
    void setHeuristicRBFS(int heuristicRbfs);

public:
    int getHeuristicRBFS() const;

private:
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
    vector<pair<short, short>> findSolutionDLS(int depthLimit);

    vector<pair<short, short>> recursiveDLS(int depthLimit, solutionNode *curNode);

    vector<pair<short, short>> recursiveRBFS(solutionNode* curNode, int fLimit){
        curNode->debugStateOut();
        cout << "Num of pairs: " << curNode->getHeuristicRBFS() << '\n';
        if(curNode->isSolved()){
            return curNode->getState();
        }
        if(curNode->getChildrenNodes().empty()){
            curNode->generateChildrenNodes();
            for(auto node : curNode->getChildrenNodes()){
                node->heuristicCalc();
            }
        }
        auto tempChildren = curNode->getChildrenNodes();
        vector<pair<short, short>> solution;
        while (true){
            sort(tempChildren.begin(), tempChildren.end(), [](solutionNode* &a, solutionNode* &b){
                return a->getHeuristicRBFS() < b->getHeuristicRBFS();
            });
            solutionNode *bestNode = tempChildren[0];
            auto alternativeLimit = tempChildren[1]->getHeuristicRBFS();
            if(bestNode->getHeuristicRBFS() > fLimit){
                curNode->setHeuristicRBFS(bestNode->getHeuristicRBFS());
                //TODO: Delete subtree
                vector<pair<short, short>> noSolution;
                return noSolution;
            }
            solution = recursiveRBFS(bestNode, min(fLimit, alternativeLimit));
            if(!solution.empty()){
                return solution;
            }
        }
    }



public:
    explicit solutionTree(solutionNode *rootNode);

    vector<pair<short, short>> findSolutionIDS();

    vector<pair<short, short>> findSolutionRBFS() {
        if(rootNode->isSolved()){
            return rootNode->getState();
        }
        if(rootNode->getChildrenNodes().empty()){
            rootNode->generateChildrenNodes();
            for(auto node : rootNode->getChildrenNodes()){
                node->heuristicCalc();
            }
        }
        auto tempChildren = rootNode->getChildrenNodes();
        vector<pair<short, short>> solution;
        while (true){
            sort(tempChildren.begin(), tempChildren.end(), [](solutionNode* &a, solutionNode* &b){
                return a->getHeuristicRBFS() < b->getHeuristicRBFS();
            });
            solutionNode *bestNode = tempChildren[0];
            auto alternativeLimit = tempChildren[1]->getHeuristicRBFS();
            solution = recursiveRBFS(bestNode, alternativeLimit);
            if(!solution.empty()){
                return solution;
            }
        }
    }
};
