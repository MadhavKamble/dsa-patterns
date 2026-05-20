# DSA Patterns Study System

> Based on Swati Ahuja's (Thita) DSA Patterns Sheet — the most pattern-complete OA/interview prep resource.
> Original sheet: https://thita.ai/dsa-patterns-sheet

---

## What This Repo Is

A complete, self-contained DSA study system built around **pattern recognition** — the single most important skill for cracking OA rounds and technical interviews.

Instead of grinding random problems, this system teaches you to **recognize the pattern first**, then apply the correct algorithm. Every pattern file gives you:
- A beginner explanation with visuals
- A revision card for quick review
- Interview tell signs and keyword triggers
- A reusable C++ template
- A scripted interview walkthrough
- Full solutions for every problem in the pattern
- Pattern recognition drills
- Complexity cheatsheets and follow-up questions

---

## Folder Structure

```
dsa-patterns/
├── README.md                    ← you are here
├── progress.md                  ← track your progress across all 99 patterns
├── pattern_index.md             ← master index of all patterns with priority
│
├── 00_templates/                ← reusable C++ skeletons for each pattern family
│
├── 01_two_pointers/             ← Patterns 1–7
├── 02_sliding_window/           ← Patterns 8–11
├── 03_trees/                    ← Patterns 12–17
├── 04_graphs/                   ← Patterns 18–29
├── 05_dynamic_programming/      ← Patterns 30–41
├── 06_heaps/                    ← Patterns 42–45
├── 07_backtracking/             ← Patterns 46–52
├── 08_greedy/                   ← Patterns 53–58
├── 09_binary_search/            ← Patterns 59–63
├── 10_stack/                    ← Patterns 64–69
├── 11_bit_manipulation/         ← Patterns 70–73
├── 12_linked_list/              ← Patterns 74–78
├── 13_array_matrix/             ← Patterns 79–85
├── 14_strings/                  ← Patterns 86–92
└── 15_design_and_tries/         ← Patterns 93–99
```

---

## How to Study One Pattern Per Session

Follow this workflow for every pattern file:

### Phase 1 — Learn (30 min)
1. Read **Section 1 (First-Timer Explanation)** — understand the pattern from scratch
2. Study the ASCII visual walkthrough
3. Read the real-world analogy
4. Understand "When TO use" vs "When NOT to use"

### Phase 2 — Internalize (15 min)
5. Read **Section 2 (Revision Card)** — memorize the recognition signal and core idea
6. Read **Section 3 (Interview Tell Signs)** — burn the keywords into memory

### Phase 3 — Code (45–90 min)
7. Study the **C++ Template** (Section 4) — understand every comment
8. Read Section 5 (How to Present) — rehearse the verbal script once
9. Solve problems in Section 6 — **attempt first**, then read solution
10. Write your own solution in the "My Solution" block

### Phase 4 — Drill (15 min)
11. Do the **Pattern Recognition Drills** (Section 7) without hints
12. Check answers only after committing to a guess

### Phase 5 — Review (5 min)
13. Update **progress.md** — mark the pattern complete, log confidence (1–5)
14. Add anything surprising to "My Notes" in the pattern file

---

## How to Update progress.md

After each session, open `progress.md` and update the row for the pattern you studied:
- Change **Status** from `Not Started` → `In Progress` → `Completed`
- Fill in **Problems Solved** (e.g., `4/9`)
- Rate your **Confidence** from 1 (can't do it alone) to 5 (could teach it)
- Add the **Date Completed**

---

## Recommended Study Order for Placement/OA

### Tier 1 — Master These First (Covers ~70% of OA problems)
| Priority | Pattern | File |
|----------|---------|------|
| 1 | Variable Size Sliding Window | `02_sliding_window/P09_variable_size.md` |
| 2 | Two Pointers — Converging | `01_two_pointers/P01_converging.md` |
| 3 | Binary Search on Answer | `09_binary_search/P61_on_answer_condition_function.md` |
| 4 | BFS Level Order Traversal | `03_trees/P12_level_order_traversal.md` |
| 5 | Recursive Postorder (Tree) | `03_trees/P15_recursive_postorder.md` |
| 6 | Fibonacci-Style DP | `05_dynamic_programming/P30_fibonacci_style.md` |
| 7 | Kadane's Algorithm | `05_dynamic_programming/P31_kadanes_algorithm.md` |
| 8 | DFS Island Counting | `04_graphs/P18_dfs_connected_components.md` |
| 9 | BFS Topological Sort | `04_graphs/P21_bfs_topological_sort.md` |
| 10 | Top K Elements (Heap) | `06_heaps/P42_top_k_elements.md` |

### Tier 2 — Add For Full Interview Readiness
| Priority | Pattern | File |
|----------|---------|------|
| 11 | Monotonic Stack | `10_stack/P65_monotonic_stack.md` |
| 12 | Subsets / Backtracking | `07_backtracking/P46_subsets.md` |
| 13 | Coin Change / Unbounded Knapsack | `05_dynamic_programming/P32_coin_change_unbounded_knapsack.md` |
| 14 | Union-Find | `04_graphs/P25_union_find.md` |
| 15 | LRU Cache / Design | `15_design_and_tries/P93_design_patterns.md` |
| 16 | Trie | `15_design_and_tries/P94_tries.md` |
| 17 | Shortest Path (Dijkstra) | `04_graphs/P23_shortest_path_dijkstra.md` |
| 18 | 0/1 Knapsack | `05_dynamic_programming/P33_01_knapsack_subset_sum.md` |
| 19 | Interval Merging | `08_greedy/P53_interval_merging_scheduling.md` |
| 20 | LCS / Edit Distance | `05_dynamic_programming/P35_longest_common_subsequence.md` |

### Tier 3 — Advanced (For FAANG / Hard Rounds)
All remaining patterns (P21–P99 not listed above), especially:
- Segment Trees (P95), Fenwick Trees (P96) for range query problems
- Strongly Connected Components (P26) for advanced graph rounds
- Minimum Spanning Tree (P28)
- Interval DP (P38), Catalan Numbers (P39)

---

## 30-Day Accelerated Plan

If your interview/OA is in **30 days or less**, study the `Swatis 30 days patterns sheet` subset:

| Week | Focus | Patterns |
|------|-------|---------|
| Week 1 | Arrays + Strings foundation | P1–P11 |
| Week 2 | Trees + Graphs | P12–P29 |
| Week 3 | DP + Heaps + Backtracking | P30–P52 |
| Week 4 | Greedy + BS + Stack + Remaining | P53–P99 |

Do **1 problem per pattern** minimum. Revisit weak areas in the final 2 days.

---

## Quick Reference: Pattern by Problem Type

| If you see... | Use pattern... |
|---------------|----------------|
| "subarray", "substring", "window" | Sliding Window (P8/P9) |
| "sorted array", two elements summing | Two Pointers Converging (P1) |
| "linked list cycle", "duplicate" | Fast & Slow Pointers (P2) |
| "level by level", "right side view" | BFS Level Order (P12) |
| "diameter", "max depth", "path sum" | DFS Postorder (P15) |
| "number of islands", "connected components" | DFS/BFS Islands (P18/P19) |
| "course schedule", "prerequisite" | Topological Sort (P21) |
| "minimum/maximum... find X" | Binary Search on Answer (P61) |
| "top K", "K closest", "K largest" | Heap Top K (P42) |
| "all subsets", "combinations" | Backtracking (P46/P48) |
| "merge intervals", "meeting rooms" | Greedy Intervals (P53) |
| "next greater element", "temperatures" | Monotonic Stack (P65) |
| "edit distance", "common subsequence" | DP LCS/Edit (P35/P36) |
| "coin change", "ways to make" | Unbounded Knapsack (P32) |
| "word break", "s can be segmented" | Word Break DP (P34) |
| "serialize/deserialize", "LRU cache" | Design (P93) |
| "prefix of words", "autocomplete" | Trie (P94) |

---

## Resources

- Original sheet: https://thita.ai/dsa-patterns-sheet
- Video playlist: https://www.youtube.com/watch?v=DKWEYzF2xJU&list=PL2SB3o9_VW78xKoiCPtzLnTWjMOklYlNy
- Theory: https://thita.ai/dashboard/learning-path/dsa
- Discord: https://discord.gg/zxywjSuvDT
