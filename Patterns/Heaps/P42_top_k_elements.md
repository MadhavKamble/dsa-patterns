# P42 — Top-K Elements (Heap / Priority Queue)

## 1. First-Timer Explanation

### What Is It?
A **heap** (priority queue) is a tree-based data structure that always gives you the min or max element in O(1). Inserting and removing costs O(log n). The "Top-K" pattern uses a heap of size K to efficiently track the K largest (or K most frequent, K closest, etc.) elements without sorting everything.

### Analogy
Imagine sorting 1 million applicants by score to find the top 10. You don't need to rank all 1M — just maintain a "waiting room" of 10 people. When someone new arrives, compare with the weakest in the room. If they're better, kick the weakest out and let the new person in.

That waiting room is a **min-heap of size K** (weakest person is always at the top).

### Visual Walkthrough — Kth Largest in Array
```
nums = [3, 2, 1, 5, 6, 4], k = 2

Min-heap (size ≤ k):
Push 3 → [3]
Push 2 → [2, 3]
Push 1 → heap size = k=2, 1 < top(2), skip
Push 5 → 5 > top(2), pop 2, push 5 → [3, 5]
Push 6 → 6 > top(3), pop 3, push 6 → [5, 6]
Push 4 → 4 < top(5), skip

Heap top = 5 = 2nd largest ✓
```

### When to Use
- "Find top/bottom K elements" by any metric
- "Kth largest/smallest"
- "K most/least frequent"
- "K closest points"
- Stream of data, maintain running top-K

### When NOT to Use
- K = 1 → just use `max_element` O(n)
- Small arrays → sort is simpler
- Need all elements sorted → sort is O(n log n), same as heap approach

### Common Mistakes
1. Using max-heap when you need min-heap (for top-K largest, use MIN-heap)
2. Forgetting to check heap size before accessing top
3. Using `greater<>` vs default comparison — get them right
4. Off-by-one: Kth largest means heap size = K, return top

---

## 2. Revision Card

**Recognition Signal:** "top K", "Kth largest/smallest", "K most frequent", "K closest"

**Core Idea:** Maintain a min-heap of size K. For top-K largest: if new element > heap top, pop and push. Final heap contains the K largest; top is the Kth largest.

**Trigger Keywords:** top K, K frequent, K closest, Kth largest, Kth smallest, K pairs

**Complexity:**
| Operation | Time | Space |
|-----------|------|-------|
| Top-K from array | O(n log k) | O(k) |
| Top-K frequent | O(n log k) | O(n) |
| K closest (sort) | O(n log n) | O(k) |
| K closest (heap) | O(n log k) | O(k) |

---

## 3. Interview Tell Signs

- "Return K elements" → heap
- "K most/least frequent" → count with map, then heap by frequency
- "K closest to origin/target" → heap by distance
- "Design a data structure that supports finding median" → two heaps
- "Continuously arriving data, track top K" → streaming heap

---

## 4. C++ Template

```cpp
#include <queue>
#include <vector>
using namespace std;

// ── Top-K Largest using MIN-heap of size K ──────────────────────────────────
// For top-K largest: use min-heap (priority_queue<int, vector<int>, greater<int>>)
// Invariant: heap contains K largest seen so far; top = Kth largest

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minH; // min-heap
    for (int x : nums) {
        minH.push(x);
        if ((int)minH.size() > k) minH.pop(); // evict smallest
    }
    return minH.top(); // Kth largest
}

// ── Top-K Frequent using pair (freq, val) ───────────────────────────────────
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> cnt;
    for (int x : nums) cnt[x]++;
    
    // min-heap by frequency
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minH;
    for (auto& [val, freq] : cnt) {
        minH.push({freq, val});
        if ((int)minH.size() > k) minH.pop();
    }
    
    vector<int> res;
    while (!minH.empty()) { res.push_back(minH.top().second); minH.pop(); }
    return res;
}

// ── K Closest Points using custom comparator ────────────────────────────────
// Max-heap of size K, evict farthest
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    auto dist = [](vector<int>& p) { return p[0]*p[0] + p[1]*p[1]; };
    // max-heap: keep K smallest distances (evict largest)
    priority_queue<pair<int,int>> maxH; // {dist, index}
    for (int i = 0; i < (int)points.size(); i++) {
        maxH.push({dist(points[i]), i});
        if ((int)maxH.size() > k) maxH.pop();
    }
    vector<vector<int>> res;
    while (!maxH.empty()) { res.push_back(points[maxH.top().second]); maxH.pop(); }
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I see we need to find the K largest elements. My instinct is a min-heap of size K. I'll iterate through the array — if an element is larger than the heap's top (the current Kth largest), I pop the top and push the new element. This keeps the heap containing exactly the K largest. At the end, the heap top is our answer. Time is O(n log k), space is O(k)."

**Checklist:**
- [ ] Confirm: largest or smallest? Determines heap type
- [ ] State the heap invariant clearly
- [ ] Handle edge cases: k > n? k = 0?
- [ ] Mention O(n log k) vs sort O(n log n) — heap is better for large n, small k
- [ ] For frequencies: first count with hash map, then heap

---

## 6. Problems

### Problem 1: Kth Largest Element in an Array
**Difficulty:** Medium | **LC:** 215

**Approach:** Min-heap of size k. Iterate; if element > top, pop and push.

```cpp
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minH;
    for (int x : nums) {
        minH.push(x);
        if ((int)minH.size() > k) minH.pop();
    }
    return minH.top();
}
// Time: O(n log k) | Space: O(k)
// Edge: k=1 (returns max), k=n (returns min)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Top K Frequent Elements
**Difficulty:** Medium | **LC:** 347

**Approach:** Count frequencies with hash map. Min-heap by frequency of size k.

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> cnt;
    for (int x : nums) cnt[x]++;
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minH;
    for (auto& [val, freq] : cnt) {
        minH.push({freq, val});
        if ((int)minH.size() > k) minH.pop();
    }
    
    vector<int> res;
    while (!minH.empty()) { res.push_back(minH.top().second); minH.pop(); }
    return res;
}
// Time: O(n log k) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: K Closest Points to Origin
**Difficulty:** Medium | **LC:** 973

**Approach:** Max-heap of size k by squared distance. Evict farthest when size > k.

```cpp
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    // max-heap: {dist^2, index}
    priority_queue<pair<int,int>> maxH;
    for (int i = 0; i < (int)points.size(); i++) {
        int d = points[i][0]*points[i][0] + points[i][1]*points[i][1];
        maxH.push({d, i});
        if ((int)maxH.size() > k) maxH.pop();
    }
    vector<vector<int>> res;
    while (!maxH.empty()) { res.push_back(points[maxH.top().second]); maxH.pop(); }
    return res;
}
// Time: O(n log k) | Space: O(k)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Sort Characters By Frequency
**Difficulty:** Medium | **LC:** 451

**Approach:** Count frequencies, max-heap by frequency, build string.

```cpp
string frequencySort(string s) {
    unordered_map<char,int> cnt;
    for (char c : s) cnt[c]++;
    
    priority_queue<pair<int,char>> maxH;
    for (auto& [c, f] : cnt) maxH.push({f, c});
    
    string res;
    while (!maxH.empty()) {
        auto [f, c] = maxH.top(); maxH.pop();
        res += string(f, c);
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

### Problem 5: Find K Pairs with Smallest Sums
**Difficulty:** Medium | **LC:** 373

**Approach:** Min-heap starting with (nums1[i], nums2[0]) for all i. Expand by incrementing j.

```cpp
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    // {sum, i, j}
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minH;
    for (int i = 0; i < min((int)nums1.size(), k); i++)
        minH.push({nums1[i] + nums2[0], i, 0});
    
    vector<vector<int>> res;
    while (!minH.empty() && (int)res.size() < k) {
        auto [sum, i, j] = minH.top(); minH.pop();
        res.push_back({nums1[i], nums2[j]});
        if (j + 1 < (int)nums2.size())
            minH.push({nums1[i] + nums2[j+1], i, j+1});
    }
    return res;
}
// Time: O(k log k) | Space: O(k)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Reorganize String
**Difficulty:** Medium | **LC:** 767

**Approach:** Max-heap by frequency. Greedily pick most frequent, then second-most, alternating.

```cpp
string reorganizeString(string s) {
    int cnt[26] = {};
    for (char c : s) cnt[c-'a']++;
    
    priority_queue<pair<int,char>> maxH;
    for (int i = 0; i < 26; i++)
        if (cnt[i]) maxH.push({cnt[i], 'a'+i});
    
    string res;
    while (maxH.size() >= 2) {
        auto [f1, c1] = maxH.top(); maxH.pop();
        auto [f2, c2] = maxH.top(); maxH.pop();
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
// Edge: most frequent char > (n+1)/2 → impossible, return ""
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Given a list of students with scores, find the K students with highest scores. What heap type and size?
<details><summary>Reveal</summary>
Min-heap of size K. For each student: if score > heap.top(), pop and push. Top = Kth highest.
</details>

**Drill 2:** You're given a stream of integers. After processing each integer, report the current top-3 largest. How do you maintain this efficiently?
<details><summary>Reveal</summary>
Min-heap of size 3. For each new integer: push; if size > 3, pop. The heap contains the top-3 at any point.
</details>

**Drill 3:** You have 1 billion numbers but only 1KB of memory. Find the top 10 largest. What's your approach?
<details><summary>Reveal</summary>
Min-heap of size 10. Process numbers one at a time (streaming). Memory = O(10) = constant. This is the heap pattern's killer use case.
</details>

**Drill 4:** Given frequency counts {a:5, b:3, c:8, d:1}, return top-2 frequent. Trace through min-heap of size 2.
<details><summary>Reveal</summary>
Push (5,a) → heap: [(5,a)]. Push (3,b) → [(3,b),(5,a)]. Push (8,c) → size=3>2, pop min=(3,b) → [(5,a),(8,c)]. Push (1,d) → 1<top(5), skip. Result: a, c.
</details>

**Drill 5:** Problem says "find the K-th smallest element." Do you use min-heap or max-heap? Size?
<details><summary>Reveal</summary>
Max-heap of size K. Keep the K smallest seen so far. The top of the max-heap = largest among the K smallest = Kth smallest overall.
</details>

---

## 8. Complexity Cheatsheet

| Approach | Time | Space | Use When |
|----------|------|-------|----------|
| Sort + slice | O(n log n) | O(1) | Simple, n is small |
| Min-heap size K | O(n log k) | O(k) | Large n, small k |
| Quickselect | O(n) avg | O(1) | Exact Kth, in-place |
| Bucket/counting sort | O(n) | O(n) | Frequencies in [1,n] |

---

## 9. Common Follow-up Questions

**Q: Can you do it in O(n) instead of O(n log k)?**
A: Quickselect (partial sort). Average O(n), worst O(n²). For frequencies, bucket sort on [1,n] range.

**Q: What if elements arrive in a stream?**
A: Heap is perfect — O(log k) per element, O(k) memory.

**Q: How would you find the median of a stream?**
A: Two heaps — max-heap for lower half, min-heap for upper half. (That's P43.)

**Q: Top-K with custom comparator?**
A: Pass a lambda to `priority_queue`: `priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);`

---

## 10. Cross-Pattern Connections

- **P43 (Two Heaps / Median Stream):** Two heaps for median; builds on single-heap intuition
- **P44 (K-Way Merge):** Merge K sorted lists using min-heap with (val, list_idx, elem_idx)
- **P30 (1D DP):** Kadane's finds max subarray — different "max tracking" approach
- **P23 (Dijkstra):** Core mechanism IS a min-heap extracting minimum distance
- **P28 (MST/Prim's):** Prim's algorithm = heap-based greedy, same as top-K structure
