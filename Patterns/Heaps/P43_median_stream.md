# P43 — Median of Data Stream (Two Heaps)

## 1. First-Timer Explanation

### What Is It?
The **two-heap / median stream** pattern maintains two heaps to efficiently track the median of a dynamically growing set of numbers. One heap holds the lower half (max-heap), the other holds the upper half (min-heap). The median is derived from the tops of these heaps.

### Analogy
Imagine splitting a line of people by height. Left side: short people, tallest at the back (max-heap). Right side: tall people, shortest at the front (min-heap). The median is either the tallest-short person, the shortest-tall person, or their average. When someone new joins, route them to the correct side, then rebalance if one side gets too long.

### Visual Walkthrough
```
Add 1: lower=[1]  upper=[]      median = 1
Add 2: lower=[1]  upper=[2]     median = (1+2)/2 = 1.5
Add 3: lower=[1,2] upper=[3]    → rebalance: lower=[1,2] upper=[3], but size diff=1
       lower size = upper size  → wrong → lower=[1] upper=[2,3] rebalance
       Actually: push to lower, if lower.top > upper.push, move
       
       Correct trace:
       Add 3 → push to lower (max-heap) → lower=[1,2,3]
       Move lower.top(3) to upper → lower=[1,2] upper=[3]
       Size diff ok. median = lower.top = 2

Add 4: push to lower → lower=[1,2,4]? No:
       push 4 to lower → top=4, move to upper → lower=[1,2] upper=[3,4]
       Rebalance: sizes equal. median = (2+3)/2 = 2.5

lower (max-heap): [1, 2]   ← lower half, top = 2
upper (min-heap): [3, 4]   ← upper half, top = 3
sizes equal → median = (2+3)/2.0 = 2.5 ✓
```

### Invariants to Maintain
1. Every element in `lower` ≤ every element in `upper`
2. `|lower.size() - upper.size()| ≤ 1`
3. If sizes differ, `lower` has the extra element (so median = lower.top())

### When to Use
- "Median of a stream"
- "Running median after each insertion"
- "Sliding window median" (harder variant — use two multisets)

### When NOT to Use
- Static array → just sort
- Only need max or min → single heap

### Common Mistakes
1. Not maintaining the ordering invariant (lower ≤ upper)
2. Wrong rebalancing direction
3. Accessing top of empty heap
4. Integer overflow when averaging — cast to `double`

---

## 2. Revision Card

**Recognition Signal:** "median of stream", "running median", "find median after each insertion"

**Core Idea:** Two heaps: max-heap `lower` (left half) + min-heap `upper` (right half). After each insert, fix ordering then balance sizes.

**Trigger Keywords:** median, stream, data structure median, running median

**Complexity:**
| Operation | Time | Space |
|-----------|------|-------|
| addNum | O(log n) | O(n) |
| findMedian | O(1) | — |

---

## 3. Interview Tell Signs

- "Design a data structure that supports..." → think heaps or segment tree
- "Median" + "stream/dynamic" → two heaps
- "Median" + "sliding window" → two multisets with lazy deletion
- Numbers arrive one by one, need median at each step → two heaps

---

## 4. C++ Template

```cpp
#include <queue>
using namespace std;

class MedianFinder {
    priority_queue<int> lower;                          // max-heap: left half
    priority_queue<int, vector<int>, greater<int>> upper; // min-heap: right half
    
public:
    void addNum(int num) {
        // Step 1: push to lower
        lower.push(num);
        
        // Step 2: fix ordering (ensure lower.top ≤ upper.top)
        if (!upper.empty() && lower.top() > upper.top()) {
            upper.push(lower.top()); lower.pop();
        }
        
        // Step 3: rebalance sizes (lower can have at most 1 extra)
        if (lower.size() > upper.size() + 1) {
            upper.push(lower.top()); lower.pop();
        } else if (upper.size() > lower.size()) {
            lower.push(upper.top()); upper.pop();
        }
    }
    
    double findMedian() {
        if (lower.size() > upper.size()) return lower.top();
        return (lower.top() + (double)upper.top()) / 2.0;
    }
};
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "The key insight is that the median only depends on the boundary between lower and upper halves. So I'll maintain a max-heap for the lower half and a min-heap for the upper half. After each insertion, I enforce two invariants: ordering (every lower element ≤ every upper element) and balance (sizes differ by at most 1). AddNum is O(log n) and findMedian is O(1)."

**Checklist:**
- [ ] Draw the two-heap picture
- [ ] State the two invariants clearly
- [ ] Walk through steps: push, fix order, rebalance
- [ ] Handle odd/even size cases for findMedian
- [ ] Mention sliding window median variant (multisets)

---

## 6. Problems

### Problem 1: Find Median from Data Stream
**Difficulty:** Hard | **LC:** 295

**Approach:** Classic two-heap. See template above.

```cpp
class MedianFinder {
    priority_queue<int> lo;
    priority_queue<int, vector<int>, greater<int>> hi;
    
public:
    void addNum(int num) {
        lo.push(num);
        if (!hi.empty() && lo.top() > hi.top()) {
            hi.push(lo.top()); lo.pop();
        }
        if (lo.size() > hi.size() + 1) {
            hi.push(lo.top()); lo.pop();
        } else if (hi.size() > lo.size()) {
            lo.push(hi.top()); hi.pop();
        }
    }
    
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + (double)hi.top()) / 2.0;
    }
};
// addNum: O(log n) | findMedian: O(1) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Sliding Window Median
**Difficulty:** Hard | **LC:** 480

**Approach:** Two multisets (ordered, allow duplicates) instead of heaps. Remove elements that slide out using `erase(iterator)`.

```cpp
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> lo, hi; // lo = lower half, hi = upper half
    
    auto rebalance = [&]() {
        // ensure lo size = hi size or lo size = hi size + 1
        while (lo.size() > hi.size() + 1) {
            hi.insert(*lo.rbegin()); lo.erase(prev(lo.end()));
        }
        while (hi.size() > lo.size()) {
            lo.insert(*hi.begin()); hi.erase(hi.begin());
        }
    };
    
    auto addNum = [&](int x) {
        lo.insert(x);
        // fix ordering
        if (!hi.empty() && *lo.rbegin() > *hi.begin()) {
            hi.insert(*lo.rbegin()); lo.erase(prev(lo.end()));
        }
        rebalance();
    };
    
    auto removeNum = [&](int x) {
        if (lo.count(x)) { lo.erase(lo.find(x)); }
        else { hi.erase(hi.find(x)); }
        rebalance();
    };
    
    auto getMedian = [&]() -> double {
        if (lo.size() > hi.size()) return *lo.rbegin();
        return (*lo.rbegin() + (double)*hi.begin()) / 2.0;
    };
    
    vector<double> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        addNum(nums[i]);
        if (i >= k - 1) {
            res.push_back(getMedian());
            removeNum(nums[i - k + 1]);
        }
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

### Problem 3: IPO (Maximize Capital)
**Difficulty:** Hard | **LC:** 502

**Approach:** Two heaps: min-heap by capital (sort projects by cost), max-heap by profit (available projects). Unlock projects as capital grows.

```cpp
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    // min-heap by capital requirement
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> locked;
    priority_queue<int> available; // max-heap by profit
    
    for (int i = 0; i < n; i++) locked.push({capital[i], profits[i]});
    
    for (int i = 0; i < k; i++) {
        // unlock all projects we can afford
        while (!locked.empty() && locked.top().first <= w) {
            available.push(locked.top().second); locked.pop();
        }
        if (available.empty()) break; // can't afford any project
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

### Problem 4: Maximum Average Pass Ratio
**Difficulty:** Medium | **LC:** 1792

**Approach:** Max-heap by "gain in pass ratio" if one extra student joins. Greedily assign extra students to class with highest marginal gain.

```cpp
double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
    auto gain = [](double pass, double total) {
        return (pass+1)/(total+1) - pass/total;
    };
    
    priority_queue<pair<double,int>> maxH;
    for (int i = 0; i < (int)classes.size(); i++)
        maxH.push({gain(classes[i][0], classes[i][1]), i});
    
    for (int s = 0; s < extraStudents; s++) {
        auto [g, i] = maxH.top(); maxH.pop();
        classes[i][0]++; classes[i][1]++;
        maxH.push({gain(classes[i][0], classes[i][1]), i});
    }
    
    double sum = 0;
    for (auto& c : classes) sum += (double)c[0] / c[1];
    return sum / classes.size();
}
// Time: O((n + e) log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** After each integer is added to a dataset, return the current median. How many heaps do you need?
<details><summary>Reveal</summary>
Two heaps: max-heap for lower half, min-heap for upper half. Median = top of larger heap, or average of both tops.
</details>

**Drill 2:** What's the key difference between using two heaps vs two sorted multisets for median tracking?
<details><summary>Reveal</summary>
Heaps don't support arbitrary deletion. For sliding window median, you need to delete the element leaving the window — multiset's `erase(iterator)` handles this in O(log n). Heaps would require lazy deletion tricks.
</details>

**Drill 3:** The two heaps have sizes lo=4, hi=3. What is the median?
<details><summary>Reveal</summary>
lo has the extra element (size 4 > size 3 by 1). Median = lo.top() (the max of the lower half).
</details>

**Drill 4:** You add 7 to the system, but lo.top()=5 and hi.top()=10. Trace the rebalancing.
<details><summary>Reveal</summary>
Push 7 to lo → lo.top()=7. Check: 7 < 10, ordering OK. Rebalance sizes as needed. If lo is now too large, move lo.top() to hi.
</details>

**Drill 5:** You need the median of each sliding window of size k=3 over [1,3,5,2,4]. Can you use two heaps?
<details><summary>Reveal</summary>
Not directly — heaps don't support efficient deletion. Use two multisets instead, which support O(log n) deletion by iterator, maintaining the same lower/upper half invariant.
</details>

---

## 8. Complexity Cheatsheet

| Approach | addNum | findMedian | Delete (window) | Space |
|----------|--------|------------|-----------------|-------|
| Two heaps | O(log n) | O(1) | Not supported | O(n) |
| Two multisets | O(log n) | O(1) | O(log n) | O(n) |
| Sort each time | O(n log n) | O(1) | O(n) | O(n) |
| Segment tree | O(log V) | O(log V) | O(log V) | O(V) |

---

## 9. Common Follow-up Questions

**Q: What if numbers can repeat?**
A: Heaps handle duplicates naturally. Multisets too.

**Q: Sliding window median?**
A: Two multisets. Use `lo.erase(lo.find(x))` to delete by value (not all occurrences).

**Q: What if k is odd vs even?**
A: Odd k → median is always lo.top() (lower has extra). Even k → average of lo.top() and hi.top(). Your code handles both if you check sizes.

**Q: Can you do it with one data structure?**
A: Order statistics tree (policy-based in C++) supports O(log n) find_by_order and order_of_key, giving O(log n) median. Segment tree on compressed values also works.

---

## 10. Cross-Pattern Connections

- **P42 (Top-K):** Single heap; this pattern uses two heaps for boundary tracking
- **P44 (K-Way Merge):** Also uses min-heap as core mechanism
- **P35 (Interval DP):** Burst Balloons; different but both involve careful boundary management
- **P64 (Monotonic Stack):** Alternative for some "running max/min" problems
