#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class TreeNode {
public:
    vector<TreeNode*> children;  // Children nodes
    int value;                    // Value of the node (for leaf nodes)
    bool isLeaf;                  // Whether it's a leaf node or not

    // Constructor for non-leaf nodes
    TreeNode(bool isLeaf = false, int value = 0) : isLeaf(isLeaf), value(value) {}

    // Add a child node
    void addChild(TreeNode* child) {
        children.push_back(child);
    }
};

class GameTree {
private:
    static int globalAlphaBetaCount;  // Counts the number of nodes evaluated
    TreeNode* root;                  // Root of the tree

public:
    GameTree() {
        // Create the tree structure (Depth 3 example)
        root = new TreeNode();  // Root node (non-leaf)

        // Level 1 (internal nodes)
        TreeNode* n1 = new TreeNode(false);  // Internal node
        TreeNode* n2 = new TreeNode(false);  // Internal node
        root->addChild(n1);
        root->addChild(n2);

        // Level 2 (children of n1)
        n1->addChild(new TreeNode(true, 7));  // Leaf node with value 7
        n1->addChild(new TreeNode(true, 5));  // Leaf node with value 5

        // Level 2 (children of n2)
        n2->addChild(new TreeNode(true, 6));  // Leaf node with value 6
        n2->addChild(new TreeNode(true, 9));  // Leaf node with value 9
    }

    // Getter for root node
    TreeNode* getRoot() const {
        return root;
    }

    static void setGlobalAlphaBetaCount(int value) {
        globalAlphaBetaCount = value;
    }

    static int getGlobalAlphaBetaCount() {
        return globalAlphaBetaCount;
    }

    // Alpha-Beta pruning algorithm
    int alphaBeta(TreeNode* node, int alpha, int beta, bool maximizingPlayer) {
        globalAlphaBetaCount++;  // Increment count for each node visited

        // If the node is a leaf, return its value
        if (node->isLeaf) {
            return node->value;
        }

        if (maximizingPlayer) {
            int maxEval = std::numeric_limits<int>::min();
            for (TreeNode* child : node->children) {
                int eval = alphaBeta(child, alpha, beta, false);  // Recurse to the minimizer
                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha) {
                    break; // Beta cutoff
                }
            }
            return maxEval;
        } else {
            int minEval = std::numeric_limits<int>::max();
            for (TreeNode* child : node->children) {
                int eval = alphaBeta(child, alpha, beta, true);  // Recurse to the maximizer
                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha) {
                    break; // Alpha cutoff
                }
            }
            return minEval;
        }
    }
};

// Define the static member variable
int GameTree::globalAlphaBetaCount = 0;

int main() {
    GameTree tree;
    GameTree::setGlobalAlphaBetaCount(0); // Reset the count

    // Execute the Alpha-Beta pruning algorithm on the root node with depth 3
    int score = tree.alphaBeta(tree.getRoot(), std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true);
    
    // Output the results
    cout << "Best score from Alpha-Beta pruning: " << score << endl;
    cout << "Total nodes evaluated (Global AlphaBeta Count): " << GameTree::getGlobalAlphaBetaCount() << endl;
    
    return 0;
}

