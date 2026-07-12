# Sort a Stack using Recursion

> **GFG / Striver** · **Difficulty:** Medium · **Step 7 — Recursion · P04**

---

## 🧠 Problem Understanding

**What is it asking?**
Sort a stack such that the smallest element is at the top, using recursion only — no loops allowed for the sorting logic, no extra data structures.

**Input:** `[4, 1, 3, 2]` (top = 2) → **Output:** `[1, 2, 3, 4]` (top = 4)

**Key Observations:**
- We can only access the top of a stack.
- Two mutually recursive functions needed: one to sort, one to insert in the correct sorted position.
- **sortStack**: peel off the top, sort the rest recursively, then insert the peeled element back in sorted order.
- **insert**: place an element so that all elements below it are smaller (largest at top).

---

## 🥉 Brute Force — Auxiliary Array

```cpp
void sortStack(stack<int>& s){
    vector<int> v;
    while(!s.empty()){ v.push_back(s.top()); s.pop(); }
    sort(v.begin(),v.end());
    for(int x:v) s.push(x);
}
```

**Time:** O(N log N) · **Space:** O(N) — uses extra array. Violates "no extra DS" constraint.

---

## 🥇 Recursive Approach

### Key Insight

> 💡 Think of `sortStack` as: "pop top → sort rest → insert top back in its correct position." The `insert` function is itself recursive: if top ≤ temp, push; otherwise pop top, recurse deeper, push top back.

### The Two-Function Pattern

```
sortStack(s):
  if s is empty → return          ← base case
  temp = pop top
  sortStack(s)                    ← sort the remaining stack
  insert(s, temp)                 ← place temp in correct position

insert(s, temp):
  if s is empty OR top ≤ temp → push temp and return   ← base case
  val = pop top
  insert(s, temp)                 ← go deeper
  push val back                   ← restore
```

### Why Does This Work?

- After `sortStack(s)` returns, the remaining stack is already sorted (largest on top).
- `insert(s, temp)` walks down past all elements larger than `temp`, places `temp`, then restores those elements on top — maintaining sorted order.

### Algorithm

**sortStack(s):**
1. Base: if `s.empty()` → return.
2. `temp = s.top(); s.pop()`.
3. `sortStack(s)` — sort the rest.
4. `insert(s, temp)` — place temp in sorted position.

**insert(s, temp):**
1. Base: if `s.empty()` OR `s.top() <= temp` → `s.push(temp); return`.
2. `val = s.top(); s.pop()`.
3. `insert(s, temp)` — recurse deeper.
4. `s.push(val)` — restore val on top.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

void insert(stack<int>& s,int temp){
    if(s.empty() || s.top()<=temp){
        s.push(temp);
        return;
    }
    int val=s.top();
    s.pop();
    insert(s,temp);
    s.push(val);
}

void sortStack(stack<int>& s){
    if(!s.empty()){
        int temp=s.top();
        s.pop();
        sortStack(s);
        insert(s,temp);
    }
}

int main(){
    stack<int> s;
    s.push(4); s.push(1); s.push(3); s.push(2);
    sortStack(s);
    while(!s.empty()){ cout<<s.top()<<" "; s.pop(); }
    return 0;
}
```

**Time:** O(N²) · **Space:** O(N) — call stack depth up to N

### Dry Run — `stack: [4,1,3,2]` (top=2)

**sortStack calls** (peeling off tops):
```
sortStack([4,1,3,2]) → peel 2 → sortStack([4,1,3])
  sortStack([4,1,3]) → peel 3 → sortStack([4,1])
    sortStack([4,1]) → peel 1 → sortStack([4])
      sortStack([4]) → peel 4 → sortStack([])
        sortStack([]) → return
      insert([], 4) → empty → push 4 → [4]
    insert([4], 1) → top=4 > 1 → pop 4, insert([],1) → push 1, push 4 → [1,4]
  insert([1,4], 3) → top=4>3 → pop 4, insert([1],3) → top=1≤3 → push 3, push 4 → [1,3,4]
insert([1,3,4], 2) → top=4>2 → pop 4, top=3>2 → pop 3, top=1≤2 → push 2, push 3, push 4 → [1,2,3,4]
```

Final stack (top→bottom): 4,3,2,1 → prints `4 3 2 1` ✓

---

## 🧾 Recall Line *(10-Second Revision)*

> "sortStack = peel top → sort rest → insert back. insert = if empty/top≤temp push; else pop top, recurse, restore. Two mutually recursive functions, O(N²)."

---

## 📝 Short Revision Notes

- `insert` condition `s.top() <= temp`: push temp here (temp will be above this smaller element), maintaining largest-on-top order.
- Largest ends up at top because we always insert temp above everything ≤ temp.
- This is the same pattern as **Insertion Sort** — sort N-1 elements, insert the Nth in position.
- Stack sort by recursion = insertion sort on a stack.

---

## ⚠️ Common Mistakes

❌ Using `s.top() < temp` (strict `<`) instead of `<=` — fails when equal elements exist.
❌ Forgetting to `s.push(val)` after the recursive `insert` call — leaves elements missing.
❌ Confusing the base case order in `insert` — check `s.empty()` before `s.top()` or it crashes.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "sort/insert into stack with only recursion" → **peel-sort-reinsert**: pop all elements with sortStack, reinsert each with a recursive insert that restores larger elements.

---

## 🏆 Pattern Category

`Recursion` · `Stack` · `Insertion Sort Analogy`

---

## ⏱️ 30-Second Last-Minute Revision

> Two functions: `sortStack` (peel top, sort rest, insert) + `insert` (pop elements > temp, push temp, restore). Condition: `s.empty() || s.top() <= temp` → push. **Time:** O(N²) | **Space:** O(N) stack.
