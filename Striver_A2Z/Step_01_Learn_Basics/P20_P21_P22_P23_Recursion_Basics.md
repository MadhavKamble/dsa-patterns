# 🔥 Recursion Basics (P20–P23)

> **Step 1 — Basic Recursion · P20/P21/P22/P23**  
> These four problems are designed to **build the mental model of recursion** — not to solve LeetCode-hard problems.

---

## 🧠 What Is Recursion?

A function that calls itself with a **smaller subproblem** until it hits a **base case**.

**Every recursive function needs:**
1. **Base case** — when to stop
2. **Recursive case** — reduce problem size, call self

**Call stack visualization:**
```
f(3)
  └─ f(2)
       └─ f(1)
            └─ f(0) ← base case, return
```

**Space cost:** Every call sits on the stack. N recursive calls = O(N) stack space.

---

## P20 — Understand Recursion: Print Something N Times

### Problem
Print "Hello" exactly N times using recursion. **No loops allowed.**

### Key Insight
"Do this N times" = "do it once, then do it N-1 more times."

### Algorithm
```
print(N):
  if N == 0: return      ← base case
  print("Hello")          ← do work
  print(N - 1)            ← recurse with smaller problem
```

### Dry Run (N = 3)
```
print(3) → prints "Hello", calls print(2)
  print(2) → prints "Hello", calls print(1)
    print(1) → prints "Hello", calls print(0)
      print(0) → base case, returns
```
Output: Hello Hello Hello ✅

### C++ Code
```cpp
/*
 * RECURSION MODEL: Print N times
 * Base case: N == 0, stop
 * Recursive case: print once, recurse with N-1
 * Time O(N) | Space O(N) call stack
 */
void printNTimes(int n) {
    if (n == 0) return;          // base case
    cout << "Hello\n";           // do work
    printNTimes(n - 1);          // recurse
}
```

### Complexity
- **Time:** O(N) — N function calls
- **Space:** O(N) — N frames on call stack

---

## P21 — Print Name N Times Using Recursion

### Problem
Print your name exactly N times using recursion.

### Key Insight
Identical to P20 — the "work" is just printing a name instead.  
**Purpose:** Reinforce that recursion = base case + reduce + recurse.

### C++ Code
```cpp
void printName(int n, string name) {
    if (n == 0) return;          // base case
    cout << name << "\n";
    printName(n - 1, name);      // recurse
}
```

---

## P22 — Print 1 to N Using Recursion

### Problem
Print numbers 1 through N in ascending order using recursion.

### Two Approaches

**Approach 1: Recurse first, print after (backtracking)**
```
print1ToN(N):
  if N == 0: return
  print1ToN(N - 1)     ← go deep first
  print(N)             ← print on the way BACK UP
```
Dry run (N=3): goes 3→2→1→0(base)→prints 1→prints 2→prints 3 ✅

**Approach 2: Track current position**
```
print1ToN(i, N):
  if i > N: return
  print(i)             ← print on way DOWN
  print1ToN(i+1, N)   ← recurse
```

### C++ Code
```cpp
// Approach 1: Backtracking style (recurse first)
void print1ToN_v1(int n) {
    if (n == 0) return;
    print1ToN_v1(n - 1);    // recurse FIRST (go to bottom)
    cout << n << " ";        // print on the way BACK UP
}

// Approach 2: Forward tracking (print on way down)
void print1ToN_v2(int i, int n) {
    if (i > n) return;
    cout << i << " ";        // print NOW
    print1ToN_v2(i + 1, n); // recurse with next
}
// Call: print1ToN_v2(1, N);
```

### Dry Run (Approach 1, N=4)
```
Calls:   f(4) → f(3) → f(2) → f(1) → f(0)[base]
Prints:  ← 1 ← 2 ← 3 ← 4    (printed on the way back)
Output:  1 2 3 4
```

---

## P23 — Print N to 1 Using Recursion

### Problem
Print numbers N down to 1 using recursion.

### Two Approaches

**Approach 1: Print on way DOWN (natural)**
```
printNTo1(N):
  if N == 0: return
  print(N)             ← print first
  printNTo1(N - 1)     ← then recurse
```

**Approach 2: Backtrack — recurse first, print after (opposite of P22)**

### C++ Code
```cpp
// Approach 1: Print on way down
void printNTo1_v1(int n) {
    if (n == 0) return;
    cout << n << " ";       // print first
    printNTo1_v1(n - 1);   // then recurse
}

// Approach 2: Using backtracking
void printNTo1_v2(int i, int n) {
    if (i < 1) return;
    cout << i << " ";
    printNTo1_v2(i - 1, n);
}
```

---

## 🔑 The Core Recursion Mental Model

```
┌─────────────────────────────────────────────┐
│  Print on way DOWN  │  Print on way UP       │
│  (before recursion) │  (after recursion)     │
├─────────────────────┼────────────────────────┤
│  N to 1             │  1 to N                │
│  Pre-order tree     │  Post-order tree       │
│  Natural countdown  │  Backtracking pattern  │
└─────────────────────┴────────────────────────┘
```

---

## 🎤 Interview Explanation Script

> "Recursion breaks a problem into: a base case (stop condition) and a recursive case (reduce and call self)."

> "Printing before the recursive call processes things top-down (N to 1). Printing after the recursive call processes bottom-up (1 to N) — this is the backtracking pattern."

> "Every recursive call uses O(1) stack space, and with N calls, total space is O(N). This is the hidden cost of recursion."

---

## ⚠️ Common Mistakes

❌ No base case → infinite recursion → stack overflow  
❌ Base case doesn't actually terminate → `if n == 0 return` but calling `f(n)` not `f(n-1)`  
❌ Confusing "print before recurse" vs "print after recurse" ordering  
❌ Forgetting O(N) space cost of recursive calls  

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "do X n times without a loop"
- "process array/string recursively"
- "print in order / reverse order"

**I should think of:** Recursion with pre/post call positioning

---

## 📝 Short Revision Notes

- Recursion = base case + recursive case
- Print before recursion → top-down order (N→1)
- Print after recursion → bottom-up order (1→N) via backtracking
- Time O(N), Space O(N) call stack for all these
- P20/P21 = same pattern, P22 = backtrack variant, P23 = direct variant

---

## ⏱️ 30-Second Last-Minute Revision

> **P20/P21:** `if(n==0) return; print(); f(n-1);`  
> **P22 (1 to N):** Recurse first, then print — or use `f(i+1,N)` printing i first  
> **P23 (N to 1):** Print first, then recurse  
> **Key:** Print BEFORE call = top-down; print AFTER call = bottom-up  
> **Space:** Always O(N) call stack
