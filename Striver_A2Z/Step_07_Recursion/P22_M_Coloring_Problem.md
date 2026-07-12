# M Coloring Problem

> **GFG** · **Difficulty:** Medium · **Step 7 — Recursion · P22**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an undirected graph with N nodes and M colors, determine whether the graph can be colored using at most M colors such that no two adjacent nodes share the same color.

**Input:** N=4, M=3, edges: (0,1),(1,2),(2,3),(3,0),(0,2) → **Output:** `true`

**Key Observations:**
- Color one node at a time (node 0 → node 1 → ... → node N-1).
- For each node, try all M colors. If no adjacent node has that color, assign it and recurse.
- Backtrack if no valid color exists for the current node.
- `isSafe`: checks ALL neighbors of `node` (left already colored, right not yet) — since undirected, only neighbors assigned so far can conflict.

---

## 🥇 Recursive Backtracking

### Key Insight

> 💡 Node-by-node assignment. Try colors 1 to M. If `isSafe`, assign and recurse to next node. Backtrack (reset to 0) if recursion fails. Base: `node == N` → all nodes colored → true.

### isSafe Logic

```cpp
isSafe(node, color[], graph, n, col):
  for each neighbor k of node:
    if color[k] == col: return false
  return true
```

Since we fill left-to-right (node 0 first), only nodes `k < node` have assigned colors that can conflict. The loop checks all k (0 to N-1) but `color[k] == 0` for unassigned nodes → no false conflict since we never assign color 0.

### Algorithm
1. **Base:** `node == N` → return true.
2. Loop `i = 1` to `m`:
   - If `isSafe(node, color, graph, N, i)`:
     - `color[node] = i`, recurse `node+1`.
     - If recursion returns true → return true.
     - Backtrack: `color[node] = 0`.
3. Return false.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

bool isSafe(int node,int color[],bool graph[101][101],int n,int col){
    for(int k=0;k<n;k++){
        if(k!=node && graph[k][node]==1 && color[k]==col)
            return false;
    }
    return true;
}

bool solve(int node,int color[],int m,int N,bool graph[101][101]){
    if(node==N) return true;
    for(int i=1;i<=m;i++){
        if(isSafe(node,color,graph,N,i)){
            color[node]=i;
            if(solve(node+1,color,m,N,graph)) return true;
            color[node]=0;
        }
    }
    return false;
}

bool graphColoring(bool graph[101][101],int m,int N){
    int color[N]={0};
    return solve(0,color,m,N,graph);
}
```

**Time:** O(M^N × N) — M choices for N nodes, O(N) safety check per assignment
**Space:** O(N) — recursion depth + color array

### Dry Run — N=4, M=3, 4-node complete-ish graph

```
solve(0): try color=1 → isSafe(0,c,g,4,1)=true → color[0]=1
  solve(1): try color=1 → graph[0][1]=1,color[0]=1 → unsafe
            try color=2 → safe → color[1]=2
    solve(2): try color=1 → graph[0][2]=1,color[0]=1 → unsafe
              try color=2 → graph[1][2]=1,color[1]=2 → unsafe
              try color=3 → safe → color[2]=3
      solve(3): try color=1 → graph[0][3]=1,color[0]=1 → unsafe
                try color=2 → graph[2][3]=1,color[2]=3 → safe → color[3]=2
        solve(4): node=4=N → return true ✓
```

Coloring: 0→red(1), 1→green(2), 2→blue(3), 3→green(2) ✓

---

## 🔁 Connection to N-Queens (P19)

| | N-Queens | M-Coloring |
|---|---|---|
| Fill order | column by column | node by node |
| Try options | rows 0 to N-1 | colors 1 to M |
| Safety check | row/diagonal conflict | adjacent node same color |
| Backtrack | reset to '.' | reset to 0 |
| Return type | collect all | return true/false (existence) |

Both are constraint-satisfaction backtracking — differ only in the domain and safety predicate.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Node by node. Try colors 1→M. isSafe: no adjacent node has same color. Assign, recurse(node+1), backtrack(color=0). Base: node==N → true. O(M^N × N)."

---

## 📝 Short Revision Notes

- `color[k] == 0` for unassigned → never conflicts since 0 is not a valid color.
- `k != node` in `isSafe` skips self-loop check — not strictly necessary if no self-loops, but defensive.
- This is a decision problem (does a coloring exist?) — to enumerate all colorings, collect instead of return-true.

---

## ⚠️ Common Mistakes

❌ Starting colors from 0 — 0 is used as "unassigned", causes false conflicts.
❌ Not resetting `color[node] = 0` after failed recursion — corrupts future attempts.
❌ Checking only nodes < current instead of all — misses diagonal/reverse edges in undirected graph.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "color a graph with M colors, no two adjacent same color" → **node-by-node assignment, try 1→M, isSafe = no adjacent same color, backtrack**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Graph` · `Constraint Satisfaction`

---

## ⏱️ 30-Second Last-Minute Revision

> Try colors 1→M at each node. `isSafe`: scan all adj nodes for same color. Assign, recurse(node+1), backtrack(0). Base: node==N → true. **Time:** O(M^N × N).
