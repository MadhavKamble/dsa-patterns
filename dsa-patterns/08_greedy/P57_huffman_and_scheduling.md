# P57 — Huffman Coding and Advanced Scheduling

## 1. First-Timer Explanation

### What Is It?
**Huffman coding** builds an optimal prefix-free encoding: frequent characters get shorter codes, rare characters get longer ones. The algorithm is purely greedy: repeatedly merge the two lowest-frequency nodes. The same "always merge smallest two" pattern appears in many scheduling and cost-minimization problems.

**CPU task scheduling** with ordering constraints: given tasks with dependencies (DAG), find the optimal execution order minimizing some metric (makespan, total weighted completion time, etc.).

### Huffman Visual Walkthrough
```
Characters: A(freq=5), B(3), C(8), D(1)

Initial min-heap: [D:1, B:3, A:5, C:8]

Step 1: Merge D(1) + B(3) = DB(4)
Heap: [A:5, DB:4, C:8] → after insert: [DB:4, A:5, C:8]

Step 2: Merge DB(4) + A(5) = DBA(9)
Heap: [C:8, DBA:9]

Step 3: Merge C(8) + DBA(9) = root(17)

Tree:         root(17)
            /         \
          C(8)        DBA(9)
                     /      \
                   DB(4)    A(5)
                  /    \
               D(1)   B(3)

Codes: C=0, A=11, B=100, D=101
Total bits = 8*1 + 5*2 + 3*3 + 1*3 = 8+10+9+3 = 30 (optimal)
```

### When to Use
- "Minimize total cost of merging" → Huffman / always merge smallest two
- "Optimal encoding" → Huffman tree
- "Schedule tasks to minimize weighted completion time" → sort by weight/length ratio

### Common Mistakes
1. Using max-heap instead of min-heap for Huffman
2. Forgetting that each merge creates a new node with combined weight
3. Scheduling: weighted job scheduling is DP, not greedy

---

## 2. Revision Card

**Recognition Signal:** "minimize merging cost", "optimal code length", "encode with minimum bits"

**Core Idea:** Min-heap. Extract two smallest, merge (cost = sum), push merged back. Repeat until one remains. Total cost = sum of all merge costs.

**Trigger Keywords:** Huffman, encoding, prefix, merge cost, minimum bits, optimal compression

**Complexity:**
| Operation | Time | Space |
|-----------|------|-------|
| Huffman build | O(n log n) | O(n) |
| Merge all sticks | O(n log n) | O(n) |

---

## 3. Interview Tell Signs

- "Minimum cost to merge all groups" → Huffman / min-heap greedy
- "Optimal lossless compression" → Huffman coding
- "Minimize total weighted completion time" → sort by weight/processing time ratio
- "Build tree with minimum path length" → Huffman tree construction

---

## 4. C++ Template

```cpp
#include <queue>
#include <vector>
using namespace std;

// ── Huffman Cost (same as Connect Sticks) ────────────────────────────────────
int huffmanCost(vector<int>& freq) {
    priority_queue<int, vector<int>, greater<int>> minH(freq.begin(), freq.end());
    int totalCost = 0;
    while (minH.size() > 1) {
        int a = minH.top(); minH.pop();
        int b = minH.top(); minH.pop();
        totalCost += a + b;
        minH.push(a + b);
    }
    return totalCost;
}

// ── Optimal Order for Weighted Job Scheduling ────────────────────────────────
// Minimize sum of weighted completion times: sort by w[i]/p[i] descending
// (equivalently: w[i]*p[j] > w[j]*p[i])
int minimizeWeightedCompletion(vector<pair<int,int>>& jobs) { // {weight, time}
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return a.first * b.second > b.first * a.second; // w_i/p_i > w_j/p_j
    });
    int total = 0, time = 0;
    for (auto& [w, p] : jobs) { time += p; total += w * time; }
    return total;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Huffman coding uses a min-heap. I start with each character as a leaf node weighted by frequency. I repeatedly extract the two minimum-weight nodes, create a parent node with their combined weight, and push it back. The final tree gives optimal prefix-free codes — frequent characters are closer to the root (shorter codes). Total cost = sum of all merge costs."

**Checklist:**
- [ ] Min-heap initialization
- [ ] Extract two → merge → push back
- [ ] Count total merge cost (not just final root weight)
- [ ] For actual codes: traverse tree, track left/right path (0/1)

---

## 6. Problems

### Problem 1: Minimum Cost to Connect Sticks (Huffman Application)
**Difficulty:** Medium | **LC:** 1167

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
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Minimum Cost to Merge Stones
**Difficulty:** Hard | **LC:** 1000

**Approach:** Interval DP. Merge k adjacent piles repeatedly. Different from Huffman — requires DP.

```cpp
int mergeStones(vector<int>& stones, int K) {
    int n = stones.size();
    if ((n - 1) % (K - 1) != 0) return -1; // impossible
    
    vector<int> prefix(n+1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + stones[i];
    
    // dp[i][j] = min cost to merge stones[i..j] into as few piles as possible
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = K; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            for (int m = i; m < j; m += K-1)
                dp[i][j] = min(dp[i][j], dp[i][m] + dp[m+1][j]);
            if ((len - 1) % (K - 1) == 0)
                dp[i][j] += prefix[j+1] - prefix[i];
        }
    }
    return dp[0][n-1];
}
// Time: O(n^3/K) | Space: O(n^2)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Reorganize String (Greedy Scheduling)
**Difficulty:** Medium | **LC:** 767

**Approach:** Always place the most frequent remaining character (that's different from last placed). Max-heap.

```cpp
string reorganizeString(string s) {
    int cnt[26] = {};
    for (char c : s) cnt[c-'a']++;
    
    priority_queue<pair<int,char>> maxH;
    for (int i = 0; i < 26; i++)
        if (cnt[i]) maxH.push({cnt[i], 'a'+i});
    
    string res;
    while (maxH.size() >= 2) {
        auto [f1,c1] = maxH.top(); maxH.pop();
        auto [f2,c2] = maxH.top(); maxH.pop();
        res += c1; res += c2;
        if (f1 > 1) maxH.push({f1-1, c1});
        if (f2 > 1) maxH.push({f2-1, c2});
    }
    if (!maxH.empty()) {
        if (maxH.top().first > 1) return "";
        res += maxH.top().second;
    }
    return res;
}
// Time: O(n log n) | Space: O(1) — 26 chars
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: IPO (Maximize Capital via Greedy)
**Difficulty:** Hard | **LC:** 502

**Approach:** Two heaps: locked (min-heap by capital) + available (max-heap by profit). Unlock projects as capital grows, always pick highest-profit available.

```cpp
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> locked;
    priority_queue<int> available;
    for (int i = 0; i < n; i++) locked.push({capital[i], profits[i]});
    
    for (int i = 0; i < k; i++) {
        while (!locked.empty() && locked.top().first <= w) {
            available.push(locked.top().second); locked.pop();
        }
        if (available.empty()) break;
        w += available.top(); available.pop();
    }
    return w;
}
// Time: O(n log n + k log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** What's the key property of Huffman that makes greedy work?
<details><summary>Reveal</summary>
The two least frequent characters should always be the deepest in the tree (longest codes). By always merging the two smallest, we build from the bottom up. Exchange argument: any other pairing of the two smallest would result in equal or greater total cost.
</details>

**Drill 2:** Connect Sticks [1,8,3,5]. Trace the Huffman cost.
<details><summary>Reveal</summary>
Heap: [1,3,5,8]. Merge 1+3=4, cost=4. Heap: [4,5,8]. Merge 4+5=9, cost=4+9=13. Heap: [8,9]. Merge 8+9=17, cost=13+17=30. Answer: 30.
</details>

**Drill 3:** Merge Stones vs Connect Sticks — why is one DP and one greedy?
<details><summary>Reveal</summary>
Connect Sticks: you always merge exactly 2 sticks, free to choose any two. Huffman greedy works. Merge Stones: you must merge exactly K adjacent piles (position matters). The adjacency constraint means you can't just pick the smallest K globally — you must consider which ranges can be merged. This requires interval DP.
</details>

**Drill 4:** Reorganize String: why take the top TWO from the max-heap each round?
<details><summary>Reveal</summary>
Taking only the top 1 each time would fail when the most frequent character appears consecutively. By taking two at a time, we ensure different characters are always adjacent. The second character acts as a "spacer" for the first. If only 1 character remains with count > 1, it's impossible.
</details>

**Drill 5:** Optimal weighted job scheduling: two jobs (w=3, p=2) and (w=4, p=3). Which runs first?
<details><summary>Reveal</summary>
Compare w1*p2 vs w2*p1: 3*3=9 vs 4*2=8. Since 9 > 8, job 1 (w=3,p=2) runs first. Verify: order (1,2): completion 2 and 5, weighted = 3*2 + 4*5 = 26. Order (2,1): completion 3 and 5, weighted = 4*3 + 3*5 = 27. First order wins ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Huffman Build | O(n log n) | O(n) |
| Connect Sticks | O(n log n) | O(n) |
| Merge Stones (K) | O(n³/K) | O(n²) |
| Reorganize String | O(n log n) | O(1) |
| IPO | O(n log n + k log n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: Can Huffman handle non-integer frequencies?**
A: Yes — the algorithm works with any comparable weights. Float frequencies work fine.

**Q: What's the length of the optimal Huffman code for n equal-frequency symbols?**
A: ⌈log₂(n)⌉ bits per symbol. A balanced binary tree.

**Q: Is there an O(n) Huffman if input is pre-sorted?**
A: Yes — two-queue algorithm. Use two queues: one for original sorted leaves, one for merged nodes. Always pick from the front of whichever queue has the smaller element. O(n) total.

---

## 10. Cross-Pattern Connections

- **P42 (Top-K/Heap):** Both use min-heap as core mechanism
- **P45 (Task Scheduling):** Same greedy heap scheduling idea
- **P56 (Greedy Arrays):** Connect Sticks appeared there too; this covers theory
- **P35 (Interval DP):** Merge Stones requires interval DP when K > 2
