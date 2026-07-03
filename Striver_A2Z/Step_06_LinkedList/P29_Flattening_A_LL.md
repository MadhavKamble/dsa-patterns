# 🔥 Flattening a Linked List

> **Concept Problem (GfG)** · **Difficulty:** Medium/Hard · **Step 6 — Linked List · P29**

---

## 🧠 Problem Understanding

**What is it asking?**
A list where each node has a `next` (right) pointer and a `child` (down) pointer. Each **child sub-list is sorted**. Flatten everything into a single **sorted** list linked entirely through `child` pointers.

**Key Observation:**
This is **merge k sorted lists** in disguise. Recurse to the rightmost column, then merge each column into the accumulated result from the right, using the `child` pointer as the "next" during the merge.

**Simple Example:**
```
5 -> 10 -> 12 -> 7
|     |     |     |
14    4    20    17
            |
            13

Flattened: 4 -> 5 -> 7 -> 10 -> 12 -> 13 -> 14 -> 17 -> 20
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Recursive Merge from the Right

> 💡 `flattenLinkedList` recurses to the end via `next`, then merges the current vertical list with the already-flattened result. `merge` is the standard two-list merge but threads nodes through `child` (and nulls out `next`).

```cpp
class Solution {
private:
    ListNode* merge(ListNode* list1,ListNode* list2){
        ListNode* dummyNode=new ListNode(-1);
        ListNode* res=dummyNode;
        while(list1!=NULL&&list2!=NULL){
            if(list1->val<list2->val){
                res->child=list1;
                res=list1;
                list1=list1->child;
            }else{
                res->child=list2;
                res=list2;
                list2=list2->child;
            }
            res->next=NULL;
        }
        if(list1){
            res->child=list1;
        }else{
            res->child=list2;
        }
        if(dummyNode->child){
            dummyNode->child->next=NULL;
        }
        return dummyNode->child;
    }

public:
    ListNode* flattenLinkedList(ListNode* head){
        if(head==NULL||head->next==NULL){
            return head;
        }
        ListNode* mergedHead=flattenLinkedList(head->next);
        head=merge(head,mergedHead);
        return head;
    }
};
```

**Time:** O(N × M) where N = columns, M = total nodes (each merge scans the growing result) · **Space:** O(N) recursion depth.

### Why merge from the right
- Recursion first flattens `head->next` (everything to the right), returning one sorted `child`-linked list.
- Then the current column (`head` and its children) is merged into that result. Merging right-to-left keeps each merge between one small column and the sorted accumulation.
- The merge uses `child` as the forward link (`list1 = list1->child`) and nulls `next` so the output is purely vertical — no stray horizontal links to form cycles.

### Dry Run (structure)
Rightmost column `7 -> 17` stays; merge column `12 -> 20 -> 13` → sorted; keep merging leftward until the head column `5 -> 14` merges into the full sorted chain → `4 5 7 10 12 13 14 17 20` ✅

---

## 🚀 Alternative

| Approach | Time | Space | Idea |
|----------|------|-------|------|
| **Recursive merge (this)** | O(N·M) | O(N) stack | Merge columns right→left |
| Collect + sort | O(M log M) | O(M) | Dump all vals, sort, rebuild — ignores pre-sorted columns |
| Min-heap of k columns | O(M log N) | O(N) | Push column heads, pop min, advance |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Recurse right via next, merge each column into result through child pointers, null out next. It's merge-k-sorted-lists. O(N·M)."

---

## 📝 Short Revision Notes

- Columns (child chains) are pre-sorted → merge, don't re-sort.
- Merge threads through **child**, sets **next = NULL**.
- Recurse to rightmost, merge back leftward.
- Dummy node builds each merged result; break trailing `next` to avoid cycles.

---

## ⚠️ Common Mistakes

❌ Merging via `next` instead of `child` → wrong final linkage.
❌ Not nulling `next` on merged nodes → horizontal links create cycles.
❌ Forgetting the base case `head->next == NULL` → infinite recursion.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "flatten multi-level / child-pointer list", "merge k sorted vertical lists" → **recursive merge from the right through child**.

---

## 📚 Related Problems

- [ ] LeetCode #23 — Merge k Sorted Lists
- [ ] LeetCode #21 — Merge Two Sorted Lists

---

## 🏆 Pattern Category

`Linked List` · `Merge` · `Recursion` · `Multi-level`

---

## ⏱️ 30-Second Last-Minute Revision

> **Flatten LL:** recurse `flatten(head->next)`, then `merge(head, rest)` through **child** pointers (null the `next`). Merge-k-sorted. O(N·M), O(N) stack.
