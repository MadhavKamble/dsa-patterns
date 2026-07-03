# 🔥 Detect a Cycle in a Linked List

> **LeetCode #141** · **Difficulty:** Easy · **Step 6 — Linked List · P12**

---

## 🧠 Problem Understanding

**What is it asking?**
Return `true` if the linked list has a **cycle** (some node's `next` points back to an earlier node), else `false`.

**Key Observation:**
**Floyd's Tortoise & Hare.** Slow moves 1, fast moves 2. If there's a loop, fast keeps lapping the track and **must** eventually collide with slow. If there's no loop, fast simply hits `NULL`.

**Simple Example:**
```
1 -> 2 -> 3 -> 4 -> 5
          ▲          |
          └──────────┘     → cycle → true
```

---

## 🎯 Interview Progression

### 🥉 Brute — Hash Set of Visited Nodes

> Store every node's address; if you revisit one, there's a cycle.

```cpp
bool hasCycleBrute(ListNode* head){
    unordered_set<ListNode*> seen;
    ListNode* temp=head;
    while(temp!=NULL){
        if(seen.find(temp)!=seen.end()) return true;
        seen.insert(temp);
        temp=temp->next;
    }
    return false;
}
```

**Time:** O(N) · **Space:** O(N). Correct but uses extra memory.

### 🥇 Optimal — Floyd's Tortoise & Hare

> 💡 Two pointers at different speeds. In a loop, the gap between them shrinks by 1 each step, so they're guaranteed to meet. O(1) space.

```cpp
class Solution {
public:
    bool hasCycle(ListNode* head){
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast) return true;
        }
        return false;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Why they must meet
Inside the loop, think in the cycle's frame: fast gains **1 node per step** on slow. The distance between them decreases 1 each iteration until it hits 0 → collision. No loop → fast escapes to `NULL` and the guard ends the walk.

### Dry Run
`1→2→3→4→5→(back to 3)`:

| slow | fast | meet? |
|------|------|-------|
| 2 | 3 | no |
| 3 | 5 | no |
| 4 | 4 | **yes → true** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Slow +1, fast +2. If they ever meet → cycle. Fast hits NULL → no cycle. O(1) space."

---

## 📝 Short Revision Notes

- Compare the **collision test** `slow==fast` *after* moving both.
- Guard `fast && fast->next` before moving fast two steps.
- Hash-set works but is O(N) space; Floyd's is the expected O(1).

---

## ⚠️ Common Mistakes

❌ Checking `slow==fast` **before** the first move → both start at head → false positive.
❌ Comparing `slow->data == fast->data` → wrong; compare **node addresses**.
❌ Missing the `fast->next` guard → null deref on `fast->next->next`.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "loop / cycle in a list", "does it terminate" → **Floyd's slow-fast**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Floyd's Cycle Detection`

---

## ⏱️ 30-Second Last-Minute Revision

> **Cycle detect = Floyd's.** `while(fast && fast->next){ slow=slow->next; fast=fast->next->next; if(slow==fast) return true; } return false;`. O(N)/O(1).
