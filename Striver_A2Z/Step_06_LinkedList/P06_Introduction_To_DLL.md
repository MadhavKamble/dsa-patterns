# 🔥 Introduction to Doubly Linked List (DLL)

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P06**

---

> ⚠️ **Note on the pasted snippet:** the code sent for this problem was the *singly* LL node (only `next`). A **doubly** linked list node needs a **`back`** (previous) pointer too. This note uses the correct DLL node — the same one used in your P07 code.

---

## 🧠 Problem Understanding

**What is it asking?**
Understand the **doubly linked list** node — like a singly LL node but with an extra `back` (a.k.a. `prev`) pointer to the **previous** node. Build a DLL from an array and traverse it.

**Singly vs Doubly:**
- **Singly LL:** each node → `next` only. Can move **forward** only.
- **Doubly LL:** each node → `next` **and** `back`. Can move **both directions**. Costs one extra pointer per node (more memory), but makes deletion / backward traversal O(1) when you already hold the node.

**Key Observations:**
- Head node's `back` is `nullptr`; tail node's `next` is `nullptr`.
- Every internal link is **two-way**: if `a->next == b` then `b->back == a`. Keeping this invariant consistent is the whole game in DLL problems.

**Simple Example:**
```
arr = {12, 5, 8, 7, 4}

NULL◄─┤12│◄─►│5│◄─►│8│◄─►│7│◄─►│4├─►NULL
       head                        tail
```

---

## 🎯 Interview Progression

### 🥇 The DLL Node + Array→DLL Conversion

> 💡 The node carries `data`, `next`, `back`. When building from an array, each new node's `back` points to the previous node, and the previous node's `next` points to the new node — wire **both** directions every time.

```cpp
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* back;

    Node(int data1,Node* next1,Node* back1){
        data=data1;
        next=next1;
        back=back1;
    }

    Node(int data1){
        data=data1;
        next=nullptr;
        back=nullptr;
    }
};

Node* convertArr2DLL(vector<int> arr){
    Node* head=new Node(arr[0]);
    Node* prev=head;
    for(int i=1;i<arr.size();i++){
        Node* temp=new Node(arr[i],nullptr,prev);
        prev->next=temp;
        prev=temp;
    }
    return head;
}

void print(Node* head){
    while(head!=nullptr){
        cout<<head->data<<" ";
        head=head->next;
    }
}
```

**Time:** O(N) to build · **Space:** O(N) for the nodes.

### Why the wiring works
- `new Node(arr[i], nullptr, prev)` sets the new node's `back = prev` immediately.
- `prev->next = temp` closes the forward link. Now `prev ⇄ temp` is a valid two-way bond.
- `prev = temp` advances the builder to the new tail.
- Head's `back` stays `nullptr` (single-arg constructor); the current tail's `next` stays `nullptr` until the next iteration attaches to it.

---

## 🧾 Recall Line *(10-Second Revision)*

> "DLL node = data + next + back. Build: new node's `back=prev`, then `prev->next=new`, then `prev=new`. Two-way links everywhere."

---

## 📝 Short Revision Notes

- DLL = singly LL **+ `back` pointer** per node → bidirectional traversal.
- Invariant: `a->next==b` ⇔ `b->back==a`. Keep it consistent on every insert/delete.
- Head's `back==nullptr`, tail's `next==nullptr`.
- Extra pointer = more memory, but O(1) delete/insert when the node is in hand.

---

## ⚠️ Common Mistakes

❌ Wiring only `prev->next=temp` and forgetting `temp->back=prev` (or vice-versa) → broken back-traversal.
❌ Forgetting head's `back` must be `nullptr`.
❌ Using the singly-LL node (no `back`) for a DLL problem.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "traverse backward", "delete a node given only its pointer in O(1)", "LRU cache" → **doubly linked list** with `next` + `back`.

---

## 🏆 Pattern Category

`Linked List` · `Doubly Linked List` · `Pointers`

---

## ⏱️ 30-Second Last-Minute Revision

> **DLL node = data + next + back.** Build from array: `temp=new Node(arr[i],nullptr,prev); prev->next=temp; prev=temp;`. Invariant `a->next==b ⇔ b->back==a`.
