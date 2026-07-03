# 🔥 Rotate List

> **LeetCode #61** · **Difficulty:** Medium · **Step 6 — Linked List · P28**

---

## 🧠 Problem Understanding

**What is it asking?**
Rotate the list to the **right** by `k` places. The last `k % length` nodes move to the front.

**Key Observation:**
Make the list **circular**, then break it at the right spot. Rotating right by `k` means the new head is at position `length − k` (0-indexed from the old head), and the node just before it becomes the new tail. Use `k % length` since rotating by a full length is a no-op.

**Simple Example:**
```
1 -> 2 -> 3 -> 4 -> 5,  k=2   →   4 -> 5 -> 1 -> 2 -> 3
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Connect into a Ring, Cut at length−k

> 💡 Walk to the tail counting `length`. Close the ring (`tail->next = head`). Reduce `k %= length`. Walk `length − k` steps to reach the new tail; the node after it is the new head; sever the ring.

```cpp
class Solution {
public:
    ListNode* rotateRight(ListNode* head,int k){
        if(!head||!head->next||k==0){
            return head;
        }
        ListNode* temp=head;
        int length=1;
        while(temp->next){
            ++length;
            temp=temp->next;
        }
        temp->next=head;
        k=k%length;
        int end=length-k;
        while(end--) temp=temp->next;
        head=temp->next;
        temp->next=nullptr;
        return head;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Why `length − k` steps
- After `temp->next = head`, `temp` sits on the **old tail** and the list is a ring.
- The new tail must be the node at index `length − k − 1` from the old head; walking `temp` forward `length − k` steps (starting from the old tail) lands `temp` exactly there. Then `head = temp->next` is the new head and `temp->next = nullptr` cuts the ring.
- `k %= length` collapses redundant full rotations (e.g. k=7, length=5 → k=2). The early guards (empty / single node / k=0) avoid needless work and division issues.

### Dry Run
`1 2 3 4 5`, k=2:
- length=5, ring closed at node5→node1.
- k=2, end = 5−2 = 3. Walk temp (at node5) 3 steps → node1→node2→node3. temp=node3.
- head = node3->next = node4; node3->next = null.

**Result:** `4 -> 5 -> 1 -> 2 -> 3` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Count length, make ring (tail->next=head), k%=length, walk length−k from old tail → new tail, cut. O(N)."

---

## 📝 Short Revision Notes

- `k %= length` — full-length rotations cancel out.
- New head at position `length − k`; new tail is the node before it.
- Build a ring then break it — cleaner than juggling two pointers.
- Guard empty / single-node / k==0 up front.

---

## ⚠️ Common Mistakes

❌ Forgetting `k %= length` → over-rotates / walks off with large k.
❌ Cutting at the wrong node (off-by-one on `length − k`).
❌ Not severing the ring (`temp->next = nullptr`) → infinite cyclic list.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "rotate list by k", "cyclic shift of a list" → **ring + cut at length−k**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Math (modulo)`

---

## ⏱️ 30-Second Last-Minute Revision

> **Rotate right by k:** count length, `tail->next=head` (ring), `k%=length`, walk `length−k` → new tail, `head=tail->next; tail->next=null`. O(N)/O(1).
