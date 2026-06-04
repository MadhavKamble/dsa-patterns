# P69 — Simulation with Stack (Asteroid Collision and Variants)

## 1. First-Timer Explanation

### What Is It?
**Simulation with stack** handles problems where elements interact with each other based on rules — particularly "collisions" or "cancellations" between neighboring elements. The stack naturally models the "current state" of surviving elements.

### Asteroid Collision Core Idea
```
Asteroids moving: positive = right, negative = left
Only right-moving and left-moving asteroids can collide.

[5, 10, -5]:
Stack: [5]. Push 10: [5,10]. Push -5:
  -5 collides with 10: |-5| < |10| → -5 destroyed. Stack: [5,10]. ✓ Result: [5,10]

[8, -8]:
Stack: [8]. Push -8:
  -8 collides with 8: equal size → both destroyed. Stack: []. Result: []

[10, 2, -5]:
Stack: [10]. Push 2: [10,2]. Push -5:
  -5 vs 2: |-5| > |2| → 2 destroyed. Stack: [10].
  -5 vs 10: |-5| < |10| → -5 destroyed. Stack: [10]. Result: [10]
```

### When to Use
- "Elements collide based on direction/sign" → stack simulation
- "Remove adjacent duplicates" → stack
- "Remove K adjacent duplicates" → stack with counts
- "Number after removing duplicates satisfying rule" → stack

### Common Mistakes
1. Collision only happens when positive right meets negative left (not left vs left or right vs right)
2. Equal-size collision: both are destroyed (don't forget this case)
3. Remove K adjacent: track counts alongside values

---

## 2. Revision Card

**Recognition Signal:** "collision", "remove when equal", "adjacent elements interact", "surviving elements"

**Core Idea:** Stack holds current "survivors." When new element enters, check if it interacts with stack top. Process interaction (destroy one/both) repeatedly until stable. Push new element if it survives.

**Trigger Keywords:** collision, asteroid, adjacent duplicates, remove, destroy

**Complexity:** O(n) time (each element pushed/popped once), O(n) space

---

## 3. Interview Tell Signs

- "Asteroids/particles collide" → stack collision simulation
- "Remove adjacent duplicate characters" → stack push/pop
- "Remove all adjacent duplicates of length k" → stack of (char, count)
- "Score of parentheses" → stack-based simulation

---

## 4. C++ Template

```cpp
#include <stack>
#include <vector>
#include <string>
using namespace std;

// ── Asteroid Collision ────────────────────────────────────────────────────────
vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> stk;
    for (int a : asteroids) {
        bool alive = true;
        while (alive && a < 0 && !stk.empty() && stk.top() > 0) {
            if (stk.top() < -a) { stk.pop(); }      // stack asteroid destroyed
            else if (stk.top() == -a) { stk.pop(); alive = false; } // both destroyed
            else { alive = false; }                   // new asteroid destroyed
        }
        if (alive) stk.push(a);
    }
    vector<int> res;
    while (!stk.empty()) { res.push_back(stk.top()); stk.pop(); }
    reverse(res.begin(), res.end());
    return res;
}

// ── Remove Adjacent Duplicates ────────────────────────────────────────────────
string removeDuplicates(string s) {
    string stk;
    for (char c : s) {
        if (!stk.empty() && stk.back() == c) stk.pop_back();
        else stk += c;
    }
    return stk;
}

// ── Remove K Adjacent Duplicates ─────────────────────────────────────────────
string removeDuplicatesK(string s, int k) {
    stack<pair<char,int>> stk; // {char, count}
    for (char c : s) {
        if (!stk.empty() && stk.top().first == c) {
            stk.top().second++;
            if (stk.top().second == k) stk.pop();
        } else {
            stk.push({c, 1});
        }
    }
    string res;
    while (!stk.empty()) {
        res += string(stk.top().second, stk.top().first); stk.pop();
    }
    reverse(res.begin(), res.end());
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Asteroid Collision):**
> "I use a stack to track surviving asteroids. For each new asteroid: if it's positive, push it (moves right, no collision). If it's negative, it might collide with the rightmost positive asteroid on the stack. I loop: if the stack top is positive and smaller, pop it (destroyed). If equal, pop both (both destroyed). If stack top is positive and larger, the new asteroid is destroyed. The loop stops when the new asteroid is destroyed, the stack is empty, or the top is negative (moving same direction). If the new asteroid survives, push it."

**Checklist:**
- [ ] Collision only when: stack.top() > 0 AND new asteroid < 0
- [ ] Three cases: top wins, equal (both die), new wins (continue)
- [ ] `alive` flag to break the inner loop
- [ ] Push if alive at the end

---

## 6. Problems

### Problem 1: Asteroid Collision
**Difficulty:** Medium | **LC:** 735

```cpp
vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> stk;
    for (int a : asteroids) {
        bool alive = true;
        while (alive && a < 0 && !stk.empty() && stk.top() > 0) {
            if (stk.top() < -a) stk.pop();
            else if (stk.top() == -a) { stk.pop(); alive = false; }
            else alive = false;
        }
        if (alive) stk.push(a);
    }
    vector<int> res;
    while (!stk.empty()) { res.push_back(stk.top()); stk.pop(); }
    reverse(res.begin(), res.end());
    return res;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Remove All Adjacent Duplicates in String
**Difficulty:** Easy | **LC:** 1047

```cpp
string removeDuplicates(string s) {
    string stk;
    for (char c : s) {
        if (!stk.empty() && stk.back() == c) stk.pop_back();
        else stk += c;
    }
    return stk;
}
// Time: O(n) | Space: O(n)
// String used as stack (appending/popping from back)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Remove All Adjacent Duplicates in String II (k duplicates)
**Difficulty:** Medium | **LC:** 1209

```cpp
string removeDuplicates(string s, int k) {
    stack<pair<char,int>> stk;
    for (char c : s) {
        if (!stk.empty() && stk.top().first == c) {
            stk.top().second++;
            if (stk.top().second == k) stk.pop();
        } else stk.push({c, 1});
    }
    string res;
    while (!stk.empty()) { res += string(stk.top().second, stk.top().first); stk.pop(); }
    reverse(res.begin(), res.end());
    return res;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Score of Parentheses
**Difficulty:** Medium | **LC:** 856

**Approach:** Stack of scores. `(` → push 0. `)` → pop; if top was 0 (empty inner): score = 1; else score = 2*v. Add to new top.

```cpp
int scoreOfParentheses(string s) {
    stack<int> stk;
    stk.push(0); // base score
    for (char c : s) {
        if (c == '(') stk.push(0);
        else {
            int v = stk.top(); stk.pop();
            stk.top() += max(2*v, 1); // () = 1, (X) = 2*X
        }
    }
    return stk.top();
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: 132 Pattern Detection
**Difficulty:** Medium | **LC:** 456

**Approach:** Scan right to left. Maintain a stack and `third` (the "2" in pattern 132, i.e., the largest value ever popped). If current element < third, we found the pattern.

```cpp
bool find132pattern(vector<int>& nums) {
    int n = nums.size(), third = INT_MIN;
    stack<int> stk; // decreasing stack (candidates for "3" in 132)
    for (int i = n-1; i >= 0; i--) {
        if (nums[i] < third) return true; // nums[i] is "1", third is "2", stk.top is "3"
        while (!stk.empty() && stk.top() < nums[i]) {
            third = stk.top(); stk.pop(); // nums[i] is "3", popped is "2"
        }
        stk.push(nums[i]);
    }
    return false;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Asteroid collision [10, -5, -10, -15]. What survives?
<details><summary>Reveal</summary>
Stack: push 10. -5: 10>5, -5 destroyed, stack=[10]. -10: 10==10, both destroyed, stack=[]. -15: stack empty, push -15, stack=[-15]. Result: [-15].
</details>

**Drill 2:** Remove adjacent duplicates from "aabbccddeeff".
<details><summary>Reveal</summary>
Stack trace: a→"a", a==top→pop, "". b→"b", b==top→pop, "". ... All pairs cancel: result = "" (empty string).
</details>

**Drill 3:** Remove k=3 adjacent duplicates from "aaabcccbbad".
<details><summary>Reveal</summary>
Stack: a(1)→a(2)→a(3)→pop(aaa gone)→[]. b(1). c(1)→c(2)→c(3)→pop→[b(1)]. b(2)→b(3)... wait: after removing aaa, stack=[], then b(1). Stack at 'b': [(b,1)]. Then c: [(b,1),(c,1)]. c: [(b,1),(c,2)]. c: [(b,1),(c,3)]→pop→[(b,1)]. b: [(b,2)]. b: [(b,3)]→pop→[]. a(1). d(1). Result: "ad".
</details>

**Drill 4:** Score of parentheses "(()(()))". Apply the stack algorithm.
<details><summary>Reveal</summary>
Push 0. '(': push 0. '(': push 0. ')': v=0, top gets max(1,0)=1 → stack=[0,1]. '(': push 0. '(': push 0. ')': v=0, top gets 1 → stack=[0,1,1]. ')': v=1, top gets 2 → stack=[0,3]. ')': v=3, top gets 6 → stack=[6]. ')' (extra): v=6, base gets 6. Wait the string "(()(()))" has 8 chars. Let me redo: Push 0. '(': push 0 → [0,0]. '(': push 0 → [0,0,0]. ')': v=0, stack=[0,0], stack.top()+=1 → [0,1]. '(': push 0 → [0,1,0]. '(': push 0 → [0,1,0,0]. ')': v=0, [0,1,0], top+=1 → [0,1,1]. ')': v=1, [0,1], top+=2 → [0,3]. ')': v=3, [0], top+=6 → [6]. Answer: 6. ✓
</details>

**Drill 5:** 132 Pattern: why scan right to left?
<details><summary>Reveal</summary>
We need to find i < j < k with nums[i] < nums[k] < nums[j]. Scanning right to left: for each position i, we want to know if there's a valid (j,k) to its right. The stack maintains decreasing candidates for "3" (nums[j]); `third` tracks the best "2" (nums[k]). If current element < third, we found "1".
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Asteroid Collision | O(n) | O(n) |
| Remove Adjacent Dups | O(n) | O(n) |
| Remove K Adjacent Dups | O(n) | O(n) |
| Score of Parentheses | O(n) | O(n) |
| 132 Pattern | O(n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: What if asteroids can also have the same direction?**
A: They never collide — only right-moving vs left-moving can collide. Same direction: always push.

**Q: Remove until no more adjacent duplicates remain?**
A: The single-pass stack algorithm already handles this! Each element is pushed and potentially popped with its match. By the end, no two adjacent elements are equal.

**Q: Can you solve 132 Pattern in O(n)?**
A: Yes — the stack approach shown is O(n). Naive O(n²) triple loop, O(n log n) with sorted structures, O(n) with stack.

---

## 10. Cross-Pattern Connections

- **P64 (Monotonic Stack):** Same mechanism; collision = pop when condition met
- **P65 (Expression Eval):** Both use stack for "interaction" simulation
- **P55 (Greedy Strings):** Remove K digits is another "pop when condition" stack problem
- **P04 (Two Pointers):** 3Sum variant: i < j < k pattern with different constraints
