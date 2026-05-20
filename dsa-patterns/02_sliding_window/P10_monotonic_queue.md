# Pattern 10: Monotonic Queue for Max/Min in Window

## Category
Sliding Window

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 239. Sliding Window Maximum | Hard | https://leetcode.com/problems/sliding-window-maximum/ |
| 2 | 862. Shortest Subarray with Sum at Least K | Hard | https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/ |
| 3 | 1696. Jump Game VI | Medium | https://leetcode.com/problems/jump-game-vi/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Finding the maximum or minimum element inside a sliding window naively takes O(k) per window → O(n×k) total. The monotonic deque (double-ended queue) reduces this to O(1) per window → O(n) total.

**How it works for maximum:**
- Maintain a deque of indices in **decreasing order of values** (front = index of maximum)
- When adding a new element: pop from the BACK all indices whose values are ≤ new element (they can never be the maximum anymore — the new element is bigger AND more recently added)
- When the front of the deque is outside the current window: pop it from the FRONT
- The deque front always gives the maximum for the current window

### Real-World Analogy
You're in a competitive job market. The "max" at any point is the most capable candidate currently in consideration. When a new, more capable candidate arrives, all less capable candidates who haven't been hired yet are immediately eliminated (they'll never be picked over the better candidate). This keeps the "current best" always at the front of your queue.

### Visual Walkthrough
```
Array: [1, 3, -1, -3, 5, 3, 6, 7], k=3

i=0: add 0(val=1). deque=[0]
i=1: add 1(val=3). pop 0 (3>1). deque=[1]
i=2: add 2(val=-1). deque=[1,2]. window=[0,2] → max=nums[1]=3
i=3: add 3(val=-3). deque=[1,2,3]. window=[1,3] → max=nums[1]=3
i=4: add 4(val=5). pop 3(-3),2(-1),1(3) (all < 5). deque=[4].
     window=[2,4] → max=nums[4]=5. Also pop front 1 (outside window? no, 1<2? yes) → already popped.
i=5: add 5(val=3). deque=[4,5]. window=[3,5] → max=nums[4]=5
i=6: add 6(val=6). pop 5(3),4(5). deque=[6]. window=[4,6] → max=nums[6]=6
i=7: add 7(val=7). pop 6(6). deque=[7]. window=[5,7] → max=nums[7]=7

Result: [3, 3, 5, 5, 6, 7]
```

### When TO use this pattern
- Find max or min value in every window of size k (fixed or variable)
- DP optimization where dp[i] depends on max/min of recent dp values
- Shortest subarray with sum ≥ k (with negative numbers)

### When NOT to use this pattern
- Simple sum/average (no need for deque)
- Max/min in entire array (just scan once)
- Only one window (no sliding needed)

### Common Beginner Mistakes
- **Storing indices not values**: deque stores indices — values are looked up by index
- **Pop from BACK when adding**: for max deque, pop back elements ≤ new value
- **Pop from FRONT when expired**: check if deque.front() < i - k + 1
- **Order of operations**: check front validity BEFORE reading maximum

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | Max/min per window efficiently, DP with range max/min optimization |
| Core Idea | Deque maintains decreasing/increasing order; front = current window max/min |
| Trigger Keywords | "sliding window maximum/minimum", "DP max over recent k elements" |
| Avoid When | Sum/average windows (simpler), only one window needed |
| Time Complexity | O(n) — each element pushed/popped at most once |
| Space Complexity | O(k) for the deque |

**Gotchas:**
- Deque stores INDICES (so you can check window expiry)
- Pop from BACK on add (smaller elements are useless when new larger arrives)
- Pop from FRONT on read (if index is out of window)
- For MINIMUM window: use increasing deque (pop back if back value ≥ new value)

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"sliding window maximum"` → monotonic decreasing deque
- `"shortest subarray with sum ≥ k"` with negative numbers → prefix sum + monotonic deque
- `"jump game, maximize score over last k steps"` → deque DP optimization

### Constraint hints
- Max/min per window, n up to 10^5 → O(n log k) with heap or O(n) with deque
- Contains negative numbers + min subarray constraint → standard sliding window fails → deque

---

## 4. C++ Template

```cpp
/*
 * Pattern: Monotonic Deque for Sliding Window Max/Min
 * Use when: max/min per window, DP range max
 * Time: O(n) | Space: O(k)
 */

// SLIDING WINDOW MAXIMUM
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // stores INDICES, front = index of max
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // remove elements outside current window
        if (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();

        // pop back elements smaller than current (they'll never be max)
        while (!dq.empty() && nums[dq.back()] < nums[i]) dq.pop_back();

        dq.push_back(i);  // add current index

        // window is full starting from index k-1
        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}

// SLIDING WINDOW MINIMUM (change to increasing deque)
vector<int> minSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        if (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();
        while (!dq.empty() && nums[dq.back()] > nums[i]) dq.pop_back(); // > for min
        dq.push_back(i);
        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Finding max in each window naively is O(n×k). With a monotonic deque we can do O(n).
The deque stores indices in decreasing order of values. When we add a new element, we pop all smaller elements from the back — they can never be the maximum while this new (larger and newer) element is in the window. Elements that fall outside the window are removed from the front.
The front of the deque is always the maximum of the current window."

### Interview Flow Checklist
- [ ] Explain O(n) amortized (each element pushed/popped once)
- [ ] Draw the deque state for a small example
- [ ] Code: pop front (expiry check), pop back (monotonicity), push, read front
- [ ] Distinguish max deque (pop when back < new) vs min deque (pop when back > new)

---

## 6. Problems

---

### Problem 1: 239. Sliding Window Maximum
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/sliding-window-maximum/
**Why this pattern fits:** Find max per window of fixed size k → monotonic decreasing deque

**Optimal C++ Solution:**
```cpp
// Sliding Window Maximum
// Time: O(n) | Space: O(k)

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // indices, front = max of current window
    vector<int> result;

    for (int i = 0; i < (int)nums.size(); i++) {
        // expire elements outside window
        while (!dq.empty() && dq.front() <= i - k) dq.pop_front();

        // maintain decreasing order: pop smaller elements from back
        while (!dq.empty() && nums[dq.back()] <= nums[i]) dq.pop_back();

        dq.push_back(i);

        if (i >= k - 1) result.push_back(nums[dq.front()]);
    }
    return result;
}
```

**Complexity Analysis:**
- Time: O(n) — each index is pushed and popped at most once
- Space: O(k)

**Edge Cases:**
- [ ] k = 1 (window size 1 → answer is the array itself)
- [ ] k = n (one window = entire array)
- [ ] All elements same

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 862. Shortest Subarray with Sum at Least K
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
**Why this pattern fits:** With negative numbers, standard sliding window fails; use prefix sums + monotone increasing deque to find minimum-width subarray with sum ≥ K

**Problem Summary:**
Find the length of the shortest contiguous subarray with sum ≥ k. Numbers can be negative.

**Approach Walkthrough:**
1. Compute prefix sums: prefix[i] = sum of first i elements
2. For each right endpoint r, find the smallest l such that prefix[r] - prefix[l] ≥ k → l should be as large as possible while prefix[l] is as small as possible
3. Maintain a monotonic INCREASING deque of prefix sum indices
4. When prefix[r] - prefix[front] ≥ k: record answer, pop front (can do better with later r)

**Optimal C++ Solution:**
```cpp
// Shortest Subarray with Sum at Least K
// Time: O(n) | Space: O(n)

int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + nums[i];

    deque<int> dq;  // indices into prefix; increasing prefix sum order
    int minLen = INT_MAX;

    for (int i = 0; i <= n; i++) {
        // while front gives a valid subarray, record and pop
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            minLen = min(minLen, i - dq.front());
            dq.pop_front();
        }
        // maintain increasing prefix sum in deque
        while (!dq.empty() && prefix[dq.back()] >= prefix[i]) dq.pop_back();
        dq.push_back(i);
    }
    return (minLen == INT_MAX) ? -1 : minLen;
}
```

**Edge Cases:**
- [ ] No valid subarray → return -1
- [ ] Single element ≥ k

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1696. Jump Game VI
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/jump-game-vi/
**Why this pattern fits:** DP: dp[i] = max score reaching index i; depends on max dp in last k positions → deque optimizes range max

**Optimal C++ Solution:**
```cpp
// Jump Game VI
// Time: O(n) | Space: O(k)

int maxResult(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];

    deque<int> dq;  // indices, decreasing dp values
    dq.push_back(0);

    for (int i = 1; i < n; i++) {
        // expire indices outside window
        while (!dq.empty() && dq.front() < i - k) dq.pop_front();

        // dp[i] = max dp in [i-k, i-1] + nums[i]
        dp[i] = dp[dq.front()] + nums[i];

        // maintain decreasing dp deque
        while (!dq.empty() && dp[dq.back()] <= dp[i]) dq.pop_back();
        dq.push_back(i);
    }
    return dp[n - 1];
}
```

**Edge Cases:**
- [ ] k ≥ n (can jump to end in one step)
- [ ] All negative numbers

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given an array, find the maximum of the minimum values for all windows of every size from 1 to n.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Monotonic Stack + Contribution technique
**Reason:** For each element, find how large a window it can be the minimum of (using next smaller left/right). The answer for window size = that element's contribution range. Not directly deque-sliding-window, but related.
</details>

---

**Drill 2:**
> DP problem: dp[i] = max(dp[j] + cost) for j in [i-k, i-1]. How do you compute this efficiently?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Monotonic Deque DP Optimization
**Reason:** Maintain a decreasing deque of (dp[j]) values. For each i, the front of the deque gives max dp[j] in the last k positions. This is the Jump Game VI pattern generalized.
</details>

---

**Drill 3:**
> Given a circular array, find the max sum of any subarray of length exactly k.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Sliding Window (not deque needed for sum)
**Reason:** Circular: handle by considering the array doubled (2n elements). Fixed sum window of size k, iterate and track max. For max element per window, deque would be needed.
</details>

---

**Drill 4:**
> Find the minimum absolute difference between max and min in any window of size k.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Two Monotonic Deques (one for max, one for min)
**Reason:** Maintain one decreasing deque (max) and one increasing deque (min) simultaneously. For each window of size k, answer is deq_max.front() - deq_min.front().
</details>

---

**Drill 5:**
> Given a sequence of stock prices, for each day find the maximum price in the last k days (including today).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Monotonic Deque — Sliding Window Maximum
**Reason:** Classic application. Window size = k, find max per window. Use decreasing deque of indices.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Sliding Window Max/Min | O(n) | O(k) | Each element pushed/popped once |
| Shortest subarray ≥ K (neg nums) | O(n) | O(n) | Prefix sum + deque |
| DP range max optimization | O(n) | O(k) | Deque bounds last k values |
| Using heap instead of deque | O(n log k) | O(k) | Heap operations are log k |

---

## 9. Common Follow-up Questions

1. Why not use a heap? (Heap gives O(n log k); deque is O(n). For interviews, heap is more intuitive but deque is optimal)
2. How to extend to 2D maximum in rectangular window? (Row-by-row deque, then column-by-column deque — O(n²) for n×n grid)
3. Can you find the second maximum per window? (Yes — maintain a deque and track the second element, but it's complex)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| DP | Range max/min optimization | 1696. Jump Game VI |
| Prefix Sum | Negative number min subarray | 862. Shortest Subarray ≥ K |
| Fixed Sliding Window | Fixed k with max/min requirement | 239. Sliding Window Maximum |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
