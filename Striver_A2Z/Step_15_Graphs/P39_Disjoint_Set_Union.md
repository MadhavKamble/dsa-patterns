# Disjoint Set Union (DSU) / Union-Find

> **Concept + Implementation** · **Step 15 — Graphs · P39**

---

## What Problem Does DSU Solve?

Given a set of elements, DSU answers two questions in near-constant time:
1. **Find:** Are two elements in the same group (connected component)?
2. **Union:** Merge two groups into one.

**Without DSU:** Checking if two nodes are connected requires BFS/DFS → O(V+E) per query.
**With DSU:** Both operations take O(α(N)) ≈ O(1) amortized (α = inverse Ackermann function, practically ≤ 4 for any realistic N).

**Use cases:**
- Kruskal's MST (cycle detection)
- Dynamic connectivity queries
- Number of connected components
- Detecting redundant edges

---

## Core Idea — Forest of Trees

DSU represents each group as a **tree**. Each node points to its parent. The **root** of the tree is the group representative (ultimate parent).

```
Initial state (each node is its own parent = own group):
  1→1  2→2  3→3  4→4  5→5

After union(1,2) and union(2,3):
  1←2←3   (or 1 as root with 2,3 as children)
  parent: [_,1,1,2,4,5]  (2's parent=1, 3's parent=2)

Finding group of 3: 3→2→1 → root is 1
Finding group of 1: 1→1 → root is 1
Same group? Yes ✓
```

**Two optimizations make this fast:**
1. **Path Compression** — flatten the tree during `find`
2. **Union by Rank/Size** — keep trees shallow during `union`

---

## Optimization 1 — Path Compression

**Problem:** Without optimization, finding the root of a deep chain 1←2←3←4←5 takes O(N).

**Solution:** While traversing to the root, make every node point **directly to the root**.

```cpp
int findUPar(int node) {
    if (node == parent[node])
        return node;
    return parent[node] = findUPar(parent[node]);  // ← path compression
}
```

```
Before findUPar(5):        After findUPar(5):
  1←2←3←4←5               1←2
                             ↑ ↑
                             3 4
                              ↑
                              5
All nodes now point directly (or closer) to root → future finds are faster.
```

---

## Optimization 2a — Union by Rank

**Problem:** If we always attach one tree under the other arbitrarily, we can get a chain (depth O(N)).

**Solution:** Attach the **smaller-rank tree** under the **larger-rank tree** to keep depth minimal.

**Rank = upper bound on tree height** (not exact height after path compression):
- Initially: `rank[i] = 0` for all nodes
- When merging two trees of equal rank: attach one under the other, increment root's rank by 1
- When ranks differ: attach the smaller-rank root under larger-rank root (no rank change)

```
rank[A]=1, rank[B]=0: attach B under A (larger rank wins)
rank[A]=1, rank[B]=1: attach B under A, rank[A] becomes 2

Rule: smaller rank → child. Equal rank → either becomes child, winner's rank++.
```

```cpp
void unionByRank(int u, int v) {
    int ulp_u = findUPar(u);
    int ulp_v = findUPar(v);
    if (ulp_u == ulp_v) return;          // already same group
    if (rank[ulp_u] < rank[ulp_v]) {
        parent[ulp_u] = ulp_v;           // u's root goes under v's root
    } else if (rank[ulp_v] < rank[ulp_u]) {
        parent[ulp_v] = ulp_u;           // v's root goes under u's root
    } else {
        parent[ulp_v] = ulp_u;           // tie: pick either, increment winner
        rank[ulp_u]++;
    }
}
```

---

## Optimization 2b — Union by Size

**Problem:** Rank is an approximation — path compression makes it inaccurate as a height measure.

**Solution:** Track the **actual size** (number of nodes) of each tree. Attach the smaller tree under the larger tree. Update size of the new root.

```cpp
void unionBySize(int u, int v) {
    int ulp_u = findUPar(u);
    int ulp_v = findUPar(v);
    if (ulp_u == ulp_v) return;
    if (size[ulp_u] < size[ulp_v]) {
        parent[ulp_u] = ulp_v;
        size[ulp_v] += size[ulp_u];      // add smaller size to larger
    } else {
        parent[ulp_v] = ulp_u;
        size[ulp_u] += size[ulp_v];      // covers both equal and larger case
    }
}
```

**Note:** No `size++` for equal case — just always attach smaller under larger (or either when equal), and add sizes together.

---

## Complete Implementation — Union by Rank

```cpp
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n+1,0);
        parent.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
        }
    }

    int findUPar(int node) {
        if(node==parent[node])
            return node;
        return parent[node]=findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u=findUPar(u);
        int ulp_v=findUPar(v);
        if(ulp_u==ulp_v) return;
        if(rank[ulp_u]<rank[ulp_v]){
            parent[ulp_u]=ulp_v;
        }else if(rank[ulp_v]<rank[ulp_u]){
            parent[ulp_v]=ulp_u;
        }else{
            parent[ulp_v]=ulp_u;
            rank[ulp_u]++;
        }
    }
};

int main() {
    DisjointSet ds(7);
    ds.unionByRank(1,2);
    ds.unionByRank(2,3);
    ds.unionByRank(4,5);
    ds.unionByRank(6,7);
    ds.unionByRank(5,6);
    if(ds.findUPar(3)==ds.findUPar(7)) cout<<"Same\n";
    else cout<<"Not same\n";      // prints: Not same

    ds.unionByRank(3,7);
    if(ds.findUPar(3)==ds.findUPar(7)) cout<<"Same\n";
    else cout<<"Not same\n";      // prints: Same
    return 0;
}
```

---

## Complete Implementation — Union by Size

```cpp
#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n+1,0);
        parent.resize(n+1);
        size.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
            size[i]=1;
        }
    }

    int findUPar(int node) {
        if(node==parent[node])
            return node;
        return parent[node]=findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u=findUPar(u);
        int ulp_v=findUPar(v);
        if(ulp_u==ulp_v) return;
        if(rank[ulp_u]<rank[ulp_v]){
            parent[ulp_u]=ulp_v;
        }else if(rank[ulp_v]<rank[ulp_u]){
            parent[ulp_v]=ulp_u;
        }else{
            parent[ulp_v]=ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u=findUPar(u);
        int ulp_v=findUPar(v);
        if(ulp_u==ulp_v) return;
        if(size[ulp_u]<size[ulp_v]){
            parent[ulp_u]=ulp_v;
            size[ulp_v]+=size[ulp_u];
        }else{
            parent[ulp_v]=ulp_u;
            size[ulp_u]+=size[ulp_v];
        }
    }
};
```

---

## Dry Run — `unionByRank(1,2)` through `unionByRank(3,7)`

**Initial state (n=7):**
```
parent: [0,1,2,3,4,5,6,7]
rank:   [0,0,0,0,0,0,0,0]
```

**unionByRank(1,2):** findUPar(1)=1, findUPar(2)=2. rank equal → parent[2]=1, rank[1]=1
```
parent: [_,1,1,3,4,5,6,7]   rank: [_,1,0,0,0,0,0,0]
Tree: 1←2
```

**unionByRank(2,3):** findUPar(2)=1 (via path compress), findUPar(3)=3. rank[1]=1 > rank[3]=0 → parent[3]=1
```
parent: [_,1,1,1,4,5,6,7]   rank: [_,1,0,0,0,0,0,0]
Tree: 1←2, 1←3
```

**unionByRank(4,5):** findUPar(4)=4, findUPar(5)=5. Equal → parent[5]=4, rank[4]=1
```
parent: [_,1,1,1,4,4,6,7]   rank: [_,1,0,0,1,0,0,0]
Tree: 4←5
```

**unionByRank(6,7):** Equal → parent[7]=6, rank[6]=1
```
parent: [_,1,1,1,4,4,6,6]   rank: [_,1,0,0,1,0,1,0]
Tree: 6←7
```

**unionByRank(5,6):** findUPar(5)=4, findUPar(6)=6. rank[4]=1 == rank[6]=1 → parent[6]=4, rank[4]=2
```
parent: [_,1,1,1,4,4,4,6]   rank: [_,1,0,0,2,0,1,0]
Tree: 4←5, 4←6←7
```

**findUPar(3)==findUPar(7)?** findUPar(3)=1, findUPar(7)=4 → **Not same** ✓

**unionByRank(3,7):** findUPar(3)=1, findUPar(7)=4. rank[1]=1 < rank[4]=2 → parent[1]=4
```
parent: [_,4,1,1,4,4,4,6]   rank: [_,1,0,0,2,0,1,0]
Tree: 4 is root of everything
```

**findUPar(3)==findUPar(7)?** findUPar(3)→1→4, findUPar(7)→6→4 → both 4 → **Same** ✓

---

## Rank vs Size — Which to Use?

| | Union by Rank | Union by Size |
|--|---------------|---------------|
| Tracks | Upper bound on height | Exact node count |
| After path compression | Rank may be inaccurate (but still works) | Size remains accurate |
| Equal case | Attach either, increment rank | Attach either, add sizes |
| Preferred in | Most competitive programming | When size of component needed |
| Both give | O(α(N)) amortized time | O(α(N)) amortized time |

> **In practice:** Use `unionBySize` when you need to query component sizes later (e.g., "how many nodes in the same group?"). Use `unionByRank` when you only need connectivity queries.

---

## Time Complexity

| Operation | Naive (no optimization) | Path compression only | Rank/Size only | Both |
|-----------|------------------------|----------------------|----------------|------|
| find | O(N) | O(log N) amortized | O(log N) | **O(α(N)) ≈ O(1)** |
| union | O(N) | O(log N) amortized | O(log N) | **O(α(N)) ≈ O(1)** |

α(N) = inverse Ackermann function. For any N ≤ 10^600 (more than atoms in universe), α(N) ≤ 4. Effectively constant.

---

## How DSU Detects Cycles (used in Kruskal's)

```
For each edge (u, v):
  if findUPar(u) == findUPar(v):
      → u and v are already in the same component
      → adding this edge creates a CYCLE → skip it
  else:
      → safe to add this edge → union(u, v)

This is Kruskal's core: sort edges by weight, add if no cycle (different roots).
```

---

## Interview Explanation Script

> "DSU maintains a forest of trees where each tree = one connected component. `findUPar` finds the root (representative) of a node's component with path compression — making every node on the path point directly to the root, flattening future lookups."

> "Union by rank attaches the shallower tree under the deeper one, preventing the forest from degenerating into a chain. Together, path compression + union by rank gives O(α(N)) ≈ O(1) per operation."

> "Cycle detection: if two nodes share the same root before a union, adding an edge between them would create a cycle."

---

## Recall Line *(10-Second Revision)*

> "DSU: parent[i]=i init. findUPar = recursive + path compress. Union: find roots, attach smaller rank/size under larger. O(α(N))."

---

## Short Revision Notes

- `parent[i]=i` and `rank[i]=0`, `size[i]=1` for all i
- `findUPar`: base case `node==parent[node]`, recursive path compression via `parent[node]=findUPar(parent[node])`
- Always find roots (`ulp_u`, `ulp_v`) before comparing/unioning
- `ulp_u == ulp_v` → same component → return early (no union needed)
- Rank: equal → attach v's root under u's root, `rank[u]++`
- Size: always add smaller size into larger; update winner's size
- DSU indices are 1-based here (`resize(n+1)`) — adjust for 0-based problems

---

## Pattern Recognition Trigger

**When I see:**
- "Are these two nodes connected?" (repeated queries)
- "Add edges dynamically, check connectivity"
- "Number of connected components"
- "Detect cycle in undirected graph (Kruskal's)"

**I should think of:** DSU with path compression + union by rank/size

---

## Common Mistakes

❌ Comparing nodes directly (`u == v`) instead of their roots (`findUPar(u) == findUPar(v)`)
❌ Updating parent of node instead of root: `parent[u] = v` should be `parent[ulp_u] = ulp_v`
❌ Forgetting path compression in `findUPar` → O(N) find instead of O(1)
❌ In `unionBySize`: forgetting to update `size[winner] += size[loser]` → sizes become wrong
❌ 0-indexed problems with `resize(n+1)` DSU — off-by-one on node indices

---

## Related Problems

- [ ] Striver Step 15 P40 — Kruskal's Algorithm (uses DSU for cycle detection)
- [ ] LeetCode #547 — Number of Provinces (DSU or DFS)
- [ ] LeetCode #684 — Redundant Connection (DSU cycle detection)
- [ ] LeetCode #1319 — Number of Operations to Make Network Connected

---

## Pattern Category

`DSU` · `Union-Find` · `Connected Components` · `Cycle Detection` · `MST`

---

## 30-Second Last-Minute Revision

> **DSU:** `parent[i]=i`, `rank[i]=0`, `size[i]=1`.
> `findUPar(node)`: if `node==parent[node]` → return node. Else `parent[node]=findUPar(parent[node])`.
> `unionByRank`: find roots. Smaller rank → child. Tie: either child, root rank++.
> `unionBySize`: find roots. Smaller size → child. Winner `size += loser size`.
> **Cycle?** `findUPar(u)==findUPar(v)` before union → cycle exists.
> **Time:** O(α(N)) ≈ O(1) per operation.
