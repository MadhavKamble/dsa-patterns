# Pattern 14: Recursive Inorder Traversal

## Category
Trees

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 94. Binary Tree Inorder Traversal | Easy | https://leetcode.com/problems/binary-tree-inorder-traversal/ |
| 2 | 98. Validate Binary Search Tree | Medium | https://leetcode.com/problems/validate-binary-search-tree/ |
| 3 | 173. Binary Search Tree Iterator | Medium | https://leetcode.com/problems/binary-search-tree-iterator/ |
| 4 | 230. Kth Smallest Element in a BST | Medium | https://leetcode.com/problems/kth-smallest-element-in-a-bst/ |
| 5 | 501. Find Mode in Binary Search Tree | Easy | https://leetcode.com/problems/find-mode-in-binary-search-tree/ |
| 6 | 530. Minimum Absolute Difference in BST | Easy | https://leetcode.com/problems/minimum-absolute-difference-in-bst/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Inorder = **Left → Root → Right**. For a Binary Search Tree (BST), inorder traversal produces elements in **sorted (non-decreasing) order**. This is the key property that makes inorder essential for BST problems.

Think of a BST as a sorted array stored in a tree: inorder gives you that sorted array back.

### Visual Walkthrough
```
BST:
      4
     / \
    2   6
   / \ / \
  1  3 5  7

Inorder: 1, 2, 3, 4, 5, 6, 7  (sorted!)

Inorder traversal:
  go left until null: 1 (leaf)
  backtrack to 2: process 2
  go right of 2: 3 (leaf)
  backtrack to 4: process 4
  ... and so on
```

### When TO use this pattern
- BST operations: validate BST, find kth smallest, min difference between adjacent nodes
- Produce sorted output from a BST
- In-order iteration (BST Iterator design problem)

### When NOT to use this pattern
- Non-BST problems where sorted order isn't meaningful
- Need to process parent before children → use preorder

### Common Beginner Mistakes
- **BST validation**: don't just compare with parent — compare with bounds (lo, hi). A value could be wrong relative to a grandparent.
- **Kth smallest**: use a counter that decrements — stop when counter hits 0
- **BST Iterator**: use a stack to simulate inorder iteratively (space-efficient O(h) not O(n))
- **Inorder on non-BST**: inorder is defined for any binary tree, but sorted property only holds for BST

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | BST problems, "kth smallest", "sorted order", "minimum difference" |
| Core Idea | Left → Root → Right; BST gives sorted sequence |
| Trigger Keywords | "BST", "sorted order", "kth element", "validate", "minimum difference" |
| Avoid When | Non-BST tree, or need top-down processing |
| Time Complexity | O(n) |
| Space Complexity | O(h) recursive, O(h) iterative stack |

**Gotchas:**
- BST Validate: pass (lo, hi) bounds to each call — never compare just with parent
- Kth Smallest: use a reference counter, stop recursion early when k hits 0
- BST Iterator: iterative inorder with explicit stack; `next()` = O(h) amortized, not O(1) per call

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"kth smallest in BST"` → inorder counter
- `"validate BST"` → inorder must be strictly increasing, or use bounds recursion
- `"mode in BST"`, `"minimum difference in BST"` → inorder gives sorted sequence, track previous node
- `"BST iterator"` → iterative inorder with stack

---

## 4. C++ Template

```cpp
/*
 * Pattern: Recursive Inorder
 * Use when: BST sorted-order problems
 * Time: O(n) | Space: O(h)
 */

struct TreeNode { int val; TreeNode *left, *right; };

// BASIC INORDER
void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);     // left first
    result.push_back(root->val);     // process root
    inorder(root->right, result);    // then right
}

// VALIDATE BST (with bounds)
bool isValidBST(TreeNode* root, long lo = LLONG_MIN, long hi = LLONG_MAX) {
    if (!root) return true;
    if (root->val <= lo || root->val >= hi) return false;
    return isValidBST(root->left, lo, root->val) &&
           isValidBST(root->right, root->val, hi);
}

// KTH SMALLEST
int kthSmallest(TreeNode* root, int k) {
    int count = k, result = -1;
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node || count == 0) return;
        inorder(node->left);
        if (--count == 0) result = node->val;
        inorder(node->right);
    };
    inorder(root);
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For BST problems that need sorted order, inorder traversal gives elements in ascending order. I'll use inorder DFS. For BST validation, I pass valid (min, max) bounds rather than just comparing with the parent node — that handles cases where a grandchild is invalid relative to a grandparent."

### Interview Flow Checklist
- [ ] Confirm: is it a BST?
- [ ] Explain: inorder gives sorted sequence for BST
- [ ] For validate: use bounds (lo, hi), not just parent comparison
- [ ] For kth: decrement counter, stop early

---

## 6. Problems

---

### Problem 1: 98. Validate Binary Search Tree
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/validate-binary-search-tree/
**Optimal C++ Solution:**
```cpp
bool isValidBST(TreeNode* root, long lo = LLONG_MIN, long hi = LLONG_MAX) {
    if (!root) return true;
    if ((long)root->val <= lo || (long)root->val >= hi) return false;
    return isValidBST(root->left, lo, root->val) &&
           isValidBST(root->right, root->val, hi);
}
```
**Edge Cases:** [ ] Single node, [ ] Values at INT_MIN or INT_MAX, [ ] Duplicate values (strict inequality)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 230. Kth Smallest Element in a BST
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/kth-smallest-element-in-a-bst/
**Optimal C++ Solution:**
```cpp
int kthSmallest(TreeNode* root, int k) {
    int result = -1;
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node || k == 0) return;
        inorder(node->left);
        if (--k == 0) result = node->val;
        inorder(node->right);
    };
    inorder(root);
    return result;
}
```
**Edge Cases:** [ ] k = 1 (smallest), [ ] k = n (largest)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 173. Binary Search Tree Iterator
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/binary-search-tree-iterator/
**Why this pattern fits:** Iterative inorder with stack; simulate paused traversal

**Optimal C++ Solution:**
```cpp
class BSTIterator {
    stack<TreeNode*> stk;

    void pushLeft(TreeNode* node) {
        while (node) { stk.push(node); node = node->left; }
    }

public:
    BSTIterator(TreeNode* root) { pushLeft(root); }

    int next() {
        TreeNode* node = stk.top(); stk.pop();
        pushLeft(node->right);  // push all left children of right subtree
        return node->val;
    }

    bool hasNext() { return !stk.empty(); }
};
```
**Complexity:** O(h) space, O(h) amortized per next() call

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 530. Minimum Absolute Difference in BST
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/minimum-absolute-difference-in-bst/
**Optimal C++ Solution:**
```cpp
int getMinimumDifference(TreeNode* root) {
    int minDiff = INT_MAX, prev = INT_MIN;
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        if (prev != INT_MIN) minDiff = min(minDiff, node->val - prev);
        prev = node->val;
        inorder(node->right);
    };
    inorder(root);
    return minDiff;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a BST, convert it into a sorted doubly linked list in-place.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Inorder DFS with prev pointer
**Reason:** Track previous inorder node. Connect prev->right = curr, curr->left = prev. At the end, connect head and tail for circular list. LC 426 (premium).
</details>

---

**Drill 2:**
> Given a BST and two nodes, find their lowest common ancestor.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BST Property (not strictly inorder)
**Reason:** For BST LCA: if both p and q are less than root, go left; if both greater, go right; else root is the LCA. O(h) time, no traversal needed. LC 235.
</details>

---

**Drill 3:**
> Find the in-order successor of a given node in a BST.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BST Property
**Reason:** If node has right subtree → leftmost of right subtree. If not → walk from root, track the last node where we went left (that's the successor). O(h) time.
</details>

---

**Drill 4:**
> Given a sorted array, convert it to a height-balanced BST.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Divide and Conquer (not inorder traversal)
**Reason:** Middle element of array becomes root. Recursively build left from left half, right from right half. This produces a balanced BST. LC 108.
</details>

---

**Drill 5:**
> Check if the inorder traversal of two BSTs produces the same sequence.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Iterative Inorder (BST Iterator on both)
**Reason:** Use two BST iterators simultaneously. At each step, advance both and compare. If any values differ → not same. This avoids materializing the full sorted arrays.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Inorder traversal | O(n) | O(h) | — |
| Validate BST | O(n) | O(h) | With bounds recursion |
| Kth Smallest | O(k + h) | O(h) | Early exit after k visits |
| BST Iterator | O(1) amortized | O(h) | Stack holds left spine |
| Min Difference | O(n) | O(h) | Track prev node |

---

## 9. Common Follow-up Questions

1. BST Iterator with O(1) space? (Not straightforward — needs Morris traversal)
2. Is there an iterative inorder without recursion? (Yes — use explicit stack, see template)
3. Can you find kth LARGEST instead? (Yes — reverse inorder: right → root → left, or count n-k+1 from smallest)
4. Mode in BST with O(1) space? (Morris inorder traversal to avoid stack space)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Stack (iterative) | BST Iterator design | 173. BST Iterator |
| Divide and Conquer | Reconstruct BST | 1008. Construct BST from Preorder |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
