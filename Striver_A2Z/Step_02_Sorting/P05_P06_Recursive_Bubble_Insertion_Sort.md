# 🔥 Recursive Bubble Sort & Recursive Insertion Sort

> **Step 2 — Sorting Techniques · P05 & P06**  
> These are the **recursive implementations** of Bubble and Insertion Sort —  
> same algorithms, different control flow. Goal: build recursion intuition.

---

## 🧠 Why Recursive Versions?

These problems teach you to convert iterative loops into recursive calls — a skill needed for:
- Writing recursive backtracking solutions
- Understanding tail recursion
- Interview questions that say "implement X without loops"

**Key translation:**
```
for (int i = 0; i < N; i++) { ... }
         ↓ becomes
void f(int i, int N) {
    if (i == N) return;   // base case replaces loop termination
    ...                   // loop body
    f(i + 1, N);          // recursive call replaces i++
}
```

---

# Part 1 — Recursive Bubble Sort (P05)

## 🥇 Algorithm

### Key Observation

> 💡 One full pass of Bubble Sort bubbles the largest element to the end.  
> After that, the problem reduces to: sort `arr[0..N-2]`.  
> This is the recursive structure.

**`bubbleSortRecursive(arr, n)`:**
1. Base case: if `n == 1`, return (single element is sorted)
2. Do one full pass: for `j` from 0 to `n-2`, swap adjacent if out of order
3. Recurse: `bubbleSortRecursive(arr, n-1)`

With optimization — pass `swapped` flag up:
- If no swap in pass → array sorted → stop recursion early

### Dry Run

**Input:** `[3, 1, 2]`, n=3

```
Call f(arr, 3):
  Pass: j=0: arr[0]=3>arr[1]=1 → swap → [1,3,2]
        j=1: arr[1]=3>arr[2]=2 → swap → [1,2,3]
        swapped=true
  Recurse f(arr, 2):
    Pass: j=0: arr[0]=1 < arr[1]=2 → no swap
          swapped=false → return early (already sorted)
```

**Output:** `[1, 2, 3]` ✅

### Complexity
- **Time:** O(N²) worst · O(N) best (sorted, with early exit)
- **Space:** O(N) call stack (N recursive calls)

### C++ Code

```cpp
/*
 * RECURSIVE BUBBLE SORT
 *
 * BASE CASE: n == 1 (single element is sorted)
 * RECURSIVE CASE: one pass → largest goes to end → recurse on n-1
 *
 * COMPLEXITY: Time O(N²) | Space O(N) call stack
 */

void bubbleSortRecursive(vector<int>& arr, int n) {
    if (n == 1) return;                  // base case: 1 element, already sorted

    bool swapped = false;

    // one pass: bubble largest to arr[n-1]
    for (int j = 0; j < n - 1; j++) {
        if (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
            swapped = true;
        }
    }

    if (!swapped) return;                // early exit: already sorted

    bubbleSortRecursive(arr, n - 1);     // recurse on smaller problem
}

// Call: bubbleSortRecursive(arr, arr.size());
```

---

# Part 2 — Recursive Insertion Sort (P06)

## 🥇 Algorithm

### Key Observation

> 💡 Insertion Sort inserts `arr[i]` into the sorted prefix `arr[0..i-1]`.  
> If `arr[0..i-1]` is sorted, inserting one more element = sorted `arr[0..i]`.  
> This is the recursive structure.

**`insertionSortRecursive(arr, i, n)`:**
1. Base case: if `i == n`, return (processed all elements)
2. Insert `arr[i]` into its correct position in `arr[0..i-1]`
3. Recurse: `insertionSortRecursive(arr, i+1, n)`

**Helper — insert one element:**
- `key = arr[i]`, `j = i-1`
- While `j >= 0` and `arr[j] > key`: shift right
- Place key

### Dry Run

**Input:** `[4, 2, 1, 3]`

```
Call f(arr, 1):  insert arr[1]=2 into [4] → [2,4,1,3]
Call f(arr, 2):  insert arr[2]=1 into [2,4] → [1,2,4,3]
Call f(arr, 3):  insert arr[3]=3 into [1,2,4] → [1,2,3,4]
Call f(arr, 4):  i==n → return
```

**Output:** `[1, 2, 3, 4]` ✅

### Complexity
- **Time:** O(N²) worst · O(N) best (sorted input)
- **Space:** O(N) call stack

### C++ Code

```cpp
/*
 * RECURSIVE INSERTION SORT
 *
 * BASE CASE: i == n (processed all elements)
 * RECURSIVE CASE: sort first i elements, then insert arr[i]
 *
 * COMPLEXITY: Time O(N²) | Space O(N) call stack
 */

void insertElement(vector<int>& arr, int i) {
    if (i <= 0 || arr[i - 1] <= arr[i]) return;  // already in position
    swap(arr[i - 1], arr[i]);                      // swap to move left
    insertElement(arr, i - 1);                     // keep moving left if needed
}

void insertionSortRecursive(vector<int>& arr, int i, int n) {
    if (i == n) return;                            // base case

    insertElement(arr, i);                         // insert arr[i] into sorted prefix
    insertionSortRecursive(arr, i + 1, n);         // recurse for next element
}

// Call: insertionSortRecursive(arr, 1, arr.size());
```

---

## 🎤 Interview Explanation Script

> "Recursive Bubble Sort: one call = one pass that bubbles the largest to the end, then we recurse on n-1 elements. Base case is n=1."

> "Recursive Insertion Sort: one call handles inserting the i-th element into the sorted prefix, then recurses for i+1. Base case is i==n."

> "Both have the same time complexity as their iterative versions — O(N²) — but now use O(N) stack space instead of O(1). In interviews, this shows you understand how to convert iterative to recursive and vice versa."

---

## 📝 Short Revision Notes

**Recursive Bubble:**
- `f(arr, n)`: one pass (bubble max to end), recurse `f(arr, n-1)`
- Base: `n == 1`; Optimization: early exit if no swaps

**Recursive Insertion:**
- `f(arr, i, n)`: insert `arr[i]` into `arr[0..i-1]`, recurse `f(arr, i+1, n)`
- Base: `i == n`
- Helper: shift left using recursion or a loop

**Both:** O(N²) time, O(N) stack space (worse than iterative O(1) space)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "implement sort recursively"
- "convert iterative algorithm to recursive"
- "sort without explicit for/while loop"

**I should think of:** Replace loop with recursive call; loop body → recursive case; loop termination → base case

---

## ⚠️ Common Mistakes

❌ Recursive Bubble: outer loop variable `n` doesn't change in body — must pass `n-1` to recursive call  
❌ Recursive Insertion: forgetting to handle the insertion recursively (the inner while loop also needs a base case)  
❌ Both: forgetting the base case → infinite recursion  
❌ Claiming these are more efficient than iterative — they're actually worse (extra O(N) stack space)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Iterative ↔ recursive equivalence
- **Reasoning:** Can you identify the recursive substructure in an iterative algorithm?
- **Awareness:** Understanding the space cost of recursion vs. iteration

---

## 📚 Related Problems

- [ ] Striver Step 2 P02 — Bubble Sort (iterative)
- [ ] Striver Step 2 P03 — Insertion Sort (iterative)
- [ ] Striver Step 1 P26 — Reverse Array (recursive two-pointer pattern)

---

## 🏆 Pattern Category

`Sorting` · `Recursion` · `In-Place`

---

## ⏱️ 30-Second Last-Minute Revision

> **Recursive Bubble:** `f(n)`: one pass (bubble max) → recurse `f(n-1)`. Base: n==1.  
> **Recursive Insertion:** `f(i)`: insert arr[i] into sorted prefix → recurse `f(i+1)`. Base: i==n.  
> **Both:** O(N²) time, O(N) stack. Worse than iterative (O(1) space). Purpose: recursion practice.
