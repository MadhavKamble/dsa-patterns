# 🔥 Add Two Numbers Represented by Linked Lists

> **LeetCode #2** · **Difficulty:** Medium · **Step 6 — Linked List · P23**

---

## 🧠 Problem Understanding

**What is it asking?**
Two numbers are stored as lists with digits in **reverse order** (least-significant digit at the head). Add them and return the sum as a list, also LSD-first.

**Key Observation:**
Because digits are already **LSD-first**, we add straight from the heads — no reversal needed (contrast with P22). Walk both lists together, sum digit + digit + carry, emit `sum % 10`, carry `sum / 10`. A single **dummy** node builds the result cleanly.

**Simple Example:**
```
l1: 2 -> 4 -> 3   (342)
l2: 5 -> 6 -> 4   (465)
sum:7 -> 0 -> 8   (807)
```

---

## 🎯 Interview Progression

### 🥇 Optimal — One Pass with Dummy + Carry

> 💡 Loop while **either** list has nodes **or** a carry remains. Add whatever's available from each list plus carry; append a new node with `sum % 10`. The `|| carry` in the condition handles a final leading carry (e.g. `5+5=10`).

```cpp
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1,ListNode* l2){
        ListNode* dummy=new ListNode();
        ListNode* temp=dummy;
        int carry=0;
        while((l1!=NULL||l2!=NULL)||carry){
            int sum=0;
            if(l1!=NULL){
                sum+=l1->val;
                l1=l1->next;
            }
            if(l2!=NULL){
                sum+=l2->val;
                l2=l2->next;
            }
            sum+=carry;
            carry=sum/10;
            ListNode* node=new ListNode(sum%10);
            temp->next=node;
            temp=temp->next;
        }
        return dummy->next;
    }
};
```

**Time:** O(max(N, M)) · **Space:** O(max(N, M)) for the result.

### Why the loop condition covers everything
- `l1 || l2` → keep going while **either** list still has digits (handles unequal lengths — the shorter one just contributes 0).
- `|| carry` → even after both lists end, a leftover carry needs one more node (`999 + 1` style). Without it, the final digit is dropped.
- Dummy node means `temp->next` is always valid — no "first node?" special case; return `dummy->next`.

### Dry Run
`l1: 2->4->3`, `l2: 5->6->4`:

| l1 | l2 | carry in | sum | node | carry out |
|----|----|----------|-----|------|-----------|
| 2 | 5 | 0 | 7 | 7 | 0 |
| 4 | 6 | 0 | 10 | 0 | 1 |
| 3 | 4 | 1 | 8 | 8 | 0 |
| — | — | 0 | stop | | |

**Result:** `7 -> 0 -> 8` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "LSD-first → add heads directly. Loop `while(l1||l2||carry)`: sum digits+carry, node=`sum%10`, carry=`sum/10`. Dummy builds result."

---

## 📝 Short Revision Notes

- Digits already reversed (LSD-first) → **no reversal** needed (unlike Add-One P22).
- Loop condition must include `|| carry` for the final carry node.
- Unequal lengths handled by guarding each `l1`/`l2` add.
- Dummy node → clean build, return `dummy->next`.

---

## ⚠️ Common Mistakes

❌ Dropping `|| carry` from the loop → loses the final carry digit.
❌ Assuming equal lengths → crash / wrong sum on unequal lists.
❌ Forgetting to advance `temp` after appending.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "add two numbers as lists (LSD-first)", "digit-wise addition with carry" → **parallel walk + dummy + carry**.

---

## 📚 Related Problems

- [ ] LeetCode #445 — Add Two Numbers II (MSD-first → reverse first or use stacks)
- [ ] Step 6 P22 — Add One to LL (MSD-first, needs reverse/recursion)

---

## 🏆 Pattern Category

`Linked List` · `Dummy Node` · `Carry Propagation`

---

## ⏱️ 30-Second Last-Minute Revision

> **Add two numbers (LSD-first):** `while(l1||l2||carry){ sum=(l1?)+(l2?)+carry; carry=sum/10; append(sum%10); }` return `dummy->next`. O(max(N,M)).
