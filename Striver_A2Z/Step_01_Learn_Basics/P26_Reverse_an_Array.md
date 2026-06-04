# 🔥 Reverse an Array

> **LeetCode #344** · **Difficulty:** Easy · **Step 1 — Basic Recursion · P26**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given an array, reverse it **in-place**.

**Input:** Array of integers (1 ≤ n ≤ 10⁵)  
**Output:** Same array, reversed in-place

**Simple Example:**
```
Input:  [1, 2, 3, 4, 5]
Output: [5, 4, 3, 2, 1]

Input:  [1, 2, 3, 4]
Output: [4, 3, 2, 1]
```

---

## 🥉 Brute Force

### Idea
Create a new array, copy elements in reverse order.

### Complexity
- **Time:** O(N) · **Space:** O(N)

```cpp
vector<int> reverse(vector<int>& arr) {
    int n = arr.size();
    vector<int> rev(n);
    for (int i = 0; i < n; i++) rev[i] = arr[n - 1 - i];
    return rev;
}
```

---

## 🥈 Better — Two Pointers (Iterative In-Place)

### Key Observation

> 💡 Swap first and last, then second and second-last, converging toward center.

```
[1, 2, 3, 4, 5]
 ↑           ↑  swap → [5, 2, 3, 4, 1]
    ↑     ↑     swap → [5, 4, 3, 2, 1]
       ↑        middle (odd length), skip
```

### Dry Run

**Input:** `[1, 2, 3, 4, 5]`

| l | r | arr |
|---|---|-----|
| 0 | 4 | [5, 2, 3, 4, 1] |
| 1 | 3 | [5, 4, 3, 2, 1] |
| 2 | 2 | l >= r, stop |

**Output:** `[5, 4, 3, 2, 1]` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

```cpp
void reverseArray(vector<int>& arr) {
    int l = 0, r = arr.size() - 1;
    while (l < r) {
        swap(arr[l], arr[r]);
        l++; r--;
    }
}
```

---

## 🥇 Optimal — Recursive

### Key Observation

> 💡 Reverse(arr, l, r) = swap(arr[l], arr[r]) + Reverse(arr, l+1, r-1)

### Algorithm
1. Base case: if `l >= r`, stop
2. Swap `arr[l]` and `arr[r]`
3. Recurse on `(l+1, r-1)`

### Dry Run

**Input:** `arr = [1,2,3,4,5]`, `l=0, r=4`

```
reverse(0,4): swap(1,5) → [5,2,3,4,1], recurse(1,3)
  reverse(1,3): swap(2,4) → [5,4,3,2,1], recurse(2,2)
    reverse(2,2): l >= r → base case, return
```

**Output:** `[5, 4, 3, 2, 1]` ✅

### Complexity
- **Time:** O(N) · **Space:** O(N/2) = O(N) call stack

### C++ Code
```cpp
/*
 * PROBLEM: Reverse array in-place
 *
 * BRUTE: Extra array O(N) space
 * BETTER: Two pointers iterative O(1) space
 * RECURSIVE: swap outer elements, recurse inward
 *
 * COMPLEXITY: Time O(N) | Space O(1) iterative, O(N) recursive
 */

class Solution {
public:
    // Iterative Two Pointers — preferred
    void reverseIterative(vector<int>& arr) {
        int l = 0, r = arr.size() - 1;
        while (l < r) {
            swap(arr[l++], arr[r--]);
        }
    }

    // Recursive
    void reverseRecursive(vector<int>& arr, int l, int r) {
        if (l >= r) return;                    // base case
        swap(arr[l], arr[r]);                  // swap outer elements
        reverseRecursive(arr, l + 1, r - 1);  // recurse inward
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Two pointers: swap `arr[l]` and `arr[r]`, converge until `l >= r`."

---

## 📝 Short Revision Notes

- Two pointers is optimal: O(N) time, O(1) space
- Recursive: same logic, O(N) stack space — good for learning, not production
- `std::reverse(arr.begin(), arr.end())` in STL does this
- Works for strings too (`reverseString`)
- Even-length: all pairs swapped; odd-length: middle element untouched
- Basis for many harder problems: rotate array, palindrome check

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "reverse in-place"
- "symmetric array check"
- "rotate array"

**I should think of:** Two pointers from both ends converging to center

---

## ⚠️ Common Mistakes

❌ `while (l <= r)` — swaps middle element with itself (harmless but unnecessary)  
❌ Creating new array when in-place is required  
❌ Recursive version: forgetting the `l >= r` base case → infinite recursion  
❌ Off-by-one in index calculation for new array approach  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Two pointers and in-place modification
- **Reasoning:** Space optimization (O(N) → O(1))
- **Recursion:** Understanding the recursive decomposition

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Two pointers (iterative) | O(N) | O(1) | Best — use in interviews |
| Recursive | O(N) | O(N) | Good for demonstrating recursion |
| Extra array | O(N) | O(N) | Only if in-place not required |
| `std::reverse` | O(N) | O(1) | Production code |

---

## 📚 Related Problems

- [ ] LeetCode #344 — Reverse String
- [ ] LeetCode #189 — Rotate Array (uses reversal trick)
- [ ] LeetCode #206 — Reverse Linked List (same concept, different structure)
- [ ] LeetCode #234 — Palindrome Linked List
- [ ] Striver P27 — Check Palindrome String (uses reversal comparison)

---

## 🏆 Pattern Category

`Arrays` · `Two Pointers` · `Recursion`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why:** The two-pointer swap is intuitive. The recursion variant reinforces the mental model from P20–P25.

---

## 📈 Progression Insight

**Harder variant:** Rotate array by K positions → reverse trick: reverse all, reverse [0,k-1], reverse [k,n-1]  
**Even harder:** Reverse words in a string (LeetCode 151)  
**Pattern extension:** This two-pointer pattern appears in: palindrome checking, sorted two-sum, container with most water

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Reverse array in-place  
> **Approach:** Two pointers `l=0, r=n-1`. Swap `arr[l]` and `arr[r]`, then `l++, r--`. Stop when `l >= r`.  
> **Recursive:** `swap(arr[l], arr[r])`, then `f(l+1, r-1)`, base `l >= r`  
> **Time:** O(N) | **Space:** O(1) iterative  
> **Watch out for:** Prefer iterative (O(1) space) over recursive (O(N) stack)
