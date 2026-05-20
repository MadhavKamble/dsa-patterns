# P67 — Stock Span and Sliding Window Maximum

## 1. First-Timer Explanation

### What Is It?
The **stock span** problem asks: for each day, how many consecutive days (including today) have had prices ≤ today's price? The **sliding window maximum** asks: given a sliding window of size k, what's the maximum in each window?

Both use the same deque-based or stack-based approach to answer range queries efficiently.

### Stock Span Insight
```
Prices: [100, 80, 60, 70, 60, 75, 85]
Spans:  [  1,  1,  1,  2,  1,  4,  6]

For price=75 (day 5): consecutive days with price ≤ 75?
70 ≤ 75 ✓, 60 ≤ 75 ✓, 80 > 75 ✗ → span = 3+1 = 4

Key: instead of looking back each time (O(n²)), maintain a stack of "blocking" days.
```

### Sliding Window Maximum
```
nums = [1,3,-1,-3,5,3,6,7], k=3

Window [1,3,-1] → max=3
Window [3,-1,-3] → max=3
Window [-1,-3,5] → max=5
...

Use a deque maintaining indices of potential maximums in decreasing order.
Elements smaller than the new element can never be the maximum → pop them.
```

### When to Use
- "Stock span" → decreasing monotone stack
- "Maximum in sliding window" → deque maintaining candidates
- "Maximum/minimum in contiguous range" → deque-based approach

---

## 2. Revision Card

**Recognition Signal:** "span of stock", "max in sliding window", "running max"

**Core Idea (Stock Span):** Maintain a stack of (price, span). When current price ≥ stack top, pop and accumulate span. Push (cur_price, total_span).

**Core Idea (Sliding Window Max):** Deque maintains indices in decreasing order of value. Pop from front when out of window. Pop from back when new element is larger. Front = max.

**Trigger Keywords:** span, sliding window max, range max, deque, consecutive

**Complexity:** O(n) time (each element pushed/popped once), O(n) space

---

## 3. Interview Tell Signs

- "For each element, count consecutive previous elements ≤ current" → stock span
- "Maximum element in every window of size k" → deque monotone
- "Days until warmer/cooler" → NGE/NSE variant (P64)
- "Online stream, report max in last k elements" → deque

---

## 4. C++ Template

```cpp
#include <stack>
#include <deque>
#include <vector>
using namespace std;

// ── Stock Span (online, one by one) ──────────────────────────────────────────
class StockSpanner {
    stack<pair<int,int>> stk; // {price, span}
public:
    int next(int price) {
        int span = 1;
        while (!stk.empty() && stk.top().first <= price) {
            span += stk.top().second; stk.pop();
        }
        stk.push({price, span});
        return span;
    }
};

// ── Sliding Window Maximum (offline, all at once) ─────────────────────────────
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq; // stores indices, decreasing values
    vector<int> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        // Remove indices out of window
        if (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();
        // Remove smaller elements from back (they'll never be max)
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1) res.push_back(nums[dq.front()]); // front = max
    }
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Sliding Window Max):**
> "I maintain a deque of indices where elements are in decreasing order of value. For each new element: first, remove indices that are out of the current window from the front. Then, remove all indices from the back whose values are smaller than the new element — they can never be the window maximum while the new element is in the window. Add the new index to the back. The front of the deque is always the window maximum."

---

## 6. Problems

### Problem 1: Online Stock Span
**Difficulty:** Medium | **LC:** 901

```cpp
class StockSpanner {
    stack<pair<int,int>> stk;
public:
    int next(int price) {
        int span = 1;
        while (!stk.empty() && stk.top().first <= price) {
            span += stk.top().second; stk.pop();
        }
        stk.push({price, span});
        return span;
    }
};
// Each call: O(1) amortized | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Sliding Window Maximum
**Difficulty:** Hard | **LC:** 239

```cpp
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (!dq.empty() && dq.front() < i-k+1) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();
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

### Problem 3: Jump Game VI (Sliding Window Max + DP)
**Difficulty:** Medium | **LC:** 1696

**Approach:** `dp[i]` = max score reaching i. `dp[i] = max(dp[i-k..i-1]) + nums[i]`. Sliding window max on dp array.

```cpp
int maxResult(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];
    deque<int> dq;
    dq.push_back(0);
    
    for (int i = 1; i < n; i++) {
        if (dq.front() < i - k) dq.pop_front();
        dp[i] = dp[dq.front()] + nums[i];
        while (!dq.empty() && dp[dq.back()] <= dp[i]) dq.pop_back();
        dq.push_back(i);
    }
    return dp[n-1];
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Constrained Subsequence Sum (Sliding Window Max + DP)
**Difficulty:** Hard | **LC:** 1425

```cpp
int constrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    deque<int> dq;
    
    for (int i = 0; i < n; i++) {
        dp[i] = nums[i];
        if (!dq.empty()) dp[i] = max(dp[i], dp[dq.front()] + nums[i]);
        while (!dq.empty() && dp[dq.back()] <= dp[i]) dq.pop_back();
        if (dp[i] > 0) dq.push_back(i); // only keep if dp[i]>0 (positive contribution)
        if (!dq.empty() && dq.front() <= i-k) dq.pop_front();
    }
    return *max_element(dp.begin(), dp.end());
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Stock Span for prices [100, 80, 60, 70, 60, 75, 85]. Trace spans.
<details><summary>Reveal</summary>
100: stack empty, push (100,1), span=1. 80: 80<100, push (80,1), span=1. 60: 60<80, push (60,1), span=1. 70: 70>60 → pop(60,1) span=2; 70<80 → push(70,2), span=2. 60: 60<70, push(60,1), span=1. 75: 75>60→pop(60,1) span=2; 75>70→pop(70,2) span=4; 75<80→push(75,4), span=4. 85: 85>75→pop(75,4) span=5; 85>80→pop(80,1) span=6; 85<100→push(85,6), span=6. Spans: [1,1,1,2,1,4,6] ✓.
</details>

**Drill 2:** Sliding window max of [2,1,5,3,6,4,8,7], k=4. What are the window maxima?
<details><summary>Reveal</summary>
[2,1,5,3] → 5; [1,5,3,6] → 6; [5,3,6,4] → 6; [3,6,4,8] → 8; [6,4,8,7] → 8. Result: [5,6,6,8,8].
</details>

**Drill 3:** Why use a deque instead of a stack for sliding window max?
<details><summary>Reveal</summary>
A stack only allows operations at one end. For sliding window max, we need to: (1) remove expired elements from the FRONT (oldest), and (2) remove smaller elements from the BACK (newest). This requires a double-ended queue (deque) — not possible with a stack alone.
</details>

**Drill 4:** Jump Game VI: why is it O(n) with the deque instead of O(nk)?
<details><summary>Reveal</summary>
O(nk) naive: for each i, scan back k positions for max dp value. With deque: the max dp in [i-k, i-1] is always at the front. Each index is pushed and popped at most once → O(n) total operations.
</details>

**Drill 5:** In sliding window max, what happens if all elements in the window are equal?
<details><summary>Reveal</summary>
The deque stores one index per element (since new element < existing → don't pop; equal → pop since it will also be `< nums[i]+ε` check... actually equal elements: `nums[dq.back()] < nums[i]` — strict less, so equal elements stay). The deque might contain multiple equal indices. The front is the oldest equal index. When it expires, the next equal index becomes front. Correct result throughout.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Stock Spanner (per call) | O(1) amortized | O(n) |
| Sliding Window Max | O(n) | O(k) |
| Jump Game VI | O(n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: Sliding window minimum (not maximum)?**
A: Same deque approach, but pop from back when new element is SMALLER (not larger). Front = minimum.

**Q: Sliding window sum?**
A: Simple prefix sum: `sum[i-k+1..i] = prefix[i+1] - prefix[i-k+1]`. O(n) without any special structure.

**Q: Maximum product in a sliding window?**
A: Tricky due to sign changes. Track both max and min (min can become max when multiplied by negative). More complex than the sum/max version.

---

## 10. Cross-Pattern Connections

- **P64 (Monotonic Stack):** Stock span IS monotone stack; sliding window max uses same "pop smaller" idea
- **P08 (Sliding Window):** Fixed-size window; deque adds efficient max tracking
- **P30 (1D DP):** Jump Game VI uses DP + sliding window max
- **P42 (Heap):** Heap gives O(n log k) for sliding window max; deque gives O(n)
