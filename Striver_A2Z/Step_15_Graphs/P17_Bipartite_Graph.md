# Bipartite Graph

> **LeetCode #785** · **Difficulty:** Medium · **Step 15 — Graphs · P17**

---

## Problem Understanding

**What is it asking?**
Given an undirected graph represented as an adjacency list, determine if it is **bipartite** — i.e., can its nodes be split into two groups such that every edge connects a node from group A to a node from group B (no edge within the same group).

**Input:** `graph[][]` — adjacency list (graph[i] = neighbors of node i)
**Output:** `true` if bipartite, `false` otherwise

**Example:**
```
graph = [[1,3],[0,2],[1,3],[0,2]]
0 - 1 - 2 - 3 - 0  (cycle of length 4 — even cycle)

Color: 0→0, 1→1, 2→0, 3→1
No two adjacent nodes share a color → bipartite ✅

graph = [[1,2,3],[0,2],[0,1],[0]]
Contains triangle 0-1-2 (odd cycle)
→ not bipartite ❌
```

**Key Observations:**
- A graph is bipartite ↔ it has **no odd-length cycles**
- BFS/DFS with 2-coloring: try to color graph with 2 colors, no adjacent nodes same color
- `color[node] = -1` means unvisited; `0` and `1` are the two colors
- `1 - color[node]` elegantly flips between 0 and 1
- Outer loop required — handles disconnected graphs

---

## Optimal Approach — BFS 2-Coloring

### Key Observation

> Assign alternating colors (0/1) during BFS. If we ever try to color a node that's already colored the same as its neighbor, we found an odd cycle — not bipartite. `1 - color[node]` is a clean way to flip color without branching.

### Algorithm
1. `color[0..n-1] = -1` (uncolored)
2. For each uncolored node `i`: BFS from `i`, color it `0`
3. For each neighbor `adj` of dequeued `node`:
   - Uncolored: `color[adj] = 1 - color[node]`, enqueue
   - Same color as `node`: return `false`
4. Return `true`

### Dry Run

**graph = [[1,3],[0,2],[1,3],[0,2]]**

| Dequeued | color[node] | Neighbor | color[adj] before | Action |
|----------|-------------|----------|-------------------|--------|
| 0 | 0 | 1 | -1 | color[1]=1, enqueue |
| 0 | 0 | 3 | -1 | color[3]=1, enqueue |
| 1 | 1 | 0 | 0 | 0≠1 → ok |
| 1 | 1 | 2 | -1 | color[2]=0, enqueue |
| 3 | 1 | 0 | 0 | 0≠1 → ok |
| 3 | 1 | 2 | 0 | 0≠1 → ok |
| 2 | 0 | 1 | 1 | 1≠0 → ok |
| 2 | 0 | 3 | 1 | 1≠0 → ok |

Return `true` ✅

### Complexity
- **Time:** O(V + E) — each node and edge processed once
- **Space:** O(V) — color array + queue

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, -1);
        for(int i = 0; i < n; i++) {
            if(color[i] == -1) {
                queue<int> q;
                q.push(i);
                color[i] = 0;
                while(!q.empty()) {
                    int node = q.front();
                    q.pop();
                    for(auto adj : graph[node]) {
                        if(color[adj] == -1) {
                            color[adj] = !color[node];
                            q.push(adj);
                        }
                        else if(color[adj] == color[node]) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }
};
```

### DFS Variant

```cpp
class Solution {
    bool dfs(int node, int col, vector<int>& color,
             vector<vector<int>>& graph) {
        color[node]=col;
        for(auto adj : graph[node]) {
            if(color[adj]==-1) {
                if(!dfs(adj, !col, color, graph)) return false;
            }
            else if(color[adj]==col) {
                return false;
            }
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int> color(n,-1);
        for(int i=0;i<n;i++) {
            if(color[i]==-1) {
                if(!dfs(i, 0, color, graph)) return false;
            }
        }
        return true;
    }
};
```

---

## Interview Explanation Script

> "I use BFS with 2-coloring. Initialize all nodes as uncolored (-1). For each uncolored node, BFS and color it 0. For each neighbor: if uncolored, assign the opposite color (`!color[node]`) and enqueue; if already colored the same as the current node, we have a conflict — return false."

> "`!color[node]` is elegant: `!0=1` and `!1=0` — flips between the two colors with no branching."

> "The outer for-loop handles disconnected graphs — every component is independently 2-colored."

---

## Recall Line *(10-Second Revision)*

> "Bipartite: BFS 2-coloring. color=-1 unvisited. !color[node] flips. Same color neighbor → false. O(V+E)."

---

## Short Revision Notes

- `color[i] = -1`: unvisited; `0` and `1`: two groups
- `!color[node]`: flips between 0 and 1 without branching (`!0=1`, `!1=0`)
- Conflict condition: `color[adj] == color[node]` (same color, adjacent nodes)
- Outer loop is mandatory — graph may be disconnected
- Bipartite ↔ no odd-length cycle ↔ 2-colorable
- All trees are bipartite (no cycles → no odd cycles)

---

## Pattern Recognition Trigger

**When I see:**
- "Can nodes be split into two groups with no intra-group edges?"
- "Is graph 2-colorable?"
- "Check if graph has any odd cycle"
- "Divide into teams such that no two teammates are connected"

**I should think of:** BFS/DFS 2-coloring

---

## Common Mistakes

❌ Forgetting the outer loop → only checks first connected component
❌ Not initializing `color[i]=0` before pushing to queue → BFS starts uncolored
❌ Checking `color[adj] != color[node]` as the error condition (inverted logic)
❌ Using visited array instead of color array — need the actual color to detect conflicts

---

## What Interviewer Is Testing

- **2-coloring insight:** bipartite = 2-colorable
- **`!color[node]` trick** for flipping colors
- **Disconnected graph handling** with outer loop

---

## Bipartite Facts

| Graph type | Bipartite? |
|-----------|-----------|
| All trees | Yes |
| Even-length cycles | Yes |
| Odd-length cycles | No |
| Complete graph K₂ | Yes |
| Complete graph K₃ (triangle) | No |

---

## Related Problems

- [ ] LeetCode #886 — Possible Bipartition (same 2-coloring on a different graph construction)
- [ ] LeetCode #207 — Course Schedule (cycle detection, related concept)
- [ ] Striver Step 15 P10/P11 — Cycle Detection Undirected

---

## Pattern Category

`Graphs` · `BFS` · `DFS` · `Bipartite` · `2-Coloring`

---

## Difficulty Analysis

**Rating:** Medium (recognizing bipartite = 2-colorable is the key insight; implementation is clean)

**Why challenging:** `1 - color[node]` trick, handling disconnected graphs, and knowing that bipartite ↔ no odd cycle.

---

## 30-Second Last-Minute Revision

> **Bipartite:** BFS 2-coloring. `color[]` init to -1.
> Push node with color 0. Dequeue → for each neighbor:
> uncolored → `color[adj]=!color[node]`, enqueue.
> same color as node → return false.
> Outer loop for disconnected components.
> **Time:** O(V+E) | **Space:** O(V)
