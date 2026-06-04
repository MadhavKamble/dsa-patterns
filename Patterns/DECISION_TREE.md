# DSA Pattern Decision Tree

**How to use:** Start at the green node. Follow arrows based on your input type and what the problem asks. Land on the blue box — that's your pattern.

---

## Part 1 — Input is an Array or String

```mermaid
flowchart TD
    classDef start fill:#2E7D32,color:#fff,stroke:#1B5E20,font-weight:bold
    classDef decision fill:#1565C0,color:#fff,stroke:#0D47A1,font-weight:bold
    classDef pattern fill:#0277BD,color:#fff,stroke:#01579B

    S([Start]):::start --> SORTED{Input is\nsorted?}

    SORTED -->|Yes| SQ{What to find?}
    SQ -->|Pair with target sum| P01[Two Pointers\nP01]:::pattern
    SQ -->|Find position or value| P59[Binary Search\nP59 - P63]:::pattern
    SQ -->|Min capacity / feasibility| P61[Binary Search\non Answer  P61]:::pattern

    SORTED -->|No| Q{Question\nis asking for...}

    Q -->|ALL of something\ncombinations permutations| P46[Backtracking\nP46 - P52]:::pattern

    Q -->|Number of ways\nMax or min possible\nIs it possible?| DEC{Decisions affect\neach other?}
    DEC -->|Yes — subproblems overlap| P30[Dynamic Programming\nP30 - P41]:::pattern
    DEC -->|No — locally optimal works| GRC{Threshold where\npossible flips\nto impossible?}
    GRC -->|Yes| P61B[Binary Search\non Answer  P61]:::pattern
    GRC -->|No| P53[Greedy\nP53 - P58]:::pattern

    Q -->|Subarray or\nsubstring| SUB{Size?}
    SUB -->|Fixed size k| P08[Fixed Sliding Window\nP08]:::pattern
    SUB -->|Variable size| P09[Variable Sliding Window\nP09]:::pattern
    SUB -->|Anagram or char frequency| P11[Char Frequency Window\nP11]:::pattern
    SUB -->|Range sum or count| P79[Prefix Sums\nP79]:::pattern
    SUB -->|Range updates| P80[Difference Arrays\nP80]:::pattern

    Q -->|String building\nor distance between elements| P64[Monotonic Stack\nP64 - P67]:::pattern

    Q -->|Prefix matching\nautocomplete| P93[Trie\nP93]:::pattern

    Q -->|Find specific\nelement or pair| P79B[Hash Map or Set]:::pattern

    Q -->|Elements added or\nremoved dynamically| DYN{What do you\nneed from them?}
    DYN -->|Max or min in a sliding window| P10[Monotonic Queue\nP10  P99]:::pattern
    DYN -->|Continuously max or min element| P42[Heap\nP42 - P45]:::pattern
    DYN -->|Running median| P43[Two Heaps\nP43]:::pattern

    Q -->|Pattern matching\nin string| STR{Type?}
    STR -->|Exact substring search| P86[KMP  P86\nor Z-Algo  P88]:::pattern
    STR -->|Longest palindrome| P89[Manacher\nP89]:::pattern
    STR -->|Edit or transform string| P33[String DP\nP33  P92]:::pattern
    STR -->|Multiple pattern hashing| P87[Rabin-Karp\nP87  P91]:::pattern
```

---

## Part 2 — Input is a Tree

```mermaid
flowchart TD
    classDef start fill:#2E7D32,color:#fff,stroke:#1B5E20,font-weight:bold
    classDef decision fill:#1565C0,color:#fff,stroke:#0D47A1,font-weight:bold
    classDef pattern fill:#0277BD,color:#fff,stroke:#01579B

    T([Tree]):::start --> LVL{Process\nlevel by level?}

    LVL -->|Yes| P12[BFS Level Order\nP12]:::pattern
    LVL -->|No| Q{Question involves...}

    Q -->|BST property\nkth smallest validate| P14[Inorder DFS\nP14]:::pattern

    Q -->|Compute value\nfrom children up\nheight diameter path sum| P15[Postorder DFS\nP15]:::pattern

    Q -->|Top-down path\nfrom root| P13[Preorder DFS\nP13]:::pattern

    Q -->|Lowest common\nancestor| P16[LCA\nP16]:::pattern

    Q -->|Encode or decode\nserialize tree| P17[Serialization\nP17]:::pattern

    Q -->|Optimal value across\nnodes max path rob house| P34[Tree DP\nP34]:::pattern

    Q -->|Prefix or word\nsearch in tree| P93[Trie\nP93]:::pattern

    Q -->|Ancestor queries\nLCA with many queries| P99[Binary Lifting\nP99]:::pattern
```

---

## Part 3 — Input is a Graph

```mermaid
flowchart TD
    classDef start fill:#2E7D32,color:#fff,stroke:#1B5E20,font-weight:bold
    classDef decision fill:#1565C0,color:#fff,stroke:#0D47A1,font-weight:bold
    classDef pattern fill:#0277BD,color:#fff,stroke:#01579B

    G([Graph]):::start --> SP{Need shortest\npath or\nfewest steps?}

    SP -->|Yes| WT{Weighted\nedges?}
    WT -->|No unweighted| P19[BFS\nP19]:::pattern
    WT -->|Yes no negative weights| P23[Dijkstra\nP23]:::pattern
    WT -->|Yes negative weights ok| P24[Bellman-Ford\nP24]:::pattern
    WT -->|All pairs shortest path| P40[Floyd-Warshall\nP40]:::pattern

    SP -->|No| Q{Question involves...}

    Q -->|Connected components\nnumber of islands provinces| CC{Static or\ndynamic?}
    CC -->|Static one time| P18[DFS Components\nP18]:::pattern
    CC -->|Dynamic merging over time| P98[Union Find DSU\nP98]:::pattern

    Q -->|Task ordering\ndependency resolution| P21[Topological Sort\nP21]:::pattern

    Q -->|Detect cycle| CYC{Graph type?}
    CYC -->|Undirected| P98B[Union Find DSU\nP98]:::pattern
    CYC -->|Directed| P20[DFS Cycle Detection\nP20]:::pattern

    Q -->|Minimum cost to\nconnect all nodes| P28[MST Kruskal\nP28  P98]:::pattern

    Q -->|Critical edges\nor critical nodes| P27[Bridges and\nArticulation Points  P27]:::pattern

    Q -->|Groups that are\nmutually reachable| P26[SCC Kosaraju\nP26]:::pattern

    Q -->|Clone or copy| P22[Deep Copy Graph\nP22]:::pattern

    Q -->|Shortest path but\ngraph is huge| P29[Bidirectional BFS\nP29]:::pattern
```

---

## Part 4 — Input is a Linked List

```mermaid
flowchart TD
    classDef start fill:#2E7D32,color:#fff,stroke:#1B5E20,font-weight:bold
    classDef decision fill:#1565C0,color:#fff,stroke:#0D47A1,font-weight:bold
    classDef pattern fill:#0277BD,color:#fff,stroke:#01579B

    LL([Linked List]):::start --> Q{Question involves...}

    Q -->|Detect cycle\nfind middle\nfind intersection| P75[Fast and Slow Pointers\nP75]:::pattern

    Q -->|Reverse the list\nor reverse k-group| P74[Reverse Linked List\nP74  dummy pointer]:::pattern

    Q -->|Find Nth node\nfrom end| P03[Fixed Gap Two Pointers\nP03]:::pattern

    Q -->|Cache with eviction\nO1 get and put| LRU{Evict by?}
    LRU -->|Recency LRU| P76[LRU Cache\nP76  DLL + HashMap]:::pattern
    LRU -->|Frequency LFU| P94[LFU Cache\nP94  3 Maps]:::pattern

    Q -->|Merge two or more\nsorted lists| P77[Merge Linked Lists\nP77  dummy head]:::pattern

    Q -->|Remove duplicates\nrotate list| P78[Advanced Linked List\nP78]:::pattern

    Q -->|Odd-even grouping\nadd two numbers| P77B[Merge and Partition\nP77]:::pattern
```

---

## Part 5 — Input is a Matrix or Grid

```mermaid
flowchart TD
    classDef start fill:#2E7D32,color:#fff,stroke:#1B5E20,font-weight:bold
    classDef decision fill:#1565C0,color:#fff,stroke:#0D47A1,font-weight:bold
    classDef pattern fill:#0277BD,color:#fff,stroke:#01579B

    M([Matrix or Grid]):::start --> Q{Question involves...}

    Q -->|Explore connected\ncells islands regions| P18[DFS or BFS\nP18  P19]:::pattern

    Q -->|Shortest path\nin grid| P19[BFS\nP19  01-BFS]:::pattern

    Q -->|Count paths\nor min cost path| P31[2D DP\nP31]:::pattern

    Q -->|Word search\nin grid| P49[Grid Backtracking\nP49]:::pattern

    Q -->|Rectangle sum query\nno updates| P83[2D Prefix Sum\nP83]:::pattern

    Q -->|Rotate matrix\nor spiral print| P81[Matrix Rotation\nand Spiral  P81]:::pattern

    Q -->|Interval or\ntime-based events| P84[Sweep Line\nP84]:::pattern

    Q -->|Range update\nover intervals| P80[Difference Arrays\nP80]:::pattern
```

---

## Part 6 — Design Problems

```mermaid
flowchart TD
    classDef start fill:#2E7D32,color:#fff,stroke:#1B5E20,font-weight:bold
    classDef decision fill:#1565C0,color:#fff,stroke:#0D47A1,font-weight:bold
    classDef pattern fill:#0277BD,color:#fff,stroke:#01579B

    D([Design a\nData Structure]):::start --> Q{Operations\nneeded?}

    Q -->|O1 insert delete\nand getRandom| P95[RandomizedSet\nArray + HashMap  P95]:::pattern

    Q -->|Cache with eviction| EV{Evict by?}
    EV -->|Recency| P76[LRU Cache\nDLL + HashMap  P76]:::pattern
    EV -->|Frequency| P94[LFU Cache\n3 Maps + minFreq  P94]:::pattern

    Q -->|Range sum with\npoint updates| P96[Segment Tree\nP96  or BIT P97]:::pattern

    Q -->|Range min or max\nno updates| P99[Sparse Table\nO1 query  P99]:::pattern

    Q -->|Prefix search\nautocomplete| P93[Trie\nP93]:::pattern

    Q -->|Union merge groups\ncheck connectivity| P98[Union Find DSU\nP98]:::pattern

    Q -->|Time-stamped\nkey value store| P95B[TimeMap\nHashMap + OrderedMap  P95]:::pattern

    Q -->|Versioned array\nsnapshots| P95C[SnapshotArray\nBinary Search per index  P95]:::pattern

    Q -->|Sliding window\nmax or min| P99B[Monotonic Deque\nP99]:::pattern

    Q -->|Kth ancestor\nLCA queries| P99C[Binary Lifting\nP99]:::pattern
```

---

## Quick-Scan Summary

```
Input Type        → First Question                  → Pattern
─────────────────────────────────────────────────────────────────
Array (sorted)    → find pair/position              → Two Pointers / Binary Search
Array (unsorted)  → all combos?                     → Backtracking
                  → optimal value?                  → DP or Greedy
                  → subarray condition?             → Sliding Window / Prefix Sum
                  → elements added dynamically?     → Heap / Monotonic Queue
String            → pattern match?                  → KMP / Z / Rabin-Karp
                  → palindrome?                     → Manacher / Expand Center
                  → prefix / autocomplete?          → Trie
                  → edit / transform?               → String DP
Tree              → level by level?                 → BFS Level Order
                  → BST property?                   → Inorder DFS
                  → bottom-up compute?              → Postorder DFS
                  → common ancestor?                → LCA
Graph             → shortest path unweighted?       → BFS
                  → shortest path weighted?         → Dijkstra / Bellman-Ford
                  → components / grouping?          → DFS / Union Find DSU
                  → task ordering?                  → Topological Sort
                  → minimum spanning tree?          → Kruskal + DSU
Linked List       → cycle / middle?                 → Fast & Slow Pointers
                  → reverse?                        → Reverse LL
                  → cache?                          → LRU / LFU
Matrix/Grid       → explore regions?               → DFS / BFS
                  → count paths?                    → 2D DP
                  → rectangle sum?                  → 2D Prefix Sum
Design            → O(1) all ops?                   → HashMap + Array/DLL
                  → range queries + updates?        → Segment Tree / BIT
                  → prefix / word search?           → Trie
                  → group merging?                  → Union Find DSU
```
