# 🔥 Find Minimum in Rotated Sorted Array

> **LeetCode #153** · **Difficulty:** Medium · **Step 4 — Binary Search · P10**

---

## 🧠 Problem Understanding

**What is it asking?**
A sorted array of **distinct** elements is rotated at an unknown pivot. Find the **minimum** element in O(log N).

**Input:** `nums = [3, 4, 5, 1, 2]` → **Output:** `1`
**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]` → **Output:** `0`

**Edge cases:** not rotated (first element is the minimum), single element.

**Key Observation:**
The rotated array is **two sorted parts**, and the minimum sits at the pivot.
- If `nums[low] <= nums[high]`, the current segment is fully sorted → `nums[low]` is the minimum.
- Otherwise one half is sorted; the minimum lies in the **unsorted** half → always move there.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

`min_element` over the array. **Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Binary Search (pick the smaller of the sorted half's start, move to the unsorted half)

> 💡 At each step, one half is sorted. Take its **smallest** value as an answer candidate, then jump into the **unsorted** half (that's where a still-smaller pivot value hides). Early exit when the whole window is already sorted.

```cpp
class Solution {
public:
    int findMin(vector<int>& nums){
        int low=0,high=nums.size()-1;
        int ans=INT_MAX;
        while(low<=high){
            if(nums[low]<nums[high]){
                ans=min(ans,nums[low]);
                break;
            }
            int mid=low+(high-low)/2;
            if(nums[low]<=nums[mid]){
                ans=min(ans,nums[low]);
                low=mid+1;
            }else{
                ans=min(ans,nums[mid]);
                high=mid-1;
            }
        }
        return ans;
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run
`nums = [4, 5, 6, 7, 0, 1, 2]`

| low | high | mid | Window sorted? | Sorted half | Candidate | Action |
|-----|------|-----|----------------|-------------|-----------|--------|
| 0 | 6 | 3 | 4<2? no | left (4≤7) | ans=4 | low=4 |
| 4 | 6 | 5 | 0<2? yes | — | ans=min(4,0)=0 | **break** |

**Output:** `0` ✅

---

### 🥈 Alternative — Compare `nums[mid]` with `nums[high]` (compact)

> The same idea, minus the candidate tracking — converge directly to the pivot index.

```cpp
class Solution {
public:
    int findMin(vector<int>& nums){
        int low=0,high=nums.size()-1;
        while(low<high){
            int mid=low+(high-low)/2;
            if(nums[mid]>nums[high]) low=mid+1;
            else high=mid;
        }
        return nums[low];
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Minimum lies in the unsorted part. Take the sorted half's start as a candidate, then move into the unsorted half. Early-exit when `nums[low] < nums[high]`."

---

## 📝 Short Revision Notes

- Rotated array = two sorted parts; minimum = pivot.
- `nums[low] <= nums[high]` → segment sorted → `nums[low]` is the min of that window.
- Left sorted (`nums[low] <= nums[mid]`) → candidate `nums[low]`, go right; else candidate `nums[mid]`, go left.
- Compact variant: compare `nums[mid]` with `nums[high]`, converge with `low < high`.

---

## ⚠️ Common Mistakes

❌ Comparing `nums[mid]` with `nums[low]` without care → trickier invariant.
❌ Forgetting the early exit → still correct but does extra work.
❌ `low = mid` (not `mid+1`) in the compact variant → infinite loop.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "minimum / pivot of a rotated sorted array" → **eliminate the sorted half, keep the unsorted half**.

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array`

---

## ⏱️ 30-Second Last-Minute Revision

> **Min is at the pivot, inside the unsorted half.** Grab the sorted half's smallest as candidate, move to the unsorted side. Early exit when window is sorted. `O(log N)`.
