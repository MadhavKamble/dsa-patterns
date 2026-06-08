# Depth First Search (DFS)

> **Concept Problem** (no direct LC#) · **Difficulty:** Medium · **Step 15 — Graphs · P06**

---

## Problem Understanding

**What is it asking?**
Given a graph and a source vertex, perform **Depth First Search** — visit as deep as possible along one path before backtracking and exploring other paths.

**Input:** Graph (adjacency list), source vertex
**Output:** DFS traversal order (list of vertices in DFS order)

**Input:**
```
Graph (undirected):
0 — 1 — 3
|
2 — 4

Adjacency list:
0: [1, 2]
1: [0, 3]
2: [0, 4]
3: [1]
4: [2]
```
**Output (DFS from 0):** `[0, 1, 3, 2, 4]`

**Key Observations:**
- DFS goes as deep as possible before backtracking
- Uses a **Stack** (explicit or recursion call stack)
- Must maintain a `visited` array to avoid revisiting vertices
- DFS does NOT give shortest paths (unlike BFS)
- Time complexity: O(V + E) — each vertex and edge is processed once

---

## DFS Algorithm

### Key Observation

> DFS works like exploring a maze — go down one hallway as far as possible, then backtrack and try the next hallway. Recursion naturally models this: each recursive call goes one level deeper, and returning from the call is the backtrack.
>
> **Visited array** is set when we **enter** a vertex (before recursing), not when we return.

```
Recursive DFS trace for graph above, starting from 0:

dfs(0): visited={0}, result=[0]
  dfs(1): visited={0,1}, result=[0,1]
    dfs(0): already visited, skip
    dfs(3): visited={0,1,3}, result=[0,1,3]
      dfs(1): already visited, skip
      return
    return
  dfs(2): visited={0,1,2,3}, result=[0,1,3,2]
    dfs(0): already visited, skip
    dfs(4): visited={0,1,2,3,4}, result=[0,1,3,2,4]
      dfs(2): already visited, skip
      return
    return
  return
return

DFS order: 0, 1, 3, 2, 4
```

### Algorithm (Recursive)
1. Mark `visited[src] = true`, add `src` to result
2. For each neighbor `nb` of `src`:
   - If `!visited[nb]`: recurse `dfs(nb)`

### Algorithm (Iterative — explicit stack)
1. Push source onto stack, mark visited
2. While stack not empty:
   - Pop `curr`, add to result
   - For each neighbor `nb` of `curr`:
     - If `!visited[nb]`: mark visited, push `nb`

### Dry Run

**Input:** Graph as above, source = 0

| Call Stack (top) | Visited Set | Result |
|------------------|-------------|--------|
| dfs(0) | {0} | [0] |
| dfs(0)→dfs(1) | {0,1} | [0,1] |
| dfs(0)→dfs(1)→dfs(3) | {0,1,3} | [0,1,3] |
| dfs(0)→dfs(1) (backtrack) | {0,1,3} | [0,1,3] |
| dfs(0)→dfs(2) | {0,1,2,3} | [0,1,3,2] |
| dfs(0)→dfs(2)→dfs(4) | {0,1,2,3,4} | [0,1,3,2,4] |

**Output:** `[0, 1, 3, 2, 4]` ✅

### Complexity
- **Time:** O(V + E) — each vertex visited once (O(V)), each edge checked once (O(E))
- **Space:** O(V) — visited array + recursion stack depth (up to V in worst case)

---

## Clean C++ Interview Code

```cpp
/*
 * DEPTH FIRST SEARCH (DFS)
 *
 * PROBLEM UNDERSTANDING:
 *   Traverse all vertices of a graph by going as deep as possible
 *   along each path before backtracking.
 *
 * DATA STRUCTURE: Recursion stack (or explicit stack)
 *
 * KEY STEPS:
 *   1. Mark current as visited, add to result
 *   2. Recurse on all unvisited neighbors
 *
 * PROPERTIES OF DFS:
 *   - Visits entire path before backtracking
 *   - Useful for: cycle detection, topological sort, connected components
 *   - Does NOT guarantee shortest path
 *
 * COMPLEXITY: Time O(V+E) | Space O(V)
 */
class Solution {
    void dfs(int node, vector<vector<int>>& adj,
             vector<bool>& visited, vector<int>& result) {
        visited[node] = true;
        result.push_back(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, adj, visited, result);
            }
        }
    }

public:
    vector<int> dfsTraversal(int n, vector<vector<int>>& adj) {
        vector<bool> visited(n, false);
        vector<int> result;
        dfs(0, adj, visited, result);    // start from vertex 0
        return result;
    }
};
```

### Iterative DFS (explicit stack)

```cpp
// Iterative DFS — avoids stack overflow on very deep graphs
vector<int> dfsIterative(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> result;
    stack<int> st;

    visited[0] = true;
    st.push(0);

    while (!st.empty()) {
        int curr = st.top();
        st.pop();
        result.push_back(curr);

        // push neighbors in reverse order to match recursive DFS order
        for (int i = adj[curr].size() - 1; i >= 0; i--) {
            int nb = adj[curr][i];
            if (!visited[nb]) {
                visited[nb] = true;
                st.push(nb);
            }
        }
    }

    return result;
}
```

### DFS for Disconnected Graphs

```cpp
// Handle all components
vector<int> dfsAll(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> result;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited, result);    // new component
        }
    }

    return result;
}
```

---

## Interview Explanation Script

> "DFS explores as deep as possible before backtracking, using the call stack for recursion. I mark the current node visited and add it to the result, then recurse on each unvisited neighbor. When there are no more unvisited neighbors, I backtrack automatically via the call stack."

> "I set visited before recursing (not after returning) — otherwise I'd revisit the same node through a different path before the first visit completes, causing infinite recursion on cycles."

> "For disconnected graphs, I wrap DFS in an outer loop over all vertices to ensure every component is visited."

---

## Recall Line *(10-Second Revision)*

> "DFS: Recurse + visited array. Mark visited on ENTRY. Goes deep first. O(V+E)."

---

## Short Revision Notes

- Recursion = implicit stack; iterative DFS uses explicit stack
- Mark visited **before** recursing — prevents infinite loops on cycles
- DFS order depends on adjacency list ordering (not unique)
- BFS vs DFS: BFS = queue + shortest path; DFS = stack + complete path exploration
- Multi-component: outer `for` loop, call DFS on every unvisited vertex
- DFS tree has **tree edges** and **back edges** (in undirected graphs)

---

## Pattern Recognition Trigger

**When I see:**
- "Find all paths between two nodes"
- "Detect a cycle"
- "Topological sort"
- "Connected components / number of islands"
- "Flood fill"

**I should think of:** DFS with visited array

---

## Common Mistakes

❌ Not marking visited before recursing → infinite loop on cycles
❌ Marking visited after recursion returns → same node enters call stack multiple times
❌ Forgetting the outer loop for disconnected graphs → misses some components
❌ Confusing iterative DFS with BFS — iterative DFS uses **stack** (LIFO), BFS uses **queue** (FIFO)

---

## What Interviewer Is Testing

- **Concept:** Depth-first exploration, backtracking
- **Detail:** Why visited is set on entry not exit
- **Application:** Connecting DFS to cycle detection, topological sort, pathfinding

---

## DFS vs BFS Summary

| Property | DFS | BFS |
|----------|-----|-----|
| Data structure | Stack / Recursion | Queue |
| Space (worst) | O(V) — stack depth | O(V) — queue width |
| Shortest path | No | Yes (unweighted) |
| Best for | Cycle detection, topo sort, paths | Shortest path, level order |
| Explores | Deepest first | Nearest first |

---

## Related Problems

- [ ] LeetCode #200 — Number of Islands (DFS on grid)
- [ ] LeetCode #547 — Number of Provinces (DFS on adjacency matrix)
- [ ] LeetCode #207 — Course Schedule (cycle detection via DFS)
- [ ] LeetCode #417 — Pacific Atlantic Water Flow (DFS from borders)
- [ ] Striver Step 15 P07 — Number of Provinces

---

## Pattern Category

`Graphs` · `DFS` · `Traversal` · `Recursion`

---

## Difficulty Analysis

**Rating:** Medium (concept simple, but details — visited timing, disconnected graphs — trip people up)

**Why challenging:** Cycle handling, understanding the recursive call stack as implicit backtracking, and adapting to grid or state-space DFS.

---

## 30-Second Last-Minute Revision

> **DFS:** Recurse. Mark visited on ENTRY. Go deep → backtrack → try next neighbor.
> **Disconnected:** outer loop over all vertices.
> **Time:** O(V+E) | **Space:** O(V)
> **Watch out for:** Mark visited BEFORE recursing, not after returning
