# P75 — Slow and Fast Pointers

## 1. First-Timer Explanation

### What Is It?
**Slow/fast pointers** (Floyd's algorithm) uses two pointers moving at different speeds through a linked list:
- Slow moves 1 step at a time
- Fast moves 2 steps at a time

This enables detecting cycles, finding the middle, and finding the Kth element from end — all in O(n) with O(1) space.

### Why Does Cycle Detection Work?
If there's a cycle, fast eventually laps slow (like a faster runner on a circular track). Once they meet inside the cycle, you can find the cycle start: reset one pointer to head, move both one step at a time — they meet at the cycle start.

### Visual Walkthrough — Cycle Detection
```
List: 1 → 2 → 3 → 4 → 5 → 3 (cycle back to node 3)

slow: 1→2→3→4→5→3→4
fast: 1→3→5→4→3→5→4

They meet at node 4.

Now: slow=head(1), fast=4, both move 1 step:
slow: 1→2→3
fast: 4→5→3

They meet at node 3 = cycle start ✓
```

### Find Middle of Linked List
```
When fast reaches null, slow is at middle.

Odd length [1,2,3,4,5]:
slow=1,fast=1 → slow=2,fast=3 → slow=3,fast=5 → fast.next=null, stop.
slow=3 = middle ✓

Even length [1,2,3,4]:
slow=1,fast=1 → slow=2,fast=3 → slow=3,fast=null, stop.
slow=3 = second middle (for "lower middle": stop when fast.next==null)
```

### When to Use
- "Detect cycle in linked list"
- "Find cycle start"
- "Find middle of linked list"
- "Kth element from end" (set fast K steps ahead of slow)
- "Happy number" (cycle detection on number sequence)

### Common Mistakes
1. Cycle: check `fast && fast->next` to avoid null dereference
2. Middle: `fast->next && fast->next->next` stops at LOWER middle for even
3. Kth from end: move fast K steps, THEN move both together
4. Meeting point ≠ cycle start (need second phase to find start)

---

## 2. Revision Card

**Recognition Signal:** "cycle", "middle", "Kth from end", "find loop"

**Core Idea:** Slow moves 1, fast moves 2. If cycle: they meet. Find middle: when fast hits end. Find cycle start: reset slow to head, move both 1 at a time.

**Trigger Keywords:** cycle, loop, middle, Kth from end, Floyd, hare and tortoise

**Complexity:** O(n) time, O(1) space

---

## 3. Interview Tell Signs

- "Detect cycle" → fast/slow, return fast==slow
- "Find cycle start" → two-phase Floyd
- "Middle of list" → fast/slow, return slow
- "Kth from end" → fast goes K steps ahead, then both move together
- "Happy number" → cycle detection on integer sequence

---

## 4. C++ Template

```cpp
struct ListNode { int val; ListNode* next; };

// ── Cycle Detection ───────────────────────────────────────────────────────────
bool hasCycle(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// ── Find Cycle Start ──────────────────────────────────────────────────────────
ListNode* detectCycle(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) {
            slow = head; // reset to head
            while (slow != fast) { slow = slow->next; fast = fast->next; }
            return slow; // cycle start
        }
    }
    return nullptr;
}

// ── Find Middle ───────────────────────────────────────────────────────────────
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    return slow; // upper middle for even length
}

// ── Kth From End ──────────────────────────────────────────────────────────────
ListNode* removeNthFromEnd(ListNode* head, int k) {
    ListNode dummy(0); dummy.next = head;
    ListNode* fast = &dummy, *slow = &dummy;
    for (int i = 0; i <= k; i++) fast = fast->next; // advance fast k+1 steps
    while (fast) { slow = slow->next; fast = fast->next; }
    slow->next = slow->next->next; // remove kth from end
    return dummy.next;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Cycle Start):**
> "Phase 1: Detect meeting point using slow (1 step) and fast (2 steps). If they meet, a cycle exists. Phase 2: Reset slow to head, keep fast at meeting point. Move both 1 step at a time. They'll meet at the cycle start. This works due to the math: if the meeting point is at distance d from the start, the head is also exactly cycle_length - d away from the start via slow's path."

**Checklist:**
- [ ] Always check `fast && fast->next` in loop condition
- [ ] Cycle start: two-phase after meeting
- [ ] Middle: use `fast && fast->next` to stop at upper middle
- [ ] Kth from end: advance fast by k+1 using dummy node to handle deletion
- [ ] Happy number: apply cycle detection to the digit-square sum sequence

---

## 6. Problems

### Problem 1: Linked List Cycle
**Difficulty:** Easy | **LC:** 141

```cpp
bool hasCycle(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Linked List Cycle II (Find Start)
**Difficulty:** Medium | **LC:** 142

```cpp
ListNode* detectCycle(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next; fast = fast->next->next;
        if (slow == fast) {
            slow = head;
            while (slow != fast) { slow = slow->next; fast = fast->next; }
            return slow;
        }
    }
    return nullptr;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Middle of the Linked List
**Difficulty:** Easy | **LC:** 876

```cpp
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    return slow;
}
// Time: O(n) | Space: O(1)
// For even [1,2,3,4]: returns node 3 (upper middle, 2nd of two middles)
// To get lower middle: while (fast->next && fast->next->next)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Remove Nth Node From End of List
**Difficulty:** Medium | **LC:** 19

```cpp
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0); dummy.next = head;
    ListNode* fast = &dummy, *slow = &dummy;
    for (int i = 0; i <= n; i++) fast = fast->next; // advance n+1
    while (fast) { slow = slow->next; fast = fast->next; }
    slow->next = slow->next->next;
    return dummy.next;
}
// Time: O(n) | Space: O(1)
// Dummy node handles edge case: removing the head
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Happy Number
**Difficulty:** Easy | **LC:** 202

**Approach:** Apply Floyd's cycle detection to the sequence of digit-square sums.

```cpp
int digitSquareSum(int n) {
    int sum = 0;
    while (n) { int d = n%10; sum += d*d; n /= 10; }
    return sum;
}

bool isHappy(int n) {
    int slow = n, fast = digitSquareSum(n);
    while (fast != 1 && slow != fast) {
        slow = digitSquareSum(slow);
        fast = digitSquareSum(digitSquareSum(fast));
    }
    return fast == 1;
}
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Intersection of Two Linked Lists
**Difficulty:** Easy | **LC:** 160

**Approach:** Two pointers. When one reaches the end, redirect to the other list's head. They'll meet at intersection (or both null).

```cpp
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    ListNode* a = headA, *b = headB;
    while (a != b) {
        a = a ? a->next : headB; // redirect to other list when null
        b = b ? b->next : headA;
    }
    return a; // null if no intersection
}
// Time: O(m+n) | Space: O(1)
// Key: both traverse total m+n nodes before meeting
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Cycle detection: why does fast eventually meet slow if a cycle exists?
<details><summary>Reveal</summary>
Once both are in the cycle, the gap between them changes by 1 each step (fast gains 1 on slow each round since fast moves 2 and slow moves 1). Since the cycle has finite length, the gap eventually becomes 0 (they meet). This takes at most cycle_length steps.
</details>

**Drill 2:** Cycle start proof: why does resetting slow to head and moving both 1 step lead to the cycle start?
<details><summary>Reveal</summary>
Let F = distance from head to cycle start, C = cycle length, k = F mod C. When they first meet, slow has traveled F+k steps, fast has traveled F+k+m*C steps (some multiple m of the cycle). Setting fast speed to 1: from meeting point, cycle_start is C-k steps away. From head, cycle_start is F steps = k + (n*C - k) mod... simplification: F ≡ C-k (mod C), so both arrive at cycle start simultaneously after F steps.
</details>

**Drill 3:** Find middle of [1,2,3,4,5]. Trace slow/fast.
<details><summary>Reveal</summary>
slow=1,fast=1. Iter1: slow=2,fast=3. Iter2: slow=3,fast=5. fast.next=null → stop. Middle=3 ✓ (position 3 of 5).
</details>

**Drill 4:** Remove 2nd from end of [1,2,3,4,5]. Trace with dummy node.
<details><summary>Reveal</summary>
dummy→1→2→3→4→5. fast and slow start at dummy. Advance fast 3 steps (n+1=3): fast=3. Both move together: slow=1,fast=4. slow=2,fast=5. slow=3,fast=null(end). slow=3 (node before the 2nd-from-end). slow.next=4, slow.next.next=5. slow.next=5. List: 1→2→3→5. ✓ (4 removed = 2nd from end).
</details>

**Drill 5:** Intersection: list A=[1,2,3,4], list B=[7,4] where 4→null is shared. Trace the two-pointer.
<details><summary>Reveal</summary>
a starts at 1, b at 7. a: 1→2→3→4→null→7→4→... b: 7→4→null→1→2→3→4→... Both traverse 4+2=6 total nodes. They meet at node 4 (the shared node) ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Cycle detection | O(n) | O(1) |
| Cycle start | O(n) | O(1) |
| Find middle | O(n) | O(1) |
| Remove Kth from end | O(n) | O(1) |
| Intersection | O(m+n) | O(1) |
| Happy number | O(log n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: How can you find the cycle length?**
A: After finding the meeting point, keep slow fixed and move fast one step at a time, counting steps until they meet again. That count is the cycle length.

**Q: Can you detect a cycle without modifying the list?**
A: Yes — Floyd's algorithm doesn't modify the list. The hash set approach (O(n) space) is the alternative.

**Q: What if the linked list has a self-loop (single node pointing to itself)?**
A: Floyd's handles it. slow and fast both start at head. After 1 step: slow = node.next = node (self-loop), fast = node.next.next = node. They meet on the first iteration.

---

## 10. Cross-Pattern Connections

- **P74 (Reverse):** Finding middle is used before reversing for palindrome check
- **P04 (Two Pointers):** Same concept on arrays; slow/fast is linked list variant
- **P76 (LRU):** Uses doubly-linked list; single-direction fast/slow not applicable
- **P19 (BFS):** Both find boundaries in graph/list structures efficiently
