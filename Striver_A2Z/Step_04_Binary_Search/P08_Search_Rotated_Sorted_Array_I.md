# 🔥 Search in Rotated Sorted Array I (No Duplicates)

> **LeetCode #33** · **Difficulty:** Medium · **Step 4 — Binary Search · P08**

---

## 🧠 Problem Understanding

**What is it asking?**
A sorted array of **distinct** elements is rotated at an unknown pivot. Given `target`, return its index, or `-1` if absent — in O(log N).

**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 0` → **Output:** `4`
**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 3` → **Output:** `-1`

**Edge cases:** empty array, single element, no rotation (already sorted), target absent.

**Key Observation:**
Even after rotation, at any `mid` **at least one half is fully sorted**:
- `nums[low] <= nums[mid]` → **left half is sorted**
- otherwise → **right half is sorted**

Identify the sorted half, check whether `target` lies inside its range, and move accordingly.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Search

Scan every element. **Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Modified Binary Search

> 💡 At each step: (1) find the sorted half, (2) check if `target` is within that half's range, (3) discard the other half.

```cpp
class Solution {
public:
    int search(vector<int>& nums,int target){
        int low=0;
        int high=nums.size()-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(nums[mid]==target){
                return mid;
            }
            if(nums[low]<=nums[mid]){
                if(nums[low]<=target && target<nums[mid]){
                    high=mid-1;
                }else{
                    low=mid+1;
                }
            }else{
                if(nums[mid]<target && target<=nums[high]){
                    low=mid+1;
                }else{
                    high=mid-1;
                }
            }
        }
        return -1;
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Algorithm
1. `nums[mid]==target` → return `mid`.
2. **Left sorted** (`nums[low] <= nums[mid]`): if `nums[low] <= target < nums[mid]` search left (`high=mid-1`), else search right.
3. **Right sorted** (else): if `nums[mid] < target <= nums[high]` search right (`low=mid+1`), else search left.

### Dry Run
`nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 0`

| low | high | mid | nums[mid] | Sorted half | target in it? | Action |
|-----|------|-----|-----------|-------------|---------------|--------|
| 0 | 6 | 3 | 7 | left (4≤7) | 0 in [4,7)? ❌ | low=4 |
| 4 | 6 | 5 | 1 | left (0≤1) | 0 in [0,1)? ✅ | high=4 |
| 4 | 4 | 4 | 0 | — | nums[4]==0 | **return 4** ✅ |

---

## 🎤 Interview Explanation Script

> "The array isn't globally sorted, but at any midpoint one half always is. I check `nums[low] <= nums[mid]` — if true, the left half is sorted, and I can test whether the target falls in `[nums[low], nums[mid])`. If it does, I go left; otherwise right. If the left half isn't sorted, the right half is, and I mirror the logic. Each step halves the space, so O(log N)."

---

## 🧾 Recall Line *(10-Second Revision)*

> "`nums[low]<=nums[mid]` → left sorted: if `low<=target<mid` go left else right. Else right sorted: if `mid<target<=high` go right else left."

---

## 📝 Short Revision Notes

- At least one half is always sorted (guaranteed by **distinct** elements).
- Left sorted test: `nums[low] <= nums[mid]` (use `<=`, not `<`, so no-rotation case works).
- Range checks: left half `nums[low] <= target < nums[mid]`; right half `nums[mid] < target <= nums[high]`.
- Works unchanged for a non-rotated array.

---

## ⚠️ Common Mistakes

❌ Using `<` instead of `<=` in `nums[low] <= nums[mid]` → breaks when `low==mid`.
❌ Wrong range boundaries (`<` vs `<=`) in the target-in-half checks.
❌ Comparing against `nums[low]`/`nums[high]` inconsistently for the two halves.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "search in rotated sorted array", "sorted then rotated at unknown pivot" → **find the sorted half, check the range**.

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array`

---

## ⏱️ 30-Second Last-Minute Revision

> **One half is always sorted.** `nums[low]<=nums[mid]` → left sorted (check `[low,mid)`), else right sorted (check `(mid,high]`). Move into the half that can contain target. `O(log N)`.
