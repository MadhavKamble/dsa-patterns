# Number of Operations to Make Network Connected

> **LeetCode #1319** · **Difficulty:** Medium · **Step 15 — Graphs · P41**

---

## Problem Understanding

**What is it asking?**
Given `n` computers (0-indexed) and `connections[][]` (each `[u,v]` = cable between u and v), find the **minimum number of cable moves** needed to connect all computers. Return `-1` if impossible.

**Input:** `n`, `connections[][]`
**Output:** Minimum moves, or `-1`

**Example:**
```
n=4, connections=[[0,1],[0,2],[1,2]]

Current components: {0,1,2} and {3}
Extra edges: 0-1, 0-2, 1-2 form a triangle — one is redundant
Move one redundant edge to connect {3}

Output: 1
```

**Key Observations:**
- To connect k components you need exactly k-1 edge moves
- An edge move = take a redundant (extra) edge and reconnect a component
- Extra edge = edge where both endpoints are already in the same component
- Impossible condition: `connections.size() < n-1` (not enough edges for a spanning tree)
- If enough extra edges exist: answer = `components - 1`

---

## Core Insight

```
After processing all edges with DSU:

  extra edges   = edges that formed cycles (both endpoints same component)
  components    = number of distinct connected components

To connect all components: need (components - 1) cable moves.
Each move uses one extra edge.

If extra >= components-1 → answer = components-1
Else → -1

Early impossibility check:
  Minimum edges for n nodes to be fully connected = n-1
  If connections.size() < n-1 → no matter how we rearrange, impossible → -1
```

---

## Why the Final `-1` Branch Never Actually Triggers

```
Given connections.size() >= n-1 (passed the early check):

  Total edges = extra + (edges that built the spanning forest)
              = extra + (n - components)

  So: extra = connections.size() - (n - components)
            = connections.size() - n + components

  Since connections.size() >= n-1:
    extra >= (n-1) - n + components = components - 1

  → extra is ALWAYS >= components-1 when connections.size() >= n-1

The final `if(extra>=ans)` check is defensive — the `-1` at the end
is dead code given the early return guard. The early check is sufficient.
```

---

## Optimal Approach — DSU + Count Extra Edges

### Algorithm
1. If `connections.size() < n-1` → return `-1` immediately
2. DSU: for each edge `(u,v)`:
   - Same component → `extra++`
   - Different components → `unionBySize(u,v)`
3. Count components: `components` = number of roots (`parent[i]==i`)
4. Return `components - 1`

### Dry Run

**n=6, connections=[[0,1],[0,2],[0,3],[1,2],[1,3]]**

```
Check: 5 connections >= n-1=5 ✓

DSU init: parent=[0,1,2,3,4,5]

Edge 0-1: findUPar(0)=0 ≠ findUPar(1)=1 → union. parent=[0,0,2,3,4,5]
Edge 0-2: findUPar(0)=0 ≠ findUPar(2)=2 → union. parent=[0,0,0,3,4,5]
Edge 0-3: findUPar(0)=0 ≠ findUPar(3)=3 → union. parent=[0,0,0,0,4,5]
Edge 1-2: findUPar(1)=0, findUPar(2)=0. Same → extra=1
Edge 1-3: findUPar(1)=0, findUPar(3)=0. Same → extra=2

Components: roots where parent[i]==i:
  i=0: parent[0]=0 ✓ → root
  i=1: parent[1]=0 ✗
  i=2: parent[2]=0 ✗
  i=3: parent[3]=0 ✗
  i=4: parent[4]=4 ✓ → root
  i=5: parent[5]=5 ✓ → root
  components = 3

ans = components-1 = 2
extra=2 >= ans=2 → return 2 ✅
(Move 2 extra edges to connect node 4 and node 5)
```

### Complexity
- **Time:** O(E × α(N)) ≈ O(E) — DSU operations
- **Space:** O(N) — DSU arrays

---

## Clean C++ Interview Code

```cpp
class DSU{
public:
    vector<int> parent,size;
    DSU(int n){
        parent.resize(n);
        size.resize(n,1);
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }
    int findUPar(int node){
        if(node==parent[node])
            return node;
        return parent[node]=findUPar(parent[node]);
    }
    void unionBySize(int u,int v){
        int pu=findUPar(u);
        int pv=findUPar(v);
        if(pu==pv) return;
        if(size[pu]<size[pv]){
            parent[pu]=pv;
            size[pv]+=size[pu];
        }else{
            parent[pv]=pu;
            size[pu]+=size[pv];
        }
    }
};

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if(connections.size()<n-1)
            return -1;
        DSU ds(n);
        int extra=0;
        for(auto &edge: connections){
            int u=edge[0];
            int v=edge[1];
            if(ds.findUPar(u)==ds.findUPar(v))
                extra++;
            else
                ds.unionBySize(u,v);
        }
        int components=0;
        for(int i=0;i<n;i++){
            if(ds.parent[i]==i)
                components++;
        }
        int ans=components-1;
        if(extra>=ans){
            return ans;
        }
        return -1;
    }
};
```

> Component count uses `ds.parent[i]==i` (O(1)) — safe here since all unions are complete before counting.

---

## Interview Explanation Script

> "To connect k components I need k-1 cable moves. First, I check feasibility: if there are fewer than n-1 cables total, it's impossible — you need at least n-1 edges to span n nodes."

> "I use DSU to process edges. When both endpoints already share a root, the edge is redundant — I count it as `extra`. Otherwise I union the components."

> "After processing, I count components by checking `parent[i]==i`. Answer is `components-1`. Since we passed the feasibility check, `extra >= components-1` is always guaranteed, so we always return `components-1`."

---

## Recall Line *(10-Second Revision)*

> "Network connected: if edges < n-1 → -1. DSU: same root → extra++, else union. Components = root count. Return components-1."

---

## Short Revision Notes

- Early check: `connections.size() < n-1` → `-1` (not enough cables even if rearranged perfectly)
- `extra++` when `findUPar(u)==findUPar(v)` before the union check — detect redundant edges
- `ds.parent[i]==i` for root count (O(1)), not `findUPar(i)==i` (O(α(N)))
- Answer is always `components-1` when early check passes — final `-1` branch is dead code
- 0-indexed nodes → DSU `resize(n)` not `resize(n+1)`

---

## Generalisation — "Connect Components" Pattern

```
Whenever the problem is: "minimum moves/operations to connect all nodes":

  answer = (number of connected components) - 1

Each move merges two components → after (k-1) moves, k components become 1.

Feasibility: you need at least (k-1) resources (edges/cables) to perform those moves.
```

---

## Pattern Recognition Trigger

**When I see:**
- "Minimum operations to make graph fully connected"
- "How many edges to add/move to connect all components?"

**I should think of:** DSU → count components → answer = components-1. Check feasibility first.

---

## Common Mistakes

❌ Not checking `connections.size() < n-1` early — will get wrong answer on impossible cases
❌ Counting extra edges AFTER union (too late — edge already merged components)
❌ `extra++` when roots are different (should be when they're the same — redundant edge)
❌ `resize(n+1)` when nodes are 0-indexed to n-1

---

## What Interviewer Is Testing

- **Feasibility check** — minimum edges for spanning tree = n-1
- **DSU for component counting** — clean alternative to BFS/DFS
- **Extra edge counting** — same root before union = redundant
- **Components-1 formula** — connecting k components needs k-1 operations

---

## Related Problems

- [ ] Striver Step 15 P39 — DSU Theory
- [ ] Striver Step 15 P40 — Kruskal's (same DSU, cycle = redundant edge)
- [ ] LeetCode #547 — Number of Provinces (P07 — component counting)
- [ ] LeetCode #684 — Redundant Connection (find the one extra edge)

---

## Pattern Category

`Graphs` · `DSU` · `Connected Components` · `Greedy`

---

## 30-Second Last-Minute Revision

> **Network Connected:** If `edges < n-1` → return `-1`.
> DSU: for each edge — same root → `extra++`; else `unionBySize`.
> Count components: `parent[i]==i` → roots.
> Return `components-1`. (Extra edges always sufficient after early check.)
> **Key formula:** components-1 moves needed. extra edges = spare cables to move.
