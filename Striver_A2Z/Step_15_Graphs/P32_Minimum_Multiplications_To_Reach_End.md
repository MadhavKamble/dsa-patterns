# Minimum Multiplications to Reach End

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P32**

---

## Problem Understanding

**What is it asking?**
Given an array `arr[]`, a `start` value, and an `end` value, find the **minimum number of multiplications** needed to convert `start` to `end`. Each step: multiply current number by any element in `arr`, then take modulo 100000. Return `-1` if impossible.

**Input:** `arr[]`, `start`, `end`
**Output:** Minimum steps, or `-1`

**Example:**
```
arr=[2,5,7], start=3, end=30

Step 1: 3×2=6 (mod 100000 = 6) — or 3×5=15, 3×7=21
Step 2: 6×5=30 ✓

Output: 2
```

**Key Observations:**
- State = current number (after mod 1000)
- BFS gives minimum steps because each multiplication = exactly 1 step (unit cost)
- Mod 1000 means at most 1000 distinct states → bounded state space
- `dist[]` of size 1000 — one entry per possible state
- `1LL * it * node` before mod — prevents integer overflow
- Early return on reaching `end`

---

## Why BFS (Not Dijkstra)?

```
Each multiplication costs exactly 1 step → unit weight graph.
BFS guarantees shortest path in O(V+E) without a priority queue.

State graph:
  Nodes = numbers 0..999 (mod space)
  Edges = multiply by arr[i] → new state (mod 1000)
  Edge weight = 1 (always)

→ BFS is correct and optimal here.
  Dijkstra would work but adds unnecessary O(log V) overhead.
```

---

## Optimal Approach — BFS on Mod-1000 State Space

### Key Observation

> After modulo 1000, the state space is bounded to [0, 999]. BFS explores states in order of step count (minimum steps first). The first time we reach `end`, it's via the minimum number of multiplications.

### Algorithm
1. Handle edge case: `start == end` → return `0`
2. `dist[1000]=1e9`, `dist[start]=0`, queue `{start, 0}`
3. BFS: for each state `node`, try multiplying by every element in `arr`
   - `num = (1LL * it * node) % mod`
   - If `steps+1 < dist[num]`: update dist, early return if `num==end`, else push
4. Queue exhausted → return `-1`

### Dry Run

**arr=[3,7], start=4, end=24, mod=100 (simplified)**

```
Init: dist[4]=0, queue={(4,0)}

Pop (4,0):
  ×3: (3×4)%100=12, 0+1=1<1e9 → dist[12]=1, push (12,1)
  ×7: (7×4)%100=28, 0+1=1<1e9 → dist[28]=1, push (28,1)

Pop (12,1):
  ×3: (3×12)%100=36, 1+1=2<1e9 → dist[36]=2, push (36,2)
  ×7: (7×12)%100=84, 1+1=2<1e9 → dist[84]=2, push (84,2)

Pop (28,1):
  ×3: (3×28)%100=84, 2 not < dist[84]=2 → skip
  ×7: (7×28)%100=96, 1+1=2<1e9 → dist[96]=2, push (96,2)

...
(continuing until 24 is reached)
```

**With actual arr=[2,5,7], start=3, end=30, mod=1000:**
```
Pop (3,0): ×2→6(push), ×5→15(push), ×7→21(push)
Pop (6,1): ×2→12, ×5→30 → 30==end → return 2 ✅
```

### Complexity
- **Time:** O(1000 × |arr|) — at most 1000 states × arr size transitions
- **Space:** O(1000) — dist array + queue bounded by state space

---

## Clean C++ Interview Code

```cpp
class Solution {
  public:
    int minSteps(vector<int>& arr, int start, int end) {
        if(start==end)
            return 0;
        queue<pair<int,int>> q;
        q.push({start,0});
        vector<int> dist(1000,1e9);
        dist[start]=0;
        int mod=1000;
        while(!q.empty()){
            int node=q.front().first;
            int steps=q.front().second;
            q.pop();
            for(auto it: arr){
                int num=(1LL*it*node)%mod;
                if(steps+1<dist[num]){
                    dist[num]=steps+1;
                    if(num==end)
                        return steps+1;
                    q.push({num,steps+1});
                }
            }
        }
        return -1;
    }
};
```

---

## The `1LL` Overflow Guard

```
it and node are both int. arr[i] can be up to 10^4, node up to 999.
  10^4 × 999 = ~10^7 → fits in int (max ~2×10^9) barely.

But to be safe:
  1LL * it * node   ← promotes to long long before multiplication
  then % mod        ← result fits in int after mod

Without 1LL: if arr elements or node values are large, it*node
might overflow int silently → wrong modulo result.
```

---

## Interview Explanation Script

> "This is BFS on an implicit graph where each node is a number mod 1000. Each edge is 'multiply by arr[i]' and costs 1 step. BFS gives minimum steps because all edges have unit cost."

> "The state space is bounded to [0, 999] by the modulo — so BFS runs in O(1000 × |arr|) time. I use `dist[]` as both a visited marker and a minimum-steps tracker."

> "Early return when `num == end` on enqueue — BFS guarantees this is the shortest path."

---

## Recall Line *(10-Second Revision)*

> "Min multiplications: BFS, state=num%1000. dist[1000]. num=(1LL*it*node)%1000. steps+1<dist[num] → update+push. num==end → return."

---

## Short Revision Notes

- `start==end` edge case → return 0 before BFS
- `dist[1000]` not `dist[n]` — indexed by number mod 1000, not by input index
- `1LL * it * node` prevents int overflow before `% mod`
- Early return on `num==end` — BFS guarantees minimum steps on first reach
- State space is exactly 1000 → O(1000) space regardless of input size
- Directed implicit graph — multiply is one operation, not reversible implicitly

---

## Comparison: This vs Other BFS Shortest Path Problems

| Problem | State | Edge | State space |
|---------|-------|------|-------------|
| Binary Maze (P28) | `{row,col}` | Move to adjacent cell | n×m |
| Word Ladder (P24) | `string` | Change 1 char | N words |
| **Min Multiplications (P32)** | `num % 1000` | Multiply by arr[i] | 1000 |
| Cheapest K Stops (P30) | `{node,stops}` | Follow edge | V×K |

---

## Pattern Recognition Trigger

**When I see:**
- "Minimum operations to transform X to Y"
- "State changes with unit cost, bounded state space"
- "Implicit graph BFS with modular arithmetic"

**I should think of:** BFS on state space, `dist[]` indexed by state

---

## Common Mistakes

❌ Using Dijkstra — unnecessary for unit-cost transitions
❌ `dist[n]` where n = arr size — should be `dist[1000]` (state = mod value)
❌ `it * node` without `1LL` — potential int overflow before mod
❌ Not handling `start == end` → would return -1 (dist[start]=0, never pushed as result)
❌ Missing early return at `num==end` — functionally okay but wastes BFS iterations

---

## What Interviewer Is Testing

- **State space recognition** — state is `num % 1000`, not the input values
- **BFS for unit-cost implicit graph** — choosing BFS over Dijkstra
- **Overflow awareness** — `1LL *` before multiply
- **Bounded state space** — why O(1000 × |arr|) is acceptable

---

## Related Problems

- [ ] LeetCode #127 — Word Ladder (BFS on implicit graph, string states)
- [ ] Striver Step 15 P28 — Binary Maze (BFS on grid)
- [ ] LeetCode #752 — Open the Lock (BFS, state = 4-digit combo, mod 10)

---

## Pattern Category

`Graphs` · `BFS` · `Implicit Graph` · `State Space` · `Modular Arithmetic`

---

## 30-Second Last-Minute Revision

> **Min Multiplications:** BFS. State = number mod 1000. `dist[1000]=1e9`.
> `start==end` → return 0 early.
> Queue `{node, steps}`. For each arr[i]: `num=(1LL*it*node)%1000`.
> `steps+1 < dist[num]` → update + early return if `num==end` + push.
> **Time:** O(1000×|arr|) | **Key:** BFS not Dijkstra (unit cost). 1LL for overflow.
