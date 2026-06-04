# 🔥 Longest Consecutive Sequence

> **LeetCode #128** · **Difficulty:** Medium · **Step 3 — Arrays · P26**

---

## 🧠 Problem Understanding

Find the length of the longest consecutive sequence of integers in an unsorted array. Must run in O(N).

**Input:** `[100,4,200,1,3,2]` → **Output:** `4` (sequence: `1,2,3,4`)

---

## 🥉 Brute Force
Sort, scan for consecutive. **Time:** O(N log N)

---

## 🥇 Optimal — Hash Set

### Key Observation
> 💡 A consecutive sequence `[x, x+1, x+2, ..., x+k]` starts only at `x` where `x-1` is NOT in the set. For each such starting point, count how long the sequence extends.

### Algorithm
1. Insert all elements into `unordered_set`
2. For each `num`:
   - If `num-1` NOT in set → this is the **start of a sequence**
   - Count: while `num+1` in set, increment `num` and `length`
   - Update `maxLength`

### Dry Run
`nums = [100, 4, 200, 1, 3, 2]`  
Set = `{100, 4, 200, 1, 3, 2}`

| num | num-1 in set? | Start? | sequence length |
|-----|--------------|--------|-----------------|
| 100 | 99 not in set | ✅ | 100 only → 1 |
| 4 | 3 in set | ❌ | skip |
| 200 | 199 not in set | ✅ | 200 only → 1 |
| 1 | 0 not in set | ✅ | 1→2→3→4 → **4** |
| 3 | 2 in set | ❌ | skip |
| 2 | 1 in set | ❌ | skip |

**maxLength = 4** ✅

### Complexity
- **Time:** O(N) — each element is added to set once, and each element is visited at most twice (once as start candidate, once as continuation)
- **Space:** O(N)

---

## 💻 Clean C++ Code

```cpp
/*
 * LONGEST CONSECUTIVE SEQUENCE — hash set + start-only expansion
 *
 * KEY: Only expand from sequence START (num-1 not in set)
 *      This ensures each element is processed at most twice → O(N) total
 *
 * Time O(N) | Space O(N)
 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;

        for (int num : numSet) {                  // iterate set, not array (avoids duplicate work)
            if (numSet.find(num - 1) == numSet.end()) {
                // num is the start of a sequence
                int len = 1;
                while (numSet.count(num + len)) len++;
                maxLen = max(maxLen, len);
            }
        }

        return maxLen;
    }
};
```

---

## 🎤 Interview Explanation Script
> "The brute force sorts and scans — O(N log N). To get O(N), I use a hash set."

> "The key insight: a consecutive sequence `[x, x+1, ..., x+k]` has a unique starting point `x` where `x-1` is NOT in the array. I check this condition before expanding — this way I only expand from true starts, ensuring each element is visited at most twice total."

> "Build the set in O(N), then for each start, expand in O(length). Since all lengths sum to at most N, total is O(N)."

---

## 🧾 Recall Line
> "Hash set. For each num where `num-1` not in set (sequence start), count consecutive chain. O(N)/O(N)."

## 📝 Short Revision Notes
- Only expand from sequence start (num-1 not in set) → ensures O(N) total
- Iterate over `numSet` not `nums` to avoid redundant work on duplicates
- `unordered_set` for O(1) lookup
- Edge case: empty array → return 0
- Duplicates in input: set handles them — no extra work

## ⚠️ Common Mistakes
❌ Expanding from every element → O(N²) in worst case  
❌ Using `set` instead of `unordered_set` → O(N log N) lookup  
❌ Iterating array instead of set → duplicates cause redundant work  

## 🔥 What Interviewer Is Testing
- Why the start-check makes this O(N) not O(N²)
- Hash set for O(1) membership check

## 📚 Related Problems
- [ ] LeetCode #128 — Longest Consecutive Sequence
- [ ] LeetCode #298 — Binary Tree Longest Consecutive Sequence

## 🏆 Pattern Category
`Arrays` · `Hashing` · `Set`

## ⏱️ 30-Second Revision
> Put all in hash set. For each num where `num-1 not in set`: count chain `num, num+1, ...`. Update max. O(N)/O(N).
