# 🔥 Copy List with Random Pointers

> **LeetCode #138** · **Difficulty:** Medium/Hard · **Step 6 — Linked List · P30**

---

## 🧠 Problem Understanding

**What is it asking?**
Deep-copy a list where each node has `next` **and** a `random` pointer (to any node or null). The copy must be fully independent — no pointers into the original.

**Key Observation:**
The hard part is `random`: you can't set a copy's random until every copy exists. The **O(1)-space trick**: interleave each copy **right after** its original (`A → A' → B → B' → …`). Then `original->random->next` *is* the copy's random. Finally, unweave the two lists.

**Simple Example:**
```
Original: A → B → C  (with random links)
Weave:    A → A' → B → B' → C → C'
Result:   A' → B' → C' (independent copy)
```

---

## 🎯 Interview Progression

### 🥉 Brute — Hash Map old→new

> Map every original node to its copy, then a second pass wires `copy->next` and `copy->random` via the map. O(N) time, **O(N) space**.

### 🥇 Optimal — Interleave, Link Random, Detach (O(1) space)

> 💡 Three passes: (1) insert each copy between original and its next; (2) set each copy's `random = original->random->next`; (3) separate the woven list back into original + copy.

```cpp
class Solution {
public:
    void insertCopyInBetween(Node* head){
        Node* temp=head;
        while(temp){
            Node* nextElement=temp->next;
            Node* copy=new Node(temp->val);
            copy->next=nextElement;
            temp->next=copy;
            temp=nextElement;
        }
    }

    void connectRandomPointer(Node* head){
        Node* temp=head;
        while(temp){
            Node* copyNode=temp->next;
            if(temp->random){
                copyNode->random=temp->random->next;
            }else{
                copyNode->random=nullptr;
            }
            temp=temp->next->next;
        }
    }

    Node* getDeepCopyList(Node* head){
        Node* temp=head;
        Node* dummyNode=new Node(-1);
        Node* res=dummyNode;
        while(temp){
            res->next=temp->next;
            res=res->next;
            temp->next=temp->next->next;
            temp=temp->next;
        }
        return dummyNode->next;
    }

    Node* copyRandomList(Node* head){
        if(!head) return nullptr;
        insertCopyInBetween(head);
        connectRandomPointer(head);
        return getDeepCopyList(head);
    }
};
```

**Time:** O(N) (three linear passes) · **Space:** O(1) extra (besides the copy itself).

### Why the interleave makes random trivial
- After weaving, every copy sits **directly after** its original. So for original `X`, its copy is `X->next`, and the copy of `X->random` is `X->random->next`. That's the whole insight: `copyNode->random = temp->random->next`.
- Guard `temp->random == nullptr` → copy's random stays null.
- The detach pass restores each original's `next` (`temp->next = temp->next->next`) **and** builds the copy chain via the dummy — leaving the original list exactly as it was.

### Dry Run (random linking)
Weave `A → A' → B → B'`. If `A->random = B`, then `A'->random = A->random->next = B->next = B'` ✅ — copy points to copy, not original.

---

## 🚀 Approach Comparison

| Approach | Time | Space | Note |
|----------|------|-------|------|
| Hash map old→new | O(N) | O(N) | Easiest to reason about |
| **Interleave + detach** | O(N) | O(1) | Optimal, no extra map |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Weave copies (A→A'→B→B'). Copy random = `orig->random->next`. Detach into two lists. O(1) space."

---

## 📝 Short Revision Notes

- Three passes: insert copies, link randoms via `orig->random->next`, detach.
- Interleaving is what makes `random` computable in O(1) space.
- Detach must **restore** the original list's `next` too.
- Hash-map version is the O(N)-space fallback if asked for something simpler.

---

## ⚠️ Common Mistakes

❌ Setting `copy->random = temp->random` (points to original, not copy).
❌ Not guarding `temp->random == nullptr` → null deref.
❌ Detach pass forgetting to relink the original's `next` → corrupts the input list.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "deep copy with random/arbitrary pointer", "clone graph-like list in O(1) space" → **interleave copies + detach**.

---

## 🏆 Pattern Category

`Linked List` · `Interleaving` · `Deep Copy`

---

## ⏱️ 30-Second Last-Minute Revision

> **Copy random list:** weave `A→A'→B→B'`, set `copy->random = orig->random->next`, then detach into original + copy. O(N) time, O(1) space.
