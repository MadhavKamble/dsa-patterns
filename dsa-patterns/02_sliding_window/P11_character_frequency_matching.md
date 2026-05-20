# Pattern 11: Character Frequency Matching

## Category
Sliding Window

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 1. Two Sum | Easy | https://leetcode.com/problems/two-sum/ |
| 2 | 438. Find All Anagrams in a String | Medium | https://leetcode.com/problems/find-all-anagrams-in-a-string/ |
| 3 | 567. Permutation in String | Medium | https://leetcode.com/problems/permutation-in-string/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Given a pattern string p, find all windows in string s where the frequency of each character matches p's frequency exactly. Two strings are anagrams/permutations iff they have the same character frequency map.

The trick: maintain a frequency map of the current window. As the window slides, update the map by adding the new right character and removing the left character. Compare the window map to the target map.

Key optimization: instead of comparing two 26-element arrays each step (O(26)), track a single counter `matches` = number of characters whose frequency is currently satisfied. Increment/decrement `matches` based on whether a character's window count crosses above/below its required count.

### Real-World Analogy
You have a shopping list (pattern p). Walk through a store shelf (string s) with a cart that holds exactly |p| items. As you push the cart forward, add one item from the right and drop one from the left. Check if your cart's contents match your shopping list at each position.

### Visual Walkthrough
```
s = "cbaebafd", p = "abc"
pFreq = {a:1, b:1, c:1}
Window size = 3

Window [0,2] = "cba": wFreq = {c:1, b:1, a:1}
  pFreq == wFreq? YES → record start index 0

Window [1,3] = "bae": wFreq = {b:1, a:1, e:1}
  NO match

Window [2,4] = "aeb": NO match
Window [3,5] = "eba": NO match
Window [4,6] = "baf": NO match

Window [5,7] = "afd": NO
...

Result: [0, 6]
```

### When TO use this pattern
- Find all starting positions where a window of s is an anagram of p
- Check if p is a permutation of a substring of s
- Frequency-based window matching with fixed window size

### When NOT to use this pattern
- Pattern matching where ORDER matters (use KMP, not frequency matching)
- Multiset matching where frequency must be a subset (slightly different tracking)

### Common Beginner Mistakes
- **Using set equality**: comparing `map == map` is O(k) per step; use a `matches` counter for O(1)
- **Handling non-p characters**: characters not in p are irrelevant to matching, but still affect window contents
- **Two Sum**: this problem uses a hash map for O(1) lookup — classified here but is not a sliding window

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "find all anagrams", "permutation of s in t", fixed-size frequency match |
| Core Idea | Track frequency map of window; compare to pattern frequency; use matches counter |
| Trigger Keywords | "anagram", "permutation", "same characters", "frequency match" |
| Avoid When | Order matters in matching |
| Time Complexity | O(n + m) — n=|s|, m=|p| |
| Space Complexity | O(1) — alphabet is fixed at 26 |

**Gotchas:**
- Window size is |p| (fixed) — this IS a fixed-size sliding window
- matches counter: only update when count crosses the threshold (== required or drops below)
- Two Sum note: hash map gives O(n) time, O(n) space — different from sliding window

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"anagram"` → frequency map matching, fixed window
- `"permutation"` → same as anagram (same chars, any order)
- `"same characters different order"` → frequency matching

---

## 4. C++ Template

```cpp
/*
 * Pattern: Character Frequency Matching
 * Use when: find windows matching pattern frequency
 * Time: O(n) | Space: O(1) with fixed alphabet
 */

// Using matches counter for O(1) comparison
vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    if (s.size() < p.size()) return result;

    vector<int> pFreq(26, 0), wFreq(26, 0);
    for (char c : p) pFreq[c - 'a']++;

    int k = p.size();
    int matches = 0;  // how many chars have correct frequency in window

    // build first window
    for (int i = 0; i < k; i++) {
        wFreq[s[i] - 'a']++;
    }
    // count initial matches
    for (int i = 0; i < 26; i++) {
        if (wFreq[i] == pFreq[i]) matches++;
    }
    if (matches == 26) result.push_back(0);

    // slide window
    for (int i = k; i < (int)s.size(); i++) {
        int add = s[i] - 'a';           // new right char
        int rem = s[i - k] - 'a';       // leaving left char

        // update match count before updating wFreq
        // ADD new character
        if (wFreq[add] == pFreq[add]) matches--;  // was matching, may break
        wFreq[add]++;
        if (wFreq[add] == pFreq[add]) matches++;  // now matching again?

        // REMOVE old character
        if (wFreq[rem] == pFreq[rem]) matches--;  // was matching, may break
        wFreq[rem]--;
        if (wFreq[rem] == pFreq[rem]) matches++;  // now matching again?

        if (matches == 26) result.push_back(i - k + 1);
    }
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Finding anagrams = finding windows with matching character frequencies. The window size is fixed at |p|. I slide the window and maintain a frequency map. For efficiency, instead of comparing two 26-element arrays each step (O(26)), I track a matches counter that counts how many characters have the correct frequency. This makes each slide O(1)."

### Interview Flow Checklist
- [ ] Window size is |p| (fixed)
- [ ] Explain frequency matching
- [ ] Mention matches counter optimization
- [ ] Handle edge: |s| < |p|
- [ ] Code and dry run

---

## 6. Problems

---

### Problem 1: 1. Two Sum
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/two-sum/
**Why this pattern fits:** Hash map for O(1) complement lookup — finds pair summing to target in one pass

**Problem Summary:**
Given array and target, return indices of two numbers that add up to target. Exactly one solution guaranteed.

**Optimal C++ Solution:**
```cpp
// Two Sum
// Approach: hash map stores value → index; check for complement on each pass
// Time: O(n) | Space: O(n)

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // value → index

    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];

        if (seen.count(complement)) {
            return {seen[complement], i};  // found the pair
        }
        seen[nums[i]] = i;  // store for future lookups
    }
    return {};
}
```

**Edge Cases:**
- [ ] Target requires using the same element twice (not allowed — check index)
- [ ] Negative numbers
- [ ] No solution (problem says exactly one, but in general return empty)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 567. Permutation in String
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/permutation-in-string/
**Why this pattern fits:** Check if any window of s has the same frequency as p

**Optimal C++ Solution:**
```cpp
// Permutation in String
// Time: O(n) | Space: O(1)

bool checkInclusion(string s1, string s2) {
    if (s1.size() > s2.size()) return false;
    int k = s1.size();

    vector<int> p(26, 0), w(26, 0);
    for (char c : s1) p[c - 'a']++;
    for (int i = 0; i < k; i++) w[s2[i] - 'a']++;

    if (p == w) return true;

    for (int i = k; i < (int)s2.size(); i++) {
        w[s2[i] - 'a']++;
        w[s2[i - k] - 'a']--;
        if (p == w) return true;
    }
    return false;
}
```

**Edge Cases:**
- [ ] s1 longer than s2
- [ ] s1 == s2

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 438. Find All Anagrams in a String
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-all-anagrams-in-a-string/
**Why this pattern fits:** Same as permutation check but collect all starting indices

**Optimal C++ Solution:**
```cpp
// Find All Anagrams in a String
// Time: O(n) | Space: O(1)

vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    if (s.size() < p.size()) return result;
    int k = p.size();

    vector<int> pf(26, 0), wf(26, 0);
    for (char c : p) pf[c - 'a']++;
    for (int i = 0; i < k; i++) wf[s[i] - 'a']++;
    if (pf == wf) result.push_back(0);

    for (int i = k; i < (int)s.size(); i++) {
        wf[s[i] - 'a']++;
        wf[s[i - k] - 'a']--;
        if (pf == wf) result.push_back(i - k + 1);
    }
    return result;
}
```

**Edge Cases:**
- [ ] No anagrams → return empty vector
- [ ] p longer than s → return empty

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Check if one string is a scramble of another (same characters, any rearrangement, potentially split and rearranged).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Frequency matching (with caveats for recursive scramble)
**Reason:** First check: same character frequency (necessary but not sufficient for true scramble). For full scramble check (LC 87), use DP or memoization on substrings.
</details>

---

**Drill 2:**
> Given two strings, find the minimum number of characters to add to make them anagrams.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Character frequency difference
**Reason:** Compute frequency maps of both strings. For each character, the difference in counts tells you how many need to be added. Sum all positive differences.
</details>

---

**Drill 3:**
> Find the shortest substring of s that contains all characters of t (each at least as many times as in t).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Minimum Window Substring (P09 — variable sliding window with frequency tracking)
**Reason:** This is exactly LC 76. Variable window: expand right until all of t's chars are covered, then shrink left to minimize.
</details>

---

**Drill 4:**
> Given n strings, group them into anagram groups.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Sort-as-key or frequency-as-key hash map
**Reason:** Sort each string → use as key. OR: encode frequency as a tuple "a1b2c3" → use as key. Group strings by their key. LC 49 (Group Anagrams).
</details>

---

**Drill 5:**
> Given a string, check if it can be rearranged into a palindrome.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Character frequency analysis
**Reason:** Count frequencies. A string can be a palindrome iff at most one character has an odd frequency (that char goes in the middle). Check count of odd-frequency chars ≤ 1.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Permutation check | O(n) | O(26) | Fixed alphabet |
| Find all anagrams | O(n) | O(26) | Fixed alphabet |
| Using matches counter | O(n) | O(26) | O(1) per slide with counter |
| Two Sum | O(n) | O(n) | Hash map lookup |

---

## 9. Common Follow-up Questions

1. What if the alphabet is not lowercase English (e.g., Unicode)? (Use unordered_map instead of vector[26])
2. Can you check in O(1) per slide without comparing two arrays? (Yes — matches counter: track how many chars have the right count)
3. Two Sum for sorted array? (Use converging two pointers — O(n) time, O(1) space)
4. Three Sum (sum of 3 elements = target)? (See P01 — sort + fix one + converging two pointers)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Fixed Sliding Window | All anagram/permutation problems | 438, 567 |
| Min Variable Window | Minimum window containing all chars | 76. Min Window Substring |
| Sorting | Group anagrams (hash by sorted string) | 49. Group Anagrams |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
