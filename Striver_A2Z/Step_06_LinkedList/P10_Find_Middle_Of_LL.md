# 🔥 Find the Middle of a Linked List

> **LeetCode #876** · **Difficulty:** Easy · **Step 6 — Linked List · P10**

---

## 🧠 Problem Understanding

**What is it asking?**
Return the **middle** node of a singly linked list. If there are two middles (even length), return the **second** one.

**Key Observation:**
Use **slow & fast pointers** (Tortoise & Hare). Fast moves 2 steps for every 1 of slow. When fast reaches the end, slow is exactly at the middle — one pass, no length precomputation.

**Simple Example:**
```
1 -> 2 -> 3 -> 4 -> 5        middle = 3   (odd)
1 -> 2 -> 3 -> 4 -> 5 -> 6   middle = 4   (even → 2nd middle)
```

---

## 🎯 Interview Progression

### 🥉 Brute — Count then Re-traverse

> Compute length `N`, then walk again `N/2` steps.

```cpp
Node* findMiddleBrute(Node* head){
    int n=0;
    Node* temp=head;
    while(temp!=NULL){
        n++;
        temp=temp->next;
    }
    temp=head;
    for(int i=0;i<n/2;i++) temp=temp->next;
    return temp;
}
```

**Time:** O(N) + O(N/2) → two passes · **Space:** O(1). Correct but traverses ~1.5×.

### 🥇 Optimal — Slow & Fast (Tortoise & Hare)

> 💡 One pass. `slow` steps 1, `fast` steps 2. Loop while `fast && fast->next`. When it stops, `slow` sits on the middle (2nd middle for even length — which is exactly the required output).

```cpp
Node* findMiddle(Node* head){
    Node* slow=head;
    Node* fast=head;
    while(fast!=NULL&&fast->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}
```

**Time:** O(N) single pass · **Space:** O(1).

### Why the loop condition
- `fast != NULL` handles **even** length (fast lands exactly on `NULL`).
- `fast->next != NULL` handles **odd** length (fast lands on the last node).
- Both starting at `head` gives the **second** middle for even lists. (Starting `fast = head->next` would give the *first* middle — the LeetCode variant wants the second, so both start at head.)

### Dry Run
`1 -> 2 -> 3 -> 4 -> 5`:

| slow | fast | fast valid? |
|------|------|-------------|
| 1 | 1 | yes → move |
| 2 | 3 | yes → move |
| 3 | 5 | fast->next == NULL → stop |

**Middle = node(3)** ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Slow +1, fast +2, `while(fast && fast->next)`. Slow ends at middle (2nd for even). O(N) one pass."

---

## 📝 Short Revision Notes

- Both pointers start at `head` → returns **second** middle on even length.
- Loop guard `fast && fast->next` covers odd *and* even.
- This slow/fast setup is the backbone of cycle detection, palindrome check, and nth-from-end.

---

## ⚠️ Common Mistakes

❌ Checking `fast->next` before `fast` → null deref when fast is already NULL (order matters).
❌ Advancing `fast = fast->next` (one step) → slow ends at ~¼, not middle.
❌ Wanting the *first* middle but starting both at head (or vice-versa).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "middle of list", "detect cycle", "nth from end", "split list in half" → **slow & fast pointers**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Slow-Fast`

---

## ⏱️ 30-Second Last-Minute Revision

> **Middle = Tortoise & Hare.** `slow=fast=head; while(fast && fast->next){ slow=slow->next; fast=fast->next->next; } return slow;`. O(N), one pass, 2nd middle on even.
