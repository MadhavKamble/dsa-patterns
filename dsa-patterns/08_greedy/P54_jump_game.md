# P54 — Jump Game and Reach-Based Greedy

## 1. First-Timer Explanation

### What Is It?
The **jump game** pattern uses a greedy "maximum reach" approach: track how far you can currently reach, and update it as you scan. If your current position exceeds your reach, you're stuck. If you reach or pass the destination, you succeed.

### Visual Walkthrough — Jump Game I
```
nums = [2, 3, 1, 1, 4]
        0  1  2  3  4

Position 0: reach = max(0, 0+2) = 2
Position 1: reach = max(2, 1+3) = 4 ← can reach index 4
Position 2: 2 ≤ reach, continue; reach = max(4, 2+1) = 4
...
Never stuck. Return true ✓
```

### Visual Walkthrough — Jump Game II (Min Jumps)
```
nums = [2, 3, 1, 1, 4]
        0  1  2  3  4

Greedy BFS levels:
Level 0: can reach up to index 2 (from 0, jump 2)
Level 1: from [0..2], max reach = max(0+2, 1+3, 2+1) = 4 = end
jumps = 2 ✓
```

Think of it as BFS on implicit graph: each "level" = one jump. Expand the frontier greedily.

### When to Use
- "Can you reach the end?" (Jump Game I)
- "Minimum jumps to reach end" (Jump Game II)
- "Maximum reach / coverage"
- "Minimum number of [moves/steps] to cover [0,T]" — interval cover variant

### When NOT to Use
- Need to track which cells were visited → BFS/DFS
- Obstacles (blocked cells) → BFS
- Negative jump values → DP (can't greedy)

### Common Mistakes
1. Jump Game II: using `i <= curEnd` vs `i < curEnd` in loop
2. Not updating `curEnd = nextEnd` only at jump boundaries
3. Missing the edge case where starting position already reaches end

---

## 2. Revision Card

**Recognition Signal:** "can reach end", "minimum jumps", "maximum reach"

**Core Idea:** Scan left to right. Maintain `reach` (max index reachable). At each position i ≤ reach, update `reach = max(reach, i + nums[i])`. If reach ≥ n-1 → reachable.

**Trigger Keywords:** jump, reach, minimum steps, cover, extend

**Complexity:** O(n) time, O(1) space for all variants

---

## 3. Interview Tell Signs

- "Can you reach position N?" → track max reach greedily
- "Min jumps to reach end" → BFS-style greedy with jump count
- "Minimum intervals to cover [0,T]" → same reach idea on intervals
- "Maximum reach from each position" → O(n) reach array

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Jump Game I (can reach end?) ─────────────────────────────────────────────
bool canJump(vector<int>& nums) {
    int reach = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > reach) return false; // stuck
        reach = max(reach, i + nums[i]);
    }
    return true;
}

// ── Jump Game II (minimum jumps) ─────────────────────────────────────────────
int jump(vector<int>& nums) {
    int jumps = 0, curEnd = 0, nextEnd = 0;
    for (int i = 0; i < (int)nums.size() - 1; i++) {
        nextEnd = max(nextEnd, i + nums[i]);
        if (i == curEnd) { // end of current jump's reach → must jump
            jumps++;
            curEnd = nextEnd;
        }
    }
    return jumps;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Jump Game I):**
> "I'll track the maximum index I can reach. For each position up to `reach`, I update `reach = max(reach, i + nums[i])`. If at any position i I have i > reach, I'm stuck. If reach reaches the end, return true. O(n) time, O(1) space."

**Verbal Script (Jump Game II):**
> "This is like BFS. I maintain the current jump's boundary (`curEnd`) and the farthest I can reach within this jump (`nextEnd`). When I hit `curEnd`, I must jump — increment the count, update `curEnd = nextEnd`, and continue. This greedy always extends as far as possible in one jump."

**Checklist:**
- [ ] Start: reach = 0, jumps = 0
- [ ] Loop through all positions (for II: up to n-2, not n-1)
- [ ] Update reach/nextEnd at each position
- [ ] For II: increment jumps when i == curEnd
- [ ] Return reach >= n-1 (for I)

---

## 6. Problems

### Problem 1: Jump Game I
**Difficulty:** Medium | **LC:** 55

```cpp
bool canJump(vector<int>& nums) {
    int reach = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (i > reach) return false;
        reach = max(reach, i + nums[i]);
    }
    return true; // or: return reach >= (int)nums.size() - 1;
}
// Time: O(n) | Space: O(1)
// Edge: nums=[0] → already at end → true; nums=[0,1] → stuck at 0 → false
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Jump Game II (Minimum Jumps)
**Difficulty:** Medium | **LC:** 45

```cpp
int jump(vector<int>& nums) {
    int jumps = 0, curEnd = 0, nextEnd = 0;
    for (int i = 0; i < (int)nums.size() - 1; i++) {
        nextEnd = max(nextEnd, i + nums[i]);
        if (i == curEnd) { jumps++; curEnd = nextEnd; }
    }
    return jumps;
}
// Time: O(n) | Space: O(1)
// Note: loop to n-2 (not n-1): no need to jump from last position
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Jump Game III (Can Reach 0?)
**Difficulty:** Medium | **LC:** 1306

**Approach:** BFS from start. From index i, can jump to `i + arr[i]` or `i - arr[i]`. Find if any reachable index has value 0.

```cpp
bool canReach(vector<int>& arr, int start) {
    int n = arr.size();
    queue<int> q;
    vector<bool> visited(n, false);
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int i = q.front(); q.pop();
        if (arr[i] == 0) return true;
        for (int next : {i + arr[i], i - arr[i]}) {
            if (next >= 0 && next < n && !visited[next]) {
                visited[next] = true;
                q.push(next);
            }
        }
    }
    return false;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Jump Game VII (Reach End with Max/Min Jump Range)
**Difficulty:** Medium | **LC:** 1871

**Approach:** Sliding window of reachable positions. Track how many positions in [i-maxJump, i-minJump] are reachable.

```cpp
bool canReach(string s, int minJump, int maxJump) {
    int n = s.size();
    vector<bool> reachable(n, false);
    reachable[0] = true;
    int count = 0; // count of reachable positions in sliding window
    
    for (int i = 1; i < n; i++) {
        if (i >= minJump) count += reachable[i - minJump];
        if (i > maxJump) count -= reachable[i - maxJump - 1];
        if (s[i] == '0' && count > 0) reachable[i] = true;
    }
    return reachable[n-1];
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Gas Station
**Difficulty:** Medium | **LC:** 134

**Approach:** Greedy. If total gas ≥ total cost → solution exists. Find start: reset when tank goes negative.

```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total = 0, tank = 0, start = 0;
    for (int i = 0; i < (int)gas.size(); i++) {
        int net = gas[i] - cost[i];
        total += net;
        tank += net;
        if (tank < 0) { start = i + 1; tank = 0; } // reset start
    }
    return total >= 0 ? start : -1;
}
// Time: O(n) | Space: O(1)
// Key insight: if you can't reach i+1 from start, no point before i can do better
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Minimum Number of Taps to Open a Garden
**Difficulty:** Hard | **LC:** 1326

**Approach:** Convert to interval cover problem. Each tap i covers [i-ranges[i], i+ranges[i]]. Use greedy interval cover (same as Jump Game II on intervals).

```cpp
int minTaps(int n, vector<int>& ranges) {
    // Convert to "max reach from left endpoint"
    vector<int> maxReach(n + 1, 0);
    for (int i = 0; i <= n; i++) {
        int l = max(0, i - ranges[i]);
        int r = min(n, i + ranges[i]);
        maxReach[l] = max(maxReach[l], r);
    }
    
    // Jump Game II on the maxReach array
    int taps = 0, curEnd = 0, nextEnd = 0;
    for (int i = 0; i < n; i++) {
        nextEnd = max(nextEnd, maxReach[i]);
        if (i == curEnd) {
            if (nextEnd == curEnd) return -1; // can't extend
            taps++;
            curEnd = nextEnd;
        }
    }
    return taps;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** nums=[3,2,1,0,4]. Can you reach the end?
<details><summary>Reveal</summary>
reach=0. i=0: reach=max(0,3)=3. i=1: reach=max(3,3)=3. i=2: reach=max(3,3)=3. i=3: reach=max(3,3)=3. i=4: 4>3, stuck! Return false.
</details>

**Drill 2:** Jump Game II: why loop to `nums.size()-1` and not `nums.size()`?
<details><summary>Reveal</summary>
The last position (index n-1) is the destination. We never need to jump FROM it. If we include it, we'd incorrectly count an extra jump. The loop condition `i < n-1` ensures we stop before the last element.
</details>

**Drill 3:** Gas Station: why does "if total_gas >= total_cost, a solution exists"?
<details><summary>Reveal</summary>
If the total circuit has non-negative net gas, then by a circular argument, starting from the right point will work. The "reset start" greedy finds that starting point: whenever the running total goes negative, the current start is impossible, so try starting after the problematic station.
</details>

**Drill 4:** Minimum Taps: how does it reduce to Jump Game II?
<details><summary>Reveal</summary>
Each tap i covers [i-ranges[i], i+ranges[i]]. Map each interval to: "from left endpoint l, you can reach right endpoint r." Store maxReach[l] = max(maxReach[l], r). Then Jump Game II on this maxReach array gives minimum intervals (taps) to cover [0,n].
</details>

**Drill 5:** Jump Game I with DP approach: `dp[i] = can[i] = can[j] && j+nums[j] >= i for some j < i`. Why is greedy O(n) better?
<details><summary>Reveal</summary>
DP approach is O(n²): for each i, check all previous j. Greedy O(n): just track max reach seen so far. If i ≤ max_reach, it's reachable. The greedy subsumes all DP transitions in a single pass.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Jump Game I | O(n) | O(1) |
| Jump Game II | O(n) | O(1) |
| Jump Game III | O(n) BFS | O(n) |
| Gas Station | O(n) | O(1) |
| Min Taps | O(n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: What if jump values can be negative?**
A: Greedy breaks. Use DP. `dp[i] = min/max over reachable predecessors`.

**Q: Jump Game with obstacles (some cells blocked)?**
A: BFS. Greedy can't handle blocking.

**Q: Can you find the actual path (which cells to land on)?**
A: Track parent array alongside the greedy. For each `jump` boundary update, record which positions were in the previous frontier.

**Q: What if you can jump backwards too?**
A: BFS (bidirectional). Greedy fails because going backward could enable better forward paths.

---

## 10. Cross-Pattern Connections

- **P53 (Interval Scheduling):** Video Stitching and Min Taps are interval versions of Jump Game II
- **P19 (BFS):** Jump Game III uses BFS; conceptually Jump Game II is "greedy BFS"
- **P30 (1D DP):** Jump Game with obstacles or negative jumps → DP
- **P08 (Sliding Window):** Jump Game VII uses sliding window for efficient reach counting
