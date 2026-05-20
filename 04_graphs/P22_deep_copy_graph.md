# Pattern 22: Deep Copy of Graph

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 133. Clone Graph | Medium | https://leetcode.com/problems/clone-graph/ |
| 2 | 138. Copy List with Random Pointer | Medium | https://leetcode.com/problems/copy-list-with-random-pointer/ |
| 3 | 1490. Clone N-ary Tree | Easy | https://leetcode.com/problems/clone-n-ary-tree/ |

---

## 1. First-Timer Explanation

### What is this pattern?
A **deep copy** creates a completely independent duplicate of a data structure where modifying the copy doesn't affect the original. For graphs, this means:
1. Create a new node for every original node
2. Wire up the same edges between the new nodes (not pointing back to originals)

The key challenge: graphs can have **cycles** and **shared references**. A naive recursion without tracking will loop infinitely or create duplicate nodes.

**The algorithm (DFS with hash map):**
1. Use a `map<original_node → clone_node>` to track what's been copied
2. For each node: if already in map → return the clone; else create clone, add to map, then recursively clone neighbors
3. The map both prevents revisiting AND resolves shared references

**BFS variant**: same idea — use queue, map source to clone, enqueue unvisited neighbors.

### Visual Walkthrough
```
Original graph: 1 ↔ 2 ↔ 3 ↔ 1 (triangle with mutual edges)

DFS from node 1:
  visited[1]? No → create clone(1), visited[1] = clone(1)
  Recurse on neighbor 2:
    visited[2]? No → create clone(2), visited[2] = clone(2)
    Recurse on neighbor 1:
      visited[1]? YES → return clone(1)
    Recurse on neighbor 3:
      visited[3]? No → create clone(3), visited[3] = clone(3)
      Recurse on neighbor 2: visited → return clone(2)
      Recurse on neighbor 1: visited → return clone(1)
      clone(3).neighbors = [clone(2), clone(1)]
    clone(2).neighbors = [clone(1), clone(3)]
  Recurse on neighbor 3: visited → return clone(3)
  clone(1).neighbors = [clone(2), clone(3)]

Result: independent triangle clone
```

### When TO use this pattern
- Deep copy any graph or linked structure with back/cross references
- "Clone graph" problems
- Copy a linked list with random pointers
- Clone any structure with shared references

### When NOT to use this pattern
- Simple trees without back edges (regular recursive copy without map)
- Shallow copy (just duplicate pointers, not objects)

### Common Beginner Mistakes
- **Add to map BEFORE recursing**: if you recurse first, cycles cause infinite recursion
- **Map maps original→clone**: don't confuse direction
- **Random pointer linked list**: same idea — two-pass or hash map approach
- **N-ary tree**: no cycles, but still use the map to handle shared subtree references if any

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "clone", "deep copy", "copy with random pointer", "duplicate graph" |
| Core Idea | DFS/BFS with `map<original→clone>`; create clone before recursing to handle cycles |
| Trigger Keywords | "clone graph", "copy list with random pointer", "deep copy" |
| Avoid When | Simple tree (no shared references), shallow copy needed |
| Time Complexity | O(V + E) |
| Space Complexity | O(V) for the map |

**Gotchas:**
- Insert into map BEFORE recursing on neighbors (prevents infinite loop on cycles)
- The map serves double duty: cycle prevention + shared reference resolution
- Random pointer list: map[original] = clone; set clone.random = map[original.random]

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"clone graph"` → DFS/BFS with hash map
- `"deep copy"` → hash map to track original→clone
- `"copy list with random pointer"` → same pattern on linked list
- `"duplicate"` + graph/structure → deep copy pattern

---

## 4. C++ Template

```cpp
/*
 * Pattern: Deep Copy Graph
 * Time: O(V+E) | Space: O(V)
 */

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int v) : val(v) {}
};

// DFS CLONE
Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    unordered_map<Node*, Node*> visited;

    function<Node*(Node*)> dfs = [&](Node* orig) -> Node* {
        if (visited.count(orig)) return visited[orig];
        Node* clone = new Node(orig->val);
        visited[orig] = clone;  // MUST insert before recursing (handles cycles)
        for (Node* nb : orig->neighbors)
            clone->neighbors.push_back(dfs(nb));
        return clone;
    };

    return dfs(node);
}

// BFS CLONE
Node* cloneGraphBFS(Node* node) {
    if (!node) return nullptr;
    unordered_map<Node*, Node*> visited;
    queue<Node*> q;
    visited[node] = new Node(node->val);
    q.push(node);
    while (!q.empty()) {
        Node* cur = q.front(); q.pop();
        for (Node* nb : cur->neighbors) {
            if (!visited.count(nb)) {
                visited[nb] = new Node(nb->val);
                q.push(nb);
            }
            visited[cur]->neighbors.push_back(visited[nb]);
        }
    }
    return visited[node];
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"The challenge with deep copying a graph is handling cycles and shared references. I'll use DFS with a hash map from original node to its clone. When I visit a node, I first create its clone and immediately store it in the map — before recursing into neighbors. This way, if a cycle brings us back to this node, we return the already-created clone instead of creating a duplicate or infinitely recursing."

### Interview Flow Checklist
- [ ] Handle null input
- [ ] Initialize hash map `original → clone`
- [ ] DFS: check map first (return existing clone if present)
- [ ] Create clone, insert into map BEFORE recursing
- [ ] Recurse on all neighbors, adding results to clone's neighbor list
- [ ] Return clone

---

## 6. Problems

---

### Problem 1: 133. Clone Graph
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/clone-graph/
**Optimal C++ Solution:**
```cpp
Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    unordered_map<Node*, Node*> mp;
    function<Node*(Node*)> dfs = [&](Node* n) -> Node* {
        if (mp.count(n)) return mp[n];
        mp[n] = new Node(n->val);
        for (Node* nb : n->neighbors)
            mp[n]->neighbors.push_back(dfs(nb));
        return mp[n];
    };
    return dfs(node);
}
```
**Edge Cases:** [ ] Single node with no neighbors, [ ] Self-loop, [ ] Fully connected graph

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 138. Copy List with Random Pointer
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/copy-list-with-random-pointer/
**Why this pattern fits:** Linked list with random pointers = graph with back/cross edges; same hash map approach

**Optimal C++ Solution:**
```cpp
struct Node {
    int val;
    Node *next, *random;
    Node(int v) : val(v), next(nullptr), random(nullptr) {}
};

Node* copyRandomList(Node* head) {
    if (!head) return nullptr;
    unordered_map<Node*, Node*> mp;

    // pass 1: create all clones
    Node* cur = head;
    while (cur) {
        mp[cur] = new Node(cur->val);
        cur = cur->next;
    }

    // pass 2: wire next and random pointers
    cur = head;
    while (cur) {
        if (cur->next) mp[cur]->next = mp[cur->next];
        if (cur->random) mp[cur]->random = mp[cur->random];
        cur = cur->next;
    }
    return mp[head];
}
```
**Edge Cases:** [ ] Single node, [ ] Random pointer pointing to itself, [ ] Random pointer = null

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1490. Clone N-ary Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/clone-n-ary-tree/
**Why this pattern fits:** Same deep copy pattern; tree has no cycles but pattern generalizes

**Optimal C++ Solution:**
```cpp
struct Node {
    int val;
    vector<Node*> children;
    Node(int v) : val(v) {}
};

Node* cloneTree(Node* root) {
    if (!root) return nullptr;
    Node* clone = new Node(root->val);
    for (Node* child : root->children)
        clone->children.push_back(cloneTree(child));
    return clone;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a graph where nodes contain a value and a list of weighted edges, create a deep copy preserving all weights.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Deep Copy with hash map
**Reason:** Same clone graph approach. The clone node stores the same value; for edges, store (clone_neighbor, weight) pairs. Map original → clone as before; create clone before recursing to handle cycles.
</details>

---

**Drill 2:**
> You have a nested list structure where a list can contain integers or other lists (possibly with shared sub-lists). Deep copy it.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Deep Copy with hash map (for shared references)
**Reason:** If sub-lists can be shared (same list object appears in multiple places), use a map from original object to its clone — same as clone graph. If sub-lists are never shared, simple recursion suffices.
</details>

---

**Drill 3:**
> Clone a doubly linked list.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Two-pass clone or hash map
**Reason:** Doubly linked = each node has prev and next. Clone all nodes first (pass 1), then wire prev/next pointers using the map (pass 2). No cycles in the traditional sense, but prev creates a back-reference that needs the map.
</details>

---

**Drill 4:**
> Given a directed graph, return a deep copy but with all edge directions reversed.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Deep Copy + Edge Reversal
**Reason:** Same clone graph approach, but during wiring: for edge u→v in original, add v→u in the clone (i.e., add u's clone to v's clone's neighbor list instead of v's clone to u's clone's list). Build the transpose graph.
</details>

---

**Drill 5:**
> You're implementing a save/load system for a game state represented as a graph of objects. How would you serialize and deserialize it?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Graph Serialization (P17 pattern) + Deep Copy concepts
**Reason:** Serialization: DFS/BFS over the graph, assign IDs to nodes (= the "map" from object to ID). Write ID + value + neighbor ID list. Deserialization: create all nodes first (like pass 1 of copy-list), then wire edges using IDs (like pass 2). Handles cycles via the ID lookup table.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Clone Graph (DFS) | O(V+E) | O(V) | V for map + recursion stack |
| Clone Graph (BFS) | O(V+E) | O(V) | V for map + queue |
| Copy List with Random | O(n) | O(n) | Two-pass approach |
| Clone N-ary Tree | O(n) | O(h) | h = tree height, no cycle risk |

---

## 9. Common Follow-up Questions

1. Can you clone without extra space? (For linked list: interleave clones between originals — O(1) space trick. For general graph with cycles, hard to avoid the map)
2. What if nodes have unique IDs? (Map by ID instead of pointer — useful for serialization/deserialization)
3. How to clone a cyclic doubly linked list? (Use hash map; same two-pass approach as random pointer list)
4. Deep copy vs. shallow copy — when does each matter? (Shallow: references shared = mutations in copy affect original. Deep: fully independent. For immutable values, shallow is fine; for mutable objects, deep copy needed)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| DFS Traversal | Visit every node to clone it | 133. Clone Graph |
| Two-pointer / Two-pass | Clone all nodes, then wire pointers | 138. Random Pointer List |
| Graph Serialization | Assign IDs during deep copy for serialization | Design: game save/load |
| BFS | Alternative traversal for cloning | 133. Clone Graph BFS |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
