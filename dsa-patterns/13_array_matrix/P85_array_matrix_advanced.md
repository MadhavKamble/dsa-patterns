# P85 — Array and Matrix Advanced Patterns

## 1. First-Timer Explanation

### What Is It?
**Advanced array/matrix** patterns cover techniques that don't fit neatly into prefix sums, difference arrays, or matrix rotation: in-place index manipulation, cyclic replacement, Boyer-Moore majority vote, Dutch national flag, and coordinate hashing.

### Boyer-Moore Majority Vote
```
Find element appearing > n/2 times.
candidate=nums[0], count=1
For each x: if count==0, candidate=x, count=1
           elif x==candidate, count++
           else count--

The majority element will always survive: every non-candidate cancels
one candidate vote; since majority has > n/2 votes, it outlasts all others.
```

### Dutch National Flag (3-way partition)
```
Partition [0,1,2] in-place with one pass.
Three pointers: lo (left of lo: all 0s), mid (current), hi (right of hi: all 2s)

while mid <= hi:
  if arr[mid]==0: swap(arr[lo],arr[mid]); lo++; mid++
  elif arr[mid]==1: mid++
  else: swap(arr[mid],arr[hi]); hi-- (don't advance mid: new arr[mid] unknown)
```

### Cyclic Sort (for arrays with values 1..n)
```
Each value i should be at index i-1. If it's not, swap it there.
O(n) overall despite nested loops — each element is placed at most once.
```

### When to Use
- "Majority element" → Boyer-Moore vote
- "Sort colors (0,1,2)" → Dutch national flag
- "Find missing/duplicate number (1..n)" → cyclic sort or XOR or sum formula
- "Next permutation" → find rightmost descent, find next larger, reverse suffix
- "Rotate array" → reverse trick (3 reverses)

### Common Mistakes
1. Dutch national flag: when swapping with hi, don't advance mid (the swapped value needs checking)
2. Next permutation: find the pivot, then find the smallest element > pivot to its right
3. Cyclic sort: `while nums[i] != nums[i-1]` to handle duplicates
4. Rotate: direction matters — rotating right by k is NOT same as rotating left by k

---

## 2. Revision Card

**Recognition Signal:** "majority element", "sort colors", "missing number", "next permutation", "rotate array"

**Core Idea:**
- Majority vote: count up/down with one candidate; winner is majority
- Dutch flag: three-region partition with lo/mid/hi pointers
- Next permutation: find rightmost descending pair, swap with successor, reverse suffix

**Trigger Keywords:** majority, colors, cyclic, missing, permutation, rotate in-place

**Complexity:** O(n) time, O(1) space for all these patterns

---

## 3. Interview Tell Signs

- "Majority element (appears > n/2 times)" → Boyer-Moore vote
- "Sort 0s, 1s, 2s in place" → Dutch national flag
- "Missing number in 1..n" → XOR, formula `n(n+1)/2 - sum`, or cyclic sort
- "Find duplicate in 1..n array" → Floyd's cycle detection on array (treat as linked list)
- "Next/previous permutation" → find descent, swap, reverse
- "Rotate array right by k" → reverse [0..n-1], reverse [0..k-1], reverse [k..n-1]

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── Boyer-Moore Majority Vote ─────────────────────────────────────────────────
int majorityElement(vector<int>& nums) {
    int candidate = nums[0], count = 1;
    for (int i = 1; i < (int)nums.size(); i++) {
        if (count == 0) { candidate = nums[i]; count = 1; }
        else if (nums[i] == candidate) count++;
        else count--;
    }
    return candidate; // guaranteed to be majority if problem states one exists
}

// ── Dutch National Flag ───────────────────────────────────────────────────────
void sortColors(vector<int>& nums) {
    int lo = 0, mid = 0, hi = nums.size() - 1;
    while (mid <= hi) {
        if (nums[mid] == 0) { swap(nums[lo++], nums[mid++]); }
        else if (nums[mid] == 1) { mid++; }
        else { swap(nums[mid], nums[hi--]); } // don't advance mid
    }
}

// ── Next Permutation ──────────────────────────────────────────────────────────
void nextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 2;
    while (i >= 0 && nums[i] >= nums[i+1]) i--; // find rightmost descent
    if (i >= 0) {
        int j = n - 1;
        while (nums[j] <= nums[i]) j--; // find next larger element
        swap(nums[i], nums[j]);
    }
    reverse(nums.begin() + i + 1, nums.end()); // reverse suffix to get smallest
}

// ── Rotate Array Right by K ───────────────────────────────────────────────────
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k %= n;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

// ── Find Duplicate (Floyd's on Array) ────────────────────────────────────────
int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[0];
    do { slow = nums[slow]; fast = nums[nums[fast]]; } while (slow != fast);
    slow = nums[0];
    while (slow != fast) { slow = nums[slow]; fast = nums[fast]; }
    return slow;
}

// ── Missing Number (XOR) ──────────────────────────────────────────────────────
int missingNumber(vector<int>& nums) {
    int res = nums.size();
    for (int i = 0; i < (int)nums.size(); i++) res ^= i ^ nums[i];
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Boyer-Moore):**
> "I maintain a candidate and a count. For each element: if count is 0, make it the new candidate. If it matches the candidate, increment count. Otherwise decrement. The majority element (present > n/2 times) always survives because it can be canceled at most n/2 times by non-majority elements."

**Verbal Script (Next Permutation):**
> "Three steps: find the rightmost index i where nums[i] < nums[i+1] (the 'descent point'). Find the smallest element > nums[i] in the suffix (by scanning right from end). Swap them. Reverse everything after index i to get the lexicographically smallest suffix."

**Checklist:**
- [ ] Dutch flag: don't advance mid when swapping with hi
- [ ] Next permutation: if no descent found (fully descending), just reverse all
- [ ] Rotate array: `k %= n` first to handle k > n
- [ ] Floyd's for duplicate: treat indices as linked list nodes
- [ ] Missing number XOR: XOR all i from 0..n and all nums[i]; pairs cancel

---

## 6. Problems

### Problem 1: Majority Element
**Difficulty:** Easy | **LC:** 169

```cpp
int majorityElement(vector<int>& nums) {
    int cand=nums[0], cnt=1;
    for (int i=1; i<(int)nums.size(); i++) {
        if (cnt==0) {cand=nums[i]; cnt=1;}
        else cnt += (nums[i]==cand) ? 1 : -1;
    }
    return cand;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Sort Colors (Dutch National Flag)
**Difficulty:** Medium | **LC:** 75

```cpp
void sortColors(vector<int>& nums) {
    int lo=0, mid=0, hi=nums.size()-1;
    while (mid<=hi) {
        if (nums[mid]==0) swap(nums[lo++],nums[mid++]);
        else if (nums[mid]==1) mid++;
        else swap(nums[mid],nums[hi--]);
    }
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Next Permutation
**Difficulty:** Medium | **LC:** 31

```cpp
void nextPermutation(vector<int>& nums) {
    int n=nums.size(), i=n-2;
    while (i>=0&&nums[i]>=nums[i+1]) i--;
    if (i>=0) { int j=n-1; while(nums[j]<=nums[i]) j--; swap(nums[i],nums[j]); }
    reverse(nums.begin()+i+1,nums.end());
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Find the Duplicate Number
**Difficulty:** Medium | **LC:** 287

```cpp
int findDuplicate(vector<int>& nums) {
    int slow=nums[0], fast=nums[0];
    do { slow=nums[slow]; fast=nums[nums[fast]]; } while (slow!=fast);
    slow=nums[0];
    while (slow!=fast) { slow=nums[slow]; fast=nums[fast]; }
    return slow;
}
// Time: O(n) | Space: O(1)
// Treat array as linked list: index i points to nums[i]
// Values in [1,n] guarantee no null pointer
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Rotate Array
**Difficulty:** Medium | **LC:** 189

```cpp
void rotate(vector<int>& nums, int k) {
    int n=nums.size(); k%=n;
    reverse(nums.begin(),nums.end());
    reverse(nums.begin(),nums.begin()+k);
    reverse(nums.begin()+k,nums.end());
}
// Time: O(n) | Space: O(1)
// Intuition: rotating right by k = last k elements come first
// Reverse all → reverse first k → reverse rest
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: First Missing Positive
**Difficulty:** Hard | **LC:** 41

**Approach:** Cyclic sort — place each number at its correct index (num-1). Then scan for first missing.

```cpp
int firstMissingPositive(vector<int>& nums) {
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        while (nums[i] > 0 && nums[i] <= n && nums[nums[i]-1] != nums[i])
            swap(nums[i], nums[nums[i]-1]);
    }
    for (int i = 0; i < n; i++) if (nums[i] != i+1) return i+1;
    return n+1;
}
// Time: O(n) | Space: O(1)
// After sort: nums[i] == i+1 for all valid positions; first mismatch = answer
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Boyer-Moore on [3,3,4,2,3,1,3]. Trace candidate and count.
<details><summary>Reveal</summary>
Start: cand=3, cnt=1. x=3: cnt=2. x=4: cnt=1. x=2: cnt=0. x=3: cand=3,cnt=1. x=1: cnt=0. x=3: cand=3,cnt=1. Answer: 3 (appears 4 times > 7/2=3.5 ✓).
</details>

**Drill 2:** Sort colors [2,0,2,1,1,0] with Dutch national flag. Show lo/mid/hi at each step.
<details><summary>Reveal</summary>
lo=0,mid=0,hi=5. nums[0]=2: swap(mid,hi=5)→[0,0,2,1,1,2],hi=4. nums[0]=0: swap(lo=0,mid=0)→stay,lo=1,mid=1. nums[1]=0: swap(lo=1,mid=1)→stay,lo=2,mid=2. nums[2]=2: swap(mid=2,hi=4)→[0,0,1,1,2,2],hi=3. nums[2]=1: mid=3. nums[3]=1: mid=4>hi=3 → stop. Result: [0,0,1,1,2,2] ✓.
</details>

**Drill 3:** Next permutation of [1,3,2]. Find i (descent), then j.
<details><summary>Reveal</summary>
i: scan from right. nums[1]=3>nums[2]=2, so i=0 (nums[0]=1 < nums[1]=3). j: scan right from end for nums[j]>nums[i]=1. nums[2]=2>1 → j=2. Swap: [2,3,1]? Wait: swap nums[0]=1 with nums[2]=2 → [2,3,1]. Reverse suffix [1..end]: [2,1,3]? No: i=0, so suffix is [0+1..end]=[1..2]=[3,1] → reversed to [1,3]. Hmm: [2,1,3]. Expected next permutation of [1,3,2] is [2,1,3] ✓.
</details>

**Drill 4:** Floyd's duplicate on [1,3,4,2,2]. Trace slow and fast.
<details><summary>Reveal</summary>
slow=nums[0]=1, fast=nums[0]=1. Do-while: slow=nums[1]=3, fast=nums[nums[1]]=nums[3]=2. slow=nums[3]=2, fast=nums[nums[2]]=nums[4]=2. slow=nums[2]=4, fast=nums[nums[4]]=nums[2]=4. slow=nums[4]=2, fast=nums[nums[4]]=nums[2]=4. Hmm let me redo: fast=nums[nums[fast]] at each step. Start: slow=1,fast=1. Step1: slow=nums[1]=3; fast=nums[nums[1]]=nums[3]=2. Step2: slow=nums[3]=2; fast=nums[nums[2]]=nums[4]=2. slow==fast==2 → phase2. slow=nums[0]=1. While slow!=fast: slow=nums[1]=3, fast=nums[2]=4. slow=nums[3]=2, fast=nums[4]=2. slow==fast==2 → return 2. Duplicate=2 ✓.
</details>

**Drill 5:** First missing positive in [3,4,-1,1]. After cyclic sort, what does the array look like?
<details><summary>Reveal</summary>
n=4. i=0: nums[0]=3, correct pos=2. Swap [0] and [2]: [-1,4,3,1]. nums[0]=-1: invalid, leave. i=1: nums[1]=4, correct pos=3. Swap [1] and [3]: [-1,1,3,4]. nums[1]=1, correct pos=0. Swap [1] and [0]: [1,-1,3,4]. nums[1]=-1: invalid, leave. i=2: nums[2]=3, correct pos=2. Already correct. i=3: nums[3]=4, correct pos=3. Already correct. Result: [1,-1,3,4]. Scan: i=0: 1==1 ✓. i=1: -1≠2 → return 2.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Majority element | O(n) | O(1) |
| Sort colors | O(n) | O(1) |
| Next permutation | O(n) | O(1) |
| Find duplicate (Floyd's) | O(n) | O(1) |
| Rotate array | O(n) | O(1) |
| First missing positive | O(n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Majority element appearing > n/3 times (could be up to 2 candidates)?**
A: Boyer-Moore with TWO candidates and two counts. Maintain `cand1, cnt1, cand2, cnt2`. If neither matches, decrement both. Then verify both candidates against the array.

**Q: Find all permutations in lexicographic order?**
A: Start with sorted array. Repeatedly call nextPermutation() until back to sorted (descending). For k-th permutation, use the factorial number system (P47).

**Q: Is there a way to find the duplicate without modifying the array or extra space?**
A: Yes — Floyd's cycle detection (treat array as linked list). The duplicate is the cycle entry point.

---

## 10. Cross-Pattern Connections

- **P75 (Slow/Fast Pointers):** Floyd's cycle detection is identical; duplicate = cycle start
- **P47 (Permutations):** Next permutation connects to generating all permutations
- **P70 (XOR Tricks):** Missing number via XOR is an XOR cancellation trick
- **P04 (Two Pointers):** Dutch national flag is a three-pointer generalization of two-pointer partition
- **P85 → P46 (Subsets):** Cyclic sort is the array analog of in-place subset generation
