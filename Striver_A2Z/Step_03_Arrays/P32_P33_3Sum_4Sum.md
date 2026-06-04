# 🔥 3-Sum Problem & 4-Sum Problem

> **LeetCode #15 & #18** · **Difficulty:** Medium · **Step 3 — P32 & P33**

---

# P32 — 3-Sum

## 🧠 Problem Understanding

Find all **unique** triplets `[a, b, c]` such that `a + b + c = 0`. No duplicate triplets.

**Input:** `[-1,0,1,2,-1,-4]` → `[[-1,-1,2],[-1,0,1]]`

---

## 🥉 Brute Force
3 nested loops + set for deduplication. **Time:** O(N³)

## 🥈 Better — Hash Set
Fix first element, use hash map for two-sum. **Time:** O(N²) · **Space:** O(N)

---

## 🥇 Optimal — Sort + Two Pointers

### Key Observation
> 💡 Sort the array. Fix `arr[i]`. Use two pointers `l=i+1, r=N-1` to find pairs summing to `-arr[i]`. Skip duplicates carefully.

### Algorithm
1. Sort the array
2. For `i` from 0 to N-3:
   - Skip if `arr[i] > 0` (all elements after are ≥ arr[i], can't sum to 0)
   - Skip duplicate: if `i > 0` and `arr[i] == arr[i-1]`
   - `l=i+1, r=N-1`
   - While `l < r`:
     - `sum = arr[i] + arr[l] + arr[r]`
     - If `sum == 0`: add triplet, skip dup at `l` and `r`
     - If `sum < 0`: `l++`
     - If `sum > 0`: `r--`

### Dry Run
`sorted = [-4,-1,-1,0,1,2]`

i=0, arr[i]=-4: l=1,r=5: sum=-4+(-1)+2=-3<0→l++; ...(no triplet)  
i=1, arr[i]=-1: l=2,r=5: sum=-1+(-1)+2=0 ✅ → add [-1,-1,2], skip dups  
  l=3,r=4: sum=-1+0+1=0 ✅ → add [-1,0,1]  
i=2, arr[i]=-1: skip (dup of i=1)  
i=3, arr[i]=0: l=4,r=5: sum=0+1+2=3>0→r--; (no triplet)

**Output:** `[[-1,-1,2],[-1,0,1]]` ✅

### Complexity
- **Time:** O(N²) · **Space:** O(1) extra

---

## 💻 Clean C++ Code — 3Sum

```cpp
/*
 * 3-SUM — Sort + Two Pointers
 * Fix arr[i], find pair summing to -arr[i] with two pointers
 * Skip duplicates at each level
 * Time O(N²) | Space O(1)
 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int n = nums.size();

        for (int i = 0; i < n - 2; i++) {
            if (nums[i] > 0) break;              // sorted: rest all positive, can't sum to 0
            if (i > 0 && nums[i] == nums[i-1]) continue;  // skip dup for i

            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    result.push_back({nums[i], nums[l], nums[r]});
                    while (l < r && nums[l] == nums[l+1]) l++;  // skip dup l
                    while (l < r && nums[r] == nums[r-1]) r--;  // skip dup r
                    l++; r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    r--;
                }
            }
        }
        return result;
    }
};
```

---

# P33 — 4-Sum

## 🧠 Problem Understanding

Find all unique quadruplets `[a,b,c,d]` summing to `target`.

**Same idea: sort + fix two, two-pointer for remaining two.**

```cpp
/*
 * 4-SUM — Sort + Two outer loops + Two Pointers
 * Time O(N³) | Space O(1)
 */
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        int n = nums.size();

        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i-1]) continue;    // skip dup i

            for (int j = i + 1; j < n - 2; j++) {
                if (j > i+1 && nums[j] == nums[j-1]) continue;  // skip dup j

                int l = j + 1, r = n - 1;
                while (l < r) {
                    long long sum = (long long)nums[i] + nums[j] + nums[l] + nums[r];
                    if (sum == target) {
                        result.push_back({nums[i], nums[j], nums[l], nums[r]});
                        while (l < r && nums[l] == nums[l+1]) l++;
                        while (l < r && nums[r] == nums[r-1]) r--;
                        l++; r--;
                    } else if (sum < target) l++;
                    else r--;
                }
            }
        }
        return result;
    }
};
```

---

## 🎤 Interview Explanation Script
> "3-Sum: sort first, fix one element with a loop, then find the complementary pair using converging two pointers. Skip duplicates at each pointer to avoid duplicate triplets. O(N²)."

> "4-Sum: add another outer loop — fix two elements, then two-pointer for the remaining two. O(N³). The overflow trap: sum of 4 integers can exceed INT_MAX, use `long long`."

---

## 🧾 Recall Lines
> **3Sum:** Sort. Fix `arr[i]`. Two pointers `l,r` for sum == `-arr[i]`. Skip dups. O(N²).  
> **4Sum:** Sort. Fix `arr[i]`, `arr[j]`. Two pointers. Use `long long`. Skip dups. O(N³).

## 📝 Short Revision Notes
- Sort enables two-pointer and deduplication
- Dup skip: `if (i > 0 && nums[i] == nums[i-1]) continue` — not `if (nums[i] == nums[i-1])`
- After finding a valid pair in 3Sum: advance BOTH pointers and skip dups
- 4Sum: `long long` to prevent overflow

## ⚠️ Common Mistakes
❌ Dup skip at index 0: `if (i > 0 && ...)` not `if (i >= 0 && ...)` — would skip first element  
❌ Not skipping dups for `l` and `r` inside the two-pointer loop  
❌ `int` overflow in 4Sum for large values

## 📚 Related Problems
- [ ] LeetCode #15 — 3Sum
- [ ] LeetCode #16 — 3Sum Closest
- [ ] LeetCode #18 — 4Sum
- [ ] Striver P17 — 2Sum (foundation)

## 🏆 Pattern Category
`Arrays` · `Two Pointers` · `Sorting`

## ⏱️ 30-Second Revision
> 3Sum: sort, fix i, two pointers l=i+1 r=n-1, skip dups. O(N²).  
> 4Sum: fix i,j then two pointers, `long long` sum, skip dups. O(N³).
