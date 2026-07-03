# 🔥 Search in Rotated Sorted Array II (With Duplicates)

> **LeetCode #81** · **Difficulty:** Medium · **Step 4 — Binary Search · P09**

---

## 🧠 Problem Understanding

**What is it asking?**
Same as P08, but the rotated array **may contain duplicates**. Return `true` if `target` exists, else `false`.

**Input:** `nums = [2, 5, 6, 0, 0, 1, 2]`, `target = 0` → **Output:** `true`
**Input:** `nums = [2, 5, 6, 0, 0, 1, 2]`, `target = 3` → **Output:** `false`

**Key Observation:**
In P08, `nums[low] <= nums[mid]` reliably identified the sorted half. With duplicates that breaks when `nums[low] == nums[mid] == nums[high]` — we can't tell which half is sorted.

```
[3, 1, 2, 3, 3, 3, 3] → nums[low]=nums[mid]=nums[high]=3
Can't decide which side is sorted just from the endpoints.
```

**Fix:** when `nums[low] == nums[mid] == nums[high]`, shrink both ends (`low++, high--`) and continue. Everything else is identical to P08.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Search

Scan the array. **Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Modified Binary Search + Duplicate Guard

> 💡 P08's logic, plus one extra case at the top: if the three endpoints are equal, we can't identify the sorted half, so trim `low++` and `high--`.

```cpp
class Solution {
public:
    bool search(vector<int>& nums,int target){
        int low=0,high=nums.size()-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(nums[mid]==target){
                return true;
            }
            if(nums[low]==nums[mid] && nums[mid]==nums[high]){
                low++;
                high--;
                continue;
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
        return false;
    }
};
```

**Time:** O(log N) average, **O(N) worst case** (e.g. all equal, target absent) · **Space:** O(1).

### Dry Run
`nums = [2, 5, 6, 0, 0, 1, 2]`, `target = 0`

| low | high | mid | nums[mid] | Note |
|-----|------|-----|-----------|------|
| 0 | 6 | 3 | 0 | nums[mid]==target → **return true** ✅ |

For `target = 3`: mid values never equal 3 and endpoint-equal cases trim the ends until `low > high` → **false**.

---

## 🎤 Interview Explanation Script

> "It's the same as the no-duplicate version, but duplicates can make `nums[low]`, `nums[mid]`, and `nums[high]` all equal — then I genuinely can't tell which half is sorted. In that case I just move both ends inward by one and continue. All other cases use the exact P08 logic. The duplicate trimming is what pushes the worst case to O(N), for inputs like all-equal elements with an absent target."

---

## 🧾 Recall Line *(10-Second Revision)*

> "P08 + guard: `nums[low]==nums[mid]==nums[high]` → `low++, high--`. Returns bool."

---

## 📝 Short Revision Notes

- Only addition vs P08: the `nums[low]==nums[mid]==nums[high]` → `low++, high--` case.
- Returns `bool` (existence), not an index — duplicates make a unique index meaningless.
- Worst case O(N) when duplicates prevent halving (all equal, target absent).
- Everything else — sorted-half detection and range checks — is identical to P08.

---

## ⚠️ Common Mistakes

❌ Only checking `nums[low]==nums[mid]` without `nums[mid]==nums[high]` — may trim incorrectly.
❌ Forgetting `continue` after `low++, high--` → falls into stale sorted-half logic.
❌ Claiming O(log N) worst case — it degrades to O(N) with heavy duplicates.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "rotated sorted array **with duplicates**", "return true/false, not index" → **P08 + endpoint-equal trim**.

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array` · `Duplicates`

---

## ⏱️ 30-Second Last-Minute Revision

> **P08 + one guard:** `nums[low]==nums[mid]==nums[high]` → shrink both ends. Returns bool. Worst case O(N) with duplicates, else O(log N).
