# Find the City with Smallest Number of Neighbours at Threshold Distance

> **LeetCode #1334** · **Difficulty:** Medium · **Step 15 — Graphs · P36**

---

## Problem Understanding

**What is it asking?**
Given `n` cities (0-indexed), `edges[][]` (undirected weighted), and a `distanceThreshold`, find the city that has the **fewest cities reachable within the threshold distance**. If tie → return the city with the **greatest index**.

**Input:** `n`, `edges[][]` — each `[u, v, weight]`, `distanceThreshold`
**Output:** City index

**Example:**
```
n=4, distanceThreshold=4
edges: 0-1(3), 1-2(1), 1-3(4), 2-3(1)

All-pairs shortest distances:
    0  1  2  3
0 [ 0, 3, 4, 4]
1 [ 3, 0, 1, 2]
2 [ 4, 1, 0, 1]
3 [ 4, 2, 1, 0]

Cities reachable within threshold=4 (including self at dist=0):
  City 0: {0(0),1(3),2(4),3(4)} → cnt=4
  City 1: {0(3),1(0),2(1),3(2)} → cnt=4
  City 2: {1(1),2(0),3(1)}      → cnt=4 (0 is dist=4 so cnt=4)
  City 3: {1(2),2(1),3(0)}      → cnt=3 (0 is dist=4, so still included → cnt=4)

Minimum cnt with largest index → Output: 3
```

**Key Observations:**
- Floyd-Warshall gives all-pairs shortest paths — exactly what we need
- After Floyd-Warshall: scan each city, count how many are within threshold
- Tie-breaking: iterate cities 0→n-1 with `<=` update → last city with minimum count wins (highest index)
- `dist[city][city]=0` always ≤ threshold, so every city counts itself — uniform across all cities, answer still correct

---

## Optimal Approach — Floyd-Warshall + Threshold Scan

### Algorithm
1. Init `dist[n][n]=1e9`, fill edges (undirected), set diagonal to 0
2. Floyd-Warshall: triple loop k(outer),i,j
3. Scan each city: count how many cities have `dist[city][adjCity] <= threshold`
4. Track `(min count, max city index)` using `<=` update condition

### Dry Run

**n=3, threshold=3, edges: 0-1(2), 1-2(2), 0-2(6)**

```
After edge fill:
  [0, 2, 6]
  [2, 0, 2]
  [6, 2, 0]

Floyd-Warshall:
  k=0: dist[1][2]=min(2, dist[1][0]+dist[0][2])=min(2,2+6)=2 (no change)
       dist[2][1]=min(2, 6+2)=2 (no change)
  k=1: dist[0][2]=min(6, dist[0][1]+dist[1][2])=min(6,2+2)=4 ← updated
       dist[2][0]=min(6, 2+2)=4 ← updated
  k=2: no improvements

Final dist:
  [0, 2, 4]
  [2, 0, 2]
  [4, 2, 0]

Count within threshold=3:
  City 0: dist=0(self),2(city1) → cnt=2  (city2 dist=4 > 3)
  City 1: dist=2,0(self),2      → cnt=3
  City 2: dist=4,2,0(self)      → cnt=2  (city0 dist=4 > 3)

cntCity starts at n=3
city=0: cnt=2 <= 3 → cntCity=2, cityNo=0
city=1: cnt=3 not <= 2 → skip
city=2: cnt=2 <= 2 → cntCity=2, cityNo=2 (tie → update to higher index)

return 2 ✅
```

### Complexity
- **Time:** O(V³) — Floyd-Warshall dominates; threshold scan is O(V²)
- **Space:** O(V²) — `dist[][]` matrix

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>> dist(n,vector<int>(n,1e9));
        for(auto it: edges){
            dist[it[0]][it[1]]=it[2];
            dist[it[1]][it[0]]=it[2];
        }
        for(int i=0;i<n;i++){
            dist[i][i]=0;
        }
        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
        int cntCity=n;
        int cityNo=-1;
        for(int city=0;city<n;city++){
            int cnt=0;
            for(int adjCity=0;adjCity<n;adjCity++){
                if(dist[city][adjCity]<=distanceThreshold)
                    cnt++;
            }
            if(cnt<=cntCity){
                cntCity=cnt;
                cityNo=city;
            }
        }
        return cityNo;
    }
};
```

---

## The `<=` Tie-Breaking Trick

```
if(cnt <= cntCity):  ← note: <= not <

Iterating city from 0 to n-1:
  - On strict tie (cnt == cntCity): we update cityNo to the current city
  - Since we iterate forward (0→n-1), the last update on a tie is the highest index
  
This naturally gives us the city with greatest index when counts are equal.

Using < instead of <=:
  - Would keep the FIRST city with minimum count (lowest index) — wrong answer
```

---

## Why Floyd-Warshall Here, Not Dijkstra?

```
We need shortest distance between EVERY pair of cities.

Option 1: Run Dijkstra from each city → O(n × (V+E)logV)
  → n separate Dijkstra runs, more code

Option 2: Floyd-Warshall → O(V³) in one pass
  → Single algorithm, cleaner code
  → For n=100 (constraint): 100³ = 10^6 → fast enough

When n is small and all-pairs needed → Floyd-Warshall wins on simplicity.
```

---

## Interview Explanation Script

> "I need shortest distances between all city pairs — Floyd-Warshall is the natural fit. One O(V³) pass gives me the full distance matrix."

> "Then I scan each city and count how many others are within the threshold. I initialize `cntCity = n` (worst case) and update with `<=` to handle ties: since I scan cities 0→n-1, updating on tie naturally keeps the highest-indexed city when counts are equal."

> "The city itself always has dist[i][i]=0 ≤ threshold, so it's included in its own count — but this is uniform across all cities, so the relative comparison is correct."

---

## Recall Line *(10-Second Revision)*

> "Find city: Floyd-Warshall for all-pairs. Count cities within threshold per city. Update with <= for tie → largest index wins."

---

## Short Revision Notes

- Floyd-Warshall init: fill edges both ways (undirected), then set diagonal to 0
- k as outermost loop — mandatory (P35 rule applies here too)
- `dist[i][k]+dist[k][j]` overflow: `(int)1e9 + (int)1e9 = 2e9` — safe in int range
- `cnt<=cntCity` (not `<`) — gives highest-index city on tie
- `cntCity = n` init — any real city will have cnt ≤ n
- Self-count: dist[i][i]=0 always included; harmless since uniform

---

## Pattern Recognition Trigger

**When I see:**
- "For each node, count reachable neighbors within some limit"
- "All-pairs shortest path on small graph (n ≤ 200)"
- "Floyd-Warshall + post-processing scan"

**I should think of:** Floyd-Warshall → scan matrix row by row with threshold condition

---

## Common Mistakes

❌ Using `<` instead of `<=` in update → returns lowest-index city on tie, not highest
❌ Setting `cntCity = 0` instead of `n` — no city would ever update
❌ Not setting diagonal to 0 — `dist[i][i]` stays `1e9`, city never counts itself
❌ Forgetting undirected: adding edge only one way → asymmetric distance matrix
❌ k as innermost loop (P35 mistake) — wrong DP result

---

## What Interviewer Is Testing

- **Floyd-Warshall application** — recognizing all-pairs need
- **Tie-breaking with `<=`** — subtle but critical for correct answer
- **k outermost loop** — same as P35, reinforcing DP order
- **When to choose Floyd vs Dijkstra** — all-pairs + small n

---

## Related Problems

- [ ] Striver Step 15 P35 — Floyd-Warshall (core algorithm)
- [ ] LeetCode #743 — Network Delay Time (single-source Dijkstra)
- [ ] LeetCode #1462 — Course Schedule IV (reachability, Floyd-Warshall)

---

## Pattern Category

`Graphs` · `All-Pairs Shortest Path` · `Floyd-Warshall` · `Threshold Query`

---

## 30-Second Last-Minute Revision

> **Find City:** Floyd-Warshall on `dist[n][n]` (init 1e9, edges both ways, diag=0).
> Triple loop k,i,j: `dist[i][j]=min(dist[i][j], dist[i][k]+dist[k][j])`.
> Scan: for each city, `cnt` = cities with `dist<=threshold`.
> Update: `if(cnt<=cntCity)` → ties go to higher index. Return `cityNo`.
> **Time:** O(V³) | **Key:** `<=` not `<` for tie-breaking.
