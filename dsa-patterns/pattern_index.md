# Pattern Index — All 99 Patterns

> Quick-reference index. For full content, open the individual pattern file.
> Priority: **High** = appears in most OA/interviews | **Medium** = appears in ~50% | **Low** = advanced/rare

---

## I. Two Pointers (P01–P07)
*Core idea: Use two index variables moving through an array/string to avoid O(n²) nested loops.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P01 | Converging Two Pointers | Start at both ends, move inward based on comparison | 9 | **High** | 2–3 hrs |
| P02 | Fast & Slow Pointers | Two pointers moving at different speeds to detect cycles/midpoints | 4 | **High** | 1–2 hrs |
| P03 | Fixed Separation | Two pointers with a constant gap between them | 3 | **High** | 1 hr |
| P04 | In-place Array Modification | One read pointer, one write pointer to filter/compact in-place | 9 | **High** | 2 hrs |
| P05 | String Comparison w/ Special Chars | Simulate special characters (backspace etc.) with two pointers | 3 | **Medium** | 1 hr |
| P06 | Expanding From Center | Expand outward from a center point to find palindromes | 2 | **High** | 1 hr |
| P07 | String Reversal | Reverse sections of a string or array using two pointers | 4 | **Medium** | 1 hr |

---

## II. Sliding Window (P08–P11)
*Core idea: Maintain a window over a sequence, expanding/shrinking it to avoid recomputation.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P08 | Fixed Size Sliding Window | Window of constant size k slides across array | 5 | **High** | 1 hr |
| P09 | Variable Size Sliding Window | Window grows/shrinks based on a condition | 20 | **High** | 4–5 hrs |
| P10 | Monotonic Queue for Max/Min | Deque to track max/min inside window in O(1) | 3 | **High** | 2 hrs |
| P11 | Character Frequency Matching | Frequency map to check if window is an anagram/permutation | 3 | **High** | 1–2 hrs |

---

## III. Trees — DFS & BFS (P12–P17)
*Core idea: Binary tree traversal — the order you visit nodes changes what you can compute.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P12 | Level Order Traversal (BFS) | Visit nodes layer by layer using a queue | 5 | **High** | 1–2 hrs |
| P13 | Recursive Preorder (DFS) | Root → Left → Right; build or copy trees | 7 | **High** | 2 hrs |
| P14 | Recursive Inorder (DFS) | Left → Root → Right; gives sorted order for BST | 6 | **High** | 1–2 hrs |
| P15 | Recursive Postorder (DFS) | Left → Right → Root; compute subtree values bottom-up | 10 | **High** | 3 hrs |
| P16 | Lowest Common Ancestor | Find deepest node that is ancestor of both targets | 2 | **High** | 1 hr |
| P17 | Serialization & Deserialization | Convert tree to string and back | 3 | **Medium** | 1–2 hrs |

---

## IV. Graphs — DFS & BFS (P18–P29)
*Core idea: Traverse a graph to find components, paths, ordering, or connectivity.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P18 | DFS — Connected Components | DFS + visited array to count/fill islands or regions | 11 | **High** | 3 hrs |
| P19 | BFS — Connected Components | BFS to find shortest reach or minimum steps in a grid | 3 | **High** | 1–2 hrs |
| P20 | DFS — Cycle Detection | DFS with recursion stack to find cycles in directed graphs | 4 | **High** | 1–2 hrs |
| P21 | BFS — Topological Sort (Kahn's) | Process nodes in dependency order using in-degree array | 9 | **High** | 2–3 hrs |
| P22 | Deep Copy / Cloning | Clone graph or list with random pointers using hash map | 4 | **Medium** | 1–2 hrs |
| P23 | Shortest Path (Dijkstra/BFS) | Min-heap to find shortest weighted path in a graph | 10 | **High** | 3 hrs |
| P24 | Shortest Path (Bellman-Ford) | Handle negative edges or k-step constraints | 2 | **Medium** | 1–2 hrs |
| P25 | Union-Find (DSU) | Disjoint Set Union to track connected components efficiently | 12 | **High** | 3 hrs |
| P26 | Strongly Connected Components | Kosaraju or Tarjan to find SCCs in directed graph | 4 | **Low** | 2–3 hrs |
| P27 | Bridges & Articulation Points | Tarjan low-link to find critical edges/nodes | 2 | **Low** | 2 hrs |
| P28 | Minimum Spanning Tree | Kruskal (DSU) or Prim (heap) to connect all nodes cheaply | 4 | **Medium** | 2 hrs |
| P29 | Bidirectional BFS | BFS from both source and target simultaneously for speed | 3 | **Medium** | 2 hrs |

---

## V. Dynamic Programming (P30–P41)
*Core idea: Break problem into overlapping subproblems, cache results to avoid recomputation.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P30 | Fibonacci Style | dp[i] depends on dp[i-1] and/or dp[i-2] | 8 | **High** | 2 hrs |
| P31 | Kadane's Algorithm | Max/min subarray by deciding extend vs. restart | 5 | **High** | 1–2 hrs |
| P32 | Coin Change / Unbounded Knapsack | Each item can be used unlimited times | 3 | **High** | 2 hrs |
| P33 | 0/1 Knapsack / Subset Sum | Each item used at most once; partition problems | 2 | **High** | 2 hrs |
| P34 | Word Break Style | Can we partition string using a dictionary? | 2 | **High** | 1–2 hrs |
| P35 | Longest Common Subsequence | 2D DP on two sequences | 3 | **High** | 2 hrs |
| P36 | Edit Distance | Minimum operations to transform one string to another | 3 | **High** | 2 hrs |
| P37 | Unique Paths on Grid | 2D DP — count or minimize paths through grid | 7 | **High** | 2 hrs |
| P38 | Interval DP | dp[i][j] over intervals; merge ranges optimally | 2 | **Medium** | 2–3 hrs |
| P39 | Catalan Numbers | Count structurally distinct trees, parenthesizations | 3 | **Low** | 2 hrs |
| P40 | Longest Increasing Subsequence | LIS with patience sort or binary search optimization | 4 | **High** | 2 hrs |
| P41 | Stock Problems | State machine DP — hold/sell with cooldowns and fees | 5 | **High** | 2–3 hrs |

---

## VI. Heaps / Priority Queue (P42–P45)
*Core idea: Maintain a sorted "top" of a dataset efficiently using a heap.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P42 | Top K Elements | Min-heap of size K to find K largest/most-frequent | 8 | **High** | 2 hrs |
| P43 | Two Heaps for Median | Max-heap (lower half) + min-heap (upper half) | 2 | **High** | 1–2 hrs |
| P44 | K-way Merge | Merge K sorted lists using a heap | 4 | **High** | 2 hrs |
| P45 | Scheduling / Minimum Cost | Heap-based task/resource allocation | 8 | **High** | 3 hrs |

---

## VII. Backtracking (P46–P52)
*Core idea: Build candidates recursively, pruning branches that cannot lead to a valid solution.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P46 | Subsets (Include/Exclude) | At each element, choose to include or exclude | 4 | **High** | 1–2 hrs |
| P47 | Permutations | All orderings of elements using swap or used[] | 3 | **High** | 1–2 hrs |
| P48 | Combination Sum | Pick numbers that sum to target (with/without reuse) | 2 | **High** | 1 hr |
| P49 | Parentheses Generation | Add open if remaining, add close if valid | 2 | **High** | 1 hr |
| P50 | Word Search / Grid Path Finding | DFS on grid with backtrack on visited cells | 3 | **High** | 2 hrs |
| P51 | N-Queens / Constraint Satisfaction | Place queens with column/diagonal conflict checks | 2 | **Medium** | 2 hrs |
| P52 | Palindrome Partitioning | Partition string into palindrome substrings | 3 | **Medium** | 2 hrs |

---

## VIII. Greedy (P53–P58)
*Core idea: At each step, make the locally optimal choice and never look back.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P53 | Interval Merging / Scheduling | Sort by start time, merge overlapping intervals | 5 | **High** | 2 hrs |
| P54 | Jump Game Reachability | Track max reachable index greedily | 2 | **High** | 1 hr |
| P55 | Buy/Sell Stock (Greedy) | Buy on every dip, sell on every peak | 2 | **High** | 30 min |
| P56 | Gas Station Circuit | Find start where cumulative fuel never goes negative | 2 | **Medium** | 1 hr |
| P57 | Task Scheduling | Use heap + cooldown to schedule tasks optimally | 3 | **Medium** | 1–2 hrs |
| P58 | Sorting Based Greedy | Sort input by a key to greedily assign resources | 4 | **Medium** | 1–2 hrs |

---

## IX. Binary Search (P59–P63)
*Core idea: Eliminate half the search space each step using a monotone predicate.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P59 | Binary Search on Sorted Array | Classic lo/hi search on sorted data | 8 | **High** | 1–2 hrs |
| P60 | Find Min/Max in Rotated Array | Handle rotation by checking which half is sorted | 6 | **High** | 2 hrs |
| P61 | Binary Search on Answer | Search over the answer space using a feasibility function | 8 | **High** | 3 hrs |
| P62 | Find First/Last Occurrence | lo-biased vs. hi-biased binary search variants | 2 | **High** | 1 hr |
| P63 | Median / Kth in Two Sorted Arrays | Binary search on partition point across two arrays | 3 | **High** | 2 hrs |

---

## X. Stack (P64–P69)
*Core idea: LIFO structure to track pending work, unmatched elements, or monotone sequences.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P64 | Valid Parentheses Matching | Stack of open brackets, pop on close | 5 | **High** | 1 hr |
| P65 | Monotonic Stack | Maintain stack in sorted order to find next greater/smaller | 9 | **High** | 3 hrs |
| P66 | Expression Evaluation | Operator/operand stacks for infix/postfix expressions | 4 | **Medium** | 2 hrs |
| P67 | Simulation / Backtracking Helper | Stack to simulate path simplification, decode, collide | 3 | **Medium** | 1–2 hrs |
| P68 | Min Stack Design | Augment stack to support O(1) min queries | 3 | **Medium** | 1 hr |
| P69 | Largest Rectangle in Histogram | Monotonic stack to find area via boundaries | 2 | **High** | 2 hrs |

---

## XI. Bit Manipulation (P70–P73)
*Core idea: XOR, AND, OR, shifts to solve number-theoretic problems in O(1) space.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P70 | Bitwise XOR — Single/Missing | XOR cancels duplicates to isolate unique numbers | 4 | **High** | 1 hr |
| P71 | Bitwise AND — Counting Set Bits | n & (n-1) to count bits; power-of-two checks | 3 | **Medium** | 1 hr |
| P72 | Bitwise DP | Bitmask to represent subsets in DP states | 3 | **Medium** | 2 hrs |
| P73 | Power of Two/Four Check | Bit tricks for powers | 2 | **Low** | 30 min |

---

## XII. Linked List Manipulation (P74–P78)
*Core idea: Pointer surgery — reverse, merge, or restructure by changing next pointers.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P74 | In-place Reversal | Iterative reversal with prev/curr/next pointers | 6 | **High** | 2 hrs |
| P75 | Merging Sorted Lists | Interleave two sorted lists with a dummy head | 2 | **High** | 1 hr |
| P76 | Addition of Numbers | Add digit-by-digit with carry using linked list | 2 | **Medium** | 1 hr |
| P77 | Intersection Detection | Find meeting point of two linked lists | 2 | **Medium** | 1 hr |
| P78 | Reordering / Partitioning | Rearrange nodes based on position or value | 5 | **Medium** | 2 hrs |

---

## XIII. Array / Matrix Manipulation (P79–P85)
*Core idea: In-place transforms using geometric or mathematical properties of arrays.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P79 | In-place Rotation | Transpose + reverse to rotate a matrix | 3 | **High** | 1 hr |
| P80 | Spiral Traversal | Peel outer layer of matrix in direction sequence | 4 | **Medium** | 1–2 hrs |
| P81 | In-place Marking | Use sign of existing values as flags to avoid extra space | 3 | **Medium** | 1–2 hrs |
| P82 | Prefix/Suffix Products | Left-pass × right-pass to avoid division | 3 | **High** | 1–2 hrs |
| P83 | Plus One Arithmetic | Array-as-number arithmetic with carry | 4 | **Low** | 1 hr |
| P84 | In-place Merge from End | Fill array from end to avoid overwriting data | 2 | **Medium** | 1 hr |
| P85 | Cyclic Sort | Place element at its correct index in O(n) | 5 | **High** | 1–2 hrs |

---

## XIV. String Manipulation (P86–P92)
*Core idea: Character-level analysis using two pointers, frequency maps, or pattern matching.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P86 | Palindrome Check | Two pointers inward; skip invalid chars | 3 | **Medium** | 1 hr |
| P87 | Anagram Check | Sort or frequency map comparison | 2 | **High** | 30 min |
| P88 | Roman/Integer Conversion | Scan left-to-right with value comparison | 2 | **Medium** | 1 hr |
| P89 | String to Integer (atoi) | Handle sign, overflow, and non-digit chars | 2 | **Medium** | 1 hr |
| P90 | Manual Arithmetic Simulation | Simulate long addition/multiplication on strings | 3 | **Medium** | 1–2 hrs |
| P91 | String Matching (KMP / RK) | Build failure function to avoid redundant comparisons | 5 | **Medium** | 2–3 hrs |
| P92 | Repeated Substring Detection | KMP or string doubling trick | 3 | **Low** | 1 hr |

---

## XV. Design & Tries (P93–P99)
*Core idea: Build efficient data structures from scratch; Trie for prefix matching.*

| # | Pattern Name | One-Line Description | Problems | Priority | Est. Time |
|---|-------------|---------------------|----------|----------|-----------|
| P93 | Design Patterns (LRU, LFU, etc.) | Design O(1) data structures using hashmaps + linked lists | 34 | **High** | 5+ hrs |
| P94 | Tries (Prefix Trees) | Tree where each path from root to leaf encodes a word | 7 | **High** | 2–3 hrs |
| P95 | Segment Trees | Range queries and point updates in O(log n) | 5 | **Medium** | 3 hrs |
| P96 | Fenwick Trees (BIT) | Prefix sum updates and queries with bit tricks | 5 | **Medium** | 2 hrs |
| P97 | Hashing Patterns | Rolling hash, custom hash maps, grouping by hash | 6 | **High** | 2 hrs |
| P98 | Line Sweep | Sort events by coordinate, sweep to find intersections | 5 | **Medium** | 2 hrs |
| P99 | Advanced Patterns | Miscellaneous: sparse table, sqrt decomposition | 5 | **Low** | 3+ hrs |

---

## Priority Summary

### High Priority (master first — covers ~75% of OA/interview problems)
P01, P02, P03, P04, P06, P08, P09, P10, P11, P12, P13, P14, P15, P16, P18, P19, P20, P21, P23, P25, P30, P31, P32, P33, P34, P35, P36, P37, P40, P41, P42, P43, P44, P45, P46, P47, P48, P49, P50, P53, P54, P55, P59, P60, P61, P62, P63, P64, P65, P69, P70, P74, P75, P79, P82, P85, P87, P93, P94, P97

### Medium Priority
P05, P07, P17, P22, P24, P28, P29, P38, P51, P52, P56, P57, P58, P66, P67, P68, P71, P72, P76, P77, P78, P80, P81, P84, P86, P88, P89, P90, P91, P95, P96, P98

### Low Priority (advanced — for FAANG/Hard rounds)
P26, P27, P39, P73, P83, P92, P99
