# Pattern 15: Recursive Postorder Traversal

## Category
Trees

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 104. Maximum Depth of Binary Tree | Easy | https://leetcode.com/problems/maximum-depth-of-binary-tree/ |
| 2 | 110. Balanced Binary Tree | Easy | https://leetcode.com/problems/balanced-binary-tree/ |
| 3 | 124. Binary Tree Maximum Path Sum | Hard | https://leetcode.com/problems/binary-tree-maximum-path-sum/ |
| 4 | 145. Binary Tree Postorder Traversal | Easy | https://leetcode.com/problems/binary-tree-postorder-traversal/ |
| 5 | 337. House Robber III | Medium | https://leetcode.com/problems/house-robber-iii/ |
| 6 | 366. Find Leaves of Binary Tree | Medium | https://leetcode.com/problems/find-leaves-of-binary-tree/ |
| 7 | 543. Diameter of Binary Tree | Easy | https://leetcode.com/problems/diameter-of-binary-tree/ |
| 8 | 863. All Nodes Distance K in Binary Tree | Medium | https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/ |
| 9 | 1110. Delete Nodes And Return Forest | Medium | https://leetcode.com/problems/delete-nodes-and-return-forest/ |
| 10 | 2458. Height of Binary Tree After Subtree Removal Queries | Hard | https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Postorder = **Left → Right → Root**. Process children FIRST, then the current node. This is bottom-up: you collect information from subtrees before making decisions at the parent.

This is the **most powerful tree DFS pattern** — it's used whenever the current node's answer depends on subtree values (height, diameter, max path sum, subtree size, etc.).

The signature: the recursive function **returns a value** that represents "useful information for my parent."

### Real-World Analogy
Calculating a company's total revenue: each employee (leaf) reports their sales first. Each manager waits for all their team's reports, sums them up, and passes the total upward. The CEO (root) gets the final company total. Bottom-up information flow.

### Visual Walkthrough
```
Postorder of tree:
       1
      / \
     2   3

Process 2 (left leaf first) → returns
Process 3 (right leaf) → returns
Process 1 (root last)

Max Depth example:
  maxDepth(1):
    left  = maxDepth(2) = 1
    right = maxDepth(3) = 1
    return 1 + max(1,1) = 2

Diameter example:
  For each node: left_depth + right_depth = diameter through this node
  Track global maximum across all nodes
```

### When TO use this pattern
- Computing subtree properties: height, size, sum
- Path through nodes (max path sum, diameter)
- Checking subtree properties (balanced, valid)
- Delete/prune nodes based on subtree content
- House robber on tree (include/exclude decisions based on subtree values)

### When NOT to use this pattern
- Decisions depend only on ancestors → use preorder
- Level-based operations → use BFS

### Common Beginner Mistakes
- **Global variable for cross-root paths**: diameter and max path sum update a global; function returns only the "arm" extending upward
- **Return -1 for unbalanced**: in `isBalanced`, use -1 as sentinel to propagate failure upward efficiently
- **House Robber III**: return a pair (rob_root, skip_root) — not just one value
- **Delete nodes**: postorder ensures children are processed before parent → parent can check if child should be detached

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "height", "diameter", "max path", "subtree size", "rob tree", "delete nodes" |
| Core Idea | Recurse into children first; return aggregated subtree info to parent |
| Trigger Keywords | "depth", "balanced", "diameter", "path sum", "subtree" |
| Avoid When | Need top-down information flow |
| Time Complexity | O(n) |
| Space Complexity | O(h) |

**Gotchas:**
- Max Path Sum: return `node->val + max(0, left) + max(0, right)` for the path through root; but return only ONE arm to parent
- Diameter: left_depth + right_depth at each node; function returns max(left, right) + 1
- House Robber: return PAIR (with_root, without_root); parent uses both values
- Balanced: use -1 as invalid height sentinel; propagate upward to avoid re-traversal

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"maximum depth"`, `"height of tree"` → postorder returns depth
- `"diameter"` → max left_depth + right_depth across all nodes
- `"binary tree maximum path sum"` → update global with left+val+right; return val + max(left,right) arm
- `"balanced"` → postorder returns height or -1
- `"house robber"` + tree → return (rob, skip) pair

---

## 4. C++ Template

```cpp
/*
 * Pattern: Recursive Postorder
 * Use when: subtree aggregation, bottom-up computation
 * Time: O(n) | Space: O(h)
 */

struct TreeNode { int val; TreeNode *left, *right; };

// MAX DEPTH
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    int left  = maxDepth(root->left);
    int right = maxDepth(root->right);
    return 1 + max(left, right);  // process after children
}

// DIAMETER (global variable for cross-root paths)
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    function<int(TreeNode*)> depth = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int l = depth(node->left), r = depth(node->right);
        diameter = max(diameter, l + r);  // update global
        return 1 + max(l, r);             // return single arm to parent
    };
    depth(root);
    return diameter;
}

// MAX PATH SUM
int maxPathSum(TreeNode* root) {
    int best = INT_MIN;
    function<int(TreeNode*)> gain = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int l = max(0, gain(node->left));   // ignore negative branches
        int r = max(0, gain(node->right));
        best = max(best, l + node->val + r);  // path through this node
        return node->val + max(l, r);          // single arm upward
    };
    gain(root);
    return best;
}

// HOUSE ROBBER III (return pair)
pair<int,int> rob(TreeNode* node) {
    if (!node) return {0, 0};
    auto [lr, ls] = rob(node->left);   // (rob_left, skip_left)
    auto [rr, rs] = rob(node->right);
    int robRoot  = node->val + ls + rs;      // rob root: skip both children
    int skipRoot = max(lr, ls) + max(rr, rs); // skip root: optimal for each child
    return {robRoot, skipRoot};
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This problem requires computing something about each subtree before processing the node. That's postorder traversal — recurse into both children first, get their results, then combine at the current node.
For diameter/max path: I update a global maximum at each node (left_depth + right_depth), but I only return a single arm to the parent because a path can't go both ways when continuing upward."

### Interview Flow Checklist
- [ ] Identify: what does each recursive call return?
- [ ] Handle null base case
- [ ] Get left and right subtree results
- [ ] Combine at current node
- [ ] Update global answer if needed (for cross-root paths)
- [ ] Return the right value to parent (often different from what updates global)

---

## 6. Problems

---

### Problem 1: 104. Maximum Depth of Binary Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/maximum-depth-of-binary-tree/
**Optimal C++ Solution:**
```cpp
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 110. Balanced Binary Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/balanced-binary-tree/
**Optimal C++ Solution:**
```cpp
// returns height, or -1 if unbalanced
int checkHeight(TreeNode* node) {
    if (!node) return 0;
    int left  = checkHeight(node->left);
    int right = checkHeight(node->right);
    if (left == -1 || right == -1) return -1;  // propagate failure
    if (abs(left - right) > 1) return -1;      // unbalanced here
    return 1 + max(left, right);
}

bool isBalanced(TreeNode* root) { return checkHeight(root) != -1; }
```
**Edge Cases:** [ ] Single node, [ ] Left-skewed tree (unbalanced)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 543. Diameter of Binary Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/diameter-of-binary-tree/
**Optimal C++ Solution:**
```cpp
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    function<int(TreeNode*)> depth = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int l = depth(node->left), r = depth(node->right);
        diameter = max(diameter, l + r);
        return 1 + max(l, r);
    };
    depth(root);
    return diameter;
}
```
**Edge Cases:** [ ] Single node (diameter = 0), [ ] Path through root vs not

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 124. Binary Tree Maximum Path Sum
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/binary-tree-maximum-path-sum/
**Optimal C++ Solution:**
```cpp
int maxPathSum(TreeNode* root) {
    int best = INT_MIN;
    function<int(TreeNode*)> gain = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int l = max(0, gain(node->left));   // ignore if negative
        int r = max(0, gain(node->right));
        best = max(best, l + node->val + r);  // path through this node
        return node->val + max(l, r);          // only ONE direction upward
    };
    gain(root);
    return best;
}
```
**Edge Cases:** [ ] All negative nodes, [ ] Single node

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 337. House Robber III
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/house-robber-iii/
**Optimal C++ Solution:**
```cpp
int rob(TreeNode* root) {
    function<pair<int,int>(TreeNode*)> dfs = [&](TreeNode* node) -> pair<int,int> {
        if (!node) return {0, 0};
        auto [lr, ls] = dfs(node->left);
        auto [rr, rs] = dfs(node->right);
        // rob root: skip both immediate children
        int robRoot  = node->val + ls + rs;
        // skip root: each child can be robbed or skipped optimally
        int skipRoot = max(lr, ls) + max(rr, rs);
        return {robRoot, skipRoot};
    };
    auto [r, s] = dfs(root);
    return max(r, s);
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find the sum of all node values in the subtree rooted at each node. Which is the heaviest subtree?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Postorder DFS
**Reason:** Subtree sum = left subtree sum + right subtree sum + root value. Track global max as we compute each node's subtree sum.
</details>

---

**Drill 2:**
> Delete all leaf nodes with value == target. Repeat until no such leaves exist.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Postorder DFS
**Reason:** Process children first. After recursing, check if current node became a leaf AND has target value. If so, return null (detach). This handles cascading deletions automatically. LC 1325.
</details>

---

**Drill 3:**
> Prune a binary tree to remove all subtrees containing no 1-value nodes.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Postorder DFS
**Reason:** After pruning children, if current node has value 0 AND both children are null → return null (prune this node). LC 814.
</details>

---

**Drill 4:**
> Find the number of nodes with more descendants than ancestors.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Postorder (descendants count) + Preorder (ancestor count)
**Reason:** First pass postorder: compute subtree size (descendants). Second pass preorder: compute depth (ancestors). Compare. Or combine in one DFS.
</details>

---

**Drill 5:**
> Given a binary tree, return the sum of all values of nodes that are "good" — the maximum value in the path from root to that node.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Preorder DFS with running max
**Reason:** Pass maxSoFar down the tree. At each node: if node->val >= maxSoFar → it's "good", add to sum. Update maxSoFar for children. LC 1448.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| Max Depth | O(n) | O(h) | — |
| Balanced | O(n) | O(h) | -1 sentinel avoids repeat traversal |
| Diameter | O(n) | O(h) | Global updated per node |
| Max Path Sum | O(n) | O(h) | Return arm, update global |
| House Robber III | O(n) | O(h) | Return pair |

---

## 9. Common Follow-up Questions

1. Can you find the diameter iteratively? (Yes — iterative postorder with explicit stack, track depth per node)
2. What if max path sum must go through the root? (Just compute left_gain + right_gain + root.val — no global needed)
3. Balanced check without O(n²)? (The -1 sentinel approach already avoids O(n²) — it's O(n))
4. House Robber on a general graph? (DP on graph — much harder, related to maximum independent set)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| DP (pair return) | Optimize decisions per subtree | 337. House Robber III |
| Global state | Cross-root paths | 124. Max Path Sum, 543. Diameter |
| BFS | When you need parent info at each node | 863. Nodes Distance K |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
