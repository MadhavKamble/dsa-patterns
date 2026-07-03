# 🔥 Floor and Ceil in a Sorted Array

> **Striver / GFG** · **Difficulty:** Easy · **Step 4 — Binary Search · P05**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **sorted** array and a value `x`, find:
- **Floor(x):** the **largest element `≤ x`**.
- **Ceil(x):** the **smallest element `≥ x`**.

Return `-1` for either if it does not exist.

**Input:** `arr = [3, 4, 4, 7, 8, 10]`, `x = 5` → **Output:** `floor = 4`, `ceil = 7`
**Input:** `arr = [3, 4, 4, 7, 8, 10]`, `x = 8` → **Output:** `floor = 8`, `ceil = 8`

**Key Observations:**
- **Ceil** is exactly the **lower-bound value** (first element `≥ x`).
- **Floor** is the mirror: keep moving right while `arr[mid] ≤ x`, remembering the last valid value.
- Both are independent binary searches → O(log N) each.
- These return **values**, not indices (unlike lower/upper bound).

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Track the largest `≤ x` (floor) and smallest `≥ x` (ceil) in one pass.

```cpp
class Solution {
public:
    pair<int,int> getFloorAndCeil(vector<int>& arr,int n,int x){
        int floor=-1,ceil=-1;
        for(int i=0;i<n;i++){
            if(arr[i]<=x) floor=arr[i];
            if(arr[i]>=x&&ceil==-1) ceil=arr[i];
        }
        return {floor,ceil};
    }
};
```

**Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Two Binary Searches

> 💡 **Floor:** when `arr[mid] <= x`, it's a candidate floor → store `arr[mid]` and go **right** for a bigger valid value.
> **Ceil:** when `arr[mid] >= x`, it's a candidate ceil → store `arr[mid]` and go **left** for a smaller valid value.

```cpp
class Solution {
public:
    int findFloor(int arr[],int n,int x){
        int low=0,high=n-1;
        int ans=-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]<=x){
                ans=arr[mid];
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return ans;
    }
    int findCeil(int arr[],int n,int x){
        int low=0,high=n-1;
        int ans=-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]>=x){
                ans=arr[mid];
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;
    }
    pair<int,int> getFloorAndCeil(int arr[],int n,int x){
        int f=findFloor(arr,n,x);
        int c=findCeil(arr,n,x);
        return make_pair(f,c);
    }
};
```

**Time:** O(log N) per search · **Space:** O(1).

### Dry Run — Floor
`arr = [3, 4, 4, 7, 8, 10]`, `x = 5`

| low | high | mid | arr[mid] | ≤5? | ans | Action |
|-----|------|-----|----------|-----|-----|--------|
| 0 | 5 | 2 | 4 | ✅ | 4 | low=3 |
| 3 | 5 | 4 | 8 | ❌ | 4 | high=3 |
| 3 | 3 | 3 | 7 | ❌ | 4 | high=2 |
| 3 | 2 | — | — | — | 4 | low>high → **floor = 4** ✅ |

### Dry Run — Ceil
`arr = [3, 4, 4, 7, 8, 10]`, `x = 5`

| low | high | mid | arr[mid] | ≥5? | ans | Action |
|-----|------|-----|----------|-----|-----|--------|
| 0 | 5 | 2 | 4 | ❌ | -1 | low=3 |
| 3 | 5 | 4 | 8 | ✅ | 8 | high=3 |
| 3 | 3 | 3 | 7 | ✅ | 7 | high=2 |
| 3 | 2 | — | — | — | 7 | low>high → **ceil = 7** ✅ |

---

## 🎤 Interview Explanation Script

> "Ceil is the smallest element ≥ x — that's just the lower-bound value. Floor is the largest element ≤ x — the mirror image. For floor, whenever `arr[mid] <= x` I store it as a candidate and move right to try for a larger value still ≤ x. For ceil, whenever `arr[mid] >= x` I store it and move left for a smaller value still ≥ x. Two O(log N) searches."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Floor: `arr[mid]<=x` → `ans=arr[mid], low=mid+1`. Ceil: `arr[mid]>=x` → `ans=arr[mid], high=mid-1`. Both default -1."

---

## 📝 Short Revision Notes

- **Ceil = lower bound value** (first `≥ x`); **Floor = last `≤ x`**.
- Floor moves **right** on a hit (want bigger); Ceil moves **left** on a hit (want smaller).
- These return the **value** `arr[mid]`, not the index — store `arr[mid]`, not `mid`.
- If `x` is present, floor = ceil = x.
- Default `-1` when no valid element exists (e.g. floor of a value smaller than the whole array).

---

## ⚠️ Common Mistakes

❌ Storing `mid` (index) instead of `arr[mid]` (value).
❌ Swapping the directions — floor goes right on `≤`, ceil goes left on `≥`.
❌ Forgetting the `-1` default when floor/ceil doesn't exist.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "largest value ≤ x" → **floor**; "smallest value ≥ x" → **ceil** (= lower bound value).

---

## 🏆 Pattern Category

`Binary Search` · `Floor / Ceil` · `Boundary Search`

---

## ⏱️ 30-Second Last-Minute Revision

> **Floor = last `arr[mid] <= x` (go right on hit). Ceil = first `arr[mid] >= x` (go left on hit).** Store the value, not the index. Default `-1`. `O(log N)`.
