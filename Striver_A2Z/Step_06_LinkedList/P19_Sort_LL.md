# 🔥 Sort a Linked List

> **LeetCode #148** · **Difficulty:** Medium · **Step 6 — Linked List · P19**

---

## 🧠 Problem Understanding

**What is it asking?**
Sort a singly linked list in ascending order. Target: **O(N log N)** time, **O(1)** extra (ignoring recursion stack).

**Key Observation:**
**Merge sort** is the natural fit for linked lists — splitting by finding the middle and merging two sorted lists are both O(N) and pointer-only (no random access needed, unlike quicksort). This beats "dump to array, sort, rebuild" on elegance and doesn't need O(N) array space.

**Simple Example:**
```
3 -> 2 -> 5 -> 4 -> 1   →   1 -> 2 -> 3 -> 4 -> 5
```

---

## 🎯 Interview Progression

### 🥉 Brute — Copy Values, Sort, Rewrite

> Collect data into a vector, `sort()`, write back. O(N log N) time but O(N) space.

### 🥇 Optimal — Merge Sort on the List

> 💡 Three pieces: **findMiddle** (slow/fast), **split** at the middle, recurse on both halves, **merge** two sorted lists with a dummy node.

```cpp
class Solution {
public:
    Node* mergeTwoSortedLinkedLists(Node* list1,Node* list2){
        Node* dummyNode=new Node(-1);
        Node* temp=dummyNode;
        while(list1!=nullptr&&list2!=nullptr){
            if(list1->data<=list2->data){
                temp->next=list1;
                list1=list1->next;
            }else{
                temp->next=list2;
                list2=list2->next;
            }
            temp=temp->next;
        }
        if(list1!=nullptr){
            temp->next=list1;
        }else{
            temp->next=list2;
        }
        return dummyNode->next;
    }

    Node* findMiddle(Node* head){
        if(head==nullptr||head->next==nullptr){
            return head;
        }
        Node* slow=head;
        Node* fast=head->next;
        while(fast!=nullptr&&fast->next!=nullptr){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;
    }

    Node* sortLL(Node* head){
        if(head==nullptr||head->next==nullptr){
            return head;
        }
        Node* middle=findMiddle(head);
        Node* right=middle->next;
        middle->next=nullptr;
        Node* left=head;
        left=sortLL(left);
        right=sortLL(right);
        return mergeTwoSortedLinkedLists(left,right);
    }
};
```

**Time:** O(N log N) · **Space:** O(log N) recursion stack.

### Why `fast=head->next` in findMiddle here
For merge sort we need the middle-finder to return the **first middle / end of the left half** so the split `middle->next` gives a non-empty right half. Starting `fast=head->next` makes slow stop at the left-half's last node — critical: starting `fast=head` on a 2-node list would put slow on the 2nd node, giving an empty right half → **infinite recursion**.

### Dry Run (high level)
`3 2 5 4 1` → split `3 2` | `5 4 1` → sort each → merge. Recursion bottoms out at single nodes; merges rebuild sorted: `2 3` and `1 4 5` → `1 2 3 4 5` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Merge sort: findMiddle (fast=head->next), split `middle->next=null`, recurse both halves, merge with dummy. O(N log N)."

---

## 📝 Short Revision Notes

- Merge sort > quicksort for lists (no random access; stable, guaranteed N log N).
- Split via `middle->next=nullptr` after finding the middle.
- `findMiddle` must start `fast=head->next` → non-empty right half → avoids infinite recursion on size-2.
- Merge uses a dummy node; attach the leftover tail directly (already sorted).

---

## ⚠️ Common Mistakes

❌ `fast=head` in findMiddle → 2-node list never splits → infinite recursion / stack overflow.
❌ Forgetting `middle->next=nullptr` → the two halves stay linked, merge misbehaves.
❌ Not attaching the remaining list after the merge `while` loop.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "sort a linked list in O(N log N)", "merge k lists" → **merge sort / merge two sorted lists** with dummy node.

---

## 🏆 Pattern Category

`Linked List` · `Merge Sort` · `Divide & Conquer` · `Two Pointers`

---

## ⏱️ 30-Second Last-Minute Revision

> **Sort LL = merge sort.** findMiddle (`fast=head->next`) → split `middle->next=null` → recurse → merge with dummy. O(N log N), O(log N) stack.
