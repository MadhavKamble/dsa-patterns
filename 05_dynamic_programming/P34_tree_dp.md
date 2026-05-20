# Pattern 34: Tree DP (DP on Trees)

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 337. House Robber III | Medium | https://leetcode.com/problems/house-robber-iii/ |
| 2 | 543. Diameter of Binary Tree | Easy | https://leetcode.com/problems/diameter-of-binary-tree/ |
| 3 | 124. Binary Tree Maximum Path Sum | Hard | https://leetcode.com/problems/binary-tree-maximum-path-sum/ |
| 4 | 968. Binary Tree Cameras | Hard | https://leetcode.com/problems/binary-tree-cameras/ |
| 5 | 1245. Tree Diameter | Medium | https://leetcode.com/problems/tree-diameter/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Tree DP** applies dynamic programming on tree structures using postorder DFS. Each recursive call returns a tuple of values representing different "states" for that subtree. The parent combines children's states to form its own.

**Core structure:**
- The recursive function returns **multiple values** (a pair or tuple) representing different choices at each node
- Postorder: process children first, then combine at current node
- Common states: (rob, skip), (with_camera, without_camera, covered), (include_node, exclude_node)

**Why it's different from regular postorder:**
- Regular postorder: returns ONE value (like height or max)
- Tree DP: returns a VECTOR/PAIR of values (one per possible state at this node)

### Visual Walkthrough
```
House Robber III: rob the tree, can't rob adjacent nodes

States per node: (rob_this, skip_this)

    3
   / \
  2   3
   \   \
    3   1

Leaves:
  rob(3_left) = (3, 0)  [rob=3, skip=0]
  rob(1_right) = (1, 0)

Node 2 (with child 3_left):
  rob_this = 2 + skip(left) + skip(right) = 2 + 0 + 0 = 2
  skip_this = max(rob_left, skip_left) + max(rob_right, skip_right) = max(3,0) = 3
  → (2, 3)

Node 3 (with child 1_right):
  rob_this = 3 + 0 = 3
  skip_this = max(1, 0) = 1
  → (3, 1)

Root 3 (with children (2,3) and (3,1)):
  rob_this = 3 + skip(left) + skip(right) = 3 + 3 + 1 = 7
  skip_this = max(2,3) + max(3,1) = 3 + 3 = 6
  → (7, 6)  → Answer: max(7,6) = 7
```

### When TO use this pattern
- Optimization on a tree where adjacent nodes can't both be chosen
- Camera placement on tree (greedy + states)
- Maximum path sum through arbitrary nodes in a tree
- Diameter of tree (longest path)
- Any "choose or not choose each node" problem

### When NOT to use this pattern
- Linear DP (use array-based DP)
- BFS-based tree problems (level order processing)
- Problems where parent info needed top-down (use DFS with parameters, not postorder return)

### Common Beginner Mistakes
- **Single return vs tuple**: tree DP usually returns multiple values — don't flatten to one
- **Diameter**: track global max ACROSS the root (left_depth + right_depth), but return only ONE arm to parent
- **Camera placement**: 3 states needed (has_camera, covered_by_child, not_covered) — getting states wrong is the main error
- **Path sum**: function returns max "arm" to parent; path THROUGH node (left_arm + val + right_arm) updates global

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "optimal on tree", "adjacent nodes", "path through tree", "camera coverage" |
| Core Idea | Postorder DFS returning (state1, state2, ...); parent combines children's states |
| Trigger Keywords | "house robber tree", "tree cameras", "maximum path sum", "diameter", "tree DP" |
| Avoid When | Need global tree structure (use different traversal), BFS needed |
| Time Complexity | O(n) |
| Space Complexity | O(h) — recursion stack |

**Gotchas:**
- House Robber III: return (rob_root, skip_root); parent computes both
- Camera (968): return 3 states; count cameras when you place at a node
- Path Sum: return single arm to parent; update global with two-arm path
- Diameter: same as path sum structure but measure depth not sum

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"rob houses on a tree"` → Tree DP with (rob, skip) states
- `"minimum cameras to monitor all nodes"` → Tree DP with 3 states
- `"maximum path sum"` → global variable updated with left+val+right; return single arm
- `"diameter of tree"` → same structure as max path sum but returns depth
- `"no two adjacent nodes"` in a tree → tree DP with exclude/include states

---

## 4. C++ Template

```cpp
/*
 * Pattern: Tree DP
 * Time: O(n) | Space: O(h)
 */

struct TreeNode { int val; TreeNode *left, *right; };

// HOUSE ROBBER III (return pair)
pair<int,int> robDP(TreeNode* node) {
    if (!node) return {0, 0};
    auto [lr, ls] = robDP(node->left);
    auto [rr, rs] = robDP(node->right);
    int rob  = node->val + ls + rs;       // rob root: skip both children
    int skip = max(lr,ls) + max(rr,rs);  // skip root: optimal choice per child
    return {rob, skip};
}

int rob(TreeNode* root) {
    auto [r, s] = robDP(root);
    return max(r, s);
}

// CAMERA COVERAGE (return 3 states)
// 0 = has camera, 1 = covered by child, 2 = not covered
int cameras = 0;
int cameraDP(TreeNode* node) {
    if (!node) return 1;  // null = covered (doesn't need camera)
    int left  = cameraDP(node->left);
    int right = cameraDP(node->right);
    if (left == 2 || right == 2) {  // child not covered → place camera here
        cameras++;
        return 0;
    }
    if (left == 0 || right == 0) return 1;  // child has camera → we're covered
    return 2;  // neither child covers us → not covered
}

int minCameraCover(TreeNode* root) {
    cameras = 0;
    if (cameraDP(root) == 2) cameras++;  // root not covered → add camera
    return cameras;
}

// MAX PATH SUM (global + single arm)
int maxPathSum(TreeNode* root) {
    int best = INT_MIN;
    function<int(TreeNode*)> gain = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int l = max(0, gain(node->left));
        int r = max(0, gain(node->right));
        best = max(best, l + node->val + r);  // path through this node
        return node->val + max(l, r);          // single arm to parent
    };
    gain(root);
    return best;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For House Robber on a tree, each node has two choices: rob it or skip it. I use postorder DFS, so children's results are computed before the parent decides. The function returns a pair (rob, skip). Rob = node.val + skip(left) + skip(right) — can't rob adjacent nodes so children must be skipped. Skip = max(rob, skip) for each child — can take either option for children. The root's answer is max(rob_root, skip_root)."

### Interview Flow Checklist
- [ ] Define states per node (what choices exist at each node?)
- [ ] Handle null base case (what value does null contribute?)
- [ ] Postorder: compute left and right first
- [ ] Combine children's states to compute current node's states
- [ ] Return states tuple (not just final answer — parent needs all states)
- [ ] Extract final answer at root

---

## 6. Problems

---

### Problem 1: 337. House Robber III
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/house-robber-iii/
**Optimal C++ Solution:**
```cpp
int rob(TreeNode* root) {
    function<pair<int,int>(TreeNode*)> dfs = [&](TreeNode* node) -> pair<int,int> {
        if (!node) return {0, 0};
        auto [lr, ls] = dfs(node->left);
        auto [rr, rs] = dfs(node->right);
        return {node->val + ls + rs, max(lr,ls) + max(rr,rs)};
    };
    auto [r, s] = dfs(root);
    return max(r, s);
}
```
**Edge Cases:** [ ] Single node, [ ] All nodes in a line (like linear house robber)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 124. Binary Tree Maximum Path Sum
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/binary-tree-maximum-path-sum/
**Optimal C++ Solution:**
```cpp
int maxPathSum(TreeNode* root) {
    int best = INT_MIN;
    function<int(TreeNode*)> gain = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int l = max(0, gain(node->left));
        int r = max(0, gain(node->right));
        best = max(best, node->val + l + r);
        return node->val + max(l, r);
    };
    gain(root);
    return best;
}
```
**Edge Cases:** [ ] All negative nodes (answer = max single node value), [ ] Single node

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
    int diam = 0;
    function<int(TreeNode*)> depth = [&](TreeNode* node) -> int {
        if (!node) return 0;
        int l = depth(node->left), r = depth(node->right);
        diam = max(diam, l + r);
        return 1 + max(l, r);
    };
    depth(root);
    return diam;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 968. Binary Tree Cameras
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/binary-tree-cameras/
**Optimal C++ Solution:**
```cpp
int minCameraCover(TreeNode* root) {
    int cameras = 0;
    // returns: 0=has camera, 1=covered (by child), 2=not covered
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
        if (!node) return 1;  // null is "covered" by default
        int l = dfs(node->left), r = dfs(node->right);
        if (l == 2 || r == 2) { cameras++; return 0; }  // must cover child
        if (l == 0 || r == 0) return 1;  // covered by child's camera
        return 2;  // children covered but don't cover us
    };
    if (dfs(root) == 2) cameras++;  // root uncovered → add camera
    return cameras;
}
```
**Edge Cases:** [ ] Single node (1 camera), [ ] Linear tree

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 1245. Tree Diameter
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/tree-diameter/
**Why this pattern fits:** N-ary tree diameter — same pattern as binary tree but for all children

**Optimal C++ Solution:**
```cpp
int treeDiameter(vector<vector<int>>& edges) {
    int n = edges.size() + 1;
    vector<vector<int>> adj(n);
    for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
    int diam = 0;
    function<int(int,int)> dfs = [&](int u, int parent) -> int {
        int top1 = 0, top2 = 0;
        for (int v : adj[u]) {
            if (v == parent) continue;
            int depth = dfs(v, u);
            if (depth > top1) { top2 = top1; top1 = depth; }
            else if (depth > top2) top2 = depth;
        }
        diam = max(diam, top1 + top2);
        return top1 + 1;
    };
    dfs(0, -1);
    return diam;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> In a tree where each node has a color, find the largest subtree where all nodes have the same color.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Tree DP — return (isMonochromatic, size, color)
**Reason:** Postorder: leaf returns (true, 1, leaf.color). Internal node: if all children are monochromatic with same color as current node → (true, sum_of_sizes + 1, color). Else (false, ..., ...). Track max size among all monochromatic subtrees.
</details>

---

**Drill 2:**
> Find the maximum number of edges you can remove from a tree such that the remaining forest is "balanced" — each tree in the forest has the same number of nodes.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Tree DP — subtree sizes
**Reason:** Compute subtree size for every node. Cut an edge to create a subtree of size k if n/k is an integer AND k divides n. Greedily count valid cuts. Check if total_nodes % subtree_size == 0. LC 2440 variant.
</details>

---

**Drill 3:**
> In a tree, you can paint nodes either red or blue. A valid coloring requires no two adjacent nodes to have the same color. Count the number of valid colorings.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Tree DP — (count with node red, count with node blue)
**Reason:** Since trees are bipartite (no odd cycles), exactly 2 valid 2-colorings exist for a connected tree (swap all colors). If tree has k components, answer = 2^k. But if you want to count with specific root colors: dp[node][color] = product of dp[child][1-color] for all children.
</details>

---

**Drill 4:**
> You want to select a subset of nodes from a tree to maximize the sum of selected node values, with the constraint that no two selected nodes can be more than distance 2 apart (they must be reachable within 2 edges).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Tree DP with distance-aware states
**Reason:** State per node: (selected, not_selected) — like house robber but distance constraint extends to grandchildren. Return (with_node, without_node) but the recurrence must account for children AND grandchildren. More complex state than standard tree DP.
</details>

---

**Drill 5:**
> Find the minimum number of edges to add to a tree to make every node have even degree.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Tree DP + parity tracking
**Reason:** Euler path theory: a graph has an Eulerian circuit iff all nodes have even degree. In a tree, leaves have degree 1 (odd). dp[node] = parity of subtree's "excess" edges needed. Pair up leaves optimally using tree structure. Answer relates to number of odd-degree nodes divided by 2.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | States returned |
|---------|------|-------|-----------------|
| House Robber III | O(n) | O(h) | (rob, skip) pair |
| Max Path Sum | O(n) | O(h) | int (single arm) + global |
| Diameter | O(n) | O(h) | int (depth) + global |
| Tree Cameras | O(n) | O(h) | {0, 1, 2} states |
| Tree Diameter (N-ary) | O(n) | O(h) | int (max depth) + global |

---

## 9. Common Follow-up Questions

1. How does Tree DP relate to postorder traversal? (Tree DP IS postorder DP — the DP table entries are the values computed at each node during postorder traversal)
2. Can you do tree DP iteratively? (Yes — topological sort the tree (BFS level order), then process in reverse BFS order (leaves first); same as postorder)
3. House Robber on a general graph (not tree)? (Harder — equivalent to Maximum Independent Set, which is NP-hard for general graphs. For trees it's O(n) because no cross-edges)
4. What if a tree has weights on edges (not nodes)? (Same DP structure, but "gain" from a path segment uses edge weight instead of node value)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Postorder DFS | Core traversal for tree DP | All tree DP problems |
| 1D DP | Tree DP results can feed into 1D DP | Path queries on tree |
| Greedy | Camera problem has greedy flavor | 968. Binary Tree Cameras |
| LCA | Path queries using LCA + tree DP | Distance queries on tree |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
