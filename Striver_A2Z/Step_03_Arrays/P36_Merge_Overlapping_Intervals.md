# 🔥 Merge Overlapping Intervals

> **LeetCode #56** · **Difficulty:** Medium · **Step 3 — Arrays · P36**

---

## 🧠 Problem Understanding

Given a list of intervals, merge all overlapping intervals.

**Input:** `[[1,3],[2,6],[8,10],[15,18]]` → **Output:** `[[1,6],[8,10],[15,18]]`

**Key Observation:** After sorting by start time, two intervals overlap iff `current.start <= prev.end`.

---

## 🥇 Optimal — Sort + Merge

### Algorithm
1. Sort intervals by start time
2. Initialize result with first interval
3. For each subsequent interval:
   - If `current.start <= result.back().end`: merge (extend end)
   - Else: add new interval to result

### Dry Run
Sorted: `[[1,3],[2,6],[8,10],[15,18]]`

| Interval | result.back | Overlap? | Action |
|----------|-------------|----------|--------|
| [1,3] | — | — | Add to result |
| [2,6] | [1,3] | 2≤3 ✅ | Merge → [1,max(3,6)]=[1,6] |
| [8,10] | [1,6] | 8≤6 ❌ | Add new |
| [15,18] | [8,10] | 15≤10 ❌ | Add new |

**Output:** `[[1,6],[8,10],[15,18]]` ✅

### Complexity
- **Time:** O(N log N) (sort) · **Space:** O(N) output

```cpp
/*
 * MERGE OVERLAPPING INTERVALS
 * Sort by start, then greedily merge when overlap detected
 * Overlap: current.start <= last merged end
 * Time O(N log N) | Space O(N)
 */
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());    // sort by start time

        vector<vector<int>> result;
        result.push_back(intervals[0]);

        for (int i = 1; i < intervals.size(); i++) {
            auto& last = result.back();
            if (intervals[i][0] <= last[1]) {
                last[1] = max(last[1], intervals[i][1]);  // extend end
            } else {
                result.push_back(intervals[i]);            // no overlap, add
            }
        }
        return result;
    }
};
```

---

## 🧾 Recall Line
> "Sort by start. If `curr.start <= last.end`, merge by `last.end = max(last.end, curr.end)`."

## 📝 Short Revision Notes
- Sort by start is mandatory
- Merge condition: `curr[0] <= result.back()[1]`
- Merge: update `result.back()[1] = max(result.back()[1], curr[1])` (don't assume curr[1] > last[1])
- Covers fully contained intervals: [1,10],[2,5] → [1,10]

## ⚠️ Common Mistakes
❌ Not sorting first — overlapping check only works on sorted intervals  
❌ `result.back()[1] = curr[1]` instead of `max(...)` — misses fully contained intervals

## 🔥 What Interviewer Is Testing
- Interval greedy pattern
- Sorting as a preprocessing step

## 📚 Related Problems
- [ ] LeetCode #56 — Merge Intervals
- [ ] LeetCode #57 — Insert Interval
- [ ] LeetCode #435 — Non-overlapping Intervals (greedy)
- [ ] LeetCode #452 — Minimum Arrows to Burst Balloons

## 🏆 Pattern Category
`Arrays` · `Intervals` · `Sorting` · `Greedy`

## ⏱️ 30-Second Revision
> Sort by start. Push first. For each: if `curr[0] <= last[1]`, merge `last[1]=max(last[1],curr[1])`. Else push new. O(N log N)/O(N).
