# 🔥 Reverse a Doubly Linked List

> **Concept Problem** · **Difficulty:** Medium · **Step 6 — Linked List · P09**

---

## 🧠 Problem Understanding

**What is it asking?**
Reverse a DLL **in place** so the tail becomes the head and every arrow flips direction. Return the new head.

**Key Observation:**
In a DLL, reversing = **swapping `next` and `back` of every node**. After swapping, what was `next` becomes `back` and vice-versa — the whole list is reversed without moving any data. The old tail (whose `next` was `nullptr`) ends up with `back == nullptr`, i.e. it's the new head.

**Simple Example:**
```
Before:  10 ⇄ 20 ⇄ 30 ⇄ 40
After:   40 ⇄ 30 ⇄ 20 ⇄ 10
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Swap next/back of Every Node

> 💡 Walk the list. For each node, swap its `next` and `back`. Crucially, **save the original `next` first** (into `temp`) because you're about to overwrite it — that saved pointer is how you keep moving forward through the *original* order.

```cpp
Node* reverseDLL(Node* head){
    if(head==nullptr||head->next==nullptr) return head;
    Node* curr=head;
    while(curr!=nullptr){
        Node* temp=curr->next;
        curr->next=curr->back;
        curr->back=temp;
        head=curr;
        curr=temp;
    }
    return head;
}
```

**Time:** O(N) · **Space:** O(1).

### Why it works
- `temp = curr->next` saves the original forward link **before** it's clobbered.
- `curr->next = curr->back; curr->back = temp;` swaps the two pointers of the current node.
- `head = curr;` — on the **last** iteration, `curr` is the original tail, which is the final answer. Updating `head` each step means it holds the last node processed = new head.
- `curr = temp;` advances along the **original** order (using the saved pointer).
- Loop ends when `curr == nullptr` (we've walked off the original tail).

### Dry Run
`10 ⇄ 20 ⇄ 30 ⇄ 40`:

| curr | temp (orig next) | after swap | head | next curr |
|------|------------------|-----------|------|-----------|
| 10 | 20 | 10: next=null, back=20 | 10 | 20 |
| 20 | 30 | 20: next=10, back=30 | 20 | 30 |
| 30 | 40 | 30: next=20, back=40 | 30 | 40 |
| 40 | null | 40: next=30, back=null | **40** | null → stop |

**Result:** head = `40 ⇄ 30 ⇄ 20 ⇄ 10` ✅

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Idea |
|----------|------|-------|------|
| **Swap next/back (optimal)** | O(N) | O(1) | Flip each node's two pointers in one pass |
| **Stack of values** | O(N) | O(N) | Push all data to a stack, pop back into nodes front→back |

The stack version only reverses **data**, not links — simpler to reason about but O(N) space. The pointer-swap is the expected answer.

---

## 🧾 Recall Line *(10-Second Revision)*

> "For each node: save `next` in temp, swap `next`↔`back`, advance via temp. Last node processed = new head. O(N), O(1)."

---

## 📝 Short Revision Notes

- Reverse DLL = **swap `next` and `back`** of every node.
- Must **save `curr->next` before** overwriting it.
- Advance using the saved `temp` (original order), not the swapped pointer.
- New head = the node processed last (original tail).
- Base case: empty or single node → return head unchanged.

---

## ⚠️ Common Mistakes

❌ Swapping without saving `curr->next` first → you lose the rest of the list.
❌ Advancing with `curr = curr->next` **after** the swap → moves backward / infinite loop.
❌ Forgetting to update/return the new head → returns the old (now tail) head.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "reverse a doubly linked list", "flip direction of a bidirectional list" → **swap next/back per node**, track new head.

---

## 🏆 Pattern Category

`Linked List` · `Doubly Linked List` · `Reversal` · `Pointers`

---

## ⏱️ 30-Second Last-Minute Revision

> **Reverse DLL = swap next↔back each node.** `temp=curr->next; curr->next=curr->back; curr->back=temp; head=curr; curr=temp;`. O(N)/O(1). New head = old tail.
