# 🔥 Delete the Middle Node of a Linked List

> **LeetCode #2095** · **Difficulty:** Medium · **Step 6 — Linked List · P18**

---

## 🧠 Problem Understanding

**What is it asking?**
Delete the **middle** node (for even length, the second of the two middles — index ⌊n/2⌋) and return the head.

**Key Observation:**
Use slow/fast, but start `fast` **two nodes ahead** (`head->next->next`). This offset makes `slow` stop on the node **just before** the middle, so we can bypass and delete in one pass — no separate "previous" tracking.

**Simple Example:**
```
1 -> 2 -> 3 -> 4 -> 5   →  delete 3  →  1 -> 2 -> 4 -> 5
1 -> 2 -> 3 -> 4        →  delete 3  →  1 -> 2 -> 4
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Slow/Fast with a Head-Start

> 💡 Single-node list → return `nullptr`. Otherwise `slow=head`, `fast=head->next->next`. Loop while `fast && fast->next`. `slow` ends just before the middle → `slow->next = slow->next->next` and delete.

```cpp
Node* deleteMiddle(Node* head){
    if(head==nullptr||head->next==nullptr){
        delete head;
        return nullptr;
    }
    Node* slow=head;
    Node* fast=head->next->next;
    while(fast!=nullptr&&fast->next!=nullptr){
        slow=slow->next;
        fast=fast->next->next;
    }
    Node* middle=slow->next;
    slow->next=slow->next->next;
    delete middle;
    return head;
}
```

**Time:** O(N) · **Space:** O(1).

### Why fast starts at `head->next->next`
Standard middle-finder lands slow **on** the middle. Here we need the node **before** it to unlink. Giving fast a 2-node head start shifts slow back by one, so it stops as the middle's predecessor. The single-node guard prevents `head->next->next` from dereferencing null.

### Dry Run
`1 -> 2 -> 3 -> 4 -> 5`:

| slow | fast | fast valid? |
|------|------|-------------|
| 1 | 3 | yes → move |
| 2 | 5 | fast->next==NULL → stop |

`slow=2`, `middle=slow->next=3`, bypass → `1 -> 2 -> 4 -> 5` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "slow=head, fast=head->next->next. Loop `fast && fast->next`. slow ends before middle → `slow->next=slow->next->next; delete`. Single node → null."

---

## 📝 Short Revision Notes

- Head-start on fast (`head->next->next`) → slow stops **before** middle.
- Single-node case returns `nullptr` (guard also protects `head->next->next`).
- `delete` the unlinked middle to avoid a leak.

---

## ⚠️ Common Mistakes

❌ Starting `fast=head` → slow stops *on* the middle, can't unlink cleanly.
❌ No single-node guard → `head->next->next` derefs null.
❌ Forgetting `delete middle` → memory leak.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "delete/find node just before the middle", "one-pass middle removal" → **slow/fast with a 2-node head start**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Slow-Fast`

---

## ⏱️ 30-Second Last-Minute Revision

> **Delete middle:** `fast=head->next->next`, loop `fast && fast->next`, slow lands before middle → `slow->next=slow->next->next; delete`. O(N)/O(1).
