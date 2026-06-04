# 🔥 Two Sum

> **LeetCode #1** · **Difficulty:** Easy · **Step 3 — Arrays · P17**

---

## 🧠 Problem Understanding

Given an array and a target, find two indices `i`, `j` such that `arr[i] + arr[j] == target`. Exactly one solution exists.

**Input:** `nums=[2,7,11,15]`, target=9 → **Output:** `[0,1]`

---

## 🥉 Brute Force
Check all pairs. **Time:** O(N²) · **Space:** O(1)

---

## 🥈 Better (Sorted Array) — Two Pointers
Sort, then converging two pointers. **Time:** O(N log N) · **Space:** O(1). But doesn't return original indices.

---

## 🥇 Optimal — Hash Map

### Key Observation
> 💡 For each element `x`, check if `target - x` was seen before. Store each element with its index.

### Algorithm
1. `map<int,int> seen`
2. For each `i`, `x = nums[i]`:
   - Complement = `target - x`
   - If `complement` in `seen`: return `{seen[complement], i}`
   - Else: `seen[x] = i`

### Dry Run
`nums=[2,7,11,15]`, target=9

| i | x | need | In map? | map |
|---|---|------|---------|-----|
| 0 | 2 | 7 | ❌ | {2:0} |
| 1 | 7 | 2 | ✅ → return **[0,1]** | |

**Output:** `[0,1]` ✅

### Complexity
- **Time:** O(N) · **Space:** O(N)

---

## 💻 Clean C++ Code

```cpp
/*
 * TWO SUM — hash map for O(1) complement lookup
 * For each x, check if (target-x) was seen before
 * Time O(N) | Space O(N)
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> seen;          // value → index

        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];

            if (seen.count(complement))
                return {seen[complement], i};  // found pair

            seen[nums[i]] = i;                 // store current element
        }
        return {};
    }
};
```

---

## 🎤 Interview Explanation Script
> "Brute force checks all pairs in O(N²). The optimization: for each element `x`, I need `target - x`. I can check in O(1) using a hash map. As I scan left to right, I look up the complement in the map — if it's there, I've found the pair. Otherwise, I store the current element. This gives O(N) time, O(N) space."

> "If the array were sorted and we only need the values (not indices), two converging pointers give O(N) time with O(1) space."

---

## 🧾 Recall Line
> "Hash map: for each `x`, check if `target-x` is in map. Store x→index as you go."

## 📝 Short Revision Notes
- Hash map: O(N) time, O(N) space — handles duplicates (store index, not just seen)
- Two pointers (sorted): O(N log N) time, O(1) space — loses original indices
- Problem guarantees exactly one solution → no need to handle no-solution case
- `unordered_map` O(1) avg, `map` O(log N)

## ⚠️ Common Mistakes
❌ Storing the element BEFORE checking complement — misses `nums[i] + nums[i] == target` case... actually this is fine here because we check THEN store  
❌ Using `seen[x] = i` after the check means we don't count `x` as its own complement (correct — same element can't be used twice)

## 🔥 What Interviewer Is Testing
- Hash map for O(1) lookup
- Trade-off between space and time (vs two pointers)

## 📚 Related Problems
- [ ] LeetCode #1 — Two Sum
- [ ] LeetCode #167 — Two Sum II (sorted array → two pointers)
- [ ] Striver P32 — 3-Sum (extension)
- [ ] Striver P33 — 4-Sum (extension)

## 🏆 Pattern Category
`Arrays` · `Hashing` · `Two Pointers`

## ⏱️ 30-Second Revision
> Hash map. For each `x`: if `target-x` in map → return indices. Else `map[x]=i`. O(N)/O(N).
