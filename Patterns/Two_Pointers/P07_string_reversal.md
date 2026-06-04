# Pattern 07: String Reversal

## Category
Two Pointers

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 151. Reverse Words in a String | Medium | https://leetcode.com/problems/reverse-words-in-a-string/ |
| 2 | 344. Reverse String | Easy | https://leetcode.com/problems/reverse-string/ |
| 3 | 345. Reverse Vowels of a String | Easy | https://leetcode.com/problems/reverse-vowels-of-a-string/ |
| 4 | 541. Reverse String II | Easy | https://leetcode.com/problems/reverse-string-ii/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Reversing a string (or sections of it) in-place is done with two pointers: one at the start, one at the end, swapping and moving inward. Key variations:
- **Full reverse**: swap from both ends toward center
- **Selective reverse**: skip non-qualifying characters (e.g., only swap vowels)
- **Segment reverse**: reverse every k characters
- **Reverse words**: split into words, reverse order — achieved by reverse-all then reverse-each-word

### Real-World Analogy
A line of people facing a mirror. To flip the line's order, have the leftmost and rightmost people swap positions, then move inward. To reverse only the people wearing red shirts, the left pointer jumps to the next red-shirt wearer, and so does the right pointer, before each swap.

### Visual Walkthrough
```
Reverse "hello":
  lo=0('h')  hi=4('o')  → swap → "oellh"
  lo=1('e')  hi=3('l')  → swap → "olleh"
  lo=2 == hi=2  → STOP

Reverse Vowels of "hello":
  Vowels: e, o
  lo=0('h') not vowel → lo++
  lo=1('e') vowel → pause
  hi=4('o') vowel → pause
  swap e ↔ o → "holle"
  lo=2('l') not vowel → lo++
  lo=3('l') not vowel → lo++
  lo=4 > hi=3 → STOP (hi had moved to 3 after swap)
  Result: "holle"
```

### When TO use this pattern
- Reverse entire string or array in-place
- Reverse specific characters (vowels, digits)
- Reverse every k-character block
- Reverse word order in a sentence

### When NOT to use this pattern
- Need a new string (not in-place)
- Complex transformations that can't be done by swapping

### Common Beginner Mistakes
- **Reverse words**: trim spaces first, then reverse all, then reverse each word
- **Selective reverse**: advance pointer to qualifying position before swapping
- **Reverse String II**: reverse every FIRST k chars of each 2k block, not the whole thing
- **Extra spaces**: "Reverse Words in a String" requires collapsing multiple spaces

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "reverse in-place", "reverse words", "reverse every k chars" |
| Core Idea | lo/hi pointers swap and move inward; skip non-qualifying chars for selective |
| Trigger Keywords | "reverse", "in-place", "vowels", "words", "every k characters" |
| Avoid When | New string is acceptable (just use reverse() or split()) |
| Time Complexity | O(n) |
| Space Complexity | O(1) for in-place (O(n) if output is new string) |

**Gotchas:**
- Reverse Words: multiple spaces must be collapsed. Use: reverse all → reverse each word → handle trailing/leading spaces
- Reverse Vowels: advance both pointers to vowel positions before swapping
- k-reversal: for each block of 2k, only reverse the first k characters

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"reverse string in-place"` → classic lo/hi swap
- `"reverse vowels only"` → selective pointer advance
- `"reverse every k characters"` → block reversal loop
- `"reverse word order"` → reverse-all + reverse-each-word trick

---

## 4. C++ Template

```cpp
/*
 * Pattern: String Reversal
 * Use when: reverse string or sections in-place
 * Time: O(n) | Space: O(1)
 */

// Full reverse
void reverseString(vector<char>& s) {
    int lo = 0, hi = s.size() - 1;
    while (lo < hi) swap(s[lo++], s[hi--]);
}

// Selective: reverse only vowels
void reverseVowels(string& s) {
    auto isVowel = [](char c) {
        c = tolower(c);
        return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
    };
    int lo = 0, hi = s.size() - 1;
    while (lo < hi) {
        while (lo < hi && !isVowel(s[lo])) lo++;
        while (lo < hi && !isVowel(s[hi])) hi--;
        if (lo < hi) swap(s[lo++], s[hi--]);
    }
}

// Reverse words in a string
string reverseWords(string s) {
    // reverse entire string
    reverse(s.begin(), s.end());
    int n = s.size(), start = 0;
    string result;

    for (int i = 0; i <= n; i++) {
        if (i == n || s[i] == ' ') {
            if (i > start) {
                if (!result.empty()) result += ' ';
                result += s.substr(start, i - start);
            }
            start = i + 1;
        }
    }
    // reverse each word in result
    // (simpler: split, reverse array, join)
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For reversing in-place, I use two pointers at both ends and swap toward the middle — O(n) time, O(1) space.
For reversing word order: reverse the entire string, then reverse each individual word. This puts words in the right order without extra space."

### Interview Flow Checklist
- [ ] Confirm in-place requirement
- [ ] State the 'reverse-all then reverse-words' trick for word reversal
- [ ] Handle edge cases: multiple spaces, leading/trailing spaces
- [ ] Code and dry run

---

## 6. Problems

---

### Problem 1: 344. Reverse String
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/reverse-string/
**Optimal C++ Solution:**
```cpp
void reverseString(vector<char>& s) {
    int lo = 0, hi = s.size() - 1;
    while (lo < hi) swap(s[lo++], s[hi--]);
}
```
**Edge Cases:** [ ] Empty array, [ ] Single element

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 345. Reverse Vowels of a String
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/reverse-vowels-of-a-string/
**Optimal C++ Solution:**
```cpp
string reverseVowels(string s) {
    auto isVowel = [](char c) -> bool {
        c = tolower(c);
        return string("aeiou").find(c) != string::npos;
    };
    int lo = 0, hi = s.size() - 1;
    while (lo < hi) {
        while (lo < hi && !isVowel(s[lo])) lo++;
        while (lo < hi && !isVowel(s[hi])) hi--;
        if (lo < hi) swap(s[lo++], s[hi--]);
    }
    return s;
}
```
**Edge Cases:** [ ] No vowels, [ ] All vowels, [ ] Uppercase vowels

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 151. Reverse Words in a String
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/reverse-words-in-a-string/
**Optimal C++ Solution:**
```cpp
string reverseWords(string s) {
    istringstream iss(s);
    vector<string> words;
    string word;
    while (iss >> word) words.push_back(word);  // splits on whitespace, skips extra spaces
    reverse(words.begin(), words.end());
    string result;
    for (int i = 0; i < (int)words.size(); i++) {
        if (i > 0) result += ' ';
        result += words[i];
    }
    return result;
}
```
**Edge Cases:** [ ] Multiple spaces between words, [ ] Leading/trailing spaces, [ ] Single word

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 541. Reverse String II
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/reverse-string-ii/
**Problem Summary:** Reverse the first k characters for every 2k chunk.
**Optimal C++ Solution:**
```cpp
string reverseStr(string s, int k) {
    for (int i = 0; i < (int)s.size(); i += 2 * k) {
        // reverse s[i .. min(i+k-1, n-1)]
        int lo = i, hi = min(i + k - 1, (int)s.size() - 1);
        while (lo < hi) swap(s[lo++], s[hi--]);
    }
    return s;
}
```
**Edge Cases:** [ ] k larger than string length (reverse entire string)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Reverse only the digits in a string "a1b2c3" → "a3b2c1".

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Selective Two-Pointer Reversal
**Reason:** Same as reverse vowels but condition is isDigit(). Two pointers advance to next digit before swapping.
</details>

---

**Drill 2:**
> Given an integer array, rotate it right by k positions in-place.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** String Reversal (3-step reverse)
**Reason:** LC 189. Reverse all → reverse first k → reverse rest k..n-1. This rotates right by k with O(1) space.
</details>

---

**Drill 3:**
> Given a sentence with some words in ALL_CAPS and others not, reverse only the ALL_CAPS words among themselves.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Selective Reversal + Word Parsing
**Reason:** Extract indices of ALL_CAPS words, then use two-pointer on that index list to swap word positions. Two layers of the pattern.
</details>

---

**Drill 4:**
> Given a string, reverse it but keep the positions of spaces intact. "a b c" → "c b a".

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Selective Reversal
**Reason:** Collect positions of non-space characters, then reverse their values (not positions). Use two pointers on the list of non-space indices, swap characters at those positions.
</details>

---

**Drill 5:**
> Reverse a number without converting to string. Handle negative numbers.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Math (digit extraction), not string reversal
**Reason:** Pop last digit with n%10, push to result with result*10. Handle sign separately. Check overflow before multiplying.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Full string reverse | O(n) | O(1) | Single pass swap |
| Reverse vowels | O(n) | O(1) | Skip non-vowels, single pass |
| Reverse words | O(n) | O(n) for output | Split or multi-reverse |
| Reverse every k | O(n) | O(1) | Loop with block reversal |

---

## 9. Common Follow-up Questions

1. How to reverse words in-place without extra space? (3-step: reverse all, then reverse each word by finding spaces)
2. How to reverse only alternating words? (Track word index parity, reverse odd-indexed words among themselves)
3. What if the language doesn't allow string modification? (Build a new string; O(n) space is unavoidable)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| In-place Rotation (Matrix) | Transpose + reverse rows/columns | 48. Rotate Image |
| Array Rotation | Reverse-all + reverse-halves trick | 189. Rotate Array |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
