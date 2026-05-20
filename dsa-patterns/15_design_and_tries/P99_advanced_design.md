# P99 — Advanced Design Patterns

## 1. First-Timer Explanation

### What Is It?
This pattern covers advanced data structure designs that appear in hard interview problems: **monotonic deque** for sliding window maximum, **ordered set / multiset** for rank queries, **sparse table** for O(1) range minimum/maximum queries, **jump pointers** (binary lifting) for repeated-step queries, and **design synthesis** combining multiple structures for complex operation profiles.

### Monotonic Deque (Sliding Window Max/Min)
```
Maintain deque of indices where values are decreasing (for max):
  - New element: pop back while deque.back() value ≤ new value
  - Evict old: pop front if deque.front() is out of window
  - Current max: deque.front()

Window [1,3,-1,-3,5,3,6,7], k=3:
  i=0: deque=[0(val 1)]
  i=1: 3>1 → pop 0, push 1: deque=[1(val 3)]
  i=2: -1<3 → push 2: deque=[1,2] → max=3 (deque[0]=1→val 3)
  i=3: -3<-1 → push 3: deque=[1,2,3] → max=3
       i-k=0 < front=1? No. max=arr[deque[0]]=arr[1]=3
  i=4: 5>-3,-1,3 → clear deque, push 4: deque=[4] → max=5
  ...
```

### Ordered Set for Rank Queries
```
C++ std::multiset: BST-based, O(log n) insert/delete/find
- Find kth element: std::next(ms.begin(), k) → O(k) — NOT O(log n)!
- For true O(log n) kth: use policy-based tree (GNU PBDS) or BIT

GNU PBDS order statistics tree:
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;

os.insert(x);           // O(log n)
os.order_of_key(x);     // rank of x (0-indexed) O(log n)
*os.find_by_order(k);   // kth element (0-indexed) O(log n)
```

### Sparse Table (Static RMQ)
```
Precompute: sparse[i][j] = min in range [i, i + 2^j - 1]
Build: sparse[i][0] = arr[i]
       sparse[i][j] = min(sparse[i][j-1], sparse[i+2^(j-1)][j-1])

Query [l, r]:
  k = floor(log2(r - l + 1))
  return min(sparse[l][k], sparse[r - 2^k + 1][k])
  (ranges overlap — fine for min/max which are idempotent)

Build: O(n log n) | Query: O(1) | Space: O(n log n)
Limitation: STATIC (no updates). For updates use Segment Tree.
```

### Jump Pointers (Binary Lifting)
```
For repeated application of a function f:
  jump[i][j] = result of applying f 2^j times starting from i

Build: jump[i][0] = parent[i]  (1 step)
       jump[i][j] = jump[jump[i][j-1]][j-1]  (2^j = 2^(j-1) + 2^(j-1))

Query "k steps from node x":
  for each bit in k: if bit set, x = jump[x][bit]

LCA (Lowest Common Ancestor):
  1. Bring nodes to same depth using binary lifting
  2. Binary lift both until parent is same → that's LCA
  O(log n) per LCA query, O(n log n) preprocessing
```

### When to Use
- "Max/min in sliding window" → monotonic deque O(n total)
- "Find kth element dynamically" → ordered set (PBDS) or BIT
- "Static range min/max with many queries" → sparse table O(1) query
- "kth ancestor in tree" → binary lifting
- "LCA queries" → binary lifting or Euler tour + RMQ

---

## 2. Revision Card

**Recognition Signal:** "sliding window max", "kth in dynamic set", "O(1) range min/max", "ancestor queries"

**Core Ideas:**
- Monotonic deque: maintain decreasing (for max) values; window = indices
- PBDS ordered set: `order_of_key` (rank) and `find_by_order` (kth) in O(log n)
- Sparse table: overlap-friendly precomputation; O(1) RMQ for idempotent functions
- Binary lifting: power-of-2 jumps precomputed; decompose k into bits

**Trigger Keywords:** sliding window max/min, kth dynamic, LCA, range min/max (static), repeated steps

**Complexity:** Deque O(n), PBDS O(log n), Sparse O(1) query / O(n log n) build, Binary lifting O(log n) query / O(n log n) build

---

## 3. Interview Tell Signs

- "Maximum element in every window of size k" → monotonic deque
- "Kth largest in a stream with deletions" → multiset or PBDS ordered set
- "Range minimum query with no updates" → sparse table
- "Kth ancestor of a node in a tree" → binary lifting
- "Lowest common ancestor" → binary lifting (or Euler tour + RMQ)
- "Median of a sliding window" → two heaps (max-heap + min-heap) or PBDS
- "Find closest value to x in sorted set" → multiset + lower_bound

---

## 4. C++ Template

```cpp
#include <deque>
#include <set>
#include <vector>
#include <cmath>
using namespace std;

// ── Monotonic Deque (Sliding Window Maximum) ─────────────────────────────────
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // stores indices; front = max
    vector<int> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        // remove elements out of window
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        // maintain decreasing order
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]);
    }
    return res;
}

// ── Ordered Multiset Operations ───────────────────────────────────────────────
// std::multiset for O(log n) insert/delete/find, O(n) kth
// Use PBDS for O(log n) kth:
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> pbds;

// ── Sparse Table (Static RMQ) ─────────────────────────────────────────────────
struct SparseTable {
    int n, LOG;
    vector<vector<int>> table;
    vector<int> log2_;

    SparseTable(vector<int>& arr) : n(arr.size()), LOG(1 + __lg(arr.size())),
        table(1 + __lg(arr.size()), vector<int>(arr.size())), log2_(arr.size() + 1) {
        for (int i = 2; i <= n; i++) log2_[i] = log2_[i/2] + 1;
        table[0] = arr;
        for (int j = 1; j < LOG; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[j][i] = min(table[j-1][i], table[j-1][i + (1 << (j-1))]);
    }

    int query(int l, int r) { // [l, r] inclusive
        int k = log2_[r - l + 1];
        return min(table[k][l], table[k][r - (1 << k) + 1]);
    }
};

// ── Binary Lifting (Kth Ancestor / LCA) ──────────────────────────────────────
struct BinaryLifting {
    int n, LOG = 20;
    vector<int> depth;
    vector<vector<int>> up; // up[v][j] = 2^j-th ancestor of v

    BinaryLifting(int n, vector<int>& parent) : n(n), depth(n, 0),
        up(LOG, vector<int>(n, -1)) {
        for (int i = 0; i < n; i++) up[0][i] = parent[i]; // -1 for root
        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++)
                if (up[j-1][v] != -1) up[j][v] = up[j-1][up[j-1][v]];
    }

    int kthAncestor(int node, int k) {
        for (int j = 0; j < LOG && node != -1; j++)
            if ((k >> j) & 1) node = up[j][node];
        return node;
    }

    int lca(int u, int v) {
        // Bring to same depth, then lift together
        if (depth[u] < depth[v]) swap(u, v);
        u = kthAncestor(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int j = LOG-1; j >= 0; j--)
            if (up[j][u] != -1 && up[j][u] != up[j][v]) {
                u = up[j][u]; v = up[j][v];
            }
        return up[0][u];
    }
};

// ── Sliding Window Median (Two Heaps) ─────────────────────────────────────────
// lo = max-heap (lower half), hi = min-heap (upper half)
// Balance invariant: lo.size() == hi.size() or lo.size() == hi.size() + 1
```

---

## 5. How to Present in Interview

**Verbal Script (Monotonic Deque):**
> "I'll use a deque of indices. For each new element, I pop from the back while the back's value is ≤ current (maintaining decreasing order). I pop from the front when its index falls outside the window. The front always holds the index of the current window maximum. This is O(n) total — each element is pushed and popped at most once."

**Verbal Script (Sparse Table):**
> "Since the array is static and min is idempotent (overlapping ranges give the same answer), I can use a sparse table. Build: `table[j][i]` = min of 2^j elements starting at i, built bottom-up in O(n log n). Query [l,r]: find k = floor(log2(r-l+1)), return min of table[k][l] and table[k][r-2^k+1]. These ranges overlap but min is fine with that, so it's O(1)."

**Checklist:**
- [ ] Deque stores indices, not values (need indices for window eviction)
- [ ] Deque eviction: front goes out when `dq.front() <= i - k`
- [ ] Sparse table only works for idempotent operations (min, max, gcd, NOT sum)
- [ ] Binary lifting LOG must be large enough: LOG=20 covers n up to 10^6
- [ ] LCA: must correctly set depth[] before queries; handle root (-1) as sentinel

---

## 6. Problems

### Problem 1: Sliding Window Maximum
**Difficulty:** Hard | **LC:** 239

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; vector<int> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (!dq.empty() && dq.front() <= i - k) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k-1) res.push_back(nums[dq.front()]);
    }
    return res;
}
// Time: O(n) | Space: O(k)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Kth Largest Element in a Stream
**Difficulty:** Easy | **LC:** 703

```cpp
class KthLargest {
    priority_queue<int, vector<int>, greater<int>> pq; // min-heap of size k
    int k;
public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int x : nums) add(x);
    }
    int add(int val) {
        pq.push(val);
        if ((int)pq.size() > k) pq.pop();
        return pq.top();
    }
};
// Time: O(log k) per add | Space: O(k)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Find Median from Data Stream
**Difficulty:** Hard | **LC:** 295

```cpp
class MedianFinder {
    priority_queue<int> lo;                              // max-heap: lower half
    priority_queue<int,vector<int>,greater<int>> hi;    // min-heap: upper half
public:
    void addNum(int n) {
        lo.push(n);
        hi.push(lo.top()); lo.pop();            // move lo's max to hi
        if (hi.size() > lo.size()) { lo.push(hi.top()); hi.pop(); } // rebalance
    }
    double findMedian() {
        return lo.size() > hi.size() ? lo.top() : (lo.top() + (double)hi.top()) / 2;
    }
};
// Time: O(log n) addNum, O(1) findMedian | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Kth Ancestor of a Tree Node
**Difficulty:** Hard | **LC:** 1483

```cpp
class TreeAncestor {
    int LOG = 16;
    vector<vector<int>> up;
public:
    TreeAncestor(int n, vector<int>& parent) : up(LOG, vector<int>(n, -1)) {
        up[0] = parent;
        for (int j = 1; j < LOG; j++)
            for (int v = 0; v < n; v++)
                if (up[j-1][v] != -1) up[j][v] = up[j-1][up[j-1][v]];
    }
    int getKthAncestor(int node, int k) {
        for (int j = 0; j < LOG && node != -1; j++)
            if ((k >> j) & 1) node = up[j][node];
        return node;
    }
};
// Time: O(n log n) build, O(log n) query | Space: O(n log n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Range Minimum Query (Static)
**Difficulty:** Medium (custom) | No direct LC — pattern used in many problems

```cpp
// Sparse table for O(1) RMQ
struct RMQ {
    vector<vector<int>> t; vector<int> lg;
    RMQ(vector<int>& a) {
        int n=a.size(), L=__lg(n)+1;
        t.assign(L, a); lg.resize(n+1);
        for(int i=2;i<=n;i++) lg[i]=lg[i/2]+1;
        for(int j=1;j<L;j++)
            for(int i=0;i+(1<<j)<=n;i++)
                t[j][i]=min(t[j-1][i],t[j-1][i+(1<<(j-1))]);
    }
    int query(int l,int r){int k=lg[r-l+1];return min(t[k][l],t[k][r-(1<<k)+1]);}
};
// Time: O(n log n) build, O(1) query | Space: O(n log n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Sliding Window Median
**Difficulty:** Hard | **LC:** 480

```cpp
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> lo, hi; // lo = lower half (max is lo.rbegin()), hi = upper half
    auto getMedian = [&]() -> double {
        return k % 2 ? *lo.rbegin() : ((double)*lo.rbegin() + *hi.begin()) / 2;
    };
    auto rebalance = [&]() {
        if (lo.size() > hi.size() + 1) { hi.insert(*lo.rbegin()); lo.erase(prev(lo.end())); }
        if (hi.size() > lo.size()) { lo.insert(*hi.begin()); hi.erase(hi.begin()); }
    };

    vector<double> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (lo.empty() || nums[i] <= *lo.rbegin()) lo.insert(nums[i]);
        else hi.insert(nums[i]);
        rebalance();
        if (i >= k) { // remove outgoing element
            int out = nums[i - k];
            if (lo.count(out)) lo.erase(lo.find(out));
            else hi.erase(hi.find(out));
            rebalance();
        }
        if (i >= k - 1) res.push_back(getMedian());
    }
    return res;
}
// Time: O(n log k) | Space: O(k)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** nums=[3,1,2,5,4], k=3. Trace the monotonic deque to find sliding window max.
<details><summary>Reveal</summary>
i=0: push 0. dq=[0(val 3)]. i=1: 1<3 → push. dq=[0,1]. i=2: 2<3 → push. dq=[0,1,2]. Window full → max=nums[0]=3. i=3: 5>2,1,3 → pop all, push 3. dq=[3]. Front=3≥0, in window. max=nums[3]=5. i=4: 4<5 → push. dq=[3,4]. Front=3, i-k=4-3=1, 3>1 so still in window. max=nums[3]=5. Results: [3,5,5] ✓.
</details>

**Drill 2:** Array=[2,4,3,1,6,7,8,9], k=3. Compute the sparse table for RMQ. What's query(0,5)?
<details><summary>Reveal</summary>
table[0]=[2,4,3,1,6,7,8,9]. table[1][i]=min(arr[i],arr[i+1]): [2,3,1,1,6,7,8]. table[2][i]=min(table[1][i],table[1][i+2]): [1,1,1,1,6,7]. Query(0,5): k=floor(log2(6))=2. min(table[2][0], table[2][5-4+1])=min(table[2][0], table[2][2])=min(1,1)=1 ✓.
</details>

**Drill 3:** Binary lifting: tree with parent=[−1,0,0,1,1,2], depth=[0,1,1,2,2,2]. Find 2nd ancestor of node 3.
<details><summary>Reveal</summary>
k=2 = binary 10. j=0: bit 0 is 0, skip. j=1: bit 1 is 1 → node = up[1][3]. up[1][3] = up[0][up[0][3]] = up[0][1] = 0. So 2nd ancestor of 3 is 0 (the root). ✓
</details>

**Drill 4:** Median of sliding window: nums=[1,3,-1,-3,5,3,6,7], k=3. What are the first 3 medians?
<details><summary>Reveal</summary>
Window [1,3,-1]: sorted=[-1,1,3] → median=1. Window [3,-1,-3]: sorted=[-3,-1,3] → median=-1. Window [-1,-3,5]: sorted=[-3,-1,5] → median=-1. First 3 medians: [1,-1,-1].
</details>

**Drill 5:** When should you choose sparse table over segment tree for range queries?
<details><summary>Reveal</summary>
Use sparse table when: (1) the array is STATIC (no updates), (2) the query operation is IDEMPOTENT (min, max, gcd — not sum), (3) you need O(1) query time. Sparse table uses O(n log n) space vs segment tree's O(n), but query is O(1) vs O(log n). For sum queries or with updates, use segment tree or BIT. For dynamic order statistics, use BIT or PBDS ordered set.
</details>

---

## 8. Complexity Cheatsheet

| Data Structure | Build | Query | Update | Space |
|---------------|-------|-------|--------|-------|
| Monotonic Deque | O(n) total | O(1) amortized | O(1) slide | O(k) |
| Sparse Table | O(n log n) | O(1) | ✗ static | O(n log n) |
| Segment Tree | O(n) | O(log n) | O(log n) | O(n) |
| Fenwick Tree (BIT) | O(n log n) | O(log n) | O(log n) | O(n) |
| Binary Lifting | O(n log n) | O(log n) | ✗ static | O(n log n) |
| std::multiset | — | O(log n) | O(log n) | O(n) |
| PBDS ordered_set | — | O(log n) | O(log n) | O(n) |
| Two Heaps (Median) | — | O(1) | O(log n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: When is the monotonic deque pattern applicable?**
A: Any time you need the max or min in a sliding window of fixed or variable size. It's also used for largest rectangle in histogram and trapping rain water (though stack-based solutions are more common). Key: the deque stores indices and maintains a monotone value order.

**Q: Can sparse table handle range sum queries?**
A: No. Sum is not idempotent — if ranges overlap, you double-count elements. For range sum with no updates use prefix sums (O(1) query, O(n) build). For range sum with updates, use Fenwick tree or segment tree.

**Q: What's the difference between PBDS ordered_set and std::set for kth element?**
A: std::set doesn't support O(log n) kth element — you'd need `std::next(begin(), k)` which is O(k). PBDS ordered_set (GNU policy-based) stores subtree sizes in each node, enabling `find_by_order(k)` in O(log n). It also provides `order_of_key(x)` (rank of x) in O(log n).

**Q: How to handle ties in the sliding window median?**
A: The multiset-based approach handles ties naturally — duplicates are stored as separate entries in multiset. The two-set approach (lo/hi split) correctly maintains the invariant even with duplicate values.

---

## 10. Cross-Pattern Connections

- **P84 (Sweep Line):** Monotonic structures used in both — deque for window max, monotone stack for skyline
- **P96 (Segment Tree):** Sparse table is the static, faster alternative to segment tree for RMQ
- **P97 (Fenwick Tree):** BIT is the dynamic alternative for range sum; sparse table for static range min/max
- **P98 (Union Find):** Both DSU and binary lifting work on tree structure — DSU for connectivity, binary lifting for ancestor queries
- **P43 (Two Heaps):** Median finder uses two heaps — the same structure powers sliding window median
- **P42 (Top-K / Heaps):** Kth largest uses min-heap of size k; same as the heap used in median stream
- **P67 (Monotonic Stack):** Monotonic deque is the sliding-window generalization of monotonic stack; stack = infinite window, deque = bounded window
