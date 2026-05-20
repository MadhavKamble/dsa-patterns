# Pattern 02: Fast & Slow Pointers

## Category
Two Pointers

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 141. Linked List Cycle | Easy | https://leetcode.com/problems/linked-list-cycle/ |
| 2 | 202. Happy Number | Easy | https://leetcode.com/problems/happy-number/ |
| 3 | 287. Find the Duplicate Number | Medium | https://leetcode.com/problems/find-the-duplicate-number/ |
| 4 | 392. Is Subsequence | Easy | https://leetcode.com/problems/is-subsequence/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Imagine two runners on a circular track — one slow (1 step at a time) and one fast (2 steps at a time). If there's a cycle, the fast runner will eventually lap the slow one and they'll be at the same position. If there's no cycle, the fast runner will reach the end first.

This is **Floyd's Cycle Detection Algorithm**. It detects cycles without needing extra memory (no "visited" set).

The pattern extends beyond cycles:
- **Find middle of linked list**: when fast reaches end, slow is at middle
- **Detect duplicate in range [1,n]**: treat array values as "next" pointers → becomes a linked list cycle problem

### Real-World Analogy
Two cars on a highway: one at 60 km/h, one at 120 km/h. If the highway loops, the faster car will eventually catch up to the slower car. If the highway ends, the faster car hits the end first. The meeting point tells you about the structure of the road.

### Visual Walkthrough
```
Cycle detection:
  Linked list: 1 → 2 → 3 → 4 → 5 → 3 (cycle back to node 3)

  slow  fast
  1     1    (start)
  2     3    (slow:1step, fast:2steps)
  3     5    
  4     4    ← they meet! (both at node 4)  CYCLE DETECTED

No cycle:
  1 → 2 → 3 → 4 → null

  slow  fast
  1     1
  2     3
  3     null ← fast is null → NO CYCLE

Find middle:
  1 → 2 → 3 → 4 → 5

  slow=1  fast=1
  slow=2  fast=3
  slow=3  fast=5 → fast.next==null → slow=3 is MIDDLE
```

### When TO use this pattern
- Detect cycle in linked list or sequence
- Find middle of linked list (with one pass)
- Find start of cycle
- Problem maps to "array values as pointers" (detect duplicate)
- Check if a number is "happy" (sequence eventually cycles or reaches 1)

### When NOT to use this pattern
- Problem involves array indices, not linked-list-like traversal
- Need to find ALL cycle members (use DFS instead)
- Random access is needed (use index-based two pointers)

### Common Beginner Mistakes
- **Null check**: always check `fast != null && fast->next != null` before advancing fast
- **Starting point**: both start at head, not fast at head->next
- **Is Subsequence**: this uses same-direction pointers (not cycle), not fast/slow exactly — classified here because of the two-pointer nature
- **Duplicate number**: forgetting phase 2 — after finding meeting point, you need a second phase to find cycle entry point

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "detect cycle", "find middle", "duplicate in [1,n] array" |
| Core Idea | Slow moves 1 step, fast moves 2; they meet iff cycle exists |
| Trigger Keywords | "linked list cycle", "happy number", "duplicate", "no extra memory" |
| Avoid When | Need path details, random access array problems |
| Time Complexity | O(n) |
| Space Complexity | O(1) |

**Gotchas:**
- Check `fast && fast->next` before advancing, not just `fast`
- To find ENTRY of cycle: after meeting, reset one pointer to head, advance both 1 step at a time — they meet at cycle start
- Happy number: the digit-sum function creates a sequence that either reaches 1 (happy) or loops

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"detect cycle"` → classic fast/slow on linked list
- `"find duplicate number"` + "O(1) space" + array values in [1,n] → treat as linked list
- `"happy number"`, `"eventually reach"`, `"cycle in sequence"` → fast/slow on number sequence
- `"is subsequence"` → two pointers moving right on two separate sequences

### Constraint hints
- No extra memory allowed → rules out visited set → fast/slow is the way
- Array of n+1 integers with values in [1,n] → pigeonhole says duplicate exists → Floyd's

---

## 4. C++ Template

```cpp
/*
 * Pattern: Fast & Slow Pointers
 * Use when: cycle detection, find middle, duplicate in range
 * Time: O(n) | Space: O(1)
 */

struct ListNode { int val; ListNode* next; };

// CYCLE DETECTION
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {  // check BOTH fast and fast->next
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;  // cycle: they meet
    }
    return false;  // fast reached end: no cycle
}

// FIND MIDDLE
ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;  // slow is at middle when fast reaches end
}

// FIND CYCLE START (Floyd's Phase 2)
ListNode* detectCycleStart(ListNode* head) {
    ListNode* slow = head, *fast = head;
    bool hasCycle = false;

    // Phase 1: find meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) { hasCycle = true; break; }
    }
    if (!hasCycle) return nullptr;

    // Phase 2: move one pointer to head, advance both 1 step at a time
    ListNode* ptr = head;
    while (ptr != slow) {
        ptr = ptr->next;
        slow = slow->next;
    }
    return slow;  // meeting point = cycle start
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I see this is a linked list cycle problem with a constraint of O(1) extra space.
The brute force would be to store every visited node in a hash set — but that's O(n) space.
Floyd's cycle detection gives us O(1): I use two pointers — slow advances 1 step, fast advances 2 steps.
If there's a cycle, fast will eventually lap slow, and they'll meet.
If there's no cycle, fast will hit null first.
Let me code this up..."

### What to TYPE as comments while coding live
```cpp
// PROBLEM RESTATEMENT: detect cycle in linked list with O(1) space
// BRUTE FORCE: hash set of visited nodes → O(n) space
// OPTIMIZATION: Floyd's algorithm → O(1) space
// APPROACH: slow = 1 step, fast = 2 steps; meet iff cycle

// EDGE CASES to handle:
// - empty list (head == null)
// - single node with no self-loop
// - cycle at the head itself

// COMPLEXITY: Time O(n) | Space O(1)
```

### Interview Flow Checklist
- [ ] Clarify: can there be a self-loop (node points to itself)?
- [ ] State brute force (hash set)
- [ ] Explain Floyd's algorithm intuitively
- [ ] Code with null-safety checks
- [ ] Dry run on a list with a cycle
- [ ] State complexity

---

## 6. Problems

---

### Problem 1: 141. Linked List Cycle
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/linked-list-cycle/
**Why this pattern fits:** Classic cycle detection — fast/slow pointers meet iff cycle exists

**Problem Summary:**
Given head of a linked list, return true if there is a cycle in it (some node's next pointer points back to a previous node).

**Approach Walkthrough:**
1. slow and fast both start at head
2. Advance slow 1 step, fast 2 steps each iteration
3. If they ever point to the same node → cycle exists
4. If fast or fast->next becomes null → no cycle

**Optimal C++ Solution:**
```cpp
// Linked List Cycle
// Approach: Floyd's fast & slow pointers
// Time: O(n) | Space: O(1)

bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;          // 1 step
        fast = fast->next->next;    // 2 steps
        if (slow == fast) return true;  // met → cycle
    }
    return false;  // fast reached null → no cycle
}
```

**Complexity Analysis:**
- Time: O(n) — in a cycle of length c, fast laps slow after at most c steps
- Space: O(1)

**Edge Cases:**
- [ ] Empty list (head == null)
- [ ] Single node, no cycle
- [ ] Single node with self-loop (next points to itself)

**Interview Follow-up Questions:**
- How do you find WHERE the cycle starts? (Phase 2 of Floyd's)
- How do you find the LENGTH of the cycle? (After meeting, keep one pointer fixed, advance the other until they meet again)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

### Problem 2: 287. Find the Duplicate Number
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-the-duplicate-number/
**Why this pattern fits:** Array of n+1 numbers in [1,n] → treat values as next pointers → linked list with cycle → cycle entry = duplicate

**Problem Summary:**
Array of n+1 integers where each value is in [1,n]. Exactly one number is duplicated. Find it without modifying the array, O(1) extra space.

**Approach Walkthrough:**
1. The array creates a "linked list": index 0 → arr[0] → arr[arr[0]] → ...
2. The duplicate value means two indices point to the same "next" → cycle!
3. Use Floyd's algorithm on this virtual linked list
4. Phase 1: find meeting point
5. Phase 2: find cycle entry = the duplicate number

**Optimal C++ Solution:**
```cpp
// Find the Duplicate Number
// Approach: Floyd's cycle detection on array-as-linked-list
// Time: O(n) | Space: O(1)

int findDuplicate(vector<int>& nums) {
    // treat array as linked list: i → nums[i]
    int slow = nums[0];
    int fast = nums[0];

    // Phase 1: find meeting point inside cycle
    do {
        slow = nums[slow];           // 1 step
        fast = nums[nums[fast]];     // 2 steps
    } while (slow != fast);

    // Phase 2: find cycle entry (= duplicate number)
    int ptr = nums[0];
    while (ptr != slow) {
        ptr  = nums[ptr];
        slow = nums[slow];
    }
    return slow;  // cycle entry = duplicate
}
```

**Complexity Analysis:**
- Time: O(n)
- Space: O(1) — no modification, no extra arrays

**Edge Cases:**
- [ ] Duplicate appears more than twice
- [ ] Duplicate is the largest possible value (n)

**Interview Follow-up Questions:**
- Why can't we sort? (Problem says don't modify array — sorting counts as modification)
- If we could use O(n) space, what's simpler? (Boolean visited array or count array)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

### Problem 3: 202. Happy Number
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/happy-number/
**Why this pattern fits:** The sum-of-squares sequence either terminates at 1 (happy) or loops forever — detect cycle with fast/slow

**Problem Summary:**
A "happy number" is one where repeatedly replacing the number with the sum of squares of its digits eventually reaches 1. If it loops without reaching 1, it's not happy.

**Approach Walkthrough:**
1. Define a function `next(n)` that computes sum of squares of digits
2. Apply fast/slow pointers on this sequence
3. If fast (applying `next` twice per step) ever equals 1 → happy
4. If slow and fast meet at a non-1 value → cycle → not happy

**Optimal C++ Solution:**
```cpp
// Happy Number
// Approach: fast & slow on the digit-sum sequence
// Time: O(log n) per step, bounded iterations | Space: O(1)

int digitSquareSum(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n;
    int fast = n;

    do {
        slow = digitSquareSum(slow);               // 1 step
        fast = digitSquareSum(digitSquareSum(fast)); // 2 steps
    } while (slow != fast);

    return slow == 1;  // if they meet at 1 → happy; else → cycle
}
```

**Complexity Analysis:**
- Time: O(log n) — bounded by the number of digits and known cycle length
- Space: O(1)

**Edge Cases:**
- [ ] n = 1 (already happy)
- [ ] n = 4 (enters the known unhappy cycle: 4→16→37→58→89→145→42→20→4)

**Interview Follow-up Questions:**
- Why does the sequence always either reach 1 or cycle? (Numbers with more digits always decrease toward single digits, so the range is bounded)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

### Problem 4: 392. Is Subsequence
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/is-subsequence/
**Why this pattern fits:** Two pointers moving right on s and t respectively — check if all of s appears in t in order

**Problem Summary:**
Given strings s and t, return true if s is a subsequence of t (all characters of s appear in t in order, not necessarily contiguous).

**Approach Walkthrough:**
1. Pointer i for s, pointer j for t
2. When s[i] == t[j]: advance both
3. Always advance j
4. If i reaches end of s: s is a subsequence

**Optimal C++ Solution:**
```cpp
// Is Subsequence
// Approach: two pointers scanning both strings left to right
// Time: O(|t|) | Space: O(1)

bool isSubsequence(string s, string t) {
    int i = 0, j = 0;  // i scans s, j scans t

    while (i < (int)s.size() && j < (int)t.size()) {
        if (s[i] == t[j]) i++;  // match: advance s pointer
        j++;                     // always advance t pointer
    }
    return i == (int)s.size();  // did we match all of s?
}
```

**Complexity Analysis:**
- Time: O(|t|) — j always advances
- Space: O(1)

**Edge Cases:**
- [ ] Empty s (always true)
- [ ] s longer than t
- [ ] s not in t at all

**Interview Follow-up Questions:**
- If there are 10^9 queries of s against the same t, what's more efficient? (Precompute next-occurrence array for each character at each position in t, then answer each query in O(|s| log |t|))

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```
**My Notes:** *(fill this in after solving)*

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a sequence generated by a function f(x) where the domain and codomain are both [1, N]. Given a starting point, determine if the sequence eventually revisits a value.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Fast & Slow Pointers
**Subpattern:** Cycle detection in implicit linked list
**Reason:** Any finite-domain function applied repeatedly either terminates or cycles. Fast/slow detects this in O(n) time, O(1) space.

</details>

---

**Drill 2:**
> Given a singly linked list, check if it is a palindrome using O(1) extra space.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Fast & Slow Pointers (combined with in-place reversal)
**Subpattern:** Find middle, reverse second half
**Reason:** Use fast/slow to find the middle, reverse the second half of the list, compare with the first half. This achieves O(n) time and O(1) space.

</details>

---

**Drill 3:**
> Find the node at the beginning of a cycle in a linked list (not just detect it).

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Fast & Slow Pointers — Floyd's Phase 2
**Subpattern:** Cycle entry detection
**Reason:** Phase 1 finds meeting point inside cycle. Phase 2: reset one pointer to head, advance both 1 step. Mathematical proof shows they meet exactly at the cycle entry node.

</details>

---

**Drill 4:**
> Given a string s and pattern p, check if all characters of p appear in s in the same order (but not necessarily contiguous). Return the index in s where matching ends.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Fast & Slow (or Two Pointers same direction)
**Subpattern:** Is Subsequence variant
**Reason:** Standard subsequence check — i on p, j on s, advance both on match, only j otherwise. Return j when i == p.size().

</details>

---

**Drill 5:**
> An array contains integers in the range [0, n-1]. Each value can be used as an index into the array. Starting from index 0, follow the chain of values. Determine if you'll ever revisit index 0.

<details>
<summary>Click to reveal answer</summary>

**Pattern:** Fast & Slow Pointers
**Subpattern:** Cycle detection starting from specific node
**Reason:** The array defines a functional graph (each node has exactly one outgoing edge). Fast/slow detects cycles. Since we start at 0, if 0 is in a cycle, we'll revisit it; if it leads to a cycle not containing 0, we won't.

</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Cycle detection | O(n) | O(1) | Fast catches slow within one loop pass |
| Find middle | O(n) | O(1) | Fast reaches end while slow is at middle |
| Find cycle start | O(n) | O(1) | Two phases, each O(n) |
| Duplicate in [1,n] array | O(n) | O(1) | Floyd's on virtual linked list |
| Is Subsequence | O(\|t\|) | O(1) | j always advances through t |

---

## 9. Common Follow-up Questions

1. How do you find the length of the cycle? (After meeting, keep one pointer fixed, advance the other, count steps until they meet again)
2. How do you remove the cycle? (Find cycle start with Phase 2, then find the last node in the cycle that points back to start, set its next to null)
3. Can this work on doubly linked lists? (Yes, same logic applies)
4. What if there are multiple cycles? (Each connected component can be checked independently; Floyd's finds if a cycle is reachable from start)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| In-place Reversal | Palindrome linked list check | Reverse second half after finding middle |
| Binary Search | Find duplicate with different constraints | If modification is allowed: binary search on value |
| Hashing | When O(n) space is acceptable | Use visited set instead of Floyd's |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
