/*
 * ============================================================
 * TEMPLATE: Binary Search
 * ============================================================
 * Use when: search space is sorted OR has a monotone property
 *           (feasible/infeasible boundary)
 * Time: O(log n) | Space: O(1)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: CLASSIC — find exact target
// ─────────────────────────────────────────────────────────────

int binarySearch(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;

    while (lo <= hi) {  // ← "=" because lo==hi is still a valid single element
        int mid = lo + (hi - lo) / 2;  // avoid overflow: NOT (lo+hi)/2

        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) lo = mid + 1;  // target in right half
        else                         hi = mid - 1;  // target in left half
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: LOWER BOUND — first position where nums[i] >= target
// ─────────────────────────────────────────────────────────────
// Returns: insertion point such that all left elements < target

int lowerBound(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size();  // hi = n (one past end) for insertion

    while (lo < hi) {  // ← strict "<" (lo==hi means we've converged)
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] < target) lo = mid + 1;  // mid is too small, go right
        else                    hi = mid;       // mid could be the answer, don't skip
    }
    return lo;  // lo == hi at convergence; this is the first index >= target
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: UPPER BOUND — first position where nums[i] > target
// ─────────────────────────────────────────────────────────────

int upperBound(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size();

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] <= target) lo = mid + 1;  // mid is ≤ target, go right
        else                     hi = mid;
    }
    return lo;  // first index > target
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: ROTATED SORTED ARRAY
// ─────────────────────────────────────────────────────────────

int searchRotated(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] == target) return mid;

        // determine which half is sorted
        if (nums[lo] <= nums[mid]) {
            // left half [lo..mid] is sorted
            if (nums[lo] <= target && target < nums[mid]) {
                hi = mid - 1;  // target in sorted left half
            } else {
                lo = mid + 1;  // target in right half
            }
        } else {
            // right half [mid..hi] is sorted
            if (nums[mid] < target && target <= nums[hi]) {
                lo = mid + 1;  // target in sorted right half
            } else {
                hi = mid - 1;  // target in left half
            }
        }
    }
    return -1;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 5: BINARY SEARCH ON ANSWER
// ─────────────────────────────────────────────────────────────
// Use when: "find minimum X such that [condition is satisfied]"
// The answer space is [lo, hi] and condition is monotone

// Example: Koko eating bananas — min speed to eat all in H hours
bool canEatAll(vector<int>& piles, int speed, int H) {
    int hours = 0;
    for (int pile : piles) {
        hours += (pile + speed - 1) / speed;  // ceil division
    }
    return hours <= H;
}

int minEatingSpeed(vector<int>& piles, int H) {
    int lo = 1;                                    // min possible speed
    int hi = *max_element(piles.begin(), piles.end());  // max possible speed

    // find minimum speed (lo-biased)
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (canEatAll(piles, mid, H)) {
            hi = mid;      // mid works, try smaller (minimize)
        } else {
            lo = mid + 1;  // mid doesn't work, need more speed
        }
    }
    return lo;  // lo == hi == minimum valid speed
}

// ─────────────────────────────────────────────────────────────
// VARIANT 6: FIND PEAK ELEMENT
// ─────────────────────────────────────────────────────────────

int findPeakElement(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (nums[mid] > nums[mid + 1]) {
            // peak is in left half (including mid)
            hi = mid;
        } else {
            // peak is in right half
            lo = mid + 1;
        }
    }
    return lo;  // lo == hi == peak index
}

/*
 * ─────────────────────────────────────────────────────────────
 * BINARY SEARCH CHEAT SHEET
 * ─────────────────────────────────────────────────────────────
 *
 *  | Goal                          | Condition         | Move lo/hi    |
 *  |-------------------------------|-------------------|---------------|
 *  | Find exact target             | nums[mid]==target | lo=mid+1 else hi=mid-1 |
 *  | First index >= target         | nums[mid] < t     | lo=mid+1      |
 *  | First index > target          | nums[mid] <= t    | lo=mid+1      |
 *  | Min X where f(X) is true      | f(mid) == true    | hi=mid        |
 *  | Max X where f(X) is true      | f(mid) == true    | lo=mid        |
 *
 * ─────────────────────────────────────────────────────────────
 * LOOP INVARIANT
 * ─────────────────────────────────────────────────────────────
 *  while (lo <= hi):  target could be at lo, mid, or hi → terminates when lo > hi
 *  while (lo < hi):   lo==hi means we have the answer → use when searching for boundary
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Integer overflow: use lo + (hi-lo)/2, NOT (lo+hi)/2
 *  2. Infinite loop: if lo=mid instead of lo=mid+1 when condition fails
 *  3. Off-by-one: hi=n vs hi=n-1 depends on whether answer can be at end
 *  4. Binary search on answer: always verify "does mid satisfy the condition?"
 *  5. Rotated array: check which HALF is sorted, not just mid comparison
 */
