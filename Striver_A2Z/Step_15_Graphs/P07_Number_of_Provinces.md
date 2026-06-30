# Number of Provinces

> **LeetCode #547** · **Difficulty:** Medium · **Step 15 — Graphs · P07**

---

## Problem Understanding

**What is it asking?**
Given an `n x n` matrix `isConnected` where `isConnected[i][j] = 1` if cities `i` and `j` are directly connected (and `0` otherwise), return the **number of provinces** (connected components / groups of directly or indirectly connected cities).

**Input:** `isConnected` — adjacency matrix (n×n), symmetric, `isConnected[i][i] = 1`
**Output:** Integer — number of provinces

**Example:**
```
isConnected = [[1,1,0],
               [1,1,0],
               [0,0,1]]

City 0 — City 1 (connected)
City 2 (isolated)

Provinces: {0,1} and {2} → answer = 2
```

**Key Observations:**
- "Province" = connected component in the graph
- The input is an **adjacency matrix**, not adjacency list — convert or traverse directly
- Each unvisited city starts a new province → run DFS/BFS from it, count how many times we start fresh
- Self-loops (`isConnected[i][i] = 1`) don't matter — skip same-index neighbors

---

## Optimal Approach — DFS / BFS on Adjacency Matrix

### Key Observation

> Every time we start DFS from an unvisited city, we've found a new province. DFS marks all cities in that province as visited. Count the number of DFS calls from the outer loop.

### Algorithm
1. Initialize `visited[0..n-1] = false`, `provinces = 0`
2. For each city `i` from `0` to `n-1`:
   - If `!visited[i]`:
     - `provinces++`
     - DFS from `i` — marks all cities in the same province visited
3. Return `provinces`

### DFS Inner Logic
- For city `node`, iterate through all cities `j` from `0` to `n-1`
- If `isConnected[node][j] == 1` AND `!visited[j]`:
  - Mark `visited[j] = true`, recurse `dfs(j)`

### Dry Run

**Input:**
```
isConnected = [[1,1,0],
               [1,1,0],
               [0,0,1]]
```

| Step | i | visited | provinces | DFS visits |
|------|---|---------|-----------|------------|
| i=0 | 0 | {0,1} | 1 | 0 → neighbor 1 → no more |
| i=1 | 1 | already visited | — | — |
| i=2 | 2 | {0,1,2} | 2 | 2 → no unvisited neighbors |

**Output:** `2` ✅

**Second Example:**
```
isConnected = [[1,0,0],
               [0,1,0],
               [0,0,1]]
→ 3 provinces (all isolated)
```

### Complexity
- **Time:** O(n²) — for each of n cities, we scan all n columns in the adjacency matrix
- **Space:** O(n) — visited array + recursion stack (at most n deep)

---

## Clean C++ Interview Code

```cpp
class Solution {
    void dfs(int node, vector<vector<int>>& isConnected, vector<bool>& visited) {
        visited[node]=true;
        for(int j=0;j<isConnected.size();j++){
            if(isConnected[node][j]==1 && !visited[j]){
                dfs(j,isConnected,visited);
            }
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size();
        vector<bool> visited(n,false);
        int provinces=0;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                provinces++;
                dfs(i,isConnected,visited);
            }
        }
        return provinces;
    }
};
```

### BFS Variant

```cpp
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size();
        vector<bool> visited(n,false);
        int provinces=0;
        for(int i=0;i<n;i++){
            if(!visited[i]){
                provinces++;
                queue<int> q;
                visited[i]=true;
                q.push(i);
                while(!q.empty()){
                    int node=q.front(); q.pop();
                    for(int j=0;j<n;j++){
                        if(isConnected[node][j]==1 && !visited[j]){
                            visited[j]=true;
                            q.push(j);
                        }
                    }
                }
            }
        }
        return provinces;
    }
};
```

### Union-Find Variant

```cpp
class DisjointSet {
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n);
        for(int i=0;i<n;i++){
            parent[i]=i;
            size[i]=1;
        }
    }
    int findUPar(int node) {
        if(node==parent[node])
            return node;
        return parent[node]=findUPar(parent[node]);
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

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n=isConnected.size();
        DisjointSet ds(n);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(isConnected[i][j]==1){
                    ds.unionBySize(i,j);
                }
            }
        }
        int provinces=0;
        for(int i=0;i<n;i++){
            if(ds.findUPar(i)==i) provinces++;
        }
        return provinces;
    }
};
```

> Nodes are 0-indexed here — `resize(n)` not `resize(n+1)`.
> Count provinces: after all unions, nodes whose `findUPar(i)==i` are roots — one root per province.

---

## Interview Explanation Script

> "The problem reduces to counting connected components in a graph. I use DFS: for each unvisited city, I increment the province count and run DFS to mark all cities reachable from it as visited. The adjacency matrix lets me check connections directly in O(n) per node."

> "The key insight is: every DFS launch from the outer loop = a new province. DFS ensures we visit the entire component before moving on."

> "Three valid approaches: DFS, BFS, or Union-Find. DFS/BFS are O(n²) time, same as iterating the matrix. Union-Find is also O(n²) since we still scan all edges."

---

## Recall Line *(10-Second Revision)*

> "Provinces = connected components. Outer loop + DFS. Count DFS launches. O(n²)."

---

## Short Revision Notes

- Input is adjacency **matrix** (n×n) — iterate over columns instead of adjacency list
- `isConnected[i][i] = 1` always — skip self-loops (or they're harmlessly caught by `visited`)
- Province count = number of times the outer for-loop triggers a DFS
- Equivalent problems: friend circles, number of islands (on grid), connected components
- Union-Find is also applicable — each `isConnected[i][j]=1` is a `union(i,j)` call

---

## Pattern Recognition Trigger

**When I see:**
- "Number of groups / clusters / provinces / friend circles"
- "How many connected components"
- "Indirectly connected" cities/nodes

**I should think of:** DFS/BFS with outer loop to count components, or Union-Find

---

## Common Mistakes

❌ Not using an outer loop — only runs DFS from node 0 → misses other components
❌ Treating `isConnected[i][i] = 1` as a connection to self → causes re-visit (harmless if visited check is correct, but confusing)
❌ Counting edges instead of components
❌ Using adjacency list conversion when direct matrix traversal is simpler here

---

## What Interviewer Is Testing

- **Graph fundamentals:** Recognizing "connected component counting" pattern
- **Adjacency matrix traversal:** Iterating columns instead of an adj list
- **Multiple approaches:** DFS, BFS, Union-Find — and knowing tradeoffs

---

## Approach Comparison

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| DFS (recursive) | O(n²) | O(n) | Simplest code |
| BFS | O(n²) | O(n) | Same complexity, iterative |
| Union-Find | O(n² · α(n)) | O(n) | Best for dynamic connectivity queries |

---

## Related Problems

- [ ] LeetCode #200 — Number of Islands (same pattern on 2D grid)
- [ ] LeetCode #323 — Number of Connected Components in Undirected Graph
- [ ] LeetCode #684 — Redundant Connection (Union-Find)
- [ ] LeetCode #1319 — Number of Operations to Make Network Connected
- [ ] Striver Step 15 P06 — DFS

---

## Pattern Category

`Graphs` · `DFS` · `BFS` · `Connected Components` · `Union-Find`

---

## Difficulty Analysis

**Rating:** Medium (easy if you recognize the "count connected components" pattern)

**Why challenging:** Input is an adjacency matrix (not list) — easy to miss iterating all n columns. Also requires recognizing that "province" = connected component.

---

## 30-Second Last-Minute Revision

> **Number of Provinces = connected components.**
> Outer `for` loop over all cities. If unvisited → `provinces++` → DFS to mark component.
> DFS: iterate all columns `j`, recurse if `isConnected[node][j]==1 && !visited[j]`.
> **Time:** O(n²) | **Space:** O(n)
