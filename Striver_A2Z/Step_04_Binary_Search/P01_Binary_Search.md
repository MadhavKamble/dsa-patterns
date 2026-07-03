# 🔥 Binary Search (Standard)

> **LeetCode #704** · **Difficulty:** Easy · **Step 4 — Binary Search · P01**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **sorted** array `nums` and a `target`, return the index of `target`. Return `-1` if it is not present.

**Input:** `nums = [-1, 0, 3, 5, 9, 12]`, `target = 9` → **Output:** `4`
**Input:** `nums = [-1, 0, 3, 5, 9, 12]`, `target = 2` → **Output:** `-1`

**Key Observations:**
- Array is sorted → we can discard half the search space at every step.
- Compare `target` with the middle element to decide which half to keep.
- `O(log N)` is the best possible for search in a sorted array.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Walk the array, return the first index equal to `target`.

```cpp
class Solution {
public:
    int search(vector<int>& nums,int target){
        for(int i=0;i<nums.size();i++)
            if(nums[i]==target) return i;
        return -1;
    }
};
```

**Time:** O(N) · **Space:** O(1) — ignores the fact that the array is sorted.

---

### 🥇 Optimal — Binary Search (Recursive)

> 💡 Look at the middle. If it equals `target`, done. If `target` is smaller, it can only be in the **left** half; if larger, only in the **right** half. Recurse on that half and throw the other half away.

```cpp
class Solution {
public:
    int binarySearch(vector<int> nums,int low,int high,int target){
        if(low>high) return -1;
        int mid=(low+high)/2;
        if(nums[mid]==target) return mid;
        else if(nums[mid]>target) return binarySearch(nums,low,mid-1,target);
        else return binarySearch(nums,mid+1,high,target);
    }
    int search(vector<int>& nums,int target){
        return binarySearch(nums,0,nums.size()-1,target);
    }
};
```

**Time:** O(log N) · **Space:** O(log N) recursion stack.

### Algorithm
1. Base case: `low>high` → search space empty → return `-1`.
2. `mid=(low+high)/2`.
3. `nums[mid]==target` → return `mid`.
4. `nums[mid]>target` → answer is in `[low, mid-1]` → recurse left.
5. Else → answer is in `[mid+1, high]` → recurse right.

### Dry Run
`nums = [-1, 0, 3, 5, 9, 12]`, `target = 9`

| low | high | mid | nums[mid] | Action |
|-----|------|-----|-----------|--------|
| 0 | 5 | 2 | 3 | 3<9 → recurse right [3,5] |
| 3 | 5 | 4 | 9 | 9==9 → **return 4** ✅ |

---

### 🥇 Optimal — Binary Search (Iterative, O(1) space)

Same logic without the call stack — preferred in interviews to avoid recursion overhead.

```cpp
class Solution {
public:
    int search(vector<int>& nums,int target){
        int lo=0,hi=nums.size()-1;
        while(lo<=hi){
            int mid=lo+(hi-lo)/2;
            if(nums[mid]==target) return mid;
            else if(nums[mid]<target) lo=mid+1;
            else hi=mid-1;
        }
        return -1;
    }
};
```

**Time:** O(log N) · **Space:** O(1).

---

## 🎤 Interview Explanation Script

> "The array is sorted, so I use binary search. I look at the middle element: if it's the target, I'm done. If the target is smaller, it must lie in the left half, otherwise in the right half. I discard the other half and repeat. Each step halves the search space, giving O(log N)."

> "I can write it recursively — passing the shrinking `[low, high]` bounds — or iteratively with two pointers. The iterative version is O(1) space, so I'd usually prefer it."

---

## 🧾 Recall Line *(10-Second Revision)*

> "`mid=(low+high)/2`. `==target` return mid. `>target` go left `[low, mid-1]`. `<target` go right `[mid+1, high]`. Empty range → -1."

---

## 📝 Short Revision Notes

- Works **only on sorted** input.
- Recursive: base case `low>high`. Iterative: loop `lo<=hi`.
- Overflow-safe mid: `lo+(hi-lo)/2` (the `(low+high)/2` form can overflow for very large indices).
- Move `lo=mid+1` / `hi=mid-1` — never `mid` — to guarantee progress and avoid infinite loops.

---

## ⚠️ Common Mistakes

❌ Recursing on the wrong bound (e.g. passing `0` instead of `low` for the left half) — re-scans an excluded region.
❌ `lo=mid` / `hi=mid` in the iterative form → infinite loop.
❌ Wrong loop/base condition: iterative uses `lo<=hi`, recursion stops at `low>high`.
❌ Applying binary search to an unsorted array.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "sorted array" + "find / search / index of" → **binary search**, O(log N).

---

## 🏆 Pattern Category

`Binary Search` · `Arrays` · `Sorted`

---

## ⏱️ 30-Second Last-Minute Revision

> **Sorted array search.** Compare `target` with `nums[mid]`; keep the half that can contain it. Recursive `[low,high]` bounds or iterative `lo<=hi`. `O(log N)` time. Watch the boundary updates (`mid±1`).
