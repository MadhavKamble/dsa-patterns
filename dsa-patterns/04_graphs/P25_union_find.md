# Pattern 25: Union-Find (Disjoint Set Union)

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 200. Number of Islands (UF variant) | Medium | https://leetcode.com/problems/number-of-islands/ |
| 2 | 261. Graph Valid Tree | Medium | https://leetcode.com/problems/graph-valid-tree/ |
| 3 | 323. Number of Connected Components | Medium | https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/ |
| 4 | 399. Evaluate Division | Medium | https://leetcode.com/problems/evaluate-division/ |
| 5 | 547. Number of Provinces | Medium | https://leetcode.com/problems/number-of-provinces/ |
| 6 | 684. Redundant Connection | Medium | https://leetcode.com/problems/redundant-connection/ |
| 7 | 721. Accounts Merge | Medium | https://leetcode.com/problems/accounts-merge/ |
| 8 | 1202. Smallest String With Swaps | Medium | https://leetcode.com/problems/smallest-string-with-swaps/ |
| 9 | 1584. Min Cost to Connect All Points | Medium | https://leetcode.com/problems/min-cost-to-connect-all-points/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Union-Find (DSU)** efficiently answers two questions:
1. **Find**: which group does this element belong to? (returns the root/representative)
2. **Union**: merge two groups into one

**Two key optimizations:**
- **Path Compression** (`find`): make every node point directly to root after finding it → amortizes cost
- **Union by Rank**: always attach smaller tree under larger → keeps trees flat

With both, operations are nearly O(1) amortized — technically O(α(n)) where α is the inverse Ackermann function.

**Core operations:**
```
find(x): follow parent pointers to root; compress path
union(x, y): find roots; if different, merge (attach smaller rank under larger)
connected(x, y): find(x) == find(y)
```

### Visual Walkthrough
```
Initial: parent = [0,1,2,3,4] (each is its own root)

union(0, 1): find(0)=0, find(1)=1 → parent[1]=0
             parent = [0,0,2,3,4]

union(1, 2): find(1)→find(0)=0, find(2)=2 → parent[2]=0
             parent = [0,0,0,3,4]

union(3, 4): parent = [0,0,0,3,3]

find(2): 2→0 (compressed to point directly at root)
connected(1, 2): find(1)=0, find(2)=0 → true
connected(2, 4): find(2)=0, find(4)=3 → false

Path compression on find(2):
  Before: 2→0 (already direct, but in deeper tree: 3→1→0 becomes 3→0)
```

### When TO use this pattern
- Dynamic connectivity: incrementally add edges, query if two nodes are connected
- Count connected components as edges are added
- Detect cycle in undirected graph (union edge; if already same component → cycle)
- Group merging: accounts merge, friend circles
- Minimum spanning tree (Kruskal's algorithm)
- "Can we connect everything?" questions

### When NOT to use this pattern
- Need to delete edges (UF doesn't support un-union)
- Directed graphs (UF is for undirected relationships)
- Need actual path (not just connectivity)
- Need to know the full component membership list quickly (use DFS/BFS or maintain sets alongside)

### Common Beginner Mistakes
- **Path compression in `find`**: must return the root, not just update parent
- **Union by rank**: track rank per root; only increment rank when two equal-rank trees merge
- **1-indexed vs 0-indexed**: be consistent with array initialization
- **Accounts Merge**: union emails (as strings with hash map), then group by root

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "connect", "group", "merge", "same component", "redundant edge", "friends circle" |
| Core Idea | `find` with path compression + `union` by rank; near-O(1) per operation |
| Trigger Keywords | "connected components", "merge groups", "redundant connection", "accounts merge" |
| Avoid When | Directed graphs, need to delete connections, need actual path |
| Time Complexity | O(α(n)) per operation — effectively O(1) |
| Space Complexity | O(n) |

**Gotchas:**
- Path compression: `parent[x] = find(parent[x])` — recursive or iterative
- Union by rank: compare ranks; merge smaller-rank under larger
- Count components: start with n components, decrement by 1 on each successful union
- Cycle detection: if find(u) == find(v) before union → edge (u,v) creates cycle

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"connected components"` → UF or DFS
- `"redundant connection"` → UF: first edge that connects already-connected nodes
- `"accounts merge"` → UF: merge emails by account; group by root
- `"smallest string with swaps"` → UF: group swappable indices; sort each group
- `"min cost to connect all points"` → Kruskal's = UF + sort edges
- `"friend circles"`, `"provinces"` → UF or DFS on adjacency matrix

---

## 4. C++ Template

```cpp
/*
 * Pattern: Union-Find (DSU)
 * Time: O(α(n)) per op — effectively O(1) | Space: O(n)
 */

struct DSU {
    vector<int> parent, rank_;

    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);  // path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;  // already same component
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
};

// USAGE: count components
int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    int components = n;
    for (auto& e : edges)
        if (dsu.unite(e[0], e[1])) components--;
    return components;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll use Union-Find. It supports two operations in nearly constant time: `find` returns the representative (root) of a node's group, and `union` merges two groups. I use path compression in `find` — making every node point directly to the root — and union by rank — always attaching the smaller tree under the larger. These two optimizations together give amortized O(α(n)) per operation, which is effectively constant time."

### Interview Flow Checklist
- [ ] Initialize `parent[i] = i`, `rank[i] = 0`
- [ ] `find(x)`: recursive with path compression
- [ ] `unite(x, y)`: find roots, check if same (cycle/connected), merge by rank
- [ ] Count components: start with n, decrement per successful union
- [ ] Handle edge cases (self-loops, disconnected graph)

---

## 6. Problems

---

### Problem 1: 684. Redundant Connection
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/redundant-connection/
**Why this pattern fits:** First edge that unions already-connected nodes

**Optimal C++ Solution:**
```cpp
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    DSU dsu(n + 1);
    for (auto& e : edges)
        if (!dsu.unite(e[0], e[1])) return e;  // already connected → redundant
    return {};
}
```
**Edge Cases:** [ ] Self-loop, [ ] Multiple redundant edges (return last one)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 323. Number of Connected Components
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
**Optimal C++ Solution:**
```cpp
int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    int components = n;
    for (auto& e : edges)
        if (dsu.unite(e[0], e[1])) components--;
    return components;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 721. Accounts Merge
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/accounts-merge/
**Why this pattern fits:** Union emails within same account; group by root email → merge accounts

**Optimal C++ Solution:**
```cpp
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, string> parent;  // email → root email
    unordered_map<string, string> owner;   // email → account name

    function<string(string)> find = [&](string x) -> string {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    auto unite = [&](string x, string y) {
        string px = find(x), py = find(y);
        if (px != py) parent[px] = py;
    };

    for (auto& acc : accounts) {
        string name = acc[0];
        for (int i = 1; i < (int)acc.size(); i++) {
            if (!parent.count(acc[i])) parent[acc[i]] = acc[i];
            owner[acc[i]] = name;
            if (i > 1) unite(acc[1], acc[i]);
        }
    }

    unordered_map<string, set<string>> groups;
    for (auto& [email, _] : parent)
        groups[find(email)].insert(email);

    vector<vector<string>> result;
    for (auto& [root, emails] : groups) {
        vector<string> merged = {owner[root]};
        merged.insert(merged.end(), emails.begin(), emails.end());
        result.push_back(merged);
    }
    return result;
}
```
**Edge Cases:** [ ] Single email per account, [ ] All accounts same person

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 1202. Smallest String With Swaps
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/smallest-string-with-swaps/
**Why this pattern fits:** Characters at swap-connected indices can be rearranged among themselves → sort each component

**Optimal C++ Solution:**
```cpp
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    int n = s.size();
    DSU dsu(n);
    for (auto& p : pairs) dsu.unite(p[0], p[1]);

    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < n; i++) groups[dsu.find(i)].push_back(i);

    for (auto& [root, indices] : groups) {
        string chars;
        for (int i : indices) chars += s[i];
        sort(chars.begin(), chars.end());
        sort(indices.begin(), indices.end());
        for (int i = 0; i < (int)indices.size(); i++)
            s[indices[i]] = chars[i];
    }
    return s;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 1584. Min Cost to Connect All Points (Kruskal's)
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/min-cost-to-connect-all-points/
**Why this pattern fits:** Minimum Spanning Tree via Kruskal = sort edges + Union-Find

**Optimal C++ Solution:**
```cpp
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    vector<tuple<int,int,int>> edges;  // (dist, i, j)
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            int d = abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]);
            edges.push_back({d, i, j});
        }
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int cost = 0, edges_used = 0;
    for (auto& [d, u, v] : edges) {
        if (dsu.unite(u, v)) {
            cost += d;
            if (++edges_used == n-1) break;
        }
    }
    return cost;
}
```
**Complexity Analysis:**
- Time: O(n² log n) — O(n²) edges sorted
- Space: O(n²)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a social network. Users can follow others. At each query, determine if user A can reach user B through follows (even indirectly). Handle dynamic follow additions.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Union-Find (undirected) or online DFS
**Reason:** If "follow" is bidirectional (mutual friendship), Union-Find directly works: union when friends, query connected(A, B). If directed (A follows B ≠ B follows A), Union-Find won't work — need reachability in directed graph (different problem).
</details>

---

**Drill 2:**
> Given a grid that starts fully connected. Cells are destroyed one by one. After each destruction, report the number of connected components.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Offline reverse Union-Find
**Reason:** Process destructions in reverse (treat as additions). Start with empty grid, add cells in reverse destruction order. Use Union-Find to count components. Each addition may merge with adjacent already-added cells. Classic "reverse operations" trick.
</details>

---

**Drill 3:**
> You have labeled containers and pipes connecting them. A liquid can flow through pipes between containers of the same label. Count how many distinct groups of same-label containers are interconnected.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Union-Find with label filtering
**Reason:** Process each pipe: if both endpoints have the same label, union them. Count distinct roots among all containers. Containers with different labels are never unioned even if connected by a pipe.
</details>

---

**Drill 4:**
> In a weighted graph, find the maximum edge weight you can include in a spanning tree such that all nodes remain connected.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Kruskal's MST (Union-Find)
**Reason:** The maximum edge in the MST is the answer. Kruskal's adds edges in sorted order; the last edge added to complete the MST (connecting the final two components) is the maximum bottleneck. Binary search on edge weight + UF connectivity check also works.
</details>

---

**Drill 5:**
> Given n cities and road plans, find the minimum roads to build so all cities are reachable from city 0 (some roads already exist).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Union-Find + count components
**Reason:** Add existing roads using union. Count components C reachable from city 0 that aren't yet connected (components - 1). Need to add C-1 roads (a spanning tree on the components). More precisely: count distinct components = k; need k-1 roads to connect them all.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Notes |
|-----------|------|-------|
| find (with path compression) | O(α(n)) ≈ O(1) | Amortized |
| union (with rank) | O(α(n)) ≈ O(1) | Amortized |
| n operations total | O(n · α(n)) | Nearly O(n) |
| Kruskal's MST | O(E log E) | Sorting dominates |
| Accounts Merge | O(n α(n)) | n = total emails |

---

## 9. Common Follow-up Questions

1. Can Union-Find handle deletions? (Not natively — it's designed for union-only. For dynamic connectivity with deletions, need link-cut trees or offline processing)
2. What if you need the actual list of component members? (Maintain a map from root to list of members; on union, merge smaller list into larger — "small-to-large" merging)
3. How to find the size of a component? (Maintain `size[]` array; on union, update size[new_root] += size[old_root])
4. Weighted Union-Find for ratios? (399. Evaluate Division: track weight from node to root; find returns (root, cumulative_product). Union weights accordingly)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Sorting (Kruskal) | MST: sort edges, union greedily | 1584. Min Cost Connect Points |
| DFS | Alternative for static connected components | 200. Number of Islands |
| Graph Cycle Detection | Undirected: same component edge = cycle | 684. Redundant Connection |
| Offline Reverse Processing | Deletions → reverse additions + UF | Percolation problems |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
