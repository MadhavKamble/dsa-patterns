# 🔥 Insert at the End of a Doubly Linked List

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P07**

---

## 🧠 Problem Understanding

**What is it asking?**
Given the `head` of a doubly linked list and a value `k`, append a new node at the **tail** and return the head.

**Key Observation:**
Without a stored tail pointer, we must **walk to the last node** (O(N)), then wire the new node in **both directions**: `tail->next = newNode` and `newNode->back = tail`.

**Edge Case:** empty list (`head == nullptr`) → the new node *is* the whole list; return it.

**Simple Example:**
```
Before:  12 ⇄ 5 ⇄ 8 ⇄ 7 ⇄ 4        insert 10 at tail
After:   12 ⇄ 5 ⇄ 8 ⇄ 7 ⇄ 4 ⇄ 10
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Walk to Tail, Wire Both Links

> 💡 Traverse with `while(tail->next != nullptr)` to land **on** the last node. Attach the new node forward (`tail->next`) and backward (`newNode->back`). Head is unchanged for a non-empty list.

```cpp
Node* insertAtTail(Node* head,int k){
    Node* newNode=new Node(k);
    if(head==nullptr){
        return newNode;
    }
    Node* tail=head;
    while(tail->next!=nullptr){
        tail=tail->next;
    }
    tail->next=newNode;
    newNode->back=tail;
    return head;
}
```

**Time:** O(N) (must reach the tail) · **Space:** O(1).

### Why it works
- Note the loop condition here is `tail->next != nullptr` (not `->next->next`) — for **insertion** we want to stop **on** the last node, not one before it (contrast with delete-tail in P03).
- New node created via single-arg constructor → its `next` and `back` are both `nullptr`. After wiring, only `back` is set; `next` correctly stays `nullptr` (it's the new tail).
- Empty-list guard returns the new node as head — its `back`/`next` are already `nullptr`, a valid one-node DLL.

### Dry Run
`12 ⇄ 5`, insert `10`:

| Step | tail | tail->next | Action |
|------|------|-----------|--------|
| 1 | node(12) | node(5) ≠ null | advance → tail = node(5) |
| 2 | node(5) | null | stop |
| 3 | node(5) | — | `node(5)->next = node(10)`, `node(10)->back = node(5)` |

**Result:** `12 ⇄ 5 ⇄ 10` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Walk while `tail->next`, then `tail->next=newNode; newNode->back=tail`. Empty list → return newNode. O(N)."

---

## 📝 Short Revision Notes

- **Insert** stops **on** the tail (`tail->next != nullptr`); **delete-tail** stops one before (`->next->next`).
- Wire **both** directions: forward `next` and backward `back`.
- Empty-list guard essential — else `tail->next` derefs `nullptr`.
- With only a `head`, tail insert is O(N); keeping a tail pointer would make it O(1).

---

## ⚠️ Common Mistakes

❌ Setting only `tail->next = newNode` and forgetting `newNode->back = tail` → backward chain broken.
❌ Using `tail->next->next` (delete-style condition) → skips past the real tail / null deref.
❌ Missing the `head == nullptr` guard → crash on empty list.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "append to a doubly list", "add at tail" → **walk to last node, wire `next` + `back`** (or keep a tail pointer for O(1)).

---

## 🏆 Pattern Category

`Linked List` · `Doubly Linked List` · `Insertion`

---

## ⏱️ 30-Second Last-Minute Revision

> **DLL tail insert = O(N).** Guard empty → return newNode. Else `while(tail->next) tail=tail->next;`, then `tail->next=newNode; newNode->back=tail;`, return head.
