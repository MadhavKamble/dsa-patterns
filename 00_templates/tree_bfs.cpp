/*
 * ============================================================
 * TEMPLATE: Tree BFS (Level Order Traversal)
 * ============================================================
 * Use when: process tree level by level, find shortest path
 *           from root, level-based properties
 * Time: O(n) | Space: O(w) — w = max width of tree
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
// CLASSIC LEVEL ORDER TRAVERSAL
// ─────────────────────────────────────────────────────────────

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);  // start BFS from root

    while (!q.empty()) {
        int levelSize = q.size();  // CRITICAL: snapshot size before processing
                                   // ensures we only process current level's nodes
        vector<int> level;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();

            level.push_back(node->val);  // process this node

            // enqueue children for next level
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT: RIGHT SIDE VIEW
// ─────────────────────────────────────────────────────────────
// Only keep the LAST node at each level (rightmost visible)

vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();

            // only save the LAST node of each level
            if (i == levelSize - 1) result.push_back(node->val);

            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT: ZIGZAG LEVEL ORDER
// ─────────────────────────────────────────────────────────────
// Alternate direction each level

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;  // direction flag

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level(levelSize);  // pre-size for index assignment

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();

            // place in correct position based on direction
            int idx = leftToRight ? i : (levelSize - 1 - i);
            level[idx] = node->val;

            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
        leftToRight = !leftToRight;  // flip direction for next level
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT: MAXIMUM VALUE PER LEVEL
// ─────────────────────────────────────────────────────────────

vector<int> largestValues(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        int levelMax = INT_MIN;

        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            levelMax = max(levelMax, node->val);  // track max in level

            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(levelMax);
    }
    return result;
}

/*
 * ─────────────────────────────────────────────────────────────
 * UNIVERSAL BFS SKELETON
 * ─────────────────────────────────────────────────────────────
 *
 *  queue<TreeNode*> q;
 *  q.push(root);
 *
 *  while (!q.empty()) {
 *      int levelSize = q.size();   // ← ALWAYS snapshot this first
 *
 *      for (int i = 0; i < levelSize; i++) {
 *          auto node = q.front(); q.pop();
 *          // process node
 *          if (node->left)  q.push(node->left);
 *          if (node->right) q.push(node->right);
 *      }
 *      // post-level processing here
 *  }
 *
 * ─────────────────────────────────────────────────────────────
 * KEY INSIGHT
 * ─────────────────────────────────────────────────────────────
 *  The `int levelSize = q.size()` snapshot is what separates
 *  levels. Without it, you'd process all nodes as one flat list.
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Not snapshotting q.size() → processes across level boundaries
 *  2. Null check: always check root != null before pushing to queue
 *  3. Pushing null children to queue causes null pointer dereference
 */
