# P77 — Merge and Rearrange Linked Lists

## 1. First-Timer Explanation

### What Is It?
**Merging linked lists** covers problems that combine two or more linked lists into a sorted or structured result. The core operations are:
- **Merge two sorted lists:** Use a dummy head; always pick the smaller next node
- **Partition list:** Split into two sub-lists (<x and ≥x), then concatenate
- **Odd-even grouping:** Collect odd-indexed nodes, then even-indexed nodes, join them

### Visual Walkthrough — Merge Two Sorted
```
L1: 1 → 3 → 5
L2: 2 → 4 → 6

dummy → ?
Compare 1 vs 2 → pick 1: dummy → 1
Compare 3 vs 2 → pick 2: dummy → 1 → 2
Compare 3 vs 4 → pick 3: dummy → 1 → 2 → 3
Compare 5 vs 4 → pick 4: dummy → 1 → 2 → 3 → 4
Compare 5 vs 6 → pick 5: dummy → 1 → 2 → 3 → 4 → 5
L1 exhausted, append L2: ... → 5 → 6

Result: 1 → 2 → 3 → 4 → 5 → 6
```

### Visual Walkthrough — Partition List (x=3)
```
List: 1 → 4 → 3 → 2 → 5 → 2

lessDummy → [nodes < 3]: 1 → 2 → 2
grtrDummy → [nodes ≥ 3]: 4 → 3 → 5

Connect: 2 → 4 → 3 → 5
Result: 1 → 2 → 2 → 4 → 3 → 5 ✓ (relative order preserved)
```

### When to Use
- "Merge two sorted linked lists" → dummy head, compare and pick
- "Partition list around value x" → two separate lists, then join
- "Odd-even linked list" → two separate lists (odd/even indexed), join
- "Add two numbers as linked lists" → digit-by-digit with carry
- "Find if linked list has cycle + next greater" → combine patterns

### Common Mistakes
1. Not terminating the greater-than list: set `grtr->next = nullptr` before joining
2. Off-by-one in odd-even: even starts at `head->next`; odd link advance before even
3. Add two numbers: don't forget final carry — `if (carry) tail->next = new Node(1)`
4. Merge sorted: when one list exhausted, append the rest (not one-by-one)

---

## 2. Revision Card

**Recognition Signal:** "merge sorted lists", "partition list", "odd-even", "add numbers as list"

**Core Idea:** Use a dummy head to avoid edge cases with empty/null lists. Build result by re-linking nodes (no new node allocation except for dummy and possibly carry).

**Trigger Keywords:** merge, sorted, partition, rearrange, odd-even, add numbers

**Complexity:** O(n+m) time, O(1) space for merging two lists

---

## 3. Interview Tell Signs

- "Merge two sorted linked lists" → dummy head + two pointers
- "Merge K sorted lists" → min-heap (P44) or divide-and-conquer
- "Partition around x" → two sub-lists
- "Odd-even rearrangement" → maintain two chains, join at end
- "Add two numbers" → traverse simultaneously, track carry
- "Multiply two numbers as lists" → handle like grade-school multiplication

---

## 4. C++ Template

```cpp
struct ListNode { int val; ListNode* next; ListNode(int v): val(v), next(nullptr){} };

// ── Merge Two Sorted Lists ────────────────────────────────────────────────────
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0); ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// ── Partition List ────────────────────────────────────────────────────────────
ListNode* partition(ListNode* head, int x) {
    ListNode lessD(0), grtrD(0);
    ListNode* less = &lessD, *grtr = &grtrD;
    while (head) {
        if (head->val < x) { less->next = head; less = less->next; }
        else { grtr->next = head; grtr = grtr->next; }
        head = head->next;
    }
    grtr->next = nullptr; // terminate greater list
    less->next = grtrD.next;
    return lessD.next;
}

// ── Odd-Even Linked List ──────────────────────────────────────────────────────
ListNode* oddEvenList(ListNode* head) {
    if (!head) return head;
    ListNode* odd = head, *even = head->next, *evenHead = even;
    while (even && even->next) {
        odd->next = even->next; odd = odd->next;
        even->next = odd->next; even = even->next;
    }
    odd->next = evenHead;
    return head;
}

// ── Add Two Numbers ───────────────────────────────────────────────────────────
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0); ListNode* tail = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) { sum += l1->val; l1 = l1->next; }
        if (l2) { sum += l2->val; l2 = l2->next; }
        carry = sum / 10;
        tail->next = new ListNode(sum % 10);
        tail = tail->next;
    }
    return dummy.next;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Merge Two Sorted):**
> "I'll use a dummy head to avoid special-casing the start. Two pointers iterate through both lists, always attaching the smaller node to the result. When one list runs out, I attach the remainder of the other. O(n+m) time, O(1) space since I'm reusing existing nodes."

**Verbal Script (Partition):**
> "Two dummy heads: one for values less than x, one for values at least x. Traverse once, splice each node onto the appropriate list. Connect the 'less' tail to the 'greater' head. Crucially, set the greater tail's next to null — otherwise we might have a cycle or garbage pointer."

**Checklist:**
- [ ] Merge: use dummy head; after loop, append remaining list
- [ ] Partition: terminate greater list with nullptr before joining
- [ ] Odd-even: save evenHead before loop; advance odd BEFORE even in each iteration
- [ ] Add two numbers: handle the case where carry remains after both lists exhausted
- [ ] All: no new node allocation except for add-two-numbers

---

## 6. Problems

### Problem 1: Merge Two Sorted Lists
**Difficulty:** Easy | **LC:** 21

```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0); ListNode* tail = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { tail->next = l1; l1 = l1->next; }
        else { tail->next = l2; l2 = l2->next; }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}
// Time: O(n+m) | Space: O(1)
// Recursive: return l1->val<=l2->val ? (l1->next=merge(l1->next,l2),l1) : (l2->next=merge(l1,l2->next),l2)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Partition List
**Difficulty:** Medium | **LC:** 86

```cpp
ListNode* partition(ListNode* head, int x) {
    ListNode ld(0), gd(0);
    ListNode* l = &ld, *g = &gd;
    while (head) {
        if (head->val < x) { l->next = head; l = l->next; }
        else { g->next = head; g = g->next; }
        head = head->next;
    }
    g->next = nullptr;
    l->next = gd.next;
    return ld.next;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Odd Even Linked List
**Difficulty:** Medium | **LC:** 328

```cpp
ListNode* oddEvenList(ListNode* head) {
    if (!head) return head;
    ListNode* odd = head, *even = head->next, *evenHead = even;
    while (even && even->next) {
        odd->next = even->next; odd = odd->next;
        even->next = odd->next; even = even->next;
    }
    odd->next = evenHead;
    return head;
}
// Time: O(n) | Space: O(1)
// Indices are 1-based: odd=1,3,5... even=2,4,6...
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Add Two Numbers
**Difficulty:** Medium | **LC:** 2

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0); ListNode* cur = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int s = carry;
        if (l1) { s += l1->val; l1 = l1->next; }
        if (l2) { s += l2->val; l2 = l2->next; }
        carry = s / 10;
        cur->next = new ListNode(s % 10);
        cur = cur->next;
    }
    return dummy.next;
}
// Time: O(max(n,m)) | Space: O(max(n,m)) for result
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Add Two Numbers II (Most Significant Digit First)
**Difficulty:** Medium | **LC:** 445

**Approach:** Reverse both lists, add, then reverse result. Or use stacks.

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    stack<int> s1, s2;
    while (l1) { s1.push(l1->val); l1 = l1->next; }
    while (l2) { s2.push(l2->val); l2 = l2->next; }
    int carry = 0;
    ListNode* head = nullptr;
    while (!s1.empty() || !s2.empty() || carry) {
        int s = carry;
        if (!s1.empty()) { s += s1.top(); s1.pop(); }
        if (!s2.empty()) { s += s2.top(); s2.pop(); }
        carry = s / 10;
        ListNode* node = new ListNode(s % 10);
        node->next = head; // insert at head (MSB first)
        head = node;
    }
    return head;
}
// Time: O(n+m) | Space: O(n+m) for stacks
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Merge K Sorted Lists
**Difficulty:** Hard | **LC:** 23

**Approach:** Min-heap of (value, node pointer). Pop minimum, push its next.

```cpp
ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b){ return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minH(cmp);
    for (ListNode* h : lists) if (h) minH.push(h);
    ListNode dummy(0); ListNode* tail = &dummy;
    while (!minH.empty()) {
        tail->next = minH.top(); minH.pop(); tail = tail->next;
        if (tail->next) minH.push(tail->next);
    }
    return dummy.next;
}
// Time: O(N log k) N=total nodes, k=num lists | Space: O(k)
// Alternative: divide-and-conquer pairwise merges: O(N log k) time
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Merge [1,3,5] and [2,4,6]. Trace the pointer movement.
<details><summary>Reveal</summary>
tail=dummy. Compare 1 vs 2 → pick 1. l1=3. Compare 3 vs 2 → pick 2. l2=4. Compare 3 vs 4 → pick 3. l1=5. Compare 5 vs 4 → pick 4. l2=6. Compare 5 vs 6 → pick 5. l1=null. Append l2: 6. Result: 1→2→3→4→5→6 ✓.
</details>

**Drill 2:** Partition [1,4,3,2,5,2] around x=3. Which nodes go to less? Which to greater?
<details><summary>Reveal</summary>
Less (<3): 1, 2, 2. Greater (≥3): 4, 3, 5. Connect: less tail (node 2) → 4 → 3 → 5 → null. Result: 1→2→2→4→3→5. Note: relative order preserved within each group ✓.
</details>

**Drill 3:** Odd-even list on [1,2,3,4,5]. Trace the two pointer advances.
<details><summary>Reveal</summary>
odd=1, even=2, evenHead=2. Iter1: 1.next=3(odd=3), 2.next=4(even=4). Iter2: 3.next=5(odd=5), 4.next=null(even=null). even=null → stop. odd.next=evenHead: 5.next=2. Result: 1→3→5→2→4 ✓.
</details>

**Drill 4:** Add [2,4,3] (342) and [5,6,4] (465). Trace carry.
<details><summary>Reveal</summary>
Digit 1: 2+5=7, carry=0 → node(7). Digit 2: 4+6=10, carry=1 → node(0). Digit 3: 3+4+1=8, carry=0 → node(8). No remaining carry. Result: 7→0→8 (represents 807 = 342+465) ✓.
</details>

**Drill 5:** Why does setting `g->next = nullptr` matter in partition before joining?
<details><summary>Reveal</summary>
The 'greater' tail's next still points to wherever it pointed in the original list — possibly a node that now belongs to the 'less' chain. If we don't null it, the greater chain may have a spurious link creating a cycle or pointing into the wrong section. Setting it null ensures the greater chain properly terminates before we append it to the less chain.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Merge two sorted | O(n+m) | O(1) |
| Partition list | O(n) | O(1) |
| Odd-even list | O(n) | O(1) |
| Add two numbers | O(max(n,m)) | O(max(n,m)) |
| Add two numbers II | O(n+m) | O(n+m) stacks |
| Merge K sorted (heap) | O(N log k) | O(k) |
| Merge K sorted (D&C) | O(N log k) | O(log k) |

---

## 9. Common Follow-up Questions

**Q: Can you merge K sorted lists without extra space?**
A: Divide-and-conquer pairwise merging: merge pairs, then merge results. Each round processes all N nodes in O(N) time over log k rounds → O(N log k) time, O(log k) recursion space (vs O(k) for the heap).

**Q: What if the linked lists have duplicates and you want a deduplicated merge?**
A: During merge, skip nodes where `tail->val == next_node->val`. Or after merging, do a second pass to remove consecutive duplicates.

**Q: Add two numbers: how would you handle very large lists efficiently?**
A: The current approach already handles arbitrarily long numbers in O(n) time. For strings instead of lists, same approach: right-to-left with carry.

---

## 10. Cross-Pattern Connections

- **P44 (K-Way Merge):** Merge K sorted lists is the canonical K-way merge with min-heap
- **P74 (Reverse Linked List):** Reverse + merge is a common two-step pattern
- **P75 (Slow/Fast Pointers):** Find middle is used before merge-sort split
- **P04 (Two Pointers):** Merge two sorted arrays uses same idea on contiguous memory
