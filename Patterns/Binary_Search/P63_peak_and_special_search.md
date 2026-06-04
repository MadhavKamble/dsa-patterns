# P63 — Peak Finding and Special Binary Search

## 1. First-Timer Explanation

### What Is It?
Not all binary search problems involve sorted arrays. **Peak finding** and other "special" binary searches apply when the structure is partially ordered or has a specific shape:
- **Peak in array:** `nums[i] > nums[i-1] && nums[i] > nums[i+1]`
- **Mountain array:** Strictly increases then strictly decreases
- **Median of two sorted arrays:** Partition trick

The key: even without full sorting, you can find a local property (going uphill/downhill) that tells you which half to discard.

### Peak Finding Insight
```
[1, 2, 3, 1]
      ^peak (index 2)

At index mid, compare with nums[mid+1]:
- If nums[mid] < nums[mid+1]: peak is to the RIGHT (going uphill → peak must be ahead)
- If nums[mid] > nums[mid+1]: peak is to the LEFT or at mid (going downhill → peak is here or left)
```

This gives O(log n) peak finding even though the array isn't sorted.

### Median of Two Sorted Arrays
The partition trick: partition both arrays such that the left side has half the total elements. Binary search on the smaller array's partition point.

```
A = [1, 3, 5]
B = [2, 4, 6]

Partition A at i=1, B at j=2:
A_left=[1], A_right=[3,5]
B_left=[2,4], B_right=[6]

Check: max(left) ≤ min(right)?
max(1,4)=4, min(3,6)=3 → 4>3: wrong partition, move right

Partition A at i=2, B at j=1:
A_left=[1,3], A_right=[5]
B_left=[2], B_right=[4,6]

max(3,2)=3 ≤ min(5,4)=4 ✓
Median = (max(left) + min(right)) / 2 = (3+4)/2 = 3.5 ✓
```

### When to Use
- "Find a peak element" → peak binary search
- "Find element in mountain array" → two-phase binary search
- "Median of two sorted arrays" → partition trick
- "Local minimum/maximum in partially ordered structure"

---

## 2. Revision Card

**Recognition Signal:** "find peak", "mountain array", "median of two sorted arrays", "local minimum"

**Core Idea (Peak):** At mid, if nums[mid] < nums[mid+1] → go right. Else → go left (mid might be peak). Converges to a peak.

**Core Idea (Median):** Binary search partition of smaller array. Ensure left halves combine to (m+n)/2 elements and cross-partition max ≤ cross-partition min.

**Trigger Keywords:** peak, mountain, median two arrays, local max

**Complexity:** O(log n) peak; O(log(min(m,n))) for median

---

## 3. Interview Tell Signs

- "Find any peak" → peak binary search
- "Mountain array" → find peak first, then binary search each side
- "Median of two sorted arrays in O(log n)" → partition trick
- "Local minimum in undirected graph" → variation of peak finding

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Find Peak Element ─────────────────────────────────────────────────────────
int findPeakElement(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < nums[mid+1]) lo = mid + 1; // going uphill, peak is right
        else hi = mid;                              // going downhill, peak is here or left
    }
    return lo;
}

// ── Median of Two Sorted Arrays ───────────────────────────────────────────────
double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
    if (A.size() > B.size()) swap(A, B); // ensure A is smaller
    int m = A.size(), n = B.size();
    int lo = 0, hi = m;
    
    while (lo <= hi) {
        int i = (lo + hi) / 2;          // partition A at i
        int j = (m + n + 1) / 2 - i;   // partition B at j
        
        int A_left  = (i == 0) ? INT_MIN : A[i-1];
        int A_right = (i == m) ? INT_MAX : A[i];
        int B_left  = (j == 0) ? INT_MIN : B[j-1];
        int B_right = (j == n) ? INT_MAX : B[j];
        
        if (A_left <= B_right && B_left <= A_right) {
            if ((m + n) % 2 == 0)
                return (max(A_left, B_left) + min(A_right, B_right)) / 2.0;
            else
                return max(A_left, B_left);
        } else if (A_left > B_right) {
            hi = i - 1;
        } else {
            lo = i + 1;
        }
    }
    return 0;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Peak):**
> "At any midpoint, I compare nums[mid] with nums[mid+1]. If mid < mid+1, I'm on an upward slope — the peak must be to the right. Otherwise, I'm on a downward slope or at a peak — the answer is mid or to the left. This is O(log n) binary search without needing a fully sorted array."

**Verbal Script (Median):**
> "Binary search on partitioning the smaller array. I partition A at position i and B at j=(m+n+1)/2-i so combined left side has half the elements. I need max(left) ≤ min(right). If A_left > B_right, move i left; if B_left > A_right, move i right. When the partition is valid, the median is max(left) for odd total, or (max(left)+min(right))/2 for even."

---

## 6. Problems

### Problem 1: Find Peak Element
**Difficulty:** Medium | **LC:** 162

```cpp
int findPeakElement(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] < nums[mid+1]) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}
// Time: O(log n) | Space: O(1)
// Note: nums[-1] = nums[n] = -inf by problem guarantee
// Guaranteed that nums[i] != nums[i+1] for all i
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Find in Mountain Array
**Difficulty:** Hard | **LC:** 1095

**Approach:** Find peak (binary search). Search ascending half. If not found, search descending half.

```cpp
// MountainArray interface: get(index), length()
int findInMountainArray(int target, MountainArray& arr) {
    int n = arr.length();
    
    // Step 1: Find peak
    int lo = 0, hi = n - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr.get(mid) < arr.get(mid+1)) lo = mid + 1;
        else hi = mid;
    }
    int peak = lo;
    
    // Step 2: Search ascending part [0, peak]
    lo = 0; hi = peak;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = arr.get(mid);
        if (val == target) return mid;
        else if (val < target) lo = mid + 1;
        else hi = mid - 1;
    }
    
    // Step 3: Search descending part [peak+1, n-1]
    lo = peak + 1; hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = arr.get(mid);
        if (val == target) return mid;
        else if (val > target) lo = mid + 1; // descending: go right for smaller
        else hi = mid - 1;
    }
    
    return -1;
}
// Time: O(log n) (3 binary searches) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Median of Two Sorted Arrays
**Difficulty:** Hard | **LC:** 4

```cpp
double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
    if (A.size() > B.size()) swap(A, B);
    int m = A.size(), n = B.size();
    int lo = 0, hi = m;
    
    while (lo <= hi) {
        int i = (lo + hi) / 2;
        int j = (m + n + 1) / 2 - i;
        
        int Al = (i == 0) ? INT_MIN : A[i-1];
        int Ar = (i == m) ? INT_MAX : A[i];
        int Bl = (j == 0) ? INT_MIN : B[j-1];
        int Br = (j == n) ? INT_MAX : B[j];
        
        if (Al <= Br && Bl <= Ar) {
            if ((m + n) % 2 == 0) return (max(Al,Bl) + min(Ar,Br)) / 2.0;
            return max(Al, Bl);
        }
        if (Al > Br) hi = i - 1;
        else lo = i + 1;
    }
    return 0;
}
// Time: O(log(min(m,n))) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Valid Perfect Square (Binary Search)
**Difficulty:** Easy | **LC:** 367

```cpp
bool isPerfectSquare(int num) {
    long long lo = 1, hi = num;
    while (lo <= hi) {
        long long mid = lo + (hi - lo) / 2;
        if (mid * mid == num) return true;
        else if (mid * mid < num) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Why does peak binary search work on an array that's not sorted?
<details><summary>Reveal</summary>
The invariant is not "sorted" but "uphill or downhill." At mid, if nums[mid] < nums[mid+1], we're going uphill — a peak MUST exist in [mid+1, hi] because the array must eventually come down (or end, which counts). This monotone direction property is sufficient for binary search.
</details>

**Drill 2:** Mountain array: why search ascending half first?
<details><summary>Reveal</summary>
The problem asks for the leftmost occurrence (smallest index). If the target appears on the ascending side, that index is smaller than any index on the descending side. Search left-to-right priority returns the leftmost result.
</details>

**Drill 3:** Median of two sorted arrays: why ensure A is the smaller array?
<details><summary>Reveal</summary>
We binary search on A's partition point i in [0, m]. B's partition j = (m+n+1)/2 - i must be valid (0 ≤ j ≤ n). If m > n, j could become negative for small i. Ensuring m ≤ n guarantees j is always in [0, n].
</details>

**Drill 4:** Peak finding: nums=[1,2,3,4,5]. Where is the peak?
<details><summary>Reveal</summary>
Index 4 (value 5). The algorithm: mid=2, nums[2]=3 < nums[3]=4 → lo=3. mid=3, nums[3]=4 < nums[4]=5 → lo=4. lo==hi=4. Peak at index 4. (Boundary: nums[5] = -inf by problem statement, so index 4 is a valid peak.)
</details>

**Drill 5:** For median of [1,3] and [2], the partition should give what result?
<details><summary>Reveal</summary>
Total m+n=3, odd. Left side needs 2 elements. Binary search on A=[1,3]: try i=1, j=1. A_left=1, A_right=3, B_left=2, B_right=INT_MAX. Check: 1 ≤ INF and 2 ≤ 3 ✓. Median = max(A_left=1, B_left=2) = 2 ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Find Peak Element | O(log n) | O(1) |
| Find in Mountain Array | O(log n) | O(1) |
| Median Two Sorted Arrays | O(log(min(m,n))) | O(1) |
| Valid Perfect Square | O(log n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Can you find ALL peaks in O(log n)?**
A: No — there can be O(n) peaks, and finding all requires at least O(n) time. The O(log n) algorithm finds ANY one peak.

**Q: What if you need the global maximum (not just any peak)?**
A: Linear scan O(n). Binary search only guarantees finding some local maximum (peak).

**Q: Median of K sorted arrays?**
A: Binary search on value range [global_min, global_max]. Count elements ≤ mid across all arrays. O(K × N × log(max-min)) where N = max array length.

**Q: Why INT_MIN / INT_MAX for boundary sentinels in median problem?**
A: When i=0 (nothing in A's left half), we want A_left to be conceptually -∞ (never blocks). When i=m (all of A in left), A_right = +∞. The INT_MIN/INT_MAX sentinels simulate these boundaries.

---

## 10. Cross-Pattern Connections

- **P59 (Binary Search Basics):** Same template; different condition
- **P60 (Rotated Array):** Also binary search on partially ordered array
- **P61 (Binary Search on Answer):** Value-space binary search; median uses index-space
- **P43 (Two Heaps/Median Stream):** Dynamic median; this is static two-array median
