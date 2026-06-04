# 🔥 Check if a String is Palindrome

> **LeetCode #125** (variant) · **Difficulty:** Easy · **Step 1 — Basic Recursion · P27**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given a string, check if it reads the same forwards and backwards.

**Input:** String s (1 ≤ s.length ≤ 10⁵)  
**Output:** `true` if palindrome, `false` otherwise

**Key Observations:**
- Case sensitivity: "Racecar" vs "racecar" — clarify with interviewer
- Striver version: pure string, case sensitive
- LeetCode 125: ignore non-alphanumeric, case-insensitive

**Simple Example:**
```
"madam"   → palindrome ✅
"racecar" → palindrome ✅
"hello"   → not palindrome ❌
"a"       → palindrome ✅ (single char)
""        → palindrome ✅ (empty string)
```

---

## 🥉 Brute Force

### Idea
Reverse the string, compare with original.

```cpp
bool isPalindrome(string s) {
    string rev = s;
    reverse(rev.begin(), rev.end());   // O(N) space for reversed copy
    return s == rev;
}
// Time O(N), Space O(N)
```

---

## 🥈 Better — Two Pointers (Iterative)

### Key Observation

> 💡 Compare characters from both ends inward. If any mismatch → not palindrome.

### Dry Run

**Input:** `s = "racecar"`

| l | r | s[l] | s[r] | Match? |
|---|---|------|------|--------|
| 0 | 6 | 'r' | 'r' | ✅ |
| 1 | 5 | 'a' | 'a' | ✅ |
| 2 | 4 | 'c' | 'c' | ✅ |
| 3 | 3 | l >= r → stop | | |

**Output:** `true` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

```cpp
bool isPalindrome(string s) {
    int l = 0, r = s.length() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}
```

---

## 🥇 Optimal — Recursive (for this problem context)

### Key Observation

> 💡 isPalindrome(s, l, r) = (s[l]==s[r]) AND isPalindrome(s, l+1, r-1)

### Algorithm
1. Base case: if `l >= r`, return true (empty or single char)
2. If `s[l] != s[r]`, return false
3. Recurse on `(l+1, r-1)`

### Dry Run

**Input:** `s = "abcba"`, `l=0, r=4`

```
f(0,4): s[0]='a' == s[4]='a' ✅, recurse f(1,3)
  f(1,3): s[1]='b' == s[3]='b' ✅, recurse f(2,2)
    f(2,2): l >= r → return true
  f(1,3) → true
f(0,4) → true
```

### Complexity
- **Time:** O(N) · **Space:** O(N/2) = O(N) call stack

### C++ Code

```cpp
/*
 * PROBLEM: Check if string is palindrome
 *
 * BRUTE:   Reverse and compare — O(N) space
 * BETTER:  Two pointers — O(1) space
 * OPTIMAL: Recursive two pointers — O(N) stack
 *          (Iterative is actually better; recursive shown for pattern learning)
 *
 * COMPLEXITY: Time O(N) | Space O(1) iterative / O(N) recursive
 */

class Solution {
public:
    // Iterative two pointers — use this in interviews
    bool isPalindromeIterative(string s) {
        int l = 0, r = s.length() - 1;
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++; r--;
        }
        return true;
    }

    // Recursive — for pattern learning
    bool isPalindromeRecursive(string& s, int l, int r) {
        if (l >= r) return true;               // base case
        if (s[l] != s[r]) return false;        // mismatch
        return isPalindromeRecursive(s, l + 1, r - 1);
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Two pointers from ends. If any `s[l] != s[r]` → false. Stop when `l >= r`."

---

## 📝 Short Revision Notes

- Two pointers is O(N) time, O(1) space — best for interviews
- Recursive: good for demonstrating recursion; uses O(N) stack
- LeetCode 125 variant: filter non-alphanumeric, lowercase before checking
- Edge cases: empty string → true; single char → true
- Basis for palindrome DP problems (longest palindromic substring)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "palindrome check" on string
- "symmetric structure"
- "compare from both ends"

**I should think of:** Two pointers from both ends

---

## ⚠️ Common Mistakes

❌ Creating reversed copy when O(1) space required  
❌ `while (l <= r)` with char comparison — works but checks middle against itself (harmless)  
❌ Not handling case sensitivity when problem requires it  
❌ Not handling non-alphanumeric for LeetCode 125 variant  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Two pointers + string traversal
- **Reasoning:** Space optimization
- **Follow-up readiness:** Can extend to "valid palindrome" ignoring special chars

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Two pointers iterative | O(N) | O(1) | Best |
| Recursive | O(N) | O(N) | Good for recursion practice |
| Reverse and compare | O(N) | O(N) | Simple but extra space |

---

## 📚 Related Problems

- [ ] LeetCode #125 — Valid Palindrome (filter non-alphanumeric)
- [ ] LeetCode #680 — Valid Palindrome II (allow one deletion)
- [ ] LeetCode #5 — Longest Palindromic Substring
- [ ] LeetCode #516 — Longest Palindromic Subsequence (DP)
- [ ] Striver Step 1 P15 — Palindrome Number (same concept, numbers)

---

## 🏆 Pattern Category

`Strings` · `Two Pointers` · `Recursion`

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Is string s a palindrome?  
> **Approach:** Two pointers `l=0, r=n-1`. While `l < r`: if `s[l] != s[r]` → false; else `l++, r--`. Return true.  
> **Key trick:** Works identically for odd and even length strings  
> **Time:** O(N) | **Space:** O(1)  
> **Watch out for:** LeetCode 125 needs alphanumeric filter + lowercase normalization
