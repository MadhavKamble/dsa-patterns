# 🔥 Reverse a Linked List

> **LeetCode #206** · **Difficulty:** Easy · **Step 6 — Linked List · P11**

---

## 🧠 Problem Understanding

**What is it asking?**
Reverse a singly linked list — the last node becomes the head — and return the new head.

**Key Observation:**
Flip each node's `next` to point at its **predecessor**. The catch: before overwriting `temp->next`, save it (`front`) so you don't lose the rest of the list. Old head becomes the tail (`next = NULL`); old tail becomes the new head.

**Simple Example:**
```
Before:  1 -> 2 -> 3 -> 4 -> 5
After:   5 -> 4 -> 3 -> 2 -> 1
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Iterative 3-Pointer

> 💡 Keep `prev` (reversed part so far), `temp` (current), `front` (saved next). Each step: save `front`, point `temp->next` back to `prev`, slide both forward. `prev` ends up as the new head.

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head){
        ListNode* prev=NULL;
        ListNode* temp=head;
        while(temp!=NULL){
            ListNode* front=temp->next;
            temp->next=prev;
            prev=temp;
            temp=front;
        }
        return prev;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Dry Run
`1 -> 2 -> 3`:

| temp | front | after `temp->next=prev` | prev | temp next |
|------|-------|-------------------------|------|-----------|
| 1 | 2 | 1->NULL | 1 | 2 |
| 2 | 3 | 2->1 | 2 | 3 |
| 3 | NULL | 3->2 | 3 | NULL → stop |

**Return prev = 3 -> 2 -> 1** ✅

---

### 🔁 Variant — Recursive

> 💡 Reverse the rest of the list first, then fix the link between `head` and `head->next`: make `head->next->next = head` and `head->next = NULL`. `newHead` bubbles up unchanged (it's always the original tail).

```cpp
class Solution {
public:
    ListNode* reverseList(ListNode* head){
        if(head==NULL||head->next==NULL) return head;
        ListNode* newHead=reverseList(head->next);
        ListNode* front=head->next;
        front->next=head;
        head->next=NULL;
        return newHead;
    }
};
```

**Time:** O(N) · **Space:** O(N) recursion stack.

**How the flip works:** after `reverseList(head->next)` returns, `head->next` is now the **tail** of the reversed sublist. `front = head->next` grabs it; `front->next = head` appends `head` behind it; `head->next = NULL` makes `head` the new tail (correct for when recursion unwinds to the original head).

---

## 🚀 Approach Comparison

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| **Iterative 3-pointer** | O(N) | O(1) | Preferred — no stack risk |
| **Recursive** | O(N) | O(N) | Elegant; risks stack overflow on huge lists |
| **Stack of values** | O(N) | O(N) | Push data, pop back into nodes; reverses data only |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Iter: `front=temp->next; temp->next=prev; prev=temp; temp=front;` return prev. Recursive: reverse rest, `head->next->next=head; head->next=NULL`."

---

## 📝 Short Revision Notes

- **Save the next node before** rewriting `temp->next` — the #1 rule.
- Iterative returns `prev` (old tail = new head).
- Recursive base case: empty or single node returns itself.
- Recursive: `newHead` is passed straight up; only the local link is fixed each frame.

---

## ⚠️ Common Mistakes

❌ Overwriting `temp->next` before saving it → lose the rest of the list.
❌ Returning `head` instead of `prev` (iterative) → returns the old head (now tail).
❌ Recursive: forgetting `head->next = NULL` → creates a cycle at the tail.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "reverse a list", "reverse in k-groups", "palindrome check", "reorder list" → **3-pointer iterative reversal**.

---

## 🏆 Pattern Category

`Linked List` · `Reversal` · `Two/Three Pointers` · `Recursion`

---

## ⏱️ 30-Second Last-Minute Revision

> **Reverse LL:** iterative `prev=NULL`, loop `front=temp->next; temp->next=prev; prev=temp; temp=front;` → return prev. O(N)/O(1). Recursive: reverse rest, `head->next->next=head; head->next=NULL;`.
