# 🔥 Introduction to Linked List

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P01**

---

## 🧠 Problem Understanding

**What is it asking?**
Understand the fundamental building block of a linked list — the **Node** — and how nodes chain together via pointers instead of contiguous memory (as arrays do). Build the first node from an array and access its address and data.

**Array vs Linked List:**
- **Array:** elements sit in **contiguous** memory. Random access `arr[i]` is O(1), but insertion/deletion in the middle shifts elements → O(N).
- **Linked List:** elements (`Node`s) are scattered in memory, each holding its **data** plus a **pointer** to the next node. No random access, but insert/delete at a known position is O(1).

**Key Observations:**
- A `Node` bundles two things: the **value** (`data`) and the **address of the next node** (`next`).
- The last node's `next` is `nullptr` — that's how we know the list has ended.
- We only ever hold a pointer to the **head**; everything else is reached by following `next`.

**Simple Example:**
```
arr = {2, 5, 8, 7}

[2|•]──►[5|•]──►[8|•]──►[7|NULL]
 head
```

---

## 🎯 Interview Progression

### 🥇 The Node Class

> 💡 A node is a self-referential struct/class: it stores an `int data` and a `Node* next` **pointer to its own type**. Two constructors give convenience — one when you know the next node, one when it's a standalone/tail node (`next = nullptr`).

```cpp
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int data1,Node* next1){
        data=data1;
        next=next1;
    }

    Node(int data1){
        data=data1;
        next=nullptr;
    }
};

int main(){
    vector<int> arr={2,5,8,7};

    Node* y=new Node(arr[0]);

    cout<<y<<'\n';
    cout<<y->data<<'\n';

    return 0;
}
```

**Time:** O(1) to create one node · **Space:** O(1).

### What each line does
- `Node* y = new Node(arr[0]);` — `new` allocates a node on the **heap** and returns its address; `y` holds that address. This node stores `data=2`, `next=nullptr`.
- `cout << y;` — prints the **memory address** the pointer holds (e.g. `0x561...`), not the value.
- `cout << y->data;` — dereferences the pointer and reads the `data` field → `2`. `y->data` is shorthand for `(*y).data`.

---

## 🔗 Convert the Whole Array into a Linked List

> This is the natural next step and the real "intro" pattern — build the full chain, not just one node.

```cpp
Node* convertArrToLL(vector<int>& arr){
    Node* head=new Node(arr[0]);
    Node* mover=head;
    for(int i=1;i<arr.size();i++){
        Node* temp=new Node(arr[i]);
        mover->next=temp;
        mover=temp;
    }
    return head;
}
```

- `head` is fixed — it's what we return, the entry point of the list.
- `mover` walks along the tail so we can attach each new node in O(1) without re-traversing.

### Traverse & Print

```cpp
void print(Node* head){
    Node* temp=head;
    while(temp!=nullptr){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
}
```

### Length of the List

```cpp
int lengthOfLL(Node* head){
    int cnt=0;
    Node* temp=head;
    while(temp!=nullptr){
        cnt++;
        temp=temp->next;
    }
    return cnt;
}
```

### Search for an Element

```cpp
bool searchInLL(Node* head,int val){
    Node* temp=head;
    while(temp!=nullptr){
        if(temp->data==val) return true;
        temp=temp->next;
    }
    return false;
}
```

**Traverse / length / search:** each is **O(N)** time, **O(1)** space.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Node = data + `next` pointer. `new Node(...)` gives a heap address. Keep a fixed `head`, walk a `mover`/`temp` via `temp=temp->next` until `nullptr`."

---

## 📝 Short Revision Notes

- `y->data` = `(*y).data` → follow the pointer, read the field.
- Printing the pointer itself (`cout<<y`) shows the **address**, not the data.
- Always guard traversal with `while(temp!=nullptr)` — dereferencing `nullptr->next` is a crash.
- Never move `head` while traversing; use a separate `temp`/`mover`, or you lose the list.
- Last node's `next` **must** be `nullptr` — forgetting it in a manual build = infinite loop / garbage.

---

## ⚠️ Common Mistakes

❌ Moving `head` in the loop → you can no longer return/reprint the list.
❌ Dereferencing `temp->data` after `temp` becomes `nullptr` (loop check in wrong place).
❌ Forgetting `mover->next=temp` before `mover=temp` → nodes created but never linked.
❌ Confusing `y` (address) with `y->data` (value) when printing.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "build a list from an array", "traverse", "count nodes", "search" → **head-fixed + moving-temp** traversal skeleton (`while(temp) temp=temp->next`).

---

## 🏆 Pattern Category

`Linked List` · `Pointers` · `Traversal`

---

## ⏱️ 30-Second Last-Minute Revision

> **Node = data + next.** Build: fix `head`, walk `mover`, `mover->next=temp; mover=temp`. Traverse/length/search: `while(temp) temp=temp->next`, all `O(N)`. Tail's `next=nullptr`.
