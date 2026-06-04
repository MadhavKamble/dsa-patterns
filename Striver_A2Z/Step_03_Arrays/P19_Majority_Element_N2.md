# 🔥 Majority Element (> N/2 Times) — Boyer-Moore Voting

> **LeetCode #169** · **Difficulty:** Easy · **Step 3 — Arrays · P19**

---

## 🧠 Problem Understanding

Find the element that appears **more than N/2 times** in an array. It is guaranteed to exist.

**Input:** `[3,2,3]` → **Output:** `3`  
**Input:** `[2,2,1,1,1,2,2]` → **Output:** `2`

---

## 🥉 Brute Force
Check count of each element. **Time:** O(N²)

## 🥈 Better — Hash Map
Count frequencies, return element with count > N/2. **Time:** O(N) · **Space:** O(N)

## 🥈 Better 2 — Sort
Sorted middle element is always the majority. **Time:** O(N log N) · **Space:** O(1)

---

## 🥇 Optimal — Boyer-Moore Voting Algorithm

### Key Observation
> 💡 Majority element appears > N/2 times. If we cancel every majority vote with a minority vote, the majority element survives.
>
> Maintain a `candidate` and `count`. When we see the candidate, `count++`. When we see another, `count--`. When `count==0`, change candidate. The surviving candidate is the majority element.

### Algorithm
1. `candidate = arr[0]`, `count = 1`
2. For `i` from 1 to N-1:
   - If `arr[i] == candidate`: `count++`
   - Else: `count--`; if `count == 0`: `candidate = arr[i+1]`, reset... *(simpler: when count hits 0, next element becomes new candidate)*
3. Verify candidate (if guarantee given, skip verification)

### Dry Run
`arr = [2, 2, 1, 1, 1, 2, 2]`

| i | arr[i] | candidate | count |
|---|--------|-----------|-------|
| 0 | 2 | 2 | 1 |
| 1 | 2 | 2 | 2 |
| 2 | 1 | 2 | 1 |
| 3 | 1 | 2 | 0 |
| 4 | 1 | **1** | 1 |
| 5 | 2 | 1 | 0 |
| 6 | 2 | **2** | 1 |

**Candidate:** `2` ✅ (appears 4/7 > 3.5 times)

### Complexity
- **Time:** O(N) · **Space:** O(1)

### Why does it work?
The majority element has > N/2 votes. Even if every other element "cancels" a majority vote, there are still more majority votes than cancellations. The final candidate must be the majority element.

---

## 💻 Clean C++ Code

```cpp
/*
 * MAJORITY ELEMENT (> N/2) — Boyer-Moore Voting Algorithm
 *
 * INTUITION: Majority element can "survive" cancellation by all others.
 *            Count +1 for candidate match, -1 for mismatch.
 *            Reset candidate when count hits 0.
 *
 * NOTE: If majority not guaranteed, verify the candidate in a 2nd pass.
 *
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = nums[0], count = 1;

        for (int i = 1; i < nums.size(); i++) {
            if (count == 0) {
                candidate = nums[i];    // reset to new candidate
                count = 1;
            } else if (nums[i] == candidate) {
                count++;
            } else {
                count--;
            }
        }

        // if majority guaranteed, return directly
        // if not guaranteed: verify candidate in second pass
        return candidate;
    }
};
```

---

## 🎤 Interview Explanation Script
> "Hash map is O(N) time but O(N) space. Boyer-Moore achieves O(1) space."

> "The key insight: the majority element (> N/2 times) can survive any cancellation attack. I maintain a candidate and a vote count. When I see the candidate, I vote for it (+1). When I see anything else, I cancel a vote (-1). When votes hit 0, I pick a new candidate."

> "Since the majority element outnumbers all others combined, it always survives to be the final candidate."

> "If the majority is not guaranteed to exist, I'd do a second pass to verify the candidate's count."

---

## 🧾 Recall Line
> "Boyer-Moore: candidate + count. Match → count++. Mismatch → count--. count==0 → new candidate."

## 📝 Short Revision Notes
- Works only when majority is guaranteed (> N/2)
- For N/3 majority (LC 229) → extend to 2 candidates
- Verification pass needed if majority not guaranteed
- O(N) time, O(1) space — beats hash map on space

## ⚠️ Common Mistakes
❌ Not verifying candidate when majority not guaranteed  
❌ Applying to N/3 case without modifying algorithm  
❌ Initializing count=0 then using arr[-1] — always init with arr[0]

## 📚 Related Problems
- [ ] LeetCode #169 — Majority Element
- [ ] LeetCode #229 — Majority Element II (> N/3, extended algorithm)
- [ ] Striver P31 — Majority Element N/3 times

## 🏆 Pattern Category
`Arrays` · `Boyer-Moore Voting` · `Linear Scan`

## ⏱️ 30-Second Revision
> `candidate=arr[0], count=1`. For each x: if count==0→new candidate. Else if x==candidate→count++. Else count--. Return candidate.
