# 🔥 Search an Element in a Linked List

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P05**

---

## 🧠 Problem Understanding

**What is it asking?**
Given the `head` of a singly linked list and a `key`, return whether the key exists in the list (`true`/`false`).

**Key Observation:**
No random access and (in general) no sorted order → the only option is **linear search**: walk every node, compare `data == key`, return early on the first match. **O(N)**.

**Simple Example:**
```
10 -> 20 -> 30, key=20  →  Found
10 -> 20 -> 30, key=40  →  Not Found
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Linear Scan with Early Exit

> 💡 Traverse from `head`; the moment `current->data == key`, return `true`. If we run off the end (`nullptr`), it's not there → `false`.

```cpp
struct Node {
    int data;
    Node* next;
    Node(int val):data(val),next(NULL){}
};

class Solution {
public:
    bool searchValue(Node* head,int key){
        Node* current=head;
        while(current!=NULL){
            if(current->data==key) return true;
            current=current->next;
        }
        return false;
    }
};
```

**Time:** O(N) worst case (key absent / at tail) · **Space:** O(1).

### Why it works
- **Early exit** on match avoids scanning the rest — best case O(1) if key is the head.
- Empty list → loop skipped → returns `false`. No special case.
- `struct Node` with an **initializer list** constructor `:data(val),next(NULL)` is just a compact alternative to assigning in the body — same result.

### Dry Run
`10 -> 20 -> 30`, `key = 20`:

| current | data==key? | Action |
|---------|-----------|--------|
| node(10) | 10==20 no | advance |
| node(20) | 20==20 yes | return **true** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Walk from head, `if(data==key) return true`, else advance; hit null → false. O(N)."

---

## 📝 Short Revision Notes

- Unsorted singly list → **linear search only**, O(N).
- Early return on first match; return `false` after the loop, not inside it.
- Empty list handled by the `while` guard automatically.
- Initializer-list constructor `Node(int v):data(v),next(NULL){}` ≡ body assignment.

---

## ⚠️ Common Mistakes

❌ Returning `false` inside the loop on the first mismatch → stops after checking one node.
❌ Comparing pointers (`current == key`) instead of `current->data == key`.
❌ Forgetting to advance `current` → infinite loop.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "does the list contain X", "find/locate a value in a list" → **linear traversal with early return**.

---

## 🏆 Pattern Category

`Linked List` · `Search` · `Traversal`

---

## ⏱️ 30-Second Last-Minute Revision

> **Search = O(N) linear.** `while(current){ if(data==key) return true; current=current->next; } return false;`. Early exit on match.
