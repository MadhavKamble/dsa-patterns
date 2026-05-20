# Pattern 13: Recursive Preorder Traversal

## Category
Trees

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 100. Same Tree | Easy | https://leetcode.com/problems/same-tree/ |
| 2 | 101. Symmetric Tree | Easy | https://leetcode.com/problems/symmetric-tree/ |
| 3 | 105. Construct Binary Tree from Preorder and Inorder Traversal | Medium | https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/ |
| 4 | 114. Flatten Binary Tree to Linked List | Medium | https://leetcode.com/problems/flatten-binary-tree-to-linked-list/ |
| 5 | 226. Invert Binary Tree | Easy | https://leetcode.com/problems/invert-binary-tree/ |
| 6 | 257. Binary Tree Paths | Easy | https://leetcode.com/problems/binary-tree-paths/ |
| 7 | 988. Smallest String Starting From Leaf | Medium | https://leetcode.com/problems/smallest-string-starting-from-leaf/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Preorder = **Root → Left → Right**. Process the current node FIRST, then recurse into children. This is naturally top-down: you make decisions at each node before knowing what's in its subtrees.

Key uses:
- **Structural checks**: compare two trees (Same Tree, Symmetric)
- **Path tracking**: accumulate path from root to current node (Binary Tree Paths)
- **Reconstruction**: given preorder + inorder, rebuild the tree
- **Transformation**: invert tree (swap children), flatten to linked list

### Visual Walkthrough
```
Preorder of tree:
       1
      / \
     2   3

Visit 1 (root first)
  Visit 2 (left subtree)
    Visit null (left of 2) → return
    Visit null (right of 2) → return
  Visit 3 (right subtree)
    Visit null (left of 3) → return
    Visit null (right of 3) → return

Sequence: 1, 2, 3
```

### When TO use this pattern
- Decision/comparison needs root value before going into subtrees
- Building paths from root to leaves
- Cloning or modifying tree structure top-down
- Reconstructing tree from traversal arrays

### When NOT to use this pattern
- Need subtree information to process current node → use postorder
- Need sorted BST output → use inorder

### Common Beginner Mistakes
- **Base case**: always handle null node first
- **Symmetric Tree**: compare mirrored positions, not same positions
- **Binary Tree Paths**: pass current path by value (or restore by backtracking)
- **Invert**: swap children BEFORE or AFTER recursing — both work, but before is preorder style

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "same tree", "symmetric", "paths from root", "invert", "construct from preorder" |
| Core Idea | Process root before children; top-down decision making |
| Trigger Keywords | "construct", "path", "root to leaf", "same structure", "clone" |
| Avoid When | Need subtree aggregation (use postorder) |
| Time Complexity | O(n) |
| Space Complexity | O(h) — h = height |

**Gotchas:**
- Symmetric: compare root->left's left with root->right's right (mirror, not same side)
- Construct from pre+inorder: preorder[0] is root; find it in inorder to split left/right
- Binary Tree Paths: use string concatenation or backtracking — pass reference and restore

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"same tree"`, `"structurally identical"` → preorder comparison
- `"invert binary tree"`, `"mirror"` → preorder swap
- `"path from root to leaf"` → preorder DFS with path accumulation
- `"construct from preorder and inorder"` → classic divide-and-conquer

---

## 4. C++ Template

```cpp
/*
 * Pattern: Recursive Preorder
 * Use when: process root before children, top-down decisions
 * Time: O(n) | Space: O(h)
 */

struct TreeNode { int val; TreeNode *left, *right; };

// SAME TREE
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;   // both null: same
    if (!p || !q) return false;  // one null: different
    return p->val == q->val &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}

// INVERT TREE (preorder: swap, then recurse)
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);  // process root first
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

// BINARY TREE PATHS
void dfs(TreeNode* node, string path, vector<string>& result) {
    if (!node) return;
    path += to_string(node->val);
    if (!node->left && !node->right) {  // leaf
        result.push_back(path);
        return;
    }
    path += "->";
    dfs(node->left, path, result);
    dfs(node->right, path, result);
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This problem involves processing each node before its children — that's preorder DFS. The base case is null: return a sentinel value or false/true as appropriate. Then process the root, and recurse into left and right subtrees."

### Interview Flow Checklist
- [ ] Handle null base case
- [ ] Process current node first (preorder)
- [ ] Recurse left, then right
- [ ] Collect/return values from recursion

---

## 6. Problems

---

### Problem 1: 226. Invert Binary Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/invert-binary-tree/
**Optimal C++ Solution:**
```cpp
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}
```
**Edge Cases:** [ ] Null tree, [ ] Single node, [ ] Only one side

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 100. Same Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/same-tree/
**Optimal C++ Solution:**
```cpp
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    return p->val == q->val &&
           isSameTree(p->left, q->left) &&
           isSameTree(p->right, q->right);
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 101. Symmetric Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/symmetric-tree/
**Why this pattern fits:** Preorder comparison of mirrored positions

**Optimal C++ Solution:**
```cpp
bool isMirror(TreeNode* left, TreeNode* right) {
    if (!left && !right) return true;
    if (!left || !right) return false;
    return left->val == right->val &&
           isMirror(left->left, right->right) &&   // outer pair
           isMirror(left->right, right->left);      // inner pair
}

bool isSymmetric(TreeNode* root) {
    return isMirror(root->left, root->right);
}
```
**Edge Cases:** [ ] Null root (symmetric), [ ] One child only

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 105. Construct Binary Tree from Preorder and Inorder
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
**Approach:**
1. preorder[0] = root
2. Find root in inorder → splits left and right subtrees
3. Recursively build left and right

**Optimal C++ Solution:**
```cpp
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> inPos;
    for (int i = 0; i < (int)inorder.size(); i++) inPos[inorder[i]] = i;

    function<TreeNode*(int,int,int)> build = [&](int preStart, int inStart, int inEnd) -> TreeNode* {
        if (preStart >= (int)preorder.size() || inStart > inEnd) return nullptr;

        int rootVal = preorder[preStart];
        TreeNode* root = new TreeNode(rootVal);
        int inMid = inPos[rootVal];
        int leftSize = inMid - inStart;

        root->left  = build(preStart + 1, inStart, inMid - 1);
        root->right = build(preStart + 1 + leftSize, inMid + 1, inEnd);
        return root;
    };

    return build(0, 0, inorder.size() - 1);
}
```
**Edge Cases:** [ ] Single element, [ ] Left-skewed, [ ] Right-skewed

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 257. Binary Tree Paths
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/binary-tree-paths/
**Optimal C++ Solution:**
```cpp
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> result;
    function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path) {
        if (!node) return;
        path += to_string(node->val);
        if (!node->left && !node->right) { result.push_back(path); return; }
        path += "->";
        dfs(node->left, path);
        dfs(node->right, path);
    };
    dfs(root, "");
    return result;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Count all root-to-leaf paths where the sum of node values equals a target.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Preorder DFS with running sum
**Reason:** Subtract node value from target as you go down. At leaf, check if remaining sum == 0. LC 112/113.
</details>

---

**Drill 2:**
> Clone a binary tree (create a deep copy).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Preorder DFS
**Reason:** Create new node with same value, then recursively clone left and right. Return new root. O(n) time.
</details>

---

**Drill 3:**
> Given a binary tree and a target node, find all paths from any node to any node that sum to target.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Preorder DFS + prefix sum
**Reason:** LC 437 (Path Sum III). Use DFS with a running prefix sum map. At each node, check how many previous prefix sums satisfy (current - target) in the map.
</details>

---

**Drill 4:**
> Given a binary tree, check if it is a complete binary tree (all levels full except possibly last, last level left-filled).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS Level Order
**Reason:** BFS — once you see a null node, all subsequent nodes in queue must also be null. If a non-null appears after null, not complete.
</details>

---

**Drill 5:**
> Given two binary trees, merge them by summing overlapping nodes (where they overlap, sum; where one is null, keep the other).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Preorder DFS on both trees simultaneously
**Reason:** Recurse both trees in parallel. If one is null, return the other. If both exist, sum values, recurse left and right. LC 617.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| Same Tree / Invert | O(n) | O(h) | h = height |
| Symmetric | O(n) | O(h) | Compare mirrored pairs |
| Construct from pre+in | O(n) | O(n) | Hash map for inorder lookup |
| Binary Tree Paths | O(n²) | O(n) | String copy per path = O(n) |

---

## 9. Common Follow-up Questions

1. Can you invert iteratively? (Yes — use a queue/stack, swap children at each dequeued node)
2. Construct from postorder + inorder? (Similar: postorder's last element is root)
3. Can you get unique paths without duplicate code? (Yes — pass path as reference, restore on return — backtracking style)
4. Is Symmetric check iterative possible? (Yes — use a queue with pairs of nodes to compare)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Postorder | When need subtree info (height, sum) at each node | 105: Construction needs left subtree size |
| Backtracking | Path tracking with restoration | 257 variant with restore |
| BFS | Symmetric can be solved with BFS | 101 iterative |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
