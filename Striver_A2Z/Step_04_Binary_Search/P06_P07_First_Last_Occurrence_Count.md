# 🔥 First/Last Occurrence & Count Occurrences in Sorted Array

> **LeetCode #34** · **Difficulty:** Easy · **Step 4 — Binary Search · P06 & P07**

---

## 🧠 Problem Understanding

**P06:** Given a sorted array and target, find the **first and last** position of target.  
**P07:** Count total occurrences of target.

**Input:** `arr=[5,7,7,8,8,10]`, target=8 → First=3, Last=4, Count=2

---

## 🥇 Optimal — Two Binary Searches

### Key Observation
> 💡 First occurrence = **lower bound** of target.  
> Last occurrence = **upper bound** of target − 1.  
> Count = last − first + 1.

### Algorithm
- `first = lowerBound(arr, target)` → if `arr[first] != target`, target absent
- `last = upperBound(arr, target) - 1`
- `count = last - first + 1`

### Dry Run
`arr=[5,7,7,8,8,10]`, target=8

Lower bound of 8: first index ≥ 8 = index **3**  
Upper bound of 8: first index > 8 = index **5**  
Last = 5 - 1 = **4**, Count = 4 - 3 + 1 = **2** ✅

---

## 💻 Clean C++ Code

```cpp
/*
 * FIRST AND LAST OCCURRENCE — two binary searches
 * first  = lower_bound (first >= target)
 * last   = upper_bound - 1 (last <= target)
 * count  = last - first + 1
 * Time O(log N) | Space O(1)
 */
class Solution {
private:
    int lowerBound(vector<int>& arr, int target) {
        int lo = 0, hi = arr.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] < target) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }

    int upperBound(vector<int>& arr, int target) {
        int lo = 0, hi = arr.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] <= target) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }

public:
    // P06: first and last position
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = lowerBound(nums, target);
        if (first == nums.size() || nums[first] != target)
            return {-1, -1};
        int last = upperBound(nums, target) - 1;
        return {first, last};
    }

    // P07: count occurrences
    int countOccurrences(vector<int>& nums, int target) {
        int first = lowerBound(nums, target);
        if (first == nums.size() || nums[first] != target) return 0;
        int last = upperBound(nums, target) - 1;
        return last - first + 1;
    }
};
```

---

## 🧾 Recall Line
> "first = lowerBound(target). last = upperBound(target) - 1. count = last - first + 1."

## 📝 Short Revision Notes
- Always verify `arr[first] == target` after lower bound (target may not exist)
- STL: `lower_bound` and `upper_bound` from `<algorithm>`
- Count formula: `upper_bound(target) - lower_bound(target)`
- Time O(log N) — two binary searches

## ⚠️ Common Mistakes
❌ Not checking if target actually exists after getting lower bound  
❌ `last = upperBound - 1` forgetting the `-1`  
❌ Single binary search that finds one occurrence but doesn't generalize

## 🏆 Pattern Category
`Binary Search` · `Lower/Upper Bound`

## ⏱️ 30-Second Revision
> first = lowerBound. If out-of-bounds or arr[first]≠target: return -1. last = upperBound-1. count = last-first+1.
