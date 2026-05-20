# P51 — Expression Operators and Number Splitting

## 1. First-Timer Explanation

### What Is It?
This pattern generates all expressions by inserting operators (+, -, ×) between digits of a number string, evaluating them to find those that reach a target value. The tricky part: **multiplication has higher precedence**, so we can't just track a running sum. We track the last operand to handle `×` correctly.

### Why Is Multiplication Tricky?
```
"123", target=6

With +: 1+2+3 = 6 ✓
Running sum: easy.

But with ×:
"1*2+3" = 1*2 + 3 = 5
"1+2*3" = 1 + 2*3 = 7

When we see '*3', we must UNDO the previous addition of '2'
and instead add '2*3' = 6.

Track: current_eval + last_operand
When multiply: new_eval = current_eval - last + last * cur_num
               new_last = last * cur_num
```

### Visual Walkthrough — "123", target=6
```
dfs(idx=0, eval=0, last=0, current="")
├── take "1" → dfs(1, eval=1, last=1, "1")
│   ├── + "2" → dfs(2, eval=3, last=2, "1+2")
│   │   ├── + "3" → eval=6 == target → RECORD "1+2+3"
│   │   ├── - "3" → eval=0, skip
│   │   └── * "3" → eval = 3-2 + 2*3 = 1+6=7, skip
│   ├── - "2" → dfs(2, eval=-1, last=-2, "1-2")
│   │   └── ...
│   └── * "2" → dfs(2, eval=1-1+1*2=2, last=2, "1*2")
│       └── + "3" → eval=5, skip
│           * "3" → eval=2-2+2*3=6 → RECORD "1*2*3"
│           ...
└── take "12" → ...
    └── + "3" → eval=15, skip
```

### When to Use
- "Add operators between digits to reach target"
- "All ways to evaluate expression to value"
- "Number splitting with operators"

### Common Mistakes
1. Not handling leading zeros (e.g., "05" is not valid as a number)
2. Forgetting the multiplication precedence trick (`eval - last + last * cur`)
3. Integer overflow: use `long long`

---

## 2. Revision Card

**Recognition Signal:** "add operators between digits", "evaluate to target", "insert +, -, *"

**Core Idea:** DFS taking each prefix as a number. Track `eval` (current sum) and `last` (last operand, for undoing on multiply). For +: `eval+cur, last=cur`. For -: `eval-cur, last=-cur`. For *: `eval-last+last*cur, last=last*cur`.

**Trigger Keywords:** operators, digits, expression, target value, evaluate

**Complexity:** O(4^n × n) — 4 choices per gap (no-op/split + 3 operators), O(n) to build string

---

## 3. Interview Tell Signs

- "Insert operators into digits" → this pattern
- "Count/find expressions equaling target" → DFS with eval tracking
- "No leading zeros" → check `len > 1 && s[start] == '0'` → break

---

## 4. C++ Template

```cpp
#include <vector>
#include <string>
using namespace std;

vector<string> addOperators(string num, int target) {
    vector<string> res;
    int n = num.size();
    
    // idx: current position, eval: current value, last: last term (for * undo)
    function<void(int, long long, long long, string)> dfs =
        [&](int idx, long long eval, long long last, string expr) {
        if (idx == n) {
            if (eval == target) res.push_back(expr);
            return;
        }
        for (int len = 1; idx + len <= n; len++) {
            string part = num.substr(idx, len);
            if (len > 1 && part[0] == '0') break; // no leading zeros
            long long cur = stoll(part);
            
            if (idx == 0) {
                // first number: no operator before it
                dfs(idx + len, cur, cur, part);
            } else {
                dfs(idx + len, eval + cur,  cur,       expr + "+" + part);
                dfs(idx + len, eval - cur,  -cur,      expr + "-" + part);
                dfs(idx + len, eval - last + last * cur, last * cur, expr + "*" + part);
            }
        }
    };
    
    dfs(0, 0, 0, "");
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "The key challenge is multiplication precedence. I track two values: `eval` (total expression value) and `last` (the last operand added). When I multiply by a new number `cur`, I must undo the last addition and replace it with `last * cur`: `eval = eval - last + last * cur`. For addition: `eval + cur, last = cur`. For subtraction: `eval - cur, last = -cur`. I also guard against leading zeros and use long long to prevent overflow."

**Checklist:**
- [ ] Explain `last` trick for multiplication precedence
- [ ] Handle first number specially (no operator before it)
- [ ] Break on leading zeros
- [ ] Use `long long` for intermediate values
- [ ] Time: O(4^n × n)

---

## 6. Problems

### Problem 1: Expression Add Operators
**Difficulty:** Hard | **LC:** 282

```cpp
vector<string> addOperators(string num, int target) {
    vector<string> res;
    int n = num.size();
    function<void(int, long long, long long, string)> dfs =
        [&](int idx, long long eval, long long last, string expr) {
        if (idx == n) { if (eval == target) res.push_back(expr); return; }
        for (int len = 1; idx + len <= n; len++) {
            string part = num.substr(idx, len);
            if (len > 1 && part[0] == '0') break;
            long long cur = stoll(part);
            if (idx == 0) { dfs(idx+len, cur, cur, part); }
            else {
                dfs(idx+len, eval+cur, cur, expr+"+"+part);
                dfs(idx+len, eval-cur, -cur, expr+"-"+part);
                dfs(idx+len, eval-last+last*cur, last*cur, expr+"*"+part);
            }
        }
    };
    dfs(0, 0, 0, "");
    return res;
}
// Time: O(4^n * n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Different Ways to Add Parentheses
**Difficulty:** Medium | **LC:** 241

**Approach:** For each operator in the string, split left and right, recurse, combine all left-right result pairs.

```cpp
vector<int> diffWaysToCompute(string expr) {
    vector<int> res;
    for (int i = 0; i < (int)expr.size(); i++) {
        char op = expr[i];
        if (op == '+' || op == '-' || op == '*') {
            auto left = diffWaysToCompute(expr.substr(0, i));
            auto right = diffWaysToCompute(expr.substr(i+1));
            for (int l : left)
                for (int r : right) {
                    if (op == '+') res.push_back(l + r);
                    else if (op == '-') res.push_back(l - r);
                    else res.push_back(l * r);
                }
        }
    }
    if (res.empty()) res.push_back(stoi(expr)); // base: single number
    return res;
}
// Time: O(C_n * n) Catalan | Space: O(C_n)
// Memoize with unordered_map<string, vector<int>> if needed
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Evaluate Division
**Difficulty:** Medium | **LC:** 399

**Approach:** Graph + DFS/Floyd-Warshall. Each `a/b = k` adds edges a→b (k) and b→a (1/k). Query = product of edge weights along path.

```cpp
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                             vector<vector<string>>& queries) {
    unordered_map<string, unordered_map<string, double>> graph;
    for (int i = 0; i < (int)equations.size(); i++) {
        auto& [a, b] = equations[i];
        graph[a][b] = values[i];
        graph[b][a] = 1.0 / values[i];
        graph[a][a] = 1.0;
        graph[b][b] = 1.0;
    }
    
    function<double(string, string, unordered_set<string>&)> dfs =
        [&](string src, string dst, unordered_set<string>& visited) -> double {
        if (!graph.count(src)) return -1.0;
        if (graph[src].count(dst)) return graph[src][dst];
        visited.insert(src);
        for (auto& [next, w] : graph[src]) {
            if (visited.count(next)) continue;
            double res = dfs(next, dst, visited);
            if (res != -1.0) return w * res;
        }
        return -1.0;
    };
    
    vector<double> ans;
    for (auto& [a, b] : queries) {
        unordered_set<string> visited;
        ans.push_back(dfs(a, b, visited));
    }
    return ans;
}
// Time: O((E + Q) * V) | Space: O(V + E)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** "123", target=6. Without the `last` trick, how would "1*2+3" be evaluated incorrectly?
<details><summary>Reveal</summary>
Without `last`: after "1*2" we'd have eval=2. Then "+3": eval=5. Correct answer is 2+3=5 ✓ here. But for "1+2*3": without `last`, we'd compute eval=3 then *3=9. Correct is 1+(2*3)=7. The issue is '*' must undo the '2' that was added before multiplying.
</details>

**Drill 2:** For multiplication, the formula is `eval - last + last * cur`. Explain each term.
<details><summary>Reveal</summary>
`eval - last`: undo the last operand that was added. `last * cur`: replace it with last×cur (multiplication of those two terms). The net effect: the previous operator between `last` and the operand before `last` is still correct; we just replaced `last` with `last*cur`.
</details>

**Drill 3:** "05" — why break instead of continue?
<details><summary>Reveal</summary>
Numbers with leading zeros like "05" are invalid. But longer numbers like "056" are also invalid (still has leading zero). Since all longer substrings starting at the same position will also have a leading zero, we `break` (stop trying longer lengths) not `continue`.
</details>

**Drill 4:** Different Ways to Add Parentheses for "2-1-1". What are all results?
<details><summary>Reveal</summary>
Split at first '-': (2) and (1-1) → 2 - 0 = 2. Split at second '-': (2-1) and (1) → 1 - 1 = 0. Results: [2, 0].
</details>

**Drill 5:** Why use long long in expression operators?
<details><summary>Reveal</summary>
The number string can have up to 10 digits. 10^10 overflows int (max ~2×10^9). Also, `last * cur` compounds the multiplication. Using long long (max ~9×10^18) prevents overflow for reasonable inputs.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Add Operators | O(4^n × n) | O(n) |
| Different Ways | O(C_n × n) Catalan | O(C_n) |
| Evaluate Division | O((E+Q) × V) | O(V+E) |

---

## 9. Common Follow-up Questions

**Q: What if division operator is also allowed?**
A: Add division case, but guard against division by zero.

**Q: Count expressions (not enumerate)?**
A: DP on digit positions tracking the "remainder" modulo target — harder but feasible for some cases.

**Q: Different Ways — can you memoize?**
A: Yes, map from substring to results vector. But since substrings are unique by position, you can also memoize by (l, r) indices.

---

## 10. Cross-Pattern Connections

- **P46 (Subsets):** Enumerating cuts is like choosing subset of positions for operators
- **P35 (Interval DP):** Different Ways uses interval DP on the expression
- **P40 (Floyd-Warshall):** Evaluate Division can be solved with multiplicative Floyd-Warshall
- **P23 (Dijkstra/Graph):** Evaluate Division uses graph path product
