/*
 * ============================================================
 * TEMPLATE: Two Pointers
 * ============================================================
 * Use when: Array/string problem that can be solved without
 *           examining every pair → reduces O(n²) to O(n)
 * Prerequisite: Often requires sorted input (converging variant)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: CONVERGING (both ends moving inward)
// ─────────────────────────────────────────────────────────────
// Use when: searching for a pair/triple satisfying a condition
//           in a SORTED array
// Time: O(n) | Space: O(1)
// Examples: Two Sum II, Container With Most Water, 3Sum

int convergingTwoPointers(vector<int>& arr, int target) {
    int lo = 0;               // left pointer starts at beginning
    int hi = arr.size() - 1;  // right pointer starts at end

    while (lo < hi) {
        int sum = arr[lo] + arr[hi];

        if (sum == target) {
            return 1;           // found a valid pair
        } else if (sum < target) {
            lo++;               // sum too small → move left pointer right to increase
        } else {
            hi--;               // sum too large → move right pointer left to decrease
        }
    }
    return -1;  // no valid pair found
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: FAST & SLOW (Floyd's cycle detection)
// ─────────────────────────────────────────────────────────────
// Use when: detecting cycles, finding midpoint, finding duplicate
//           in linked list or array
// Time: O(n) | Space: O(1)

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool hasCycle(ListNode* head) {
    ListNode* slow = head;  // moves 1 step at a time
    ListNode* fast = head;  // moves 2 steps at a time

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;        // 1 step
        fast = fast->next->next;  // 2 steps

        if (slow == fast) return true;  // cycle detected: they meet
    }
    return false;  // fast reached end → no cycle
}

ListNode* findMiddle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    // when fast reaches end, slow is at middle
    // for even length: slow lands at second-middle node
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: FIXED SEPARATION (k-apart pointers)
// ─────────────────────────────────────────────────────────────
// Use when: need to find element k steps from end,
//           or maintain a constant gap between pointers
// Time: O(n) | Space: O(1)

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;

    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    // advance fast pointer n+1 steps ahead
    // so when fast reaches null, slow is at node BEFORE the target
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }

    // move both until fast reaches end
    while (fast != nullptr) {
        slow = slow->next;
        fast = fast->next;
    }

    // slow.next is the node to remove
    slow->next = slow->next->next;
    return dummy.next;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: READ/WRITE POINTERS (in-place array modification)
// ─────────────────────────────────────────────────────────────
// Use when: filter elements in-place, remove duplicates,
//           partition array by a condition
// Time: O(n) | Space: O(1)

// Remove duplicates from sorted array → return new length
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;

    int write = 1;  // write pointer: next position to write unique element
                    // starts at 1 because first element is always unique

    for (int read = 1; read < (int)nums.size(); read++) {
        // read pointer scans every element
        if (nums[read] != nums[write - 1]) {
            // found a new unique element → write it
            nums[write] = nums[read];
            write++;
        }
        // if duplicate, read moves on but write stays (effectively "deleting")
    }
    return write;  // new length of deduplicated array
}

// Move all zeros to end, maintain relative order of non-zeros
void moveZeroes(vector<int>& nums) {
    int write = 0;  // position to write next non-zero element

    // Phase 1: compact all non-zeros to front
    for (int read = 0; read < (int)nums.size(); read++) {
        if (nums[read] != 0) {
            nums[write++] = nums[read];
        }
    }
    // Phase 2: fill rest with zeros
    while (write < (int)nums.size()) {
        nums[write++] = 0;
    }
}

// ─────────────────────────────────────────────────────────────
// VARIANT 5: EXPANDING FROM CENTER
// ─────────────────────────────────────────────────────────────
// Use when: palindrome detection, finding longest palindromic
//           substring
// Time: O(n²) | Space: O(1)

string longestPalindromeExpand(const string& s) {
    int n = s.size();
    int start = 0, maxLen = 1;

    // helper: expand around center and return length of palindrome
    auto expand = [&](int l, int r) {
        // expand outward as long as characters match and within bounds
        while (l >= 0 && r < n && s[l] == s[r]) {
            if (r - l + 1 > maxLen) {
                start = l;
                maxLen = r - l + 1;
            }
            l--;  // expand left
            r++;  // expand right
        }
    };

    for (int i = 0; i < n; i++) {
        expand(i, i);      // odd length palindrome: single center
        expand(i, i + 1);  // even length palindrome: two-char center
    }

    return s.substr(start, maxLen);
}

// ─────────────────────────────────────────────────────────────
// VARIANT 6: CONVERGING ON UNSORTED (Dutch National Flag)
// ─────────────────────────────────────────────────────────────
// Use when: 3-way partition (sort colors, 0/1/2)
// Time: O(n) | Space: O(1)

void sortColors(vector<int>& nums) {
    int lo = 0;                    // everything before lo is 0
    int mid = 0;                   // everything between lo and mid is 1
    int hi = nums.size() - 1;      // everything after hi is 2

    while (mid <= hi) {
        if (nums[mid] == 0) {
            swap(nums[lo++], nums[mid++]);  // 0: move to front, advance both
        } else if (nums[mid] == 1) {
            mid++;                           // 1: already in correct region
        } else {
            swap(nums[mid], nums[hi--]);    // 2: move to back, hi shrinks
            // don't advance mid: newly swapped element needs to be examined
        }
    }
}

/*
 * ─────────────────────────────────────────────────────────────
 * DECISION GUIDE: Which variant to use?
 * ─────────────────────────────────────────────────────────────
 *
 *  "find pair/triple with sum X in sorted array"
 *      → CONVERGING (variant 1)
 *
 *  "detect cycle", "find duplicate in range [1,n]", "find middle"
 *      → FAST & SLOW (variant 2)
 *
 *  "remove Nth from end", "find element k steps from end"
 *      → FIXED SEPARATION (variant 3)
 *
 *  "remove duplicates in-place", "move zeros", "filter elements"
 *      → READ/WRITE (variant 4)
 *
 *  "longest palindromic substring"
 *      → EXPANDING FROM CENTER (variant 5)
 *
 *  "sort array with 3 distinct values" (0/1/2)
 *      → DUTCH NATIONAL FLAG (variant 6)
 *
 * ─────────────────────────────────────────────────────────────
 * COMPLEXITY TABLE
 * ─────────────────────────────────────────────────────────────
 *  All variants: Time O(n) | Space O(1)
 *  Exception: Expanding From Center is O(n²) time
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Forgetting to sort before using converging variant
 *  2. Off-by-one in fixed separation (use n+1 advance trick)
 *  3. In Dutch Flag: not re-examining mid after swapping with hi
 *  4. Fast/slow: check fast != null AND fast->next != null
 *  5. Expand from center: try BOTH odd (i,i) and even (i,i+1)
 */
