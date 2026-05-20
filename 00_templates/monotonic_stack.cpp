/*
 * ============================================================
 * TEMPLATE: Monotonic Stack
 * ============================================================
 * Use when: find Next Greater / Next Smaller Element,
 *           sum of subarray min/max, largest rectangle
 * Time: O(n) — each element pushed/popped at most once
 * Space: O(n) for the stack
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: NEXT GREATER ELEMENT (monotonic decreasing stack)
// ─────────────────────────────────────────────────────────────
// Maintain stack in DECREASING order
// When a larger element arrives, it's the "next greater" for top

vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);  // default: -1 if no greater element
    stack<int> stk;             // stack of INDICES (not values)

    for (int i = 0; i < n; i++) {
        // pop all elements smaller than current → current is their answer
        while (!stk.empty() && nums[stk.top()] < nums[i]) {
            result[stk.top()] = nums[i];  // nums[i] is NGE for this index
            stk.pop();
        }
        stk.push(i);  // push current index (will find its NGE later)
    }
    // elements remaining in stack have no greater element → result stays -1
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: DAILY TEMPERATURES (days until warmer)
// ─────────────────────────────────────────────────────────────

vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    vector<int> result(n, 0);
    stack<int> stk;  // stack of indices

    for (int i = 0; i < n; i++) {
        while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
            int idx = stk.top();
            stk.pop();
            result[idx] = i - idx;  // distance to next warmer day
        }
        stk.push(i);
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: CIRCULAR ARRAY (use index % n trick)
// ─────────────────────────────────────────────────────────────

vector<int> nextGreaterCircular(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, -1);
    stack<int> stk;

    // iterate 2n times to simulate circular behavior
    for (int i = 0; i < 2 * n; i++) {
        int actual = i % n;

        while (!stk.empty() && nums[stk.top()] < nums[actual]) {
            result[stk.top()] = nums[actual];
            stk.pop();
        }
        // only push in first pass (avoid duplicating stack entries)
        if (i < n) stk.push(actual);
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: LARGEST RECTANGLE IN HISTOGRAM
// ─────────────────────────────────────────────────────────────
// Monotonic INCREASING stack
// When a shorter bar arrives, pop and compute area for each taller bar

int largestRectangleHistogram(vector<int>& heights) {
    stack<int> stk;  // stack of indices in increasing height order
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i <= n; i++) {
        // treat sentinel height 0 at the end to flush the stack
        int currHeight = (i == n) ? 0 : heights[i];

        while (!stk.empty() && heights[stk.top()] > currHeight) {
            int h = heights[stk.top()];
            stk.pop();
            // width: from the element below stack top to current index
            int width = stk.empty() ? i : (i - stk.top() - 1);
            maxArea = max(maxArea, h * width);
        }
        stk.push(i);
    }
    return maxArea;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 5: SUM OF SUBARRAY MINIMUMS
// ─────────────────────────────────────────────────────────────
// For each element, find how many subarrays it is the minimum of

int sumSubarrayMins(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    int n = arr.size();
    long long result = 0;

    stack<int> stk;  // monotonic increasing stack of indices

    for (int i = 0; i <= n; i++) {
        int curr = (i == n) ? 0 : arr[i];

        while (!stk.empty() && arr[stk.top()] > curr) {
            int mid = stk.top();
            stk.pop();
            int left  = stk.empty() ? -1 : stk.top();   // previous smaller
            int right = i;                                // next smaller

            // arr[mid] is the minimum for subarrays starting in (left, mid]
            // and ending in [mid, right)
            long long count = (long long)(mid - left) * (right - mid);
            result = (result + count * arr[mid]) % MOD;
        }
        stk.push(i);
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 6: REMOVE K DIGITS (lexicographically smallest)
// ─────────────────────────────────────────────────────────────

string removeKdigits(string num, int k) {
    stack<char> stk;

    for (char c : num) {
        // remove larger digits from top to make number smaller
        while (k > 0 && !stk.empty() && stk.top() > c) {
            stk.pop();
            k--;
        }
        stk.push(c);
    }

    // if k remains, remove from the end (largest remaining)
    while (k-- > 0) stk.pop();

    // build result (stack is in bottom-to-top = left-to-right order)
    string result;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }
    reverse(result.begin(), result.end());

    // remove leading zeros
    int start = result.find_first_not_of('0');
    return (start == string::npos) ? "0" : result.substr(start);
}

/*
 * ─────────────────────────────────────────────────────────────
 * DECISION GUIDE
 * ─────────────────────────────────────────────────────────────
 *
 *  DECREASING stack → finds NEXT GREATER element
 *  INCREASING stack → finds NEXT SMALLER element
 *  Both variants → O(n) since each element is pushed/popped once
 *
 * ─────────────────────────────────────────────────────────────
 * TELL SIGNS
 * ─────────────────────────────────────────────────────────────
 *  "next greater/smaller element"
 *  "number of days until temperature rises"
 *  "largest rectangle in histogram"
 *  "sum/product over all subarrays involving min/max"
 *  "remove digits to minimize number"
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Storing values in stack instead of INDICES (you need indices for width)
 *  2. Histogram: forgetting the sentinel 0 at the end to flush remaining bars
 *  3. Circular array: iterating 2n but only pushing in first n iterations
 *  4. SubarrayMins: formula is (mid-left) * (right-mid), not the other way
 */
