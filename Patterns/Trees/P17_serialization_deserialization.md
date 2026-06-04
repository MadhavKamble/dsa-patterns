# Pattern 17: Serialization and Deserialization

## Category
Trees

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 297. Serialize and Deserialize Binary Tree | Hard | https://leetcode.com/problems/serialize-and-deserialize-binary-tree/ |
| 2 | 572. Subtree of Another Tree | Easy | https://leetcode.com/problems/subtree-of-another-tree/ |
| 3 | 652. Find Duplicate Subtrees | Medium | https://leetcode.com/problems/find-duplicate-subtrees/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Serialization**: convert a tree to a string (for storage/transmission).
**Deserialization**: rebuild the tree from that string.

The key challenge: encode enough structure so you can uniquely reconstruct the tree. Null nodes must be explicitly encoded (e.g., as `"null"` or `"#"`), otherwise you can't distinguish different tree shapes.

**Preorder serialization** is simplest: visit root first, then recurse. During deserialization, consume tokens in the same preorder sequence and rebuild.

**Application in Subtree/Duplicate**: serialize each subtree as a string; two identical strings = identical subtrees. Use hash map for O(1) lookup.

### Visual Walkthrough
```
Tree:
       1
      / \
     2   3
        / \
       4   5

Preorder serialization: "1,2,#,#,3,4,#,#,5,#,#"
  Visit 1 → "1,"
  Visit 2 → "2,"
  Visit null (left of 2) → "#,"
  Visit null (right of 2) → "#,"
  Visit 3 → "3,"
  Visit 4 → "4,"
  ... etc.

Deserialization: read token by token
  Read "1" → create node(1)
  Read "2" → node(1).left = node(2)
  Read "#" → node(2).left = null
  Read "#" → node(2).right = null
  Read "3" → node(1).right = node(3)
  ...
```

### When TO use this pattern
- Encode/decode trees for storage or network transmission
- Compare two trees by string equality (subtree check, duplicate detection)
- Unique representation of tree structure

### When NOT to use this pattern
- Tree comparison only needs structure (use isSameTree recursion instead)
- Memory efficiency is critical (string serialization is verbose)

### Common Beginner Mistakes
- **Null representation**: must encode nulls explicitly — without them you can't decode
- **Delimiter**: use a separator (comma, space) between values to handle multi-digit numbers
- **Deserialization index**: use a reference to an integer index (or global) that advances as tokens are consumed
- **Duplicate subtrees**: serialize subtree including null markers → hash the result

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "serialize/deserialize", "subtree check by string", "find duplicate subtrees" |
| Core Idea | Preorder DFS with explicit null markers; parse tokens for deserialization |
| Trigger Keywords | "serialize", "encode", "subtree of another tree", "duplicate subtrees" |
| Avoid When | Just comparing trees (use recursive comparison) |
| Time Complexity | O(n) |
| Space Complexity | O(n) for the string |

**Gotchas:**
- Always include null markers in serialization
- Use a delimiter to separate values (multi-digit numbers)
- Deserialization: advance a shared index variable as tokens are consumed
- Duplicate subtrees: serialize each node's subtree → two identical serializations = duplicate

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"serialize and deserialize"` → direct pattern
- `"subtree of another tree"` → serialize both, check substring or recursive isSameTree
- `"duplicate subtrees"` → serialize each subtree, use hash map for duplicates

---

## 4. C++ Template

```cpp
/*
 * Pattern: Serialization and Deserialization
 * Time: O(n) | Space: O(n)
 */

struct TreeNode { int val; TreeNode *left, *right; };

class Codec {
    void serializeHelper(TreeNode* node, string& s) {
        if (!node) { s += "#,"; return; }
        s += to_string(node->val) + ",";
        serializeHelper(node->left, s);
        serializeHelper(node->right, s);
    }

    TreeNode* deserializeHelper(istringstream& ss) {
        string token;
        getline(ss, token, ',');
        if (token == "#") return nullptr;
        TreeNode* node = new TreeNode(stoi(token));
        node->left  = deserializeHelper(ss);
        node->right = deserializeHelper(ss);
        return node;
    }

public:
    string serialize(TreeNode* root) {
        string s;
        serializeHelper(root, s);
        return s;
    }

    TreeNode* deserialize(string data) {
        istringstream ss(data);
        return deserializeHelper(ss);
    }
};
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Serialization: preorder DFS, write node value followed by '#' for null nodes, comma-separated. This uniquely encodes the tree structure because null positions are explicit.
Deserialization: read tokens one by one. '#' creates a null node; any other value creates a real node, and we recursively build left and right from subsequent tokens."

### Interview Flow Checklist
- [ ] Confirm what separates tokens (comma, space)
- [ ] Confirm null representation ('#' or 'null')
- [ ] Serialize: preorder, include nulls
- [ ] Deserialize: consume tokens in same order, return null on '#'
- [ ] Test with a simple tree

---

## 6. Problems

---

### Problem 1: 297. Serialize and Deserialize Binary Tree
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
**Optimal C++ Solution:**
```cpp
class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) return "#";
        return to_string(root->val) + "," +
               serialize(root->left) + "," +
               serialize(root->right);
    }

    TreeNode* deserialize(string data) {
        queue<string> q;
        stringstream ss(data);
        string token;
        while (getline(ss, token, ',')) q.push(token);
        return build(q);
    }

    TreeNode* build(queue<string>& q) {
        string val = q.front(); q.pop();
        if (val == "#") return nullptr;
        TreeNode* node = new TreeNode(stoi(val));
        node->left  = build(q);
        node->right = build(q);
        return node;
    }
};
```
**Edge Cases:** [ ] Empty tree (serialize as "#"), [ ] Single node, [ ] Negative values

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 572. Subtree of Another Tree
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/subtree-of-another-tree/
**Why this pattern fits:** Serialize both trees; check if serialize(subRoot) is a substring of serialize(root) — but careful with false matches. Better: use explicit delimiters and compare node-by-node.

**Optimal C++ Solution:**
```cpp
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    // serialize approach: add delimiters to avoid false matches
    auto serialize = [](TreeNode* node, string& s) {};  // see below

    function<string(TreeNode*)> ser = [&](TreeNode* node) -> string {
        if (!node) return "#";
        return "(" + ser(node->left) + ")" +
               to_string(node->val) +
               "(" + ser(node->right) + ")";
    };

    // Alternative: recursive isSame check
    function<bool(TreeNode*, TreeNode*)> isSame = [&](TreeNode* s, TreeNode* t) -> bool {
        if (!s && !t) return true;
        if (!s || !t) return false;
        return s->val == t->val && isSame(s->left, t->left) && isSame(s->right, t->right);
    };

    function<bool(TreeNode*)> check = [&](TreeNode* node) -> bool {
        if (!node) return false;
        return isSame(node, subRoot) || check(node->left) || check(node->right);
    };

    return check(root);
}
```

**Complexity Analysis:**
- Time: O(n × m) — n = root size, m = subRoot size; naive approach
- Space: O(n + m) for recursion stacks

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 652. Find Duplicate Subtrees
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-duplicate-subtrees/
**Why this pattern fits:** Serialize each subtree; hash map detects duplicates by string equality

**Optimal C++ Solution:**
```cpp
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    unordered_map<string, int> count;
    vector<TreeNode*> result;

    function<string(TreeNode*)> serialize = [&](TreeNode* node) -> string {
        if (!node) return "#";
        string s = "(" + serialize(node->left) + ")" +
                   to_string(node->val) +
                   "(" + serialize(node->right) + ")";
        if (++count[s] == 2) result.push_back(node);  // found duplicate
        return s;
    };

    serialize(root);
    return result;
}
```
**Complexity Analysis:**
- Time: O(n²) worst case (string building)
- Space: O(n²)

**Edge Cases:** [ ] No duplicates, [ ] All identical subtrees

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a list of serialized trees, group them by structure (structurally identical trees in one group).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Serialization + Hash Map grouping
**Reason:** Serialize each tree using canonical preorder notation. Use the serialization string as a key in a hash map. Trees with same serialization are structurally identical.
</details>

---

**Drill 2:**
> Design a system where trees are stored in a database and can be retrieved. How do you store them efficiently?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Serialization
**Reason:** Serialize to JSON or a compact format with delimiter. Store as a string column. Deserialize on retrieval. Consider compression for large trees.
</details>

---

**Drill 3:**
> Check if tree T1 contains tree T2 as a subtree, where T2 can appear at any rotation (rotated 90°).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Serialization + multiple canonical forms
**Reason:** Generate all rotation variants of T2's serialization. Check if any variant appears as a subtree in T1.
</details>

---

**Drill 4:**
> Given two BSTs, check if they represent the same set of values.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Inorder traversal (not serialization)
**Reason:** Inorder both BSTs → compare resulting sorted arrays. No serialization needed since BST inorder is unique for a given set of values.
</details>

---

**Drill 5:**
> After deleting some nodes, check if the remaining tree structure matches a given pattern.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Serialization comparison
**Reason:** Serialize the modified tree and the pattern tree. If strings match → structure matches. Use canonical form to avoid delimiter issues.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Serialize + Deserialize | O(n) | O(n) | Linear string building |
| Subtree check (recursive) | O(n×m) | O(n+m) | Can do O(n+m) with KMP |
| Find duplicate subtrees | O(n²) worst | O(n²) | String hashing can reduce |

---

## 9. Common Follow-up Questions

1. Can you serialize more compactly? (Yes — use BFS level order, encode nulls as '-1')
2. Is preorder serialization the only option? (No — level order works too; postorder works but deserialization is less natural)
3. How to handle very deep trees? (Iterative serialization with an explicit stack)
4. Duplicate subtrees with O(n) time? (Use integer IDs: each unique serialization gets an ID; check if ID appears twice. Reduces string comparison to integer comparison)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Preorder DFS | Natural traversal order for serialization | 297. Serialize/Deserialize |
| Hash Map | Detect duplicate subtrees | 652. Find Duplicate Subtrees |
| KMP / String matching | Efficient subtree check | 572. Subtree (O(n+m) approach) |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
