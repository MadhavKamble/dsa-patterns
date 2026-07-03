# 🔥 Delete Last Node of Linked List

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P03**

---

## 🧠 Problem Understanding

**What is it asking?**
Given the `head` of a singly linked list, delete the **tail** (last node), free its memory, and return the (possibly changed) head.

**Key Observation:**
To remove the tail we must reach the **second-last** node and set its `next = nullptr`. We stop one node early using the `curr->next->next != NULL` condition. Deleting the tail is **O(N)** — unavoidable in a singly LL because there's no backward pointer.

**Edge Cases:**
- Empty list (`head == NULL`) → nothing to delete, return `NULL`.
- Single node (`head->next == NULL`) → delete head, return `NULL`.

**Simple Example:**
```
Before:  1 -> 2 -> 3
After:   1 -> 2
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Stop at Second-Last Node

> 💡 Walk until `curr->next->next == NULL`. At that point `curr` is the second-last node, `curr->next` is the tail. Delete the tail and null out the link. Handle empty / single-node lists **before** the loop so we never dereference a null `next->next`.

```cpp
struct Node {
    int data;
    Node* next;
    Node(int val){
        data=val;
        next=NULL;
    }
};

class Solution {
public:
    Node* deleteTail(Node* head){
        if(head==NULL||head->next==NULL){
            delete head;
            return NULL;
        }
        Node* curr=head;
        while(curr->next->next!=NULL){
            curr=curr->next;
        }
        delete curr->next;
        curr->next=NULL;
        return head;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Why the guard matters
- The loop condition reads `curr->next->next`. If the list had **0 or 1** node, `curr->next` could be `NULL` and `curr->next->next` would **crash**. The early `if` removes those cases first.
- `delete curr->next;` frees the tail's heap memory (avoids a memory leak); `curr->next = NULL;` makes `curr` the new tail.
- Head is unchanged for lists of size ≥ 2, so we return the original `head`.

### Dry Run
`1 -> 2 -> 3`, delete tail:

| Step | curr | curr->next->next | Action |
|------|------|------------------|--------|
| 1 | node(1) | node(3) ≠ NULL | move → curr = node(2) |
| 2 | node(2) | NULL | stop loop |
| 3 | node(2) | — | delete node(3), `node(2)->next = NULL` |

**Result:** `1 -> 2` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Guard empty/single first. Walk while `curr->next->next != NULL`, then `delete curr->next; curr->next=NULL`. O(N)."

---

## 📝 Short Revision Notes

- Need the **second-last** node → loop condition uses `curr->next->next`.
- Always handle `head==NULL` and single-node **before** the loop (else null deref).
- `delete` frees memory; without it → memory leak.
- Head pointer is unchanged for size ≥ 2; only single-node case returns `NULL`.

---

## ⚠️ Common Mistakes

❌ Looping on `curr->next != NULL` → `curr` ends up *on* the tail, one node too far.
❌ Skipping the single-node guard → `curr->next->next` dereferences `NULL`.
❌ Setting `curr->next = NULL` but forgetting `delete curr->next` → memory leak (and lost handle).
❌ Doing `delete` after nulling `curr->next` → you lose the pointer to the node you meant to free.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "delete tail / last node", "remove from the end of a singly list" → **stop-one-early** traversal (`curr->next->next`).

---

## 🏆 Pattern Category

`Linked List` · `Deletion` · `Traversal`

---

## ⏱️ 30-Second Last-Minute Revision

> **Delete tail = O(N).** Guard empty/single → return NULL. Else walk to second-last via `while(curr->next->next)`, `delete curr->next; curr->next=NULL;`, return head.
