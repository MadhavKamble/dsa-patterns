# 🔥 Split Array Largest Sum

> **LeetCode #410** · **Difficulty:** Hard · **Step 4 — Binary Search · P23**

---

## 🧠 Problem Understanding

**What is it asking?**
Split `nums` into `k` **contiguous** subarrays so that the **largest subarray sum is minimized**. Return that minimized largest sum.

**Input:** `nums = [7, 2, 5, 10, 8]`, `k = 2` → **Output:** `18` (`[7,2,5] | [10,8]` → max(14,18)=18)

**Key Observation:**
- This is **exactly Book Allocation / Painter's Partition** — same technique, different story.
- Search over the **max-sum limit**; a larger limit needs **fewer** splits (monotonic).
- Search space: `low = max(nums)`, `high = sum(nums)`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Limit

For each candidate max-sum from `max(nums)` to `sum(nums)`, count splits; return the first needing `≤ k`. **Time:** O(sum · n).

---

### 🥇 Optimal — Binary Search on the Max-Sum

> 💡 `splitArr(mid)` greedily extends the current subarray until adding the next element would exceed `mid`, then starts a new split. If splits `≤ k`, `mid` is feasible → minimize (`high = mid-1`); else raise the limit.

```cpp
class Solution {
public:
    int splitArr(vector<int>& nums,int mid){
        int splits=1;
        int splitSum=0;
        for(int num:nums){
            if(splitSum+num<=mid){
                splitSum+=num;
            }else{
                splits++;
                splitSum=num;
            }
        }
        return splits;
    }
    int splitArray(vector<int>& nums,int k){
        if(nums.size()<k) return -1;
        int low=*max_element(nums.begin(),nums.end());
        int high=accumulate(nums.begin(),nums.end(),0);
        int ans=low;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(splitArr(nums,mid)<=k){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;
    }
};
```

**Time:** O(n · log(sum(nums))) · **Space:** O(1).

### Dry Run
`nums = [7, 2, 5, 10, 8]`, `k = 2`, search `[10, 32]`

| low | high | mid | splits at ≤mid | ≤2? | ans | Action |
|-----|------|-----|----------------|-----|-----|--------|
| 10 | 32 | 21 | [7,2,5],[10,8] → 2 | ✅ | 21 | high=20 |
| 10 | 20 | 15 | [7,2,5],[10],[8] → 3 | ❌ | 21 | low=16 |
| 16 | 20 | 18 | [7,2,5],[10,8] → 2 | ✅ | 18 | high=17 |
| 16 | 17 | 16 | [7,2,5],[10],[8] → 3 | ❌ | 18 | low=17 |
| 17 | 17 | 17 | 3 | ❌ | 18 | low=18 |
| 18 | 17 | — | — | — | 18 | **return 18** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on max-sum `[max, sum]`. `splitArr<=k` → minimize (`high=mid-1`), else raise limit. Same as Book Allocation."

---

## 📝 Short Revision Notes

- **Twin of Book Allocation (P22) & Painter's Partition (P24)** — identical binary-search-on-answer with greedy split count.
- `low = max(nums)` (a single element can't be split), `high = sum(nums)`.
- Feasible (`splits ≤ k`) → shrink the limit; store the candidate answer.
- Subarrays must be **contiguous** — that's what validates the greedy pass.

---

## ⚠️ Common Mistakes

❌ Setting `low = 0` instead of `max(nums)`.
❌ Comparing `splits < k` instead of `≤ k` (fewer splits than allowed is still fine).
❌ Not handling the impossible `k > n` case.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "split into k contiguous parts, minimize the largest part sum" → **binary search on answer** (= Book Allocation).

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Minimize Maximum` · `Greedy Partition`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS max-sum `[max, sum]`.** Greedy `splitArr`; `splits<=k` → minimize, else raise. Same code as Book Allocation. `O(n·log sum)`.
