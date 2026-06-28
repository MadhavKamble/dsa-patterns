# Number of Ways to Arrive at Destination

> **LeetCode #1976** · **Difficulty:** Medium · **Step 15 — Graphs · P33**

---

## Problem Understanding

**What is it asking?**
Given `n` intersections and `roads[][]` (undirected weighted edges), count the **number of ways to travel from node 0 to node n-1 in the shortest possible time**. Return count modulo 10^9+7.

**Input:** `n`, `roads[][]` — each `[u, v, time]`
**Output:** Number of shortest paths from 0 to n-1, mod 10^9+7

**Example:**
```
n=7
roads: 0-6(7), 0-1(2), 1-2(3), 1-3(3), 6-3(3), 3-5(1), 6-5(2), 2-5(1), 0-4(5), 4-6(2)

Shortest path 0→6: time=7
Paths of length 7:
  0→6 (direct)
  0→1→2→5→6
  0→1→3→5→6
  0→4→6

Output: 4
```

**Key Observations:**
- Modified Dijkstra: track `dist[]` (shortest time) AND `ways[]` (count of shortest paths)
- When shorter path found: `ways[adj] = ways[node]` (reset — old count is obsolete)
- When equal path found: `ways[adj] = (ways[adj] + ways[node]) % mod` (accumulate)
- `dist` is `long long` (1e18 init) — road weights can be large
- `ways[0]=1` — exactly one way to be at the source

---

## The Two-Case Relaxation

```
Standard Dijkstra has one case:
  if (dis+w < dist[adj]): update dist, push

Here we have two cases:
  Case 1: dis+w < dist[adj]   → SHORTER path found
    dist[adj] = dis+w
    ways[adj] = ways[node]    ← reset: all previous paths to adj are now suboptimal
    push to heap

  Case 2: dis+w == dist[adj]  → EQUAL path found
    ways[adj] = (ways[adj] + ways[node]) % mod  ← accumulate
    (no push — dist[adj] unchanged, already in heap)
```

---

## Optimal Approach — Modified Dijkstra with Path Counting

### Algorithm
1. Build undirected adjacency list, `adj` uses `pair<int, long long>`
2. `dist[n]=1e18`, `ways[n]=0`, `dist[0]=0`, `ways[0]=1`
3. Push `{0, 0}` to min-heap (ordered by dist)
4. Stale skip: `if(dis > dist[node]) continue`
5. For each neighbor:
   - Shorter: update dist, reset ways, push
   - Equal: accumulate ways (no push needed)
6. Return `ways[n-1]`

### Dry Run

**n=4, roads: 0-1(1), 0-2(2), 1-3(2), 2-3(1)**

```
Init: dist=[0,1e18,1e18,1e18], ways=[1,0,0,0], pq={(0,0)}

Pop (0,0): not stale
  →1(w=1): 0+1=1 < 1e18 → dist[1]=1, ways[1]=1, push (1,1)
  →2(w=2): 0+2=2 < 1e18 → dist[2]=2, ways[2]=1, push (2,2)

Pop (1,1): not stale
  →0(w=1): 1+1=2 > dist[0]=0 → skip
  →3(w=2): 1+2=3 < 1e18 → dist[3]=3, ways[3]=1, push (3,3)

Pop (2,2): not stale
  →0(w=2): 2+2=4 > 0 → skip
  →3(w=1): 2+1=3 == dist[3]=3 → ways[3]=(1+1)%mod=2 (no push)

Pop (3,3): not stale (destination, but BFS continues)
  →1(w=2): 3+2=5 > 1 → skip
  →2(w=1): 3+1=4 > 2 → skip

ways[3]=2 → return 2 ✅
(Paths: 0→1→3 and 0→2→3, both cost 3)
```

### Complexity
- **Time:** O((V+E) log V) — Dijkstra with min-heap
- **Space:** O(V+E) — adjacency list + dist + ways arrays

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        vector<pair<int,long long>> adj[n];
        for(auto it: roads){
            adj[it[0]].push_back({it[1],it[2]});
            adj[it[1]].push_back({it[0],it[2]});
        }
        priority_queue<pair<long long,int>,
                       vector<pair<long long,int>>,
                       greater<pair<long long,int>>> pq;
        vector<long long> dist(n,1e18);
        vector<int> ways(n,0);
        dist[0]=0;
        ways[0]=1;
        pq.push({0,0});
        int mod=(int)(1e9+7);
        while(!pq.empty()){
            long long dis=pq.top().first;
            int node=pq.top().second;
            pq.pop();
            if(dis>dist[node]) continue;
            for(auto it: adj[node]){
                int adjNode=it.first;
                int edgeWeight=it.second;
                if(dis+edgeWeight<dist[adjNode]){
                    dist[adjNode]=dis+edgeWeight;
                    pq.push({dist[adjNode],adjNode});
                    ways[adjNode]=ways[node];
                }else if(dis+edgeWeight==dist[adjNode]){
                    ways[adjNode]=(ways[adjNode]+ways[node])%mod;
                }
            }
        }
        return ways[n-1];
    }
};
```

> **Note:** `edgeWeight` is declared `int` but `it.second` is `long long` (from `adj` type). For this problem road weights fit in int, but to be fully safe use `long long edgeWeight=it.second`.

---

## Why No Push on Equal Case?

```
Case 1 (shorter): dist[adj] changes → need new entry in heap with updated distance
Case 2 (equal):   dist[adj] unchanged → existing heap entry for adj is still valid
                  No need to push again — just update ways[adj]

If you push on equal case:
  → Duplicate entries with same dist → harmless but wasteful
  → Stale skip handles them, but avoid extra pushes
```

---

## Interview Explanation Script

> "This is Dijkstra extended with a `ways[]` array to count shortest paths. I maintain two things per node: the shortest distance, and how many ways I can reach it at that distance."

> "When I find a strictly shorter path to a neighbor, I reset `ways[adj] = ways[node]` — all previously known paths are now suboptimal. When I find an equal-length path, I add `ways[node]` to `ways[adj]` — it's a new valid shortest path."

> "I use `long long` for distances since road weights can be large. `ways[]` uses modulo 10^9+7 since the count can be huge."

---

## Recall Line *(10-Second Revision)*

> "Count shortest paths: Dijkstra + ways[]. Shorter → ways[adj]=ways[node]. Equal → ways[adj]+=ways[node]. Return ways[n-1]."

---

## Short Revision Notes

- `dist[]` is `long long` (use `1e18` init, not `1e9`) — edge weights can sum large
- `ways[0]=1`, `ways[i]=0` for i≠0
- Heap stores `{dist, node}` — note `long long` first in pair
- Equal case: accumulate `ways[adj]`, no push needed
- Shorter case: reset `ways[adj] = ways[node]` (not +=), then push
- `if(dis > dist[node]) continue` — stale skip same as standard Dijkstra
- Modulo only needed in the `ways[]` accumulation (addition), not assignment

---

## Dijkstra + Counting vs Standard Dijkstra

| | Standard Dijkstra | Count Paths Dijkstra |
|--|------------------|---------------------|
| Arrays | `dist[]` | `dist[]` + `ways[]` |
| Shorter case | update dist, push | update dist + `ways[adj]=ways[node]` + push |
| Equal case | — (no update) | `ways[adj]+=ways[node]` (no push) |
| Answer | `dist[dst]` | `ways[dst]` |
| `dist` type | `int` or `long long` | always `long long` |

---

## Pattern Recognition Trigger

**When I see:**
- "Count the number of shortest paths"
- "How many minimum-cost routes exist?"
- "Number of ways to reach destination optimally"

**I should think of:** Dijkstra + `ways[]` array, two-case relaxation (shorter vs equal)

---

## Common Mistakes

❌ Using `int` for `dist[]` — road weights can overflow
❌ `ways[adj] += ways[node]` in the shorter case — should be `=` (reset), not `+=`
❌ Pushing to heap in the equal case — unnecessary (dist unchanged)
❌ Forgetting `ways[0]=1` — source has exactly 1 way to reach itself
❌ Taking modulo on `dist[]` — only `ways[]` needs mod, not distances

---

## What Interviewer Is Testing

- **Two-case relaxation** — shorter (reset ways) vs equal (accumulate ways)
- **`long long` for distances** — overflow awareness
- **Modulo only on ways**, not distances
- Extension of Dijkstra beyond just shortest distance

---

## Related Problems

- [ ] Striver Step 15 P26 — Dijkstra (distance only)
- [ ] Striver Step 15 P31 — Network Delay Time (max of all distances)
- [ ] LeetCode #787 — Cheapest Flights K Stops
- [ ] LeetCode #1514 — Path with Maximum Probability

---

## Pattern Category

`Graphs` · `Dijkstra` · `Shortest Path` · `Path Counting` · `Priority Queue`

---

## 30-Second Last-Minute Revision

> **Count Shortest Paths:** Dijkstra + `ways[]`. `dist[]=1e18` (long long). `ways[0]=1`.
> Shorter: `dist[adj]=dis+w`, `ways[adj]=ways[node]`, push.
> Equal: `ways[adj]=(ways[adj]+ways[node])%mod`. No push.
> Stale skip: `if(dis>dist[node]) continue`.
> Return `ways[n-1]`. **Key:** shorter→reset, equal→accumulate.
