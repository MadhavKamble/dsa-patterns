# Pattern 21: Topological Sort

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 207. Course Schedule | Medium | https://leetcode.com/problems/course-schedule/ |
| 2 | 210. Course Schedule II | Medium | https://leetcode.com/problems/course-schedule-ii/ |
| 3 | 269. Alien Dictionary | Hard | https://leetcode.com/problems/alien-dictionary/ |
| 4 | 310. Minimum Height Trees | Medium | https://leetcode.com/problems/minimum-height-trees/ |
| 5 | 444. Sequence Reconstruction | Medium | https://leetcode.com/problems/sequence-reconstruction/ |
| 6 | 1203. Sort Items by Groups Respecting Dependencies | Hard | https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Topological sort** orders nodes of a DAG such that for every edge u→v, u comes before v. It's the linear ordering of a dependency graph.

**Two equivalent approaches:**

**Kahn's Algorithm (BFS, iterative):**
1. Compute in-degree for every node
2. Enqueue all nodes with in-degree 0 (no dependencies)
3. Dequeue a node → add to result → decrement in-degrees of its neighbors
4. When a neighbor's in-degree hits 0 → enqueue it
5. If result has all nodes → valid topo order; else → cycle exists

**DFS Postorder:**
1. DFS; after fully exploring a node's neighbors, push it to a stack
2. Reverse the stack → topological order
3. Cycle detection: same as 3-color DFS (gray node = cycle)

### Visual Walkthrough
```
Graph: A → C, B → C, C → D
       In-degrees: A=0, B=0, C=2, D=1

Kahn's BFS:
  Queue: [A, B]
  Dequeue A: result=[A], C.indegree=1
  Dequeue B: result=[A,B], C.indegree=0 → enqueue C
  Dequeue C: result=[A,B,C], D.indegree=0 → enqueue D
  Dequeue D: result=[A,B,C,D]
  All 4 nodes → valid, no cycle

DFS postorder:
  DFS(A) → DFS(C) → DFS(D) → push D → push C → push A
  DFS(B) → push B
  Stack: [D, C, A, B] → reverse → [B, A, C, D] (valid order)
```

### When TO use this pattern
- Order tasks with dependencies
- "Can all tasks be completed?" (detect cycle)
- "Find a valid ordering" of dependent items
- Alien dictionary (infer character order from sorted word list)
- Minimum height trees (peel leaves iteratively = Kahn's on undirected)

### When NOT to use this pattern
- Graph has undirected edges (topo sort only for DAGs)
- Need shortest/longest path (different algorithms, though topo sort can help for DAG DP)

### Common Beginner Mistakes
- **Cycle = no valid order**: Kahn's result size < n means cycle exists
- **Multiple valid orders**: any valid topological order is acceptable unless uniqueness is required
- **Alien dictionary**: edge direction is FROM smaller to larger char in ordering; wrong direction = wrong answer
- **In-degree initialization**: count all prerequisites, not just first appearances

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "ordering with dependencies", "prerequisites", "compile order", "build order" |
| Core Idea | Kahn's BFS: process 0-in-degree nodes first, decrement neighbors; or DFS postorder reversed |
| Trigger Keywords | "course schedule", "prerequisites", "order", "alien dictionary", "dependency" |
| Avoid When | Undirected graph, or need shortest path (use BFS/Dijkstra) |
| Time Complexity | O(V + E) |
| Space Complexity | O(V + E) |

**Gotchas:**
- Kahn's: result.size() != n means cycle
- DFS topo: push to result AFTER all neighbors are done (postorder)
- Alien dictionary: only adjacent word pairs give ordering constraints
- Multiple valid orders: any is fine unless problem asks for lexicographically smallest

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"course schedule"`, `"finish all courses"` → topo sort + cycle detection
- `"order of"`, `"build order"` → topo sort output
- `"alien dictionary"`, `"unknown language"` → derive char ordering from word list → topo sort
- `"minimum height trees"` → BFS peel-leaves (Kahn's on undirected, find centroid)
- `"sequence reconstruction"` → verify unique topo order

---

## 4. C++ Template

```cpp
/*
 * Pattern: Topological Sort
 * Time: O(V+E) | Space: O(V+E)
 */

// KAHN'S ALGORITHM (BFS)
vector<int> topoSortKahn(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) indegree[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0) q.push(i);

    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--indegree[v] == 0) q.push(v);
    }
    return (int)order.size() == n ? order : vector<int>{};  // empty = cycle
}

// DFS POSTORDER (reversed)
vector<int> topoSortDFS(int n, vector<vector<int>>& adj) {
    vector<int> state(n, 0), order;
    function<bool(int)> dfs = [&](int u) -> bool {
        state[u] = 1;
        for (int v : adj[u]) {
            if (state[v] == 1) return false;  // cycle
            if (state[v] == 0 && !dfs(v)) return false;
        }
        state[u] = 2;
        order.push_back(u);
        return true;
    };
    for (int i = 0; i < n; i++)
        if (state[i] == 0 && !dfs(i)) return {};
    reverse(order.begin(), order.end());
    return order;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll use Kahn's algorithm — an iterative BFS approach. First, I compute the in-degree of every node. Nodes with in-degree 0 have no prerequisites, so I enqueue them. I then process nodes from the queue: each dequeued node is added to the result, and I decrement the in-degree of all its successors. When a successor reaches in-degree 0, it's ready to process and gets enqueued. At the end, if the result contains all n nodes, we have a valid topological order. If not, a cycle exists."

### Interview Flow Checklist
- [ ] Build adjacency list + in-degree array
- [ ] Enqueue all in-degree-0 nodes
- [ ] BFS: dequeue → add to result → decrement successors' in-degrees → enqueue newly 0
- [ ] Check result.size() == n (no cycle)
- [ ] Return order or empty/false for cycle

---

## 6. Problems

---

### Problem 1: 210. Course Schedule II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/course-schedule-ii/
**Optimal C++ Solution:**
```cpp
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        indegree[p[0]]++;
    }
    queue<int> q;
    for (int i = 0; i < numCourses; i++)
        if (indegree[i] == 0) q.push(i);
    vector<int> order;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (--indegree[v] == 0) q.push(v);
    }
    return (int)order.size() == numCourses ? order : vector<int>{};
}
```
**Edge Cases:** [ ] No prerequisites (any order), [ ] Cycle (return empty), [ ] Disconnected components

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 269. Alien Dictionary
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/alien-dictionary/
**Why this pattern fits:** Extract character ordering from adjacent word pairs → topo sort

**Approach:**
1. Compare adjacent words: find first differing character → that's an ordering constraint
2. Build directed graph: `words[i][j] → words[i+1][j]` (smaller char comes first)
3. Topological sort gives the alien alphabet order
4. Edge cases: if word1 is prefix of word2 but word1 is AFTER word2 → invalid

**Optimal C++ Solution:**
```cpp
string alienOrder(vector<string>& words) {
    unordered_map<char, set<char>> adj;
    unordered_map<char, int> indegree;
    for (string& w : words)
        for (char c : w) { adj[c]; indegree[c] = indegree.count(c) ? indegree[c] : 0; }

    for (int i = 0; i < (int)words.size()-1; i++) {
        string& w1 = words[i], &w2 = words[i+1];
        int len = min(w1.size(), w2.size());
        bool found = false;
        for (int j = 0; j < (int)len; j++) {
            if (w1[j] != w2[j]) {
                if (!adj[w1[j]].count(w2[j])) {
                    adj[w1[j]].insert(w2[j]);
                    indegree[w2[j]]++;
                }
                found = true; break;
            }
        }
        if (!found && w1.size() > w2.size()) return "";  // prefix violation
    }

    queue<char> q;
    for (auto& [c, deg] : indegree)
        if (deg == 0) q.push(c);
    string result;
    while (!q.empty()) {
        char c = q.front(); q.pop();
        result += c;
        for (char nb : adj[c])
            if (--indegree[nb] == 0) q.push(nb);
    }
    return result.size() == indegree.size() ? result : "";
}
```
**Edge Cases:** [ ] Single char, [ ] Longer word before prefix, [ ] Cycle in constraints

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 310. Minimum Height Trees
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/minimum-height-trees/
**Why this pattern fits:** Iteratively remove leaves (in-degree 1) until 1-2 nodes remain — those are the centroids

**Optimal C++ Solution:**
```cpp
vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
    if (n == 1) return {0};
    vector<set<int>> adj(n);
    for (auto& e : edges) { adj[e[0]].insert(e[1]); adj[e[1]].insert(e[0]); }
    queue<int> leaves;
    for (int i = 0; i < n; i++)
        if (adj[i].size() == 1) leaves.push(i);
    int remaining = n;
    while (remaining > 2) {
        int sz = leaves.size();
        remaining -= sz;
        queue<int> newLeaves;
        while (sz--) {
            int leaf = leaves.front(); leaves.pop();
            int neighbor = *adj[leaf].begin();
            adj[neighbor].erase(leaf);
            if (adj[neighbor].size() == 1) newLeaves.push(neighbor);
        }
        leaves = newLeaves;
    }
    vector<int> result;
    while (!leaves.empty()) { result.push_back(leaves.front()); leaves.pop(); }
    return result;
}
```
**Complexity Analysis:**
- Time: O(n) — each node removed once
- Space: O(n)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 444. Sequence Reconstruction
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/sequence-reconstruction/
**Why this pattern fits:** Check if org is the UNIQUE topological sort of the graph built from sequences

**Optimal C++ Solution:**
```cpp
bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
    unordered_map<int, unordered_set<int>> adj;
    unordered_map<int, int> indegree;
    for (int v : org) indegree[v] = 0;
    for (auto& seq : seqs) {
        for (int v : seq) if (!indegree.count(v)) return false;  // unknown node
        for (int i = 0; i+1 < (int)seq.size(); i++) {
            if (!adj[seq[i]].count(seq[i+1])) {
                adj[seq[i]].insert(seq[i+1]);
                indegree[seq[i+1]]++;
            }
        }
    }
    queue<int> q;
    for (auto& [v, d] : indegree)
        if (d == 0) q.push(v);
    int idx = 0;
    while (!q.empty()) {
        if (q.size() > 1) return false;  // not unique order
        int u = q.front(); q.pop();
        if (org[idx++] != u) return false;
        for (int v : adj[u])
            if (--indegree[v] == 0) q.push(v);
    }
    return idx == (int)org.size();
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a list of projects and dependencies, find the order in which to build them. If no valid order exists, return empty. If multiple orders exist, return lexicographically smallest.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Topological Sort with priority queue (min-heap instead of regular queue)
**Reason:** Kahn's algorithm but replace the regular queue with a min-heap. This always processes the lexicographically smallest available node first, guaranteeing the lexicographically smallest valid topological order.
</details>

---

**Drill 2:**
> You have a timeline of events, each with a start day and end day. Event B must start after event A ends. Find an ordering where no constraints are violated.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Topological Sort
**Reason:** Build a directed graph: edge A → B means "A must come before B." Topological sort gives a valid event ordering. If a cycle exists (circular dependency), no valid schedule exists.
</details>

---

**Drill 3:**
> Given a DAG, find the longest path (in terms of number of edges).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Topological Sort + DP
**Reason:** Process nodes in topological order. For each node u and each edge u→v: dist[v] = max(dist[v], dist[u] + 1). Process in topo order guarantees u is fully processed before v. O(V+E).
</details>

---

**Drill 4:**
> You're given partial ordering constraints for letters. Determine if all given constraints are consistent (can form a valid ordering).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Cycle Detection / Topological Sort
**Reason:** Each constraint "A before B" = edge A → B. Build a directed graph and check for cycles using DFS 3-color or Kahn's (result size == number of nodes). Cycle = inconsistent constraints.
</details>

---

**Drill 5:**
> Find all nodes in a DAG from which every path leads to a terminal node (no outgoing edges).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Reverse topological sort / Safe nodes (LC 802)
**Reason:** A node is "safe" if all paths from it eventually reach a terminal. Reverse the graph and run Kahn's from all terminals (in-degree 0 in reversed graph). All nodes processed in Kahn's are safe. LC 802.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Kahn's BFS topo sort | O(V+E) | O(V+E) | BFS from in-degree-0 nodes |
| DFS postorder topo sort | O(V+E) | O(V) | Push after all neighbors done |
| Alien Dictionary | O(C) where C = total chars | O(1) since ≤26 chars | |
| Min Height Trees (centroid) | O(n) | O(n) | Peel leaves repeatedly |
| Lexicographically smallest topo | O((V+E) log V) | O(V+E) | Min-heap instead of queue |

---

## 9. Common Follow-up Questions

1. What if there are multiple valid topological orders? (Any is valid unless problem requires lexicographically smallest — use min-heap)
2. Can topological sort be applied to undirected graphs? (No — topo sort is defined only for DAGs. Undirected graphs can have cycles and no notion of direction)
3. What is the relationship between topo sort and DFS finish times? (In DFS, nodes with later finish times come earlier in topo order — hence reverse postorder = topo order)
4. Can you find the critical path (longest path) using topo sort? (Yes — DP on topo order, dp[v] = max(dp[u] + weight) for all u→v edges)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Cycle Detection | Cycle = no valid topo order | 207. Course Schedule |
| DP on DAG | Longest path, counting paths | 329. Longest Increasing Path in Matrix |
| Min-Heap | Lexicographically smallest order | Alien Dictionary variant |
| SCC | Condense graph to DAG, then topo sort | Complex dependency analysis |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
