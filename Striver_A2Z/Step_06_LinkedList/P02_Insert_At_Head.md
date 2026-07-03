# 🔥 Insert at the Head of Linked List

> **Concept Problem** · **Difficulty:** Easy · **Step 6 — Linked List · P02**

---

## 🧠 Problem Understanding

**What is it asking?**
Given the `head` of a singly linked list and a value, insert a **new node at the front** so it becomes the new head, then return the new head.

**Key Observation:**
Inserting at the head is the cheapest operation on a linked list — **O(1)**. No traversal needed. The new node's `next` simply points to the old head; the new node *is* the new head.

**Simple Example:**
```
Before:  2 -> 3          insert 1 at head
After:   1 -> 2 -> 3
```

---

## 🎯 Interview Progression

### 🥇 Optimal — Point New Node to Old Head

> 💡 Create the node with its `next` already pointing to the current `head` (the two-arg constructor does exactly this), then return it as the new head. Order matters: the new node must grab the old head *before* we reassign.

```cpp
class Solution {
public:
    Node* insertAtHead(Node* head,int newData){
        Node* newNode=new Node(newData,head);
        return newNode;
    }

    void printList(Node* head){
        Node* temp=head;
        while(temp!=nullptr){
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
};
```

**Time:** O(1) · **Space:** O(1).

### Why it works
- `new Node(newData, head)` allocates the node **and** sets `next = head` in one step — the new node now leads the existing chain.
- Returning `newNode` makes the caller reassign `head = insertAtHead(...)`. If you forget to capture the return, the head pointer in `main` still points at the old first node and the insert is "lost."
- Works even on an **empty list** (`head == nullptr`): the new node's `next` becomes `nullptr` → a valid single-node list.

### Dry Run
`head: 2 -> 3`, insert `1`:

| Step | Action | List |
|------|--------|------|
| 1 | `newNode = Node(1, head)` → next = node(2) | `1 -> 2 -> 3` |
| 2 | `return newNode` → caller sets `head = newNode` | `1 -> 2 -> 3` ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "New node's `next` = old head, return new node. O(1). Caller must do `head = insertAtHead(...)`."

---

## 📝 Short Revision Notes

- Head insertion = **O(1)**, no traversal.
- The two-arg constructor `Node(val, head)` does the linking in one line.
- Must **return and reassign** the head — otherwise the caller loses the update.
- Handles empty list automatically (`next` ends up `nullptr`).

---

## ⚠️ Common Mistakes

❌ Setting `newNode->next` **after** reassigning `head` → you point the new node at itself / lose the list.
❌ Not capturing the return in `main` (`head = ...`) → the head still points to the old first node.
❌ Manually writing `newNode->next = head; head = newNode;` but in the wrong order.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "add to front", "push to a stack built on a list", "prepend" → **O(1) head insert**: new node's `next` = head, return new node.

---

## 🏆 Pattern Category

`Linked List` · `Insertion` · `Pointers`

---

## ⏱️ 30-Second Last-Minute Revision

> **Head insert = O(1).** `newNode = new Node(val, head); return newNode;`. Caller reassigns `head`. Works on empty list too.
