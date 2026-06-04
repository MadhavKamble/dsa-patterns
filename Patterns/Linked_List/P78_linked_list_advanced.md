# P78 — Linked List Advanced Patterns

## 1. First-Timer Explanation

### What Is It?
**Advanced linked list** problems combine multiple primitives: finding intersection, detecting and removing duplicates, inserting into sorted lists, and number representations. These require careful pointer manipulation and often multiple passes.

### Remove Duplicates — Sorted List
```
Sorted: 1 → 1 → 2 → 3 → 3 → null

Keep one of each:
curr = 1. while curr.next && curr.val == curr.next.val → skip duplicates
curr.next = 3 (skipped second 1)
Result: 1 → 2 → 3

Remove ALL duplicates:
Use dummy + prev pointer. When duplicates detected, skip the entire group.
```

### Insert Into Sorted Circular List
```
Circular: 3 → 4 → 1 → (back to 3), insert 2

Walk: find where val >= insert_val >= prev_val (between 1 and 3: 1≤2≤3)
Insert 2 between 1 and 3.
Result: 3 → 4 → 1 → 2 → (back to 3)
```

### Rotate List Right by K
```
List: 1 → 2 → 3 → 4 → 5, k=2
New head: 5-2=3rd node from start = node 4
1 → 2 → 3 becomes tail group; 4 → 5 becomes head group
Result: 4 → 5 → 1 → 2 → 3
```

### When to Use
- "Remove duplicates from sorted list" → single pass comparing adjacent
- "Remove all occurrences of duplicates" → dummy + prev, skip groups
- "Insert into sorted circular linked list" → find the right gap
- "Rotate list by k" → find length, find new head, reconnect
- "Delete node without head pointer" → copy next node's value, skip next

### Common Mistakes
1. Remove duplicates (all): not advancing `prev` when a duplicate group is found
2. Rotate: use `k = k % len` to handle k > length; k=0 means no rotation
3. Circular insert: edge case when all values are equal (insert anywhere) or inserting at boundary (new min or new max)
4. Delete without head: only works when node is NOT the tail

---

## 2. Revision Card

**Recognition Signal:** "remove duplicates", "rotate list", "insert sorted circular", "delete without head"

**Core Idea:** Use dummy nodes to handle head deletion; use length + modulo for rotation; use prev/curr pairs for duplicate removal.

**Trigger Keywords:** duplicates, rotate, circular, sorted insertion, delete node

**Complexity:** O(n) time, O(1) space for all patterns

---

## 3. Interview Tell Signs

- "Remove duplicates from sorted list" → compare `curr` and `curr.next`
- "Remove ALL duplicates" → dummy + skip entire groups
- "Rotate right by k" → find len, connect tail to head, cut at `len - k % len`
- "Delete middle node given pointer only" → copy next value, skip next node
- "Insert into sorted circular" → walk to find gap; handle wrap-around
- "Linked list is palindrome" → find middle, reverse second half, compare

---

## 4. C++ Template

```cpp
struct ListNode { int val; ListNode* next; ListNode(int v):val(v),next(nullptr){} };

// ── Remove Duplicates (Keep One) ──────────────────────────────────────────────
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while (cur && cur->next) {
        if (cur->val == cur->next->val) cur->next = cur->next->next;
        else cur = cur->next;
    }
    return head;
}

// ── Remove All Duplicates ─────────────────────────────────────────────────────
ListNode* deleteDuplicatesAll(ListNode* head) {
    ListNode dummy(0); dummy.next = head;
    ListNode* prev = &dummy;
    while (prev->next) {
        ListNode* cur = prev->next;
        bool dup = false;
        while (cur->next && cur->val == cur->next->val) {
            cur = cur->next; dup = true;
        }
        if (dup) prev->next = cur->next; // skip entire group
        else prev = prev->next;
    }
    return dummy.next;
}

// ── Rotate Right by K ─────────────────────────────────────────────────────────
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    int len = 1; ListNode* tail = head;
    while (tail->next) { tail = tail->next; len++; }
    k %= len;
    if (k == 0) return head;
    tail->next = head; // make circular
    ListNode* newTail = head;
    for (int i = 1; i < len - k; i++) newTail = newTail->next;
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    return newHead;
}

// ── Delete Node (No Head Pointer) ─────────────────────────────────────────────
void deleteNode(ListNode* node) {
    node->val = node->next->val;   // copy next value
    node->next = node->next->next; // skip next node
}

// ── Insert Into Sorted Circular List ─────────────────────────────────────────
Node* insert(Node* head, int insertVal) {
    Node* node = new Node(insertVal);
    if (!head) { node->next = node; return node; }
    Node* prev = head, *cur = head->next;
    bool inserted = false;
    do {
        if (prev->val <= insertVal && insertVal <= cur->val) { inserted = true; break; }
        if (prev->val > cur->val) { // at the wrap point (max to min)
            if (insertVal >= prev->val || insertVal <= cur->val) { inserted = true; break; }
        }
        prev = cur; cur = cur->next;
    } while (prev != head);
    prev->next = node; node->next = cur;
    return head;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Remove All Duplicates):**
> "I use a dummy head and a `prev` pointer. For each group, I check if consecutive values match. If they do, I find the end of the duplicate group, then set prev.next to skip the entire group (prev doesn't advance). If no duplicates, advance prev normally. This is O(n) one-pass."

**Verbal Script (Rotate Right):**
> "First, find the list length and make it circular. Then compute the new tail position: index `len - k % len - 1` from the head. Split there. O(n) since we traverse at most twice."

**Checklist:**
- [ ] Remove duplicates (all): prev advances only when no duplicate found
- [ ] Rotate: always `k %= len` to normalize
- [ ] Rotate: make circular, walk to new tail, cut
- [ ] Delete node: only works when node is not the tail
- [ ] Circular insert: handle case where all values equal (after full loop → insert anywhere)

---

## 6. Problems

### Problem 1: Remove Duplicates from Sorted List
**Difficulty:** Easy | **LC:** 83

```cpp
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* cur = head;
    while (cur && cur->next) {
        if (cur->val == cur->next->val) cur->next = cur->next->next;
        else cur = cur->next;
    }
    return head;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Remove Duplicates from Sorted List II (All Occurrences)
**Difficulty:** Medium | **LC:** 82

```cpp
ListNode* deleteDuplicates(ListNode* head) {
    ListNode dummy(0); dummy.next = head;
    ListNode* prev = &dummy;
    while (prev->next) {
        ListNode* cur = prev->next;
        bool dup = false;
        while (cur->next && cur->val == cur->next->val) { cur = cur->next; dup = true; }
        if (dup) prev->next = cur->next;
        else prev = prev->next;
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

### Problem 3: Rotate List
**Difficulty:** Medium | **LC:** 61

```cpp
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    int len = 1; ListNode* tail = head;
    while (tail->next) { tail = tail->next; len++; }
    k %= len;
    if (k == 0) return head;
    tail->next = head;
    ListNode* newTail = head;
    for (int i = 1; i < len - k; i++) newTail = newTail->next;
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    return newHead;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Delete Node in a Linked List
**Difficulty:** Medium | **LC:** 237

```cpp
void deleteNode(ListNode* node) {
    node->val = node->next->val;
    node->next = node->next->next;
}
// Time: O(1) | Space: O(1)
// Assumes node is NOT the tail (guaranteed by problem)
// Trick: impersonate next node by copying its value
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Insert into a Sorted Circular Linked List
**Difficulty:** Medium | **LC:** 708

```cpp
Node* insert(Node* head, int insertVal) {
    Node* node = new Node(insertVal);
    if (!head) { node->next = node; return node; }
    Node* prev = head, *cur = head->next;
    do {
        if (prev->val <= insertVal && insertVal <= cur->val) break; // normal insertion
        if (prev->val > cur->val) { // at boundary (max→min)
            if (insertVal >= prev->val || insertVal <= cur->val) break;
        }
        prev = cur; cur = cur->next;
    } while (prev != head); // full loop: all equal, insert anywhere
    prev->next = node; node->next = cur;
    return head;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Next Greater Node in Linked List
**Difficulty:** Medium | **LC:** 1019

**Approach:** Convert to array, apply monotonic stack for next greater element.

```cpp
vector<int> nextLargerNodes(ListNode* head) {
    vector<int> vals;
    while (head) { vals.push_back(head->val); head = head->next; }
    int n = vals.size();
    vector<int> res(n, 0);
    stack<int> stk; // indices with no NGE yet
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && vals[stk.top()] < vals[i]) {
            res[stk.top()] = vals[i]; stk.pop();
        }
        stk.push(i);
    }
    return res;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Remove all duplicates from [1,1,2,3,3]. Trace prev and cur.
<details><summary>Reveal</summary>
dummy→1→1→2→3→3, prev=dummy. cur=first 1. cur.next=second 1, same val → advance cur to second 1, dup=true. No more duplicates. dup=true: prev.next = second_1.next = 2. prev stays at dummy. cur=2. cur.next=first 3, different → prev=2. cur=first 3. cur.next=second 3, same → cur=second 3, dup=true. prev.next = null. Result: 1→2→(done? no wait: dummy→2→3? Let me re-trace). Actually the first 1s are both dup so they all get skipped: prev.next = 2. Then 3s get skipped: prev.next=null. Result: dummy→2→null. Output: [2] ✓.
</details>

**Drill 2:** Rotate [1,2,3,4,5] right by k=2. What is the new tail position index?
<details><summary>Reveal</summary>
len=5. k=2. newTail position: len-k-1 = 5-2-1 = 2 (0-indexed), which is node with value 3. Steps from head: len-k = 3 (1-indexed traversal stops at 3rd node). Make circular: 5→1. Walk: newTail starts at 1, advance 2 times: 1→2→3. newHead = 4. Cut: 3.next=null. Result: 4→5→1→2→3 ✓.
</details>

**Drill 3:** Delete node with value 5 in [4,5,1,9] using only a pointer to node(5).
<details><summary>Reveal</summary>
node = node(5). node.val = node.next.val = 1. node.next = node.next.next = node(9). List becomes: 4→1→9. We effectively made node(5) impersonate node(1) and skipped the original node(1). Result: [4,1,9] ✓.
</details>

**Drill 4:** Insert 2 into sorted circular list [3,4,1] (3→4→1→3). Trace the do-while.
<details><summary>Reveal</summary>
prev=3, cur=4. 3≤2≤4? No (2<3). prev.val > cur.val? No (3<4). Advance: prev=4, cur=1. 4≤2≤1? No. prev.val > cur.val? Yes (4>1). insertVal≥4? No. insertVal≤1? No (2>1). Advance: prev=1, cur=3. 1≤2≤3? Yes → break. Insert: 1.next=node(2), node(2).next=3. Result: 3→4→1→2→3 ✓.
</details>

**Drill 5:** Next greater node for list [2,1,5]. What does the stack contain after i=1?
<details><summary>Reveal</summary>
vals = [2,1,5]. i=0: stk empty, push 0. stk=[0]. i=1: vals[0]=2 > vals[1]=1 → don't pop. Push 1. stk=[0,1]. i=2: vals[1]=1 < 5 → res[1]=5, pop 1. vals[0]=2 < 5 → res[0]=5, pop 0. Push 2. stk=[2]. After loop: res[2]=0 (no NGE). Result: [5,5,0] ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Remove duplicates (keep one) | O(n) | O(1) |
| Remove all duplicates | O(n) | O(1) |
| Rotate list | O(n) | O(1) |
| Delete node (no head) | O(1) | O(1) |
| Insert sorted circular | O(n) | O(1) |
| Next greater node | O(n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: Remove duplicates from an unsorted linked list?**
A: Use a hash set of seen values. If `cur.val` is in the set, splice it out (requires tracking prev). O(n) time, O(n) space.

**Q: What if the "delete node" problem gives you the tail node?**
A: Impossible to delete in O(1) without the head pointer — must traverse from head to find the predecessor. The trick only works for non-tail nodes.

**Q: What if k > len in rotate list?**
A: `k %= len` handles it — rotating by len gives the same list. So k=7 on a 5-element list is same as k=2.

---

## 10. Cross-Pattern Connections

- **P74 (Reverse Linked List):** Rotation is essentially a reversal of two sub-lists (alternative approach)
- **P75 (Slow/Fast Pointers):** Finding the new tail in rotate uses the "k steps from end" technique
- **P64 (Monotonic Stack):** Next greater node directly applies the NGE stack pattern
- **P77 (Merge Lists):** After removing duplicates, merging produces sorted unique results
