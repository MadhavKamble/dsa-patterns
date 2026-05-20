# Pattern 29: Bidirectional BFS

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 127. Word Ladder | Hard | https://leetcode.com/problems/word-ladder/ |
| 2 | 126. Word Ladder II | Hard | https://leetcode.com/problems/word-ladder-ii/ |
| 3 | 752. Open the Lock | Medium | https://leetcode.com/problems/open-the-lock/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Bidirectional BFS** runs two simultaneous BFS searches — one forward from the source and one backward from the target — and terminates when the two frontiers meet.

**Why it's faster:**
- Standard BFS: explores a "sphere" of radius d from source. Nodes explored ≈ b^d (branching factor b, depth d)
- Bidirectional: each side explores radius d/2. Total ≈ 2 × b^(d/2) — exponentially fewer nodes

**The algorithm:**
1. Maintain two frontier sets: `frontA` (from source) and `frontB` (from target)
2. Two visited sets: `visitedA` and `visitedB`
3. At each step: expand the SMALLER frontier (keeps work balanced)
4. For each node expanded from frontA: if it's in visitedB → path found!
5. Steps taken = `stepsA + stepsB`

### Visual Walkthrough
```
Word Ladder: "hit" → "cog"
Branching factor ≈ 26×3 = 78 words per level

Standard BFS (depth 5): 78^5 ≈ 28 billion nodes
Bidirectional BFS (depth 2.5 each): 2 × 78^2.5 ≈ 85,000 nodes — ~300,000x faster

Execution:
  frontA = {"hit"}, frontB = {"cog"}
  Step 1: expand frontA → {"hot", "hit-variants..."}
  Step 1: expand frontB → {"dog", "log", "cog-variants..."}
  Step 2: expand frontA → {"dot", "dog", ...} — "dog" in visitedB? → YES → found!
  Distance = 2 + 1 = 3? Actually track steps more carefully.
```

### When TO use this pattern
- Source AND destination both known
- BFS search space is very large (word ladder, social network degrees)
- Symmetric graph (can search backward from target)
- When standard BFS is too slow (TLE)

### When NOT to use this pattern
- Target unknown (can't start backward BFS)
- Directed graph where backward BFS doesn't make sense
- Graph is very sparse (regular BFS already fast)
- Need actual paths (not just distance) — bidirectional path reconstruction is complex

### Common Beginner Mistakes
- **Always expand smaller frontier**: skip this optimization and the algorithm may not be faster
- **Check intersection when EXPANDING, not just inserting**: check if newly generated neighbors are in the other frontier
- **Steps tracking**: total distance = steps from A to meeting point + steps from B to meeting point
- **Word Ladder**: bidirectional BFS reduces the large branching factor significantly

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | Large BFS search space, both source and target known, symmetric graph |
| Core Idea | Expand from both ends; meet in the middle. Total work ≈ 2b^(d/2) vs b^d |
| Trigger Keywords | "shortest path" + large state space + both endpoints known |
| Avoid When | Target unknown, directed (backward not defined), small graph |
| Time Complexity | O(b^(d/2)) instead of O(b^d) — exponential improvement |
| Space Complexity | O(b^(d/2)) per side |

**Gotchas:**
- Expand the SMALLER frontier each step
- When a neighbor is in the OTHER visited set → path found, return accumulated distance
- Don't forget to mark new nodes as visited when adding to frontier (not when popping)

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"word ladder"` + large dictionary → bidirectional BFS for optimization
- `"6 degrees of separation"` → bidirectional BFS on social graph
- `"open the lock"` → can apply bidirectional BFS
- Interviewer asks to optimize a TLE-ing standard BFS → bidirectional BFS

---

## 4. C++ Template

```cpp
/*
 * Pattern: Bidirectional BFS
 * Time: O(b^(d/2)) | Space: O(b^(d/2))
 */

int bidirectionalBFS(string src, string dst, unordered_set<string>& wordSet) {
    if (src == dst) return 1;
    unordered_set<string> frontA = {src}, frontB = {dst};
    unordered_set<string> visitedA = {src}, visitedB = {dst};
    int steps = 1;

    while (!frontA.empty() && !frontB.empty()) {
        steps++;
        // always expand smaller frontier
        if (frontA.size() > frontB.size()) {
            swap(frontA, frontB);
            swap(visitedA, visitedB);
        }

        unordered_set<string> nextFront;
        for (string word : frontA) {
            for (int i = 0; i < (int)word.size(); i++) {
                char orig = word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    if (c == orig) continue;
                    word[i] = c;
                    if (frontB.count(word)) return steps;  // frontiers meet!
                    if (wordSet.count(word) && !visitedA.count(word)) {
                        visitedA.insert(word);
                        nextFront.insert(word);
                    }
                    word[i] = orig;
                }
            }
        }
        frontA = nextFront;
    }
    return 0;  // no path
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Standard BFS from source would explore O(b^d) nodes where b is the branching factor and d is the depth. With bidirectional BFS, I simultaneously search from both source and target, expanding the smaller frontier each time. The two searches meet in the middle, so each explores only b^(d/2) nodes — exponentially fewer. This is critical for Word Ladder where the branching factor is large."

### Interview Flow Checklist
- [ ] Initialize two frontier sets (source side and target side)
- [ ] Initialize two visited sets
- [ ] Loop: expand smaller frontier
- [ ] For each new neighbor: if in OTHER frontier → found, return steps
- [ ] Add to current frontier's visited; add to next frontier
- [ ] Return 0 if frontiers empty (no path)

---

## 6. Problems

---

### Problem 1: 127. Word Ladder (Bidirectional)
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/word-ladder/
**Why this pattern fits:** Large branching factor (26 substitutions × word length); bidirectional exponentially reduces search

**Optimal C++ Solution:**
```cpp
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord)) return 0;

    unordered_set<string> frontA = {beginWord}, frontB = {endWord};
    int steps = 1;

    while (!frontA.empty() && !frontB.empty()) {
        steps++;
        if (frontA.size() > frontB.size()) swap(frontA, frontB);
        unordered_set<string> next;
        for (string word : frontA) {
            wordSet.erase(word);  // remove visited from wordSet directly
            for (int i = 0; i < (int)word.size(); i++) {
                char orig = word[i];
                for (char c = 'a'; c <= 'z'; c++) {
                    word[i] = c;
                    if (frontB.count(word)) return steps;
                    if (wordSet.count(word)) { next.insert(word); wordSet.erase(word); }
                    word[i] = orig;
                }
            }
        }
        frontA = next;
    }
    return 0;
}
```
**Complexity Analysis:**
- Time: O(M² × N / 2) — M = word length, N = dict size. Bidirectional halves the depth
- Space: O(M × N)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 752. Open the Lock (Bidirectional)
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/open-the-lock/
**Why this pattern fits:** State space is 10^4 = 10,000 combinations; bidirectional BFS meets in middle

**Optimal C++ Solution:**
```cpp
int openLock(vector<string>& deadends, string target) {
    unordered_set<string> dead(deadends.begin(), deadends.end());
    if (dead.count("0000") || dead.count(target)) return -1;
    if (target == "0000") return 0;

    unordered_set<string> frontA = {"0000"}, frontB = {target};
    unordered_set<string> visitedA = {"0000"}, visitedB = {target};
    int steps = 0;

    while (!frontA.empty() && !frontB.empty()) {
        steps++;
        if (frontA.size() > frontB.size()) {
            swap(frontA, frontB); swap(visitedA, visitedB);
        }
        unordered_set<string> next;
        for (const string& cur : frontA) {
            for (int i = 0; i < 4; i++) {
                for (int d : {1, -1}) {
                    string nxt = cur;
                    nxt[i] = (nxt[i] - '0' + d + 10) % 10 + '0';
                    if (frontB.count(nxt)) return steps;
                    if (!dead.count(nxt) && !visitedA.count(nxt)) {
                        visitedA.insert(nxt);
                        next.insert(nxt);
                    }
                }
            }
        }
        frontA = next;
    }
    return -1;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find the minimum number of moves to go from position A to position B on a chessboard for a knight. Board is very large (10^9 × 10^9).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bidirectional BFS
**Reason:** Standard BFS from A would explore 8^d states. Bidirectional BFS meets in middle: 2 × 8^(d/2). For large boards where d might be large, this is crucial. State = (row, col); neighbors = 8 knight moves.
</details>

---

**Drill 2:**
> Given a social network with millions of users, find the shortest connection chain between two specific users (degrees of separation).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bidirectional BFS
**Reason:** Starting from one user, the BFS frontier grows as (avg_friends)^depth. With branching factor 100 and depth 6, that's 100^6 = 10^12 nodes. Bidirectional: 2 × 100^3 = 2 million — completely feasible. This is how LinkedIn "2nd degree connections" works.
</details>

---

**Drill 3:**
> In a 15-puzzle (4×4 sliding tile puzzle), find the minimum number of moves to reach the solved state from a given starting configuration.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bidirectional BFS + A* (meet in the middle)
**Reason:** The state space is 16!/2 ≈ 10^13 possible configurations. Standard BFS would be infeasible. Bidirectional BFS from start and goal, or A* with Manhattan distance heuristic, are the standard approaches. Bidirectional BFS cuts the effective depth in half.
</details>

---

**Drill 4:**
> Find the shortest path between two nodes in a large undirected graph where nodes represent web pages and edges represent links.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bidirectional BFS
**Reason:** The web graph has very high average branching factor. Standard BFS from source would be enormous. Since both source and target pages are known, bidirectional BFS from both ends dramatically reduces the frontier size. This is how Google's "Six Degrees of Wikipedia" works.
</details>

---

**Drill 5:**
> Given two protein structures, find the minimum number of amino acid swaps to transform one into the other, where only biologically valid swaps are allowed.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bidirectional BFS on state space
**Reason:** State = current protein configuration. Edges = valid swaps. If the state space is large but both start and end states are known, bidirectional BFS from both reduces the search dramatically. The valid swap rules define the neighbors function.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Standard BFS | Bidirectional BFS | Improvement |
|---------|-------------|-------------------|-------------|
| Word Ladder (b=78, d=5) | 78^5 ≈ 28B | 2×78^2.5 ≈ 85K | ~330,000x |
| Social network (b=100, d=6) | 100^6 = 10^12 | 2×100^3 = 2M | ~500,000x |
| Open Lock (b=8, d≈10) | 8^10 ≈ 1B | 2×8^5 ≈ 65K | ~15,000x |

---

## 9. Common Follow-up Questions

1. Can bidirectional BFS reconstruct the actual path? (Yes, but harder — track parent pointers in both directions; when frontiers meet, concatenate the two partial paths. The meeting-point handling requires care)
2. What if the graph is directed? (Backward BFS must follow reversed edges. For directed graphs, reversing edges might not always make sense semantically)
3. When should you NOT use bidirectional BFS? (When target is unknown, graph is very sparse, or the overhead of maintaining two frontiers outweighs savings for small d)
4. Is bidirectional BFS always faster? (No — if the target is very close to source (small d), the overhead of managing two frontiers can make it slower than standard BFS)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Standard BFS | Bidirectional is an optimization of BFS | 127. Word Ladder |
| A* Search | Combine bidirectional + heuristic for even faster search | 15-puzzle, navigation |
| State BFS | State = more than just position (word, lock combo) | 752. Open Lock |
| Hash Set | Efficient frontier lookup (O(1) membership test) | All bidirectional BFS |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
