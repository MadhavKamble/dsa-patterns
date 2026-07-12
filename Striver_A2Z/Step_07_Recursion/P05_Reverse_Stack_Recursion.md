# Reverse a Stack using Recursion

> **GFG / Striver** · **Difficulty:** Medium · **Step 7 — Recursion · P05**

---

## 🧠 Problem Understanding

**What is it asking?**
Reverse a stack using recursion only — no loops for the reversal, no extra data structures.

**Input:** `[4,1,3,2]` (top=2) → **Output:** `[2,3,1,4]` (top=4)

**Key Observations:**
- Reversing a stack = what was on top (2) must go to the bottom, and the bottom (4) must come to the top.
- Two mutually recursive functions: `reverseStack` (peels elements off the top) + `insertAtBottom` (pushes an element past everything currently in the stack to the very bottom).
- Same structure as sorting — but instead of inserting in sorted order, we always insert at the bottom.

---

## 🥉 Brute Force — Auxiliary Vector

```cpp
void reverseStack(stack<int>& st){
    vector<int> v;
    while(!st.empty()){ v.push_back(st.top()); st.pop(); }
    for(int x:v) st.push(x);
}
```

**Time:** O(N) · **Space:** O(N) — violates "no extra DS" constraint.

---

## 🥇 Recursive Approach

### Key Insight

> 💡 `reverseStack`: pop top, reverse the rest, then insert the popped element at the **bottom** (instead of restoring at top). `insertAtBottom`: recursively empty the stack, push the new value, then restore all elements — making it end up at the bottom.

### The Two-Function Pattern

```
reverseStack(st):
  if st is empty → return           ← base case
  topVal = pop top
  reverseStack(st)                  ← reverse the rest
  insertAtBottom(st, topVal)        ← put topVal at the very bottom

insertAtBottom(st, val):
  if st is empty → push val         ← base case: stack empty → val goes here (bottom)
  topVal = pop top
  insertAtBottom(st, val)           ← go deeper until empty
  push topVal back                  ← restore: topVal ends up above val
```

### Why Does This Work?

- After `reverseStack(rest)`, the sub-stack is already reversed.
- `insertAtBottom(topVal)` pushes `topVal` below everything in the reversed sub-stack.
- Net effect: the original top element ends up at the bottom of the final stack.

### Algorithm

**insertAtBottom(st, val):**
1. Base: `st.empty()` → `st.push(val); return`.
2. `topVal = st.top(); st.pop()`.
3. `insertAtBottom(st, val)` — recurse until empty.
4. `st.push(topVal)` — restore topVal above val.

**reverseStack(st):**
1. Base: `st.empty()` → return.
2. `topVal = st.top(); st.pop()`.
3. `reverseStack(st)` — reverse remaining.
4. `insertAtBottom(st, topVal)` — place topVal at bottom.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

void insertAtBottom(stack<int>& st,int val){
    if(st.empty()){
        st.push(val);
        return;
    }
    int topVal=st.top();
    st.pop();
    insertAtBottom(st,val);
    st.push(topVal);
}

void reverseStack(stack<int>& st){
    if(st.empty()) return;
    int topVal=st.top();
    st.pop();
    reverseStack(st);
    insertAtBottom(st,topVal);
}

int main(){
    stack<int> st;
    st.push(4); st.push(1); st.push(3); st.push(2);
    reverseStack(st);
    cout<<"Reversed Stack: ";
    while(!st.empty()){ cout<<st.top()<<" "; st.pop(); }
    cout<<endl;
    return 0;
}
```

**Time:** O(N²) · **Space:** O(N) — call stack depth up to N

### Dry Run — `stack: [4,1,3,2]` (top=2)

**Peeling phase** (reverseStack calls):
```
reverseStack([4,1,3,2]) → peel 2 → reverseStack([4,1,3])
  reverseStack([4,1,3]) → peel 3 → reverseStack([4,1])
    reverseStack([4,1]) → peel 1 → reverseStack([4])
      reverseStack([4]) → peel 4 → reverseStack([])
        reverseStack([]) → return (base)
      insertAtBottom([], 4) → empty → push 4 → [4]
    insertAtBottom([4], 1) → pop 4, empty → push 1, push 4 → [1,4]
  insertAtBottom([1,4], 3) → pop 4, pop 1, empty → push 3, push 1, push 4 → [3,1,4]
insertAtBottom([3,1,4], 2) → pop 4, pop 1, pop 3, empty → push 2, push 3, push 1, push 4
                           → [2,3,1,4]
```

Final stack (top→bottom): 4,1,3,2 → prints `4 1 3 2` ✓ (original was 2,3,1,4 top→bottom)

---

## 🔁 Comparison: Sort Stack vs Reverse Stack

| | sortStack | reverseStack |
|---|---|---|
| Helper | `insert` (sorted position) | `insertAtBottom` (always bottom) |
| insert condition | `s.empty() \|\| top ≤ temp` | `st.empty()` only |
| Result | sorted, largest on top | fully reversed |
| Time | O(N²) | O(N²) |

Both follow the same **peel → recurse → reinsert** skeleton. Only the helper differs.

---

## 🧾 Recall Line *(10-Second Revision)*

> "reverseStack = peel top → reverse rest → insertAtBottom. insertAtBottom = pop everything, push val, restore all. Both O(N²). Mirror of sortStack but helper inserts at bottom not sorted position."

---

## 📝 Short Revision Notes

- `insertAtBottom` empties the entire stack recursively before pushing `val`, then restores everything — effectively tunneling to the bottom.
- If you forget `st.push(topVal)` after the recursive call in `insertAtBottom`, elements vanish.
- The call stack itself acts as the auxiliary storage — no explicit array/vector needed.

---

## ⚠️ Common Mistakes

❌ Forgetting `st.push(topVal)` in `insertAtBottom` after recursion — removes elements.
❌ Swapping the order: calling `insertAtBottom` before `reverseStack` in `reverseStack` — puts element at bottom before sub-stack is reversed.
❌ Missing base case check in `reverseStack` — infinite recursion on empty stack.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "reverse stack / insert at bottom using only recursion" → **peel-recurse-reinsert at bottom**: two functions, `reverseStack` peels and `insertAtBottom` tunnels to the bottom.

---

## 🏆 Pattern Category

`Recursion` · `Stack` · `Two-Function Recursive Pattern`

---

## ⏱️ 30-Second Last-Minute Revision

> Two functions: `reverseStack` (peel top, reverse rest, insertAtBottom) + `insertAtBottom` (pop all, push val, restore all). Both O(N²) time. The call stack replaces the auxiliary array. Mirror of sort stack.
