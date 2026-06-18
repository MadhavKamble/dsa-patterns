# Number of Distinct Islands

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P16**

---

## Problem Understanding

**What is it asking?**
Given a binary grid where `1` = land and `0` = water, return the number of **distinct islands**. Two islands are considered the same if one can be translated (not rotated/reflected) to match the other.

**Input:** `grid[][]` — binary matrix
**Output:** Integer — number of distinct island shapes

**Example:**
```
grid = [[1,1,0,1,1],
        [1,0,0,0,0],
        [0,0,0,0,1],
        [1,1,0,1,1]]

Islands at (0,0)-(1,0)-(0,1):  shape = {(0,0),(0,1),(1,0)}
Island at (0,3)-(0,4):          shape = {(0,0),(0,1)}
Island at (2,4)-(3,3)-(3,4):   shape = {(0,0),(1,-1),(1,0)}
Island at (3,0)-(3,1):          shape = {(0,0),(0,1)}

Distinct shapes: 3 (the two {(0,0),(0,1)} islands are the same)
Output: 3
```

**Key Observations:**
- Two islands are "same" if their shapes match after translating to origin
- Store **relative coordinates** `(row - baseRow, col - baseCol)` for each cell in island
- Use a `set` of shapes — set deduplicates identical shapes automatically
- Base cell = top-left cell of each island → normalize all others relative to it

---

## Optimal Approach — DFS + Relative Coordinates + Set

### Key Observation

> When DFS starts at `(i, j)`, treat it as the origin `(0, 0)`. Every other cell in the island is stored as `(row - i, col - j)`. Since we always start DFS from the top-left unvisited cell (row by row, left to right), the same physical shape always produces the same relative coordinate list — so a `set` of these lists deduplicates correctly.

### Algorithm
1. For each unvisited land cell `(i,j)`:
   - Start DFS with `baseRow=i, baseCol=j`
   - Collect relative coords `{row-baseRow, col-baseCol}` into `shape` vector
   - Insert `shape` into a `set`
2. Return `set.size()`

### Dry Run

```
Island 1 starting at (0,0):
  Visit (0,0): shape={(0,0)}
  Visit (0,1): shape={(0,0),(0,1)}
  Visit (1,0): shape={(0,0),(0,1),(1,0)}
  → insert {(0,0),(0,1),(1,0)}

Island 2 starting at (0,3):
  Visit (0,3): shape={(0,0)}
  Visit (0,4): shape={(0,0),(0,1)}
  → insert {(0,0),(0,1)}

Island 3 starting at (2,4):
  Visit (2,4): shape={(0,0)}
  Visit (3,3): shape={(0,0),(1,-1)}
  Visit (3,4): shape={(0,0),(1,-1),(1,0)}
  → insert {(0,0),(1,-1),(1,0)}

Island 4 starting at (3,0):
  Visit (3,0): shape={(0,0)}
  Visit (3,1): shape={(0,0),(0,1)}
  → already in set (same as island 2)

set.size() = 3 ✅
```

### Complexity
- **Time:** O(m × n × log k) — each cell visited once; set insertion O(shape_size × log k) where k = distinct islands
- **Space:** O(m × n) — vis array + set of shapes

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    void dfs(int row, int col, int baseRow, int baseCol,
             vector<vector<int>>& grid, vector<vector<int>>& vis,
             vector<pair<int,int>>& shape) {
        vis[row][col]=1;
        shape.push_back({row-baseRow, col-baseCol});
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};
        for(int i=0;i<4;i++){
            int nRow=row+dRow[i];
            int nCol=col+dCol[i];
            if(nRow>=0 && nRow<grid.size() &&
            nCol>=0 && nCol<grid[0].size() &&
            !vis[nRow][nCol] && grid[nRow][nCol]==1){
                dfs(nRow,nCol,baseRow,baseCol,grid,vis,shape);
            }
        }
    }
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<int>> vis(n,vector<int>(m,0));
        set<vector<pair<int,int>>> st;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==1 && !vis[i][j]){
                    vector<pair<int,int>> shape;
                    dfs(i,j,i,j,grid,vis,shape);
                    st.insert(shape);
                }
            }
        }
        return st.size();
    }
};
```

### String Encoding Variant (same idea, uses string key instead of vector)

```cpp
class Solution {
    void dfs(int row, int col, int baseRow, int baseCol,
             vector<vector<int>>& grid, vector<vector<int>>& vis,
             string& key) {
        vis[row][col]=1;
        key+=to_string(row-baseRow)+","+to_string(col-baseCol)+"|";
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};
        for(int i=0;i<4;i++){
            int nRow=row+dRow[i];
            int nCol=col+dCol[i];
            if(nRow>=0 && nRow<grid.size() &&
            nCol>=0 && nCol<grid[0].size() &&
            !vis[nRow][nCol] && grid[nRow][nCol]==1){
                dfs(nRow,nCol,baseRow,baseCol,grid,vis,key);
            }
        }
    }
public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<int>> vis(n,vector<int>(m,0));
        set<string> st;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==1 && !vis[i][j]){
                    string key="";
                    dfs(i,j,i,j,grid,vis,key);
                    st.insert(key);
                }
            }
        }
        return st.size();
    }
};
```

---

## Interview Explanation Script

> "The key insight is that two islands have the same shape if their cells have the same relative positions when both are translated to the origin. I always start DFS from the top-left cell of each island — so the base is always `(i,j)` where the outer loop first finds land. Every cell in the island is stored as `(row-baseRow, col-baseCol)`. The DFS visits cells in a fixed order (determined by direction priority), so same-shaped islands always produce identical coordinate lists — a set deduplicates them."

> "This works because we scan row by row, left to right. The first cell found for any island is always its topmost-leftmost cell — consistent normalization."

---

## Recall Line *(10-Second Revision)*

> "Distinct Islands: DFS + relative coords from top-left base. Insert shape into set. set.size() = answer."

---

## Short Revision Notes

- Relative coord: `(row - baseRow, col - baseCol)` — normalizes to origin
- DFS traversal order must be **consistent** — same direction priority every time → same shape = same vector
- `set<vector<pair<int,int>>>` auto-deduplicates identical shapes
- String encoding is an alternative: cheaper comparison, same correctness
- Does NOT handle rotations/reflections — only translation equivalence

---

## Pattern Recognition Trigger

**When I see:**
- "Number of distinct islands / shapes"
- "Islands that are translations of each other"
- "Count unique connected components by shape"

**I should think of:** DFS + relative coordinates + set for deduplication

---

## Common Mistakes

❌ Storing absolute coordinates — two same-shaped islands at different positions get different sets → wrong count
❌ Inconsistent DFS direction order — same island visited in different orders produces different vectors
❌ Using unordered_set with vector — vectors aren't hashable by default in C++
❌ Confusing translation equivalence with rotation/reflection (problem only asks translation)

---

## What Interviewer Is Testing

- **Shape normalization:** relative coordinates from a consistent base
- **DFS traversal order consistency** — why fixed direction priority matters
- **Set-based deduplication** of complex objects

---

## Related Problems

- [ ] LeetCode #200 — Number of Islands (same DFS without shape tracking)
- [ ] Striver Step 15 P15 — Number of Islands

---

## Pattern Category

`Graphs` · `DFS` · `Grid` · `Hashing` · `Shape Normalization`

---

## Difficulty Analysis

**Rating:** Medium-Hard (DFS is easy; the shape normalization insight is what makes it tricky)

**Why challenging:** Understanding why relative coordinates work, why traversal order must be consistent, and implementing set-based deduplication of shapes.

---

## 30-Second Last-Minute Revision

> **Distinct Islands:** DFS from each unvisited `1`. Store `(row-baseRow, col-baseCol)` for each visited cell.
> Insert shape vector into `set`. Return `set.size()`.
> Key: same shape + consistent DFS order → identical vectors → set deduplicates.
> **Time:** O(m×n × log k) | **Space:** O(m×n)
