# Cheapest Flights Within K Stops

> **LeetCode #787** · **Difficulty:** Medium · **Step 15 — Graphs · P30**

---

## Problem Understanding

**What is it asking?**
Given `n` cities, `flights[][]` (directed edges `[from, to, price]`), `src`, `dst`, and `k`, find the **cheapest price** from `src` to `dst` with **at most `k` stops**. Return `-1` if no such route exists.

**Input:** `n`, `flights[][]`, `src`, `dst`, `k`
**Output:** Minimum cost, or `-1`

**Example:**
```
n=4, src=0, dst=3, k=1
flights: 0→1(100), 1→2(100), 2→3(100), 0→2(500), 0→3(600)

k=1 means at most 1 stop (at most 2 edges):
  0→3 direct: 600 (0 stops) ✓
  0→1→3: no edge 1→3
  0→2→3: 500+100=600 (1 stop) ✓

Answer: 600
```

**Key Observations:**
- "At most k stops" = at most k+1 edges in the path
- Directed graph (flights are one-way)
- BFS ordered by stops — not Dijkstra — because stops always increment by 1
- `dist[]` used for pruning but can't be the only gate — a costlier path with fewer stops may unlock a cheaper final route
- Do NOT early-return at destination — a later path with different stops may be cheaper

---

## Why BFS, Not Dijkstra?

```
Dijkstra processes by minimum cost → may reach dst early with too many stops.
Here we have TWO constraints: cost AND stops.

BFS by stops:
  - Level 0: paths using 0 stops (direct edges from src)
  - Level 1: paths using 1 stop
  - Level k: paths using k stops
  → Naturally processes all k-stop routes before (k+1)-stop routes
  → Avoids O(log N) heap push/pop — simpler regular queue
  → Stop constraint enforced by: if(stops>k) continue

Key: stop count increments by exactly 1 per BFS level → BFS ordering is valid.
Dijkstra would need (stops, cost) as key — just use BFS instead.
```

---

## Optimal Approach — BFS Ordered by Stops

### Key Observation

> Process nodes in order of stop count (not cost). BFS ensures we see all 0-stop routes before 1-stop, all 1-stop before 2-stop, etc. Prune with `dist[]` to avoid pushing clearly suboptimal paths. Skip nodes where `stops > k`.

### Algorithm
1. Build directed adjacency list from `flights`
2. Queue: `{stops, {node, cost}}`, init with `{0, {src, 0}}`
3. `dist[]=1e9`, `dist[src]=0`
4. BFS: if `stops > k` → skip (prune too-deep paths)
5. For each neighbor: if `cost+edgeWeight < dist[adjNode]` and `stops <= k` → update dist, push `{stops+1, {adjNode, new_cost}}`
6. Return `dist[dst]` or `-1`

### Dry Run

**n=4, k=1, src=0, dst=3**
**flights: 0→1(100), 1→2(100), 2→3(100), 0→2(500), 0→3(600)**

```
Init: dist=[0,1e9,1e9,1e9], queue={(0,{0,0})}

Pop (0,{0,0}): stops=0 ≤ k=1
  →1: 0+100=100 < dist[1]=1e9 → dist[1]=100, push (1,{1,100})
  →2: 0+500=500 < dist[2]=1e9 → dist[2]=500, push (1,{2,500})
  →3: 0+600=600 < dist[3]=1e9 → dist[3]=600, push (1,{3,600})

Pop (1,{1,100}): stops=1 ≤ k=1
  →2: 100+100=200 < dist[2]=500 → dist[2]=200, push (2,{2,200})

Pop (1,{2,500}): stops=1 ≤ k=1
  →3: 500+100=600, not < dist[3]=600 → skip

Pop (1,{3,600}): stops=1 ≤ k=1
  (no outgoing edges from 3)

Pop (2,{2,200}): stops=2 > k=1 → continue (skip)

dist[3]=600, return 600 ✅
```

### Complexity
- **Time:** O(V + E×K) — each edge processed at most K+1 times (once per stop level)
- **Space:** O(V + E) — adjacency list + queue

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<pair<int,int>> adj[n];
        for(auto it: flights){
            adj[it[0]].push_back({it[1],it[2]});
        }
        queue<pair<int,pair<int,int>>> q;
        q.push({0,{src,0}});
        vector<int> dist(n,1e9);
        dist[src]=0;
        while(!q.empty()){
            auto it=q.front();
            q.pop();
            int stops=it.first;
            int node=it.second.first;
            int cost=it.second.second;
            if(stops>k) continue;
            for(auto iter: adj[node]){
                int adjNode=iter.first;
                int edgeWeight=iter.second;
                if(cost+edgeWeight<dist[adjNode] && stops<=k){
                    dist[adjNode]=cost+edgeWeight;
                    q.push({stops+1,{adjNode,dist[adjNode]}});
                }
            }
        }
        if(dist[dst]==(int)1e9) return -1;
        return dist[dst];
    }
};
```

---

## Why We Can't Use Standard Dijkstra Alone

```
Dijkstra with just dist[] would give wrong answer:

Example: src=0, dst=2, k=1
  0→1 (cost=1), 1→2 (cost=1), 0→2 (cost=10)

Dijkstra pops (cost=1, node=1) first, then relaxes 2 to cost=2.
Later when it pops (cost=10, node=2 via direct)... already has dist[2]=2.
This seems fine, but consider:

  src=0, dst=2, k=0 (zero stops = direct edge only)
  Dijkstra might take 0→1→2 (2 stops) if it's cheaper, violating k=0.

BFS by stops naturally enforces the stop constraint level by level.
```

---

## The `dist[]` Pruning Subtlety

```
We update dist[adjNode] = cost+edgeWeight when it's cheaper.
But we DON'T skip if a node was already visited — because:

  A node may be reachable cheaply via many stops,
  AND also reachable expensively via fewer stops.
  
  The expensive+few-stops path may still be useful for reaching dst within k.

dist[] is a PRUNING optimization (skip clearly worse paths),
NOT a "visited" marker like in standard BFS/Dijkstra.

Both conditions must hold: cost+edgeWeight < dist[adjNode] AND stops <= k
```

---

## Interview Explanation Script

> "I use BFS ordered by stop count instead of Dijkstra. Since each edge adds exactly 1 stop, BFS naturally processes all 0-stop paths, then 1-stop, then 2-stop, etc. This gives O(E×K) time vs Dijkstra's O(E log V) — and simpler code."

> "I use `dist[]` as a pruning array: if the new cost to a neighbor isn't better than what we've already found, skip it. And I prune with `if(stops > k) continue` to not explore beyond the allowed depth."

> "I don't stop when reaching dst because a different path with a different number of stops might give a cheaper answer."

---

## Recall Line *(10-Second Revision)*

> "K stops: BFS not Dijkstra. Queue={stops,{node,cost}}. if(stops>k) skip. Relax if cheaper AND stops≤k. O(E×K)."

---

## Short Revision Notes

- Queue: `{stops, {node, cost}}` — stops first so we can check the k limit
- Init: `dist[src]=0`, push `{0, {src, 0}}`
- `if(stops > k) continue` — prune; don't process further from here
- Second check `stops <= k` in relaxation is redundant (covered by `if(stops>k) continue`) but harmless
- Directed graph → adjacency list built one-way only
- Don't early-return at dst — not guaranteed to have cheapest cost yet (could come via fewer stops)
- `dist[dst]==(int)1e9` for return check — cast avoids float comparison

---

## BFS vs Dijkstra for This Problem

| | BFS (stops-ordered) | Dijkstra |
|--|---------------------|----------|
| Queue | Regular queue | Min-heap |
| Order | By stop count | By cost |
| Time | O(E×K) | O((V+E)logV) but may give wrong answer without stop tracking |
| Stop constraint | `if(stops>k) continue` | Need to track stops in state |
| Correctness | Correct | Correct only if state = (node, stops) |

---

## Pattern Recognition Trigger

**When I see:**
- "Shortest path with at most K edges/hops/stops"
- "Constrained Dijkstra" — extra dimension limits path exploration
- "Cheapest/shortest with bounded depth"

**I should think of:** BFS by constraint level (not cost), not standard Dijkstra

---

## Common Mistakes

❌ Using Dijkstra — will not respect k-stop limit without tracking stops in heap state
❌ Early return when node == dst — might miss cheaper path via different stop count
❌ Building undirected adjacency list — flights are directed
❌ Using `dist[]` as visited marker and skipping already-seen nodes — may miss valid paths with fewer stops
❌ Off-by-one: "k stops" = k+1 edges; `stops` in queue counts edges, not nodes

---

## What Interviewer Is Testing

- **Why BFS over Dijkstra** — understanding stop constraint ordering
- **Not early-returning at dst** — multiple paths may reach it
- **`dist[]` as pruning, not visited** — subtle but important
- **Directed graph** construction

---

## Related Problems

- [ ] Striver Step 15 P26 — Dijkstra's Algorithm (no stop constraint)
- [ ] LeetCode #743 — Network Delay Time (Dijkstra, no stop constraint)
- [ ] LeetCode #1514 — Path with Maximum Probability (modified Dijkstra)

---

## Pattern Category

`Graphs` · `BFS` · `Shortest Path` · `Constrained Traversal` · `Directed Graph`

---

## 30-Second Last-Minute Revision

> **Cheapest K Stops:** BFS (not Dijkstra). Queue = `{stops, {node, cost}}`.
> `dist[]=1e9`, `dist[src]=0`. Push `{0,{src,0}}`.
> Pop → if `stops>k` → skip. Relax neighbors: `cost+w < dist[adj]` → update + push `{stops+1,...}`.
> Return `dist[dst]` or `-1`.
> **Key:** BFS by stops (not cost). Don't stop at dst mid-BFS. dist[] = pruning, not visited.
