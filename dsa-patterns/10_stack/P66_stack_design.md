# P66 — Stack Design Problems (Min Stack, Max Stack, Frequency Stack)

## 1. First-Timer Explanation

### What Is It?
**Stack design problems** extend the basic stack with additional operations (getMin, getMax, getFreq) in O(1). The key trick: instead of augmenting the stack externally, **store the extra information alongside each element** or maintain a parallel stack.

### Min Stack Insight
Naive approach: maintain a global minimum. Problem: when you pop the current minimum, you've lost the previous minimum. Solution: every time you push, also track what the minimum WAS at that point. This "snapshot" restores history on pop.

```
Push 3: stack=[(3, min=3)]
Push 5: stack=[(3, min=3), (5, min=3)]
Push 2: stack=[(3, min=3), (5, min=3), (2, min=2)]
Push 4: stack=[(3, min=3), (5, min=3), (2, min=2), (4, min=2)]

getMin() = 2

pop() removes (4, min=2): min still tracked in (2, min=2) at top
pop() removes (2, min=2): now top is (5, min=3), getMin()=3 ← restored!
```

### Frequency Stack
Keeps track of element frequencies. `pop()` removes the most frequently pushed element (ties broken by most recent). Uses:
- `freq[x]`: frequency of x
- `group[f]`: stack of elements at frequency f
- `maxFreq`: current maximum frequency

### When to Use
- "Design a stack that also returns the minimum in O(1)" → Min Stack
- "Pop the most frequent element" → Frequency Stack
- "Design a max stack with push/pop/peekMax" → augmented stack

---

## 2. Revision Card

**Recognition Signal:** "O(1) min/max", "frequency-based pop", "stack with history"

**Core Idea:** Store auxiliary information per element or maintain parallel tracking structure. On pop, the stored info restores the previous state.

**Trigger Keywords:** min stack, max stack, frequency, design stack, O(1)

**Complexity:** All operations O(1) for min/max stack, O(1) amortized for frequency stack

---

## 3. Interview Tell Signs

- "Design stack with O(1) getMin/getMax" → parallel min/max stack
- "Pop most frequent element" → frequency stack with group map
- "Stack with constant time all operations" → augmented stack

---

## 4. C++ Template

```cpp
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

// ── Min Stack ─────────────────────────────────────────────────────────────────
class MinStack {
    stack<pair<int,int>> stk; // {value, min_at_this_point}
public:
    void push(int val) {
        int curMin = stk.empty() ? val : min(val, stk.top().second);
        stk.push({val, curMin});
    }
    void pop() { stk.pop(); }
    int top() { return stk.top().first; }
    int getMin() { return stk.top().second; }
};

// ── Frequency Stack ───────────────────────────────────────────────────────────
class FreqStack {
    unordered_map<int,int> freq;      // element → frequency
    unordered_map<int, vector<int>> group; // frequency → [elements at that freq]
    int maxFreq = 0;
public:
    void push(int val) {
        freq[val]++;
        maxFreq = max(maxFreq, freq[val]);
        group[freq[val]].push_back(val);
    }
    int pop() {
        int val = group[maxFreq].back();
        group[maxFreq].pop_back();
        if (group[maxFreq].empty()) maxFreq--;
        freq[val]--;
        return val;
    }
};
```

---

## 5. How to Present in Interview

**Verbal Script (Min Stack):**
> "The challenge is restoring the minimum when the current minimum is popped. I solve this by storing the minimum AT EACH PUSH alongside the element as a pair. When I push, the new minimum is `min(val, current_top_min)`. When I pop, the top pair's min value represents the minimum for the remaining stack. All operations are O(1), O(n) space."

**Checklist:**
- [ ] Store (value, min_so_far) pairs, NOT just values
- [ ] getMin() reads the top pair's second element
- [ ] pop() removes the pair — min is automatically restored
- [ ] Alternative: maintain separate min_stack alongside main stack

---

## 6. Problems

### Problem 1: Min Stack
**Difficulty:** Medium | **LC:** 155

```cpp
class MinStack {
    stack<pair<int,int>> stk;
public:
    void push(int val) {
        int m = stk.empty() ? val : min(val, stk.top().second);
        stk.push({val, m});
    }
    void pop() { stk.pop(); }
    int top() { return stk.top().first; }
    int getMin() { return stk.top().second; }
};
// All operations: O(1) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Maximum Frequency Stack
**Difficulty:** Hard | **LC:** 895

```cpp
class FreqStack {
    unordered_map<int,int> freq;
    unordered_map<int,vector<int>> group;
    int maxFreq = 0;
public:
    void push(int val) {
        maxFreq = max(maxFreq, ++freq[val]);
        group[freq[val]].push_back(val);
    }
    int pop() {
        int val = group[maxFreq].back();
        group[maxFreq].pop_back();
        if (group[maxFreq].empty()) maxFreq--;
        freq[val]--;
        return val;
    }
};
// push/pop: O(1) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Implement Queue using Stacks
**Difficulty:** Easy | **LC:** 232

**Approach:** Two stacks. Push to `in`. Pop from `out`; if empty, transfer all from `in`.

```cpp
class MyQueue {
    stack<int> in, out;
    void transfer() { while (!in.empty()) { out.push(in.top()); in.pop(); } }
public:
    void push(int x) { in.push(x); }
    int pop() { if (out.empty()) transfer(); int t = out.top(); out.pop(); return t; }
    int peek() { if (out.empty()) transfer(); return out.top(); }
    bool empty() { return in.empty() && out.empty(); }
};
// push: O(1) | pop/peek: amortized O(1) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Implement Stack using Queues
**Difficulty:** Easy | **LC:** 225

```cpp
class MyStack {
    queue<int> q;
public:
    void push(int x) {
        q.push(x);
        for (int i = 0; i < (int)q.size()-1; i++) { q.push(q.front()); q.pop(); }
    }
    int pop() { int t = q.front(); q.pop(); return t; }
    int top() { return q.front(); }
    bool empty() { return q.empty(); }
};
// push: O(n) | pop/top: O(1) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Design a Stack With Increment Operation
**Difficulty:** Medium | **LC:** 1381

**Approach:** Lazy increment using an extra array. `inc[i]` = pending increment for elements at indices ≤ i.

```cpp
class CustomStack {
    vector<int> stk, inc;
    int sz = 0, maxSize;
public:
    CustomStack(int maxSize) : maxSize(maxSize), stk(maxSize), inc(maxSize, 0) {}
    void push(int x) { if (sz < maxSize) stk[sz++] = x; }
    int pop() {
        if (sz == 0) return -1;
        int val = stk[sz-1] + inc[sz-1];
        if (sz > 1) inc[sz-2] += inc[sz-1]; // propagate increment
        inc[sz-1] = 0;
        sz--;
        return val;
    }
    void increment(int k, int val) {
        if (sz > 0) inc[min(k, sz)-1] += val; // lazy: only mark the boundary
    }
};
// All operations: O(1) | Space: O(maxSize)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Min Stack: push [5,3,4,2,1], then pop twice. What is getMin() after?
<details><summary>Reveal</summary>
Stack of pairs: (5,5),(3,3),(4,3),(2,2),(1,1). Pop (1,1): top=(2,2), getMin()=2. Pop (2,2): top=(4,3), getMin()=3. Answer: 3.
</details>

**Drill 2:** Frequency Stack: push [5,7,5,7,4,5]. Pop three times. What do you get?
<details><summary>Reveal</summary>
freq: 5→3, 7→2, 4→1. maxFreq=3. group[1]=[5,7,4], group[2]=[5,7], group[3]=[5]. Pop1: group[3].back()=5, maxFreq=2. Pop2: group[2].back()=7, maxFreq=2. Pop3: group[2].back()=5, maxFreq=1. Pops: [5, 7, 5].
</details>

**Drill 3:** Queue using two stacks: push 1,2,3 then pop. How many elements move from `in` to `out`?
<details><summary>Reveal</summary>
After pushing: in=[1,2,3], out=[]. Pop: out is empty → transfer all 3 from in: out=[3,2,1] (reversed). Pop from out: 1. So 3 elements move. Next pop is O(1) from out=[3,2] (no transfer needed).
</details>

**Drill 4:** Custom Stack with lazy increment: push [1,2,3], increment(2, 100), pop. What's returned?
<details><summary>Reveal</summary>
After push: stk=[1,2,3], inc=[0,0,0], sz=3. increment(2,100): min(2,3)=2, inc[1]+=100 → inc=[0,100,0]. Pop: val = stk[2]+inc[2] = 3+0=3. propagate: inc[1] += inc[2]=0. sz=2. Return 3. Next pop: val=stk[1]+inc[1]=2+100=102. Return 102.
</details>

**Drill 5:** Alternative Min Stack approach — separate min stack. What's the tradeoff vs pair approach?
<details><summary>Reveal</summary>
Separate min stack: push to min_stack only when new element ≤ current min. Pop from min_stack only when popped element == min_stack.top(). Advantage: saves space when many elements are pushed above the current min. Pair approach: always stores min at every level — uses more space but simpler logic.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Min Stack | Freq Stack | Queue (2 stacks) |
|-----------|-----------|------------|------------------|
| push | O(1) | O(1) | O(1) |
| pop | O(1) | O(1) | O(1) amortized |
| peek/top | O(1) | O(1) | O(1) amortized |
| getMin | O(1) | — | — |

---

## 9. Common Follow-up Questions

**Q: Max Stack with popMax() in O(log n)?**
A: Use a doubly-linked list + max-heap of (value, pointer). Pop the max from heap, delete from linked list via pointer. O(log n) per operation.

**Q: Min Stack with O(1) extra space?**
A: Mathematical trick. Push `2*val - curMin`. If popped value < curMin, it was the minimum — restore previous min from `2*curMin - val`. Complex but O(1) extra space.

**Q: Thread-safe MinStack?**
A: Use mutex around push/pop/getMin. Or use lock-free data structures (more complex).

---

## 10. Cross-Pattern Connections

- **P64 (Monotonic Stack):** Both use stacks; min stack tracks global min, monotonic tracks local boundaries
- **P43 (Two Heaps):** Both solve "running median/min/max" problems
- **P93 (LRU Cache):** Another classic "design with O(1) operations" problem
- **P65 (Expression Eval):** Both use stacks; this for meta-information tracking
