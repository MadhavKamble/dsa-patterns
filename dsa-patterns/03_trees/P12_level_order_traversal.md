# Pattern 12: Level Order Traversal (BFS)

## Category
Trees

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 102. Binary Tree Level Order Traversal | Medium | https://leetcode.com/problems/binary-tree-level-order-traversal/ |
| 2 | 103. Binary Tree Zigzag Level Order Traversal | Medium | https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/ |
| 3 | 199. Binary Tree Right Side View | Medium | https://leetcode.com/problems/binary-tree-right-side-view/ |
| 4 | 515. Find Largest Value in Each Tree Row | Medium | https://leetcode.com/problems/find-largest-value-in-each-tree-row/ |
| 5 | 1161. Maximum Level Sum of a Binary Tree | Medium | https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Level order traversal visits all nodes level by level — first the root (level 0), then all children (level 1), then grandchildren (level 2), etc. It's implemented using a **queue** (BFS).

The key technique for keeping track of levels: snapshot the queue size at the start of each level. Process exactly that many nodes (they're all at the current level), and enqueue their children (which belong to the next level).

### Real-World Analogy
Broadcasting an announcement in an organization: first tell the CEO (root), then tell all VP's (level 1 — direct reports), then all managers (level 2), and so on. Each "generation" is fully notified before moving to the next.

### Visual Walkthrough
```
Tree:
       3
      / \
     9   20
        /  \
       15   7

Queue processing:
Level 0: snapshot_size=1. Process [3]. Enqueue 9, 20.
Level 1: snapshot_size=2. Process [9, 20]. Enqueue 15, 7.
Level 2: snapshot_size=2. Process [15, 7]. No children.

Result: [[3], [9,20], [15,7]]
```

### When TO use this pattern
- Process tree nodes level by level
- Find right/left side view
- Find level with max/min sum or value
- Shortest path from root to a target node
- Zigzag traversal

### When NOT to use this pattern
- Need path sum, height, diameter → use DFS postorder
- No level-grouping needed → DFS is simpler
- Memory is tight (BFS uses O(width) space; DFS uses O(height) space — BFS worse for wide trees)

### Common Beginner Mistakes
- **Snapshot queue size at start of level loop**: `int levelSize = q.size()` THEN loop exactly levelSize times
- **Never snapshot during processing**: queue grows as you enqueue children mid-loop
- **Always null-check**: only enqueue non-null children
- **Zigzag**: reverse direction flag each level, use pre-sized array for placement

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "level by level", "right side view", "zigzag", "max per level" |
| Core Idea | BFS with queue; snapshot size at start of each level to group nodes |
| Trigger Keywords | "level order", "row by row", "layer", "breadth-first" |
| Avoid When | No level grouping needed, deep trees (BFS has O(width) space) |
| Time Complexity | O(n) |
| Space Complexity | O(w) — w = maximum width of tree |

**Gotchas:**
- `int levelSize = q.size()` snapshots BEFORE the inner loop — this is essential
- Always check `node->left` and `node->right` before pushing to queue
- For right side view: save only the LAST node of each level

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"level order traversal"` → direct BFS with level grouping
- `"right side view"` → BFS, take last element of each level
- `"zigzag"` → BFS with direction toggle per level
- `"maximum/minimum in each row"` → BFS, track per-level extremes

---

## 4. C++ Template

```cpp
/*
 * Pattern: Level Order BFS
 * Use when: process tree level by level
 * Time: O(n) | Space: O(w) — w = max width
 */

struct TreeNode { int val; TreeNode *left, *right; };

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();  // snapshot BEFORE inner loop
        vector<int> level;

        for (int i = 0; i < levelSize; i++) {
            auto node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This requires processing nodes level by level. I'll use BFS with a queue. The critical technique: snapshot `q.size()` before each level's inner loop. That tells me exactly how many nodes are at the current level. Process them, enqueue their children (which go to the next level). Then the outer while loop repeats for the next level."

### Interview Flow Checklist
- [ ] Handle null root
- [ ] Snapshot level size before inner loop
- [ ] Process exact levelSize nodes in inner loop
- [ ] Enqueue non-null children
- [ ] Collect or process level result

---

## 6. Problems

---

### Problem 1: 102. Binary Tree Level Order Traversal
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/binary-tree-level-order-traversal/
**Optimal C++ Solution:**
```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            auto n = q.front(); q.pop();
            level.push_back(n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        result.push_back(level);
    }
    return result;
}
```
**Edge Cases:** [ ] Empty tree, [ ] Single node, [ ] Only left children (linear)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 199. Binary Tree Right Side View
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/binary-tree-right-side-view/
**Why this pattern fits:** BFS level order — take the last node of each level

**Optimal C++ Solution:**
```cpp
vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            auto n = q.front(); q.pop();
            if (i == sz - 1) result.push_back(n->val);  // last in level = rightmost
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }
    return result;
}
```
**Edge Cases:** [ ] Only left children → left nodes are "visible" from right

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 103. Binary Tree Zigzag Level Order Traversal
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
**Why this pattern fits:** BFS with direction flag; use pre-sized level vector for index-based placement

**Optimal C++ Solution:**
```cpp
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    while (!q.empty()) {
        int sz = q.size();
        vector<int> level(sz);
        for (int i = 0; i < sz; i++) {
            auto n = q.front(); q.pop();
            int idx = leftToRight ? i : sz - 1 - i;
            level[idx] = n->val;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        result.push_back(level);
        leftToRight = !leftToRight;
    }
    return result;
}
```
**Edge Cases:** [ ] Single level (no zigzag needed)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 515. Find Largest Value in Each Tree Row
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-largest-value-in-each-tree-row/
**Optimal C++ Solution:**
```cpp
vector<int> largestValues(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size(), levelMax = INT_MIN;
        for (int i = 0; i < sz; i++) {
            auto n = q.front(); q.pop();
            levelMax = max(levelMax, n->val);
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        result.push_back(levelMax);
    }
    return result;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 1161. Maximum Level Sum of a Binary Tree
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/
**Optimal C++ Solution:**
```cpp
int maxLevelSum(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    int maxSum = INT_MIN, bestLevel = 1, level = 1;
    while (!q.empty()) {
        int sz = q.size(), sum = 0;
        for (int i = 0; i < sz; i++) {
            auto n = q.front(); q.pop();
            sum += n->val;
            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
        if (sum > maxSum) { maxSum = sum; bestLevel = level; }
        level++;
    }
    return bestLevel;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find all nodes at distance k from the root in a binary tree.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS Level Order
**Reason:** Level k in BFS from root = all nodes at distance k. Process k levels, collect the last level.
</details>

---

**Drill 2:**
> Check if two binary trees are the same tree, level by level.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS Level Order (on both trees simultaneously)
**Reason:** Run BFS on both trees in parallel, comparing level arrays. Alternatively, use DFS preorder comparison.
</details>

---

**Drill 3:**
> Find the width of the widest level in a binary tree (number of nodes between leftmost and rightmost non-null nodes inclusive).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS Level Order with position tracking
**Reason:** Assign position indices to nodes (left child = 2*pos, right child = 2*pos+1). Width = rightmost - leftmost + 1 per level. This is LC 662.
</details>

---

**Drill 4:**
> Given a binary tree and a target node, find all nodes that are exactly k distance away (not just from root).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS from target node (requires parent pointers)
**Reason:** First pass: DFS to record parent pointers (convert to undirected graph). Second pass: BFS from target node, stopping at distance k. This is LC 863.
</details>

---

**Drill 5:**
> Connect all nodes at the same level to their right neighbor (next node in the same level).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS Level Order — connect consecutive nodes per level
**Reason:** During level processing, connect current node's `next` to the next node in queue (before popping it). Or use O(1) space "perfect binary tree" approach with existing connections. LC 116/117.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Level order traversal | O(n) | O(w) | w = max width |
| Right side view | O(n) | O(w) | BFS, take last per level |
| Zigzag | O(n) | O(w) | Pre-size level array |
| Max per level | O(n) | O(w) | Track max per level |

---

## 9. Common Follow-up Questions

1. What's the maximum space used by BFS? (O(w) = O(n) in worst case for complete binary tree)
2. Can you do level order without a queue? (Yes — iterative DFS with explicit level tracking, or recursion with depth parameter)
3. How to print tree level by level without grouping? (Just BFS without the level snapshot)
4. What's the difference between right side view and rightmost node per level? (Same thing — rightmost visible node is the last in BFS queue at each level)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Graph BFS | Any shortest path on tree | Find distance between nodes |
| DFS Postorder | Some level-order questions solved more naturally with DFS | Tree height via postorder |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
