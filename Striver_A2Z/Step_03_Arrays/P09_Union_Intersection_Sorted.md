# 🔥 Union and Intersection of Two Sorted Arrays

> **GFG Classic** · **Difficulty:** Easy · **Step 3 — Arrays · P09**

---

## 🧠 Problem Understanding

Given two **sorted** arrays, find their **Union** (all unique elements from both) and **Intersection** (elements common to both).

**Input:** `A=[1,1,2,3,4,5]`, `B=[2,3,4,4,5,6]`  
**Union:** `[1,2,3,4,5,6]`  
**Intersection:** `[2,3,4,5]`

**Key Observation:** Two pointers on sorted arrays — compare heads, advance the smaller (union) or both on match (intersection).

---

## 🥉 Brute Force
Use sets/maps. **Time:** O((M+N) log(M+N)) · **Space:** O(M+N)

---

## 🥇 Optimal — Two Pointers

### Union Algorithm
1. `i=0, j=0`
2. While both valid:
   - If `A[i] < B[j]`: add A[i] if not duplicate, `i++`
   - If `A[i] > B[j]`: add B[j] if not duplicate, `j++`
   - If equal: add once, `i++, j++`
3. Add remaining elements (skip duplicates)

### Intersection Algorithm
1. `i=0, j=0`
2. While both valid:
   - If `A[i] < B[j]`: `i++`
   - If `A[i] > B[j]`: `j++`
   - If equal: add to result, `i++, j++`

### Dry Run — Intersection
`A=[1,2,3,4,5]`, `B=[2,3,4,5,6]`

| i | j | A[i] | B[j] | Action |
|---|---|------|------|--------|
| 0 | 0 | 1 | 2 | 1<2 → i++ |
| 1 | 0 | 2 | 2 | equal → add 2, i++,j++ |
| 2 | 1 | 3 | 3 | equal → add 3, i++,j++ |
| 3 | 2 | 4 | 4 | equal → add 4, i++,j++ |
| 4 | 3 | 5 | 5 | equal → add 5, i++,j++ |
| 5 | 4 | end | 6 | stop |

**Intersection:** `[2,3,4,5]` ✅

### Complexity
- **Time:** O(M+N) · **Space:** O(1) extra (output not counted)

---

## 💻 Clean C++ Code

```cpp
/*
 * UNION & INTERSECTION OF SORTED ARRAYS
 * Two pointers — O(M+N) time, O(1) space
 */
class Solution {
public:
    vector<int> unionSorted(vector<int>& A, vector<int>& B) {
        vector<int> res;
        int i = 0, j = 0;
        while (i < A.size() && j < B.size()) {
            if (A[i] < B[j]) {
                if (res.empty() || res.back() != A[i]) res.push_back(A[i]);
                i++;
            } else if (A[i] > B[j]) {
                if (res.empty() || res.back() != B[j]) res.push_back(B[j]);
                j++;
            } else {
                if (res.empty() || res.back() != A[i]) res.push_back(A[i]);
                i++; j++;
            }
        }
        while (i < A.size()) { if (res.back() != A[i]) res.push_back(A[i]); i++; }
        while (j < B.size()) { if (res.back() != B[j]) res.push_back(B[j]); j++; }
        return res;
    }

    vector<int> intersectionSorted(vector<int>& A, vector<int>& B) {
        vector<int> res;
        int i = 0, j = 0;
        while (i < A.size() && j < B.size()) {
            if (A[i] < B[j])      i++;
            else if (A[i] > B[j]) j++;
            else {                                    // equal
                if (res.empty() || res.back() != A[i])
                    res.push_back(A[i]);              // avoid duplicates
                i++; j++;
            }
        }
        return res;
    }
};
```

---

## 🧾 Recall Line
> "Two pointers on sorted arrays. Union: take smaller, skip dups. Intersection: advance both only on match."

## 📝 Short Revision Notes
- Both O(M+N) time, O(1) extra space
- Handle duplicates within each array: check `res.back() != element` before adding
- For unsorted arrays: use `unordered_set` O(M+N) time/space
- Union size ≤ M+N; Intersection size ≤ min(M,N)

## ⚠️ Common Mistakes
❌ Not handling duplicates within a single array  
❌ Forgetting to process remaining elements after one pointer exhausts  
❌ Using `set` (O(log N) per insert) when O(1) two-pointer is sufficient for sorted input

## 🏆 Pattern Category
`Arrays` · `Two Pointers` · `Sorted Arrays`

## ⏱️ 30-Second Revision
> Two pointers i,j. Union: take min, skip dups, advance. Intersection: skip unequal, record equals. O(M+N)/O(1).
