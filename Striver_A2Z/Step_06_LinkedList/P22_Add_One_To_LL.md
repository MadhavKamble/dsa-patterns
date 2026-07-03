# 🔥 Add 1 to a Number Represented by a Linked List

> **Concept Problem** · **Difficulty:** Medium · **Step 6 — Linked List · P22**

---

## 🧠 Problem Understanding

**What is it asking?**
Each node is one digit of a number (most-significant first). Add `1` and return the head. A carry may create a new leading digit (e.g. `999 → 1000`).

**Key Observation:**
Addition flows from the **least-significant digit** — the **tail**. But a singly list only goes forward. Two ways to reach the tail's carry: **reverse → add → reverse back**, or **recurse to the end and carry back up** the call stack.

**Simple Example:**
```
1 -> 2 -> 9   (129)   +1   →   1 -> 3 -> 0   (130)
9 -> 9 -> 9   (999)   +1   →   1 -> 0 -> 0 -> 0
```

---

## 🎯 Interview Progression

### 🥇 Optimal A — Reverse, Add, Reverse Back (Iterative)

> 💡 Reverse so the LSD is at the head. Add `carry=1`, propagate `sum/10`. If a carry survives past the tail, append a new node. Reverse back to restore MSD-first order.

```cpp
class Solution {
public:
    Node* reverseList(Node* node){
        Node* prev=nullptr;
        Node* current=node;
        while(current){
            Node* nextNode=current->next;
            current->next=prev;
            prev=current;
            current=nextNode;
        }
        return prev;
    }

    Node* addOne(Node* head){
        head=reverseList(head);
        Node* current=head;
        int carry=1;
        while(current&&carry){
            int sum=current->data+carry;
            current->data=sum%10;
            carry=sum/10;
            if(!current->next&&carry){
                current->next=new Node(carry);
                carry=0;
            }
            current=current->next;
        }
        head=reverseList(head);
        return head;
    }
};
```

**Time:** O(N) (three linear passes) · **Space:** O(1).

### 🥇 Optimal B — Recursion (Carry Bubbles Up)

> 💡 Recurse to the end; the base case returns carry `1` (the "+1"). Each frame adds the returned carry to its digit and returns the new carry. If the head still emits a carry, prepend a new node — no reversal needed.

```cpp
class Solution {
public:
    int addOneUtil(Node* node){
        if(!node) return 1;
        int carry=addOneUtil(node->next);
        int sum=node->data+carry;
        node->data=sum%10;
        return sum/10;
    }

    Node* addOne(Node* head){
        int carry=addOneUtil(head);
        if(carry){
            Node* newHead=new Node(carry);
            newHead->next=head;
            head=newHead;
        }
        return head;
    }
};
```

**Time:** O(N) · **Space:** O(N) recursion stack.

### Why the recursive base returns 1
The "+1" is injected as the carry coming **into** the last digit — so `addOneUtil(nullptr)` (past the tail) returns `1`. Each frame does `digit + carry`, stores `sum%10`, returns `sum/10`. When the head's frame returns a leftover carry, we prepend it (the `999 → 1000` case).

### Dry Run (recursive, `1 -> 2 -> 9`)

| frame | digit | carry in | sum | new digit | carry out |
|-------|-------|----------|-----|-----------|-----------|
| node(9) | 9 | 1 | 10 | 0 | 1 |
| node(2) | 2 | 1 | 3 | 3 | 0 |
| node(1) | 1 | 0 | 1 | 1 | 0 |

Head carry 0 → result `1 -> 3 -> 0` ✅

---

## 🚀 Approach Comparison

| Approach | Time | Space | Note |
|----------|------|-------|------|
| Reverse + add + reverse | O(N) | O(1) | Iterative, 3 passes, no stack |
| **Recursion** | O(N) | O(N) | Cleanest, uses call stack as implicit reversal |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Add flows from tail. Either reverse→add carry→reverse back, or recurse (base returns 1), prepend node if head carries out."

---

## 📝 Short Revision Notes

- Addition starts at the **LSD = tail**; singly list needs reverse or recursion to get there.
- Carry init = 1 (that's the "+1"); recursive base case returns 1.
- New leading node needed only when the final carry survives (all 9s).
- Iterative = O(1) space; recursive = O(N) stack but no reversals.

---

## ⚠️ Common Mistakes

❌ Forgetting to reverse **back** in the iterative version → digits stay reversed.
❌ Not handling the surviving carry → `999 + 1` loses the leading `1`.
❌ Recursive base returning `0` instead of `1` → adds nothing.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "number as a linked list", "add / process from least-significant digit", "carry propagation" → **reverse-or-recurse from the tail**.

---

## 📚 Related Problems

- [ ] LeetCode #2 — Add Two Numbers (digits stored LSD-first → no reversal needed)
- [ ] LeetCode #369 — Plus One Linked List

---

## 🏆 Pattern Category

`Linked List` · `Recursion` · `Reversal` · `Carry Propagation`

---

## ⏱️ 30-Second Last-Minute Revision

> **Add 1 to LL:** reverse → `carry=1`, `sum=d+carry; d=sum%10; carry=sum/10`, append if carry left → reverse back. OR recurse (base returns 1), prepend node if head carries. O(N).
