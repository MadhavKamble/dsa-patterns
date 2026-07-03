# 🔥 Delete Tail of a Doubly Linked List

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P08**

---

> ⚠️ **Note:** this was sent titled "delete head", but the pasted `deleteTail` code deletes the **tail**. This note covers delete-tail (what the code does). A quick delete-**head** version is added at the bottom.

---

## 🧠 Problem Understanding

**What is it asking?**
Given the `head` of a DLL, delete the **last** node, free its memory, and return the head.

**Key Observation:**
In a DLL the tail node stores a `prev` pointer, so once we reach the tail we can null its predecessor's `next` via `temp->prev->next` — no need to track the second-last node separately (unlike the singly-LL delete-tail in P03).

**Edge Cases:**
- Empty (`head == NULL`) → return `NULL`.
- Single node (`head->next == NULL`) → delete head, return `NULL`.

**Simple Example:**
```
Before:  1 ⇄ 2 ⇄ 3
After:   1 ⇄ 2
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Walk to Tail, Use `prev` to Detach

> 💡 Traverse to the last node. Its `prev` is the new tail: set `temp->prev->next = NULL`, then `delete temp`. The DLL's back pointer saves us from tracking two nodes.

```cpp
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val){
        data=val;
        prev=NULL;
        next=NULL;
    }
};

class Solution {
public:
    Node* deleteTail(Node* head){
        if(head==NULL) return NULL;
        if(head->next==NULL){
            delete head;
            return NULL;
        }
        Node* temp=head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->prev->next=NULL;
        delete temp;
        return head;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Why it works
- Loop `while(temp->next != NULL)` lands `temp` **on** the tail.
- `temp->prev->next = NULL` detaches the tail from the list (the new tail's `next` is now null). We don't touch `temp->prev->prev` — the rest of the back-chain is untouched.
- `delete temp` frees the removed node → no leak.
- Guards handle empty/single-node before the loop so `temp->prev` is always valid.

### Dry Run
`1 ⇄ 2 ⇄ 3`, delete tail:

| Step | temp | temp->next | Action |
|------|------|-----------|--------|
| 1 | node(1) | node(2) | advance |
| 2 | node(2) | node(3) | advance |
| 3 | node(3) | NULL | stop → `node(3)->prev->next = NULL` (node(2)->next=NULL), delete node(3) |

**Result:** `1 ⇄ 2` ✅

---

## 🔁 Variant — Delete **Head** of DLL

> For completeness (matches the sent title). Move head forward, cut the new head's `back`.

```cpp
Node* deleteHead(Node* head){
    if(head==NULL||head->next==NULL){
        delete head;
        return NULL;
    }
    Node* newHead=head->next;
    newHead->prev=NULL;
    head->next=NULL;
    delete head;
    return newHead;
}
```

Delete-head is **O(1)** (no traversal) — cheaper than delete-tail's O(N).

---

## 🧾 Recall Line *(10-Second Revision)*

> "Tail: walk to last node, `temp->prev->next=NULL; delete temp`. Head: `newHead=head->next; newHead->prev=NULL; delete head`."

---

## 📝 Short Revision Notes

- DLL delete-tail uses `temp->prev` → no need to track second-last node (unlike singly LL).
- Guard empty + single-node before the loop.
- `delete` the removed node to avoid a leak.
- Delete-tail = O(N); delete-head = O(1).

---

## ⚠️ Common Mistakes

❌ Forgetting to null the new tail's `next` (`temp->prev->next = NULL`) → dangling pointer to freed node.
❌ On delete-head, forgetting `newHead->prev = NULL` → back-chain points to a freed node.
❌ Missing empty/single-node guards → `temp->prev` deref on null.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "remove first/last node of a doubly list" → use the node's own `prev`/`next` to relink, then `delete`.

---

## 🏆 Pattern Category

`Linked List` · `Doubly Linked List` · `Deletion`

---

## ⏱️ 30-Second Last-Minute Revision

> **DLL delete-tail = O(N):** walk to tail, `temp->prev->next=NULL; delete temp`. **Delete-head = O(1):** `newHead=head->next; newHead->prev=NULL; delete head; return newHead`.
