# Pattern 08: Fixed Size Sliding Window

## Category
Sliding Window

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 346. Moving Average from Data Stream | Easy | https://leetcode.com/problems/moving-average-from-data-stream/ |
| 2 | 643. Maximum Average Subarray I | Easy | https://leetcode.com/problems/maximum-average-subarray-i/ |
| 3 | 2985. Calculate Compressed Mean | Easy | https://leetcode.com/problems/calculate-compressed-mean/ |
| 4 | 3254. Find the Power of K-Size Subarrays I | Medium | https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/ |
| 5 | 3318. Find X-Sum of All K-Long Subarrays I | Medium | https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/ |

---

## 1. First-Timer Explanation

### What is this pattern?
When you need to compute something (sum, max, average, frequency) over every contiguous subarray of a fixed size k, the brute force re-computes from scratch for each window: O(n × k). The sliding window trick observes that consecutive windows overlap in k-1 elements — so when moving the window one step right, you only need to ADD the new element and REMOVE the old leftmost element. One O(1) update per step = O(n) total.

### Real-World Analogy
You're calculating the 7-day moving average of stock prices. Each day, add today's price and subtract the price from 7 days ago. You don't recompute all 7 days — you just update the edges.

### Visual Walkthrough
```
Array: [2, 1, 5, 1, 3, 2], k=3
Find max sum of any subarray of size 3.

Initial window: [2, 1, 5], sum=8
Slide right:
  Add nums[3]=1, remove nums[0]=2 → [1, 5, 1], sum=8-2+1=7
  Add nums[4]=3, remove nums[1]=1 → [5, 1, 3], sum=7-1+3=9  ← max!
  Add nums[5]=2, remove nums[2]=5 → [1, 3, 2], sum=9-5+2=6
Max sum = 9
```

### When TO use this pattern
- "Find max/min/average/sum of every subarray of size k"
- "Moving average", "sliding maximum"
- Any per-window aggregation over fixed-length windows

### When NOT to use this pattern
- Window size is not fixed (use variable sliding window)
- Non-contiguous subsets (use sorting or DP)

### Common Beginner Mistakes
- **Build the first window manually**: don't start sliding from index 0
- **Remove the element k steps back**: `nums[i - k]`, not `nums[i - k + 1]`
- **Frequency map comparison**: comparing two maps is O(26) or O(alphabet size), treat as O(1) for interviews
- **Not initializing the first window**: must sum first k elements before the sliding loop

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "every subarray of size k", "moving average", "window of size k" |
| Core Idea | Build first window manually; slide by add-new, remove-old |
| Trigger Keywords | "subarray of length k", "fixed window", "moving average" |
| Avoid When | Window size varies based on condition |
| Time Complexity | O(n) |
| Space Complexity | O(1) or O(k) for frequency map |

**Gotchas:**
- Build first window in a separate loop (0 to k-1), then slide from k to n-1
- The element leaving the window is at index `i - k` when sliding to index `i`
- For frequency-based windows: compare full freq maps (O(1) amortized if alphabet is fixed)

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"every subarray of size k"` → fixed window
- `"moving average of size k"` → fixed window with running sum
- `"k consecutive elements"` → fixed window

### Constraint hints
- k is given as a fixed constant → fixed size window
- O(n × k) too slow → O(n) fixed window

---

## 4. C++ Template

```cpp
/*
 * Pattern: Fixed Size Sliding Window
 * Use when: aggregate over every window of fixed size k
 * Time: O(n) | Space: O(1)
 */

double maxAverageSubarray(vector<int>& nums, int k) {
    double windowSum = 0;

    // Step 1: build the first window
    for (int i = 0; i < k; i++) windowSum += nums[i];
    double maxAvg = windowSum / k;

    // Step 2: slide the window
    for (int i = k; i < (int)nums.size(); i++) {
        windowSum += nums[i];       // add new right element
        windowSum -= nums[i - k];  // remove old left element
        maxAvg = max(maxAvg, windowSum / k);
    }
    return maxAvg;
}

// Fixed window with frequency map (for anagram-type problems)
vector<int> findAllAnagrams(string s, string p) {
    vector<int> result;
    if (s.size() < p.size()) return result;
    int k = p.size();

    vector<int> pFreq(26, 0), wFreq(26, 0);
    for (char c : p) pFreq[c - 'a']++;

    // build first window
    for (int i = 0; i < k; i++) wFreq[s[i] - 'a']++;
    if (pFreq == wFreq) result.push_back(0);

    // slide
    for (int i = k; i < (int)s.size(); i++) {
        wFreq[s[i] - 'a']++;             // add new
        wFreq[s[i - k] - 'a']--;         // remove old
        if (pFreq == wFreq) result.push_back(i - k + 1);
    }
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Since k is fixed, every window of size k shares k-1 elements with the previous window. Instead of recomputing from scratch — O(n×k) — I maintain a running sum and update it by adding the new element and subtracting the element that just left. This gives O(n) total."

### Interview Flow Checklist
- [ ] Confirm: is k fixed?
- [ ] Build first window
- [ ] Slide: add new, remove old
- [ ] Update answer per window
- [ ] Handle edge: n < k (return -1 or empty)

---

## 6. Problems

---

### Problem 1: 643. Maximum Average Subarray I
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/maximum-average-subarray-i/
**Why this pattern fits:** Fixed window sum / k, find maximum

**Optimal C++ Solution:**
```cpp
// Maximum Average Subarray I
// Time: O(n) | Space: O(1)

double findMaxAverage(vector<int>& nums, int k) {
    double sum = 0;
    for (int i = 0; i < k; i++) sum += nums[i];
    double maxSum = sum;

    for (int i = k; i < (int)nums.size(); i++) {
        sum += nums[i] - nums[i - k];
        maxSum = max(maxSum, sum);
    }
    return maxSum / k;
}
```

**Edge Cases:**
- [ ] Array length exactly k
- [ ] All negative numbers

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 346. Moving Average from Data Stream
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/moving-average-from-data-stream/
**Why this pattern fits:** Online version — maintain running sum, drop oldest element when window full

**Optimal C++ Solution:**
```cpp
// Moving Average from Data Stream
// Time: O(1) per call | Space: O(k) for queue

class MovingAverage {
    queue<int> window;
    double sum = 0;
    int size;

public:
    MovingAverage(int size) : size(size) {}

    double next(int val) {
        window.push(val);
        sum += val;

        if ((int)window.size() > size) {
            sum -= window.front();
            window.pop();
        }
        return sum / window.size();
    }
};
```

**Edge Cases:**
- [ ] Window not yet full (first few elements)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 3254. Find the Power of K-Size Subarrays I
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/
**Why this pattern fits:** For each window of size k, check if it's a consecutive increasing sequence

**Optimal C++ Solution:**
```cpp
// Find the Power of K-Size Subarrays
// Power = max element if all k elements are consecutive and increasing, else -1
// Time: O(n) | Space: O(1)

vector<int> resultsArray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> result;
    int consecutive = 1;  // length of current consecutive increasing run

    for (int i = 1; i < k; i++) {
        if (nums[i] == nums[i-1] + 1) consecutive++;
    }
    result.push_back(consecutive == k ? nums[k-1] : -1);

    for (int i = k; i < n; i++) {
        if (nums[i] == nums[i-1] + 1) consecutive++;
        else consecutive = 1;
        // if consecutive >= k, the last k elements form a consecutive run
        result.push_back(consecutive >= k ? nums[i] : -1);
    }
    return result;
}
```

**Edge Cases:**
- [ ] k=1 (every element is its own power)
- [ ] All elements same (no consecutive increasing)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given an array and window size k, find the minimum value in each window of size k.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Window + Monotonic Deque (P10)
**Reason:** Naive fixed window minimum is O(n×k). For O(n), use a monotonic deque (Pattern 10). The deque maintains candidates for minimum in the current window.
</details>

---

**Drill 2:**
> Given a binary array, count how many windows of size k contain exactly m ones.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Size Sliding Window
**Reason:** Maintain a count of 1s in the window. Slide: add new element, subtract old. When count == m, increment result.
</details>

---

**Drill 3:**
> Find the sum of all products of adjacent k-element windows in an array.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Size Sliding Window
**Reason:** Maintain a running product. But note: products can't be updated by add/remove like sums — you'd need to divide, which fails if element is 0. Better: track the product and recompute when a 0 enters/leaves, or use log sums to convert to addition.
</details>

---

**Drill 4:**
> Given a string, find all starting indices of substrings of length k that are pangrams (contain all 26 letters).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Size Sliding Window + frequency map
**Reason:** Maintain a frequency map of size 26 for the window. Track how many distinct characters are present. If count == 26, record the start index. Add/remove chars as window slides.
</details>

---

**Drill 5:**
> Given an array, for each window of size k, find whether the window is "balanced" (max - min ≤ threshold).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Window + Two Monotonic Deques
**Reason:** Maintain one monotonic increasing deque for min, one decreasing for max. Both slide the window in O(1) per step. Check max_deque.front() - min_deque.front() ≤ threshold.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Sum/average | O(n) | O(1) | Running sum update |
| Frequency matching | O(n × 26) ≈ O(n) | O(26) | Vector comparison |
| Max/min per window | O(n) with deque | O(k) | Monotonic deque |
| Moving average (online) | O(1) per call | O(k) | Queue for window |

---

## 9. Common Follow-up Questions

1. What if k can vary per query? (Recompute for each k — or use sparse tables for O(1) range min/max queries)
2. What if the array is a stream (online)? (Use a queue of size k — Moving Average problem)
3. What if you need BOTH min and max per window? (Two monotonic deques — one increasing, one decreasing)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Monotonic Deque | Need min/max per fixed window | 239. Sliding Window Maximum |
| Frequency Map | Anagram/permutation detection per window | 438. Find All Anagrams |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
