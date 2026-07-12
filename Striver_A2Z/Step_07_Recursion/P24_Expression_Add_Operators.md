# Expression Add Operators

> **LeetCode #282** · **Difficulty:** Hard · **Step 7 — Recursion · P24**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a string of digits and a target, insert operators `+`, `-`, `*` between digits to produce expressions that evaluate to the target. Return all such expressions.

**Input:** `num="123", target=6` → `["1+2+3","1*2*3"]`
**Input:** `num="232", target=8` → `["2+3*2","2*3+2"]`

**Key Observations:**
- At each position, try all possible number substrings from the current start.
- For each number (not the first), try inserting `+`, `-`, or `*` before it.
- Multiplication is tricky: `a + b * c` cannot be naïvely computed as `(a+b) * c`. Must undo the last operand.
- Skip leading zeros: `"05"` is not a valid number.

---

## 🥇 DFS with Last-Operand Tracking

### The Multiplication Trick

> 💡 The hard part: when we see `*`, we need operator precedence. Track `last_operand` to undo its contribution and re-apply with multiplication.

```
State: current_value=7, last_operand=2, expression="1+2+4"

Now want to insert *3:
  expression becomes "1+2+4*3"
  value should be 1+2+(4*3) = 1+2+12 = 15

  But current_value=7 includes last_operand=4 already added.
  new_value = current_value - last_operand + last_operand * current_num_val
            = 7            - 4            + 4 * 3
            = 15 ✓

  new last_operand = last_operand * current_num_val = 4*3 = 12
  (needed for potential chained multiply like "1+2+4*3*5")
```

For `-`: `last_operand` becomes `-current_num_val` (tracks sign for potential following `*`).
```
After "1+2-3": current_value=0, last_operand=-3
Insert *4: new_value = 0 - (-3) + (-3)*4 = 0 + 3 - 12 = -9 = 1+2-3*4 ✓
```

### Algorithm
1. `dfs(start, current_value, last_operand, expression)`:
   - **Base:** `start == num.size()` → if `current_value == target`, push `expression`.
   - Loop `i = start` to `num.size()-1`:
     - **Leading zero guard:** `if(i > start && num[start] == '0') return` (the whole number starting at `start` has leading zero if `num[start]='0'` and we haven't stopped at `start` alone).
     - Extract `current_num = num.substr(start, i-start+1)`.
     - If `start == 0`: recurse with just the number (no operator).
     - Else: branch into `+`, `-`, `*`.

### C++ Code

```cpp
class Solution {
public:
    void dfs(string& num,int target,int start,long long current_value,long long last_operand,
             string expression,vector<string>& result){
        if(start==(int)num.size()){
            if(current_value==target) result.push_back(expression);
            return;
        }
        for(int i=start;i<(int)num.size();i++){
            if(i>start && num[start]=='0') return;
            string current_num=num.substr(start,i-start+1);
            long long current_num_val=stoll(current_num);
            if(start==0){
                dfs(num,target,i+1,current_num_val,current_num_val,current_num,result);
            }else{
                dfs(num,target,i+1,current_value+current_num_val,current_num_val,
                    expression+"+"+current_num,result);
                dfs(num,target,i+1,current_value-current_num_val,-current_num_val,
                    expression+"-"+current_num,result);
                dfs(num,target,i+1,current_value-last_operand+last_operand*current_num_val,
                    last_operand*current_num_val,expression+"*"+current_num,result);
            }
        }
    }

    vector<string> addOperators(string num,int target){
        vector<string> result;
        dfs(num,target,0,0,0,"",result);
        return result;
    }
};
```

**Time:** O(N × 4^N) — N choices for number split, 3 operators + initial number
**Space:** O(N) — recursion depth + expression string

### Dry Run — `num="123", target=6`

```
dfs(start=0): i=0 → num="1", dfs(start=1, val=1, last=1, expr="1")
  i=0 → num="2", try:
    +: dfs(2, val=3, last=2, "1+2")
      i=0 → num="3": +: val=6==target ✓ push "1+2+3"
                       -: val=0≠6
                       *: val=3-2+2*3=7≠6
    -: dfs(2, val=-1, last=-2, "1-2")
      +: val=2, -: val=-4, *: val=-1-(-2)+(-2)*3=-5 → none=6
    *: dfs(2, val=1, last=2, "1*2") [current_value=1-1+1*2=2? wait]
      wait: last_operand=1 (from "1"), current_num_val=2
      new_value = 1 - 1 + 1*2 = 2, new_last = 1*2 = 2
      *: "1*2", val=2, last=2
        +: "1*2+3"=5≠6, -: "1*2-3"=-1≠6
        *: val=2-2+2*3=6==target ✓ push "1*2*3"
```

**Output:** `["1+2+3","1*2*3"]` ✓

---

## ⚠️ Leading Zero Guard — Detail

```cpp
if(i > start && num[start] == '0') return;
```

- `num[start] == '0'`: the number starting at `start` begins with zero.
- `i > start`: we've gone past the single digit (so we'd form a multi-digit number like "05").
- `return` (not `continue`) — if the current substring has leading zero, ALL longer substrings from this `start` also have it → entire branch is invalid.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Loop all number splits from `start`. First number: no operator. Else: try +/-/*. Multiply trick: `val - last + last*cur`. Leading zero guard: `i>start && num[start]=='0' → return`. Track `last_operand` for mul chain."

---

## 📝 Short Revision Notes

- `last_operand` for `+c` = `+c`, for `-c` = `-c`, for `*c` = `last * c` (chain).
- Use `long long` throughout — intermediate products can overflow `int`.
- `stoll` instead of `stoi` — handles large multi-digit numbers safely.
- `start==0` branch avoids inserting an operator before the first number.

---

## ⚠️ Common Mistakes

❌ Ignoring operator precedence for `*` — computing `(a op b) * c` instead of `a op (b*c)`.
❌ Using `int` instead of `long long` — overflow for large digit strings.
❌ `continue` instead of `return` for leading zero — still tries longer numbers with leading zeros.
❌ Not tracking `last_operand` sign for `-` — breaks chained `- *` case.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "insert operators between digits to reach target" → **DFS with current_value + last_operand (for mul undo). Leading zero guard. 3 operator branches.**

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Expression Evaluation` · `Math`

---

## ⏱️ 30-Second Last-Minute Revision

> Loop splits from `start`. First → no op. Else: `+`(last=cur), `-`(last=-cur), `*`(val=val-last+last*cur, last=last*cur). Base: start==len && val==target. Leading zero: `i>start && num[start]=='0' → return`. **Time:** O(N×4^N).
