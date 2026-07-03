# 🔥 Reverse Nodes in K-Group

> **LeetCode #25** · **Difficulty:** Hard · **Step 6 — Linked List · P27**

---

## 🧠 Problem Understanding

**What is it asking?**
Reverse the list **k nodes at a time**. If the last chunk has fewer than k nodes, leave it as-is.

**Key Observation:**
Process group by group. For each group: find the **kth node** (if it doesn't exist, the remaining tail stays untouched). Cut the group off, reverse it, then reconnect: the previous group's tail (`prevLast`) links to the group's new head (`kthNode`), and this group's new tail (`temp`, the old head) becomes the next `prevLast`.

**Simple Example:**
```
k=2:  1 -> 2 -> 3 -> 4 -> 5   →   2 -> 1 -> 4 -> 3 -> 5
k=3:  1 -> 2 -> 3 -> 4 -> 5   →   3 -> 2 -> 1 -> 4 -> 5   (last 2 kept)
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Group-wise Reverse with Reconnection

> 💡 Helpers: `getKthNode` walks k−1 steps; `reverseLinkedList` is the standard 3-pointer reverse. Main loop cuts each group at `kthNode->next`, reverses it, and stitches it back between `prevLast` and `nextNode`.

```cpp
class Solution {
public:
    ListNode* getKthNode(ListNode* temp,int k){
        k-=1;
        while(temp&&k>0){
            k--;
            temp=temp->next;
        }
        return temp;
    }

    ListNode* reverseLinkedList(ListNode* head){
        ListNode* temp=head;
        ListNode* prev=nullptr;
        while(temp!=nullptr){
            ListNode* front=temp->next;
            temp->next=prev;
            prev=temp;
            temp=front;
        }
        return prev;
    }

    ListNode* reverseKGroup(ListNode* head,int k){
        ListNode* temp=head;
        ListNode* prevLast=nullptr;
        while(temp!=nullptr){
            ListNode* kthNode=getKthNode(temp,k);
            if(!kthNode){
                if(prevLast) prevLast->next=temp;
                break;
            }
            ListNode* nextNode=kthNode->next;
            kthNode->next=nullptr;
            reverseLinkedList(temp);
            if(temp==head){
                head=kthNode;
            }else{
                prevLast->next=kthNode;
            }
            prevLast=temp;
            temp=nextNode;
        }
        return head;
    }
};
```

**Time:** O(N) — each node reversed once · **Space:** O(1).

### Why the reconnection logic
- After `kthNode->next=nullptr` + `reverseLinkedList(temp)`: `kthNode` is the group's **new head**, `temp` (old first node) becomes the group's **new tail**.
- First group → `head = kthNode` (new overall head). Later groups → `prevLast->next = kthNode` bridges from the previous group.
- `prevLast = temp` remembers this group's tail so the **next** group can attach to it. `temp = nextNode` jumps to the start of the next group.
- Incomplete final group: `getKthNode` returns `nullptr` → we reattach the untouched tail via `prevLast->next = temp` and break.

### Dry Run
`1 2 3 4 5`, k=2:
- Group1 `1,2`: kth=2, reverse → `2->1`, head=2, prevLast=node1, temp=3.
- Group2 `3,4`: kth=4, reverse → `4->3`, node1->next=4, prevLast=node3, temp=5.
- Group3 `5`: getKthNode(5,2)=null → prevLast(node3)->next=5, break.

**Result:** `2 -> 1 -> 4 -> 3 -> 5` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Per group: find kth (null → leave tail). Cut, reverse. Link prevLast→kthNode (new head), prevLast=old head. O(N)."

---

## 📝 Short Revision Notes

- After reversing a group: `kthNode`=new head, `temp`=new tail.
- Track `prevLast` to bridge consecutive groups.
- Incomplete last group (< k) stays in original order.
- `getKthNode` returns null when fewer than k nodes remain.

---

## ⚠️ Common Mistakes

❌ Reversing the incomplete last group (spec says keep it).
❌ Forgetting `kthNode->next=nullptr` before reversing → reverses the whole rest.
❌ Not updating `head` for the first group → returns old head.
❌ Losing `nextNode` (start of next group) before cutting.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "reverse every k nodes", "reverse in blocks", "swap pairs (k=2)" → **group-wise reverse with prevLast reconnection**.

---

## 📚 Related Problems

- [ ] LeetCode #24 — Swap Nodes in Pairs (k=2 special case)
- [ ] LeetCode #206 — Reverse Linked List (single group)

---

## 🏆 Pattern Category

`Linked List` · `Reversal` · `Groups`

---

## ⏱️ 30-Second Last-Minute Revision

> **Reverse K-group:** loop groups — find kth (null → attach tail, break), cut `kthNode->next=null`, reverse, link `prevLast->next=kthNode`, `prevLast=oldHead`, jump to next. O(N)/O(1).
