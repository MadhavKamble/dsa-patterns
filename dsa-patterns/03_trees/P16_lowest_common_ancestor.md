# Pattern 16: Lowest Common Ancestor (LCA)

## Category
Trees

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 235. Lowest Common Ancestor of a Binary Search Tree | Medium | https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/ |
| 2 | 236. Lowest Common Ancestor of a Binary Tree | Medium | https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/ |

---

## 1. First-Timer Explanation

### What is this pattern?
The Lowest Common Ancestor (LCA) of two nodes p and q in a binary tree is the deepest node that has both p and q as descendants (a node is a descendant of itself).

**For general binary tree (LC 236):**
- DFS postorder: if current node is p or q, return it
- If left returns non-null AND right returns non-null → current node is LCA
- Otherwise return whichever non-null result exists (it means both p and q are in that subtree)

**For BST (LC 235):**
- Use the BST property: if both p and q are less than root → LCA is in left subtree; if both greater → right subtree; else root is the LCA

### Visual Walkthrough
```
Binary Tree LCA:
       3
      / \
     5   1
    / \ / \
   6  2 0  8
     / \
    7   4

LCA(5, 4):
  At 3: search both sides
    At 5: this IS p → return 5 immediately
    At 1: neither p nor q found in this subtree → return null
  Left returned 5, Right returned null → LCA = 5

LCA(5, 1):
  At 3: search both sides
    Left subtree contains 5 → returns 5
    Right subtree contains 1 → returns 1
  Both sides returned non-null → LCA = 3 (current node)
```

### When TO use this pattern
- Find the deepest common ancestor of two nodes
- Any problem requiring "first common node on both paths"

### When NOT to use this pattern
- Need LCA of multiple nodes → extend the algorithm
- Tree has parent pointers → simpler approach (walk both nodes to root, find intersection)

### Common Beginner Mistakes
- **Base case order**: check `if node == p || node == q` BEFORE recursing in general tree
- **BST LCA**: compare values to decide direction — left if both < root, right if both > root
- **Node is ancestor of the other**: the returned non-null from the deeper side IS the LCA (p can be ancestor of q)

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "lowest common ancestor", "deepest shared ancestor", "meet point" |
| Core Idea | Postorder: return p/q when found; LCA is where both subtrees return non-null |
| Trigger Keywords | "LCA", "common ancestor", "deepest node that is ancestor of both" |
| Avoid When | Multiple LCAs needed (find all pairs — different problem) |
| Time Complexity | O(n) general; O(h) for BST |
| Space Complexity | O(h) |

**Gotchas:**
- For BST: you NEVER need to check both subtrees — always go one direction
- General tree: return p/q immediately when encountered (even if q might be in the subtree below p — that's fine: p IS the LCA in that case)
- Both non-null from left and right → THIS node is the LCA (not either child)

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"lowest common ancestor"` → direct pattern match
- `"deepest node that is ancestor of both"` → same
- `"BST"` + ancestor → use BST property for O(h) solution
- `"paths from root to both nodes intersect at"` → LCA

---

## 4. C++ Template

```cpp
/*
 * Pattern: Lowest Common Ancestor
 * Use when: find LCA of two nodes in binary tree
 * Time: O(n) general, O(h) BST | Space: O(h)
 */

struct TreeNode { int val; TreeNode *left, *right; };

// GENERAL BINARY TREE
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;       // base: null → not found
    if (root == p || root == q) return root;  // found one of the targets

    TreeNode* left  = lowestCommonAncestor(root->left,  p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root;  // both found in different subtrees → LCA
    return left ? left : right;      // return whichever found something
}

// BST (use BST property to avoid searching both sides)
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val)
            root = root->left;   // both smaller: go left
        else if (p->val > root->val && q->val > root->val)
            root = root->right;  // both larger: go right
        else
            return root;  // split point: current node is LCA
    }
    return nullptr;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For LCA on a general tree: I use postorder DFS. If the current node is p or q, return it. After recursing both subtrees: if both return non-null, this node is the LCA. If only one returns non-null, propagate that upward — it means both nodes are in that one subtree.
For BST: I use the BST property. If both p and q are smaller, go left. If both larger, go right. Otherwise, current is the split point = LCA."

### Interview Flow Checklist
- [ ] Confirm if it's a BST (O(h) solution) or general tree (O(n))
- [ ] Handle null base case
- [ ] Return p/q when found
- [ ] Check: both subtrees returned non-null → LCA
- [ ] Return non-null result otherwise

---

## 6. Problems

---

### Problem 1: 236. Lowest Common Ancestor of a Binary Tree
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/
**Optimal C++ Solution:**
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    auto left  = lowestCommonAncestor(root->left,  p, q);
    auto right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}
```
**Edge Cases:** [ ] p is ancestor of q, [ ] p == q, [ ] Deep tree

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 235. Lowest Common Ancestor of a Binary Search Tree
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
**Optimal C++ Solution:**
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val)
            root = root->left;
        else if (p->val > root->val && q->val > root->val)
            root = root->right;
        else return root;  // split point
    }
    return nullptr;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find the LCA of three nodes in a binary tree.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Extend LCA to multiple targets
**Reason:** Same DFS approach but return node if it's any of the three targets. Count non-null returns from children — if 2 sides returned non-null (or this node is one of them), this is the LCA. Or: LCA(p, LCA(q, r)).
</details>

---

**Drill 2:**
> Given parent pointers, find LCA using pointer manipulation.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Two Pointer on paths (like linked list intersection)
**Reason:** Walk both nodes to root, collecting paths. Find first common node. Or use the intersection trick: walk both pointers up; when one reaches root, restart at the other's start; they meet at LCA.
</details>

---

**Drill 3:**
> Given a tree and many (p, q) pairs, answer LCA queries efficiently.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Offline LCA (Tarjan's algorithm) or Binary Lifting
**Reason:** Binary lifting: precompute 2^k ancestors for each node in O(n log n). Answer each query in O(log n). Tarjan's: O(n + q) using DSU. Both beyond basic interview scope.
</details>

---

**Drill 4:**
> Find the distance between two nodes in a binary tree.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** LCA + depth calculation
**Reason:** distance(p, q) = depth(p) + depth(q) - 2 * depth(LCA(p, q)). Find LCA first, then compute depths from root.
</details>

---

**Drill 5:**
> In a BST, find the node that is closest in value to the average of p and q.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BST binary search (not LCA directly)
**Reason:** Compute target = (p.val + q.val) / 2. BST search for closest value to target by tracking minimum absolute difference while descending.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| General tree LCA | O(n) | O(h) | Postorder DFS |
| BST LCA | O(h) | O(1) iterative | Use BST property |
| With parent pointers | O(h) | O(h) path set | Path intersection |
| Multiple nodes LCA | O(n) | O(h) | Extend to count matches |

---

## 9. Common Follow-up Questions

1. What if the tree has parent pointers? (Simpler: walk both paths to root, find first common node using a hash set)
2. Can LCA be done iteratively? (Yes for BST — naturally iterative. For general tree — harder, need to track parent stack)
3. What if p or q might not be in the tree? (Modify: only set LCA when BOTH have been confirmed found)
4. LCA in a DAG? (More complex — use DFS with reachability; no single traversal trick)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| BST Property | BST LCA avoids O(n) scan | 235. BST LCA |
| Postorder DFS | General tree LCA | 236. Binary Tree LCA |
| Graph BFS | Distance between nodes | 863. Nodes Distance K |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
