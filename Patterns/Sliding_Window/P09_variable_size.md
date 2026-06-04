# Pattern 09: Variable Size Sliding Window

## Category
Sliding Window

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 3. Longest Substring Without Repeating Characters | Medium | https://leetcode.com/problems/longest-substring-without-repeating-characters/ |
| 2 | 76. Minimum Window Substring | Hard | https://leetcode.com/problems/minimum-window-substring/ |
| 3 | 209. Minimum Size Subarray Sum | Medium | https://leetcode.com/problems/minimum-size-subarray-sum/ |
| 4 | 219. Contains Duplicate II | Easy | https://leetcode.com/problems/contains-duplicate-ii/ |
| 5 | 424. Longest Repeating Character Replacement | Medium | https://leetcode.com/problems/longest-repeating-character-replacement/ |
| 6 | 713. Subarray Product Less Than K | Medium | https://leetcode.com/problems/subarray-product-less-than-k/ |
| 7 | 904. Fruit Into Baskets | Medium | https://leetcode.com/problems/fruit-into-baskets/ |
| 8 | 1004. Max Consecutive Ones III | Medium | https://leetcode.com/problems/max-consecutive-ones-iii/ |
| 9 | 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit | Medium | https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/ |
| 10 | 1493. Longest Subarray of 1's After Deleting One Element | Medium | https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/ |
| 11 | 1658. Minimum Operations to Reduce X to Zero | Medium | https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/ |
| 12 | 1838. Frequency of the Most Frequent Element | Medium | https://leetcode.com/problems/frequency-of-the-most-frequent-element/ |
| 13 | 2461. Maximum Sum of Distinct Subarrays With Length K | Medium | https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/ |
| 14 | 2516. Take K of Each Character From Left and Right | Medium | https://leetcode.com/problems/take-k-of-each-character-from-left-and-right/ |
| 15 | 2762. Continuous Subarrays | Medium | https://leetcode.com/problems/continuous-subarrays/ |
| 16 | 2779. Maximum Beauty of an Array After Applying Operation | Medium | https://leetcode.com/problems/maximum-beauty-of-an-array-after-applying-operation/ |
| 17 | 2981. Find Longest Special Substring That Occurs Thrice I | Medium | https://leetcode.com/problems/find-longest-special-substring-that-occurs-thrice-i/ |
| 18 | 3026. Maximum Good Subarray Sum | Medium | https://leetcode.com/problems/maximum-good-subarray-sum/ |
| 19 | 3346. Maximum Frequency of an Element After Performing Operations I | Medium | https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/ |
| 20 | 3347. Maximum Frequency of an Element After Performing Operations II | Hard | https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Unlike the fixed window, the variable window grows and shrinks based on a condition. Think of it like an elastic band stretched between two pointers:
- The **right pointer (hi)** always moves right, expanding the window by one element each step
- The **left pointer (lo)** moves right only when the window violates the condition — shrinking it

The key insight: every element is added at most once (hi scan) and removed at most once (lo shrink) → O(n) total, even though there's a nested while loop.

Two main modes:
- **Find MAXIMUM length window where condition holds**: shrink when INVALID
- **Find MINIMUM length window satisfying condition**: shrink when VALID (greedy minimize)

### Real-World Analogy
You're eating from a buffet with dietary rules. Start with nothing on your plate. Keep adding food (expand). When you've violated your diet (condition broken), remove food from what you added earliest (shrink from left) until you're back within limits. Track the most/least food you could have at any valid moment.

### Visual Walkthrough
```
Longest Substring Without Repeating Characters: "abcabcbb"

lo=0, hi=0, window={}, maxLen=0

hi=0 'a': add a → {a:1}  valid   maxLen=1
hi=1 'b': add b → {a:1,b:1}  valid   maxLen=2
hi=2 'c': add c → {a:1,b:1,c:1}  valid   maxLen=3
hi=3 'a': add a → {a:2,b:1,c:1}  INVALID (a appears twice)
  shrink: remove s[lo=0]='a' → {a:1,b:1,c:1}  valid now, lo=1
  maxLen stays 3
hi=4 'b': add b → {a:1,b:2,c:1}  INVALID
  shrink: remove s[lo=1]='b' → {a:1,b:1,c:1}  valid, lo=2
hi=5 'c': INVALID, shrink lo=3
hi=6 'b': add b → valid
hi=7 'b': INVALID, shrink lo=5

Final maxLen = 3 (window "abc")
```

### When TO use this pattern
- "Longest/shortest subarray/substring WHERE [condition]"
- "Minimum window containing all of [something]"
- "At most K distinct characters/types"
- Sum, product, count conditions on contiguous sequences

### When NOT to use this pattern
- Non-contiguous elements (use DP or sorting)
- Condition is not monotone (window growing doesn't make it strictly more invalid/valid)
- Two-dimensional problems (use DP)

### Common Beginner Mistakes
- **MAXIMUM: shrink while INVALID** (condition violated) — keep valid windows, maximize size
- **MINIMUM: shrink while VALID** (condition met) — keep minimizing as long as valid
- **Update answer**: for max-length, after shrink; for min-length, INSIDE shrink loop
- **Not using while for shrink**: using `if` instead of `while` misses cases where multiple removals are needed

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "longest/shortest subarray where [condition]", window size is not fixed |
| Core Idea | hi always advances; lo advances only when condition violated (or satisfied for min) |
| Trigger Keywords | "subarray", "substring", "contiguous", "at most k", "at least k" |
| Avoid When | Non-contiguous, or condition not monotone with window size |
| Time Complexity | O(n) amortized — each element added/removed once |
| Space Complexity | O(k) for frequency map, O(1) for sum-based |

**Gotchas:**
- MAX length: update answer AFTER shrink loop
- MIN length: update answer INSIDE shrink loop (before removing)
- Count subarrays: count += hi - lo + 1 (number of valid subarrays ending at hi)
- Min Window Substring: track `have` vs `required` counters to avoid O(26) map comparison per step

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"longest substring without repeating"` → max window, shrink when duplicate
- `"minimum window substring"` → min window, shrink when all required chars covered
- `"at most k distinct types"` → max window, shrink when distinct count > k
- `"product less than k"` → max window, shrink when product ≥ k
- `"max consecutive ones with k flips"` → max window, shrink when zeros > k

### Constraint hints
- n up to 10^5 → O(n) expected → variable window
- "subarray" + sum/count condition → variable window
- Cannot break condition monotonicity? → window won't work, may need DP

---

## 4. C++ Template

```cpp
/*
 * Pattern: Variable Size Sliding Window
 * Use when: longest/shortest subarray satisfying a condition
 * Time: O(n) | Space: O(1) or O(k)
 *
 * MAX LENGTH TEMPLATE (shrink while INVALID):
 */
int maxLengthTemplate(vector<int>& nums, int k) {
    int lo = 0, maxLen = 0;
    // STATE: sum, freq map, count of distinct, zeros flipped, etc.
    int state = 0;

    for (int hi = 0; hi < (int)nums.size(); hi++) {
        // EXPAND: update state with nums[hi]
        state += nums[hi];

        // SHRINK: while condition violated
        while (state > k) {           // adjust condition for your problem
            state -= nums[lo];
            lo++;
        }

        // window [lo, hi] is now valid → update answer
        maxLen = max(maxLen, hi - lo + 1);
    }
    return maxLen;
}

/*
 * MIN LENGTH TEMPLATE (shrink while VALID):
 */
int minLengthTemplate(vector<int>& nums, int target) {
    int lo = 0, minLen = INT_MAX;
    int sum = 0;

    for (int hi = 0; hi < (int)nums.size(); hi++) {
        sum += nums[hi];  // EXPAND

        // SHRINK: while condition satisfied (try to minimize)
        while (sum >= target) {
            minLen = min(minLen, hi - lo + 1);  // update INSIDE shrink
            sum -= nums[lo];
            lo++;
        }
    }
    return (minLen == INT_MAX) ? 0 : minLen;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I notice this asks for the [longest/shortest] subarray where [condition]. This is a classic variable sliding window problem.
I'll use two pointers lo and hi. Hi always moves right — expanding the window. When the window becomes invalid, I advance lo to shrink it.
The key insight: each element is added and removed at most once, so the total work is O(n) despite the nested loops.
Let me identify the state I need to track and the condition for expansion/shrinking..."

### What to TYPE as comments while coding live
```cpp
// PROBLEM: find [longest/shortest] subarray where [condition]
// APPROACH: variable sliding window
// STATE: [what to track — sum, freq map, count]
// EXPAND: add nums[hi] to state
// SHRINK: while [invalid/valid], remove nums[lo], lo++
// UPDATE: after shrink for max; inside shrink for min
// COMPLEXITY: O(n) time, O(k) space
```

### Interview Flow Checklist
- [ ] Identify: max or min length?
- [ ] Identify: what state to track (sum, map, count)?
- [ ] Identify: what makes the window valid/invalid?
- [ ] Code expand + shrink + update
- [ ] Check: update answer before or inside shrink?
- [ ] Handle edge cases (no valid window → return 0 or -1)

---

## 6. Problems

---

### Problem 1: 3. Longest Substring Without Repeating Characters
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/longest-substring-without-repeating-characters/
**Why this pattern fits:** Max window where no character appears more than once; shrink when duplicate found

**Optimal C++ Solution:**
```cpp
// Longest Substring Without Repeating Characters
// Time: O(n) | Space: O(min(n, alphabet))

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> freq;
    int lo = 0, maxLen = 0;

    for (int hi = 0; hi < (int)s.size(); hi++) {
        freq[s[hi]]++;  // expand

        // shrink while there's a duplicate
        while (freq[s[hi]] > 1) {
            freq[s[lo]]--;
            lo++;
        }
        maxLen = max(maxLen, hi - lo + 1);
    }
    return maxLen;
}
```

**Complexity Analysis:**
- Time: O(n) — each char added/removed once
- Space: O(min(n, 128)) for freq map

**Edge Cases:**
- [ ] Empty string
- [ ] All same characters "aaaa" → length 1
- [ ] All unique characters

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 76. Minimum Window Substring
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/minimum-window-substring/
**Why this pattern fits:** Min window containing all characters of t; shrink when all requirements satisfied

**Problem Summary:**
Find the minimum window in s that contains all characters of t (including duplicates).

**Approach Walkthrough:**
1. Build `need` map from t
2. Expand hi; when window[c] == need[c] for some char c, increment `have`
3. Shrink lo while `have == required` (all chars satisfied); update minimum
4. When shrinking causes `have < required`, stop shrinking

**Optimal C++ Solution:**
```cpp
// Minimum Window Substring
// Time: O(|s| + |t|) | Space: O(|t|)

string minWindow(string s, string t) {
    unordered_map<char, int> need;
    for (char c : t) need[c]++;

    int required = need.size();  // distinct chars needed
    int have = 0;
    int lo = 0, minStart = 0, minLen = INT_MAX;
    unordered_map<char, int> window;

    for (int hi = 0; hi < (int)s.size(); hi++) {
        char c = s[hi];
        window[c]++;

        // did this char's requirement just become satisfied?
        if (need.count(c) && window[c] == need[c]) have++;

        // shrink while all requirements satisfied
        while (have == required) {
            if (hi - lo + 1 < minLen) {
                minLen = hi - lo + 1;
                minStart = lo;
            }
            char left = s[lo];
            window[left]--;
            if (need.count(left) && window[left] < need[left]) have--;
            lo++;
        }
    }
    return (minLen == INT_MAX) ? "" : s.substr(minStart, minLen);
}
```

**Complexity Analysis:**
- Time: O(|s| + |t|)
- Space: O(|t|)

**Edge Cases:**
- [ ] t is longer than s → return ""
- [ ] s == t → return s
- [ ] t has duplicate characters

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 209. Minimum Size Subarray Sum
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/minimum-size-subarray-sum/
**Why this pattern fits:** Min window where sum ≥ target; shrink greedily while condition holds

**Optimal C++ Solution:**
```cpp
// Minimum Size Subarray Sum
// Time: O(n) | Space: O(1)

int minSubArrayLen(int target, vector<int>& nums) {
    int lo = 0, sum = 0, minLen = INT_MAX;

    for (int hi = 0; hi < (int)nums.size(); hi++) {
        sum += nums[hi];  // expand

        while (sum >= target) {  // condition met → try to shrink
            minLen = min(minLen, hi - lo + 1);
            sum -= nums[lo++];
        }
    }
    return (minLen == INT_MAX) ? 0 : minLen;
}
```

**Edge Cases:**
- [ ] Sum of entire array < target → return 0
- [ ] Single element ≥ target → return 1

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 424. Longest Repeating Character Replacement
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/longest-repeating-character-replacement/
**Why this pattern fits:** Max window where we can replace (window_size - max_freq) ≤ k characters; shrink when replacements > k

**Optimal C++ Solution:**
```cpp
// Longest Repeating Character Replacement
// Time: O(n) | Space: O(26)

int characterReplacement(string s, int k) {
    vector<int> freq(26, 0);
    int lo = 0, maxFreq = 0, maxLen = 0;

    for (int hi = 0; hi < (int)s.size(); hi++) {
        freq[s[hi] - 'A']++;
        maxFreq = max(maxFreq, freq[s[hi] - 'A']);

        // replacements needed = window_size - most_frequent_char
        if (hi - lo + 1 - maxFreq > k) {
            freq[s[lo] - 'A']--;
            lo++;
            // note: maxFreq may be stale but that's ok —
            // it only grows, so window size stays non-decreasing
        }
        maxLen = max(maxLen, hi - lo + 1);
    }
    return maxLen;
}
```

**Edge Cases:**
- [ ] k = 0 (no replacements allowed) → find longest run of same char
- [ ] k ≥ n (can replace all) → return n
- [ ] All same characters

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 1004. Max Consecutive Ones III
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/max-consecutive-ones-iii/
**Why this pattern fits:** Max window with at most k zeros (i.e., k flips); shrink when zeros > k

**Optimal C++ Solution:**
```cpp
// Max Consecutive Ones III
// Time: O(n) | Space: O(1)

int longestOnes(vector<int>& nums, int k) {
    int lo = 0, zeros = 0, maxLen = 0;

    for (int hi = 0; hi < (int)nums.size(); hi++) {
        if (nums[hi] == 0) zeros++;  // expand

        while (zeros > k) {          // too many zeros: shrink
            if (nums[lo] == 0) zeros--;
            lo++;
        }
        maxLen = max(maxLen, hi - lo + 1);
    }
    return maxLen;
}
```

**Edge Cases:**
- [ ] k = 0 → find longest run of 1s
- [ ] All 1s → return n
- [ ] All 0s → return k

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 6: 713. Subarray Product Less Than K
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/subarray-product-less-than-k/
**Why this pattern fits:** Max window with product < k; count valid subarrays (hi-lo+1 per valid hi)

**Optimal C++ Solution:**
```cpp
// Subarray Product Less Than K
// Time: O(n) | Space: O(1)

int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;  // no positive product < 1
    int lo = 0, product = 1, count = 0;

    for (int hi = 0; hi < (int)nums.size(); hi++) {
        product *= nums[hi];  // expand

        while (product >= k) {  // shrink
            product /= nums[lo++];
        }
        // all subarrays ending at hi with left in [lo, hi] are valid
        count += hi - lo + 1;
    }
    return count;
}
```

**Edge Cases:**
- [ ] k = 1 (no product can be < 1 with positive numbers)
- [ ] Single element ≥ k

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 7: 904. Fruit Into Baskets
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/fruit-into-baskets/
**Why this pattern fits:** "At most 2 distinct fruit types" = max window with at most 2 distinct values

**Optimal C++ Solution:**
```cpp
// Fruit Into Baskets (at most 2 distinct values)
// Time: O(n) | Space: O(1) since max 3 keys in map

int totalFruit(vector<int>& fruits) {
    unordered_map<int, int> basket;
    int lo = 0, maxLen = 0;

    for (int hi = 0; hi < (int)fruits.size(); hi++) {
        basket[fruits[hi]]++;  // pick fruit

        while (basket.size() > 2) {  // more than 2 types: remove from left
            basket[fruits[lo]]--;
            if (basket[fruits[lo]] == 0) basket.erase(fruits[lo]);
            lo++;
        }
        maxLen = max(maxLen, hi - lo + 1);
    }
    return maxLen;
}
```

**Edge Cases:**
- [ ] All same fruit → return n
- [ ] Only 1 type of fruit → still valid (at most 2)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find the longest subarray with sum equal to exactly k (with positive and negative numbers).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Prefix Sum + Hash Map (NOT sliding window)
**Reason:** With negative numbers, the "longer window → larger sum" monotonicity breaks. Sliding window requires the property that expanding always makes the window "more violating" and shrinking makes it "less violating." With negatives, you must use prefix sums and a hash map: prefixSum[i] - prefixSum[j] = k → prefixSum[j] = prefixSum[i] - k.
</details>

---

**Drill 2:**
> Given a binary string, find the longest substring with equal number of 0s and 1s.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Prefix Sum + Hash Map
**Reason:** Replace 0 with -1. Find longest subarray with sum = 0. Use prefix sum + hash map: store first occurrence of each prefix sum.
</details>

---

**Drill 3:**
> Find the minimum contiguous subarray whose sum is at least k, where elements can be positive or negative.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Monotonic Deque + Prefix Sum (LC 862)
**Reason:** Sliding window breaks with negative numbers. Use prefix sums + monotone deque: for each right endpoint, find the leftmost j such that prefix[right] - prefix[j] ≥ k.
</details>

---

**Drill 4:**
> Given a string and a pattern, count how many substrings of length |pattern| are a permutation of the pattern.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Size Sliding Window (P08) + frequency map
**Reason:** Window size = |pattern| is fixed. Slide window, track frequency map of current window, compare with pattern frequency. This is LC 567 (Permutation in String).
</details>

---

**Drill 5:**
> Find the number of subarrays with at most K distinct values.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Variable Sliding Window — count subarrays
**Reason:** Max window with ≤ k distinct values. For each hi, shrink until distinct ≤ k, then add (hi - lo + 1) to count (all subarrays ending at hi with left in [lo,hi] are valid). To count subarrays with EXACTLY k distinct: atMost(k) - atMost(k-1).
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Max length, single condition | O(n) | O(1) | Each element enters/exits once |
| Max length, frequency map | O(n) | O(26) | Map bounded by alphabet |
| Min length | O(n) | O(1) | Same amortized argument |
| Min window substring | O(n+m) | O(m) | n = s length, m = t length |
| Count subarrays | O(n) | O(1) | += (hi-lo+1) per step |

---

## 9. Common Follow-up Questions

1. How does the O(n) argument hold with a nested while loop? (Each element is added once by hi and removed at most once by lo — total 2n operations)
2. What if the condition is not monotone? (Sliding window won't work — use DP or prefix sums)
3. Can you count subarrays with EXACTLY k distinct? (atMost(k) - atMost(k-1) trick)
4. What about 2D subarrays? (Fix top/bottom row, use 1D sliding window on column sums)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Prefix Sum | Negative numbers, exact sum | 560. Subarray Sum Equals K |
| Monotonic Deque | Min/max within variable window | 1438. Longest Continuous Subarray |
| Frequency Map | Character-based window conditions | 76. Minimum Window Substring |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
