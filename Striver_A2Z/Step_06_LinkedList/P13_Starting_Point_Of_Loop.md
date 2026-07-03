# 🔥 Starting Point of Loop in a Linked List

> **LeetCode #142** · **Difficulty:** Medium · **Step 6 — Linked List · P13**

---

## 🧠 Problem Understanding

**What is it asking?**
If the list has a cycle, return the **node where the loop begins**; otherwise return `NULL`.

**Key Observation:**
Floyd's algorithm, two phases: (1) detect the meeting point with slow/fast, (2) reset `slow` to `head` and move **both one step at a time** — they meet exactly at the loop's start.

**Simple Example:**
```
3 -> 2 -> 0 -> -4
     ▲           |
     └───────────┘     loop starts at node(2)
```

---

## 🎯 Interview Progression

### 🥉 Brute — Hash Set

> First node you revisit is the loop's start.

```cpp
ListNode* detectCycleBrute(ListNode* head){
    unordered_set<ListNode*> seen;
    ListNode* temp=head;
    while(temp!=NULL){
        if(seen.count(temp)) return temp;
        seen.insert(temp);
        temp=temp->next;
    }
    return NULL;
}
```

**Time:** O(N) · **Space:** O(N).

### 🥇 Optimal — Floyd's Two-Phase

> 💡 After slow and fast collide, put `slow` back at `head`. Advance both by 1; the point where they meet again is the loop start.

```cpp
class Solution {
public:
    ListNode* detectCycle(ListNode* head){
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast!=NULL&&fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast){
                slow=head;
                while(slow!=fast){
                    slow=slow->next;
                    fast=fast->next;
                }
                return slow;
            }
        }
        return NULL;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Why resetting to head works (the math)
Let `L` = distance head→loop-start, `C` = loop length, and the collision happen `d` nodes into the loop. When they meet, slow has travelled `L + d`, fast `2(L + d)`, and fast's extra distance is a whole number of loops: `L + d = kC`. So `L = kC − d`. Moving one pointer from **head** (`L` steps) and the other from the **meeting point** (`kC − d` steps around the loop) lands them both on the loop start. **You don't need to memorize the proof — just: reset slow to head, step both by 1, they meet at the start.**

---

## 🧾 Recall Line *(10-Second Revision)*

> "Floyd detect meeting point, then reset slow=head, move both +1, they meet at loop start. O(1)."

---

## 📝 Short Revision Notes

- Two phases: **collision**, then **reset-and-walk**.
- Reset only **one** pointer (slow) to head; fast stays at meeting point.
- Both advance **one** step in phase 2 (not two).
- Return the node they meet at — that's the loop entry.

---

## ⚠️ Common Mistakes

❌ Moving fast by 2 in phase 2 → won't meet at the start.
❌ Resetting both pointers to head → returns head, wrong.
❌ Forgetting the no-cycle `return NULL` path.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "where does the loop start", "entry of the cycle", "find duplicate number (array as list)" → **Floyd's two-phase**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Floyd's Cycle Detection`

---

## ⏱️ 30-Second Last-Minute Revision

> **Loop start = Floyd phase 2.** Detect collision, then `slow=head; while(slow!=fast){slow=slow->next; fast=fast->next;} return slow;`. O(N)/O(1).
