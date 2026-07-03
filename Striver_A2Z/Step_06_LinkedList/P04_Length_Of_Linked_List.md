# 🔥 Find the Length of a Linked List

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P04**

---

## 🧠 Problem Understanding

**What is it asking?**
Given the `head` of a singly linked list, count how many nodes it contains.

**Key Observation:**
Unlike an array (`arr.size()` is O(1)), a linked list has **no stored size** — you must walk it node by node until you hit `nullptr`. That's **O(N)**.

**Simple Example:**
```
10 -> 20 -> 30   →   length = 3
(empty list)      →   length = 0
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Count While Traversing

> 💡 Fixed `head`, moving `temp`. Increment a counter for every node until `temp` falls off the end (`nullptr`).

```cpp
class Solution {
public:
    int lengthOfLinkedList(Node* head){
        int count=0;
        Node* temp=head;
        while(temp!=nullptr){
            count++;
            temp=temp->next;
        }
        return count;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Why it works
- `temp` starts at `head` and advances via `temp=temp->next`; each iteration counts exactly one node.
- Empty list (`head==nullptr`): loop body never runs → returns `0`. No special case needed.
- Never move `head` itself — you'd lose the list.

### Dry Run
`10 -> 20 -> 30`:

| temp | count |
|------|-------|
| node(10) | 1 |
| node(20) | 2 |
| node(30) | 3 |
| nullptr | stop → return 3 |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Walk `temp` from head to nullptr, `count++` each step. O(N), empty list → 0 free."

---

## 📝 Short Revision Notes

- No stored size → must traverse → **O(N)**.
- Empty-list case handled automatically by the `while` guard.
- Same traversal skeleton as print/search — memorize `while(temp!=nullptr) temp=temp->next`.

---

## ⚠️ Common Mistakes

❌ Moving `head` instead of a separate `temp`.
❌ Off-by-one: counting *before* the null check, or starting `count=1`.
❌ Loop condition `temp->next != nullptr` → undercounts by 1 (misses the last node).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "count nodes", "how long is the list", need list size for a middle/kth operation → **counter + full traversal**.

---

## 🏆 Pattern Category

`Linked List` · `Traversal` · `Counting`

---

## ⏱️ 30-Second Last-Minute Revision

> **Length = O(N).** `temp=head`, `while(temp) { count++; temp=temp->next; }`, return count. Empty list → 0.
