# P45 — Task Scheduling / Meeting Rooms

## 1. First-Timer Explanation

### What Is It?
The **task scheduling** pattern uses heaps (and sometimes greedy ordering) to solve problems involving:
1. **Meeting rooms:** How many rooms needed? When do intervals overlap?
2. **Task scheduler:** Minimize time to complete all tasks with cooldown constraints
3. **CPU scheduling:** Assign tasks to minimize idle time or makespan

### Analogy — Meeting Rooms
Imagine a building with conference rooms. Meetings have start/end times. To find the minimum rooms needed: sort by start time. Use a min-heap of end times (when does the earliest-ending current meeting finish?). If a new meeting starts after the earliest end, reuse that room; otherwise, open a new room.

### Visual Walkthrough — Meeting Rooms II
```
Intervals: [(0,30),(5,10),(15,20)]
Sort by start: [(0,30),(5,10),(15,20)]

Heap (end times): []

Meeting (0,30): heap empty, open room → heap: [30]
Meeting (5,10): 5 < 30 (heap top), can't reuse → open new room → heap: [10, 30]
Meeting (15,20): 15 >= 10 (heap top), reuse! pop 10, push 20 → heap: [20, 30]

Max heap size = 2 rooms needed ✓
```

### Visual Walkthrough — Task Scheduler
```
tasks = [A,A,A,B,B,B], n=2

Count: A=3, B=3
Max frequency = 3 (both A and B)

Frame: cooldown slots form "frames" of size n+1
[A _ _ | A _ _ | A _ _]
Fill other tasks: [A B _ | A B _ | A B _]
Still idle: [A B _ | A B _ | A B]

Formula: max(tasks.size(), (maxFreq - 1) * (n + 1) + count_of_max_freq_tasks)
= max(6, (3-1) * 3 + 2) = max(6, 8) = 8
```

### When to Use
- "Minimum rooms/resources needed for overlapping intervals"
- "Task scheduler with cooldown"
- "Schedule tasks to minimize completion time"

### When NOT to Use
- Non-overlapping intervals → simpler greedy (activity selection)
- No cooldown constraint → just process in any order

### Common Mistakes
1. Sorting by end time instead of start time for meeting rooms
2. Min-heap vs max-heap confusion
3. Task scheduler: forgetting the `tasks.size()` lower bound
4. Not handling the case where cooldown is 0

---

## 2. Revision Card

**Recognition Signal:** "minimum rooms", "task scheduler", "cooldown", "CPU scheduling"

**Core Idea (Meeting Rooms):** Sort by start time. Min-heap of end times. If top ≤ new start → reuse (pop, push new end); else → open new room (just push new end).

**Core Idea (Task Scheduler):** `ans = max(total_tasks, (maxFreq - 1) * (n + 1) + count_of_max_freq)`

**Trigger Keywords:** meeting rooms, conference, cooldown, interval scheduling, tasks with constraint

**Complexity:**
| Problem | Time | Space |
|---------|------|-------|
| Meeting rooms I | O(n log n) | O(1) |
| Meeting rooms II | O(n log n) | O(n) |
| Task scheduler | O(n) or O(n log n) | O(1) |

---

## 3. Interview Tell Signs

- "Minimum number of [rooms/machines/CPUs]" → meeting rooms II pattern
- "Can all meetings happen?" → meeting rooms I (check if any overlap)
- "Tasks, cooldown n" → task scheduler formula or simulation
- "Minimum time to finish all tasks" → greedy + heap simulation

---

## 4. C++ Template

```cpp
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

// ── Meeting Rooms II ─────────────────────────────────────────────────────────
int minMeetingRooms(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end()); // sort by start time
    priority_queue<int, vector<int>, greater<int>> minH; // end times
    
    for (auto& iv : intervals) {
        if (!minH.empty() && minH.top() <= iv[0])
            minH.pop(); // reuse room
        minH.push(iv[1]); // assign room, record end time
    }
    return minH.size(); // rooms in use = rooms needed
}

// ── Task Scheduler (Formula) ─────────────────────────────────────────────────
int leastInterval(vector<char>& tasks, int n) {
    int cnt[26] = {};
    for (char c : tasks) cnt[c-'A']++;
    int maxFreq = *max_element(cnt, cnt+26);
    int numMax = count(cnt, cnt+26, maxFreq);
    return max((int)tasks.size(), (maxFreq - 1) * (n + 1) + numMax);
}
```

---

## 5. How to Present in Interview

**Verbal Script (Meeting Rooms II):**
> "I need the minimum number of simultaneous meetings at any point. I'll sort intervals by start time. I maintain a min-heap of end times. For each new meeting: if the earliest-ending active meeting ends by the new start, that room is free — reuse it. Otherwise, open a new room. The heap size at the end is the answer."

**Verbal Script (Task Scheduler):**
> "The key insight: the most frequent task determines the minimum time. Think of slots: the most frequent task A (say frequency 3, n=2) creates a skeleton: [A _ _ | A _ _ | A]. Other tasks fill the blanks. If enough tasks exist, no idle time. Otherwise, idle = (maxFreq - 1) * (n + 1) + count_of_max. Total time = max(tasks.size(), this formula)."

**Checklist:**
- [ ] Sort by start time (not end time) for meeting rooms
- [ ] Min-heap stores end times
- [ ] For task scheduler: mention the formula derivation
- [ ] Handle n=0 cooldown (formula still works)
- [ ] State complexity clearly

---

## 6. Problems

### Problem 1: Meeting Rooms (Can All Meetings Happen?)
**Difficulty:** Easy | **LC:** 252

**Approach:** Sort by start. Check if any interval's start < previous end.

```cpp
bool canAttendMeetings(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    for (int i = 1; i < (int)intervals.size(); i++)
        if (intervals[i][0] < intervals[i-1][1]) return false;
    return true;
}
// Time: O(n log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Meeting Rooms II (Minimum Rooms)
**Difficulty:** Medium | **LC:** 253

**Approach:** Sort by start. Min-heap of end times. Reuse if top ≤ start; else open new room.

```cpp
int minMeetingRooms(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    priority_queue<int, vector<int>, greater<int>> minH;
    
    for (auto& iv : intervals) {
        if (!minH.empty() && minH.top() <= iv[0]) minH.pop();
        minH.push(iv[1]);
    }
    return minH.size();
}
// Time: O(n log n) | Space: O(n)
// Alternative: two sorted arrays (starts, ends), two pointers
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Task Scheduler
**Difficulty:** Medium | **LC:** 621

**Approach:** Formula: max(tasks.size(), (maxFreq-1)*(n+1) + countOfMaxFreq).

```cpp
int leastInterval(vector<char>& tasks, int n) {
    int cnt[26] = {};
    for (char c : tasks) cnt[c-'A']++;
    int maxFreq = *max_element(cnt, cnt+26);
    int numMax = count(cnt, cnt+26, maxFreq);
    return max((int)tasks.size(), (maxFreq - 1) * (n + 1) + numMax);
}
// Time: O(n) | Space: O(1) — only 26 distinct tasks
// Edge: n=0 → answer = tasks.size()
```

**Simulation approach (if formula isn't obvious in interview):**
```cpp
int leastInterval(vector<char>& tasks, int n) {
    int cnt[26] = {};
    for (char c : tasks) cnt[c-'A']++;
    
    priority_queue<int> maxH(cnt, cnt+26); // max-heap of frequencies
    // Remove zeros in simulation if needed
    
    int time = 0;
    queue<pair<int,int>> cooldown; // {remaining_count, available_at_time}
    
    while (!maxH.empty() || !cooldown.empty()) {
        time++;
        if (!maxH.empty()) {
            int top = maxH.top() - 1; maxH.pop();
            if (top > 0) cooldown.push({top, time + n});
        }
        if (!cooldown.empty() && cooldown.front().second == time) {
            maxH.push(cooldown.front().first); cooldown.pop();
        }
    }
    return time;
}
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Reorganize String
**Difficulty:** Medium | **LC:** 767

**Approach:** Task scheduler with n=1 (adjacent chars different). Use same greedy: max-heap + cooldown of 1.

```cpp
string reorganizeString(string s) {
    int cnt[26] = {};
    for (char c : s) cnt[c-'a']++;
    
    priority_queue<pair<int,char>> maxH;
    for (int i = 0; i < 26; i++)
        if (cnt[i]) maxH.push({cnt[i], 'a'+i});
    
    string res;
    while (maxH.size() >= 2) {
        auto [f1, c1] = maxH.top(); maxH.pop();
        auto [f2, c2] = maxH.top(); maxH.pop();
        res += c1; res += c2;
        if (f1 > 1) maxH.push({f1-1, c1});
        if (f2 > 1) maxH.push({f2-1, c2});
    }
    if (!maxH.empty()) {
        if (maxH.top().first > 1) return "";
        res += maxH.top().second;
    }
    return res;
}
// Time: O(n log n) | Space: O(1) — 26 chars
// If max_freq > (n+1)/2 → impossible
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Minimum Number of Arrows to Burst Balloons
**Difficulty:** Medium | **LC:** 452

**Approach:** Greedy (not strictly heap). Sort by end. Arrow at current end bursts all overlapping balloons.

```cpp
int findMinArrowShots(vector<vector<int>>& points) {
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a[1] < b[1]; // sort by end
    });
    int arrows = 1;
    int arrowPos = points[0][1];
    for (int i = 1; i < (int)points.size(); i++) {
        if (points[i][0] > arrowPos) { // balloon starts after arrow
            arrows++;
            arrowPos = points[i][1];
        }
    }
    return arrows;
}
// Time: O(n log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Car Pooling
**Difficulty:** Medium | **LC:** 1094

**Approach:** Sort trips by start. Min-heap of (end_location, passengers). Unload passengers who've reached destination before picking up new ones.

```cpp
bool carPooling(vector<vector<int>>& trips, int capacity) {
    sort(trips.begin(), trips.end()); // sort by start
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> minH; // {end, passengers}
    int cur = 0;
    
    for (auto& t : trips) {
        int pass = t[0], start = t[1], end = t[2];
        // unload passengers who've arrived
        while (!minH.empty() && minH.top().first <= start) {
            cur -= minH.top().second; minH.pop();
        }
        cur += pass;
        if (cur > capacity) return false;
        minH.push({end, pass});
    }
    return true;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Given start/end times of meetings, find minimum rooms. What's the heap type and what does it store?
<details><summary>Reveal</summary>
Min-heap storing end times. Min-heap because we want to know if the EARLIEST-ending meeting is done. If heap.top() ≤ new_start, reuse (pop + push new_end). Else open new room (just push).
</details>

**Drill 2:** Task Scheduler: tasks=[A,A,A,B,B,C], n=2. Apply the formula.
<details><summary>Reveal</summary>
maxFreq=3 (A), numMax=1 (only A has freq 3). Formula: max(6, (3-1)*3 + 1) = max(6, 7) = 7. Answer: 7.
</details>

**Drill 3:** In the two-pointer alternative for meeting rooms, what are the two sorted arrays and what do the pointers track?
<details><summary>Reveal</summary>
starts[] sorted and ends[] sorted. Pointer s walks starts, pointer e walks ends. If starts[s] < ends[e]: new meeting starts before earliest ends → rooms++, s++. Else: meeting ended, e++. Answer = max rooms seen.
</details>

**Drill 4:** Why does the task scheduler formula give max(tasks.size(), formula)?
<details><summary>Reveal</summary>
tasks.size() is the lower bound (you must execute every task). The formula is the lower bound from the cooldown constraint. We need to satisfy both, so we take the max.
</details>

**Drill 5:** You have balloons represented as intervals. One arrow at position x bursts all balloons whose range contains x. Why sort by end time (not start)?
<details><summary>Reveal</summary>
Sorting by end lets us shoot at the earliest-ending balloon's right edge, maximizing the chance of hitting overlapping balloons. This greedy choice is optimal.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Approach | Time | Space |
|---------|----------|------|-------|
| Meeting Rooms I | Sort | O(n log n) | O(1) |
| Meeting Rooms II | Sort + min-heap | O(n log n) | O(n) |
| Meeting Rooms II | Two-pointer | O(n log n) | O(n) |
| Task Scheduler | Formula | O(n) | O(1) |
| Task Scheduler | Simulation | O(n log n) | O(n) |
| Car Pooling | Sort + min-heap | O(n log n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: Meeting rooms without a heap?**
A: Two sorted arrays (starts, ends) + two pointers. Same O(n log n) time, O(n) space for copies.

**Q: What if tasks have dependencies (one task must finish before another)?**
A: Topological sort (P21) + scheduling. This becomes more complex (critical path problem).

**Q: Task scheduler but maximize throughput instead of minimize time?**
A: Different formulation. Often solved with flow algorithms or specific scheduling theory.

**Q: What if meeting rooms have different capacities?**
A: Greedy still works but need to match meetings to rooms — becomes assignment problem.

---

## 10. Cross-Pattern Connections

- **P42 (Top-K):** Heap mechanics are identical; different invariant
- **P43 (Two Heaps):** Two heaps for different halves; task scheduler uses one heap
- **P53 (Greedy / Interval Scheduling):** Activity selection is the 1-room version of meeting rooms
- **P21 (Topological Sort):** Task dependencies → topo sort before scheduling
- **P35 (Interval DP):** Interval problems; scheduling vs. optimization distinction
