# P55 — Greedy String Problems

## 1. First-Timer Explanation

### What Is It?
**Greedy string problems** build or transform strings by making locally optimal character choices at each step. The key patterns:
1. **Monotone stack greedy:** Remove k characters to get smallest/largest number
2. **Character frequency greedy:** Reorganize/interleave strings by frequency
3. **Scan greedy:** Count operations (brackets, partitions) by scanning left to right

### Analogy — Remove k Digits for Smallest Number
Imagine you have a height chart: [4, 3, 2, 5, 6, 1, 2] and must remove 3 bars. For the smallest result, always remove a bar when the next bar is shorter (a "descent") — the taller bar is locally worse. Use a stack to track the current "non-decreasing" sequence.

### Visual Walkthrough — "1432219", k=3
```
Stack: []
'1': stack=[1]
'4': 4 > 1, push → stack=[1,4]
'3': 3 < 4 → pop 4 (k=2), 3>1 push → stack=[1,3]
'2': 2 < 3 → pop 3 (k=1), 2>1 push → stack=[1,2]
'2': equal, push → stack=[1,2,2]
'1': 1 < 2 → pop 2 (k=0, done) → stack=[1,2]
push 1 → [1,2,1]
'9': push → [1,2,1,9]

Result: "1219"
Remove leading zeros if any. Return "1219" ✓
```

### When to Use
- "Remove k digits to form smallest/largest number"
- "Minimum number of brackets/operations"
- "Reorganize string with constraint"
- "Partition string into parts"
- "Minimum swaps to sort"

### When NOT to Use
- Global optimization across all characters → DP
- Order matters in non-trivial ways → DP

### Common Mistakes
1. Remove k digits: forgetting to handle remaining k removals from end of stack
2. Not stripping leading zeros
3. Min add to make valid parentheses: two-pass approach or single pass with open counter

---

## 2. Revision Card

**Recognition Signal:** "remove/add chars to get smallest/valid", "reorganize string", "balance brackets"

**Core Idea:** Monotone stack for "remove to minimize": pop when `stack.top() > cur && k > 0`. For brackets: track open count; when `)` but open=0, need insertion.

**Trigger Keywords:** remove k, smallest number, valid parentheses, add minimum, partition

**Complexity:** O(n) for most greedy string problems

---

## 3. Interview Tell Signs

- "Remove k digits, smallest result" → monotone stack greedy
- "Minimum insertions for valid parens" → count unmatched with two passes or one pass
- "Partition string, each char in exactly one part" → last occurrence greedy
- "Minimum swaps to make two strings equal" → count mismatches

---

## 4. C++ Template

```cpp
#include <string>
#include <stack>
using namespace std;

// ── Remove K Digits (smallest result) ────────────────────────────────────────
string removeKdigits(string num, int k) {
    string stack; // used as monotone stack
    for (char c : num) {
        while (k > 0 && !stack.empty() && stack.back() > c) {
            stack.pop_back(); k--;
        }
        stack += c;
    }
    // If k remains, remove from end
    while (k-- > 0) stack.pop_back();
    // Strip leading zeros
    int start = stack.find_first_not_of('0');
    return start == string::npos ? "0" : stack.substr(start);
}

// ── Minimum Add to Make Parentheses Valid ────────────────────────────────────
int minAddToMakeValid(string s) {
    int open = 0, close = 0;
    for (char c : s) {
        if (c == '(') open++;
        else if (open > 0) open--; // match
        else close++;              // unmatched ')'
    }
    return open + close;
}

// ── Partition Labels ─────────────────────────────────────────────────────────
vector<int> partitionLabels(string s) {
    int last[26] = {};
    for (int i = 0; i < (int)s.size(); i++) last[s[i]-'a'] = i;
    
    vector<int> res;
    int start = 0, end = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        end = max(end, last[s[i]-'a']);
        if (i == end) { res.push_back(end - start + 1); start = i + 1; }
    }
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Remove K Digits):**
> "I want the smallest number, so I want digits in non-decreasing order as much as possible. I use a monotone stack: when the current digit is smaller than the stack top, pop the top (that's a removal) and decrement k. After processing all digits, if k > 0, remove from the right (right = less significant). Finally, strip leading zeros."

**Checklist:**
- [ ] Remove K: pop when `stack.top > cur && k > 0`
- [ ] Handle remaining k removals from the back
- [ ] Strip leading zeros
- [ ] Partition Labels: precompute last occurrence, extend partition end greedily

---

## 6. Problems

### Problem 1: Remove K Digits (Smallest Number)
**Difficulty:** Medium | **LC:** 402

```cpp
string removeKdigits(string num, int k) {
    string res;
    for (char c : num) {
        while (k && !res.empty() && res.back() > c) { res.pop_back(); k--; }
        res += c;
    }
    while (k--) res.pop_back();
    int start = res.find_first_not_of('0');
    return start == string::npos ? "0" : res.substr(start);
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Largest Number
**Difficulty:** Medium | **LC:** 179

**Approach:** Custom comparator: `a+b > b+a` (string concatenation comparison).

```cpp
string largestNumber(vector<int>& nums) {
    vector<string> strs;
    for (int n : nums) strs.push_back(to_string(n));
    sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
        return a + b > b + a;
    });
    if (strs[0] == "0") return "0";
    string res;
    for (auto& s : strs) res += s;
    return res;
}
// Time: O(n log n * k) where k = max digit length | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Minimum Add to Make Parentheses Valid
**Difficulty:** Medium | **LC:** 921

```cpp
int minAddToMakeValid(string s) {
    int open = 0, add = 0;
    for (char c : s) {
        if (c == '(') open++;
        else if (open > 0) open--;
        else add++;
    }
    return open + add; // unmatched '(' + unmatched ')'
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Partition Labels
**Difficulty:** Medium | **LC:** 763

**Approach:** Last occurrence of each char determines partition boundary. Extend greedily.

```cpp
vector<int> partitionLabels(string s) {
    int last[26] = {};
    for (int i = 0; i < (int)s.size(); i++) last[s[i]-'a'] = i;
    vector<int> res;
    int start = 0, end = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        end = max(end, last[s[i]-'a']);
        if (i == end) { res.push_back(end-start+1); start = i+1; }
    }
    return res;
}
// Time: O(n) | Space: O(1) — 26 chars
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Minimum Number of Swaps to Make String Balanced
**Difficulty:** Medium | **LC:** 1963

**Approach:** Count unmatched ']' (those with no preceding '['). Answer = ceil(unmatched/2).

```cpp
int minSwaps(string s) {
    int open = 0, mismatch = 0;
    for (char c : s) {
        if (c == '[') open++;
        else if (open > 0) open--;
        else mismatch++;
    }
    return (mismatch + 1) / 2;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Monotone Increasing Digits
**Difficulty:** Medium | **LC:** 738

**Approach:** Scan right to left. Find where `s[i] > s[i+1]`, decrement `s[i]`, set all after to '9'.

```cpp
int monotoneIncreasingDigits(int n) {
    string s = to_string(n);
    int mark = s.size(); // position from which to fill '9'
    for (int i = s.size() - 1; i > 0; i--) {
        if (s[i-1] > s[i]) { s[i-1]--; mark = i; }
    }
    for (int i = mark; i < (int)s.size(); i++) s[i] = '9';
    return stoi(s);
}
// Time: O(log n) | Space: O(log n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** "Remove K digits for smallest number" — why use a monotone INCREASING stack (pop when larger)?
<details><summary>Reveal</summary>
We want the result to be non-decreasing (smallest lexicographic). When we see a smaller digit, the previous larger digit makes the number bigger than needed. Pop it (use one removal). This greedily ensures we keep the smallest prefix possible.
</details>

**Drill 2:** Partition Labels for "ababcbacadefegdehijhklij". How is the first partition determined?
<details><summary>Reveal</summary>
Last occurrence: a=8, b=5, c=7. Scan from 0: at i=0 ('a'), end=8. At i=1 ('b'), end=max(8,5)=8. ... At i=8, i==end → partition size=9. Then continue from i=9.
</details>

**Drill 3:** Min add for valid parens: "()))((". What's the answer?
<details><summary>Reveal</summary>
Scan: ')': open=0 → add=1. ')': open=0 → add=2. ')': open=0 → add=3. ')': open=0 → add=4. '(': open=1. '(': open=2. Result: add + open = 4 + 2 = 6. Need 4 '(' at start and 2 ')' at end.
</details>

**Drill 4:** Largest Number: why compare `a+b > b+a` instead of `stoi(a) > stoi(b)`?
<details><summary>Reveal</summary>
Numeric comparison doesn't capture concatenation order. "9" vs "34": 9 > 34 is false numerically, but "9" > "34" (nine vs thirty-four), and "934" > "349" → correct. Also "30" vs "3": "303" vs "330" → "330" wins, so "3" > "30".
</details>

**Drill 5:** Monotone Increasing Digits for n=332. Trace.
<details><summary>Reveal</summary>
s="332". i=2: s[1]='3' > s[2]='2' → s[1]--='2', mark=2. i=1: s[0]='3' > s[1]='2' → s[0]--='2', mark=1. Fill '9' from mark=1: s="299". Answer: 299.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Remove K Digits | O(n) | O(n) |
| Largest Number | O(n log n × k) | O(n) |
| Min Add Parens | O(n) | O(1) |
| Partition Labels | O(n) | O(1) |
| Monotone Digits | O(log n) | O(log n) |

---

## 9. Common Follow-up Questions

**Q: Remove K digits for LARGEST number?**
A: Reverse the condition: pop when `stack.top < cur` (monotone DECREASING stack).

**Q: What if there are multiple valid smallest numbers after removing k digits?**
A: The algorithm naturally produces the unique lexicographic minimum. After removing k characters, the remaining subsequence in original order IS the unique minimum.

**Q: Partition Labels — what if a character appears in only one position?**
A: last[c] = i = current position. The `end = max(end, last[c])` just confirms the current position, no extension needed unless another char extends further.

---

## 10. Cross-Pattern Connections

- **P64 (Monotonic Stack):** Remove K Digits IS a monotonic stack problem
- **P46 (Subsets):** Partition is related — grouping elements by constraint
- **P56 (Greedy Arrays):** Similar greedy scan patterns for arrays
- **P33 (String DP):** When greedy doesn't work for string problems → DP
