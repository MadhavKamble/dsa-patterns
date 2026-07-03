# 🔥 Book Allocation Problem (Allocate Minimum Pages)

> **Striver / GFG** · **Difficulty:** Hard · **Step 4 — Binary Search · P22**

---

## 🧠 Problem Understanding

**What is it asking?**
`arr[i]` pages in book `i`, books allocated **contiguously** to `m` students. Each book to exactly one student; each student gets consecutive books. Minimize the **maximum pages** any student reads. Return `-1` if `m > n` (not enough books).

**Input:** `arr = [25, 46, 28, 49, 24]`, `m = 4` → **Output:** `71`

**Key Observation:**
- Search over the **max-pages limit** (a value).
- **Monotonic:** a larger page limit needs **fewer** students. Feasibility (`studentsNeeded ≤ m`) flips once → binary search.
- Search space: `low = max(arr)` (one book can't be split), `high = sum(arr)` (one student reads all).

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Limit

For `limit = max(arr) ... sum(arr)`, count students needed; return the first `limit` needing `≤ m`. **Time:** O(sum · n).

---

### 🥇 Optimal — Binary Search on the Page Limit

> 💡 `countStudents(limit)` greedily gives books to the current student until adding one would exceed `limit`, then starts a new student. If it needs **more** than `m` students, the limit is too small → go right; otherwise go left.

```cpp
class Solution {
public:
    int countStudents(vector<int>& arr,int pages){
        int n=arr.size();
        int students=1;
        long long pagesStudent=0;
        for(int i=0;i<n;i++){
            if(pagesStudent+arr[i]<=pages){
                pagesStudent+=arr[i];
            }else{
                students++;
                pagesStudent=arr[i];
            }
        }
        return students;
    }
    int findPages(vector<int>& arr,int n,int m){
        if(m>n) return -1;
        int low=*max_element(arr.begin(),arr.end());
        int high=accumulate(arr.begin(),arr.end(),0);
        while(low<=high){
            int mid=(low+high)/2;
            int students=countStudents(arr,mid);
            if(students>m){
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return low;
    }
};
```

**Time:** O(n · log(sum(arr))) · **Space:** O(1).

> **Note:** the original snippet was missing `public:` and the class's closing `};` (so `findPages` was private and `main` fell inside the class) — the algorithm is unchanged; only the class wrapper is fixed here.

### Dry Run
`arr = [25, 46, 28, 49, 24]`, `m = 4`, search `[49, 172]`

Converges to the smallest limit needing `≤ 4` students → **71** (allocations: `[25,46] [28] [49] [24]` → max 71).

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on page limit `[max(arr), sum(arr)]`. `countStudents>m` → go right, else left. Return `low`. `m>n` → -1."

---

## 📝 Short Revision Notes

- `low = max(arr)` (a single book must fit), `high = sum(arr)` (one student).
- `students > m` → limit too small → `low = mid+1`; else `high = mid-1`. Answer converges to `low`.
- **Contiguous** allocation is what makes the greedy count valid.
- Identical shape to Split Array Largest Sum & Painter's Partition.

---

## ⚠️ Common Mistakes

❌ `low = 0`/`1` instead of `max(arr)` → allows an impossible limit.
❌ Forgetting the `m > n` impossibility check.
❌ Returning the stored candidate incorrectly — here the answer is `low` after the loop.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "split a contiguous array into m parts minimizing the max part sum" → **binary search on answer + greedy partition count**.

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Minimize Maximum` · `Greedy Partition`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS limit `[max(arr), sum(arr)]`.** Greedy `countStudents`; `>m` → right, else left. Return `low`. `m>n` → -1. `O(n·log sum)`.
