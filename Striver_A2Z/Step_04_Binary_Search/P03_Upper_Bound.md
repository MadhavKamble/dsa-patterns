# 🔥 Implement Upper Bound

> **Striver / GFG** · **Difficulty:** Easy · **Step 4 — Binary Search · P03**

---

## 🧠 Problem Understanding

**What is it asking?**
In a **sorted** array, find the **upper bound** of `x` — the index of the **first element strictly `> x`**. If every element is `≤ x`, the answer is `n`.

**Input:** `arr = [3, 5, 8, 9, 15, 19]`, `x = 9` → **Output:** `4` (first element > 9 is `15` at index 4)
**Input:** `arr = [3, 5, 8, 9]`, `x = 9` → **Output:** `4` (nothing > 9 → n)

**Key Observations:**
- Same as C++ STL `upper_bound`.
- Only difference from lower bound: the comparison is **strictly `>`** instead of `≥`.
- `upperBound(x) - lowerBound(x)` = count of occurrences of `x`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Return the first index whose value is strictly greater than `x`.

```cpp
class Solution {
public:
    int upperBound(vector<int>& arr,int n,int x){
        for(int i=0;i<n;i++)
            if(arr[i]>x) return i;
        return n;
    }
};
```

**Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Binary Search

> 💡 When `arr[mid] > x`, `mid` is a candidate → store it and look further left for a smaller valid index. When `arr[mid] <= x`, the answer is strictly to the right.

```cpp
class Solution {
public:
    int upperBound(vector<int>& arr,int x,int n){
        int low=0,high=n-1;
        int ans=n;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]>x){
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
1. `ans=n` (default: nothing is `> x`).
2. `arr[mid] > x` → record `ans=mid`, search left.
3. `arr[mid] <= x` → search right.
4. Return `ans`.

### Dry Run
`arr = [3, 5, 8, 9, 15, 19]`, `x = 9`

| low | high | mid | arr[mid] | >9? | ans | Action |
|-----|------|-----|----------|-----|-----|--------|
| 0 | 5 | 2 | 8 | ❌ | 6 | low=3 |
| 3 | 5 | 4 | 15 | ✅ | 4 | high=3 |
| 3 | 3 | 3 | 9 | ❌ | 4 | low=4 |
| 4 | 3 | — | — | — | 4 | low>high → **return 4** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "First index with `arr[i] > x`. `arr[mid]>x` → `ans=mid, high=mid-1`. Else `low=mid+1`. Default `ans=n`."

---

## 📝 Short Revision Notes

- Upper bound = first element **strictly > x** (`>`).
- **Lower vs Upper:** lower uses `>=`, upper uses `>` — that single character is the whole difference.
- Count of `x` in sorted array = `upperBound(x) - lowerBound(x)`.
- STL: `upper_bound(arr.begin(), arr.end(), x) - arr.begin()`.

---

## ⚠️ Common Mistakes

❌ Using `>=` instead of `>` → that's lower bound.
❌ Confusing which one is "≥": lower = ≥, upper = strictly >.
❌ Forgetting the `ans=n` default.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "first element strictly greater than x", "count occurrences via bounds" → **upper bound**.

---

## 🏆 Pattern Category

`Binary Search` · `Upper Bound` · `Boundary Search`

---

## ⏱️ 30-Second Last-Minute Revision

> **Upper bound = first `arr[i] > x`.** `arr[mid]>x` → store `ans=mid`, go left; else go right. Default `n`. Differs from lower bound only by `>` vs `>=`. `O(log N)`.
