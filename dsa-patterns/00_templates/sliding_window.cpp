/*
 * ============================================================
 * TEMPLATE: Sliding Window (Fixed Size)
 * ============================================================
 * Use when: problem asks for result over every subarray/substring
 *           of FIXED length k
 * Time: O(n) | Space: O(1) or O(k)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: FIXED SIZE SLIDING WINDOW
// ─────────────────────────────────────────────────────────────
// Use when: k is given and constant; compute sum/max/etc. over window

double fixedWindowMaxAverage(vector<int>& nums, int k) {
    double windowSum = 0;

    // build the first window of size k
    for (int i = 0; i < k; i++) {
        windowSum += nums[i];
    }
    double maxAvg = windowSum / k;

    // slide the window: add new element, remove old element
    for (int i = k; i < (int)nums.size(); i++) {
        windowSum += nums[i];      // add the new right element
        windowSum -= nums[i - k];  // remove the old left element (k steps back)
        maxAvg = max(maxAvg, windowSum / k);
    }
    return maxAvg;
}

// Fixed window with a frequency map (e.g., find all anagrams)
vector<int> findAnagrams(string s, string p) {
    vector<int> result;
    if (s.size() < p.size()) return result;

    vector<int> pCount(26, 0), wCount(26, 0);  // frequency maps

    // build pattern frequency and first window frequency
    for (int i = 0; i < (int)p.size(); i++) {
        pCount[p[i] - 'a']++;
        wCount[s[i] - 'a']++;
    }

    if (pCount == wCount) result.push_back(0);

    // slide the fixed window
    for (int i = p.size(); i < s.size(); i++) {
        wCount[s[i] - 'a']++;              // include new right char
        wCount[s[i - p.size()] - 'a']--;  // remove old left char
        if (pCount == wCount) result.push_back(i - p.size() + 1);
    }
    return result;
}
