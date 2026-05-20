# P68 — Iterative DFS and Tree Traversal with Stack

## 1. First-Timer Explanation

### What Is It?
**Iterative DFS** replaces the call stack of recursive DFS with an explicit stack. This avoids stack overflow for deep graphs/trees and gives fine-grained control over traversal order. The key: simulating what the recursion stack would hold.

### Recursive vs Iterative DFS
```
Recursive inorder (left, root, right):
    inorder(root):
        inorder(root.left)
        visit(root)
        inorder(root.right)

Iterative inorder:
    stack = []
    cur = root
    while cur or stack:
        while cur:
            stack.push(cur)
            cur = cur.left
        cur = stack.pop()
        visit(cur)
        cur = cur.right
```

### When to Use
- Tree traversal when recursion depth is a concern
- "Iterative preorder/inorder/postorder"
- Graph DFS when you need to control the order precisely
- Problems where you need to do work AFTER returning from children (postorder)

### Iterative Postorder Trick
Postorder (left, right, root) is the hardest. Trick: modified preorder visits in (root, right, left) order → reverse = (left, right, root) = postorder.

---

## 2. Revision Card

**Recognition Signal:** "iterative traversal", "avoid recursion", "explicit stack for DFS"

**Core Idea:** Replace call stack with explicit stack. For inorder: go left until null, pop, visit, go right. For preorder: push right then left (so left is processed first). For postorder: use reverse of (root, right, left).

**Trigger Keywords:** iterative, traversal, inorder, preorder, postorder, Morris traversal

**Complexity:** O(n) time, O(h) space (h = height)

---

## 3. Interview Tell Signs

- "Implement inorder traversal without recursion" → explicit stack
- "Avoid stack overflow on deep trees" → iterative
- "BFS/DFS with control over backtracking" → iterative with explicit stack state

---

## 4. C++ Template

```cpp
#include <stack>
#include <vector>
using namespace std;
struct TreeNode { int val; TreeNode *left, *right; };

// ── Inorder (Left, Root, Right) ───────────────────────────────────────────────
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    while (cur || !stk.empty()) {
        while (cur) { stk.push(cur); cur = cur->left; }
        cur = stk.top(); stk.pop();
        res.push_back(cur->val);
        cur = cur->right;
    }
    return res;
}

// ── Preorder (Root, Left, Right) ──────────────────────────────────────────────
vector<int> preorderTraversal(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    stack<TreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
        auto node = stk.top(); stk.pop();
        res.push_back(node->val);
        if (node->right) stk.push(node->right); // right first (LIFO)
        if (node->left)  stk.push(node->left);  // left on top → processed first
    }
    return res;
}

// ── Postorder (Left, Right, Root) ─────────────────────────────────────────────
vector<int> postorderTraversal(TreeNode* root) {
    if (!root) return {};
    vector<int> res;
    stack<TreeNode*> stk;
    stk.push(root);
    while (!stk.empty()) {
        auto node = stk.top(); stk.pop();
        res.push_back(node->val);  // "root" first
        if (node->left)  stk.push(node->left);  // left first (will be processed later)
        if (node->right) stk.push(node->right); // right second
    }
    reverse(res.begin(), res.end()); // reverse: root-right-left → left-right-root
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Inorder):**
> "I use an explicit stack to simulate the call stack. I maintain a `cur` pointer. I push nodes while going left (equivalent to the recursive descent). When I can't go left, I pop the node, visit it (it's the 'inorder' position), and then set cur = node.right to process the right subtree. This perfectly mirrors the recursive inorder."

**Checklist:**
- [ ] Inorder: `while cur` inner loop goes left, pop, visit, go right
- [ ] Preorder: push right then left (LIFO reverses order)
- [ ] Postorder: either modified preorder + reverse, or two-stack method
- [ ] Graph DFS: push neighbors onto stack, mark visited when pushed or popped

---

## 6. Problems

### Problem 1: Binary Tree Inorder Traversal
**Difficulty:** Easy | **LC:** 94

```cpp
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> res;
    stack<TreeNode*> stk;
    TreeNode* cur = root;
    while (cur || !stk.empty()) {
        while (cur) { stk.push(cur); cur = cur->left; }
        cur = stk.top(); stk.pop();
        res.push_back(cur->val);
        cur = cur->right;
    }
    return res;
}
// Time: O(n) | Space: O(h)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Binary Tree Preorder Traversal
**Difficulty:** Easy | **LC:** 144

```cpp
vector<int> preorderTraversal(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> stk;
    stk.push(root);
    vector<int> res;
    while (!stk.empty()) {
        auto node = stk.top(); stk.pop();
        res.push_back(node->val);
        if (node->right) stk.push(node->right);
        if (node->left)  stk.push(node->left);
    }
    return res;
}
// Time: O(n) | Space: O(n) worst (skewed tree)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Binary Search Tree Iterator
**Difficulty:** Medium | **LC:** 173

**Approach:** Inorder iterator. Initialize by going left from root. `next()` pops top, goes right.

```cpp
class BSTIterator {
    stack<TreeNode*> stk;
    void pushLeft(TreeNode* node) {
        while (node) { stk.push(node); node = node->left; }
    }
public:
    BSTIterator(TreeNode* root) { pushLeft(root); }
    int next() {
        auto node = stk.top(); stk.pop();
        pushLeft(node->right);
        return node->val;
    }
    bool hasNext() { return !stk.empty(); }
};
// next/hasNext: O(1) amortized | Space: O(h)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Flatten Binary Tree to Linked List
**Difficulty:** Medium | **LC:** 114

**Approach:** Iterative preorder. Track previous node; attach current as right child of prev.

```cpp
void flatten(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> stk;
    stk.push(root);
    TreeNode* prev = nullptr;
    while (!stk.empty()) {
        auto node = stk.top(); stk.pop();
        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
        if (prev) { prev->right = node; prev->left = nullptr; }
        prev = node;
    }
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Path Sum II (Iterative DFS)
**Difficulty:** Medium | **LC:** 113

**Approach:** Iterative DFS with explicit path tracking. Stack stores (node, current_path, current_sum).

```cpp
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> res;
    if (!root) return res;
    stack<tuple<TreeNode*, vector<int>, int>> stk;
    stk.push({root, {root->val}, root->val});
    
    while (!stk.empty()) {
        auto [node, path, sum] = stk.top(); stk.pop();
        if (!node->left && !node->right && sum == targetSum) res.push_back(path);
        if (node->right) {
            auto np = path; np.push_back(node->right->val);
            stk.push({node->right, np, sum + node->right->val});
        }
        if (node->left) {
            auto np = path; np.push_back(node->left->val);
            stk.push({node->left, np, sum + node->left->val});
        }
    }
    return res;
}
// Time: O(n^2) (path copying) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Iterative inorder for BST gives elements in sorted order. Why?
<details><summary>Reveal</summary>
BST property: left subtree < root < right subtree. Inorder visits left before root before right. Applying this recursively visits all elements in ascending order. The iterative version preserves this order since it exactly simulates the recursive inorder.
</details>

**Drill 2:** Preorder iterative: why push RIGHT then LEFT?
<details><summary>Reveal</summary>
Stack is LIFO. We want to process LEFT before RIGHT. If we push LEFT before RIGHT, RIGHT is on top → processed first (wrong). Pushing RIGHT first puts LEFT on top → LEFT processed first. LIFO reverses the push order.
</details>

**Drill 3:** BST Iterator: `hasNext()` returns true if stack is non-empty. What does an empty stack mean?
<details><summary>Reveal</summary>
Empty stack means we've processed all nodes up to the current position and there's no right subtree to expand further. The iteration is complete.
</details>

**Drill 4:** Postorder via "reverse modified preorder": explain why (root, right, left) reversed = (left, right, root).
<details><summary>Reveal</summary>
Preorder visits: root, left, right. Modified to push left first (so right processed first): root, right, left. Reversing this sequence: left, right, root = postorder. The reversal step (using a second stack or reversing the vector) completes the transformation.
</details>

**Drill 5:** What's Morris traversal and when would you use it over iterative with stack?
<details><summary>Reveal</summary>
Morris traversal uses thread pointers (temporary modifications to tree structure) to traverse in O(n) time with O(1) extra space. Use it when space is critical (e.g., embedded systems) or the interviewer specifically asks for O(1) space tree traversal.
</details>

---

## 8. Complexity Cheatsheet

| Traversal | Time | Space | Notes |
|-----------|------|-------|-------|
| Inorder iterative | O(n) | O(h) | h = height |
| Preorder iterative | O(n) | O(n) worst | O(h) balanced |
| Postorder iterative | O(n) | O(n) | uses reverse |
| Morris traversal | O(n) | O(1) | modifies tree |
| BST Iterator | O(1) amortized | O(h) | |

---

## 9. Common Follow-up Questions

**Q: Which traversal order does a BST iterator use?**
A: Inorder — gives elements in sorted order.

**Q: How would you do a level-order traversal (BFS)?**
A: Use a queue, not a stack. BFS naturally gives level-order.

**Q: Can you do Morris traversal for all three orders?**
A: Yes — Morris traversal exists for preorder, inorder, and postorder, all O(n) time O(1) space.

---

## 10. Cross-Pattern Connections

- **P12-P17 (Tree Problems):** All use DFS; iterative is an alternative implementation
- **P18 (DFS Connected Components):** Same iterative DFS principle on graphs
- **P65 (Expression Eval):** Both use explicit stacks to simulate recursion
- **P64 (Monotonic Stack):** Uses stack but for a different purpose (boundaries, not traversal)
