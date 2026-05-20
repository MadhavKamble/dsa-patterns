# P74 — Reverse Linked List Patterns

## 1. First-Timer Explanation

### What Is It?
**Reversing a linked list** (fully or in sections) is a fundamental operation. The core is maintaining three pointers: `prev`, `curr`, and `next`. Section reversal (reverse every k nodes, reverse between positions m and n) extends this with careful boundary management.

### Visual Walkthrough — Full Reverse
```
1 → 2 → 3 → 4 → 5 → null

prev=null, curr=1
Step 1: next=2, 1→null, prev=1, curr=2
Step 2: next=3, 2→1, prev=2, curr=3
Step 3: next=4, 3→2, prev=3, curr=4
Step 4: next=5, 4→3, prev=4, curr=5
Step 5: next=null, 5→4, prev=5, curr=null

Result: 5 → 4 → 3 → 2 → 1 → null
```

### Reverse Between m and n (Positions, 1-indexed)
```
1 → 2 → 3 → 4 → 5, m=2, n=4

Use dummy head to simplify edge cases.
Find node BEFORE m (prevM):
1 is prevM. Start reversing from 2, stop after (n-m+1)=3 nodes.

During reversal: reverse 2→3→4 into 4→3→2
Connect: prevM.next = 4, 2.next = 5
Result: 1 → 4 → 3 → 2 → 5
```

### When to Use
- "Reverse linked list" (full, k-group, between positions)
- "Palindrome linked list" (reverse second half)
- "Rotate list" (find tail, connect, find new tail)

### Common Mistakes
1. Not saving `curr.next` before overwriting `curr.next = prev`
2. Not connecting the reversed section back properly
3. Using `dummy.next` for the head simplifies "reverse first k" edge cases
4. Off-by-one in finding the boundary node

---

## 2. Revision Card

**Recognition Signal:** "reverse linked list", "reverse between", "k-group reversal", "rotate"

**Core Idea:** Three pointers: prev, curr, next. `next = curr.next; curr.next = prev; prev = curr; curr = next`.

**Trigger Keywords:** reverse, flip, rotate, palindrome, k-group

**Complexity:** O(n) time, O(1) space for all reversal patterns

---

## 3. Interview Tell Signs

- "Reverse linked list" → three-pointer iterative
- "Reverse in k-groups" → reverse each k-group, connect to next
- "Reverse between m and n" → find boundary, reverse section
- "Is linked list palindrome?" → find middle, reverse second half, compare
- "Rotate by k" → find length, reconnect

---

## 4. C++ Template

```cpp
struct ListNode { int val; ListNode* next; ListNode(int v) : val(v), next(nullptr) {} };

// ── Full Reverse ──────────────────────────────────────────────────────────────
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr, *curr = head;
    while (curr) {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

// ── Reverse Between m and n (1-indexed) ──────────────────────────────────────
ListNode* reverseBetween(ListNode* head, int m, int n) {
    ListNode dummy(0); dummy.next = head;
    ListNode* prevM = &dummy;
    for (int i = 1; i < m; i++) prevM = prevM->next;
    
    ListNode* curr = prevM->next;
    for (int i = 0; i < n - m; i++) {
        ListNode* next = curr->next;
        curr->next = next->next;
        next->next = prevM->next;
        prevM->next = next;
    }
    return dummy.next;
}

// ── Reverse in K-Groups ───────────────────────────────────────────────────────
ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* curr = head;
    int count = 0;
    while (curr && count < k) { curr = curr->next; count++; }
    if (count < k) return head; // not enough nodes
    
    curr = reverseList_n(head, k); // reverse k nodes, head becomes tail
    head->next = reverseKGroup(curr, k); // recurse on remainder
    return curr; // new head of this group
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Three pointers: `prev=null`, `curr=head`. At each step: save `next=curr.next`, point `curr.next=prev`, advance `prev=curr`, advance `curr=next`. Return `prev` (new head). For reversing between m and n: use a dummy head, find the node just before position m, then use the 'insert at front' technique to reverse n-m connections."

**Checklist:**
- [ ] Save `next` BEFORE overwriting `curr.next`
- [ ] Return `prev` as new head (not curr, which is null)
- [ ] For sections: dummy node avoids edge cases
- [ ] For k-groups: check if k nodes remain before reversing
- [ ] Connect reversed section back to rest of list

---

## 6. Problems

### Problem 1: Reverse Linked List
**Difficulty:** Easy | **LC:** 206

```cpp
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr, *curr = head;
    while (curr) {
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev;
}
// Time: O(n) | Space: O(1)
// Recursive: reverseList(head) → head.next = head, recurse on tail
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Reverse Linked List II (Between m and n)
**Difficulty:** Medium | **LC:** 92

```cpp
ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode dummy(0); dummy.next = head;
    ListNode* prev = &dummy;
    for (int i = 1; i < left; i++) prev = prev->next;
    
    ListNode* curr = prev->next;
    for (int i = 0; i < right - left; i++) {
        ListNode* nxt = curr->next;
        curr->next = nxt->next;
        nxt->next = prev->next;
        prev->next = nxt;
    }
    return dummy.next;
}
// Time: O(n) | Space: O(1)
// Trick: "insert at front of reversed section" avoids finding the tail of reversed section
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Reverse Nodes in k-Group
**Difficulty:** Hard | **LC:** 25

```cpp
ListNode* reverseKGroup(ListNode* head, int k) {
    // Check if k nodes available
    ListNode* curr = head;
    for (int i = 0; i < k; i++) {
        if (!curr) return head; // fewer than k nodes: don't reverse
        curr = curr->next;
    }
    // Reverse k nodes
    ListNode* prev = nullptr, *node = head;
    for (int i = 0; i < k; i++) {
        ListNode* nxt = node->next;
        node->next = prev;
        prev = node;
        node = nxt;
    }
    // head is now tail of reversed group; connect to next group
    head->next = reverseKGroup(node, k);
    return prev; // prev is new head
}
// Time: O(n) | Space: O(n/k) recursion
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Palindrome Linked List
**Difficulty:** Easy | **LC:** 234

**Approach:** Find middle (slow/fast pointers), reverse second half, compare.

```cpp
bool isPalindrome(ListNode* head) {
    // Find middle
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    
    // Reverse second half
    ListNode* prev = nullptr, *curr = slow;
    while (curr) { ListNode* nxt = curr->next; curr->next = prev; prev = curr; curr = nxt; }
    
    // Compare
    ListNode* left = head, *right = prev;
    while (right) {
        if (left->val != right->val) return false;
        left = left->next; right = right->next;
    }
    return true;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Rotate List
**Difficulty:** Medium | **LC:** 61

**Approach:** Find length. Connect tail to head. Move to new tail position.

```cpp
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    int len = 1;
    ListNode* tail = head;
    while (tail->next) { tail = tail->next; len++; }
    tail->next = head; // make circular
    
    int steps = len - k % len; // new tail is steps from current head
    ListNode* newTail = head;
    for (int i = 1; i < steps; i++) newTail = newTail->next;
    
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

### Problem 6: Reorder List (L0→Ln→L1→Ln-1→...)
**Difficulty:** Medium | **LC:** 143

**Approach:** Find middle, reverse second half, merge two halves.

```cpp
void reorderList(ListNode* head) {
    if (!head || !head->next) return;
    
    // Find middle
    ListNode* slow = head, *fast = head;
    while (fast->next && fast->next->next) { slow = slow->next; fast = fast->next->next; }
    
    // Reverse second half
    ListNode* second = slow->next; slow->next = nullptr;
    ListNode* prev = nullptr, *curr = second;
    while (curr) { ListNode* nxt = curr->next; curr->next = prev; prev = curr; curr = nxt; }
    second = prev;
    
    // Merge
    ListNode* first = head;
    while (second) {
        ListNode* tmp1 = first->next, *tmp2 = second->next;
        first->next = second;
        second->next = tmp1;
        first = tmp1;
        second = tmp2;
    }
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Three-pointer reversal: why save `next = curr.next` BEFORE `curr.next = prev`?
<details><summary>Reveal</summary>
After `curr.next = prev`, we've overwritten the link to the next node. If we didn't save `next` first, we'd lose the rest of the list. The save-then-overwrite order is critical.
</details>

**Drill 2:** Reverse between m=2, n=4 in [1,2,3,4,5]. Trace the "insert at front" method.
<details><summary>Reveal</summary>
prevM=node1, curr=node2. Iteration 1 (i=0, reverse 2→3→4 to 4→3→2): nxt=node3. node2.next=node3.next=node4. node3.next=prevM.next=node2. prevM.next=node3. List: 1→3→2→4→5. Iteration 2 (i=1): nxt=node4. node2.next=node4.next=node5. node4.next=prevM.next=node3. prevM.next=node4. List: 1→4→3→2→5. ✓
</details>

**Drill 3:** K-groups reversal: after reversing a group of k, what does `head` point to?
<details><summary>Reveal</summary>
Before reversal: head is the first node of the group (will become the last after reversal). After reversing k nodes, head points to what is now the TAIL of the reversed group. So `head->next = reverseKGroup(next_group_head, k)` connects the tail of this group to the head of the next reversed group.
</details>

**Drill 4:** Palindrome check: for list [1,2,3,2,1], where does slow stop after slow/fast traversal?
<details><summary>Reveal</summary>
Start: slow=1, fast=1. Step1: slow=2, fast=3. Step2: slow=3, fast=1(end). Fast has no fast.next.next → stop. slow=3. Reverse from 3: [3,2,1] reversed = [1,2,3]. Compare [1,2,3] with [1,2,3] → palindrome ✓.
</details>

**Drill 5:** Rotate [1,2,3,4,5] by k=2 to the right. Trace.
<details><summary>Reveal</summary>
len=5, tail=5, tail.next=1 (circular). steps = 5-2=3. Move 3 steps from head: new_tail = node3. new_head = node4. node3.next=null. Result: 4→5→1→2→3 ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Reverse full list | O(n) | O(1) |
| Reverse between m,n | O(n) | O(1) |
| Reverse k-groups | O(n) | O(n/k) recursion |
| Palindrome check | O(n) | O(1) |
| Rotate list | O(n) | O(1) |
| Reorder list | O(n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Recursive reversal of entire list?**
A: `head.next.next = head; head.next = null; return last`. O(n) time, O(n) space.

**Q: Can you reverse k-groups iteratively?**
A: Yes — track `prevGroupTail`, reverse k nodes, connect, update `prevGroupTail`. More code but O(1) space.

**Q: What if k > n (not enough nodes)?**
A: Leave them unchanged (return head as-is). The check `if count < k: return head` handles this.

---

## 10. Cross-Pattern Connections

- **P75 (Slow/Fast Pointer):** Palindrome and reorder both use slow/fast to find middle
- **P76 (LRU Cache):** Doubly-linked list for O(1) insertion/deletion
- **P04 (Two Pointers):** Fast/slow pointers on linked list
- **P18 (DFS):** Recursive reversal uses call stack like DFS
