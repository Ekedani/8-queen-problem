#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

class solutionNode {
private:
    vector<pair<short, short>> state;
    int depth;
    int heuristicRBFS;
    solutionNode *parentNode;
    vector<solutionNode *> childrenNodes;

public:
    void setHeuristicRBFS(int heuristicRbfs);

    int getHeuristicRBFS() const;

    explicit solutionNode(vector<pair<short, short>> &startState);

    solutionNode(solutionNode &parentNode);

    void generateChildrenNodes();

    int heuristicCalc();

    bool isSolved();

    [[nodiscard]] int getDepth() const;

    [[nodiscard]] solutionNode *getParentNode() const;

    [[nodiscard]] vector<pair<short, short>> getState() const;

    [[nodiscard]] vector<solutionNode *> getChildrenNodes() const;

    void clearChildrenVector();;
};

class solutionTree {
private:
    solutionNode *rootNode;

    void deleteSubTree(solutionNode *curNode);

    //Methods for IDS
    vector<pair<short, short>> findSolutionDLS(int depthLimit);

    vector<pair<short, short>> recursiveDLS(int depthLimit, solutionNode *curNode);

    //Method for RBFS
    vector<pair<short, short>> recursiveRBFS(solutionNode *curNode, int fLimit);


public:
    explicit solutionTree(solutionNode *rootNode);

    vector<pair<short, short>> findSolutionIDS();

    vector<pair<short, short>> findSolutionRBFS();
};
