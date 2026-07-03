# 🔥 Segregate Even and Odd Nodes in a Linked List

> **Concept Problem** · **Difficulty:** Easy/Medium · **Step 6 — Linked List · P16**

---

> ℹ️ **This variant groups by VALUE parity** (even-valued nodes first, then odd-valued). The LeetCode #328 "Odd Even Linked List" instead groups by **index/position** — see Related Problems.

---

## 🧠 Problem Understanding

**What is it asking?**
Rearrange the list so that all nodes with **even values** come first, followed by all nodes with **odd values**, preserving relative order within each group.

**Key Observation:**
Build **two separate chains** using dummy heads (even list, odd list). Detach each node from the original list and append it to the correct chain by parity, then **stitch** even→odd at the end. Using dummy nodes removes all "is this the first node?" edge cases.

**Simple Example:**
```
Input:  1 -> 2 -> 3 -> 4
Output: 2 -> 4 -> 1 -> 3     (evens 2,4 then odds 1,3)
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Two Dummy Chains

> 💡 `evenHead`/`oddHead` are dummy sentinels; `evenTail`/`oddTail` track where to append. Walk the original list, detach each node (`temp->next = nullptr`), append by `val & 1`. Finally link `evenTail->next = oddHead->next` and return `evenHead->next`.

```cpp
ListNode* SegregatetoOddEVen(){
    ListNode* oddHead=new ListNode(-1),*oddTail=oddHead;
    ListNode* evenHead=new ListNode(-1),*evenTail=evenHead;
    ListNode* curr=head,*temp;
    while(curr){
        temp=curr;
        curr=curr->next;
        temp->next=nullptr;
        if(temp->val&1){
            oddTail->next=temp;
            oddTail=temp;
        }else{
            evenTail->next=temp;
            evenTail=temp;
        }
    }
    evenTail->next=oddHead->next;
    return evenHead->next;
}
```

**Time:** O(N) single pass · **Space:** O(1) (reuses existing nodes; dummies are O(1)).

### Why dummy nodes help
- Without dummies you'd need `if(evenHead==nullptr) evenHead=evenTail=temp; else ...` on every append. The sentinel means `evenTail` always exists, so appends are unconditional.
- `temp->next = nullptr` on detach guarantees the last appended node in each chain terminates cleanly — critical so `evenTail->next = oddHead->next` doesn't accidentally leave a dangling old link.
- `val & 1` is a fast parity test: 1 for odd, 0 for even.

### Dry Run
`1 -> 2 -> 3 -> 4`:

| temp | parity | even chain | odd chain |
|------|--------|-----------|-----------|
| 1 | odd | -1 | -1→1 |
| 2 | even | -1→2 | -1→1 |
| 3 | odd | -1→2 | -1→1→3 |
| 4 | even | -1→2→4 | -1→1→3 |

Stitch: `evenTail(4)->next = oddHead->next(1)` → `2 -> 4 -> 1 -> 3` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Two dummy chains, append each node by `val&1`, then `evenTail->next=oddHead->next`, return `evenHead->next`. O(N)/O(1)."

---

## 📝 Short Revision Notes

- Dummy sentinel heads → unconditional appends, no first-node special case.
- Detach with `temp->next=nullptr` before appending.
- Stitch even→odd, return `evenHead->next` (skip the sentinel).
- Relative order preserved within each group.

---

## ⚠️ Common Mistakes

❌ Forgetting `temp->next=nullptr` → old links leak in, creating cycles/garbage tail.
❌ Returning `evenHead` (the dummy) instead of `evenHead->next`.
❌ Confusing value-parity with index-parity (LeetCode #328).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "partition/segregate a list into two groups by a predicate", "stable split" → **two dummy chains + stitch**.

---

## 📚 Related Problems

- [ ] LeetCode #328 — Odd Even Linked List (**by index**, not value)
- [ ] LeetCode #86 — Partition List (split around a value `x`, same dummy-chain trick)

---

## 🏆 Pattern Category

`Linked List` · `Dummy Node` · `Partitioning`

---

## ⏱️ 30-Second Last-Minute Revision

> **Segregate = two dummy chains.** Append each node by `val&1` to even/odd tail, `temp->next=nullptr` on detach, then `evenTail->next=oddHead->next; return evenHead->next;`. O(N)/O(1).
