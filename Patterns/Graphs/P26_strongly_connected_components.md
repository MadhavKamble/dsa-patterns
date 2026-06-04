# Pattern 26: Strongly Connected Components (SCC)

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 1192. Critical Connections in a Network | Hard | https://leetcode.com/problems/critical-connections-in-a-network/ |
| 2 | 802. Find Eventual Safe States | Medium | https://leetcode.com/problems/find-eventual-safe-states/ |

---

## 1. First-Timer Explanation

### What is this pattern?
A **Strongly Connected Component (SCC)** in a directed graph is a maximal set of nodes where every node is reachable from every other node in the set.

**Kosaraju's Algorithm (two-pass DFS):**
1. Run DFS on original graph; push nodes to stack in finish-time order (postorder)
2. Transpose (reverse all edges) the graph
3. Pop nodes from stack; run DFS on transposed graph — each DFS launch = one SCC

**Tarjan's Algorithm (single-pass DFS):**
- Track discovery time `disc[]` and low-link value `low[]`
- `low[u]` = earliest discovered node reachable from u's subtree
- If `low[u] == disc[u]` → u is the root of an SCC → pop stack until u

**Interview-friendly version**: Kosaraju is easier to explain; Tarjan is more efficient (single pass).

**Safe Nodes (LC 802):** A node is "safe" if all paths from it lead to a terminal (no cycle). Nodes NOT in any cycle are safe → find SCCs of size 1 with no self-loops.

### Visual Walkthrough
```
Graph: A→B, B→C, C→A, C→D, D→E, E→D

SCCs:
  {A, B, C} — all reachable from each other (cycle)
  {D, E}    — D→E→D (cycle)

Kosaraju:
  Pass 1 (DFS on original): finish order = A, B, C, D, E
    → stack bottom-to-top: [E, D, C, B, A] (last finished = first popped)
  Reverse edges: B→A, C→B, A→C, D→C, E→D
  Pass 2 (DFS on reversed, pop from stack):
    Pop A: DFS in reversed → reaches B, C → SCC {A, B, C}
    Pop D: DFS in reversed → reaches E → SCC {D, E}
```

### When TO use this pattern
- Find all cycles in a directed graph
- Condense graph to DAG (each SCC becomes one node)
- "Safe nodes" — nodes not on any cycle
- Solve 2-SAT problems (SCC on implication graph)
- Detect circular dependencies in module systems

### When NOT to use this pattern
- Undirected graph (just connected components — use DFS/UF)
- Simple cycle detection (3-color DFS is simpler)
- Just need one cycle (not all SCCs)

### Common Beginner Mistakes
- **Kosaraju finish order**: stack the node AFTER all its neighbors finish (postorder push)
- **Transpose graph**: reverse ALL edges — build a separate adjacency list
- **Safe nodes**: nodes in SCCs of size > 1 are unsafe; also nodes with self-loops; but a size-1 SCC with an outgoing edge to another cycle is also unsafe
- **Low-link in Tarjan**: only update from back edges (not from cross edges to already-completed SCCs)

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "strongly connected", "condensation", "2-SAT", "safe nodes", "circular dependency" |
| Core Idea | Kosaraju: two DFS passes (forward + reversed). Tarjan: single DFS with disc/low arrays |
| Trigger Keywords | "SCC", "strongly connected", "safe states", "all cycles in directed graph" |
| Avoid When | Undirected graph (use DFS/UF), simple cycle check (3-color DFS) |
| Time Complexity | O(V + E) |
| Space Complexity | O(V + E) |

**Gotchas:**
- Kosaraju: push to finish stack in postorder (after all children finish)
- Safe nodes: reverse edges, then find nodes with in-degree 0 (Kahn's) in reversed graph — those are safe
- Tarjan low-link: only update via gray nodes (nodes still on stack), not black ones

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"strongly connected components"` → Kosaraju or Tarjan
- `"safe states"` / `"eventual safe"` → nodes not in any cycle
- `"critical connections"` / `"bridges"` → Tarjan's bridge-finding (related but not SCC)
- `"2-SAT"` → SCC on implication graph
- `"condensation DAG"` → collapse SCCs into single nodes

---

## 4. C++ Template

```cpp
/*
 * Pattern: Strongly Connected Components
 * Time: O(V+E) | Space: O(V+E)
 */

// KOSARAJU'S ALGORITHM
vector<vector<int>> kosaraju(int n, vector<vector<int>>& adj) {
    // Pass 1: DFS on original, push nodes in finish order
    vector<bool> visited(n, false);
    stack<int> finishOrder;
    function<void(int)> dfs1 = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) if (!visited[v]) dfs1(v);
        finishOrder.push(u);
    };
    for (int i = 0; i < n; i++) if (!visited[i]) dfs1(i);

    // Build transposed graph
    vector<vector<int>> radj(n);
    for (int u = 0; u < n; u++)
        for (int v : adj[u]) radj[v].push_back(u);

    // Pass 2: DFS on transposed in reverse finish order
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> sccs;
    function<void(int, vector<int>&)> dfs2 = [&](int u, vector<int>& comp) {
        visited[u] = true;
        comp.push_back(u);
        for (int v : radj[u]) if (!visited[v]) dfs2(v, comp);
    };
    while (!finishOrder.empty()) {
        int u = finishOrder.top(); finishOrder.pop();
        if (!visited[u]) {
            sccs.emplace_back();
            dfs2(u, sccs.back());
        }
    }
    return sccs;
}

// TARJAN'S SCC
vector<vector<int>> tarjanSCC(int n, vector<vector<int>>& adj) {
    vector<int> disc(n, -1), low(n), comp(n, -1);
    vector<bool> onStack(n, false);
    stack<int> stk;
    int timer = 0, sccId = 0;
    vector<vector<int>> sccs;

    function<void(int)> dfs = [&](int u) {
        disc[u] = low[u] = timer++;
        stk.push(u); onStack[u] = true;
        for (int v : adj[u]) {
            if (disc[v] == -1) { dfs(v); low[u] = min(low[u], low[v]); }
            else if (onStack[v]) low[u] = min(low[u], disc[v]);
        }
        if (low[u] == disc[u]) {  // u is root of an SCC
            sccs.emplace_back();
            while (true) {
                int v = stk.top(); stk.pop();
                onStack[v] = false;
                comp[v] = sccId;
                sccs.back().push_back(v);
                if (v == u) break;
            }
            sccId++;
        }
    };

    for (int i = 0; i < n; i++) if (disc[i] == -1) dfs(i);
    return sccs;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll use Kosaraju's two-pass algorithm. In the first DFS on the original graph, I push nodes to a stack as they finish — this gives nodes in reverse topological order of the condensed DAG. Then I transpose all edges and run DFS from the stack's top. Each DFS launch on the transposed graph visits exactly one SCC, because in the reversed graph, the SCC that was 'last to finish' in pass 1 has no incoming edges from other SCCs."

### Interview Flow Checklist
- [ ] Build adjacency list
- [ ] Pass 1: DFS, push to stack in postorder
- [ ] Build transposed graph
- [ ] Pass 2: pop from stack, DFS on transposed — each launch = one SCC
- [ ] Collect SCC members per launch

---

## 6. Problems

---

### Problem 1: 802. Find Eventual Safe States
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-eventual-safe-states/
**Why this pattern fits:** Safe nodes = nodes NOT on any cycle = nodes in size-1 SCCs with no self-edges, OR simpler: reverse graph + Kahn's BFS from terminals

**Optimal C++ Solution (reverse + Kahn's):**
```cpp
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> radj(n);
    vector<int> outdegree(n, 0);
    for (int u = 0; u < n; u++) {
        outdegree[u] = graph[u].size();
        for (int v : graph[u]) radj[v].push_back(u);
    }
    // terminal nodes (no outgoing edges) are safe; propagate backward
    queue<int> q;
    for (int i = 0; i < n; i++) if (outdegree[i] == 0) q.push(i);
    vector<bool> safe(n, false);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        safe[u] = true;
        for (int v : radj[u])
            if (--outdegree[v] == 0) q.push(v);
    }
    vector<int> result;
    for (int i = 0; i < n; i++) if (safe[i]) result.push_back(i);
    return result;
}
```
**Edge Cases:** [ ] All nodes safe (no cycles), [ ] All nodes in one big cycle

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 1192. Critical Connections in a Network
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/critical-connections-in-a-network/
**Why this pattern fits:** Bridge finding — edge not part of any cycle = bridge = critical connection (Tarjan's bridge algorithm, related to SCC)

**Optimal C++ Solution:**
```cpp
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto& c : connections) { adj[c[0]].push_back(c[1]); adj[c[1]].push_back(c[0]); }

    vector<int> disc(n, -1), low(n);
    int timer = 0;
    vector<vector<int>> bridges;

    function<void(int,int)> dfs = [&](int u, int parent) {
        disc[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == parent) continue;  // skip the edge we came from
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) bridges.push_back({u, v});  // bridge condition
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };

    dfs(0, -1);
    return bridges;
}
```
**Edge Cases:** [ ] Multiple edges between same pair (use edge ID to avoid treating reverse edge as back edge)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> In a directed graph of software modules, find all modules that are part of circular import chains.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** SCC — find all SCCs with size > 1 (or size 1 with self-loop)
**Reason:** A circular import = cycle in directed dependency graph. Any node in an SCC of size > 1 participates in a cycle. Run Kosaraju/Tarjan, collect all SCCs with |SCC| > 1, and return all their members.
</details>

---

**Drill 2:**
> Given a directed graph, condense it to a DAG where each SCC becomes a single "super-node." Count the number of super-nodes with in-degree 0.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** SCC + condensation
**Reason:** Find all SCCs (Tarjan gives SCC IDs). Build condensed DAG: for each edge u→v in original where SCC(u) ≠ SCC(v), add edge SCC(u) → SCC(v). Count super-nodes with in-degree 0. Relevant for finding "source" modules in dependency graphs.
</details>

---

**Drill 3:**
> In a game, each room has one-way passages. Determine which rooms can be "escaped from" (can reach the exit) and which trap you in a loop.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Safe nodes (802 variant)
**Reason:** "Trapped in loop" = node on a cycle. "Can escape" = node that can reach the exit without entering a cycle. Reverse graph approach: mark exit as safe, propagate backward. Nodes that can reach safety in the reversed graph = safe nodes in original.
</details>

---

**Drill 4:**
> 2-SAT: given n boolean variables and clauses of the form "(A OR B)", find a satisfying assignment or report it's impossible.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** SCC on implication graph
**Reason:** Each clause (A OR B) becomes implications: (NOT A → B) and (NOT B → A). Build implication graph, find SCCs. If any variable x and its negation NOT_x are in the same SCC → unsatisfiable. Otherwise, assign based on SCC topological order (variable in later SCC = true).
</details>

---

**Drill 5:**
> Given a directed graph, find the minimum number of edges to add to make it strongly connected.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** SCC condensation + in-degree/out-degree analysis
**Reason:** Condense SCCs to DAG. Count super-nodes with in-degree 0 (no incoming) = p, and out-degree 0 (no outgoing) = q. Answer = max(p, q). Edge case: if already 1 SCC, answer = 0.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Kosaraju's SCC | O(V+E) | O(V+E) | Two DFS passes + transposed graph |
| Tarjan's SCC | O(V+E) | O(V) | Single DFS with stack |
| Bridge finding | O(V+E) | O(V) | Tarjan variant with low-link |
| Safe nodes (Kahn's reverse) | O(V+E) | O(V) | Simpler than full SCC |

---

## 9. Common Follow-up Questions

1. What's the difference between SCC and connected components? (SCC: directed graph — every node reachable from every other. CC: undirected — any path exists. In undirected, every CC is an SCC)
2. Which algorithm is preferred in interviews — Kosaraju or Tarjan? (Kosaraju is easier to explain; Tarjan is single-pass and more elegant. Either is fine)
3. How to find bridges vs SCCs? (Bridges: edge (u,v) is bridge if low[v] > disc[u]. SCCs: node u is SCC root if low[u] == disc[u]. Both use Tarjan-style disc/low arrays)
4. What's the condensation DAG used for? (Any problem on directed graph can be reduced to DAG by condensing SCCs. Then apply DP/topo sort on the simpler DAG structure)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Topological Sort | SCC condensation → DAG → topo sort | 802. Safe Nodes (Kahn's on reversed) |
| DFS + Stack | Both Kosaraju and Tarjan | Core SCC algorithms |
| Cycle Detection | SCCs generalize cycle detection | 207. Course Schedule (simpler version) |
| 2-SAT | Implication graph → SCC | Advanced competitive programming |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
