# P53 — Interval Scheduling and Greedy Intervals

## 1. First-Timer Explanation

### What Is It?
**Interval scheduling** problems involve selecting or processing intervals (start, end) optimally. The **greedy** insight: for maximum non-overlapping intervals, always pick the interval that ends earliest. This leaves maximum room for future intervals.

The key greedy patterns:
1. **Activity Selection (max non-overlapping):** Sort by end time, greedily pick earliest-ending compatible interval
2. **Merge overlapping intervals:** Sort by start, merge if overlapping
3. **Insert interval:** Binary search or linear scan to find insertion point, merge

### Analogy — Activity Selection
You have one conference room and many meeting requests. To fit the most meetings: always accept the meeting that ends soonest (not the shortest, not the earliest starting — the earliest ENDING). This frees the room as early as possible for future meetings.

Wrong intuition: pick shortest meeting → "1 hour" meeting from 9AM-10AM might block a 30-min meeting from 9:30-10AM and a 30-min from 10AM-10:30AM. Earliest-end is provably optimal.

### Visual Walkthrough — Activity Selection
```
Intervals (sorted by end): [(1,2),(3,4),(0,6),(5,7),(8,9),(5,9)]

Take (1,2)? Yes (first). cur_end = 2
Take (3,4)? 3 > 2 → YES. cur_end = 4
Take (0,6)? 0 < 4 (overlaps) → skip
Take (5,7)? 5 > 4 → YES. cur_end = 7
Take (8,9)? 8 > 7 → YES. cur_end = 9
Take (5,9)? 5 < 9 → skip

Max intervals: 4
```

### When to Use
- "Maximum number of non-overlapping intervals"
- "Minimum arrows to burst balloons"
- "Merge overlapping intervals"
- "Insert interval"
- "Minimum number of platforms/rooms" → sort starts and ends separately

### When NOT to Use
- Intervals have weights → weighted job scheduling → DP not greedy
- Need all valid selections (not just maximum) → backtracking

### Common Mistakes
1. Sorting by start time for max non-overlapping (wrong — use end time)
2. Forgetting to handle empty input
3. Off-by-one in overlap check: `start > cur_end` vs `start >= cur_end`
4. Merge intervals: `max(cur_end, interval.end)` when merging (not just `interval.end`)

---

## 2. Revision Card

**Recognition Signal:** "non-overlapping intervals", "merge intervals", "maximum activities"

**Core Idea (Max Non-Overlapping):** Sort by end time. Greedily take interval if `start >= last_end`. Update `last_end = current.end`.

**Core Idea (Merge):** Sort by start. If `cur.start <= last.end`, merge: `last.end = max(last.end, cur.end)`. Else, push last and update.

**Trigger Keywords:** intervals, meetings, overlapping, non-overlapping, merge, insert

**Complexity:**
| Problem | Time | Space |
|---------|------|-------|
| Activity selection | O(n log n) | O(1) |
| Merge intervals | O(n log n) | O(n) |
| Insert interval | O(n) | O(n) |
| Min arrows | O(n log n) | O(1) |

---

## 3. Interview Tell Signs

- "Maximum number of activities" → sort by end, greedy
- "Minimum number of removals" → n - max_non_overlapping
- "Merge all overlapping" → sort by start, linear merge
- "Minimum meeting rooms" → sort starts and ends, two pointers (P45)
- "Insert interval into sorted list" → binary search or linear scan

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── Activity Selection (max non-overlapping) ─────────────────────────────────
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[1] < b[1]; // sort by END time
    });
    int count = 0, end = INT_MIN;
    for (auto& iv : intervals) {
        if (iv[0] >= end) { count++; end = iv[1]; } // compatible: take it
    }
    return (int)intervals.size() - count; // total - kept = removed
}

// ── Merge Intervals ──────────────────────────────────────────────────────────
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end()); // sort by start
    vector<vector<int>> res;
    for (auto& iv : intervals) {
        if (!res.empty() && iv[0] <= res.back()[1])
            res.back()[1] = max(res.back()[1], iv[1]); // merge
        else
            res.push_back(iv); // new interval
    }
    return res;
}

// ── Insert Interval ──────────────────────────────────────────────────────────
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    int i = 0, n = intervals.size();
    // Add all intervals that end before newInterval starts
    while (i < n && intervals[i][1] < newInterval[0]) res.push_back(intervals[i++]);
    // Merge all overlapping intervals
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    res.push_back(newInterval);
    // Add remaining
    while (i < n) res.push_back(intervals[i++]);
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "For maximum non-overlapping intervals, I sort by end time. The greedy choice: always take the interval that ends soonest, as it leaves the most room for future intervals. This is provably optimal by exchange argument. For merge intervals: sort by start, then linearly scan — merge if the next interval starts at or before the current end."

**Checklist:**
- [ ] Max non-overlapping → sort by END (not start, not duration)
- [ ] Merge → sort by START
- [ ] Correct overlap condition: `new.start <= last.end` (not strict <)
- [ ] When merging: `max(last.end, new.end)` — don't assume new.end is larger
- [ ] State the exchange argument proof if asked

---

## 6. Problems

### Problem 1: Non-overlapping Intervals (Min Removal)
**Difficulty:** Medium | **LC:** 435

```cpp
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    int keep = 0, end = INT_MIN;
    for (auto& iv : intervals) {
        if (iv[0] >= end) { keep++; end = iv[1]; }
    }
    return intervals.size() - keep;
}
// Time: O(n log n) | Space: O(1)
// Note: min removal = total - max non-overlapping
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Merge Intervals
**Difficulty:** Medium | **LC:** 56

```cpp
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> res;
    for (auto& iv : intervals) {
        if (!res.empty() && iv[0] <= res.back()[1])
            res.back()[1] = max(res.back()[1], iv[1]);
        else
            res.push_back(iv);
    }
    return res;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Insert Interval
**Difficulty:** Medium | **LC:** 57

```cpp
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> res;
    int i = 0, n = intervals.size();
    while (i < n && intervals[i][1] < newInterval[0]) res.push_back(intervals[i++]);
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    res.push_back(newInterval);
    while (i < n) res.push_back(intervals[i++]);
    return res;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Minimum Number of Arrows to Burst Balloons
**Difficulty:** Medium | **LC:** 452

**Approach:** Sort by end. Arrow at current_end bursts all balloons containing that point.

```cpp
int findMinArrowShots(vector<vector<int>>& points) {
    sort(points.begin(), points.end(), [](auto& a, auto& b) { return a[1] < b[1]; });
    int arrows = 1, arrowPos = points[0][1];
    for (int i = 1; i < (int)points.size(); i++) {
        if (points[i][0] > arrowPos) { arrows++; arrowPos = points[i][1]; }
    }
    return arrows;
}
// Time: O(n log n) | Space: O(1)
// This is exactly: max non-overlapping intervals (each group = one arrow)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Minimum Interval to Include Each Query
**Difficulty:** Hard | **LC:** 1851

**Approach:** Sort intervals by size. Sort queries. Process intervals in size order, using min-heap.

```cpp
vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return (a[1]-a[0]) < (b[1]-b[0]); // sort by size
    });
    
    int n = queries.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int a, int b) { return queries[a] < queries[b]; });
    
    // For each query (sorted), add all intervals containing the query point
    // min-heap: {size, end}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minH;
    int i = 0;
    vector<int> res(n, -1);
    
    for (int qi : idx) {
        int q = queries[qi];
        // Add all intervals starting ≤ q
        while (i < (int)intervals.size() && intervals[i][0] <= q) {
            if (intervals[i][1] >= q) // also contains q
                minH.push({intervals[i][1]-intervals[i][0]+1, intervals[i][1]});
            i++;
        }
        // Remove intervals ending before q
        while (!minH.empty() && minH.top().second < q) minH.pop();
        if (!minH.empty()) res[qi] = minH.top().first;
    }
    return res;
}
// Time: O((n+q) log n) | Space: O(n+q)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Video Stitching
**Difficulty:** Medium | **LC:** 1024

**Approach:** Greedy on intervals. Sort by start. At each step, among all clips that start ≤ current_end, pick the one that extends furthest.

```cpp
int videoStitching(vector<vector<int>>& clips, int time) {
    sort(clips.begin(), clips.end());
    int count = 0, curEnd = 0, farthest = 0;
    int i = 0, n = clips.size();
    
    while (curEnd < time) {
        while (i < n && clips[i][0] <= curEnd)
            farthest = max(farthest, clips[i++][1]);
        if (farthest == curEnd) return -1; // can't extend
        count++;
        curEnd = farthest;
    }
    return count;
}
// Time: O(n log n) | Space: O(1)
// Pattern: "jump game" on intervals
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** "Remove minimum intervals so no two overlap." Sort by what? Greedy rule?
<details><summary>Reveal</summary>
Sort by END time. Greedily keep intervals with earliest end that don't overlap the previous kept interval. Min removed = total - max kept.
</details>

**Drill 2:** "Merge all overlapping intervals." Sort by what? When to merge?
<details><summary>Reveal</summary>
Sort by START time. Merge when `intervals[i][0] <= result.back()[1]`. New end = `max(result.back()[1], intervals[i][1])`. Using `max` is crucial — the new interval might be contained within the current merged interval.
</details>

**Drill 3:** Why is sorting by end time (not start or length) optimal for activity selection?
<details><summary>Reveal</summary>
Exchange argument: suppose OPT selects interval X but our greedy selects Y (which ends earlier or at same time). Replace X with Y in OPT — it still works (Y ends ≤ X.end, so anything after X is also after Y). Repeat → greedy solution matches OPT in size.
</details>

**Drill 4:** Insert interval [2,5] into [(1,3),(6,9)]. Trace the algorithm.
<details><summary>Reveal</summary>
Step 1: intervals ending before 2: none (1,3).end=3 ≥ 2, so no interval qualifies. Step 2: merge overlapping: (1,3).start=1 ≤ 5 → merge: [min(2,1), max(5,3)]=[1,5]. Next: (6,9).start=6 > 5 → stop merging. Push [1,5]. Step 3: remaining: push (6,9). Result: [[1,5],[6,9]].
</details>

**Drill 5:** Video Stitching vs Jump Game II — same pattern?
<details><summary>Reveal</summary>
Yes. Jump Game II: position = current point, jump range = interval. Video Stitching: current covered range = curEnd, clips = intervals. Both use "greedy: from current reach, pick the clip/jump that extends farthest." Both are O(n log n) sort + O(n) greedy.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Approach | Time | Space |
|---------|----------|------|-------|
| Max non-overlapping | Sort end + greedy | O(n log n) | O(1) |
| Merge intervals | Sort start + scan | O(n log n) | O(n) |
| Insert interval | Linear scan | O(n) | O(n) |
| Min arrows | Sort end + greedy | O(n log n) | O(1) |
| Min meeting rooms | Two sorted arrays | O(n log n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: What if intervals have weights (weighted activity selection)?**
A: DP, not greedy. Sort by end. `dp[i] = max(dp[i-1], w[i] + dp[last non-overlapping])`. Binary search to find last non-overlapping: O(n log n) total.

**Q: Prove that sorting by end time is optimal?**
A: By exchange argument: any optimal solution can be transformed into the greedy solution without reducing the count, by repeatedly swapping the earliest-non-greedy choice with the greedy choice.

**Q: What if you need minimum intervals to cover [0, T]?**
A: Interval cover / video stitching variant. Greedy: among all intervals starting ≤ current, pick the one extending farthest. O(n log n).

---

## 10. Cross-Pattern Connections

- **P45 (Task Scheduling):** Meeting rooms uses the same interval sort; task scheduler uses different greedy
- **P35 (Interval DP):** When the problem asks for optimal value on intervals (not counting) → DP
- **P59 (Binary Search):** Insert interval uses binary search to find position
- **P19 (BFS):** Interval cover as "jump game" on continuous space
- **P54 (Jump Game):** Video Stitching is the interval version of Jump Game II
