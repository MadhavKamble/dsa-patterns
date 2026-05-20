/*
 * ============================================================
 * TEMPLATE: Tree DFS (Preorder / Inorder / Postorder)
 * ============================================================
 * Use when: need to process tree nodes in a specific order,
 *           compute subtree properties, build/validate trees
 * Time: O(n) | Space: O(h) — h = tree height (O(log n) balanced,
 *                                              O(n) skewed)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ─────────────────────────────────────────────────────────────
// PREORDER DFS: Root → Left → Right
// ─────────────────────────────────────────────────────────────
// Use when: process/print nodes top-down, serialize tree,
//           check structural equality, copy tree

void preorder(TreeNode* root, vector<int>& result) {
    if (!root) return;          // BASE CASE: null node → do nothing

    result.push_back(root->val);  // PROCESS root FIRST
    preorder(root->left, result); // then left subtree
    preorder(root->right, result);// then right subtree
}

// Check if two trees are the same (preorder comparison)
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;   // both null → equal
    if (!p || !q) return false;  // one null, one not → not equal
    if (p->val != q->val) return false;  // values differ

    // recursively check both subtrees
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// ─────────────────────────────────────────────────────────────
// INORDER DFS: Left → Root → Right
// ─────────────────────────────────────────────────────────────
// Use when: BST operations (gives sorted order),
//           validate BST, find kth smallest in BST

void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;

    inorder(root->left, result);  // process left FIRST
    result.push_back(root->val);  // then ROOT
    inorder(root->right, result); // then right
}

// Validate BST using inorder with min/max bounds (better than sorted check)
bool isValidBST(TreeNode* root, long lo = LLONG_MIN, long hi = LLONG_MAX) {
    if (!root) return true;  // empty tree is valid BST

    // each node must be strictly within (lo, hi) bounds
    if (root->val <= lo || root->val >= hi) return false;

    // left subtree: all values must be < root->val (hi becomes root->val)
    // right subtree: all values must be > root->val (lo becomes root->val)
    return isValidBST(root->left, lo, root->val) &&
           isValidBST(root->right, root->val, hi);
}

// ─────────────────────────────────────────────────────────────
// POSTORDER DFS: Left → Right → Root
// ─────────────────────────────────────────────────────────────
// Use when: compute subtree properties (height, diameter, sum),
//           delete nodes, evaluate expressions bottom-up
// KEY PATTERN: return information from children to parent

int maxDepth(TreeNode* root) {
    if (!root) return 0;  // base case: null has depth 0

    int leftDepth  = maxDepth(root->left);   // get left subtree height
    int rightDepth = maxDepth(root->right);  // get right subtree height

    // process at root: max of both + 1 for current node
    return 1 + max(leftDepth, rightDepth);
}

// Check if tree is height-balanced
bool isBalanced(TreeNode* root) {
    // returns -1 if unbalanced, else returns height
    function<int(TreeNode*)> check = [&](TreeNode* node) -> int {
        if (!node) return 0;

        int left  = check(node->left);
        int right = check(node->right);

        // propagate failure upward
        if (left == -1 || right == -1) return -1;

        // unbalanced if height difference > 1
        if (abs(left - right) > 1) return -1;

        return 1 + max(left, right);  // return height to parent
    };
    return check(root) != -1;
}

// Diameter of binary tree (longest path between any two nodes)
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;

    function<int(TreeNode*)> depth = [&](TreeNode* node) -> int {
        if (!node) return 0;

        int left  = depth(node->left);
        int right = depth(node->right);

        // path through this node = left depth + right depth
        diameter = max(diameter, left + right);

        return 1 + max(left, right);  // return depth upward
    };

    depth(root);
    return diameter;
}

// Binary Tree Maximum Path Sum
int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;

    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
        if (!node) return 0;

        // if a subtree contributes negative, ignore it (take 0 instead)
        int left  = max(0, dfs(node->left));
        int right = max(0, dfs(node->right));

        // path through this node = left arm + root + right arm
        maxSum = max(maxSum, left + node->val + right);

        // return only ONE arm to parent (can't split a path upward)
        return node->val + max(left, right);
    };

    dfs(root);
    return maxSum;
}

// ─────────────────────────────────────────────────────────────
// ITERATIVE DFS (stack-based) — avoid recursion stack overflow
// ─────────────────────────────────────────────────────────────

vector<int> iterativePreorder(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    stack<TreeNode*> stk;
    stk.push(root);

    while (!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();
        result.push_back(node->val);  // process current

        // push RIGHT first so LEFT is processed first (LIFO)
        if (node->right) stk.push(node->right);
        if (node->left)  stk.push(node->left);
    }
    return result;
}

vector<int> iterativeInorder(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> stk;
    TreeNode* curr = root;

    while (curr || !stk.empty()) {
        // go as far left as possible
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        // process node
        curr = stk.top();
        stk.pop();
        result.push_back(curr->val);
        // move to right subtree
        curr = curr->right;
    }
    return result;
}

/*
 * ─────────────────────────────────────────────────────────────
 * DECISION GUIDE
 * ─────────────────────────────────────────────────────────────
 *
 *  PREORDER  (root first)  → serialize, clone, structural check
 *  INORDER   (root middle) → BST sorted order, kth element
 *  POSTORDER (root last)   → subtree properties, delete, evaluate
 *
 *  "from top down" → preorder
 *  "from bottom up", "return value from children to parent" → postorder
 *  "BST", "sorted output" → inorder
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Returning wrong value in postorder (e.g., int when -1 means invalid)
 *  2. Forgetting to handle null nodes early in recursion
 *  3. Not using LLONG_MIN/MAX for BST validation (int overflow)
 *  4. Diameter: updating global max but returning only single-arm depth
 *  5. Iterative inorder: pushing to stack going LEFT, process when popping
 */
