# 🔥 Graph Representation in Java

> **Conceptual + Implementation** · **Step 15 — Graphs · P03**

---

## 🧠 Problem Understanding

Same concepts as P02 (C++ representation), but using Java data structures.

---

## 📦 Adjacency List in Java

### Using ArrayList of ArrayLists (most common)

```java
// UNWEIGHTED GRAPH
int n = 5;
ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
for (int i = 0; i < n; i++)
    adj.add(new ArrayList<>());

// Add undirected edge
void addEdge(int u, int v) {
    adj.get(u).add(v);
    adj.get(v).add(u);
}

// Add directed edge
void addDirectedEdge(int u, int v) {
    adj.get(u).add(v);
}

// Iterate neighbors
for (int neighbor : adj.get(u)) {
    // process neighbor
}
```

```java
// WEIGHTED GRAPH — using int[][] or Pair class
ArrayList<int[]>[] adj = new ArrayList[n];  // int[] = {neighbor, weight}
for (int i = 0; i < n; i++)
    adj[i] = new ArrayList<>();

void addWeightedEdge(int u, int v, int w) {
    adj[u].add(new int[]{v, w});
    adj[v].add(new int[]{u, w});
}

// Iterate
for (int[] edge : adj[u]) {
    int v = edge[0], w = edge[1];
}
```

---

## 📦 Adjacency Matrix in Java

```java
// ADJACENCY MATRIX
int[][] adj = new int[n][n];

void addEdge(int u, int v) {
    adj[u][v] = 1;
    adj[v][u] = 1;  // remove for directed
}

boolean hasEdge(int u, int v) {
    return adj[u][v] != 0;
}
```

---

## 📦 Java Collections for Graph Algorithms

| Need | Java Collection |
|------|----------------|
| BFS queue | `Queue<Integer> q = new LinkedList<>()` |
| DFS stack | `Deque<Integer> st = new ArrayDeque<>()` |
| Priority queue (Dijkstra) | `PriorityQueue<int[]> pq = new PriorityQueue<>((a,b)->a[0]-b[0])` |
| Visited array | `boolean[] visited = new boolean[n]` |

---

## 💻 Standard Input Template (Competitive Programming)

```java
import java.util.*;
import java.io.*;

public class Main {
    static ArrayList<ArrayList<Integer>> adj;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());

        int n = Integer.parseInt(st.nextToken());  // vertices
        int m = Integer.parseInt(st.nextToken());  // edges

        adj = new ArrayList<>();
        for (int i = 0; i < n; i++)
            adj.add(new ArrayList<>());

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            adj.get(u).add(v);
            adj.get(v).add(u);  // undirected
        }
    }
}
```

---

## 📊 C++ vs Java Comparison

| Operation | C++ | Java |
|-----------|-----|------|
| Adjacency list | `vector<vector<int>>` | `ArrayList<ArrayList<Integer>>` |
| Weighted list | `vector<vector<pair<int,int>>>` | `ArrayList<int[]>[]` |
| Queue (BFS) | `queue<int>` | `Queue<Integer>` (LinkedList) |
| Priority Queue | `priority_queue` | `PriorityQueue<int[]>` |
| Visited | `vector<bool>` | `boolean[]` |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Java adjacency list: `ArrayList<ArrayList<Integer>>`, init each with `new ArrayList<>()`. Weighted: `ArrayList<int[]>[]`."

---

## 📝 Short Revision Notes

- Java: `ArrayList<ArrayList<Integer>>` for unweighted
- Java weighted: `ArrayList<int[]>[]` where `int[] = {neighbor, weight}`
- BFS: `Queue<Integer> q = new LinkedList<>()`
- Dijkstra PQ: `new PriorityQueue<>((a,b) -> a[0] - b[0])` — sort by distance
- No autoboxing overhead concern in interviews (use `int[]` not `Integer[]`)

---

## 🏆 Pattern Category

`Graphs` · `Data Structures` · `Representation`
