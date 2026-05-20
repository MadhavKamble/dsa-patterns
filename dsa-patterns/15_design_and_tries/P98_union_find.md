# P98 — Union Find (Disjoint Set Union)

## 1. First-Timer Explanation

### What Is It?
**Union Find** (also called Disjoint Set Union, DSU) is a data structure that tracks a partition of elements into disjoint sets. It supports two operations: `find` (which set does element x belong to?) and `union` (merge the sets containing x and y). With path compression and union by rank, both operations run in near-O(1) amortized time.

### The Core Insight
```
Think of it as a forest of trees:
  - Each set is a tree; the root is the "representative" of the set
  - find(x): walk up to the root; path compress so x points directly to root
  - union(x,y): attach one root as child of the other (by rank/size)

Without optimizations: O(n) per operation (degenerate chain)
With path compression alone: O(log n) amortized
With union by rank alone: O(log n) worst case
With BOTH: O(α(n)) ≈ O(1) amortized (inverse Ackermann — essentially constant)
```

### Visual Walkthrough
```
Elements: 0 1 2 3 4   (initially each is its own set)
parent:  [0,1,2,3,4]  rank: [0,0,0,0,0]

union(0,1): rank equal → attach 1 under 0 → parent[1]=0
union(2,3): rank equal → attach 3 under 2 → parent[3]=2
union(0,2): rank equal → attach 2 under 0 → parent[2]=0, rank[0]=1

Tree:    0
        /|\
       1  2
          |
          3

find(3): 3→2→0. Path compress: parent[3]=0, parent[2]=0.
After:   0
        /|\ \
       1  2  3
```

### Path Compression vs Union by Rank
```
Path Compression (halving):
  find(x): while parent[x] != x, parent[x]=parent[parent[x]], x=parent[x]
  → flatten tree during find so future finds are faster

Union by Rank:
  if rank[a] < rank[b]: parent[a]=b (attach smaller under larger)
  if rank[a] > rank[b]: parent[b]=a
  if rank[a] == rank[b]: parent[b]=a, rank[a]++ (rank increases only when equal)

Size-based union (alternative):
  Always attach smaller set under larger set; track size[] instead of rank[]
```

### When to Use
- "Number of connected components" → DSU or BFS/DFS
- "Are these two elements connected?" → DSU with O(α) vs BFS O(V+E)
- "Minimum spanning tree" → Kruskal's with DSU
- "Detect cycle in undirected graph" → DSU (if find(u)==find(v) before union, cycle exists)
- "Dynamic connectivity" → DSU (offline queries sorted by time)
- "Groups that merge over time" → DSU (online union queries)

### When NOT to Use
- Directed graphs (DSU doesn't track direction)
- You need to split a set (DSU only merges, never splits — use link-cut trees for that)
- Online dynamic graph problems where edges are also deleted (DSU is union-only)

---

## 2. Revision Card

**Recognition Signal:** "connected components", "union two groups", "cycle detection in undirected graph", "minimum spanning tree"

**Core Idea:** Forest of trees where each root is a group representative. `find` follows parent pointers to root with path compression. `union` attaches smaller tree under larger. Nearly O(1) per operation.

**Trigger Keywords:** connected components, union, merge groups, cycle, Kruskal, minimum spanning tree, provinces, friends, accounts

**Complexity:** O(α(n)) per operation amortized ≈ O(1). Build: O(n). Space: O(n).

---

## 3. Interview Tell Signs

- "Number of provinces/islands/connected components" → DSU or BFS
- "Redundant connection (cycle in undirected graph)" → DSU: if same component, it's redundant
- "Accounts merge (merge lists with common elements)" → DSU on elements
- "Minimum cost to connect all nodes" → Kruskal's MST with DSU
- "Satisfiability of equality equations" → DSU on variables
- "Find if path exists in graph" → DSU (static graph)
- "Number of operations to connect all" → count components = n - num_unions_that_succeeded

---

## 4. C++ Template

```cpp
#include <vector>
#include <numeric>
using namespace std;

// ── Basic DSU ─────────────────────────────────────────────────────────────────
struct DSU {
    vector<int> parent, rank_;
    int components;

    DSU(int n) : parent(n), rank_(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // path halving (compression)
            x = parent[x];
        }
        return x;
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false; // already connected
        if (rank_[x] < rank_[y]) swap(x, y);
        parent[y] = x;
        if (rank_[x] == rank_[y]) rank_[x]++;
        components--;
        return true;
    }

    bool connected(int x, int y) { return find(x) == find(y); }
};

// ── DSU with Size ─────────────────────────────────────────────────────────────
struct DSUSize {
    vector<int> parent, size_;

    DSUSize(int n) : parent(n), size_(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]); // full path compression
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (size_[x] < size_[y]) swap(x, y);
        parent[y] = x; size_[x] += size_[y];
        return true;
    }

    int getSize(int x) { return size_[find(x)]; }
};

// ── Kruskal's MST ─────────────────────────────────────────────────────────────
int kruskalMST(int n, vector<vector<int>>& edges) {
    // edges[i] = {weight, u, v}
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int cost = 0, edgesUsed = 0;
    for (auto& e : edges) {
        if (dsu.unite(e[1], e[2])) {
            cost += e[0];
            if (++edgesUsed == n - 1) break;
        }
    }
    return edgesUsed == n - 1 ? cost : -1; // -1 if not fully connected
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I'll use Union-Find. Each node starts as its own parent. `find` follows parent pointers to the root, with path halving to flatten the tree. `union` attaches the lower-rank root under the higher-rank one, or increments rank when they're equal. This gives near-O(1) per operation. For cycle detection: if two nodes share the same root before we union them, adding that edge creates a cycle."

**Checklist:**
- [ ] Initialize `parent[i] = i` for all i (iota or loop)
- [ ] Path compression in `find` (at minimum path halving: `parent[x] = parent[parent[x]]`)
- [ ] Union by rank/size: don't always attach x under y — check which is larger
- [ ] Track `components` counter: decrement only when `find(x) != find(y)`
- [ ] Kruskal's: sort edges by weight, try to unite, add cost only when `unite` returns true
- [ ] Check if MST is complete: need exactly n-1 edges used

---

## 6. Problems

### Problem 1: Number of Connected Components in an Undirected Graph
**Difficulty:** Medium | **LC:** 323

```cpp
int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    for (auto& e : edges) dsu.unite(e[0], e[1]);
    return dsu.components;
}
// Time: O(E * α(N)) | Space: O(N)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Redundant Connection
**Difficulty:** Medium | **LC:** 684

```cpp
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    DSU dsu(n + 1);
    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) return e; // already connected → cycle
    }
    return {};
}
// Time: O(E * α(N)) | Space: O(N)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Number of Islands II (Dynamic)
**Difficulty:** Hard | **LC:** 305

```cpp
vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
    int total = m * n;
    DSU dsu(total);
    vector<bool> land(total, false);
    int count = 0;
    vector<int> res;
    int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

    for (auto& p : positions) {
        int r = p[0], c = p[1], id = r * n + c;
        if (!land[id]) {
            land[id] = true;
            count++;
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1], nid = nr * n + nc;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && land[nid])
                    if (dsu.unite(id, nid)) count--;
            }
        }
        res.push_back(count);
    }
    return res;
}
// Time: O(K * α(M*N)) | Space: O(M*N)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Accounts Merge
**Difficulty:** Medium | **LC:** 721

```cpp
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, int> emailToId;
    int n = accounts.size();
    DSU dsu(n);

    for (int i = 0; i < n; i++) {
        for (int j = 1; j < (int)accounts[i].size(); j++) {
            string& email = accounts[i][j];
            if (emailToId.count(email)) dsu.unite(i, emailToId[email]);
            else emailToId[email] = i;
        }
    }

    unordered_map<int, vector<string>> groups;
    for (auto& [email, id] : emailToId)
        groups[dsu.find(id)].push_back(email);

    vector<vector<string>> res;
    for (auto& [root, emails] : groups) {
        sort(emails.begin(), emails.end());
        emails.insert(emails.begin(), accounts[root][0]);
        res.push_back(emails);
    }
    return res;
}
// Time: O(E log E) for sorting | Space: O(E) where E = total emails
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Minimum Cost to Connect All Points (Kruskal's)
**Difficulty:** Medium | **LC:** 1584

```cpp
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) {
            int d = abs(points[i][0]-points[j][0]) + abs(points[i][1]-points[j][1]);
            edges.push_back({d, i, j});
        }
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int cost = 0, used = 0;
    for (auto& [d, u, v] : edges) {
        if (dsu.unite(u, v)) { cost += d; if (++used == n-1) break; }
    }
    return cost;
}
// Time: O(N² log N) | Space: O(N²)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Satisfiability of Equality Equations
**Difficulty:** Medium | **LC:** 990

```cpp
bool equationsPossible(vector<string>& equations) {
    DSU dsu(26);
    // First pass: process all == equations
    for (auto& eq : equations)
        if (eq[1] == '=') dsu.unite(eq[0]-'a', eq[3]-'a');
    // Second pass: check all != equations
    for (auto& eq : equations)
        if (eq[1] == '!' && dsu.connected(eq[0]-'a', eq[3]-'a'))
            return false;
    return true;
}
// Time: O(N * α(26)) = O(N) | Space: O(1) (fixed 26 nodes)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** DSU state: parent=[0,0,2,2,4], rank=[1,0,1,0,0]. Call unite(1,3). Trace the result.
<details><summary>Reveal</summary>
find(1): parent[1]=0, parent[0]=0 → root=0. find(3): parent[3]=2, parent[2]=2 → root=2. rank[0]=1 > rank[2]=1? No, they're equal. rank[0]=1 == rank[2]=1 → attach 2 under 0, rank[0]++. parent[2]=0, rank[0]=2. Final: parent=[0,0,0,2,4], rank=[2,0,1,0,0]. Components decremented.
</details>

**Drill 2:** Graph: nodes 0-4, edges (0,1),(1,2),(3,4),(2,3). How many components after all edges? Which edge closes the last component gap?
<details><summary>Reveal</summary>
Start: 5 components. unite(0,1): 4 components, {0,1},{2},{3},{4}. unite(1,2): 3 components, {0,1,2},{3},{4}. unite(3,4): 2 components, {0,1,2},{3,4}. unite(2,3): 1 component. The edge (2,3) merges the last two groups. Final: 1 component.
</details>

**Drill 3:** Kruskal's on: nodes {0,1,2}, edges with weights: (0,1,1),(1,2,2),(0,2,3). What edges are in the MST?
<details><summary>Reveal</summary>
Sort by weight: (0,1,1),(1,2,2),(0,2,3). Process (0,1,1): unite(0,1) → components={0,1},{2}. Cost=1. Process (1,2,2): unite(1,2) → components={0,1,2}. Cost=3. Used 2=n-1 edges. Stop. MST edges: (0,1) and (1,2). Total cost=3. Skip (0,2,3) since already connected.
</details>

**Drill 4:** Accounts merge: accounts=[["John","a@x","b@x"],["John","b@x","c@x"],["Mary","d@x"]]. Trace the DSU.
<details><summary>Reveal</summary>
n=3 accounts. Process account 0: emailToId[a@x]=0, emailToId[b@x]=0. Process account 1: email b@x → already mapped to id=0 → unite(1,0). email c@x → emailToId[c@x]=1. Process account 2: email d@x → emailToId[d@x]=2. DSU roots: find(0)=0 (or 1 depending on rank), find(1) → same as 0, find(2)=2. Groups: root=0→[a@x, b@x, c@x], root=2→[d@x]. Result: [["John","a@x","b@x","c@x"],["Mary","d@x"]] (emails sorted).
</details>

**Drill 5:** Equality equations: ["a==b","b!=c","b==c"]. Is it satisfiable?
<details><summary>Reveal</summary>
First pass (==): a==b → unite('a','b'). b==c → unite('b','c'). Now {a,b,c} are all connected. Second pass (!=): b!=c → check connected('b','c') → YES, they're connected. Return false. Not satisfiable because we forced b==c and b!=c simultaneously.
</details>

---

## 8. Complexity Cheatsheet

| Operation | With Path Compression + Union by Rank | Without Optimizations |
|-----------|---------------------------------------|----------------------|
| find | O(α(n)) ≈ O(1) amortized | O(n) worst case |
| unite | O(α(n)) ≈ O(1) amortized | O(n) worst case |
| connected | O(α(n)) ≈ O(1) amortized | O(n) worst case |
| Build n nodes | O(n) | O(n) |
| E operations | O(E * α(n)) | O(E * n) |

| Problem | Approach | Time | Space |
|---------|----------|------|-------|
| Connected components | DSU | O(E α(V)) | O(V) |
| Cycle detection (undirected) | DSU | O(E α(V)) | O(V) |
| Kruskal's MST | Sort + DSU | O(E log E) | O(V) |
| Number of Islands II | DSU | O(K α(M*N)) | O(M*N) |
| Accounts merge | DSU + sort | O(E log E) | O(E) |

---

## 9. Common Follow-up Questions

**Q: Path compression vs union by rank — which matters more?**
A: Both together achieve O(α(n)). Path compression alone gives O(log n) amortized. Union by rank alone gives O(log n) worst case. The combination achieves the near-constant inverse Ackermann bound. In practice, either alone is fast enough for most problems.

**Q: Can DSU handle weighted edges (for minimum spanning forest)?**
A: Yes — that's exactly Kruskal's algorithm. Sort all edges by weight, then greedily add edges that don't form a cycle (checked via DSU). Stop when you have n-1 edges. The result is the MST.

**Q: How to use DSU for grid problems (Number of Islands)?**
A: Map each cell (r,c) to id = r*cols + c. When a cell becomes land, check its 4 neighbors. If a neighbor is also land and in a different component, unite them and decrement island count.

**Q: What if you need to split a merged set?**
A: Standard DSU doesn't support splits. For offline queries (all splits known in advance), process in reverse order (splits become merges). For online splits, you need link-cut trees (O(log n) per operation).

---

## 10. Cross-Pattern Connections

- **P84 (Sweep Line / Graph):** Kruskal's MST relies on edge sorting (sweep by weight), then DSU for cycle detection
- **P55 (Graph BFS/DFS):** Both DSU and BFS/DFS solve connected components — DSU is faster for dense graphs or when queries arrive online
- **P56 (Topological Sort):** Handles directed graphs where DSU doesn't apply
- **P96 (Segment Tree):** Both DSU and segment tree are "range/group query" structures; segment tree for range aggregation, DSU for set membership
- **P85 (Array Advanced):** Floyd's cycle detection (directed, in-array) vs DSU cycle detection (undirected graphs)
