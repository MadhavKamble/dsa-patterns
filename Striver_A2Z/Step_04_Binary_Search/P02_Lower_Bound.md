# 🔥 Implement Lower Bound

> **Striver / GFG** · **Difficulty:** Easy · **Step 4 — Binary Search · P02**

---

## 🧠 Problem Understanding

**What is it asking?**
In a **sorted** array, find the **lower bound** of `x` — the index of the **first element `≥ x`**. If every element is `< x`, the answer is `n` (past the end).

**Input:** `arr = [3, 5, 8, 15, 19]`, `x = 9` → **Output:** `3` (first element ≥ 9 is `15` at index 3)
**Input:** `arr = [3, 5, 8, 15, 19]`, `x = 20` → **Output:** `5` (no element ≥ 20 → n)

**Key Observations:**
- Same as C++ STL `lower_bound`.
- The array of predicates `arr[i] >= x` looks like `F F F ... T T T` — we want the **first T**.
- Since it's monotonic, binary search finds that boundary in O(log N).

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Return the first index whose value is `≥ x`.

```cpp
class Solution {
public:
    int lowerBound(vector<int>& arr,int n,int x){
        for(int i=0;i<n;i++)
            if(arr[i]>=x) return i;
        return n;
    }
};
```

**Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Binary Search

> 💡 When `arr[mid] >= x`, `mid` is a **candidate** answer, but a smaller index might also work → store it and shrink to the left. When `arr[mid] < x`, the answer is strictly to the right.

```cpp
class Solution {
public:
    int lowerBound(vector<int>& arr,int n,int x){
        int low=0,high=n-1;
        int ans=n;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]>=x){
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

**Time:** O(log N) · **Space:** O(1).

### Algorithm
1. `ans=n` (default: nothing is `≥ x`).
2. `arr[mid] >= x` → record `ans=mid`, search left (`high=mid-1`).
3. `arr[mid] < x` → search right (`low=mid+1`).
4. Return `ans`.

### Dry Run
`arr = [3, 5, 8, 15, 19]`, `x = 9`

| low | high | mid | arr[mid] | ≥9? | ans | Action |
|-----|------|-----|----------|-----|-----|--------|
| 0 | 4 | 2 | 8 | ❌ | 5 | low=3 |
| 3 | 4 | 3 | 15 | ✅ | 3 | high=2 |
| 3 | 2 | — | — | — | 3 | low>high → **return 3** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "First index with `arr[i] >= x`. `arr[mid]>=x` → `ans=mid, high=mid-1`. Else `low=mid+1`. Default `ans=n`."

---

## 📝 Short Revision Notes

- Lower bound = first element **≥ x** (`>=`).
- Default answer is `n` (insertion at end if all elements are smaller).
- STL: `lower_bound(arr.begin(), arr.end(), x) - arr.begin()`.
- Overflow-safe mid: `low+(high-low)/2` (the `(low+high)/2` form can overflow for very large indices).

---

## ⚠️ Common Mistakes

❌ Using `>` instead of `>=` → that's **upper bound**, not lower bound.
❌ Forgetting to default `ans=n` → wrong answer when no element qualifies.
❌ `high=mid` instead of `high=mid-1` while also using `low<=high` → infinite loop.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "first element ≥ x", "insert position", "count of elements < x" → **lower bound**.

---

## 🏆 Pattern Category

`Binary Search` · `Lower Bound` · `Boundary Search`

---

## ⏱️ 30-Second Last-Minute Revision

> **Lower bound = first `arr[i] >= x`.** `arr[mid]>=x` → store `ans=mid`, go left; else go right. Default `n`. `O(log N)`.
