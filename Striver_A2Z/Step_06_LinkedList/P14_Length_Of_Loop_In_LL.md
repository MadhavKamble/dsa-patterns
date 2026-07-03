# 🔥 Length of Loop in a Linked List

> **Concept Problem** · **Difficulty:** Medium · **Step 6 — Linked List · P14**

---

## 🧠 Problem Understanding

**What is it asking?**
If the list has a cycle, return the **number of nodes in the loop**; otherwise return `0`.

**Key Observation:**
Detect the loop with Floyd's slow/fast. Once slow and fast meet (a node **guaranteed inside the loop**), keep one pointer fixed and walk another around until it returns — the steps taken = loop length.

**Simple Example:**
```
1 -> 2 -> 3 -> 4 -> 5
     ▲                |
     └────────────────┘     loop = 2,3,4,5 → length 4
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Floyd's + Count Around the Loop

> 💡 After collision at `meetingPoint`, start a counter at 1 and walk `temp` from `meetingPoint->next` until it comes back to `meetingPoint`. That count is the loop length.

```cpp
class Solution {
public:
    int lengthOfLoop(Node* head){
        Node* slow=head;
        Node* fast=head;
        while(fast!=NULL&&fast->next!=NULL){
            slow=slow->next;
            fast=fast->next->next;
            if(slow==fast){
                return countLoopLength(slow);
            }
        }
        return 0;
    }

    int countLoopLength(Node* meetingPoint){
        Node* temp=meetingPoint;
        int length=1;
        while(temp->next!=meetingPoint){
            temp=temp->next;
            length++;
        }
        return length;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Why it works
- The meeting point is provably **on the loop**, so walking `next` from it must eventually return to it.
- Start `length = 1` to count the meeting node itself; each `temp = temp->next` before the recheck adds one more, stopping when `temp->next == meetingPoint` (i.e. `temp` is the last node of the loop).

### Dry Run
Loop `2→3→4→5→2`, meeting at say node(4):

| temp | length | temp->next==meet? |
|------|--------|-------------------|
| 4 | 1 | 5 → no |
| 5 | 2 | 2 → no |
| 2 | 3 | 3 → no |
| 3 | 4 | 4(meet) → stop |

**Length = 4** ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Floyd meet inside loop, then walk from meeting node back to itself counting steps = loop length. O(1)."

---

## 📝 Short Revision Notes

- Meeting point is always **inside** the loop → safe to count from it.
- `length` starts at 1 (counts the start node); loop until `temp->next == meetingPoint`.
- No cycle → return 0.

---

## ⚠️ Common Mistakes

❌ Starting `length = 0` → off by one.
❌ Counting from `head` instead of the meeting point → includes the non-loop tail.
❌ Loop condition `temp != meetingPoint` (instead of `temp->next != ...`) → returns immediately (temp already == meet).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "size of the loop", "how many nodes in the cycle" → **Floyd's meet + count one lap**.

---

## 🏆 Pattern Category

`Linked List` · `Two Pointers` · `Floyd's Cycle Detection`

---

## ⏱️ 30-Second Last-Minute Revision

> **Loop length = Floyd + one lap.** Detect meeting node, then `len=1; while(temp->next!=meet){temp=temp->next; len++;}` return len. O(N)/O(1).
