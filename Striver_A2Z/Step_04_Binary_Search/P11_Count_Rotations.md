# 🔥 Find How Many Times the Array Has Been Rotated

> **Striver / GFG** · **Difficulty:** Easy-Medium · **Step 4 — Binary Search · P11**

---

## 🧠 Problem Understanding

**What is it asking?**
A sorted array was rotated some number of times. Find that rotation count.

**Input:** `arr = [4, 5, 6, 7, 0, 1, 2, 3]` → **Output:** `4`
**Input:** `arr = [1, 2, 3, 4, 5]` (not rotated) → **Output:** `0`

**Key Observation:**
The number of rotations = **index of the minimum element**. After `k` rotations, the original smallest element ends up at index `k`. So this is [P10 Find Minimum](P10_Find_Minimum_Rotated_Sorted_Array.md) — but returning the **index** instead of the value.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Return the index of the minimum. **Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Binary Search (index of minimum)

> 💡 Compare `arr[mid]` with `arr[high]`. If `arr[mid] > arr[high]`, the minimum (pivot) is strictly to the right → `low = mid+1`. Otherwise it's at `mid` or to the left → `high = mid`. Converge with `low < high`; the meeting index is the rotation count.

```cpp
class Solution {
public:
    int findRotations(vector<int>& arr){
        int low=0,high=arr.size()-1;
        while(low<high){
            int mid=low+(high-low)/2;
            if(arr[mid]>arr[high]){
                low=mid+1;
            }else{
                high=mid;
            }
        }
        return low;
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run
`arr = [4, 5, 6, 7, 0, 1, 2, 3]`

| low | high | mid | arr[mid] | arr[high] | Action |
|-----|------|-----|----------|-----------|--------|
| 0 | 7 | 3 | 7 | 3 | 7>3 → low=4 |
| 4 | 7 | 5 | 1 | 3 | 1<3 → high=5 |
| 4 | 5 | 4 | 0 | 1 | 0<1 → high=4 |
| 4 | 4 | — | — | — | low==high → **return 4** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Rotations = index of minimum. `arr[mid]>arr[high]` → `low=mid+1`, else `high=mid`. Return `low`."

---

## 📝 Short Revision Notes

- Rotation count = index of the minimum element.
- Identical to P10's compact variant, but returns `low` (index), not `nums[low]` (value).
- Uses `low < high` and `high = mid` (not `mid-1`) so the pivot index isn't skipped.
- Non-rotated array → converges to index `0` naturally.

---

## ⚠️ Common Mistakes

❌ Returning the value instead of the index.
❌ `high = mid - 1` → can skip the actual minimum.
❌ `low <= high` with `high = mid` → infinite loop.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "how many times rotated", "rotation count of a sorted array" → **index of minimum via binary search**.

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array`

---

## ⏱️ 30-Second Last-Minute Revision

> **Rotations = index of min.** `arr[mid]>arr[high]` → go right, else `high=mid`. Return `low`. `O(log N)`.
