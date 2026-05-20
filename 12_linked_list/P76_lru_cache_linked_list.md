# P76 — LRU Cache and Doubly Linked List Design

## 1. First-Timer Explanation

### What Is It?
**LRU Cache** (Least Recently Used) evicts the least recently accessed item when the cache is full. The key insight is combining a **doubly linked list** (for O(1) insert/delete anywhere) with a **hash map** (for O(1) lookup by key).

### Why Doubly Linked List?
- Singly linked: deleting a node requires traversing to find its predecessor — O(n)
- Doubly linked: each node knows its prev and next — delete in O(1) given the node pointer
- Hash map stores key → node pointer, so we can get a node in O(1) then delete it in O(1)

### Visual Walkthrough — LRU Get/Put
```
Cache capacity = 3. Operations: put(1,1), put(2,2), put(3,3), get(1), put(4,4)

After put(1,1): head ↔ [1] ↔ tail
After put(2,2): head ↔ [2] ↔ [1] ↔ tail    (most recent at front)
After put(3,3): head ↔ [3] ↔ [2] ↔ [1] ↔ tail

get(1) → returns 1, moves node 1 to front:
         head ↔ [1] ↔ [3] ↔ [2] ↔ tail

put(4,4) → cache full, evict LRU (tail's prev = node 2):
         head ↔ [4] ↔ [1] ↔ [3] ↔ tail
```

### Core Operations
```
addToFront(node): splice after dummy head
removeNode(node): splice around node (node.prev.next = node.next; node.next.prev = node.prev)
removeLast():    remove node before dummy tail (the LRU)
```

### When to Use
- "Design LRU Cache" → doubly linked list + hash map
- "O(1) insert, delete, lookup with ordering" → ordered doubly linked list
- "Doubly linked list manipulation" → dummy head + dummy tail simplify edge cases
- Any "most recently used" or "eviction policy" problem

### Common Mistakes
1. Forgetting to update the hash map when evicting (delete the evicted key from map)
2. Not using dummy head/tail — requires special-casing empty list and single element
3. In get(): must move accessed node to front, not just read it
4. In put(): if key exists, update value AND move to front before checking capacity

---

## 2. Revision Card

**Recognition Signal:** "LRU", "most recently used", "evict oldest", "O(1) cache"

**Core Idea:** Hash map (key→node) + doubly linked list (ordered by recency). Most recent at head, LRU at tail. On access: remove and re-add at front. On eviction: remove tail's predecessor.

**Trigger Keywords:** LRU, cache, evict, O(1) get/put, recently used

**Complexity:** O(1) get, O(1) put — both amortized

---

## 3. Interview Tell Signs

- "Design LRU Cache" → hash map + doubly linked list
- "Evict least recently used" → tail of DLL is LRU
- "O(1) access and insertion" → hash map provides key lookup, DLL provides O(1) reorder
- "Move to front on access" → remove from current position, insert at head
- "Design something with ordering + fast lookup" → consider DLL + hash map combo

---

## 4. C++ Template

```cpp
// ── LRU Cache ─────────────────────────────────────────────────────────────────
class LRUCache {
    struct Node {
        int key, val;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };

    int cap;
    unordered_map<int, Node*> mp; // key → node
    Node* head; // dummy head (most recent end)
    Node* tail; // dummy tail (LRU end)

    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

public:
    LRUCache(int capacity) : cap(capacity) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!mp.count(key)) return -1;
        Node* node = mp[key];
        removeNode(node);
        addToFront(node);
        return node->val;
    }

    void put(int key, int value) {
        if (mp.count(key)) {
            mp[key]->val = value;
            removeNode(mp[key]);
            addToFront(mp[key]);
        } else {
            if ((int)mp.size() == cap) {
                Node* lru = tail->prev; // least recently used
                removeNode(lru);
                mp.erase(lru->key);
                delete lru;
            }
            Node* node = new Node(key, value);
            addToFront(node);
            mp[key] = node;
        }
    }
};

// ── Design Linked List (Doubly) ───────────────────────────────────────────────
class MyLinkedList {
    struct Node { int val; Node* prev; Node* next; Node(int v): val(v),prev(nullptr),next(nullptr){} };
    Node* head; Node* tail; int sz;
public:
    MyLinkedList() : sz(0) { head = new Node(-1); tail = new Node(-1); head->next=tail; tail->prev=head; }
    int get(int idx) {
        if (idx<0||idx>=sz) return -1;
        Node* cur = head->next;
        while (idx--) cur=cur->next;
        return cur->val;
    }
    void addAtHead(int val) { addAtIndex(0, val); }
    void addAtTail(int val) { addAtIndex(sz, val); }
    void addAtIndex(int idx, int val) {
        if (idx>sz) return;
        Node* cur = head;
        while (idx--) cur=cur->next;
        Node* node = new Node(val);
        node->next = cur->next; node->prev = cur;
        cur->next->prev = node; cur->next = node;
        sz++;
    }
    void deleteAtIndex(int idx) {
        if (idx<0||idx>=sz) return;
        Node* cur = head->next;
        while (idx--) cur=cur->next;
        cur->prev->next=cur->next; cur->next->prev=cur->prev;
        delete cur; sz--;
    }
};
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I'll use a doubly linked list with dummy head and tail, plus a hash map from key to node pointer. The list maintains recency order: most recently used at head, LRU at tail. For get: look up node in map, move it to front (remove + re-add), return value. For put: if key exists, update and move to front. If new and at capacity, evict tail's predecessor (remove from list AND erase from map). Then insert new node at front."

**Checklist:**
- [ ] Dummy head + tail — avoids edge cases with empty list
- [ ] removeNode: fix both prev.next and next.prev links
- [ ] addToFront: insert after dummy head
- [ ] get(): move to front after accessing
- [ ] put(): handle existing key (update + reorder) before checking capacity
- [ ] Evict: erase from map first, then delete node memory

---

## 6. Problems

### Problem 1: LRU Cache
**Difficulty:** Medium | **LC:** 146

```cpp
class LRUCache {
    struct Node { int key, val; Node *prev, *next; Node(int k,int v):key(k),val(v),prev(nullptr),next(nullptr){} };
    int cap; unordered_map<int,Node*> mp; Node *head, *tail;
    void addFront(Node* n) { n->next=head->next; n->prev=head; head->next->prev=n; head->next=n; }
    void rem(Node* n) { n->prev->next=n->next; n->next->prev=n->prev; }
public:
    LRUCache(int c):cap(c){head=new Node(-1,-1);tail=new Node(-1,-1);head->next=tail;tail->prev=head;}
    int get(int k){ if(!mp.count(k)) return -1; rem(mp[k]); addFront(mp[k]); return mp[k]->val; }
    void put(int k,int v){
        if(mp.count(k)){mp[k]->val=v;rem(mp[k]);addFront(mp[k]);return;}
        if((int)mp.size()==cap){Node* l=tail->prev;rem(l);mp.erase(l->key);delete l;}
        Node* n=new Node(k,v); addFront(n); mp[k]=n;
    }
};
// Time: O(1) get, O(1) put | Space: O(capacity)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Design Linked List
**Difficulty:** Medium | **LC:** 707

```cpp
class MyLinkedList {
    struct Node { int val; Node* prev; Node* next; Node(int v):val(v),prev(nullptr),next(nullptr){} };
    Node *head, *tail; int sz;
public:
    MyLinkedList():sz(0){head=new Node(-1);tail=new Node(-1);head->next=tail;tail->prev=head;}
    int get(int i){ if(i<0||i>=sz) return -1; Node* c=head->next; while(i--) c=c->next; return c->val; }
    void addAtHead(int v){ addAtIndex(0,v); }
    void addAtTail(int v){ addAtIndex(sz,v); }
    void addAtIndex(int i,int v){
        if(i>sz) return;
        Node* c=head; while(i--) c=c->next;
        Node* n=new Node(v); n->next=c->next; n->prev=c; c->next->prev=n; c->next=n; sz++;
    }
    void deleteAtIndex(int i){
        if(i<0||i>=sz) return;
        Node* c=head->next; while(i--) c=c->next;
        c->prev->next=c->next; c->next->prev=c->prev; delete c; sz--;
    }
};
// Time: O(n) per operation | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Flatten a Multilevel Doubly Linked List
**Difficulty:** Medium | **LC:** 430

```cpp
Node* flatten(Node* head) {
    Node* cur = head;
    while (cur) {
        if (cur->child) {
            Node* child = cur->child;
            Node* next = cur->next;
            // connect cur → child
            cur->next = child; child->prev = cur; cur->child = nullptr;
            // find tail of child's list
            Node* tail = child;
            while (tail->next) tail = tail->next;
            // connect tail → next
            tail->next = next;
            if (next) next->prev = tail;
        }
        cur = cur->next;
    }
    return head;
}
// Time: O(n) | Space: O(1)
// Key: process child inline, then continue iterating
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Copy List with Random Pointer
**Difficulty:** Medium | **LC:** 138

```cpp
Node* copyRandomList(Node* head) {
    if (!head) return nullptr;
    unordered_map<Node*, Node*> mp;
    Node* cur = head;
    while (cur) { mp[cur] = new Node(cur->val); cur = cur->next; }
    cur = head;
    while (cur) {
        mp[cur]->next = mp[cur->next];   // nullptr if cur->next is null
        mp[cur]->random = mp[cur->random]; // nullptr if cur->random is null
        cur = cur->next;
    }
    return mp[head];
}
// Time: O(n) | Space: O(n)
// O(1) space alternative: interleave clones, set random, split
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Swap Nodes in Pairs
**Difficulty:** Medium | **LC:** 24

```cpp
ListNode* swapPairs(ListNode* head) {
    ListNode dummy(0); dummy.next = head;
    ListNode* prev = &dummy;
    while (prev->next && prev->next->next) {
        ListNode* a = prev->next;
        ListNode* b = prev->next->next;
        // swap a and b
        prev->next = b;
        a->next = b->next;
        b->next = a;
        prev = a; // a is now second in pair; advance past it
    }
    return dummy.next;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Sort List
**Difficulty:** Medium | **LC:** 148

```cpp
ListNode* sortList(ListNode* head) {
    if (!head || !head->next) return head;
    // Find middle (lower-middle for even)
    ListNode* slow = head, *fast = head->next;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    ListNode* second = slow->next; slow->next = nullptr;
    // Merge sort halves
    ListNode* l = sortList(head), *r = sortList(second);
    // Merge
    ListNode dummy(0); ListNode* tail = &dummy;
    while (l && r) {
        if (l->val <= r->val) { tail->next = l; l = l->next; }
        else { tail->next = r; r = r->next; }
        tail = tail->next;
    }
    tail->next = l ? l : r;
    return dummy.next;
}
// Time: O(n log n) | Space: O(log n) recursion
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** In an LRU Cache, why do we use a doubly linked list instead of a singly linked list?
<details><summary>Reveal</summary>
To delete a node in O(1), you need to update its predecessor's `next` pointer. With a singly linked list, finding the predecessor requires O(n) traversal. With a doubly linked list, the node has a `prev` pointer, so deletion is O(1): `node.prev.next = node.next; node.next.prev = node.prev`. The hash map gives us the node pointer directly, so we need O(1) deletion to make the cache O(1) overall.
</details>

**Drill 2:** LRU Cache with cap=2. Trace: put(1,1), put(2,2), get(1), put(3,3), get(2).
<details><summary>Reveal</summary>
put(1,1): head↔[1]↔tail. put(2,2): head↔[2]↔[1]↔tail. get(1): move 1 to front → head↔[1]↔[2]↔tail, returns 1. put(3,3): cap full, evict LRU=[2] → erase key 2 from map, add 3: head↔[3]↔[1]↔tail. get(2): key 2 not in map → returns -1. (2 was evicted)
</details>

**Drill 3:** Flatten doubly linked list: head=[1,2,3] where node 2 has child=[4,5]. Trace.
<details><summary>Reveal</summary>
cur=1 (no child). cur=2 (has child=[4,5]). child=4, next=3. 2.next=4, 4.prev=2, 2.child=null. Tail of child list = 5. 5.next=3, 3.prev=5. Continue: cur=4 (no child). cur=5 (no child). cur=3 (no child). Result: 1↔2↔4↔5↔3.
</details>

**Drill 4:** Copy list with random pointer: why does the interleave trick work in O(1) space?
<details><summary>Reveal</summary>
Step 1: Insert clone of each node right after original: A→A'→B→B'→... Step 2: For each original node A, A.random = orig, so clone A'.random = A.random.next = orig.random's clone. Step 3: Restore originals and extract clones. The clone is always 1 step ahead of the original, so we can find any clone's random by `original.random.next`, without needing a hash map.
</details>

**Drill 5:** Swap pairs in [1,2,3,4]. Trace prev pointer.
<details><summary>Reveal</summary>
dummy→1→2→3→4. prev=dummy. Round 1: a=1, b=2. prev.next=2, 1.next=3, 2.next=1. List: dummy→2→1→3→4. prev=1. Round 2: a=3, b=4. prev.next=4, 3.next=null, 4.next=3. List: dummy→2→1→4→3. prev=3. 3.next=null, stop. Result: 2→1→4→3 ✓.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| LRU get | O(1) | O(capacity) |
| LRU put | O(1) | O(capacity) |
| Design linked list get | O(n) | O(n) |
| Design linked list add/delete | O(n) for index | O(1) |
| Flatten multilevel DLL | O(n) | O(1) |
| Copy with random | O(n) | O(n) or O(1) with interleave |
| Swap pairs | O(n) | O(1) |
| Sort list (merge sort) | O(n log n) | O(log n) |

---

## 9. Common Follow-up Questions

**Q: Can you implement LRU without pointers using only arrays?**
A: Yes — use an array as a circular buffer with two indices tracking oldest and newest. But updating on access becomes O(1) only if you use index-based hash map and keep the circular structure — essentially still O(1) but more complex.

**Q: What is the difference between LRU and LFU cache?**
A: LRU evicts the item that was accessed least recently (time-based). LFU evicts the item accessed least frequently overall (frequency-based). LFU needs frequency tracking — typically uses a frequency-to-nodes map plus a hash map.

**Q: Why use dummy head and tail?**
A: They eliminate edge cases: adding to an empty list (head.next = tail before insertion — no null check needed), removing the only element, and removing the head or tail. With dummies, addToFront and removeNode are always the same code.

---

## 10. Cross-Pattern Connections

- **P75 (Slow/Fast Pointers):** Both work on linked list structure; fast/slow on singly, DLL on doubly
- **P94 (LRU Cache Design):** Full LRU as a system design problem with thread safety considerations
- **P95 (LFU Cache):** Extends LRU concept with frequency-based eviction
- **P66 (Stack Design):** Design-first patterns; min-stack uses similar "augment each node" idea
