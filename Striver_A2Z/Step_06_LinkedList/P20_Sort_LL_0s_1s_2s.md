# 🔥 Sort a Linked List of 0s, 1s and 2s (by Changing Links)

> **Concept Problem** · **Difficulty:** Easy/Medium · **Step 6 — Linked List · P20**

---

## 🧠 Problem Understanding

**What is it asking?**
The list contains only values `0`, `1`, `2`. Sort it — but by **rearranging links**, not by swapping data.

**Key Observation:**
Three **dummy chains** (zeros, ones, twos). One pass distributes each node into its bucket by value; then stitch `zero → one → two`. Handle empty buckets when connecting.

**Simple Example:**
```
Input:  1 -> 2 -> 0 -> 1 -> 2 -> 0
Output: 0 -> 0 -> 1 -> 1 -> 2 -> 2
```

---

## 🎯 Interview Progression

### 🥉 Brute — Count and Overwrite Data

> Count 0s/1s/2s, then rewrite node `data` in order. O(2N) but changes **data**, not links (often disallowed by the "change links" constraint).

### 🥇 Optimal — Three Dummy Chains, Relink

> 💡 Bucket each node by value onto `zeroTail`/`oneTail`/`twoTail`. Stitch the three, using the conditional so an empty ones-list is skipped, and terminate with `twoTail->next = nullptr`.

```cpp
void sortZeroOneTwo(LinkedList& ll){
    Node* zeroDummy=new Node(-1);
    Node* oneDummy=new Node(-1);
    Node* twoDummy=new Node(-1);
    Node* zeroTail=zeroDummy;
    Node* oneTail=oneDummy;
    Node* twoTail=twoDummy;
    Node* curr=ll.head;
    while(curr){
        if(curr->data==0){
            zeroTail->next=curr;
            zeroTail=zeroTail->next;
        }else if(curr->data==1){
            oneTail->next=curr;
            oneTail=oneTail->next;
        }else{
            twoTail->next=curr;
            twoTail=twoTail->next;
        }
        curr=curr->next;
    }
    zeroTail->next=oneDummy->next?oneDummy->next:twoDummy->next;
    oneTail->next=twoDummy->next;
    twoTail->next=nullptr;
    ll.head=zeroDummy->next;
    delete zeroDummy;
    delete oneDummy;
    delete twoDummy;
}
```

**Time:** O(N) single pass · **Space:** O(1).

### Why the conditional stitch
- `zeroTail->next = oneDummy->next ? oneDummy->next : twoDummy->next;` — if there are **no 1s**, jump zeros straight to the 2s so we don't leave the ones-dummy (`-1`) sentinel in the chain.
- `twoTail->next = nullptr` is essential: the last node kept its **old** `next` from the original list, which could point back into the middle → cycle if not cut.
- One-pass link change beats the count-and-overwrite when the interviewer says "don't modify data."

### Dry Run
`1 2 0 1 2 0`:
- zeros: `0 -> 0`, ones: `1 -> 1`, twos: `2 -> 2`
- stitch: zeroTail→ones→twos, twoTail→null → `0 0 1 1 2 2` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Three dummy chains by value, stitch zero→one→two (skip empty ones), `twoTail->next=null`. O(N) one pass."

---

## 📝 Short Revision Notes

- Three buckets, tail pointers, one pass.
- Conditional stitch handles a missing 1s list.
- **Must** null-terminate the twos tail (old links create cycles).
- Change-links version keeps node identities; count-overwrite changes data.

---

## ⚠️ Common Mistakes

❌ Forgetting `twoTail->next = nullptr` → cycle from leftover original links.
❌ Unconditional `zeroTail->next = oneDummy->next` when there are no 1s → leaves the `-1` sentinel in the list.
❌ Losing the head — set `ll.head = zeroDummy->next` (skip sentinel).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "sort list of 0/1/2", "Dutch National Flag on a list", "3-way partition by links" → **three dummy chains**.

---

## 📚 Related Problems

- [ ] Dutch National Flag (array version, 3-pointer)
- [ ] LeetCode #86 — Partition List (2-way link partition)

---

## 🏆 Pattern Category

`Linked List` · `Dummy Node` · `3-Way Partition`

---

## ⏱️ 30-Second Last-Minute Revision

> **Sort 0/1/2 links:** three dummy chains by value, stitch zero→one→two (conditional if no 1s), `twoTail->next=null`, `head=zeroDummy->next`. O(N)/O(1).
