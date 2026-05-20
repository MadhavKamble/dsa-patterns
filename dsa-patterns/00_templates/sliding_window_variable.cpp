/*
 * ============================================================
 * TEMPLATE: Variable Size Sliding Window
 * ============================================================
 * Use when: find min/max length subarray/substring satisfying
 *           a condition; window size changes dynamically
 * Time: O(n) amortized | Space: O(1) or O(k)
 *
 * KEY INSIGHT: Every element enters the window once and leaves
 * once → O(n) total even though there's a nested loop.
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: MINIMUM SIZE WINDOW SATISFYING CONDITION
// ─────────────────────────────────────────────────────────────
// Use when: "find SHORTEST subarray where [condition]"
// Example: Minimum Size Subarray Sum ≥ target

int minSizeSubarraySum(vector<int>& nums, int target) {
    int lo = 0;          // left boundary of window
    int windowSum = 0;   // current window sum
    int minLen = INT_MAX;

    for (int hi = 0; hi < (int)nums.size(); hi++) {
        windowSum += nums[hi];  // EXPAND: include nums[hi] in window

        // SHRINK: while condition is satisfied, try to reduce window
        // (we want minimum, so shrink as much as possible)
        while (windowSum >= target) {
            minLen = min(minLen, hi - lo + 1);  // record valid window
            windowSum -= nums[lo];              // remove leftmost element
            lo++;                               // shrink from left
        }
    }
    return (minLen == INT_MAX) ? 0 : minLen;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: MAXIMUM SIZE WINDOW SATISFYING CONDITION
// ─────────────────────────────────────────────────────────────
// Use when: "find LONGEST subarray/substring where [condition]"
// Example: Longest Substring Without Repeating Characters

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> freq;  // character frequency in window
    int lo = 0;                      // left boundary
    int maxLen = 0;

    for (int hi = 0; hi < (int)s.size(); hi++) {
        freq[s[hi]]++;  // EXPAND: include s[hi]

        // SHRINK: while window is INVALID (has duplicate), shrink
        while (freq[s[hi]] > 1) {
            freq[s[lo]]--;  // remove leftmost char
            lo++;           // shrink from left
        }
        // window is now valid: update answer
        maxLen = max(maxLen, hi - lo + 1);
    }
    return maxLen;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: COUNT SUBARRAYS SATISFYING CONDITION
// ─────────────────────────────────────────────────────────────
// Use when: "count subarrays/substrings where [condition]"
// Trick: count(at most K) - count(at most K-1) = count(exactly K)

// Count subarrays with product less than k
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;

    int lo = 0;
    int product = 1;
    int count = 0;

    for (int hi = 0; hi < (int)nums.size(); hi++) {
        product *= nums[hi];  // EXPAND

        // SHRINK: while product too large
        while (product >= k) {
            product /= nums[lo];
            lo++;
        }
        // all subarrays ending at hi with left boundary in [lo, hi] are valid
        // that's (hi - lo + 1) subarrays
        count += hi - lo + 1;
    }
    return count;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: WINDOW WITH CHARACTER CONSTRAINT
// ─────────────────────────────────────────────────────────────
// Use when: "at most K distinct characters", "longest with ≤ K replacements"
// Example: Longest Repeating Character Replacement

int characterReplacement(string s, int k) {
    vector<int> freq(26, 0);
    int lo = 0;
    int maxFreq = 0;  // frequency of the most common char in window
    int maxLen = 0;

    for (int hi = 0; hi < (int)s.size(); hi++) {
        freq[s[hi] - 'A']++;
        maxFreq = max(maxFreq, freq[s[hi] - 'A']);

        // window size - maxFreq = characters that need to be replaced
        // if that count exceeds k, window is invalid → shrink
        int windowSize = hi - lo + 1;
        if (windowSize - maxFreq > k) {
            freq[s[lo] - 'A']--;  // remove leftmost
            lo++;
            // NOTE: we don't update maxFreq here — it can only stay or grow,
            // so even if it's stale, window size stays same (not worse)
        }
        maxLen = max(maxLen, hi - lo + 1);
    }
    return maxLen;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 5: MINIMUM WINDOW SUBSTRING (two freq maps)
// ─────────────────────────────────────────────────────────────
// Use when: find minimum window in s containing all chars of t
// Time: O(|s| + |t|) | Space: O(|t|)

string minWindow(string s, string t) {
    unordered_map<char, int> need;      // chars we need
    for (char c : t) need[c]++;

    int have = 0;             // how many chars we've satisfied
    int required = need.size();  // how many distinct chars we need
    int lo = 0;
    int minStart = 0, minLen = INT_MAX;

    unordered_map<char, int> window;

    for (int hi = 0; hi < (int)s.size(); hi++) {
        char c = s[hi];
        window[c]++;

        // check if this char's requirement is now fully met
        if (need.count(c) && window[c] == need[c]) {
            have++;
        }

        // shrink while all requirements are satisfied
        while (have == required) {
            // update answer
            if (hi - lo + 1 < minLen) {
                minLen = hi - lo + 1;
                minStart = lo;
            }
            // remove leftmost char and possibly break a requirement
            char left = s[lo];
            window[left]--;
            if (need.count(left) && window[left] < need[left]) {
                have--;
            }
            lo++;
        }
    }
    return (minLen == INT_MAX) ? "" : s.substr(minStart, minLen);
}

/*
 * ─────────────────────────────────────────────────────────────
 * UNIVERSAL VARIABLE WINDOW SKELETON
 * ─────────────────────────────────────────────────────────────
 *
 *  int lo = 0;
 *  STATE state;   // sum, freq map, count, product, etc.
 *  int answer = initial_value;
 *
 *  for (int hi = 0; hi < n; hi++) {
 *      // EXPAND: add nums[hi] / s[hi] to state
 *      state.add(arr[hi]);
 *
 *      // SHRINK: while window is INVALID (or while valid for min-size)
 *      while (isInvalid(state)) {     // OR: while (isValid(state)) for min
 *          state.remove(arr[lo]);
 *          lo++;
 *      }
 *
 *      // UPDATE ANSWER with current valid window [lo, hi]
 *      answer = update(answer, hi - lo + 1);
 *  }
 *
 * ─────────────────────────────────────────────────────────────
 * DECISION: SHRINK CONDITION
 * ─────────────────────────────────────────────────────────────
 *  MAX length → shrink while INVALID
 *  MIN length → shrink while VALID (try to be as small as possible)
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Forgetting to update answer AFTER shrink (not before)
 *  2. Using if instead of while for shrink (handles multi-step invalidity)
 *  3. Off-by-one: window length is hi - lo + 1 (not hi - lo)
 *  4. Not initializing freq map for both window and need
 */
