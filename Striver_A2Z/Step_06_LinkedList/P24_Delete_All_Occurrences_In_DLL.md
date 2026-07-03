# 🔥 Delete All Occurrences of a Key in a DLL

> **Concept Problem** · **Difficulty:** Medium · **Step 6 — Linked List · P24**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a doubly linked list and a `key`, delete **every** node whose value equals the key, and return the (possibly new) head.

**Key Observation:**
A DLL node knows both its neighbours (`back` and `next`), so deleting one is O(1) once you're on it — just splice: `prev->next = nextNode` and `nextNode->back = prev`. The only care points are (a) deleting the **head** (must advance head) and (b) guarding null neighbours at the ends.

**Simple Example:**
```
key = 2
Before:  2 ⇄ 3 ⇄ 2 ⇄ 4 ⇄ 2
After:   3 ⇄ 4
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Single Pass, Splice Each Match

> 💡 Walk with `temp`. On a match, capture `back` and `next`, rewire both neighbours around `temp`, move head forward if we're deleting it, `delete temp`, then continue from the saved `next`.

```cpp
Node* deleteAllOccurrences(Node* head,int key){
    Node* temp=head;
    while(temp!=NULL){
        if(temp->data==key){
            if(temp==head){
                head=temp->next;
            }
            Node* nextNode=temp->next;
            Node* prevNode=temp->back;
            if(nextNode!=NULL) nextNode->back=prevNode;
            if(prevNode!=NULL) prevNode->next=nextNode;
            delete temp;
            temp=nextNode;
        }else{
            temp=temp->next;
        }
    }
    return head;
}
```

**Time:** O(N) single pass · **Space:** O(1).

### Why the guards
- `if(temp==head) head=temp->next;` — if the node being removed is the current head, the head must slide to the next node (which may itself be a key → loop handles it next).
- `if(nextNode!=NULL)` and `if(prevNode!=NULL)` — a matching node at the **tail** has `next==NULL`; at the **head** has `back==NULL`. Skip those splices to avoid a null deref.
- Save `nextNode` **before** `delete temp`, then resume from it — never touch freed memory.

### Dry Run
`2 ⇄ 3 ⇄ 2 ⇄ 4`, key=2:

| temp | match? | action | head |
|------|--------|--------|------|
| 2 | yes (head) | head→3, delete → temp=3 | 3 |
| 3 | no | advance → temp=2 | 3 |
| 2 | yes | 3.next=4, 4.back=3, delete → temp=4 | 3 |
| 4 | no | advance → NULL | 3 |

**Result:** `3 ⇄ 4` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Walk DLL; on match splice `prev->next=next` & `next->back=prev`, move head if deleting it, delete node, continue from saved next. O(N)."

---

## 📝 Short Revision Notes

- DLL delete = O(1) per node (both neighbours known); total O(N).
- Guard head-deletion (advance head) and null neighbours at the ends.
- Save `next` before deleting; resume from it.
- Consecutive matches handled naturally — head can move multiple times.

---

## ⚠️ Common Mistakes

❌ Not updating `head` when the head node matches → returns a dangling/freed head.
❌ Splicing `prevNode->next` when `prevNode` is NULL (deleting head) → crash.
❌ Advancing `temp` before saving `temp->next`, then deleting → use-after-free.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "remove all nodes with value X in a doubly list" → **single-pass splice using `back`/`next`, guard ends + head**.

---

## 🏆 Pattern Category

`Linked List` · `Doubly Linked List` · `Deletion`

---

## ⏱️ 30-Second Last-Minute Revision

> **Delete all key in DLL:** walk; on match `prev->next=next; next->back=prev;` (guard nulls), move head if it's the head, `delete`, continue from saved next. O(N)/O(1).
