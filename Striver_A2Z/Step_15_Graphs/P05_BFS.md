# 🔥 Breadth First Search (BFS)

> **LeetCode #1971** (path finding) · **Difficulty:** Medium · **Step 15 — Graphs · P05**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a graph and a source vertex, perform **Breadth First Search** — visit all vertices layer by layer (level by level), exploring all neighbors of the current vertex before going deeper.

**Input:** Graph (adjacency list), source vertex  
**Output:** BFS traversal order (list of vertices in BFS order)

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
**Output (BFS from 0):** `[0, 1, 2, 3, 4]`

**Key Observations:**
- BFS explores all vertices at distance 1 before distance 2, distance 2 before distance 3, etc.
- Uses a **Queue** (FIFO) — first in, first out
- Must maintain a `visited` array to avoid revisiting vertices
- In an unweighted graph, BFS gives the **shortest path** (in terms of number of edges)
- Time complexity: O(V + E) — each vertex and edge is processed once

---

## 🥇 BFS Algorithm

### Key Observation

> 💡 BFS works like ripples in water. From the source, it first visits all immediate neighbors (distance 1), then their unvisited neighbors (distance 2), and so on.
>
> **Queue** is the natural data structure: we process vertices in the order we encounter them (FIFO). When we visit a vertex, we add all its unvisited neighbors to the back of the queue.

```
Queue evolution for graph above, starting from 0:

Initial: queue=[0], visited={0}

Step 1: dequeue 0, process, enqueue unvisited neighbors [1, 2]
        queue=[1, 2], visited={0,1,2}

Step 2: dequeue 1, process, enqueue unvisited neighbors [3]
        queue=[2, 3], visited={0,1,2,3}

Step 3: dequeue 2, process, enqueue unvisited neighbors [4]
        queue=[3, 4], visited={0,1,2,3,4}

Step 4: dequeue 3, no unvisited neighbors
        queue=[4]

Step 5: dequeue 4, no unvisited neighbors
        queue=[]

BFS order: 0, 1, 2, 3, 4
```

### Algorithm
1. Initialize `visited[0..N-1] = false`, `queue`
2. Mark source as visited, enqueue source
3. While queue is not empty:
   a. Dequeue node `curr`
   b. Add `curr` to result
   c. For each neighbor `nb` of `curr`:
      - If `!visited[nb]`: mark visited, enqueue `nb`
4. Return result

### Dry Run

**Input:** Graph as above, source = 0

| Step | Queue | Dequeued | Neighbors | Visited Set | Result |
|------|-------|----------|-----------|-------------|--------|
| Init | [0] | — | — | {0} | [] |
| 1 | [1,2] | 0 | 1,2 | {0,1,2} | [0] |
| 2 | [2,3] | 1 | 0(vis),3 | {0,1,2,3} | [0,1] |
| 3 | [3,4] | 2 | 0(vis),4 | {0,1,2,3,4} | [0,1,2] |
| 4 | [4] | 3 | 1(vis) | {0,1,2,3,4} | [0,1,2,3] |
| 5 | [] | 4 | 2(vis) | {0,1,2,3,4} | [0,1,2,3,4] |

**Output:** `[0, 1, 2, 3, 4]` ✅

### Complexity
- **Time:** O(V + E) — each vertex dequeued once (O(V)), each edge checked once (O(E))
- **Space:** O(V) — visited array + queue (at most all vertices in queue)

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * BREADTH FIRST SEARCH (BFS)
 *
 * PROBLEM UNDERSTANDING:
 *   Traverse all vertices of a graph level by level starting from source.
 *
 * DATA STRUCTURE: Queue (FIFO) — processes vertices in discovery order
 *
 * KEY STEPS:
 *   1. Mark source visited and enqueue
 *   2. While queue not empty: dequeue, process, enqueue unvisited neighbors
 *
 * PROPERTIES OF BFS:
 *   - Visits all nodes at distance k before distance k+1
 *   - Shortest path (unweighted) = BFS distance
 *   - Level order = BFS layers
 *
 * COMPLEXITY: Time O(V+E) | Space O(V)
 */
class Solution {
public:
    vector<int> bfsTraversal(int n, vector<vector<int>>& adj) {
        vector<bool> visited(n, false);
        vector<int> result;
        queue<int> q;

        // start BFS from vertex 0 (or any given source)
        visited[0] = true;
        q.push(0);

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            result.push_back(curr);           // process current vertex

            for (int neighbor : adj[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;  // mark before enqueue (not after dequeue!)
                    q.push(neighbor);
                }
            }
        }

        return result;
    }
};
```

### Multi-Source BFS (for disconnected graphs or multi-component)

```cpp
// Handle all components (disconnected graph)
vector<int> bfsAll(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    vector<int> result;

    for (int i = 0; i < n; i++) {        // outer loop for disconnected graphs
        if (!visited[i]) {
            queue<int> q;
            visited[i] = true;
            q.push(i);
            while (!q.empty()) {
                int curr = q.front(); q.pop();
                result.push_back(curr);
                for (int nb : adj[curr]) {
                    if (!visited[nb]) {
                        visited[nb] = true;
                        q.push(nb);
                    }
                }
            }
        }
    }
    return result;
}
```

### BFS with Level Tracking (Shortest Path)

```cpp
// BFS with distance tracking from source
vector<int> bfsDistance(int n, vector<vector<int>>& adj, int src) {
    vector<int> dist(n, -1);   // -1 = unreachable
    queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int curr = q.front(); q.pop();
        for (int nb : adj[curr]) {
            if (dist[nb] == -1) {        // unvisited
                dist[nb] = dist[curr] + 1;
                q.push(nb);
            }
        }
    }

    return dist;  // dist[v] = shortest path length from src to v
}
```

---

## 🎤 Interview Explanation Script

> "BFS explores vertices layer by layer using a queue. I start by marking the source as visited and enqueuing it. While the queue is non-empty, I dequeue a vertex, record it, and enqueue all its unvisited neighbors — marking them visited immediately to prevent duplicates."

> "The visited flag is set when we **enqueue** (not when we dequeue) — this is critical. If we set it on dequeue, the same vertex could be enqueued multiple times, ruining O(V+E) complexity."

> "BFS naturally gives the shortest path in an unweighted graph because it explores level by level — the first time we reach a vertex is via the shortest path."

---

## 🧾 Recall Line *(10-Second Revision)*

> "BFS: Queue + visited array. Mark visited on ENQUEUE not dequeue. Explores level by level. O(V+E)."

---

## 📝 Short Revision Notes

- Queue (FIFO) for BFS, Stack for DFS
- Mark visited **before** enqueuing (not after dequeuing) — prevents duplicate enqueues
- BFS gives shortest path in **unweighted** graphs
- Level k = all vertices at exactly k edges from source
- Multi-component graph: outer loop over all vertices, start new BFS if unvisited
- `dist[v] = -1` to indicate unreachable; update to `dist[curr] + 1` when enqueuing

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Shortest path in unweighted graph"
- "Level order traversal"
- "Minimum steps to reach"
- "Rotten oranges", "0/1 matrix", "word ladder" (multi-source BFS)

**I should think of:** BFS with queue

---

## ⚠️ Common Mistakes

❌ Marking visited **after** dequeue — allows same vertex to be enqueued multiple times → TLE or wrong answer  
❌ Using stack instead of queue → gives DFS, not BFS  
❌ Not handling disconnected graphs (only BFS from one source) → misses components  
❌ `while (!q.empty())` inside outer loop without proper visited check → BFS from wrong starting point  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Level-by-level traversal, queue as the core data structure
- **Detail:** Why `visited` must be set on enqueue not dequeue
- **Application:** Connecting BFS to shortest path problems

---

## 🚀 BFS Variants

| Variant | Change | Application |
|---------|--------|-------------|
| Standard BFS | As above | Traversal, reachability |
| BFS with distance | Track `dist[]` array | Shortest path unweighted |
| Multi-source BFS | Enqueue multiple sources initially | Rotten Oranges, 0/1 Matrix |
| BFS level-by-level | Process entire level before next | Level order tree traversal |
| Bidirectional BFS | BFS from both src and dst | Faster shortest path |

---

## 📚 Related Problems

- [ ] LeetCode #1971 — Find if Path Exists in Graph
- [ ] LeetCode #200 — Number of Islands (BFS on grid)
- [ ] LeetCode #994 — Rotting Oranges (multi-source BFS)
- [ ] LeetCode #542 — 0/1 Matrix (multi-source BFS)
- [ ] LeetCode #127 — Word Ladder (BFS on state graph)
- [ ] Striver Step 15 P09 — Rotten Oranges

---

## 🏆 Pattern Category

`Graphs` · `BFS` · `Shortest Path` · `Queue`

---

## 🎯 Difficulty Analysis

**Rating:** Medium (conceptually easy, but details matter)

**Why challenging:** The "mark visited on enqueue not dequeue" detail, handling disconnected graphs, and adapting to grid/state-space BFS problems require careful implementation.

---

## 📈 Progression Insight

**Harder BFS variants:**
- Multi-source BFS: enqueue multiple starting nodes simultaneously (Rotten Oranges, 0/1 Matrix)
- BFS on state space: each "state" is a node (Word Ladder — each word is a node)
- BFS with conditions: only traverse cells satisfying a condition (Binary Maze, Flood Fill)
- Bidirectional BFS: search from both ends simultaneously → O(b^(d/2)) instead of O(b^d)

---

## ⏱️ 30-Second Last-Minute Revision

> **BFS:** Queue. Mark visited on ENQUEUE. Dequeue → process → enqueue unvisited neighbors.  
> **Shortest path:** `dist[nb] = dist[curr] + 1` when enqueuing.  
> **Time:** O(V+E) | **Space:** O(V)  
> **Watch out for:** Mark visited BEFORE enqueue, not AFTER dequeue
