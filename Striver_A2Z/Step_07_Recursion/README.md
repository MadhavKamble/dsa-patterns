# Step 7 — Recursion

> Striver A2Z DSA Course · Step 7 · 15 Problems

---

## Part 1 — Get a Hold of Recursion (P01–P06)

| # | Problem | Difficulty | LeetCode | Status |
|---|---------|------------|----------|--------|
| P01 | Understanding Recursion (Print 1→N, N→1, Name N times) | Easy | — | ☐ |
| P02 | Sum of First N Natural Numbers | Easy | — | ☐ |
| P03 | Factorial of N | Easy | — | ☐ |
| P04 | Reverse an Array | Easy | LC 344 | ☐ |
| P05 | Check if String is Palindrome | Easy | LC 125 / 234 | ☐ |
| P06 | Fibonacci Number | Easy | LC 509 | ☐ |

---

## Part 2 — Subsequences Pattern (P07–P15)

| # | Problem | Difficulty | LeetCode | Status |
|---|---------|------------|----------|--------|
| P07 | Generate All Subsequences / Power Set | Medium | LC 78 | ☐ |
| P08 | Print All Subsequences with Sum K | Medium | — | ☐ |
| P09 | Count Subsequences with Sum K | Medium | — | ☐ |
| P10 | Combination Sum I (unbounded reuse) | Medium | LC 39 | ☐ |
| P11 | Combination Sum II (each element once) | Medium | LC 40 | ☐ |
| P12 | Subset Sum I (sorted list of sums) | Medium | — | ☐ |
| P13 | Subset Sum II (unique subsets) | Medium | LC 90 | ☐ |
| P14 | Permutations — Approach 1 (visited array) | Medium | LC 46 | ☐ |
| P15 | Permutations — Approach 2 (swap) | Medium | LC 46 | ☐ |

---

## Core Recursion Mental Model

```
f(n)
├── base case  →  return directly
└── recursive case  →  f(n-1), then combine/do-something
```

**Stack trace insight:** Every call pushes a frame. When base case hits, frames pop in reverse — that's how "return phase" works.

**Parameterized vs Functional recursion:**
- **Parameterized:** carry state (index, accumulator) as arguments, `void` return, print at base
- **Functional:** return a value, combine results on the way back up

---

## Subsequences Pattern Blueprint

```cpp
void generate(int idx, vector<int>& arr, vector<int>& curr, int target) {
    if (idx == arr.size()) {
        if (/* condition on curr/target */) process(curr);
        return;
    }
    // Pick
    curr.push_back(arr[idx]);
    generate(idx+1, arr, curr, target - arr[idx]);
    curr.pop_back();
    // Not pick
    generate(idx+1, arr, curr, target);
}
```

---

## Files

| File | Problem |
|------|---------|
| [P01_Understanding_Recursion.md](P01_Understanding_Recursion.md) | Print 1→N, N→1, Name N times |
| [P02_Sum_of_N_Numbers.md](P02_Sum_of_N_Numbers.md) | Sum of first N |
| [P03_Factorial.md](P03_Factorial.md) | Factorial of N |
| [P04_Reverse_Array.md](P04_Reverse_Array.md) | Reverse an array |
| [P05_Palindrome_Check.md](P05_Palindrome_Check.md) | Palindrome string |
| [P06_Fibonacci.md](P06_Fibonacci.md) | Fibonacci number |
| [P07_Generate_Subsequences.md](P07_Generate_Subsequences.md) | Power Set / all subsequences |
| [P08_Subsequences_Sum_K_Print.md](P08_Subsequences_Sum_K_Print.md) | Print all with sum K |
| [P09_Subsequences_Sum_K_Count.md](P09_Subsequences_Sum_K_Count.md) | Count with sum K |
| [P10_Combination_Sum_I.md](P10_Combination_Sum_I.md) | LC 39 |
| [P11_Combination_Sum_II.md](P11_Combination_Sum_II.md) | LC 40 |
| [P12_Subset_Sum_I.md](P12_Subset_Sum_I.md) | Sorted list of subset sums |
| [P13_Subset_Sum_II.md](P13_Subset_Sum_II.md) | LC 90 |
| [P14_Permutations_Visited.md](P14_Permutations_Visited.md) | LC 46 — visited array |
| [P15_Permutations_Swap.md](P15_Permutations_Swap.md) | LC 46 — swap |
