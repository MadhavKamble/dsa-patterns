# 🔥 Connected Components — Logic Explanation

> **Conceptual + Implementation** · **Step 15 — Graphs · P04**

---

## 🧠 Problem Understanding

**What is a Connected Component?**
In an **undirected** graph, a connected component is a maximal set of vertices such that there is a path between every pair of vertices in the set.

**In other words:** A group of vertices that are all reachable from each other.

**Input:** Undirected graph with N vertices and M edges  
**Output:** Number of connected components (and optionally, which vertices are in each)

**Example:**
```
Graph with 7 vertices:
0 — 1 — 2        4 — 5
    |               |
    3            6

Connected Components:
  Component 1: {0, 1, 2, 3}
  Component 2: {4, 5, 6}

Answer: 2 connected components
```

**Key Observations:**
- A single vertex with no edges is its own component
- For a fully connected graph: 1 component
- To find all components: start BFS/DFS from each **unvisited** vertex
- Each BFS/DFS traversal from an unvisited node discovers exactly one component

---

## 🥇 Algorithm — BFS/DFS to Find All Components

### Key Observation

> 💡 Iterate through all vertices 0 to N-1. If a vertex is **not visited**, it's the start of a new component. Run BFS/DFS from it to mark all vertices in that component as visited. Count how many times we "start a new traversal."

### Algorithm
1. Initialize `visited[0..N-1] = false`
2. `components = 0`
3. For each vertex `v` from 0 to N-1:
   - If `!visited[v]`:
     - `components++`
     - Run BFS or DFS from `v`, marking all reachable vertices as visited
4. Return `components`

### Dry Run

**Graph:** N=7, Edges: (0,1),(1,2),(1,3),(4,5),(5,6)
```
Adjacency list:
  0: [1]
  1: [0, 2, 3]
  2: [1]
  3: [1]
  4: [5]
  5: [4, 6]
  6: [5]
```

| Step | Vertex v | Visited? | Action | Components |
|------|---------|----------|--------|-----------|
| 1 | 0 | ❌ | BFS from 0 → visits {0,1,2,3} | 1 |
| 2 | 1 | ✅ | skip | 1 |
| 3 | 2 | ✅ | skip | 1 |
| 4 | 3 | ✅ | skip | 1 |
| 5 | 4 | ❌ | BFS from 4 → visits {4,5,6} | 2 |
| 6 | 5 | ✅ | skip | 2 |
| 7 | 6 | ✅ | skip | 2 |

**Answer: 2 connected components** ✅

### Complexity
- **Time:** O(V + E) — each vertex and edge visited at most once
- **Space:** O(V) — visited array + BFS/DFS queue/stack

---

## 💻 Clean C++ Code

```cpp
/*
 * CONNECTED COMPONENTS — count and identify components using BFS
 *
 * ALGORITHM:
 *   For each unvisited vertex, run BFS/DFS to visit entire component.
 *   Count how many times we initiate a new traversal = number of components.
 *
 * KEY INSIGHT: The outer loop "discovers" components; BFS "explores" each one.
 *
 * COMPLEXITY: Time O(V+E) | Space O(V)
 */
class Solution {
private:
    void bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int neighbor : adj[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

public:
    int countComponents(int n, vector<vector<int>>& adj) {
        vector<bool> visited(n, false);
        int components = 0;

        for (int v = 0; v < n; v++) {
            if (!visited[v]) {
                components++;           // new component found
                bfs(v, adj, visited);  // mark all reachable vertices
            }
        }

        return components;
    }
};
```

### With Component Labeling (which component each vertex belongs to)

```cpp
// Returns component ID for each vertex (0-indexed component IDs)
vector<int> labelComponents(int n, vector<vector<int>>& adj) {
    vector<int> comp(n, -1);  // comp[v] = component ID of vertex v
    int compId = 0;

    for (int v = 0; v < n; v++) {
        if (comp[v] == -1) {
            // BFS from v
            queue<int> q;
            q.push(v);
            comp[v] = compId;
            while (!q.empty()) {
                int node = q.front(); q.pop();
                for (int nb : adj[node]) {
                    if (comp[nb] == -1) {
                        comp[nb] = compId;
                        q.push(nb);
                    }
                }
            }
            compId++;
        }
    }
    return comp;
}
```

---

## 🎤 Interview Explanation Script

> "To find connected components, I iterate through all vertices. For each unvisited vertex, I run a BFS (or DFS) from it — this explores the entire component it belongs to and marks all reachable vertices as visited. Every time I start a new BFS, I've found a new component."

> "The key insight is that the outer for-loop 'discovers' new components, while BFS 'explores' each component. Since every vertex and edge is visited at most once, the total time is O(V + E)."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Outer loop over all vertices. If unvisited → new component, BFS/DFS to mark all reachable as visited. Count = number of BFS starts."

---

## 📝 Short Revision Notes

- Components only make sense for **undirected** graphs (directed graphs have "strongly connected components" — different concept, P54)
- A single vertex with no edges = its own component
- LeetCode #200 (Number of Islands) uses exactly this pattern on a grid
- Always need a `visited` array to avoid revisiting and infinite loops

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Count groups", "number of islands", "how many clusters"
- "Are u and v connected?"
- "Find all nodes reachable from each other"

**I should think of:** Connected components via BFS/DFS with visited array

---

## ⚠️ Common Mistakes

❌ Forgetting to start BFS from **each** unvisited vertex — only covers one component  
❌ Not resetting `visited` between separate calls  
❌ Applying "undirected" component logic to directed graphs (need Kosaraju/Tarjan for SCC)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** The outer-loop-plus-BFS/DFS pattern for components
- **Generalization:** This same pattern solves: number of islands, flood fill, counting provinces

---

## 📚 Related Problems

- [ ] LeetCode #323 — Number of Connected Components in Undirected Graph
- [ ] LeetCode #200 — Number of Islands (same pattern on 2D grid)
- [ ] LeetCode #547 — Number of Provinces
- [ ] Striver Step 15 P07 — Number of Provinces

---

## 🏆 Pattern Category

`Graphs` · `BFS/DFS` · `Connected Components`

---

## ⏱️ 30-Second Last-Minute Revision

> For each unvisited vertex: `components++`, then BFS/DFS to mark entire component.  
> **Time:** O(V+E) | **Space:** O(V)  
> Pattern used in: islands, provinces, clusters — whenever "how many groups" is asked.
