# Pattern 03: Fixed Separation Two Pointers

## Category
Two Pointers

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 19. Remove Nth Node From End of List | Medium | https://leetcode.com/problems/remove-nth-node-from-end-of-list/ |
| 2 | 876. Middle of the Linked List | Easy | https://leetcode.com/problems/middle-of-the-linked-list/ |
| 3 | 2095. Delete the Middle Node of a Linked List | Medium | https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/ |

---

## 1. First-Timer Explanation

### What is this pattern?
You don't know the length of the linked list ahead of time. You want to find a node that's N positions from the end, or the exact middle — all in a single pass.

The trick: advance the "fast" pointer N steps ahead of the "slow" pointer first. Then move both one step at a time. When fast reaches the end, slow is exactly N steps from the end. The gap between the two pointers is always fixed at N.

### Real-World Analogy
Two cars on a highway, one N miles ahead of the other. When the lead car exits at the toll booth at the end, the trailing car is exactly N miles from the exit — still on the road. You've measured N miles from the end without knowing the total distance.

### Visual Walkthrough
```
Remove Nth from end (N=2):
  List: 1 → 2 → 3 → 4 → 5 → null

  Step 1: advance fast N+1 = 3 steps ahead
  dummy → 1 → 2 → 3 → 4 → 5 → null
  slow=dummy   fast=3

  Step 2: advance both until fast=null
  Move 1: slow=1  fast=4
  Move 2: slow=2  fast=5
  Move 3: slow=3  fast=null ← STOP

  slow is at node 3, which is just BEFORE the node to delete (node 4)
  slow->next = slow->next->next  (skip node 4)
  
  Result: 1 → 2 → 3 → 5
```

### When TO use this pattern
- Find node k positions from the end of a linked list
- Find middle of linked list (gap = half the length, achieved via fast/slow)
- One-pass deletion of specific position from end
- Any problem requiring "look N ahead" in a sequence

### When NOT to use this pattern
- Random access arrays (just use length-n)
- When the gap is not fixed and needs to change

### Common Beginner Mistakes
- **Advance N+1 not N**: to find node BEFORE the target (to enable deletion), advance N+1 steps
- **Use a dummy node**: handles edge case where the head itself must be deleted
- **Check fast != null**: before advancing, always verify fast is valid

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "remove/find Nth from end" in a linked list, one pass |
| Core Idea | Advance fast N steps, then move both; when fast=null, slow=target |
| Trigger Keywords | "nth from end", "middle node", "one pass", "constant space" |
| Avoid When | Length is known, or random access structure |
| Time Complexity | O(n) |
| Space Complexity | O(1) |

**Gotchas:**
- Use a dummy node before head to simplify edge cases
- Advance N+1 (not N) if you want slow to stop at the node BEFORE the target
- For "middle": use standard fast/slow — when fast reaches end, slow is at middle

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"remove Nth node from end"` → advance fast N+1 steps, then sync
- `"middle of the linked list"` → fast/slow (fast moves 2x); fixed separation variant
- `"single pass"`, `"O(1) space"` → fixed separation is the approach

### Constraint hints
- Linked list with unknown length + O(1) space + one pass → fixed separation
- N guaranteed to be valid → no need to handle out-of-bounds N

---

## 4. C++ Template

```cpp
/*
 * Pattern: Fixed Separation Two Pointers
 * Use when: find/remove Nth node from end in one pass
 * Time: O(n) | Space: O(1)
 */

struct ListNode { int val; ListNode* next; ListNode(int x):val(x),next(nullptr){} };

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* slow = &dummy;
    ListNode* fast = &dummy;

    // advance fast N+1 steps so when fast=null, slow is BEFORE target
    for (int i = 0; i <= n; i++) fast = fast->next;

    // move both until fast reaches end
    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow is one before the node to delete
    slow->next = slow->next->next;
    return dummy.next;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I need to remove the Nth node from the end in one pass, O(1) space.
If I knew the length, I'd just compute length-N. But with one pass only, I use two pointers.
I advance one pointer N+1 steps ahead, then move both together. When the lead pointer hits null, the trailing pointer is exactly at the node before the target.
I use a dummy head to handle the edge case where head itself must be removed."

### What to TYPE as comments while coding live
```cpp
// PROBLEM: remove Nth from end, single pass, O(1) space
// APPROACH: fast pointer N+1 ahead, then move both; slow lands before target
// DUMMY NODE: handles head deletion edge case

// EDGE CASES:
// - N equals list length (delete head) → dummy node handles this
// - Single element list → dummy.next becomes null
```

### Interview Flow Checklist
- [ ] Ask: is N always valid?
- [ ] Explain why N+1 (not N) advance
- [ ] Mention dummy node for head-deletion edge case
- [ ] Code and dry run
- [ ] State complexity

---

## 6. Problems

---

### Problem 1: 19. Remove Nth Node From End of List
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/remove-nth-node-from-end-of-list/
**Why this pattern fits:** One-pass deletion of node at fixed offset from end

**Problem Summary:**
Given linked list and integer n, remove the nth node from the end of the list in one pass.

**Optimal C++ Solution:**
```cpp
// Remove Nth Node From End of List
// Time: O(n) | Space: O(1)

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    // advance fast N+1 steps
    for (int i = 0; i <= n; i++) fast = fast->next;

    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow is just before the node to remove
    ListNode* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;

    return dummy.next;
}
```

**Edge Cases:**
- [ ] N equals length (delete head — dummy handles this)
- [ ] Single node list
- [ ] N = 1 (delete tail)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 876. Middle of the Linked List
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/middle-of-the-linked-list/
**Why this pattern fits:** Fast/slow — when fast reaches end, slow is at middle

**Problem Summary:**
Return the middle node of a linked list. If even length, return the second middle.

**Optimal C++ Solution:**
```cpp
// Middle of Linked List
// Time: O(n) | Space: O(1)

ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // when fast reaches end, slow is at middle
    // for even-length: slow lands at second-middle (as required)
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

**Edge Cases:**
- [ ] Single node (slow never moves, returns head)
- [ ] Two nodes (slow moves once, returns second node)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 2095. Delete the Middle Node of a Linked List
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
**Why this pattern fits:** Find middle, but need the node BEFORE it to do deletion

**Problem Summary:**
Delete the middle node of a linked list. For even length, delete the second middle.

**Approach Walkthrough:**
1. Need slow to stop one node before the middle
2. Adjust: start fast one step ahead (at head->next), so slow lags behind by one

**Optimal C++ Solution:**
```cpp
// Delete Middle Node
// Time: O(n) | Space: O(1)

ListNode* deleteMiddle(ListNode* head) {
    if (!head || !head->next) return nullptr;  // 0 or 1 nodes

    ListNode* slow = head;
    ListNode* fast = head->next->next;  // start fast 2 ahead → slow stops 1 before middle

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // slow is one before the middle node
    slow->next = slow->next->next;
    return head;
}
```

**Edge Cases:**
- [ ] Single node (return nullptr)
- [ ] Two nodes (delete second — which is the middle)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find the kth node from the end of a linked list and return its value (not delete it).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Separation
**Reason:** Advance fast K steps (not K+1), then move both. When fast is null, slow is AT the kth-from-end node.
</details>

---

**Drill 2:**
> Given a linked list, split it into two halves.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fast & Slow (Fixed Separation variant)
**Reason:** Find middle with fast/slow, then cut the link at middle. For odd length, first half is longer.
</details>

---

**Drill 3:**
> Determine if a linked list is a palindrome using O(1) extra space.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Separation (find middle) + In-place Reversal
**Reason:** Find middle with fast/slow, reverse the second half, compare both halves node by node.
</details>

---

**Drill 4:**
> Given a linked list of length n, return the node at position ⌊n/3⌋ from the end.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Separation
**Reason:** Advance fast n/3 steps ahead (but you'd need to know n first for that specific fraction, or use 3 pointers: one at start, one n/3 ahead, one 2n/3 ahead of start).
</details>

---

**Drill 5:**
> Rotate a linked list to the right by k positions.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Fixed Separation
**Reason:** Use fixed separation to find the (length-k)th node from the end (which is the new tail). The node after it is the new head. Connect old tail to old head. This is LC 61.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Remove Nth from end | O(n) | O(1) | One pass with N+1 advance |
| Find middle | O(n) | O(1) | Fast/slow converge at middle |
| Delete middle | O(n) | O(1) | Adjusted start for pre-middle |

---

## 9. Common Follow-up Questions

1. What if N could be out of bounds? (Add validation; return original list if N > length)
2. What if the list is circular? (Detect cycle first, then handle differently)
3. Can you do it without a dummy node? (Yes, but must special-case head deletion)
4. For rotating the list by k: what if k > length? (k = k % length to normalize)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| In-place Reversal | Palindrome check, rearrange list | 234. Palindrome Linked List |
| Fast & Slow | Both use two-pointer on linked list | 876. Middle of LL |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
