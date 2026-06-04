# 🔥 Hard Array Problems: P37–P41

> **Step 3 — Arrays · P37 to P41**

---

# P37 — Merge Two Sorted Arrays Without Extra Space

> **LeetCode #88** (variant, no extra space) · **Difficulty:** Hard

## 🧠 Problem Understanding

Merge two sorted arrays `arr1[0..M-1]` and `arr2[0..N-1]` into sorted order **without extra space**.

**Input:** `arr1=[1,4,8,10]`, `arr2=[2,3,9]` → `arr1=[1,2,3,4]`, `arr2=[8,9,10]`

---

## 🥇 Optimal — Gap Method (Shell Sort idea)

### Key Observation
> 💡 Use gap = `ceil((M+N)/2)`. Compare elements `gap` apart across the combined virtual array. Swap if out of order. Halve gap each round.

### Algorithm
1. `gap = ceil((M+N)/2)`
2. While `gap >= 1`:
   - Compare all pairs `(i, i+gap)` treating `arr1` and `arr2` as one virtual array
   - Swap if `left > right`
   - `gap = ceil(gap/2)`; if gap was 1 → stop

### Complexity
- **Time:** O((M+N) log(M+N)) · **Space:** O(1)

```cpp
/*
 * MERGE WITHOUT EXTRA SPACE — Gap Method
 * Virtual array: arr1[0..M-1] + arr2[0..N-1]
 * Gap comparison and swap, halve gap each round
 * Time O((M+N) log(M+N)) | Space O(1)
 */
class Solution {
    void gapSwap(vector<int>& a1, vector<int>& a2, int i, int j) {
        int m = a1.size();
        int& left  = (i < m) ? a1[i] : a2[i - m];
        int& right = (j < m) ? a1[j] : a2[j - m];
        if (left > right) swap(left, right);
    }
public:
    void merge(vector<int>& arr1, int m, vector<int>& arr2, int n) {
        int total = m + n;
        int gap = (total + 1) / 2;

        while (gap > 0) {
            for (int i = 0; i + gap < total; i++)
                gapSwap(arr1, arr2, i, i + gap);
            if (gap == 1) break;
            gap = (gap + 1) / 2;
        }
    }
};
```

---

# P38 — Find the Repeating and Missing Number

> **GFG Classic** · **Difficulty:** Hard

## 🧠 Problem Understanding

Given array of N numbers where each number 1..N appears exactly once except one (repeating) and one (missing). Find both.

**Input:** `[3,1,3]` → Repeating=3, Missing=2

---

## 🥇 Optimal — Math (Sum + Sum of Squares)

### Key Observation
Let `X = repeating`, `Y = missing`.
- `sumArr - sumExpected = X - Y` ... (eq1)
- `sumSqArr - sumSqExpected = X² - Y²` ... (eq2)

From eq2: `(X-Y)(X+Y) = diff²`. From eq1: `X+Y = diff²/(X-Y)`.  
Then: `X = ((X-Y) + (X+Y)) / 2`, `Y = X - (X-Y)`.

```cpp
pair<int,int> findTwoElement(vector<int>& arr, int n) {
    long long s = 0, s2 = 0;
    for (int x : arr) { s += x; s2 += (long long)x*x; }
    long long expected = (long long)n*(n+1)/2;
    long long expected2 = (long long)n*(n+1)*(2*n+1)/6;

    long long diff = s - expected;           // X - Y
    long long diff2 = s2 - expected2;        // X² - Y²
    long long sumXY = diff2 / diff;          // X + Y

    long long X = (diff + sumXY) / 2;       // repeating
    long long Y = X - diff;                  // missing

    return {(int)X, (int)Y};
}
```

**Time:** O(N) · **Space:** O(1)

---

# P39 — Count Inversions

> **GFG Classic** · **Difficulty:** Hard

## 🧠 Problem Understanding

Count pairs `(i,j)` where `i < j` but `arr[i] > arr[j]`.

**Input:** `[2,4,1,3,5]` → **Output:** `3` (pairs: (2,1),(4,1),(4,3))

---

## 🥇 Optimal — Modified Merge Sort

### Key Observation
> 💡 During merge of two sorted halves, when we take from right half (arr[j] < arr[i]), ALL remaining left half elements form inversions with arr[j]. Add `mid - i + 1` to count.

```cpp
long long mergeCount(vector<int>& arr, int l, int mid, int r) {
    vector<int> temp;
    long long count = 0;
    int i = l, j = mid + 1;

    while (i <= mid && j <= r) {
        if (arr[i] <= arr[j]) {
            temp.push_back(arr[i++]);
        } else {
            count += (mid - i + 1);      // all remaining left elements > arr[j]
            temp.push_back(arr[j++]);
        }
    }
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);
    for (int k = 0; k < temp.size(); k++) arr[l + k] = temp[k];
    return count;
}

long long mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r) return 0;
    int mid = l + (r - l) / 2;
    long long cnt = mergeSort(arr, l, mid) + mergeSort(arr, mid+1, r);
    cnt += mergeCount(arr, l, mid, r);
    return cnt;
}
// Time O(N log N) | Space O(N)
```

---

# P40 — Reverse Pairs

> **LeetCode #493** · **Difficulty:** Hard

## 🧠 Problem Understanding

Count pairs `(i,j)` where `i < j` and `arr[i] > 2 * arr[j]`.

**Input:** `[1,3,2,3,1]` → **Output:** `2`

---

## 🥇 Optimal — Modified Merge Sort

### Key Observation
Same as count inversions but condition is `arr[i] > 2 * arr[j]`.  
**Separate counting from merging:** Count pairs first (two pointer across sorted halves), then merge.

```cpp
long long mergeCount(vector<int>& arr, int l, int mid, int r) {
    long long count = 0;
    int j = mid + 1;
    // count reverse pairs (before actual merge)
    for (int i = l; i <= mid; i++) {
        while (j <= r && (long long)arr[i] > 2LL * arr[j]) j++;
        count += (j - (mid + 1));
    }
    // now do regular merge
    vector<int> temp;
    int left = l, right = mid + 1;
    while (left <= mid && right <= r)
        temp.push_back(arr[left] <= arr[right] ? arr[left++] : arr[right++]);
    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= r) temp.push_back(arr[right++]);
    for (int k = 0; k < temp.size(); k++) arr[l + k] = temp[k];
    return count;
}
// Time O(N log N) | Space O(N)
```

---

# P41 — Maximum Product Subarray

> **LeetCode #152** · **Difficulty:** Medium

## 🧠 Problem Understanding

Find the contiguous subarray with the maximum product.

**Input:** `[2,3,-2,4]` → **Output:** `6` (subarray `[2,3]`)

---

## 🥇 Optimal — Track Max and Min

### Key Observation
> 💡 A negative number can flip max to min and min to max. Track both `maxProd` and `minProd`. On each element:
> - New max = `max(x, x*prevMax, x*prevMin)`
> - New min = `min(x, x*prevMax, x*prevMin)`

```cpp
/*
 * MAXIMUM PRODUCT SUBARRAY
 * Track both max and min (negatives can flip)
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxP = nums[0], minP = nums[0], result = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            // temp to avoid using updated maxP in minP calc
            int tempMax = max({nums[i], maxP * nums[i], minP * nums[i]});
            int tempMin = min({nums[i], maxP * nums[i], minP * nums[i]});
            maxP = tempMax;
            minP = tempMin;
            result = max(result, maxP);
        }
        return result;
    }
};
```

**Alternative** (cleaner for interviews): traverse forward AND backward, track running product, reset on 0:
```cpp
int maxProduct(vector<int>& nums) {
    int res = *max_element(nums.begin(), nums.end());
    int cur = 1;
    for (int x : nums) {                    // left to right
        cur = (cur == 0 ? 1 : cur) * x;
        res = max(res, cur);
    }
    cur = 1;
    for (int i = nums.size()-1; i >= 0; i--) {  // right to left
        cur = (cur == 0 ? 1 : cur) * nums[i];
        res = max(res, cur);
    }
    return res;
}
```

---

## 🧾 Recall Lines

| Problem | Key Technique | Complexity |
|---------|--------------|------------|
| P37 Merge No Space | Gap method, halving | O((M+N)log(M+N))/O(1) |
| P38 Repeat+Missing | Sum + sum-of-squares equations | O(N)/O(1) |
| P39 Count Inversions | Merge sort, count right-takes | O(N log N)/O(N) |
| P40 Reverse Pairs | Merge sort, count before merge | O(N log N)/O(N) |
| P41 Max Product | Track max AND min (negative flip) | O(N)/O(1) |

---

## ⚠️ Common Mistakes

**P37:** Gap must use `ceil` division: `(total+1)/2` not `total/2`  
**P38:** `diff2 / diff` integer division requires exact divisibility (guaranteed by math)  
**P39:** Count INSIDE merge (not after); add `mid-i+1` not just 1  
**P40:** Count BEFORE merging (sorted order needed for counting, then merge separately)  
**P41:** Must save old maxP before computing new minP; or use temp variables

## 🏆 Pattern Categories
- P37: `Arrays · Gap Method`
- P38: `Arrays · Math · Number Theory`
- P39-P40: `Arrays · Divide & Conquer · Merge Sort`
- P41: `Arrays · Dynamic Programming · Greedy`
