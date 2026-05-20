# DSA Study Roadmap — Complete in Minimum Time

## How to Use This Plan

Each pattern file has 10 sections. Work through them in this order per pattern:
1. Read Section 1 (First-Timer Explanation) — 5 min
2. Read Section 2 (Revision Card) — 2 min
3. Read the C++ Template (Section 4) — 5 min
4. Do the Pattern Recognition Drills (Section 7) WITHOUT looking at answers — 10 min
5. Write your own solution for each problem (Section 6) — 15–30 min each
6. Check your solution against the reference; note complexity

**Rule:** Never move to the next phase until you can write the current phase's templates from memory.

---

## Time Budget

| Phase | Patterns | Days | Daily Load |
|-------|----------|------|------------|
| Phase 1 — Foundation | 18 patterns | 9 days | 2 patterns/day |
| Phase 2 — Core Algorithms | 22 patterns | 11 days | 2 patterns/day |
| Phase 3 — Dynamic Programming | 12 patterns | 8 days | 1–2/day |
| Phase 4 — Advanced Structures | 22 patterns | 11 days | 2 patterns/day |
| Phase 5 — Hard Specialties | 25 patterns | 13 days | 2 patterns/day |
| **Total** | **99 patterns** | **~52 days** | |

Add 1 week of mixed revision at the end = **~8 weeks total** (aggressive pace).
Comfortable pace (1 pattern/day + weekends off) = **~5 months**.

---

## Phase 1 — Foundation (Days 1–9)
*Goal: Build intuition for the most common interview patterns. 80% of medium problems live here.*

**Prerequisites:** Know basic C++ syntax, arrays, strings, hash maps.

### Week 1 (Days 1–5): Pointers + Windows

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 1 | P01 Converging Two Pointers | Simplest pattern; two-sum, sorted array |
| 1 | P02 Fast & Slow Pointers | Floyd's cycle — directly extends P01 thinking |
| 2 | P03 Fixed Separation | Nth from end — one clean trick |
| 2 | P04 In-Place Array Modification | Remove duplicates, partition — foundational |
| 3 | P05 String Comparison Special Chars | Backspace compare — uses P01 converging |
| 3 | P06 Expanding from Center | Palindromes — sets up P89 Manacher's later |
| 4 | P07 String Reversal | Rotation tricks — easy wins |
| 4 | P08 Fixed-Size Sliding Window | Window sum/max — first window pattern |
| 5 | P09 Variable-Size Sliding Window | Longest substring k-distinct — extends P08 |
| 5 | P10 Monotonic Queue in Window | Window max — preview of P99 deque |

### Week 2 Days (Days 6–9): Trees + Binary Search

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 6 | P11 Character Frequency Matching | Anagram window — completes sliding window group |
| 6 | P59 Binary Search Basics | Before trees; used everywhere |
| 7 | P12 Level-Order Traversal (BFS) | Trees start with BFS; queue mental model |
| 7 | P13 Recursive Preorder | DFS family — simplest tree recursion |
| 8 | P14 Recursive Inorder | BST property depends on inorder |
| 8 | P15 Recursive Postorder | Bottom-up tree DP requires postorder |
| 9 | P16 Lowest Common Ancestor | Combines preorder + BST — classic hard |
| 9 | P17 Serialization/Deserialization | Tests full tree traversal mastery |

**Phase 1 Checkpoint:** Solve LC easy/mediums: Two Sum, 3Sum, Longest Substring Without Repeat, Maximum Depth Binary Tree, Validate BST, Symmetric Tree. All from memory.

---

## Phase 2 — Core Algorithms (Days 10–20)
*Goal: Graphs, heaps, backtracking, greedy, binary search variants. 90% of interviews covered.*

### Days 10–12: Graphs

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 10 | P18 DFS Connected Components | Graphs start with DFS — grid traversal |
| 10 | P19 BFS Shortest Path | BFS after DFS; shortest path = BFS |
| 11 | P20 Cycle Detection | Needs DFS/BFS foundation |
| 11 | P21 Topological Sort | Needs cycle detection; Kahn's + DFS |
| 12 | P22 Deep Copy Graph | Clone with hash map — design pattern |
| 12 | P23 Dijkstra | Weighted shortest path; min-heap + BFS |

### Days 13–14: Heaps

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 13 | P42 Top-K Elements | Core heap pattern |
| 13 | P43 Median Stream | Two heaps — most asked heap hard |
| 14 | P44 K-Way Merge | Heap + sorted lists — generalizes P43 |
| 14 | P45 Task Scheduling | Greedy + heap combo |

### Days 15–16: Backtracking

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 15 | P46 Subsets & Combinations | Easiest backtracking template |
| 15 | P47 Permutations | Extends P46; swap-based variant |
| 16 | P48 N-Queens | Classic backtracking with constraint |
| 16 | P49 Word Search | Grid backtracking — DFS on matrix |

### Days 17–18: Greedy

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 17 | P53 Interval Scheduling | Most important greedy — meetings, overlaps |
| 17 | P54 Jump Game | Greedy + DP comparison |
| 18 | P55 Greedy Strings | Rearrange, reorganize character problems |
| 18 | P56 Greedy Arrays | Gas station, candy — greedy proofs |

### Days 19–20: Binary Search Variants

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 19 | P60 Rotated Array | Builds on P59 with a twist |
| 19 | P61 Binary Search on Answer | Most powerful BS pattern |
| 20 | P62 Two Pointers + Binary Search | Matrix search |
| 20 | P63 Peak & Special Search | Find peak — tricky boundary conditions |

**Phase 2 Checkpoint:** Solve: Number of Islands, Course Schedule, Merge Intervals, Word Ladder, Coin Change, Top K Frequent. All in < 20 minutes each.

---

## Phase 3 — Dynamic Programming (Days 21–28)
*Goal: DP is the hardest category. Spend extra time here. Don't rush.*

**Mental model before starting:** Every DP problem = "what info do I need from the past to make the current decision?" That's your state.

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 21 | P41 Memoization Top-Down | Start here — convert recursion to DP |
| 21 | P30 1D DP | Fibonacci → climbing stairs → house robber |
| 22 | P31 2D DP | Grid paths — LP/DP grid foundation |
| 22 | P32 Knapsack | 0/1 and unbounded — most reused substructure |
| 23 | P33 String DP | Edit distance, LCS — critical for string problems |
| 23 | P37 DP on Sequences | LIS — O(n log n) version with binary search |
| 24 | P34 Tree DP | Max path sum — bottom-up on tree |
| 24 | P35 Interval DP | Burst balloons, matrix chain — hardest DP type |
| 25 | P36 Bitmask DP | TSP, assignment — for small n (≤20) |
| 25 | P38 Digit DP | Count numbers with digit constraint |
| 26 | P39 Matrix Chain DP | Optimal parenthesization |
| 26 | P40 DP on Graphs | Shortest path as DP; Floyd-Warshall |
| 27–28 | Review all DP | Re-solve 1 problem from each DP pattern |

**Phase 3 Checkpoint:** Solve without hints: Longest Increasing Subsequence, Edit Distance, Word Break, Partition Equal Subset Sum, Unique Paths, Burst Balloons.

---

## Phase 4 — Data Structures (Days 29–39)
*Goal: Stacks, linked lists, arrays, matrix, strings — the "know your tools" phase.*

### Days 29–30: Stacks

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 29 | P64 Monotonic Stack | NGE, largest rectangle — core pattern |
| 29 | P65 Expression Evaluation | Calculator problems |
| 30 | P66 Stack Design | Min stack, max stack |
| 30 | P67 Stock Span | Monotonic stack variant |

### Days 31–32: Linked Lists

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 31 | P74 Reverse Linked List | Must-know; iterative + recursive |
| 31 | P75 Slow/Fast Pointers | Cycle, middle, nth from end |
| 32 | P77 Merge Linked Lists | Merge sorted, odd-even grouping |
| 32 | P78 Linked List Advanced | Rotate, delete without head |

### Days 33–35: Array & Matrix

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 33 | P79 Prefix Sums | Foundation for range queries |
| 33 | P80 Difference Arrays | Range update — complement of prefix sum |
| 34 | P81 Matrix Rotation & Spiral | In-place rotate, spiral print |
| 34 | P82 Prefix Product | Product except self — no division trick |
| 35 | P83 2D Prefix Sum | Rectangle sum query — extends P79 |
| 35 | P85 Array Matrix Advanced | Dutch flag, next permutation, cyclic sort |

### Days 36–39: Strings

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 36 | P90 Anagram Detection | Frequency window — easiest string pattern |
| 36 | P86 KMP Algorithm | String matching — must know the LPS build |
| 37 | P87 Rabin-Karp | Rolling hash string matching |
| 37 | P88 Z-Algorithm | Alternative to KMP; period detection |
| 38 | P89 Manacher's Algorithm | Longest palindromic substring O(n) |
| 38 | P91 Rolling Hash | Binary search + hash for duplicates |
| 39 | P92 String Advanced | Wildcard/regex DP, interleaving, edit distance |

---

## Phase 5 — Hard Specialties (Days 40–52)
*Goal: These appear in senior/FAANG hard rounds. Don't start here — they build on everything above.*

### Days 40–41: Remaining Graph Algorithms

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 40 | P24 Bellman-Ford | Negative weights; after Dijkstra |
| 40 | P29 Bidirectional BFS | Optimization of P19 |
| 41 | P26 Strongly Connected Components | Kosaraju/Tarjan — directed graphs |
| 41 | P27 Bridges & Articulation Points | Critical edges/nodes |

### Days 42–43: More Backtracking + Greedy + Bit Manipulation

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 42 | P50 Palindrome Partition | Backtracking + DP combo |
| 42 | P51 Expression Operators | Hard backtracking; pruning required |
| 43 | P52 Sudoku Grid Fill | Constraint propagation backtracking |
| 43 | P57 Huffman & Scheduling | Priority queue greedy |

### Days 44–45: Bit Manipulation

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 44 | P70 XOR Tricks | Single number, missing number |
| 44 | P71 Bit Counting | Hamming, popcount tricks |
| 45 | P72 Bit Tricks | Subsets via bitmask, power of 2 checks |
| 45 | P73 Integer Operations | Division without operators, multiply |

### Days 46–48: Design

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 46 | P76 LRU Cache | DLL + hash map — classic design |
| 46 | P93 Trie | Insert/search/prefix; word dictionary |
| 47 | P95 Design Problems | RandomizedSet, TimeMap, SnapshotArray |
| 47 | P94 LFU Cache | Hardest cache design |
| 48 | P84 Sweep Line | Meeting rooms, skyline |
| 48 | P25 Union Find (Graph section) | Review before P98 |

### Days 49–52: Advanced Data Structures

| Day | Patterns | Why This Order |
|-----|----------|----------------|
| 49 | P98 Union Find (DSU) | Path compression, Kruskal's MST |
| 49 | P28 Minimum Spanning Tree | Prim's + Kruskal's full treatment |
| 50 | P96 Segment Tree | Range queries with updates |
| 50 | P97 Fenwick Tree (BIT) | Lighter alternative to segment tree |
| 51 | P99 Advanced Design | Sparse table, binary lifting, deque |
| 51 | P68 Iterative DFS | Stack-based tree/graph traversal |
| 52 | P58 Greedy Math + P69 Asteroid | Final cleanup of loose patterns |

---

## Revision Schedule

After completing all 99 patterns, spend 1 week on mixed revision:

| Day | Focus |
|-----|-------|
| 53 | Re-do Phase 1 drills from memory (Two Pointers + Sliding Window + Trees) |
| 54 | Re-do Phase 2 drills (Graphs + Heaps + Greedy + Binary Search) |
| 55 | Re-do Phase 3 drills (DP — hardest to retain) |
| 56 | Re-do Phase 4 drills (Stacks + Linked Lists + Arrays + Strings) |
| 57 | Re-do Phase 5 drills (Design + Advanced Structures) |
| 58 | Timed mock: pick 3 random patterns, solve 2 problems each (time limit 45 min total) |
| 59 | Weak areas only — re-read patterns where drills felt uncertain |

---

## Pattern Dependencies (Read Before These)

Some patterns have hard prerequisites. Don't skip these chains:

```
P59 Binary Search → P60, P61, P62, P63
P01 Two Pointers → P02, P03, P04, P05
P08 Sliding Window → P09, P10, P11
P12 BFS → P19 → P23 → P29
P18 DFS → P20 → P21 → P26 → P27
P30 1D DP → P31 → P32 → P33 → P37
P41 Memoization → any DP (read this first)
P42 Top-K Heap → P43 → P44 → P45
P46 Backtracking → P47 → P48 → P49 → P50 → P51 → P52
P64 Monotonic Stack → P67 → P10 (revisit) → P99 (deque)
P74 Reverse LL → P75 → P77 → P78
P79 Prefix Sum → P80 → P83
P76 LRU → P94 LFU
P25/P98 Union Find → P28 MST
P96 Segment Tree → P97 Fenwick Tree (conceptual pair)
```

---

## Red Flags — Don't Skip These 12

These are the patterns most people skip and then regret in interviews:

1. **P61** — Binary Search on Answer (capacity/feasibility problems are everywhere)
2. **P21** — Topological Sort (course schedule, build order — asked constantly)
3. **P37** — DP on Sequences (LIS O(n log n) — appears in hard DPs)
4. **P64** — Monotonic Stack (next greater element is a stepping stone to histograms)
5. **P53** — Interval Scheduling (merge intervals, meeting rooms — high frequency)
6. **P43** — Median Stream (two heaps — the prototype for all streaming stats)
7. **P86** — KMP (failure function is conceptually hard; worth getting right once)
8. **P93** — Trie (prefix matching, autocomplete — asked in design rounds)
9. **P98** — Union Find (accounts merge, redundant connection — underestimated)
10. **P32** — Knapsack (the subproblem structure appears in 30+ other DPs)
11. **P35** — Interval DP (burst balloons, palindrome partition — triggers many hard problems)
12. **P76** — LRU Cache (asked in 40% of system design + coding combo rounds)

---

## Time Per Pattern (Realistic Estimates)

| Activity | Time |
|----------|------|
| Read sections 1–3 (explanation + revision card + tell signs) | 10 min |
| Study C++ template (section 4) | 10 min |
| Do all 5 drills without looking (section 7) | 15 min |
| Solve 3 of the 6 problems from scratch | 45–60 min |
| Review remaining 3 solutions | 15 min |
| **Total per pattern** | **~1.5–2 hours** |

At 2 patterns/day: ~3–4 hours/day. Adjust to your schedule.

---

## Interview Readiness Thresholds

| After Phase | You can handle |
|-------------|---------------|
| Phase 1 done | LC Easy confidently, many LC Medium |
| Phase 2 done | LC Medium confidently, some LC Hard |
| Phase 3 done | DP Mediums confidently, DP Hards partially |
| Phase 4 done | String/Array/Stack Hards confidently |
| Phase 5 done | All LC Hard patterns; FAANG-level readiness |
