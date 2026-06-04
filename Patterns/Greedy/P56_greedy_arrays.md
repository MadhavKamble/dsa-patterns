# P56 — Greedy Array Problems

## 1. First-Timer Explanation

### What Is It?
**Greedy array problems** solve optimization by making locally optimal decisions at each step without backtracking. The classic examples: candy distribution (scan twice), boats (two pointers), wiggle sequences, and task scheduling by frequency. The key to a greedy approach: prove the local choice never hurts the global optimum.

### Analogy — Candy Problem
Distributing candy to children in a line, where children with higher ratings than their neighbors get more candy. Scan left-to-right: if a child has higher rating than left neighbor, give one more candy than left. Then scan right-to-left: if child has higher rating than right neighbor and doesn't have more candy already, fix it. Two passes, O(n).

### When to Use
- "Distribute/assign with comparison constraints" → two-pass greedy
- "Two groups/partners matching" → sort + two pointer
- "Maximize without exceeding limit" → sort, then greedily pick
- "Wiggle" sequences → track direction

### When NOT to Use
- Dependencies across many positions → DP
- Not obvious that local = global optimal → verify or use DP

### Common Mistakes
1. Candy: forgetting the max in the right-to-left pass
2. Two boats: forgetting to move both pointers when both fit in one boat
3. Not sorting before two-pointer greedy

---

## 2. Revision Card

**Recognition Signal:** "distribute with neighbor constraints", "pair elements optimally", "maximize count of valid pairs"

**Core Idea:** Sort if order doesn't matter; scan with constraints; maintain running variables tracking local state.

**Trigger Keywords:** candy, distribute, assign, wiggle, pairs, boats, two groups

**Complexity:** O(n log n) if sorting required, O(n) if pre-sorted

---

## 3. Interview Tell Signs

- "Minimum candy with neighbor rating constraint" → two-pass greedy
- "Pair boats/people with weight limit" → sort + two pointer
- "Wiggle subsequence" → scan, track direction changes
- "Assign tasks/workers optimally" → sort both, match greedily

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── Candy Distribution (two-pass greedy) ─────────────────────────────────────
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1);
    // Left pass: if rating[i] > rating[i-1], get one more than left
    for (int i = 1; i < n; i++)
        if (ratings[i] > ratings[i-1]) candies[i] = candies[i-1] + 1;
    // Right pass: if rating[i] > rating[i+1], ensure more than right
    for (int i = n-2; i >= 0; i--)
        if (ratings[i] > ratings[i+1]) candies[i] = max(candies[i], candies[i+1] + 1);
    return accumulate(candies.begin(), candies.end(), 0);
}

// ── Boats to Save People (sort + two pointers) ───────────────────────────────
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int lo = 0, hi = people.size() - 1, boats = 0;
    while (lo <= hi) {
        if (people[lo] + people[hi] <= limit) lo++; // both fit
        hi--; // heaviest always takes a boat
        boats++;
    }
    return boats;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Candy):**
> "I make two passes. In the left-to-right pass, if a child has a higher rating than their left neighbor, they get one more candy than the left. In the right-to-left pass, if they have a higher rating than their right neighbor and don't already have more candy, I fix it by taking the max. Both constraints are satisfied after two linear passes."

**Checklist:**
- [ ] Candy: start all at 1, two passes, use max in right-to-left
- [ ] Boats: sort, two pointers, always advance hi (heaviest)
- [ ] Wiggle: track previous direction, count direction changes

---

## 6. Problems

### Problem 1: Candy
**Difficulty:** Hard | **LC:** 135

```cpp
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> c(n, 1);
    for (int i = 1; i < n; i++)
        if (ratings[i] > ratings[i-1]) c[i] = c[i-1] + 1;
    for (int i = n-2; i >= 0; i--)
        if (ratings[i] > ratings[i+1]) c[i] = max(c[i], c[i+1] + 1);
    return accumulate(c.begin(), c.end(), 0);
}
// Time: O(n) | Space: O(n)
// Edge: all same ratings → all get 1 candy
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Boats to Save People
**Difficulty:** Medium | **LC:** 881

```cpp
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int lo = 0, hi = (int)people.size()-1, boats = 0;
    while (lo <= hi) {
        if (people[lo] + people[hi] <= limit) lo++;
        hi--; boats++;
    }
    return boats;
}
// Time: O(n log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Wiggle Subsequence
**Difficulty:** Medium | **LC:** 376

**Approach:** Scan array, count direction changes. Greedy: extend current sequence or start new direction.

```cpp
int wiggleMaxLength(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) return n;
    int up = 1, down = 1;
    for (int i = 1; i < n; i++) {
        if (nums[i] > nums[i-1]) up = down + 1;
        else if (nums[i] < nums[i-1]) down = up + 1;
    }
    return max(up, down);
}
// Time: O(n) | Space: O(1)
// up: length of longest wiggle ending with rise
// down: length ending with fall
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Advantage Shuffle (Optimal Matching)
**Difficulty:** Medium | **LC:** 870

**Approach:** Sort A. For each element in B (sorted by index), if A's max can beat B's max, assign it; else assign A's minimum (sacrifice).

```cpp
vector<int> advantageCount(vector<int>& A, vector<int>& B) {
    int n = A.size();
    sort(A.begin(), A.end());
    
    // Sort B by value but keep original indices
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) { return B[i] > B[j]; });
    
    vector<int> res(n);
    int lo = 0, hi = n - 1;
    for (int i : idx) {
        // Can A[hi] beat B[i]? → yes: assign A[hi]. No: sacrifice A[lo]
        if (A[hi] > B[i]) res[i] = A[hi--];
        else res[i] = A[lo++];
    }
    return res;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Two City Scheduling
**Difficulty:** Medium | **LC:** 1029

**Approach:** Sort by `cost[i][0] - cost[i][1]` (how much cheaper A is than B). Send first half to A, second half to B.

```cpp
int twoCitySchedCost(vector<vector<int>>& costs) {
    sort(costs.begin(), costs.end(), [](auto& a, auto& b) {
        return (a[0] - a[1]) < (b[0] - b[1]); // sorted by "savings from going to A"
    });
    int n = costs.size() / 2, total = 0;
    for (int i = 0; i < (int)costs.size(); i++)
        total += i < n ? costs[i][0] : costs[i][1];
    return total;
}
// Time: O(n log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Minimum Cost to Connect Sticks
**Difficulty:** Medium | **LC:** 1167

**Approach:** Huffman coding / greedy with min-heap. Always merge two smallest sticks.

```cpp
int connectSticks(vector<int>& sticks) {
    priority_queue<int, vector<int>, greater<int>> minH(sticks.begin(), sticks.end());
    int cost = 0;
    while (minH.size() > 1) {
        int a = minH.top(); minH.pop();
        int b = minH.top(); minH.pop();
        cost += a + b;
        minH.push(a + b);
    }
    return cost;
}
// Time: O(n log n) | Space: O(n)
// This is Huffman coding — optimal prefix-free encoding
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Candy: ratings=[1,0,2]. After left pass and right pass, what are the candies?
<details><summary>Reveal</summary>
Left pass: c=[1,1,2] (2>0→ c[2]=c[1]+1=2; 0<1 no change). Right pass: i=1: ratings[1]=0 < ratings[2]=2, no change; i=0: ratings[0]=1 > ratings[1]=0 → c[0]=max(1,c[1]+1)=max(1,2)=2. Final: [2,1,2]. Total=5.
</details>

**Drill 2:** Boats: people=[3,5,3,4], limit=5. Trace.
<details><summary>Reveal</summary>
Sorted: [3,3,4,5]. lo=0,hi=3. people[0]+people[3]=8>5 → boats=1,hi=2. people[0]+people[2]=7>5 → boats=2,hi=1. people[0]+people[1]=6>5 → boats=3,hi=0. lo>hi done. 4 boats... wait: lo=0,hi=0: people[0]+people[0]=6>5 → boats=4,hi=-1. End. Answer: 4? No — re-trace: after boat 3, lo=0,hi=0, lo<=hi so enter loop: people[0]+people[0] is same person. Actually lo tracks the lightest. Let me redo: [3,3,4,5]: step1: 3+5=8>5 → hi=2,boats=1. step2: 3+4=7>5 → hi=1,boats=2. step3: 3+3=6>5 → hi=0,boats=3. step4: lo=0,hi=0, lo<=hi: 3+3 same person but lo increments: 3+3=6>5, no. hi--,boats=4. lo=1>hi=0, stop. Answer: 4.
</details>

**Drill 3:** Two City Scheduling: why sort by `cost[i][0] - cost[i][1]`?
<details><summary>Reveal</summary>
This represents "extra cost of sending to A vs B". Negative = cheaper to send to A. Sorting by this and sending first half to A maximizes the savings. It's equivalent to: start everyone going to B, then find the n people where switching to A saves the most (most negative difference).
</details>

**Drill 4:** Wiggle Subsequence for [1,17,5,10,13,15,10,5,16,8]. What's the answer?
<details><summary>Reveal</summary>
Direction changes: 1→17 (up), 17→5 (down), 5→10 (up), 10→13 (skip, same dir), 13→15 (skip), 15→10 (down), 10→5 (skip same dir), 5→16 (up), 16→8 (down). Wiggles: up,down,up,down,up,down = 6 changes + 1 start = 7.
</details>

**Drill 5:** Connect Sticks [2,4,3] — trace the min-heap.
<details><summary>Reveal</summary>
Heap: [2,3,4]. Pop 2,3: merge=5, cost=5. Heap: [4,5]. Pop 4,5: merge=9, cost=5+9=14. Answer: 14. (vs [3,4,2]: pop 2,3=5, pop 4,5=9 → same.)
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Candy | O(n) | O(n) |
| Boats | O(n log n) | O(1) |
| Wiggle Subsequence | O(n) | O(1) |
| Two City Scheduling | O(n log n) | O(1) |
| Connect Sticks | O(n log n) | O(n) |
| Advantage Shuffle | O(n log n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: Candy without extra space?**
A: Yes — O(1) space approach using peak/valley math. Count ascending/descending runs algebraically. O(n) time, O(1) space but complex to implement.

**Q: What if boats can carry 3 people?**
A: Harder — becomes a bin packing variant (NP-hard in general). The two-person limit is what makes it greedy.

**Q: Connect Sticks is Huffman coding — can you build the actual tree?**
A: Yes. Instead of just tracking cost, store tree nodes. Each merge creates a parent node. The resulting tree gives optimal prefix-free encoding.

---

## 10. Cross-Pattern Connections

- **P42 (Top-K/Heap):** Connect Sticks uses min-heap — same mechanism
- **P53 (Interval Scheduling):** Both use sort + greedy scan
- **P04 (Two Pointers):** Boats problem is a two-pointer on sorted array
- **P30 (1D DP):** Wiggle can also be solved with DP O(n); greedy is O(n) O(1) space
