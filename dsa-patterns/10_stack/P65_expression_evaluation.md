# P65 — Expression Evaluation and Valid Parentheses

## 1. First-Timer Explanation

### What Is It?
**Expression evaluation** uses a stack to handle operator precedence and parentheses. When parsing arithmetic expressions, the stack temporarily holds operators or partial results, deferring computation until the right time (when a lower-priority operator or closing parenthesis is seen).

**Valid parentheses** is simpler: use a stack to match opening with closing brackets.

### Analogy — Expression Evaluation
Imagine reading a math problem out loud. When you see `3 + 4 × 5`, you can't compute `3+4` immediately — you must defer it until you know what comes next (multiplication binds tighter). A stack "remembers" what to come back to: push the partial sum `3` and the `+`, then compute `4×5=20`, then apply the deferred `+3`.

### Algorithm for Basic Calculator
1. Push current result to stack when `(` is seen (save context)
2. Pop and merge when `)` is seen (restore context)
3. Maintain running sum, last sign (+1 or -1)

### Visual Walkthrough — "3 + (2 - 1)"
```
stack=[], result=0, sign=+1, num=0

'3': num=3
' ': result += sign * num = 3, num=0
'+': sign=+1
'(': push result=3, push sign=+1, reset result=0, sign=+1
'2': num=2
' ': result += 1*2 = 2, num=0
'-': sign=-1
'1': num=1
')': result += -1*1 = 1, sign=stack.pop()=1, result = 1 + sign*result = 3 + 1*1 = 4
→ Final = 4 ✓
```

### When to Use
- "Valid parentheses" → simple stack push/pop
- "Basic calculator with +/-" → stack for nested contexts
- "Calculator with +/-/*///" → two stacks (operators + operands) or postfix
- "Evaluate reverse Polish notation" → operand stack

---

## 2. Revision Card

**Recognition Signal:** "evaluate expression", "valid brackets", "calculate with parentheses"

**Core Idea (Parens):** Push opening brackets. On closing: check top matches. Return empty at end.

**Core Idea (Calculator):** Maintain `result` and `sign`. On `(`: save current state on stack. On `)`: restore from stack. On digit: accumulate `num`. On operator: apply pending operation.

**Trigger Keywords:** expression, calculator, parentheses, brackets, evaluate, valid

**Complexity:** O(n) time, O(n) space (stack)

---

## 3. Interview Tell Signs

- "Valid parentheses/brackets" → simple stack match
- "Minimum add to make valid" → count mismatch (P55)
- "Evaluate arithmetic expression" → stack-based evaluation
- "Reverse Polish notation" → simple operand stack
- "Decode string" → recursion or stack

---

## 4. C++ Template

```cpp
#include <stack>
#include <string>
using namespace std;

// ── Valid Parentheses ─────────────────────────────────────────────────────────
bool isValid(string s) {
    stack<char> stk;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') stk.push(c);
        else {
            if (stk.empty()) return false;
            char top = stk.top(); stk.pop();
            if ((c == ')' && top != '(') || (c == ']' && top != '[') ||
                (c == '}' && top != '{')) return false;
        }
    }
    return stk.empty();
}

// ── Basic Calculator (+/- and parens) ────────────────────────────────────────
int calculate(string s) {
    stack<int> stk;
    int result = 0, sign = 1, num = 0;
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == '+' || c == '-') {
            result += sign * num; num = 0;
            sign = (c == '+') ? 1 : -1;
        } else if (c == '(') {
            stk.push(result); stk.push(sign); // save context
            result = 0; sign = 1;
        } else if (c == ')') {
            result += sign * num; num = 0;
            result *= stk.top(); stk.pop(); // multiply by sign before paren
            result += stk.top(); stk.pop(); // add result before paren
        }
    }
    return result + sign * num; // don't forget last number
}
```

---

## 5. How to Present in Interview

**Verbal Script (Valid Parens):**
> "I use a stack. For each opening bracket, push it. For each closing bracket, check if the stack top is the matching opening. If not (or stack empty), return false. At the end, the stack must be empty."

**Verbal Script (Basic Calculator):**
> "I maintain running result and current sign. When I hit a digit, accumulate the number. When I hit an operator, apply the pending number with the pending sign to result. For `(`, push current result and sign to stack and reset. For `)`, apply the last number, then restore by multiplying by the sign saved before the paren and adding the result saved before the paren."

---

## 6. Problems

### Problem 1: Valid Parentheses
**Difficulty:** Easy | **LC:** 20

```cpp
bool isValid(string s) {
    stack<char> stk;
    for (char c : s) {
        if (c=='('||c=='['||c=='{') stk.push(c);
        else {
            if (stk.empty()) return false;
            char t = stk.top(); stk.pop();
            if (c==')' && t!='(') return false;
            if (c==']' && t!='[') return false;
            if (c=='}' && t!='{') return false;
        }
    }
    return stk.empty();
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Basic Calculator (+/- with parentheses)
**Difficulty:** Hard | **LC:** 224

```cpp
int calculate(string s) {
    stack<int> stk;
    int result = 0, sign = 1, num = 0;
    for (char c : s) {
        if (isdigit(c)) { num = num*10 + (c-'0'); }
        else if (c=='+') { result += sign*num; num=0; sign=1; }
        else if (c=='-') { result += sign*num; num=0; sign=-1; }
        else if (c=='(') { stk.push(result); stk.push(sign); result=0; sign=1; }
        else if (c==')') { result += sign*num; num=0; result *= stk.top(); stk.pop(); result += stk.top(); stk.pop(); }
    }
    return result + sign*num;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Basic Calculator II (+/-/*// no parens)
**Difficulty:** Medium | **LC:** 227

**Approach:** Apply * and / immediately (higher precedence). Push + and - as sign * num on stack; sum at end.

```cpp
int calculate(string s) {
    stack<int> stk;
    int num = 0;
    char op = '+';
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (isdigit(c)) num = num*10 + (c-'0');
        if ((!isdigit(c) && c!=' ') || i==s.size()-1) {
            if (op=='+') stk.push(num);
            else if (op=='-') stk.push(-num);
            else if (op=='*') { int top=stk.top(); stk.pop(); stk.push(top*num); }
            else if (op=='/') { int top=stk.top(); stk.pop(); stk.push(top/num); }
            op = c; num = 0;
        }
    }
    int res = 0;
    while (!stk.empty()) { res += stk.top(); stk.pop(); }
    return res;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Evaluate Reverse Polish Notation
**Difficulty:** Medium | **LC:** 150

```cpp
int evalRPN(vector<string>& tokens) {
    stack<int> stk;
    for (auto& t : tokens) {
        if (t=="+"||t=="-"||t=="*"||t=="/") {
            int b = stk.top(); stk.pop();
            int a = stk.top(); stk.pop();
            if (t=="+") stk.push(a+b);
            else if (t=="-") stk.push(a-b);
            else if (t=="*") stk.push(a*b);
            else stk.push(a/b);
        } else stk.push(stoi(t));
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

### Problem 5: Decode String
**Difficulty:** Medium | **LC:** 394

**Approach:** Stack stores (current_string, repeat_count) when `[` is seen. On `]`: pop, repeat, append.

```cpp
string decodeString(string s) {
    stack<pair<string,int>> stk;
    string cur;
    int k = 0;
    for (char c : s) {
        if (isdigit(c)) { k = k*10 + (c-'0'); }
        else if (c == '[') { stk.push({cur, k}); cur = ""; k = 0; }
        else if (c == ']') {
            auto [prev, times] = stk.top(); stk.pop();
            string repeated;
            for (int i = 0; i < times; i++) repeated += cur;
            cur = prev + repeated;
        } else { cur += c; }
    }
    return cur;
}
// Time: O(output_length) | Space: O(output_length)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Remove K Digits (Monotonic Stack, Repeated Here)
**Difficulty:** Medium | **LC:** 402

```cpp
string removeKdigits(string num, int k) {
    string res;
    for (char c : num) {
        while (k && !res.empty() && res.back() > c) { res.pop_back(); k--; }
        res += c;
    }
    while (k--) res.pop_back();
    int s = res.find_first_not_of('0');
    return s == string::npos ? "0" : res.substr(s);
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Valid parentheses for "([)]" — is it valid?
<details><summary>Reveal</summary>
Stack trace: push '(', push '['. See ')': top is '[' ≠ '(' → INVALID. Return false. ✓ (interleaved brackets are invalid).
</details>

**Drill 2:** Basic Calculator "+": why push both `result` and `sign` when seeing `(`?
<details><summary>Reveal</summary>
When we see `)`, we need to (1) multiply the inner result by the sign before the parenthesis (was it `+(...)` or `-(...)`) and (2) add the result before the parenthesis. Both pieces of information must be saved on the stack. Saving only result or only sign would lose half the context.
</details>

**Drill 3:** Calculator II: "3+2*2". Trace the stack.
<details><summary>Reveal</summary>
op='+', num=0. '3': num=3. '+': push 3 (op was '+'), op='+', num=0. '2': num=2. '*': push 2 (op was '+'), op='*', num=0. '2': num=2. End (i==size-1): op='*', top=stk.top()=2, stk.pop(), push 2*2=4. Stack: [3,4]. Sum=7 ✓.
</details>

**Drill 4:** Decode "3[a2[c]]". Trace.
<details><summary>Reveal</summary>
k=3. '[': push ("",3), cur="", k=0. 'a': cur="a". k=2. '[': push ("a",2), cur="", k=0. 'c': cur="c". ']': pop ("a",2), cur = "a" + "cc" = "acc". ']': pop ("",3), cur = "" + "accaccacc" = "accaccacc". Result: "accaccacc" ✓.
</details>

**Drill 5:** Evaluate RPN "4 13 5 / +". What's the result?
<details><summary>Reveal</summary>
Push 4. Push 13. Push 5. '/': pop 5,13 → 13/5=2, push 2. '+': pop 2,4 → 4+2=6, push 6. Result: 6 ✓. (Infix: 4 + 13/5 = 4 + 2 = 6)
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Valid Parentheses | O(n) | O(n) |
| Basic Calculator I | O(n) | O(n) |
| Basic Calculator II | O(n) | O(n) |
| Evaluate RPN | O(n) | O(n) |
| Decode String | O(output) | O(output) |

---

## 9. Common Follow-up Questions

**Q: Handle expressions with unary minus (e.g., "-3 + 4")?**
A: Treat the start and after `(` as having implicit sign. Initialize sign = +1. When you see `-` at position 0 or after `(`, it's unary minus.

**Q: Shunting-yard algorithm?**
A: Dijkstra's algorithm to convert infix to postfix (RPN). Uses two stacks: output and operator. Handles full operator precedence and associativity. Then evaluate RPN with simple stack.

**Q: Can you evaluate expressions without stacks?**
A: Yes — recursive descent parsing. Implement `parseExpr()`, `parseTerm()`, `parseFactor()` following grammar. Clean for interviews but more code.

---

## 10. Cross-Pattern Connections

- **P64 (Monotonic Stack):** Different stack usage — monotonic for boundaries, this for context
- **P55 (Greedy Strings):** Min add to make valid parens — greedy O(1) space
- **P50 (Palindrome Partition):** Both use strings + backtracking/stack
- **P33 (String DP):** Decode ways uses DP on strings; this uses stack
