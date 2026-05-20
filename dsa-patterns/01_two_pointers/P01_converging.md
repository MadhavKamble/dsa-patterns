# Pattern 01: Converging Two Pointers

## Category
Two Pointers

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 11. Container With Most Water | Medium | https://leetcode.com/problems/container-with-most-water/ |
| 2 | 15. 3Sum | Medium | https://leetcode.com/problems/3sum/ |
| 3 | 16. 3Sum Closest | Medium | https://leetcode.com/problems/3sum-closest/ |
| 4 | 18. 4Sum | Medium | https://leetcode.com/problems/4sum/ |
| 5 | 167. Two Sum II — Input Array Is Sorted | Medium | https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/ |
| 6 | 349. Intersection of Two Arrays | Easy | https://leetcode.com/problems/intersection-of-two-arrays/ |
| 7 | 881. Boats to Save People | Medium | https://leetcode.com/problems/boats-to-save-people/ |
| 8 | 977. Squares of a Sorted Array | Easy | https://leetcode.com/problems/squares-of-a-sorted-array/ |
| 9 | 259. 3Sum Smaller | Medium | https://leetcode.com/problems/3sum-smaller/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Imagine you have a sorted array and you need to find two numbers that together satisfy some condition (like summing to a target). The brute force is to check every pair: two nested loops → O(n²).

The converging two-pointer trick eliminates the inner loop. You place one pointer at the left end and one at the right end, then move them toward each other based on the result of your comparison:
- If the result is "too small" → move the left pointer right (increase value)
- If the result is "too large" → move the right pointer left (decrease value)
- If the result is exactly right → record it and move both

Since every step eliminates at least one candidate, the total work is O(n).

### Real-World Analogy
You're playing "hot or cold" with a number hidden in a sorted list. A friend tells you "too high" or "too low." Instead of checking every number, you jump to the middle, hear the hint, and eliminate half the remaining options each time. Converging pointers are doing the same thing from both ends simultaneously.

### Visual Walkthrough
```
Array (sorted): [1, 3, 5, 7, 9]    Target sum = 10

Step 1:
  lo=0 (value 1)   hi=4 (value 9)
  sum = 1 + 9 = 10  ✓  FOUND!

Different example, target = 8:
  lo=0 (value 1)   hi=4 (value 9)
  sum = 10 > 8  →  hi--

  lo=0 (value 1)   hi=3 (value 7)
  sum = 8 = 8   ✓  FOUND!

Another example, target = 100 (not found):
  lo=0 (1)   hi=4 (9)  sum=10 < 100 → lo++
  lo=1 (3)   hi=4 (9)  sum=12 < 100 → lo++
  lo=2 (5)   hi=4 (9)  sum=14 < 100 → lo++
  lo=3 (7)   hi=4 (9)  sum=16 < 100 → lo++
  lo=4  NOT < hi=4  →  STOP. Not found.
```

### When TO use this pattern
- Array is sorted (or can be sorted without losing the answer)
- Looking for a pair (or triple/quadruple) satisfying a sum/product condition
- Problem asks for "does X exist", "find X", "count pairs where..."
- Problem involves comparing elements from both ends (e.g., trap water, boats)

### When NOT to use this pattern
- Array is unsorted AND sorting changes the answer (e.g., indices matter)
- Need to find ALL pairs including duplicates at the same index
- Problem requires maintaining original order

### Common Beginner Mistakes
- **Not sorting first**: converging only works on sorted data
- **lo < hi not lo <= hi**: pointers should stop when they meet (same element can't pair with itself)
- **3Sum duplicates**: forgetting to skip `nums[i] == nums[i-1]` and `nums[lo] == nums[lo-1]`
- **Modifying the wrong pointer**: if sum < target, you need MORE → move lo (increase), not hi
- **4Sum integer overflow**: use `long long` when summing four elements

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | Sorted array, find pair/triple with sum condition |
| Core Idea | Start at both ends, move inward based on comparison |
| Trigger Keywords | "sorted array", "two numbers that sum to", "three numbers", "pair" |
| Avoid When | Unsorted + order matters, need exact indices |
| Time Complexity | O(n) for two-pointer scan; O(n log n) if sort needed |
| Space Complexity | O(1) extra (O(n) for sorted copy if needed) |

**Gotchas:**
- Always check `lo < hi` (not `<=`) in the while loop
- 3Sum: fix first element in outer loop, then converge on remaining two
- Skip duplicates at every level in 3Sum/4Sum to avoid duplicate triplets

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"sorted array"` → signals this pattern because sorting is the prerequisite
- `"find two/three numbers that sum to"` → classic two-pointer setup
- `"count pairs where sum < target"` → count all valid lo positions for each hi
- `"minimum/maximum water/area"` → height formula involves both ends

### Constraint hints
- Array is given as sorted → direct converging pointer
- n ≤ 10^4 and O(n²) too slow → O(n) two-pointer is the target
- Memory limit O(1) → rules out hash map approach

---

## 4. C++ Template

```cpp
/*
 * Pattern: Converging Two Pointers
 * Use when: sorted array, find pair/triple satisfying condition
 * Time: O(n) | Space: O(1)
 */

// TWO SUM in sorted array
pair<int,int> twoSum(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size() - 1;

    while (lo < hi) {
        int sum = arr[lo] + arr[hi];
        if (sum == target) return {lo, hi};
        else if (sum < target) lo++;  // need more: move left pointer right
        else hi--;                    // too much: move right pointer left
    }
    return {-1, -1};
}

// THREE SUM
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;

    for (int i = 0; i < (int)nums.size() - 2; i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;  // skip dup fixed element

        int lo = i + 1, hi = nums.size() - 1;
        while (lo < hi) {
            int sum = nums[i] + nums[lo] + nums[hi];
            if (sum == 0) {
                result.push_back({nums[i], nums[lo], nums[hi]});
                while (lo < hi && nums[lo] == nums[lo+1]) lo++;  // skip dups
                while (lo < hi && nums[hi] == nums[hi-1]) hi--;  // skip dups
                lo++; hi--;
            } else if (sum < 0) lo++;
            else hi--;
        }
    }
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"So I'm reading the problem... I need to find two numbers in a sorted array that sum to the target.
First let me think about constraints — the array is sorted, great, that's a hint.
A brute force approach would be to check every pair → O(n²) time.
But since the array is sorted, if I have a pointer at the left and one at the right, I can decide which way to move based on whether the sum is too big or too small.
This reduces it to O(n) time with O(1) space.
Let me code this up..."

### What to TYPE as comments while coding live
```cpp
// PROBLEM RESTATEMENT: sorted array, find pair that sums to target
// BRUTE FORCE: two nested loops → O(n²) time
// OPTIMIZATION: array is sorted → use converging two pointers
// APPROACH: lo starts at 0, hi at end; move based on sum vs target

// Step 1: initialize lo=0, hi=n-1
// Step 2: while lo < hi, compute sum
// Step 3: if match → done; if small → lo++; if large → hi--

// EDGE CASES to handle:
// - empty array or single element → return immediately
// - all same elements → normal convergence handles it
// - target larger than any pair → loop ends naturally

// DRY RUN: arr=[2,7,11,15], target=9  →  lo=0(2)+hi=1(7)=9  ✓

// COMPLEXITY: Time O(n) | Space O(1)
```

### Interview Flow Checklist
- [ ] Restate problem in own words
- [ ] Ask: "Is the array sorted?"
- [ ] State brute force O(n²) approach first
- [ ] Explain: sorted array enables pointer movement decision
- [ ] Write comments before code
- [ ] Code with narration
- [ ] Dry run on given example
- [ ] Handle edge cases (empty, single element, no solution)
- [ ] State complexity

---

## 6. Problems

---

### Problem 1: 167. Two Sum II — Input Array Is Sorted
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
**Why this pattern fits:** Array is sorted → converging pointers eliminate need for nested loop

**Problem Summary:**
Given a 1-indexed sorted array, find two numbers that add up to target.
Return their 1-indexed positions. Exactly one solution is guaranteed.

**Approach Walkthrough:**
1. Start lo=0, hi=n-1
2. If arr[lo]+arr[hi]==target → return {lo+1, hi+1}
3. If sum < target → lo++ (left value is too small)
4. If sum > target → hi-- (right value is too large)

**Optimal C++ Solution:**
```cpp
// Two Sum II — Sorted Array
// Approach: converging two pointers
// Time: O(n) | Space: O(1)

vector<int> twoSum(vector<int>& numbers, int target) {
    int lo = 0, hi = numbers.size() - 1;

    while (lo < hi) {
        int sum = numbers[lo] + numbers[hi];
        if (sum == target) return {lo + 1, hi + 1};  // 1-indexed
        else if (sum < target) lo++;  // need larger value
        else hi--;                    // need smaller value
    }
    return {};  // guaranteed to have solution, won't reach here
}
```

**Complexity Analysis:**
- Time: O(n) — each pointer moves at most n times total
- Space: O(1) — no extra memory

**Edge Cases:**
- [ ] Target requires the two smallest numbers
- [ ] Target requires the two largest numbers
- [ ] Negative numbers in array

**Interview Follow-up Questions:**
- What if the array were not sorted? (Use a hash map → O(n) time, O(n) space)
- What if there could be zero solutions? (Return empty, handle while condition)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

### Problem 2: 11. Container With Most Water
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/container-with-most-water/
**Why this pattern fits:** Two vertical lines form a container; moving the shorter inward is the greedy optimal choice

**Problem Summary:**
Given n vertical lines where height[i] is the height of line i, find two lines that together with the x-axis forms a container that holds the most water.

**Approach Walkthrough:**
1. Area = min(height[lo], height[hi]) × (hi - lo)
2. To maximize: moving the taller pointer inward can NEVER increase area (width shrinks, height stays same or shrinks). Moving the shorter inward MIGHT find a taller line.
3. So always move the pointer with the shorter height inward.

**Optimal C++ Solution:**
```cpp
// Container With Most Water
// Approach: converging two pointers — always move shorter line inward
// Time: O(n) | Space: O(1)

int maxArea(vector<int>& height) {
    int lo = 0, hi = height.size() - 1;
    int maxWater = 0;

    while (lo < hi) {
        // area = width × min height
        int water = (hi - lo) * min(height[lo], height[hi]);
        maxWater = max(maxWater, water);

        // move the pointer with smaller height inward
        // (moving the taller one can only decrease or keep area the same)
        if (height[lo] < height[hi]) lo++;
        else hi--;
    }
    return maxWater;
}
```

**Complexity Analysis:**
- Time: O(n) — two pointers traverse array once
- Space: O(1)

**Edge Cases:**
- [ ] All lines same height
- [ ] Two lines only
- [ ] Heights in increasing order

**Interview Follow-up Questions:**
- Why is it correct to always move the shorter pointer? (Proof: moving taller can only decrease width; since height is min(lo,hi), it stays same or decreases. Moving shorter gives a chance for taller.)
- Can you find all pairs that give maximum water? (Track equal-max cases)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

### Problem 3: 15. 3Sum
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/3sum/
**Why this pattern fits:** Fix one element, then use converging pointers on the remaining sorted subarray to find pairs summing to -nums[i]

**Problem Summary:**
Find all unique triplets in the array that sum to zero. No duplicate triplets allowed.

**Approach Walkthrough:**
1. Sort the array
2. For each index i, fix nums[i] as the first element
3. Skip duplicates: if nums[i] == nums[i-1], skip
4. Use converging pointers on i+1 to n-1, looking for pair summing to -nums[i]
5. After finding a valid triplet, skip duplicates for lo and hi

**Optimal C++ Solution:**
```cpp
// 3Sum
// Approach: sort + fix one element + converging two pointers for remaining two
// Time: O(n²) | Space: O(1) extra (output not counted)

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    int n = nums.size();

    for (int i = 0; i < n - 2; i++) {
        // optimization: if smallest triplet is > 0, no solution possible
        if (nums[i] > 0) break;

        // skip duplicate fixed element
        if (i > 0 && nums[i] == nums[i-1]) continue;

        int lo = i + 1, hi = n - 1;
        int target = -nums[i];

        while (lo < hi) {
            int sum = nums[lo] + nums[hi];
            if (sum == target) {
                result.push_back({nums[i], nums[lo], nums[hi]});
                // skip duplicates for lo and hi
                while (lo < hi && nums[lo] == nums[lo+1]) lo++;
                while (lo < hi && nums[hi] == nums[hi-1]) hi--;
                lo++; hi--;
            } else if (sum < target) lo++;
            else hi--;
        }
    }
    return result;
}
```

**Complexity Analysis:**
- Time: O(n²) — outer loop O(n), inner two-pointer O(n) each
- Space: O(1) extra (output array not counted)

**Edge Cases:**
- [ ] Array with fewer than 3 elements
- [ ] All zeros [0,0,0,0]
- [ ] All positive numbers (no valid triplet)

**Interview Follow-up Questions:**
- Can you do it in O(n log n)? (No — O(n²) is optimal for this problem)
- What if triplets don't need to be unique? (Remove the skip-duplicate logic)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

### Problem 4: 977. Squares of a Sorted Array
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/squares-of-a-sorted-array/
**Why this pattern fits:** Sorted array with negatives — largest squares are at either end; converging fills result from back to front

**Problem Summary:**
Given sorted array with negative numbers, return array of squares in non-decreasing order.

**Approach Walkthrough:**
1. Squares of numbers near both ends could be the largest (negatives squared are large too)
2. Use lo and hi, compare squares, fill result array from the back
3. Whichever square is larger goes at current position, move that pointer inward

**Optimal C++ Solution:**
```cpp
// Squares of a Sorted Array
// Approach: converging two pointers, fill result from back to front
// Time: O(n) | Space: O(n) for result

vector<int> sortedSquares(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    int lo = 0, hi = n - 1;
    int pos = n - 1;  // fill result from back (largest first)

    while (lo <= hi) {
        int left  = nums[lo] * nums[lo];
        int right = nums[hi] * nums[hi];

        if (left > right) {
            result[pos--] = left;
            lo++;
        } else {
            result[pos--] = right;
            hi--;
        }
    }
    return result;
}
```

**Complexity Analysis:**
- Time: O(n)
- Space: O(n) for output array

**Edge Cases:**
- [ ] All negative numbers
- [ ] All positive numbers
- [ ] Single element

**Interview Follow-up Questions:**
- Can you do it in-place? (Yes, but it's more complex — two passes)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

### Problem 5: 881. Boats to Save People
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/boats-to-save-people/
**Why this pattern fits:** Sort weights → try to pair heaviest with lightest (greedy); if can't pair, heaviest goes alone

**Problem Summary:**
Each boat holds at most 2 people and a weight limit. Find minimum boats needed.

**Approach Walkthrough:**
1. Sort by weight
2. lo = lightest person, hi = heaviest person
3. If they fit together → both board, lo++, hi--
4. If not → heaviest goes alone, hi--
5. Each iteration uses exactly 1 boat

**Optimal C++ Solution:**
```cpp
// Boats to Save People
// Approach: sort + greedy converging pointers
// Time: O(n log n) | Space: O(1)

int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int lo = 0, hi = people.size() - 1;
    int boats = 0;

    while (lo <= hi) {
        if (people[lo] + people[hi] <= limit) {
            lo++;  // lightest can share with heaviest
        }
        hi--;   // heaviest always takes a boat
        boats++;
    }
    return boats;
}
```

**Complexity Analysis:**
- Time: O(n log n) dominated by sorting
- Space: O(1)

**Edge Cases:**
- [ ] Single person
- [ ] All people have the same weight
- [ ] Heaviest person exactly equals limit

**Interview Follow-up Questions:**
- What if boats could hold 3 people? (Greedy no longer trivially correct — harder problem)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a sorted array of distinct integers. Count the number of pairs (i, j) where i < j and nums[i] + nums[j] < target.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Two Pointers — Converging
**Subpattern:** Count pairs below threshold
**Reason:** Sorted array + sum condition → converging pointers. When nums[lo]+nums[hi] < target, ALL pairs from lo to hi-1 with hi are also valid (there are hi-lo such pairs). Add them all at once and move lo++.

</details>

---

**Drill 2:**
> Given a sorted array, determine if there exist two elements that are exactly k apart in value (|a-b| == k).

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Two Pointers — Converging
**Subpattern:** Find pair with exact difference
**Reason:** Sort, then use lo and hi. If arr[hi]-arr[lo] == k → found. If < k → hi++ to increase difference. If > k → lo++ to decrease difference. But wait — for difference problems, a sliding window (lo/hi both moving right) is also valid. Converging works too since the array is sorted.

</details>

---

**Drill 3:**
> You have an array of n integers. Find 4 numbers that multiply to exactly k.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Two Pointers — Converging (extended to 4Sum)
**Subpattern:** kSum generalization
**Reason:** Sort array, fix two outer elements (O(n²) loops), use converging pointers for remaining two. Similar to 4Sum but with multiplication instead of addition. Product can overflow → use long long or log-space.

</details>

---

**Drill 4:**
> A wall is represented as an array of heights. Each column can hold water equal to min(maxLeft, maxRight) - height. Find total trapped water.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Two Pointers — Converging
**Subpattern:** Trapping Rain Water (LC 42)
**Reason:** Use two pointers + track maxLeft and maxRight. Process the side with the smaller max first (since water at that position is bounded by the smaller side). This gives O(n) time without extra space, compared to prefix arrays approach.

</details>

---

**Drill 5:**
> Given array of colors (0=Red, 1=White, 2=Blue), sort them in-place in that order using O(1) space.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Two Pointers — Dutch National Flag
**Subpattern:** Three-way partition
**Reason:** Three-value sort with O(1) space → Dutch National Flag. Use lo (everything before is 0), mid (scanning pointer), hi (everything after is 2). When mid sees 0: swap with lo. When sees 2: swap with hi. When sees 1: just advance mid.

</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Two Sum (sorted) | O(n) | O(1) | Single pass with two pointers |
| Three Sum | O(n²) | O(1) | Outer O(n) loop + O(n) inner converge |
| Four Sum | O(n³) | O(1) | Two outer loops + O(n) converge |
| Squares of Sorted | O(n) | O(n) | Single pass, output array |
| Boats to Save People | O(n log n) | O(1) | Dominated by sort |

---

## 9. Common Follow-up Questions

1. What if the array is unsorted? → Sort first (costs O(n log n)) or use hash map for Two Sum (O(n) time, O(n) space)
2. Can you find all triplets (not just count)? → Yes, same approach but collect results; be careful about duplicates
3. What if numbers can repeat and you must count duplicate pairs? → Don't skip duplicates; count carefully
4. Extend 3Sum to kSum? → Recursively fix (k-2) elements, use converging for last two

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Sorting | Almost always for sorted-input variant | 3Sum, Boats to Save People |
| Sliding Window | When window size is not fixed but sum/product bounded | Subarray Product Less Than K |
| Binary Search | When counting pairs below threshold (use binary search instead of second pointer) | 3Sum Smaller (both work) |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
