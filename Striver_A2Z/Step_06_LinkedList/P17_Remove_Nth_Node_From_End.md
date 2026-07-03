# 🔥 Remove Nth Node from the End of a Linked List

> **LeetCode #19** · **Difficulty:** Medium · **Step 6 — Linked List · P17**

---

## 🧠 Problem Understanding

**What is it asking?**
Remove the **Nth node from the end** and return the head.

**Key Observation:**
Two pointers with a fixed gap of **N**. Advance `fast` N+1 steps first, then move `fast` and `slow` together until `fast` hits `NULL` — now `slow` sits **just before** the target. A **dummy** node before head makes deleting the head itself (N == length) a non-special case.

**Simple Example:**
```
1 -> 2 -> 3 -> 4 -> 5,  N=3   →  remove 3  →  1 -> 2 -> 4 -> 5
```

---

## 🎯 Interview Progression

### 🥉 Brute — Length then (L−N)th

> Compute length `L`, then walk `L−N` steps to the node before the target.

```cpp
Node* deleteBrute(Node* head,int N){
    int L=0;
    Node* t=head;
    while(t){ L++; t=t->next; }
    if(N==L) return head->next;
    Node* prev=head;
    for(int i=1;i<L-N;i++) prev=prev->next;
    prev->next=prev->next->next;
    return head;
}
```

**Time:** O(2N) two passes · **Space:** O(1). Works but needs the head special case.

### 🥇 Optimal — Two Pointers + Dummy (One Pass)

> 💡 Dummy before head. Move `fast` N+1 steps. Then advance both until `fast == NULL`; `slow` lands right before the target. Delete via `slow->next = slow->next->next`.

```cpp
class Solution {
public:
    Node* deleteNthNodeFromEnd(Node* head,int N){
        Node* dummy=new Node(0,head);
        Node* slow=dummy;
        Node* fast=dummy;
        for(int i=0;i<=N;i++){
            fast=fast->next;
        }
        while(fast!=NULL){
            slow=slow->next;
            fast=fast->next;
        }
        slow->next=slow->next->next;
        return dummy->next;
    }
};
```

**Time:** O(N) single pass · **Space:** O(1).

### Why N+1 steps and a dummy
- Starting both at `dummy` and moving `fast` **N+1** steps opens a gap so that when `fast` reaches `NULL`, `slow` is on the node **before** the one to delete (not on it) — exactly what deletion needs.
- The **dummy** handles removing the **head** (when N == list length): `slow` stays at dummy, `dummy->next = head->next`, and we return `dummy->next`. No separate branch.

### Dry Run
`1 -> 2 -> 3 -> 4 -> 5`, N=3:
- fast moves 4 steps (`0..3`) from dummy → node(4).
- Move both until fast is NULL: slow: dummy→1→2, fast: 4→5→NULL.
- slow = node(2). `slow->next = node(3)->next = node(4)` → removes node(3).

**Result:** `1 -> 2 -> 4 -> 5` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Dummy before head. fast +N+1, then move both till fast==NULL. slow is before target: `slow->next=slow->next->next`. One pass."

---

## 📝 Short Revision Notes

- Gap of **N** between fast and slow → move fast **N+1** from dummy.
- Dummy node kills the delete-head edge case.
- Stop when `fast == NULL`; slow is the predecessor of the target.
- Return `dummy->next`, never `head` directly.

---

## ⚠️ Common Mistakes

❌ Moving fast only N steps → slow lands on the target, not before it.
❌ No dummy → crashes / needs special case when removing the head.
❌ Returning `head` after removing the head node (should be `dummy->next`).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "nth from the end", "remove/find kth from end in one pass" → **two pointers with an N-gap + dummy**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Dummy Node`

---

## ⏱️ 30-Second Last-Minute Revision

> **Remove Nth from end:** dummy → fast +N+1 → move both till fast NULL → `slow->next=slow->next->next` → return `dummy->next`. O(N) one pass.
