# 🔥 Sort an Array of 0s, 1s and 2s (Dutch National Flag)

> **LeetCode #75** · **Difficulty:** Medium · **Step 3 — Arrays · P18**

---

## 🧠 Problem Understanding

Sort an array containing only 0s, 1s, and 2s **in-place** in a single pass without extra space.

**Input:** `[2,0,2,1,1,0]` → **Output:** `[0,0,1,1,2,2]`

---

## 🥉 Brute Force
Sort the array. **Time:** O(N log N)

## 🥈 Better — Count and Fill
Count 0s, 1s, 2s, then fill. **Time:** O(N) · **Space:** O(1) but **2 passes**

---

## 🥇 Optimal — Dutch National Flag (1 Pass)

### Key Observation
> 💡 Three pointers: `lo` (boundary of 0s), `mid` (current element), `hi` (boundary of 2s).
> - `arr[mid] == 0`: swap with `arr[lo]`, advance both `lo` and `mid`
> - `arr[mid] == 1`: just advance `mid`
> - `arr[mid] == 2`: swap with `arr[hi]`, advance `hi` back (don't advance `mid` — swapped element unknown)

```
[0 .. lo-1] = all 0s
[lo .. mid-1] = all 1s
[mid .. hi] = unknown
[hi+1 .. N-1] = all 2s
```

### Algorithm
1. `lo=0, mid=0, hi=N-1`
2. While `mid <= hi`:
   - If `arr[mid]==0`: `swap(arr[lo],arr[mid])`, `lo++, mid++`
   - If `arr[mid]==1`: `mid++`
   - If `arr[mid]==2`: `swap(arr[mid],arr[hi])`, `hi--`

### Dry Run
`arr = [2, 0, 2, 1, 1, 0]`

| lo | mid | hi | arr[mid] | Action | Array |
|----|-----|-----|----------|--------|-------|
| 0 | 0 | 5 | 2 | swap(0,5), hi-- | [0,0,2,1,1,**2**] |
| 0 | 0 | 4 | 0 | swap(0,0), lo++,mid++ | [**0**,0,2,1,1,2] |
| 1 | 1 | 4 | 0 | swap(1,1), lo++,mid++ | [0,**0**,2,1,1,2] |
| 2 | 2 | 4 | 2 | swap(2,4), hi-- | [0,0,**1**,1,2,2] |
| 2 | 2 | 3 | 1 | mid++ | [0,0,**1**,1,2,2] |
| 2 | 3 | 3 | 1 | mid++ | [0,0,1,**1**,2,2] |
| mid>hi → stop | | | | | |

**Output:** `[0, 0, 1, 1, 2, 2]` ✅

### Complexity
- **Time:** O(N) — single pass · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * DUTCH NATIONAL FLAG — 3-pointer single pass
 *
 * INVARIANT:
 *   arr[0..lo-1] = 0s (sorted)
 *   arr[lo..mid-1] = 1s (sorted)
 *   arr[mid..hi] = unknown
 *   arr[hi+1..N-1] = 2s (sorted)
 *
 * KEY: when swap 2 to hi, don't advance mid (swapped val is unknown)
 *
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int lo = 0, mid = 0, hi = nums.size() - 1;

        while (mid <= hi) {
            if (nums[mid] == 0) {
                swap(nums[lo++], nums[mid++]);   // 0 goes to front
            } else if (nums[mid] == 1) {
                mid++;                            // 1 is in correct zone
            } else {
                swap(nums[mid], nums[hi--]);      // 2 goes to back
                // don't advance mid — new nums[mid] is unknown
            }
        }
    }
};
```

---

## 🎤 Interview Explanation Script
> "This is the Dutch National Flag problem by Dijkstra. I use three pointers: `lo` for the 0-boundary, `mid` as the current pointer, `hi` for the 2-boundary."

> "When I see a 0, I swap it to the `lo` position and advance both lo and mid — I know the swapped element was a 1 (from the sorted 1s region). When I see a 2, I swap it to `hi` but don't advance mid — I don't know what came back. When I see a 1, just advance mid."

> "This gives one pass, O(N) time, O(1) space."

---

## 🧾 Recall Line
> "lo=0, mid=0, hi=N-1. 0: swap lo,mid, both++. 1: mid++. 2: swap mid,hi, hi-- (don't advance mid)."

## 📝 Short Revision Notes
- Dutch National Flag by Dijkstra — classic algorithm
- Key: on swap with `hi`, don't advance `mid` (unknown element comes back)
- On swap with `lo`, safe to advance `mid` (lo position had 1, now confirmed)
- Extension: sort 3 distinct values, sort K categories

## ⚠️ Common Mistakes
❌ Advancing `mid` after swapping with `hi` — skips element, wrong result  
❌ Starting `lo > 0` or `hi < N-1`  
❌ While condition `mid < hi` instead of `mid <= hi`

## 🔥 What Interviewer Is Testing
- Dutch National Flag algorithm
- Why `mid` doesn't advance on swap with `hi`

## 📚 Related Problems
- [ ] LeetCode #75 — Sort Colors
- [ ] LeetCode #905 — Sort Array by Parity (partition even/odd — same idea)
- [ ] LeetCode #2149 — Rearrange Array Elements by Sign

## 🏆 Pattern Category
`Arrays` · `Two Pointers` · `In-Place` · `Partitioning`

## ⏱️ 30-Second Revision
> 3 pointers: lo=0, mid=0, hi=n-1. While mid≤hi: 0→swap(lo,mid),lo++,mid++. 1→mid++. 2→swap(mid,hi),hi--.
