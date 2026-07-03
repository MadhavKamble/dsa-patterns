# 🔥 Remove Duplicates from a Sorted DLL

> **Concept Problem** · **Difficulty:** Easy/Medium · **Step 6 — Linked List · P26**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **sorted** doubly linked list, remove duplicate values so each value appears once; return the head.

**Key Observation:**
Sorted → all copies of a value are **adjacent**. For each node, skip forward over every following node with the same value, deleting them, then reconnect `temp` to the first different node (fixing both `next` and `back`).

**Simple Example:**
```
Before:  1 ⇄ 1 ⇄ 3 ⇄ 3 ⇄ 3 ⇄ 4
After:   1 ⇄ 3 ⇄ 4
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Skip Adjacent Equals

> 💡 For each `temp`, walk `nextNode` forward while it equals `temp->data`, deleting each duplicate. Then link `temp->next = nextNode` and, if non-null, `nextNode->back = temp`. Advance `temp`.

```cpp
Node* removeDuplicates(Node* head){
    Node* temp=head;
    while(temp!=NULL&&temp->next!=NULL){
        Node* nextNode=temp->next;
        while(nextNode!=NULL&&nextNode->data==temp->data){
            Node* duplicate=nextNode;
            nextNode=nextNode->next;
            delete duplicate;
        }
        temp->next=nextNode;
        if(nextNode!=NULL) nextNode->back=temp;
        temp=temp->next;
    }
    return head;
}
```

**Time:** O(N) — each node visited/deleted once · **Space:** O(1).

### Why it works
- Sorted guarantees duplicates are contiguous, so a single inner sweep clears all copies of the current value.
- `delete duplicate` frees each removed node (no leak); we advance `nextNode` **before** deleting so we don't lose the chain.
- After the sweep, `temp->next = nextNode` and `nextNode->back = temp` restore the two-way DLL invariant. The `if(nextNode!=NULL)` guard handles duplicates running to the **tail**.
- `temp = temp->next` moves to the next distinct value.

### Dry Run
`1 ⇄ 1 ⇄ 3 ⇄ 3 ⇄ 4`:

| temp | inner sweep deletes | relink | next temp |
|------|---------------------|--------|-----------|
| 1 | second 1 | 1.next=3, 3.back=1 | 3 |
| 3 | second 3 | 3.next=4, 4.back=3 | 4 |
| 4 | none | (4.next=NULL) | NULL → stop |

**Result:** `1 ⇄ 3 ⇄ 4` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Sorted → dups adjacent. For each node skip+delete equal-valued next nodes, then `temp->next=nextNode; nextNode->back=temp`. O(N)."

---

## 📝 Short Revision Notes

- Works only because the list is **sorted** (dups adjacent).
- Advance `nextNode` before `delete` → no use-after-free.
- Restore **both** links (`next` and `back`); guard null at the tail.
- Single O(N) pass, O(1) space.

---

## ⚠️ Common Mistakes

❌ Deleting `nextNode` before advancing it → lose the rest of the chain.
❌ Forgetting `nextNode->back = temp` → backward chain broken.
❌ Missing the `nextNode != NULL` guard when duplicates reach the tail.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "remove duplicates from a sorted (doubly) list", "dedupe adjacent equals" → **skip-and-splice contiguous duplicates**.

---

## 📚 Related Problems

- [ ] LeetCode #83 — Remove Duplicates from Sorted List (singly)
- [ ] LeetCode #82 — Remove *all* nodes that have duplicates (keep only uniques)

---

## 🏆 Pattern Category

`Linked List` · `Doubly Linked List` · `Deletion`

---

## ⏱️ 30-Second Last-Minute Revision

> **Dedupe sorted DLL:** for each node, `while(nextNode->data==temp->data) delete & advance`, then `temp->next=nextNode; nextNode->back=temp;`. O(N)/O(1).
