# 🔥 Count Occurrences in a Sorted Array

> **Striver / GFG** · **Difficulty:** Easy · **Step 4 — Binary Search · P07**

---

## 🧠 Problem Understanding

**What is it asking?**
Count how many times `x` appears in a **sorted** array (with duplicates), in O(log N).

**Input:** `arr = [2, 4, 6, 8, 8, 8, 11, 13]`, `x = 8` → **Output:** `3`
**Input:** `arr = [2, 4, 6, 8, 8, 8, 11, 13]`, `x = 5` → **Output:** `0`

**Key Observation:**
Once you know the **first** and **last** index of `x`, the count is simply:
```
count = last - first + 1
```
This directly reuses [P06_First_and_Last_Position.md](P06_First_and_Last_Position.md).

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Count

```cpp
int count(vector<int>& arr,int n,int x){
    int c=0;
    for(int i=0;i<n;i++)
        if(arr[i]==x) c++;
    return c;
}
```

**Time:** O(N) · **Space:** O(1).

---

### 🥇 Optimal — First & Last via Binary Search

> 💡 `count = (last - first + 1)`. Find first (bias left) and last (bias right) with two binary searches. If first is `-1`, the element is absent → count `0`.

```cpp
class Solution {
public:
    int firstOccurrence(vector<int>& arr,int n,int k){
        int low=0,high=n-1;
        int first=-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]==k){
                first=mid;
                high=mid-1;
            }else if(arr[mid]<k){
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return first;
    }
    int lastOccurrence(vector<int>& arr,int n,int k){
        int low=0,high=n-1;
        int last=-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]==k){
                last=mid;
                low=mid+1;
            }else if(arr[mid]<k){
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return last;
    }
    int count(vector<int>& arr,int n,int x){
        int first=firstOccurrence(arr,n,x);
        if(first==-1) return 0;
        int last=lastOccurrence(arr,n,x);
        return last-first+1;
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run
`arr = [2, 4, 6, 8, 8, 8, 11, 13]`, `x = 8`

- `firstOccurrence` → index **3**
- `lastOccurrence` → index **5**
- `count = 5 - 3 + 1 = 3` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "count = last - first + 1. first/last via biased binary search. Absent (first=-1) → 0."

---

## 📝 Short Revision Notes

- Reduces to P06 (first & last position).
- `count = last - first + 1` — the `+1` is inclusive of both ends.
- Bound view: `count = upperBound(x) - lowerBound(x)`.
- Guard `first == -1` before computing to avoid a wrong count.

---

## ⚠️ Common Mistakes

❌ Forgetting the `+1` in `last - first + 1`.
❌ Not short-circuiting to `0` when the element is absent.
❌ Doing a linear count after already having O(log N) bounds.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "count of x in sorted array", "frequency in log time" → **first & last position, then subtract**.

---

## 🏆 Pattern Category

`Binary Search` · `Lower/Upper Bound` · `Duplicates`

---

## ⏱️ 30-Second Last-Minute Revision

> **count = last - first + 1.** Two biased binary searches (first left-bias, last right-bias). `first == -1` → `0`. `O(log N)`.
