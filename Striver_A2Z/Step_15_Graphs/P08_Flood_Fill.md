# Flood Fill

> **LeetCode #733** · **Difficulty:** Easy · **Step 15 — Graphs · P08**

---

## Problem Understanding

**What is it asking?**
Given an `m x n` image (2D grid of integers), a starting pixel `(sr, sc)`, and a new color, perform a **flood fill** — change the color of the starting pixel and all 4-directionally connected pixels of the same original color to the new color.

**Input:** `image[][]`, `sr`, `sc` (start row/col), `color` (new color)
**Output:** Modified `image[][]`

**Example:**
```
image = [[1,1,1],
         [1,1,0],
         [1,0,1]]
sr=1, sc=1, color=2

Starting pixel (1,1) has color 1.
All 4-connected pixels with color 1 get replaced by 2.

Output: [[2,2,2],
         [2,2,0],
         [2,0,1]]

Note: bottom-right (2,2) has color 1 but is NOT connected to (1,1)
      through same-color pixels → stays unchanged.
```

**Key Observations:**
- This is DFS/BFS on a 2D grid, restricted to cells matching the original color
- 4-directional neighbors only (up, down, left, right) — no diagonals
- Edge case: if `image[sr][sc]` already equals `color`, return immediately (avoids infinite loop)
- The "visited" condition is implicit: a cell is visited once its color is changed

---

## Optimal Approach — DFS on Grid

### Key Observation

> Flood fill is exactly graph DFS/BFS where "nodes" are grid cells and "edges" exist between 4-directional neighbors with the same original color. We don't need a separate visited array — changing the color itself marks the cell as visited.

### Algorithm
1. Store `origColor = image[sr][sc]`
2. If `origColor == color`, return image (nothing to do)
3. DFS from `(sr, sc)`:
   - Change `image[r][c]` to `color`
   - For each of 4 neighbors `(nr, nc)`:
     - If in bounds AND `image[nr][nc] == origColor`: recurse

### Dry Run

**Input:** `image = [[1,1,1],[1,1,0],[1,0,1]]`, `sr=1, sc=1, color=2`, `origColor=1`

```
DFS(1,1): image[1][1]=2
  DFS(0,1): image[0][1]=2
    DFS(0,0): image[0][0]=2
      DFS(1,0): image[1][0]=2
        DFS(2,0): image[2][0]=2  → no more origColor neighbors
        DFS(0,0): already 2, skip
      DFS(0,1): already 2, skip
    DFS(0,2): image[0][2]=2
      DFS(1,2): image[1][2]=0 ≠ origColor, skip
  DFS(2,1): image[2][1]=0 ≠ origColor, skip
  DFS(1,0): already 2, skip
  DFS(1,2): image[1][2]=0 ≠ origColor, skip
```

**Output:**
```
[[2,2,2],
 [2,2,0],
 [2,0,1]]
```
✅

### Complexity
- **Time:** O(m × n) — each cell visited at most once
- **Space:** O(m × n) — recursion stack in worst case (all cells same color)

---

## Clean C++ Interview Code

```cpp
/*
 * FLOOD FILL (LC 733)
 *
 * PROBLEM UNDERSTANDING:
 *   Change starting pixel and all 4-connected same-color pixels to new color.
 *
 * KEY INSIGHT:
 *   DFS on grid. No separate visited array needed — color change = visited mark.
 *   Early exit if origColor == color prevents infinite recursion.
 *
 * COMPLEXITY: Time O(m*n) | Space O(m*n)
 */
class Solution {
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

    void dfs(vector<vector<int>>& image, int r, int c,
             int origColor, int newColor) {
        image[r][c] = newColor;                    // mark visited by recoloring

        for (auto& d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (nr >= 0 && nr < image.size() &&
                nc >= 0 && nc < image[0].size() &&
                image[nr][nc] == origColor) {
                dfs(image, nr, nc, origColor, newColor);
            }
        }
    }

public:
    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr, int sc, int color) {
        int origColor = image[sr][sc];
        if (origColor == color) return image;      // avoid infinite loop
        dfs(image, sr, sc, origColor, color);
        return image;
    }
};
```

### BFS Variant

```cpp
vector<vector<int>> floodFill(vector<vector<int>>& image,
                               int sr, int sc, int color) {
    int origColor = image[sr][sc];
    if (origColor == color) return image;

    int m = image.size(), n = image[0].size();
    int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    queue<pair<int,int>> q;

    image[sr][sc] = color;
    q.push({sr, sc});

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (auto& d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n &&
                image[nr][nc] == origColor) {
                image[nr][nc] = color;
                q.push({nr, nc});
            }
        }
    }

    return image;
}
```

---

## Interview Explanation Script

> "Flood fill is grid DFS. I save the original color, then DFS from the starting cell — at each cell I change its color to the new one (which also marks it visited) and recurse on the 4 neighbors that still have the original color."

> "The critical edge case: if the starting pixel already has the new color, I return immediately. Otherwise, the DFS would see the new color equals old color on revisit and loop infinitely."

---

## Recall Line *(10-Second Revision)*

> "Flood fill: DFS on grid. Change color = mark visited. Early exit if origColor==newColor. O(m*n)."

---

## Short Revision Notes

- 4-directional neighbors: `{-1,0},{1,0},{0,-1},{0,1}`
- No separate visited array — recoloring serves as visited marker
- **Must check** `origColor == color` before starting — prevents infinite recursion
- Works identically with BFS
- Bounds check: `nr >= 0 && nr < m && nc >= 0 && nc < n`

---

## Pattern Recognition Trigger

**When I see:**
- "Fill connected region with new value"
- "Paint bucket tool"
- "Spread to 4-connected same-value neighbors"

**I should think of:** DFS/BFS on grid with same-value constraint

---

## Common Mistakes

❌ Forgetting `origColor == color` early exit → infinite recursion
❌ Using 8-directional neighbors (diagonals) when problem says 4-directional
❌ Separate visited array with color check — works but unnecessary; recoloring is simpler
❌ Bounds check order — check in-bounds BEFORE checking cell value

---

## What Interviewer Is Testing

- **Grid DFS/BFS:** Applying graph traversal to 2D grid
- **Edge case awareness:** origColor == newColor
- **Clean implementation:** Recoloring as visited marker, bounds checks

---

## Related Problems

- [ ] LeetCode #200 — Number of Islands (same grid DFS, cell value is '1'/'0')
- [ ] LeetCode #994 — Rotten Oranges (multi-source BFS on grid)
- [ ] LeetCode #130 — Surrounded Regions (DFS from border)
- [ ] LeetCode #417 — Pacific Atlantic Water Flow (DFS from two borders)
- [ ] Striver Step 15 P09 — Rotten Oranges

---

## Pattern Category

`Graphs` · `DFS` · `BFS` · `Grid` · `Flood Fill`

---

## Difficulty Analysis

**Rating:** Easy (once you recognize it as grid DFS)

**Why challenging:** The `origColor == color` edge case is easy to miss and causes an infinite loop.

---

## 30-Second Last-Minute Revision

> **Flood Fill:** Grid DFS. Save origColor. If origColor==newColor → return early.
> DFS: recolor cell → recurse on 4 neighbors with origColor.
> **Time:** O(m×n) | **Space:** O(m×n) recursion stack
> **Watch out for:** origColor == newColor early exit
