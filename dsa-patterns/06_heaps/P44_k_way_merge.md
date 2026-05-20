# P44 — K-Way Merge

## 1. First-Timer Explanation

### What Is It?
**K-Way Merge** efficiently merges K sorted sequences into one sorted output. The naive approach would re-scan all lists each time to find the minimum, taking O(nK) total. Using a min-heap, we always have the current minimum ready in O(1), and replacing it costs O(log K). Total: O(n log K).

### Analogy
Imagine K queues at a bank, each already sorted so the shortest person is at the front. You want to serve all customers in height order. You peek at the front of each queue, pick the shortest, serve them, then add the next person from that queue to your "comparison pool." A min-heap is exactly that comparison pool.

### Visual Walkthrough
```
K=3 sorted lists:
L0: [1, 4, 7]
L1: [2, 5, 8]
L2: [3, 6, 9]

Initial heap: {(1,0,0), (2,1,0), (3,2,0)}
             {val, list_idx, elem_idx}

Extract (1,0,0) → output [1], push (4,0,1)
Heap: {(2,1,0), (3,2,0), (4,0,1)}

Extract (2,1,0) → output [1,2], push (5,1,1)
Heap: {(3,2,0), (4,0,1), (5,1,1)}

Extract (3,2,0) → output [1,2,3], push (6,2,1)
...
Final output: [1,2,3,4,5,6,7,8,9]
```

### When to Use
- Merge K sorted arrays/lists
- "Smallest range covering elements from K lists"
- External sort (K chunks in memory)
- K-th smallest in K sorted arrays/matrix

### When NOT to Use
- K=1 → trivial
- Lists are not sorted → just concatenate and sort

### Common Mistakes
1. Not checking if the next element exists before pushing
2. Confusing list_idx and elem_idx in the heap tuple
3. Wrong heap type (need min-heap, not max-heap)

---

## 2. Revision Card

**Recognition Signal:** "merge K sorted lists/arrays", "Kth smallest in sorted matrix", "smallest range"

**Core Idea:** Min-heap of size K. Initialize with first element of each list. Extract min, push next from same list. Repeat until heap empty.

**Trigger Keywords:** K sorted, merge lists, smallest across K lists, Kth smallest in matrix

**Complexity:**
| Operation | Time | Space |
|-----------|------|-------|
| K-way merge | O(n log K) | O(K) |
| Kth in matrix | O(k log K) | O(K) |
| Smallest range | O(n log K) | O(K) |

---

## 3. Interview Tell Signs

- "Merge K sorted linked lists" → K-way merge
- "Find Kth smallest in sorted matrix" → K-way merge on rows
- "Smallest range covering K lists" → sliding window on K-way merged stream
- "Given K sorted arrays..." → almost always K-way merge

---

## 4. C++ Template

```cpp
#include <queue>
#include <vector>
using namespace std;

// ── Merge K Sorted Arrays ────────────────────────────────────────────────────
vector<int> mergeKArrays(vector<vector<int>>& arrays) {
    // {value, list_idx, elem_idx}
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minH;
    
    for (int i = 0; i < (int)arrays.size(); i++)
        if (!arrays[i].empty())
            minH.push({arrays[i][0], i, 0});
    
    vector<int> res;
    while (!minH.empty()) {
        auto [val, i, j] = minH.top(); minH.pop();
        res.push_back(val);
        if (j + 1 < (int)arrays[i].size())
            minH.push({arrays[i][j+1], i, j+1});
    }
    return res;
}

// ── Merge K Sorted Linked Lists ──────────────────────────────────────────────
struct ListNode { int val; ListNode* next; ListNode(int v) : val(v), next(nullptr) {} };

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minH(cmp);
    
    for (ListNode* h : lists) if (h) minH.push(h);
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!minH.empty()) {
        tail->next = minH.top(); minH.pop();
        tail = tail->next;
        if (tail->next) minH.push(tail->next);
    }
    return dummy.next;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I have K sorted lists and need to merge them. The key insight: at any point, the next element in the merged output must be the minimum across all K list heads. A min-heap gives that minimum in O(1). I initialize the heap with the first element of each list (tracking which list it came from). I repeatedly extract the min, output it, and push the next element from that same list. This runs in O(n log K) where n is total elements."

**Checklist:**
- [ ] Initialize heap with first elements from all lists
- [ ] Each heap entry stores (value, list_index, element_index)
- [ ] After extracting, push next element from same list if available
- [ ] Handle empty lists during initialization
- [ ] State O(n log K) time, O(K) space

---

## 6. Problems

### Problem 1: Merge K Sorted Lists
**Difficulty:** Hard | **LC:** 23

**Approach:** Min-heap of ListNode* by value. Extract min, push next node from same list.

```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minH(cmp);
    
    for (ListNode* h : lists) if (h) minH.push(h);
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!minH.empty()) {
        tail->next = minH.top(); minH.pop();
        tail = tail->next;
        if (tail->next) minH.push(tail->next);
    }
    return dummy.next;
}
// Time: O(n log k) where n = total nodes | Space: O(k)
// Edge: all empty lists → return nullptr
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Kth Smallest Element in a Sorted Matrix
**Difficulty:** Medium | **LC:** 378

**Approach:** Treat each row as a sorted list. Min-heap with first element of each row.

```cpp
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    // {val, row, col}
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minH;
    
    for (int i = 0; i < n; i++) minH.push({matrix[i][0], i, 0});
    
    int res = 0;
    for (int i = 0; i < k; i++) {
        auto [val, r, c] = minH.top(); minH.pop();
        res = val;
        if (c + 1 < n) minH.push({matrix[r][c+1], r, c+1});
    }
    return res;
}
// Time: O(k log n) | Space: O(n)
// Alternative: binary search O(n log(max-min)) — useful if k is large
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Smallest Range Covering Elements from K Lists
**Difficulty:** Hard | **LC:** 632

**Approach:** K-way merge tracking current range [min, max]. Min-heap gives current min; track global max separately.

```cpp
vector<int> smallestRange(vector<vector<int>>& nums) {
    // {val, list_idx, elem_idx}
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minH;
    int curMax = INT_MIN;
    
    for (int i = 0; i < (int)nums.size(); i++) {
        minH.push({nums[i][0], i, 0});
        curMax = max(curMax, nums[i][0]);
    }
    
    int resL = minH.top() != minH.top() ? 0 : get<0>(minH.top());
    int resR = curMax;
    // initialize
    resL = get<0>(minH.top());
    resR = curMax;
    
    while (true) {
        auto [val, i, j] = minH.top(); minH.pop();
        if (j + 1 == (int)nums[i].size()) break; // one list exhausted
        int next = nums[i][j+1];
        curMax = max(curMax, next);
        minH.push({next, i, j+1});
        int curMin = get<0>(minH.top());
        if (curMax - curMin < resR - resL) {
            resL = curMin; resR = curMax;
        }
    }
    return {resL, resR};
}
// Time: O(n log k) | Space: O(k)
// Key: range = [heap.top(), curMax]; shrink by advancing min list
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Find K Pairs with Smallest Sums
**Difficulty:** Medium | **LC:** 373

**Approach:** Min-heap. Start with (nums1[i], nums2[0]) for i in [0, min(k, n1)). Expand by j++.

```cpp
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> minH;
    // {sum, idx1, idx2}
    for (int i = 0; i < min(k, (int)nums1.size()); i++)
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
// Key: treat each (i, *) as a sorted list sorted by nums2
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Kth Smallest Prime Fraction
**Difficulty:** Medium | **LC:** 786

**Approach:** Each row i gives fractions arr[i]/arr[j] for j > i, sorted ascending. K-way merge on these rows.

```cpp
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
    int n = arr.size();
    // {fraction_value, i, j} — fraction = arr[i]/arr[j]
    auto cmp = [&](tuple<double,int,int> a, tuple<double,int,int> b) {
        return get<0>(a) > get<0>(b);
    };
    priority_queue<tuple<double,int,int>, vector<tuple<double,int,int>>, decltype(cmp)> minH(cmp);
    
    for (int i = 0; i + 1 < n; i++)
        minH.push({(double)arr[i]/arr[n-1], i, n-1});
    
    for (int cnt = 0; cnt < k - 1; cnt++) {
        auto [val, i, j] = minH.top(); minH.pop();
        if (j - 1 > i) minH.push({(double)arr[i]/arr[j-1], i, j-1});
    }
    auto [val, i, j] = minH.top();
    return {arr[i], arr[j]};
}
// Time: O(k log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** You have K sorted arrays totaling N elements. What's the time complexity to merge them using K-way merge vs naive?
<details><summary>Reveal</summary>
K-way merge: O(N log K). Naive (scan all K heads each time): O(NK). K-way merge wins when K is large.
</details>

**Drill 2:** How do you handle a matrix where both rows AND columns are sorted (Kth smallest)?
<details><summary>Reveal</summary>
Treat rows as K sorted lists. Initialize heap with (matrix[i][0], i, 0). Extract k-1 times, then return kth extracted value. Time O(k log n).
</details>

**Drill 3:** In K-way merge, what does each heap entry need to store?
<details><summary>Reveal</summary>
At minimum: (value, list_index). If accessing by index: also (element_index). For linked lists: just the node pointer (node.val is the value, node.next gives the next element).
</details>

**Drill 4:** "Smallest range containing at least one element from each of K lists." How does K-way merge help?
<details><summary>Reveal</summary>
The heap always has exactly one element from each list (the current frontier). The range = [heap.min, current_max]. Advance the minimum's list to try to shrink the range. Stop when any list is exhausted.
</details>

**Drill 5:** Can you use K-way merge to sort an array that's "k-sorted" (each element is at most k positions from its sorted position)?
<details><summary>Reveal</summary>
Yes! Split into K groups or use a sliding window heap of size k+1. Extract min, add next element. O(n log k) time.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Merge K lists (n total) | O(n log K) | O(K) |
| Kth in sorted matrix n×n | O(k log n) | O(n) |
| Smallest range | O(n log K) | O(K) |
| K pairs smallest sums | O(k log k) | O(k) |
| K-sorted array sort | O(n log k) | O(k) |

---

## 9. Common Follow-up Questions

**Q: What if the K lists have very different lengths?**
A: Still O(n log K) — the log K factor comes from heap operations, independent of list lengths.

**Q: Could you do this without extra space?**
A: For linked lists, divide-and-conquer merge-2-at-a-time: O(n log K) time, O(log K) recursion stack.

**Q: How would you parallelize this?**
A: Parallel K-way merge: use tournament tree or parallel reduce. Each parallel merge of 2 takes O(n) and you have log K levels → O(n log K / num_processors).

**Q: Kth smallest but K can be up to n²?**
A: For sorted matrix, binary search on value range [lo, hi], count elements ≤ mid using staircase walk: O(n log(max-min)).

---

## 10. Cross-Pattern Connections

- **P42 (Top-K):** Single heap for top-K; K-way merge uses heap to track K frontiers
- **P43 (Two Heaps):** Both use heaps as core; different invariants
- **P19 (Multi-Source BFS):** Multiple starting points, like multiple list heads
- **P23 (Dijkstra):** Also extracts global minimum via heap; structural similarity
- **P74 (Merge Sorted Lists):** P21 merge-2 is the building block; K-way merge generalizes it
