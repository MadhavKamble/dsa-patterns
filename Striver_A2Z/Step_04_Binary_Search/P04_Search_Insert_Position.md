# 🔥 Search Insert Position

> **LeetCode #35** · **Difficulty:** Easy · **Step 4 — Binary Search · P04**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **sorted** array of distinct integers and a target `x`, return the index where `x` is found. If it is not present, return the index where it **would be inserted** to keep the array sorted.

**Input:** `arr = [1, 2, 4, 7]`, `x = 6` → **Output:** `3` (inserts between 4 and 7)
**Input:** `arr = [1, 3, 5, 6]`, `x = 5` → **Output:** `2` (already present)
**Input:** `arr = [1, 3, 5, 6]`, `x = 7` → **Output:** `4` (after all elements)

**Key Observation:**
The insert position is exactly the **lower bound** of `x` — the first index with `arr[i] >= x`. If `x` exists, lower bound lands on it; if not, it lands where `x` belongs.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Return the first index whose value is `≥ x`.

```java
class Solution {
    public int searchInsert(int[] arr,int x){
        int n=arr.length;
        for(int i=0;i<n;i++)
            if(arr[i]>=x) return i;
        return n;
    }
}
```

**Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — Binary Search (= Lower Bound)

> 💡 Insert position = lower bound. When `arr[mid] >= x`, `mid` is a candidate → store and go left. When `arr[mid] < x`, go right.

```java
class Solution {
    public int searchInsert(int[] arr,int x){
        int n=arr.length;
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
}
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run
`arr = [1, 2, 4, 7]`, `x = 6`

| low | high | mid | arr[mid] | ≥6? | ans | Action |
|-----|------|-----|----------|-----|-----|--------|
| 0 | 3 | 1 | 2 | ❌ | 4 | low=2 |
| 2 | 3 | 2 | 4 | ❌ | 4 | low=3 |
| 3 | 3 | 3 | 7 | ✅ | 3 | high=2 |
| 3 | 2 | — | — | — | 3 | low>high → **return 3** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Insert position = lower bound of x. `arr[mid]>=x` → `ans=mid, high=mid-1`. Else `low=mid+1`. Default `n`."

---

## 📝 Short Revision Notes

- This problem **is** lower bound (see [P02_Lower_Bound.md](P02_Lower_Bound.md)) — same code, different framing.
- Default `ans=n` handles "insert at the end".
- Assumes distinct elements; with duplicates the lower bound still gives a valid insert index.

---

## ⚠️ Common Mistakes

❌ Using `>` (upper bound) → wrong when `x` is already present.
❌ Returning `-1` when not found — the problem wants an **insert index**, not "not found".
❌ Missing the `ans=n` default → fails when `x` is greater than every element.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "insert position", "where would x go", "first index ≥ x" → **lower bound**.

---

## 🏆 Pattern Category

`Binary Search` · `Lower Bound` · `Insert Position`

---

## ⏱️ 30-Second Last-Minute Revision

> **Insert position = lower bound.** `arr[mid]>=x` → store `ans=mid`, go left; else go right. Default `n`. `O(log N)`.
