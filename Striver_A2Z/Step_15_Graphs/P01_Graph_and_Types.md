# 🔥 Graph and Types

> **Conceptual Foundation** · **Step 15 — Graphs · P01**

---

## 🧠 What is a Graph?

A **Graph** is a non-linear data structure consisting of:
- **Vertices (Nodes):** The entities (e.g., cities, people, web pages)
- **Edges:** Connections between vertices

```
Notation: G = (V, E)
V = set of vertices = {0, 1, 2, 3, 4}
E = set of edges    = {(0,1), (0,2), (1,3), (2,4)}

Visualization:
    0
   / \
  1   2
  |   |
  3   4
```

---

## 🗂️ Types of Graphs

### 1. Based on Edge Direction

#### Undirected Graph
- Edges have **no direction** — connection is bidirectional
- If there's an edge (u, v), you can travel from u→v AND v→u
- Example: Facebook friendships, road networks

```
0 --- 1 --- 3
|
2 --- 4
```

#### Directed Graph (Digraph)
- Edges have **direction** — an arrow from u to v means u→v only (not v→u)
- Example: Twitter followers, web page links, dependencies

```
0 → 1 → 3
↓
2 → 4
```

---

### 2. Based on Edge Weights

#### Unweighted Graph
- All edges have equal "cost" (or cost is not relevant)
- Example: Social network connections

#### Weighted Graph
- Each edge has a **weight/cost** associated with it
- Example: Road network with distances, flight costs

```
    0
  4/ \7
  1   2
  3\  |2
    \ |
     3
```

---

### 3. Based on Cycles

#### Acyclic Graph
- Contains **no cycles** (no path that starts and ends at the same node)

#### Cyclic Graph
- Contains **at least one cycle**

#### DAG (Directed Acyclic Graph)
- Directed + No cycles
- Critical for: Topological Sort, Dependency resolution, Build systems
```
0 → 1 → 3
↓       ↑
2 ──────┘
```

---

### 4. Other Important Types

#### Connected Graph (Undirected)
- There exists a **path between every pair of vertices**
- No isolated components

#### Disconnected Graph
- At least one vertex has no path to another
- Has multiple **connected components**

#### Bipartite Graph
- Vertices can be divided into **two disjoint sets** U and V
- Every edge connects a vertex in U to one in V (no edge within the same set)
- Property: A graph is bipartite if and only if it has **no odd-length cycles**
- Example: Matching problems (students ↔ courses)

#### Complete Graph (Kₙ)
- Every pair of vertices has an edge
- N vertices → N(N-1)/2 edges (undirected)

#### Tree
- Connected, undirected graph with **no cycles**
- N vertices, exactly N-1 edges
- Any two vertices are connected by exactly one path

#### Forest
- A collection of trees (disconnected acyclic graph)

---

## 📐 Key Graph Terminology

| Term | Definition |
|------|-----------|
| **Degree** (undirected) | Number of edges connected to a vertex |
| **In-degree** (directed) | Number of edges pointing INTO a vertex |
| **Out-degree** (directed) | Number of edges pointing OUT of a vertex |
| **Path** | Sequence of vertices connected by edges |
| **Simple Path** | Path with no repeated vertices |
| **Cycle** | Path that starts and ends at the same vertex |
| **Connected Component** | Maximal set of vertices all connected to each other |
| **Strongly Connected** | In directed graph: every vertex reachable from every other |
| **Weakly Connected** | Directed graph is connected if you ignore edge directions |
| **Spanning Tree** | Tree that includes all vertices of the graph |
| **Bridge** | An edge whose removal disconnects the graph |
| **Articulation Point** | A vertex whose removal disconnects the graph |

---

## 📊 Graph Properties

### Handshaking Lemma
> Sum of all degrees = 2 × number of edges (undirected)

```
Graph: 0—1, 0—2, 1—3
Degrees: deg(0)=2, deg(1)=2, deg(2)=1, deg(3)=1
Sum = 6 = 2 × 3 edges ✓
```

### Edge Count Bounds
| Graph Type | Min Edges | Max Edges |
|-----------|-----------|-----------|
| Tree (N vertices) | N-1 | N-1 |
| Connected graph | N-1 | N(N-1)/2 |
| Complete graph Kₙ | N(N-1)/2 | N(N-1)/2 |

---

## 🔑 Choosing the Right Graph Representation

> This directly determines algorithm efficiency. See P02 for implementation.

| Situation | Use |
|-----------|-----|
| Dense graph (many edges) | Adjacency Matrix |
| Sparse graph (few edges) | Adjacency List |
| Check if edge exists in O(1) | Adjacency Matrix |
| Iterate all neighbors efficiently | Adjacency List |
| Most interview / LeetCode problems | Adjacency List |

---

## 🧠 Interview Pattern Recognition — Graph Type Identification

**When I see:**
- "Friend network", "road map", "connections" → **Undirected Graph**
- "Prerequisites", "dependencies", "directed links" → **Directed Graph / DAG**
- "Weighted edges", "distances", "costs" → **Weighted Graph**
- "Is there a path?", "connected?" → **BFS / DFS on graph**
- "Minimum cost path" → **Dijkstra / Bellman-Ford**
- "Sort tasks by dependency" → **Topological Sort (DAG)**
- "Two groups, no conflict" → **Bipartite Check**
- "Minimum connections to connect all" → **Minimum Spanning Tree**

---

## 🔥 What Interviewer Is Testing

- Can you identify **which graph type** the problem maps to?
- Do you know the **properties** of each type? (bipartite ↔ no odd cycles, tree ↔ N-1 edges, etc.)
- Can you recognize DAG properties for topological sort?

---

## 📚 Related Problems

- [ ] LeetCode #200 — Number of Islands (connected components)
- [ ] LeetCode #207 — Course Schedule (DAG cycle detection)
- [ ] LeetCode #785 — Is Graph Bipartite?
- [ ] Striver Step 15 P04 — Connected Components
- [ ] Striver Step 15 P19 — Bipartite Graph Check

---

## ⏱️ 30-Second Last-Minute Revision

> **Undirected:** bidirectional edges. **Directed:** one-way edges.  
> **Weighted:** edges have costs. **DAG:** directed + no cycles → topological sort.  
> **Bipartite:** 2-colorable, no odd cycles. **Tree:** connected, acyclic, N-1 edges.  
> **Bridge:** edge whose removal disconnects. **Articulation point:** vertex whose removal disconnects.
