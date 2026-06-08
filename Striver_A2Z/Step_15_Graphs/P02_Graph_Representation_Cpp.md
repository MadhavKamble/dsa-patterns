# 🔥 Graph Representation in C++

> **Conceptual + Implementation** · **Step 15 — Graphs · P02**

---

## 🧠 Problem Understanding

**What is it asking?**
How do we store a graph in memory so we can efficiently:
- Check if an edge (u, v) exists
- Find all neighbors of a vertex u
- Add/remove edges

There are **three main representations** in C++. Choosing the right one determines algorithm efficiency.

---

## 📦 Representation 1 — Adjacency Matrix

### Structure
A 2D array `adj[N][N]` where:
- `adj[i][j] = 1` (or weight) if edge from i to j exists
- `adj[i][j] = 0` if no edge

### Example
```
Graph: 0—1, 0—2, 1—3, 2—3   (undirected, 4 nodes)

     0  1  2  3
  0 [0, 1, 1, 0]
  1 [1, 0, 0, 1]
  2 [1, 0, 0, 1]
  3 [0, 1, 1, 0]
```

### C++ Implementation

```cpp
// ADJACENCY MATRIX
// Space: O(V²)

const int N = 5;
int adj[N][N] = {0};   // initialize all to 0

// Add undirected edge (u, v)
void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;   // for directed graph, remove this line
}

// Add weighted edge
void addWeightedEdge(int u, int v, int w) {
    adj[u][v] = w;
    adj[v][u] = w;
}

// Check if edge exists: O(1)
bool hasEdge(int u, int v) {
    return adj[u][v] != 0;
}

// Get all neighbors of u: O(V)
void getNeighbors(int u) {
    for (int v = 0; v < N; v++)
        if (adj[u][v]) cout << v << " ";
}
```

### Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Add edge | O(1) | — |
| Check edge | O(1) | — |
| Get all neighbors | O(V) | — |
| Total space | — | O(V²) |

### When to use
✅ Dense graphs (E ≈ V²)  
✅ Frequent edge existence checks  
❌ Sparse graphs (wastes memory)  
❌ V > 10⁴ (V² = 10⁸ integers = ~400 MB)

---

## 📦 Representation 2 — Adjacency List

### Structure
An array of vectors (or lists). `adj[u]` stores all vertices adjacent to `u`.

### Example
```
Graph: 0—1, 0—2, 1—3, 2—3   (undirected, 4 nodes)

adj[0] → [1, 2]
adj[1] → [0, 3]
adj[2] → [0, 3]
adj[3] → [1, 2]
```

### C++ Implementation — Unweighted

```cpp
/*
 * ADJACENCY LIST (most common in interviews)
 * Space: O(V + E)
 * Best for: sparse graphs, BFS/DFS, most LeetCode problems
 */

// Using vector<vector<int>>
vector<vector<int>> adj(n);   // n = number of vertices

// Add undirected edge
void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);   // remove for directed graph
}

// Add directed edge
void addDirectedEdge(int u, int v) {
    adj[u].push_back(v);
}

// Iterate neighbors of u: O(degree(u))
for (int neighbor : adj[u]) {
    // process neighbor
}
```

### C++ Implementation — Weighted

```cpp
/*
 * WEIGHTED ADJACENCY LIST
 * Each entry stores {neighbor, weight}
 * Space: O(V + E)
 */

vector<vector<pair<int,int>>> adj(n);   // adj[u] = {v, weight}

void addWeightedEdge(int u, int v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});   // remove for directed
}

// Iterate: get neighbor and weight
for (auto [v, w] : adj[u]) {
    cout << "Edge " << u << "->" << v << " weight=" << w << "\n";
}
```

### Complexity
| Operation | Time | Space |
|-----------|------|-------|
| Add edge | O(1) amortized | — |
| Check edge (u,v) | O(degree(u)) | — |
| Get all neighbors | O(degree(u)) | — |
| Total space | — | O(V + E) |

### When to use
✅ Sparse graphs (E << V²) — most interview problems  
✅ BFS, DFS, Dijkstra, Prim's  
✅ When V is large (10⁵ nodes common)  
❌ When frequent edge existence checks needed (use matrix)

---

## 📦 Representation 3 — Edge List

### Structure
A list of all edges as pairs (or triples for weighted). Most compact.

```cpp
// EDGE LIST
vector<pair<int,int>> edges;          // unweighted
vector<tuple<int,int,int>> edges;     // weighted: {u, v, weight}

edges.push_back({u, v});
edges.push_back({u, v, w});          // weighted
```

### When to use
✅ Bellman-Ford (iterates all edges)  
✅ Kruskal's MST (sort edges by weight)  
❌ Most other algorithms (harder to find neighbors)

---

## 💻 Complete Input Reading Template (LeetCode / GFG Style)

```cpp
/*
 * STANDARD GRAPH INPUT READING — C++ Template
 *
 * Input format:
 *   Line 1: N V (N vertices, V edges)
 *   Next V lines: u v  (or u v w for weighted)
 *
 * This is the standard way to read a graph in competitive programming.
 */

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;    // n vertices, m edges

    // Unweighted undirected
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Weighted undirected
    vector<vector<pair<int,int>>> wadj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        wadj[u].push_back({v, w});
        wadj[v].push_back({u, w});
    }

    return 0;
}
```

---

## 📊 Comparison Summary

| Property | Adjacency Matrix | Adjacency List | Edge List |
|----------|-----------------|----------------|-----------|
| Space | O(V²) | O(V + E) | O(E) |
| Add edge | O(1) | O(1) | O(1) |
| Check edge | O(1) | O(degree) | O(E) |
| Get all neighbors | O(V) | O(degree) | O(E) |
| Best for | Dense, edge check | Sparse, traversal | Edge iteration |

---

## 🎤 Interview Explanation Script

> "For most graph problems, I use an adjacency list — `vector<vector<int>>` for unweighted, or `vector<vector<pair<int,int>>>` for weighted. It uses O(V + E) space and gives O(degree) neighbor access."

> "I'd use an adjacency matrix only if the graph is dense (E close to V²) or if I need O(1) edge existence checks — e.g., Floyd-Warshall."

> "An edge list is useful specifically for Bellman-Ford and Kruskal's, where we iterate all edges."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Adjacency List: `vector<vector<int>> adj(n)`. O(V+E) space. Standard for interviews. Matrix: O(V²), O(1) edge check. Edge list: for Bellman-Ford/Kruskal."

---

## 📝 Short Revision Notes

- **Adjacency List** = default for interviews (sparse graphs, O(V+E) space)
- **Weighted:** `vector<vector<pair<int,int>>> adj` — `{neighbor, weight}`
- **Directed:** only add one direction when building list
- **0-indexed vs 1-indexed:** read problem carefully; adjust accordingly
- `adj.resize(n)` or `vector<vector<int>> adj(n)` to initialize

---

## ⚠️ Common Mistakes

❌ Using adjacency matrix when V = 10⁵ → 10¹⁰ entries → MLE  
❌ Forgetting to add both directions for undirected graphs  
❌ Off-by-one: nodes numbered 1 to N but adjacency list size N → use N+1  
❌ Not initializing adjacency list size before adding edges  

---

## 🏆 Pattern Category

`Graphs` · `Data Structures` · `Representation`

---

## ⏱️ 30-Second Last-Minute Revision

> **Default:** `vector<vector<int>> adj(n)` — adjacency list, O(V+E).  
> **Weighted:** `vector<vector<pair<int,int>>> adj(n)`.  
> **Undirected:** add both `adj[u].push_back(v)` and `adj[v].push_back(u)`.  
> **Matrix:** only for dense graphs or O(1) edge check. O(V²) space.
