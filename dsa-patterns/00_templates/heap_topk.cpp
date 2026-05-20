/*
 * ============================================================
 * TEMPLATE: Heap / Priority Queue — Top K & Related Patterns
 * ============================================================
 * Use when: find K largest/smallest, median, merge K sorted lists,
 *           scheduling, or any "maintain best K" problem
 * Time: O(n log k) for Top K | Space: O(k)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: KTH LARGEST — MIN-HEAP of size K
// ─────────────────────────────────────────────────────────────
// Key insight: min-heap of size K keeps the K LARGEST elements.
// The heap's top (minimum of the K largest) = Kth largest.

int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;  // min-heap

    for (int num : nums) {
        minHeap.push(num);

        if ((int)minHeap.size() > k) {
            minHeap.pop();  // remove the smallest → keeps K largest
        }
    }
    return minHeap.top();  // Kth largest = minimum of K largest
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: TOP K FREQUENT ELEMENTS
// ─────────────────────────────────────────────────────────────

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int n : nums) freq[n]++;

    // min-heap: (frequency, number)
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minHeap;

    for (auto& [num, cnt] : freq) {
        minHeap.push({cnt, num});
        if ((int)minHeap.size() > k) minHeap.pop();
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: TWO HEAPS — RUNNING MEDIAN
// ─────────────────────────────────────────────────────────────
// maxHeap = lower half | minHeap = upper half
// Balance so sizes differ by at most 1
// Median = top of larger heap, or average of both tops

class MedianFinder {
    priority_queue<int> maxHeap;                                // lower half (max-heap)
    priority_queue<int, vector<int>, greater<int>> minHeap;    // upper half (min-heap)

public:
    void addNum(int num) {
        // always add to max-heap first
        maxHeap.push(num);

        // balance: ensure every element in maxHeap ≤ every element in minHeap
        if (!minHeap.empty() && maxHeap.top() > minHeap.top()) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }

        // balance sizes: maxHeap can have at most 1 more element than minHeap
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }

    double findMedian() {
        if (maxHeap.size() > minHeap.size()) return maxHeap.top();
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};

// ─────────────────────────────────────────────────────────────
// VARIANT 4: K-WAY MERGE
// ─────────────────────────────────────────────────────────────
// Merge K sorted lists using a min-heap

struct ListNode { int val; ListNode* next; ListNode(int x):val(x),next(nullptr){} };

ListNode* mergeKLists(vector<ListNode*>& lists) {
    // min-heap: (value, list_index, node_pointer)
    auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

    // push head of each non-empty list
    for (ListNode* head : lists) {
        if (head) pq.push(head);
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (!pq.empty()) {
        ListNode* node = pq.top();
        pq.pop();
        tail->next = node;
        tail = tail->next;

        if (node->next) pq.push(node->next);  // push next from same list
    }
    return dummy.next;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 5: MEETING ROOMS II (scheduling)
// ─────────────────────────────────────────────────────────────
// Minimum number of rooms = max overlapping intervals at any point
// Use min-heap to track earliest ending meeting

int minMeetingRooms(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());  // sort by start time

    priority_queue<int, vector<int>, greater<int>> endTimes;  // min-heap of end times

    for (auto& interval : intervals) {
        int start = interval[0], end = interval[1];

        if (!endTimes.empty() && endTimes.top() <= start) {
            // earliest ending meeting ended before this starts: reuse the room
            endTimes.pop();
        }
        endTimes.push(end);  // add this meeting's end time
    }

    return endTimes.size();  // heap size = rooms needed
}

// ─────────────────────────────────────────────────────────────
// VARIANT 6: K CLOSEST POINTS TO ORIGIN
// ─────────────────────────────────────────────────────────────

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    // max-heap of (distance, index) — keeps K smallest distances
    priority_queue<pair<int,int>> maxHeap;  // {dist, idx}

    for (int i = 0; i < (int)points.size(); i++) {
        int dist = points[i][0]*points[i][0] + points[i][1]*points[i][1];
        maxHeap.push({dist, i});

        if ((int)maxHeap.size() > k) maxHeap.pop();  // remove farthest
    }

    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(points[maxHeap.top().second]);
        maxHeap.pop();
    }
    return result;
}

/*
 * ─────────────────────────────────────────────────────────────
 * HEAP TYPE SELECTION
 * ─────────────────────────────────────────────────────────────
 *  K LARGEST  → min-heap of size K (top = Kth largest)
 *  K SMALLEST → max-heap of size K (top = Kth smallest)
 *  MEDIAN     → two heaps (max lower + min upper)
 *  K-WAY MERGE → min-heap initialized with heads
 *  SCHEDULING  → min-heap of end times
 *
 * ─────────────────────────────────────────────────────────────
 * C++ SYNTAX
 * ─────────────────────────────────────────────────────────────
 *  Max-heap (default):  priority_queue<int> pq;
 *  Min-heap:            priority_queue<int, vector<int>, greater<int>> pq;
 *  Custom comparator:   priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Min-heap for K largest vs max-heap — mix-up causes wrong answer
 *  2. Two heaps: must maintain size balance AND value invariant
 *  3. K-way merge: push next node ONLY if it exists
 *  4. Distances: use squared distance (avoid sqrt, no precision issues)
 *  5. Scheduling: sort by START time before using heap on END times
 */
