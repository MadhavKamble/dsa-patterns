# 🔥 Find First and Last Position of Element in Sorted Array

> **LeetCode #34** · **Difficulty:** Medium · **Step 4 — Binary Search · P06**

---

## 🧠 Problem Understanding

**What is it asking?**
In a **sorted** array (with possible duplicates), find the **first** and **last** index of `target`. Return `[-1, -1]` if it is not present.

**Input:** `nums = [5, 7, 7, 8, 8, 10]`, `target = 8` → **Output:** `[3, 4]`
**Input:** `nums = [5, 7, 7, 8, 8, 10]`, `target = 6` → **Output:** `[-1, -1]`

**Key Observations:**
- Two independent binary searches: one biased **left** (first), one biased **right** (last).
- On a match, don't stop — record the index and keep searching the side that could hold an earlier/later occurrence.
- `first = lowerBound(target)`, `last = upperBound(target) - 1` is the equivalent bound-based view.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Walk left-to-right, record the first and last index equal to `target`.

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums,int target){
        int first=-1,last=-1;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==target){
                if(first==-1) first=i;
                last=i;
            }
        }
        return {first,last};
    }
};
```

**Time:** O(N) · **Space:** O(1) — ignores sortedness.

---

### 🥇 Optimal — Two Modified Binary Searches

> 💡 **First occurrence:** on `arr[mid]==target`, store `mid` and move **left** (`high=mid-1`) to find an earlier one.
> **Last occurrence:** on `arr[mid]==target`, store `mid` and move **right** (`low=mid+1`).

```cpp
class Solution {
public:
    int firstOccurence(vector<int>& arr,int target){
        int low=0,high=arr.size()-1;
        int ans=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(arr[mid]==target){
                ans=mid;
                high=mid-1;
            }else if(arr[mid]<target){
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return ans;
    }
    int lastOccurence(vector<int>& arr,int target){
        int low=0,high=arr.size()-1;
        int ans=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(arr[mid]==target){
                ans=mid;
                low=mid+1;
            }else if(arr[mid]<target){
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return ans;
    }
    vector<int> searchRange(vector<int>& nums,int target){
        return {firstOccurence(nums,target),lastOccurence(nums,target)};
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run — First occurrence
`nums = [5, 7, 7, 8, 8, 10]`, `target = 8`

| low | high | mid | arr[mid] | Action | ans |
|-----|------|-----|----------|--------|-----|
| 0 | 5 | 2 | 7 | 7<8 → low=3 | -1 |
| 3 | 5 | 4 | 8 | ==8 → store, high=3 | 4 |
| 3 | 3 | 3 | 8 | ==8 → store, high=2 | 3 |
| 3 | 2 | — | — | low>high → **first = 3** | 3 |

### Dry Run — Last occurrence
| low | high | mid | arr[mid] | Action | ans |
|-----|------|-----|----------|--------|-----|
| 0 | 5 | 2 | 7 | 7<8 → low=3 | -1 |
| 3 | 5 | 4 | 8 | ==8 → store, low=5 | 4 |
| 5 | 5 | 5 | 10 | 10>8 → high=4 | 4 |
| 5 | 4 | — | — | low>high → **last = 4** | 4 |

**Output:** `[3, 4]` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "First: on match store & go left (`high=mid-1`). Last: on match store & go right (`low=mid+1`). Default `-1`."

---

## 📝 Short Revision Notes

- Two binary searches — one for each end.
- Only difference between them: on `==target`, first moves `high=mid-1`, last moves `low=mid+1`.
- Bound view: `first = lowerBound(target)`, `last = upperBound(target) - 1`.
- If `first == -1`, target is absent → return `[-1, -1]`.

---

## ⚠️ Common Mistakes

❌ Returning on the first `==target` match → gives *a* position, not the first/last.
❌ Swapping the bias (first moving right, last moving left).
❌ Forgetting `[-1, -1]` when the element is absent.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "first and last position", "start/end index of target", "range of a value in sorted array" → **two biased binary searches**.

---

## 🏆 Pattern Category

`Binary Search` · `Lower/Upper Bound` · `Duplicates`

---

## ⏱️ 30-Second Last-Minute Revision

> **First = leftmost match, Last = rightmost match.** On `==target`: first goes left, last goes right; both record the index. `[-1,-1]` if absent. `O(log N)`.
