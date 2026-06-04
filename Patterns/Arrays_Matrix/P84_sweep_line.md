# P84 — Sweep Line Algorithm

## 1. First-Timer Explanation

### What Is It?
**Sweep line** imagines a vertical line sweeping left to right across a plane. At each event point (start or end of an interval/rectangle), we process changes to the active set. Key applications: counting overlapping intervals, computing rectangle union area, and finding closest pair of points.

### Visual Walkthrough — Counting Overlaps
```
Intervals: [1,4], [2,6], [5,8]

Events sorted by x:
x=1: +1 (start of [1,4])
x=2: +1 (start of [2,6])
x=4: -1 (end of [1,4])
x=5: +1 (start of [5,8])
x=6: -1 (end of [2,6])
x=8: -1 (end of [5,8])

Running count: 0→1→2→1→2→1→0
Max overlap = 2 ✓
```

### Rectangle Union Area
```
For each horizontal segment (bottom/top of rectangle):
  Events: (x, y1, y2, +1/-1) sorted by x
  Use segment tree on y-axis to track covered length
  Union area += covered_length × (next_x - current_x)
```

### When to Use
- "Maximum number of overlapping intervals" → events + sort + running count
- "Meeting rooms II" (min rooms) → same as max overlap count
- "Employee free time" → merge overlapping intervals across employees
- "Rectangle union area" → sweep line + segment tree on y-axis
- "Skyline problem" → sweep line with sorted events

### Common Mistakes
1. End events vs open/closed intervals: if intervals are half-open [s,e), end event at e; if closed [s,e], end at e+1 (or sort ends before starts at same coordinate)
2. Ties at same x: process ends BEFORE starts (for "strictly overlapping" count)
3. Skyline: process right edges before left edges at same x to avoid spurious heights

---

## 2. Revision Card

**Recognition Signal:** "max overlap", "meeting rooms", "sky line", "rectangle area union"

**Core Idea:** Convert interval start/end to events. Sort events by x-coordinate. Process events left-to-right, maintaining an "active set" or counter.

**Trigger Keywords:** sweep, overlap, events, skyline, union area, meeting rooms

**Complexity:** O(n log n) for sorting events; query depends on data structure used

---

## 3. Interview Tell Signs

- "Minimum meeting rooms needed" → max overlapping intervals at any time
- "Employee free time" → merge all intervals, find gaps
- "Skyline problem" → priority queue of active building heights
- "Rectangle union area" → sweep + segment tree
- "Event-based simulation" → sweep line with priority queue or sorted events
- "Number of airplanes in the sky" → classic sweep line overlap count

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

// ── Max Overlap (Meeting Rooms II) ────────────────────────────────────────────
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<pair<int,int>> events;
    for (auto& iv : intervals) {
        events.push_back({iv[0], 1});  // start
        events.push_back({iv[1], -1}); // end
    }
    sort(events.begin(), events.end()); // sort by time; -1 before +1 at same time (end before start)
    int cur = 0, maxRooms = 0;
    for (auto& [time, type] : events) { cur += type; maxRooms = max(maxRooms, cur); }
    return maxRooms;
}

// ── Skyline Problem ────────────────────────────────────────────────────────────
vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int,int>> events;
    for (auto& b : buildings) {
        events.push_back({b[0], -b[2]}); // left edge: negative height (process before right)
        events.push_back({b[1], b[2]});  // right edge: positive height
    }
    sort(events.begin(), events.end()); // sort by x; at same x, left before right (negative first)
    multiset<int> active{0}; // current heights; 0 = ground
    vector<vector<int>> res;
    int prevMax = 0;
    for (auto& [x, h] : events) {
        if (h < 0) active.insert(-h);   // entering a building
        else active.erase(active.find(h)); // leaving a building
        int curMax = *active.rbegin();
        if (curMax != prevMax) {
            res.push_back({x, curMax});
            prevMax = curMax;
        }
    }
    return res;
}

// ── Employee Free Time (merge intervals across multiple lists) ─────────────────
// Collect all intervals, sort, merge, find gaps between merged intervals
vector<pair<int,int>> employeeFreeTime(vector<vector<pair<int,int>>>& schedule) {
    vector<pair<int,int>> all;
    for (auto& emp : schedule) for (auto& iv : emp) all.push_back(iv);
    sort(all.begin(), all.end());
    // Merge
    vector<pair<int,int>> merged;
    for (auto& iv : all) {
        if (!merged.empty() && iv.first <= merged.back().second)
            merged.back().second = max(merged.back().second, iv.second);
        else merged.push_back(iv);
    }
    // Gaps between merged intervals = free time
    vector<pair<int,int>> free;
    for (int i = 1; i < (int)merged.size(); i++)
        free.push_back({merged[i-1].second, merged[i].first});
    return free;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Meeting Rooms II):**
> "Generate two events per interval: start (+1) and end (-1). Sort events by time, breaking ties by processing ends before starts. Sweep through events, maintaining a running count of active meetings. Track the maximum — that's the minimum rooms needed."

**Verbal Script (Skyline):**
> "Events: for each building, one event at the left edge (negative height, processed first) and one at the right edge. Sort events. Maintain a multiset of active heights including 0 (ground). After each event, if the maximum active height changes, record a critical point. Using a multiset allows O(log n) insert/erase and O(1) max."

**Checklist:**
- [ ] Events sorted correctly: same x, ends (-1) before starts (+1)
- [ ] Skyline: use negative heights for left edges to sort before right at same x
- [ ] Skyline: use `multiset` not `set` (multiple buildings same height)
- [ ] Skyline: always include 0 in the active set (ground level)
- [ ] Record result ONLY when max height changes

---

## 6. Problems

### Problem 1: Meeting Rooms II
**Difficulty:** Medium | **LC:** 253

```cpp
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<int> starts, ends;
    for (auto& iv:intervals) { starts.push_back(iv[0]); ends.push_back(iv[1]); }
    sort(starts.begin(),starts.end()); sort(ends.begin(),ends.end());
    int rooms=0, ei=0;
    for (int si=0;si<(int)starts.size();si++) {
        if (starts[si]<ends[ei]) rooms++; else ei++;
    }
    return rooms;
}
// Time: O(n log n) | Space: O(n)
// Two-pointer approach: no event list needed
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: The Skyline Problem
**Difficulty:** Hard | **LC:** 218

```cpp
vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int,int>> events;
    for (auto& b:buildings) {
        events.push_back({b[0],-b[2]});
        events.push_back({b[1],b[2]});
    }
    sort(events.begin(),events.end());
    multiset<int> active{0}; vector<vector<int>> res; int prev=0;
    for (auto& [x,h]:events) {
        if (h<0) active.insert(-h); else active.erase(active.find(h));
        int cur=*active.rbegin();
        if (cur!=prev) { res.push_back({x,cur}); prev=cur; }
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

### Problem 3: Number of Airplanes in the Sky
**Difficulty:** Medium | **LintCode:** 391

```cpp
int countOfAirplanes(vector<pair<int,int>>& airplanes) {
    vector<pair<int,int>> events;
    for (auto& [s,e]:airplanes) {
        events.push_back({s,1});
        events.push_back({e,-1}); // half-open [s,e): plane leaves at e
    }
    sort(events.begin(),events.end(),[](auto& a,auto& b){
        return a.first<b.first || (a.first==b.first && a.second<b.second); // end before start
    });
    int cur=0,res=0;
    for (auto& [t,d]:events) { cur+=d; res=max(res,cur); }
    return res;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: My Calendar III (Max Simultaneous Events)
**Difficulty:** Hard | **LC:** 732

```cpp
class MyCalendarThree {
    map<int,int> diff;
public:
    int book(int start, int end) {
        diff[start]++; diff[end]--;
        int cur=0, res=0;
        for (auto& [_,d]:diff) { cur+=d; res=max(res,cur); }
        return res;
    }
};
// Time: O(n log n) per book call | Space: O(n)
// Lazy: maintain running max during map updates (not recomputed from scratch)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Rectangle Area II (Union of Rectangles)
**Difficulty:** Hard | **LC:** 850

**Approach:** Coordinate compress y-axis. Sweep x events. Track covered y-length.

```cpp
int rectangleArea(vector<vector<int>>& rectangles) {
    const int MOD = 1e9 + 7;
    set<int> ys_set;
    for (auto& r:rectangles) { ys_set.insert(r[1]); ys_set.insert(r[3]); }
    vector<int> ys(ys_set.begin(),ys_set.end());
    int yN=ys.size();
    // Events: (x, y1, y2, +1/-1)
    vector<tuple<int,int,int,int>> events;
    for (auto& r:rectangles) {
        events.push_back({r[0],r[1],r[3],1});
        events.push_back({r[2],r[1],r[3],-1});
    }
    sort(events.begin(),events.end());
    // For each x segment, track covered y length using brute-force on compressed y
    vector<int> cnt(yN,0);
    auto coveredLen=[&]()->long long{
        long long res=0; int i=0;
        while (i<yN-1) { if(cnt[i]>0) res+=ys[i+1]-ys[i]; i++; }
        return res;
    };
    long long res=0, prevX=0;
    for (int ei=0;ei<(int)events.size();) {
        auto [x,_y1,_y2,_d]=events[ei];
        res=(res+coveredLen()*(x-prevX))%MOD;
        prevX=x;
        while (ei<(int)events.size()&&get<0>(events[ei])==x) {
            auto [_x,y1,y2,d]=events[ei++];
            // Update cnt for all y segments in [y1,y2)
            for (int i=0;i<yN-1;i++) if(ys[i]>=y1&&ys[i+1]<=y2) cnt[i]+=d;
        }
    }
    return res;
}
// Time: O(n²) with coordinate compression | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Remove Interval
**Difficulty:** Medium | **LC:** 1272

```cpp
vector<vector<int>> removeInterval(vector<vector<int>>& intervals, vector<int>& toBeRemoved) {
    int rL=toBeRemoved[0], rR=toBeRemoved[1];
    vector<vector<int>> res;
    for (auto& iv:intervals) {
        if (iv[1]<=rL||iv[0]>=rR) { res.push_back(iv); } // no overlap
        else {
            if (iv[0]<rL) res.push_back({iv[0],rL});    // left part
            if (iv[1]>rR) res.push_back({rR,iv[1]});    // right part
        }
    }
    return res;
}
// Time: O(n) | Space: O(n) output
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Intervals [1,3],[2,4],[3,5]. Max overlap using events. Trace.
<details><summary>Reveal</summary>
Events: (1,+1),(2,+1),(3,-1),(3,+1),(4,-1),(5,-1). Sort: same x, -1 before +1: (1,+1),(2,+1),(3,-1),(3,+1),(4,-1),(5,-1). Running: 0→1→2→1→2→1→0. Max=2.
</details>

**Drill 2:** Skyline for buildings [[2,9,10],[3,7,15]]. List the events and trace active multiset.
<details><summary>Reveal</summary>
Events: (2,-10),(3,-15),(7,15),(9,10). Sort: (2,-10),(3,-15),(7,15),(9,10). active={0}. x=2,h=-10: insert 10. active={0,10}. curMax=10≠0 → add [2,10]. prev=10. x=3,h=-15: insert 15. active={0,10,15}. curMax=15≠10 → add [3,15]. prev=15. x=7,h=15: erase 15. active={0,10}. curMax=10≠15 → add [7,10]. prev=10. x=9,h=10: erase 10. active={0}. curMax=0≠10 → add [9,0]. Result: [[2,10],[3,15],[7,10],[9,0]] ✓.
</details>

**Drill 3:** MyCalendarThree: book(10,20), then book(15,25). What does diff look like and what is the max?
<details><summary>Reveal</summary>
After book(10,20): diff={10:1,20:-1}. Running sum: 1 (at 10), 0 (at 20). Max=1. After book(15,25): diff={10:1,15:1,20:-1,25:-1}. Running: 1,2,1,0. Max=2.
</details>

**Drill 4:** Why process end events BEFORE start events at the same timestamp?
<details><summary>Reveal</summary>
If intervals are half-open [s,e), then at time t=e, the interval has ended, and at t=s a new one starts. If a new interval starts exactly when another ends, they don't actually overlap. Processing end(-1) before start(+1) at same time ensures the count never incorrectly counts these as overlapping. If we processed +1 before -1, count would temporarily show overlap where there is none.
</details>

**Drill 5:** What does the skyline "ground" value 0 in the active multiset represent?
<details><summary>Reveal</summary>
It represents the ground level — before any building and after all buildings, the skyline height is 0. Without it, when all buildings are removed from active, `*active.rbegin()` would access an empty set (undefined behavior). The 0 also correctly generates a [x,0] critical point when the last building ends, indicating the skyline drops to ground.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Meeting rooms II (events) | O(n log n) | O(n) |
| Meeting rooms II (two arrays) | O(n log n) | O(n) |
| Skyline | O(n log n) | O(n) |
| MyCalendar III | O(n log n) per booking | O(n) |
| Rectangle union area | O(n²) | O(n) |
| Remove interval | O(n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: How to find all free time slots across employees?**
A: Collect all intervals, sort by start, merge overlapping ones, then the gaps between merged intervals are free time.

**Q: Why use a multiset instead of a max-heap for the skyline?**
A: A max-heap doesn't support O(log n) deletion of arbitrary elements. The multiset supports both O(log n) insert and O(log n) erase-by-value, while maintaining sorted order for O(1) maximum access via `rbegin()`.

**Q: Can the sweep line handle 2D objects efficiently?**
A: For rectangle union, the sweep line reduces it to 1D "covered length" queries. With a proper segment tree on the y-axis, the total complexity is O(n log n). The naive approach (update each y segment) is O(n²).

---

## 10. Cross-Pattern Connections

- **P53 (Interval Scheduling):** Same interval event model; greedy vs. sweep line approaches
- **P80 (Difference Arrays):** Difference array is a simplified sweep line for discrete positions
- **P45 (Task Scheduling):** Meeting rooms II is a special case of task scheduling
- **P97 (Segment Tree):** Segment tree with lazy propagation handles the y-axis in rectangle union
- **P64 (Monotonic Stack):** Skyline uses an ordered set analogously to monotonic stack
