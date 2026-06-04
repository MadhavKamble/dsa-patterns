# 🔥 Majority Element (> N/3 Times)

> **LeetCode #229** · **Difficulty:** Medium · **Step 3 — Arrays · P31**

---

## 🧠 Problem Understanding

Find all elements appearing **more than N/3 times**. There can be **at most 2** such elements.

**Input:** `[3,2,3]` → `[3]`  
**Input:** `[1,1,1,3,3,2,2,2]` → `[1,2]`

**Key Observation:** More than N/3 → at most 2 such elements. Extend Boyer-Moore to 2 candidates.

---

## 🥉 Brute Force
Count frequencies, filter > N/3. **Time:** O(N) · **Space:** O(N) (hash map)

---

## 🥇 Optimal — Extended Boyer-Moore (2 Candidates)

### Key Observation
> 💡 Maintain 2 candidates with 2 vote counts. Cancel pairs of different elements. At the end, verify both candidates.

### Algorithm
1. `cand1, cand2, cnt1=0, cnt2=0`
2. For each `x`:
   - If `x == cand1`: `cnt1++`
   - Elif `x == cand2`: `cnt2++`
   - Elif `cnt1 == 0`: `cand1=x, cnt1=1`
   - Elif `cnt2 == 0`: `cand2=x, cnt2=1`
   - Else: `cnt1--, cnt2--`
3. **Verify**: count both candidates in a second pass, return those with count > N/3

### Dry Run
`nums = [1,1,1,3,3,2,2,2]`

| x | cand1 | cnt1 | cand2 | cnt2 |
|---|-------|------|-------|------|
| 1 | 1 | 1 | — | 0 |
| 1 | 1 | 2 | — | 0 |
| 1 | 1 | 3 | — | 0 |
| 3 | 1 | 3 | 3 | 1 |
| 3 | 1 | 3 | 3 | 2 |
| 2 | 1 | 2 | 3 | 1 |
| 2 | 1 | 1 | 3 | 0 |
| 2 | 1 | 1 | 2 | 1 |

Candidates: 1 and 2. Verify: count(1)=3 > 8/3=2.67 ✅, count(2)=3 ✅  
**Output:** `[1, 2]` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * MAJORITY ELEMENT > N/3 — Extended Boyer-Moore Voting
 * At most 2 elements can appear > N/3 times
 * Phase 1: Find 2 candidates using vote cancellation
 * Phase 2: Verify both candidates by counting (MANDATORY — candidates not guaranteed to be majority)
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        int cand1 = INT_MIN, cand2 = INT_MIN;
        int cnt1 = 0, cnt2 = 0;

        // phase 1: find candidates
        for (int x : nums) {
            if (x == cand1)       cnt1++;
            else if (x == cand2)  cnt2++;
            else if (cnt1 == 0) { cand1 = x; cnt1 = 1; }
            else if (cnt2 == 0) { cand2 = x; cnt2 = 1; }
            else { cnt1--; cnt2--; }
        }

        // phase 2: verify candidates (MUST verify — voting only gives candidates)
        cnt1 = cnt2 = 0;
        for (int x : nums) {
            if (x == cand1) cnt1++;
            else if (x == cand2) cnt2++;
        }

        vector<int> result;
        int n = nums.size();
        if (cnt1 > n / 3) result.push_back(cand1);
        if (cnt2 > n / 3) result.push_back(cand2);
        return result;
    }
};
```

---

## 🧾 Recall Line
> "Two candidates, two counts. Match → count++. Both zero → set candidate. Else → both--. Then VERIFY both."

## 📝 Short Revision Notes
- At most 2 elements can be > N/3 → exactly 2 candidates needed
- Verification step is MANDATORY (candidates may not actually be majority)
- For N/K majority: need K-1 candidates (generalization)
- Time O(N) (2 passes), Space O(1)

## ⚠️ Common Mistakes
❌ Skipping verification — candidates from voting are NOT guaranteed to be majority  
❌ Using only 1 candidate (N/2 approach doesn't extend to N/3)  
❌ Not initializing candidates to a value not in the array

## 📚 Related Problems
- [ ] LeetCode #229 — Majority Element II
- [ ] LeetCode #169 — Majority Element I (P19)

## 🏆 Pattern Category
`Arrays` · `Boyer-Moore Voting` · `Linear Scan`

## ⏱️ 30-Second Revision
> 2 candidates. Match → cnt++. Both cnt==0 → assign. Else cnt1--, cnt2--. VERIFY in second pass.
