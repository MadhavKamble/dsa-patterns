# Floyd-Warshall Algorithm

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P35**

---

## Problem Understanding

**What is it asking?**
Given an `n×n` adjacency matrix where `-1` means no direct edge, find the **shortest distance between every pair of nodes** (all-pairs shortest path). Modify the matrix in-place.

**Input:** `matrix[][]` — adjacency matrix, `-1` for no edge
**Output:** Modified matrix with shortest distances (or `-1` if unreachable)

**Example:**
```
Input:
  0   25  -1  -1
  -1   0   5  -1
  -1  -1   0  20
  -1  -1  -1   0

Output:
  0   25  30  50
  -1   0   5  25
  -1  -1   0  20
  -1  -1  -1   0
```

**Key Observations:**
- All-pairs shortest path — not just from one source
- Works with negative weights (but not negative cycles)
- DP approach: `dist[i][j] = min(direct path, path through intermediate k)`
- Pre-process: `-1 → 1e9`, `matrix[i][i] = 0`
- Post-process: `1e9 → -1` (restore "unreachable")
- Triple nested loop: k (intermediate), then i, then j

---

## Core DP Idea

```
dist[i][j] = shortest path from i to j

After considering intermediates {0,1,...,k}:
  dist[i][j] = min(
    dist[i][j],          ← don't use k as intermediate
    dist[i][k] + dist[k][j]  ← go i→k then k→j
  )

Run k from 0 to n-1: each iteration "unlocks" node k as a potential intermediate.
After k=n-1: all nodes considered as intermediates → all shortest paths found.
```

---

## Optimal Approach — Floyd-Warshall DP

### Algorithm
1. Pre-process: `-1 → 1e9`, `matrix[i][i] = 0`
2. Triple loop — outer `k` (intermediate node 0 to n-1):
   - For each pair `(i,j)`: `matrix[i][j] = min(matrix[i][j], matrix[i][k]+matrix[k][j])`
3. Post-process: `1e9 → -1`

### Dry Run

**n=3, matrix: 0→1(3), 1→2(2), 0→2(7)**

```
After pre-process:
  [0,  3,  7]
  [1e9, 0, 2]
  [1e9,1e9, 0]

k=0 (intermediate = node 0):
  i=1,j=2: min(2, 1e9+7) = 2  (no change)
  i=2,j=1: min(1e9, 1e9+3) = 1e9  (no change)

k=1 (intermediate = node 1):
  i=0,j=2: min(7, 3+2) = 5  ← updated! 0→1→2 is shorter than 0→2

k=2:
  no further improvements

After post-process:
  [0, 3, 5]
  [1e9→-1, 0, 2]
  [1e9→-1, 1e9→-1, 0]

Final: [[0,3,5],[-1,0,2],[-1,-1,0]] ✅
```

### Complexity
- **Time:** O(V³) — three nested loops over V nodes
- **Space:** O(1) extra — in-place modification of input matrix

---

## Clean C++ Interview Code

```cpp
class Solution {
    public:
        void shortest_distance(vector<vector<int>>& matrix){
            int n=matrix.size();
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(matrix[i][j]==-1){
                        matrix[i][j]=1e9;
                    }
                    if(i==j) matrix[i][j]=0;
                }
            }
            for(int k=0;k<n;k++){
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        matrix[i][j]=min(matrix[i][j],matrix[i][k]+matrix[k][j]);
                    }
                }
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if(matrix[i][j]==(int)1e9){
                        matrix[i][j]=-1;
                    }
                }
            }
        }
};
```

> **Overflow note:** `matrix[i][k] + matrix[k][j]` can overflow if both are `(int)1e9 = 10^9`. Adding two gives `2×10^9` which is within int range (~2.1×10^9) — safe here. For safety in general, add a guard: `if(matrix[i][k]!=1e9 && matrix[k][j]!=1e9)` before relaxing.

---

## Handling Negative Cycles

```
A negative cycle is a cycle where the sum of edge weights is negative.
If node i is on a negative cycle: traveling i→...→i costs < 0 → dist[i][i] < 0.

After Floyd-Warshall, check the diagonal:
  for(int i=0;i<n;i++){
      if(matrix[i][i]<0){
          // negative cycle exists
      }
  }

Why the diagonal?
  matrix[i][i] starts at 0 (dist from i to i = 0).
  If after relaxation matrix[i][i] < 0:
    → there's a path i→...→i with negative total cost
    → that's a negative cycle through i.

In the user's code, this check is missing — for GFG problem the input is guaranteed no negative cycles. Add before post-processing if needed.
```

---

## Dijkstra vs Bellman-Ford vs Floyd-Warshall

| | Dijkstra | Bellman-Ford | Floyd-Warshall |
|--|----------|--------------|----------------|
| **Type** | Single-source | Single-source | All-pairs |
| **Time** | O((V+E) log V) | O(V×E) | O(V³) |
| **Space** | O(V) | O(V) | O(V²) |
| **Negative weights** | ❌ Wrong results | ✅ | ✅ |
| **Negative cycle detection** | ❌ | ✅ (Nth pass) | ✅ (`matrix[i][i] < 0`) |
| **Algorithm type** | Greedy | DP (edge-based) | DP (matrix-based) |
| **Data structure** | Priority queue | Edge list | Adjacency matrix |
| **Best for** | Dense/sparse graphs, non-neg weights | Negative weights, cycle detection | All-pairs, dense graphs |

### Negative Cycle Handling — Summary

```
Dijkstra:
  Cannot detect negative cycles.
  With negative edges, it may produce wrong distances or loop forever.
  Never use Dijkstra when negative edges are possible.

Bellman-Ford:
  Run V-1 relaxations normally.
  Nth relaxation: if any edge still relaxes → negative cycle reachable from src.
  Only detects cycles reachable from the source node.

Floyd-Warshall:
  After full algorithm: if matrix[i][i] < 0 → negative cycle through node i.
  Detects ALL negative cycles in the graph (not just from one source).
  After detection, distances involving nodes on/reachable from cycles are meaningless.
```

---

## Why `k` is the Outermost Loop

```
WRONG (k inner):
  for i: for j: for k:
    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j])

  When computing dist[i][j] via k, dist[i][k] might not yet use
  all intermediate nodes 0..k-1 → incorrect result.

CORRECT (k outer):
  for k: for i: for j:
    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j])

  When we process k as intermediate:
    dist[i][k] already has shortest path using intermediates {0..k-1} ✓
    dist[k][j] already has shortest path using intermediates {0..k-1} ✓
  → Combining them gives correct shortest path using {0..k} ✓
```

---

## Interview Explanation Script

> "Floyd-Warshall is a DP algorithm for all-pairs shortest paths. The idea: `dist[i][j]` = shortest path from i to j using any subset of nodes as intermediates. We incrementally add nodes as intermediates — for each new intermediate k, we check if going i→k→j is shorter than the current i→j."

> "The key insight is the loop order: k must be the outermost loop, so when we use k as an intermediate, `dist[i][k]` and `dist[k][j]` are already optimal over all previous intermediates."

> "To detect negative cycles: after the algorithm, check if `matrix[i][i] < 0` for any node. The diagonal starts at 0, so a negative value means there's a path from i back to i with negative cost — a negative cycle."

---

## Recall Line *(10-Second Revision)*

> "Floyd-Warshall: 3 loops k(outer),i,j. matrix[i][j]=min(matrix[i][j],matrix[i][k]+matrix[k][j]). O(V³). Neg cycle: matrix[i][i]<0."

---

## Short Revision Notes

- Pre-process: `-1→1e9`, `matrix[i][i]=0` before triple loop
- Post-process: `1e9→-1` after triple loop
- k is outermost — critical for correctness
- `(int)1e9 + (int)1e9 = 2e9` — within int range, no overflow for this problem
- Negative cycle check: `matrix[i][i] < 0` after the algorithm
- Modifies matrix in-place — no extra space needed

---

## Pattern Recognition Trigger

**When I see:**
- "Shortest distance between EVERY pair of nodes"
- "All-pairs shortest path"
- "Dense graph, O(V³) acceptable"

**I should think of:** Floyd-Warshall — 3 nested loops, k outermost

---

## Common Mistakes

❌ Making k the innermost loop — wrong DP order, incorrect results
❌ Not pre-processing: `-1` as infinity breaks `min()` comparisons
❌ Not setting `matrix[i][i]=0` — diagonal might be -1 (no self-loop in input)
❌ Overflow: `1e9 + 1e9 = 2e9` — safe for int, but use guard if weights are large
❌ Forgetting to post-process `1e9 → -1` — output has garbage infinity values

---

## What Interviewer Is Testing

- **Why k is outer loop** — DP order dependency
- **All-pairs vs single-source** — when to choose Floyd over Dijkstra/Bellman
- **Negative cycle detection** — diagonal check
- **Pre/post processing** of infinity representation

---

## Related Problems

- [ ] Striver Step 15 P26 — Dijkstra (single-source, non-negative)
- [ ] Striver Step 15 P34 — Bellman-Ford (single-source, negative weights)
- [ ] LeetCode #1334 — Find the City with Smallest Number of Neighbors (Floyd-Warshall + threshold)

---

## Pattern Category

`Graphs` · `All-Pairs Shortest Path` · `Dynamic Programming` · `Negative Weights` · `Matrix DP`

---

## 30-Second Last-Minute Revision

> **Floyd-Warshall:** Pre-process: `-1→1e9`, `matrix[i][i]=0`.
> Triple loop: k (outer), i, j → `matrix[i][j]=min(matrix[i][j], matrix[i][k]+matrix[k][j])`.
> Post-process: `1e9→-1`. Neg cycle: `matrix[i][i]<0` after algorithm.
> **Time:** O(V³) | **Use when:** all-pairs shortest path, negative weights ok.
> **k outermost** — non-negotiable for correctness.
