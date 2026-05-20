# P81 — Matrix Rotation and Spiral Traversal

## 1. First-Timer Explanation

### What Is It?
**Matrix rotation** rotates an n×n matrix 90° clockwise in-place. **Spiral traversal** visits all elements of a matrix in a spiral (outward-to-inward) order. Both require systematic index manipulation.

### Rotate 90° Clockwise — Two-Step Trick
```
Step 1: Transpose (flip along main diagonal)
  matrix[i][j] ↔ matrix[j][i]

Step 2: Reverse each row
  [1,2,3] → [3,2,1]

Example:
  1 2 3       1 4 7       7 4 1
  4 5 6  →T→  2 5 8  →R→  8 5 2
  7 8 9       3 6 9       9 6 3

That's 90° clockwise ✓
```

### Spiral Order
```
Matrix:
1  2  3
4  5  6
7  8  9

Layers from outside to inside.
Top row: 1,2,3 (left→right, top++)
Right col: 6,9 (top→bottom, right--)
Bottom row: 8,7 (right→left, bottom--)
Left col: 4 (bottom→top, left++)
Center: 5

Result: [1,2,3,6,9,8,7,4,5]
```

### When to Use
- "Rotate matrix 90 degrees in-place" → transpose + reverse rows
- "Spiral order traversal" → four boundary pointers (top/bottom/left/right)
- "Rotate 180°" → rotate twice or: reverse all rows, then transpose
- "Set matrix zeroes" → mark rows/cols to zero without corrupting detection
- "Diagonal traversal" → enumerate diagonals by (i+j) grouping

### Common Mistakes
1. Transpose: only swap when `j < i` (not both directions — would swap back)
2. Spiral: decrement the boundary BEFORE the next direction to avoid double-visiting
3. Spiral: always check `top <= bottom` and `left <= right` before inner traversal steps
4. Rotate 90° CCW: transpose then reverse COLUMNS (not rows) — or reverse rows then transpose

---

## 2. Revision Card

**Recognition Signal:** "rotate matrix in-place", "spiral order", "traverse layer by layer"

**Core Idea:**
- Rotate 90° CW: transpose (`swap(m[i][j], m[j][i])` for j<i), then reverse each row
- Spiral: four pointers (top, bottom, left, right); peel one layer per pass

**Trigger Keywords:** rotate, spiral, layer, in-place, transpose

**Complexity:** O(n²) time, O(1) space for both rotation and spiral

---

## 3. Interview Tell Signs

- "Rotate n×n matrix 90° clockwise in-place" → transpose + reverse rows
- "Spiral order of m×n matrix" → boundary shrink with top/bottom/left/right
- "Rotate image" → same as 90° clockwise
- "Diagonal traverse" → group by diagonal sum i+j
- "Set zeroes" → two-pass: first collect zero positions, then zero out rows/cols
- "Game of Life" → two-bit encoding to do in-place with state machine

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Rotate Matrix 90° Clockwise (in-place) ───────────────────────────────────
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    // Step 1: Transpose
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(matrix[i][j], matrix[j][i]);
    // Step 2: Reverse each row
    for (int i = 0; i < n; i++)
        reverse(matrix[i].begin(), matrix[i].end());
}

// ── Spiral Order ──────────────────────────────────────────────────────────────
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> res;
    int top = 0, bottom = matrix.size() - 1;
    int left = 0, right = matrix[0].size() - 1;
    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; c++) res.push_back(matrix[top][c]);
        top++;
        for (int r = top; r <= bottom; r++) res.push_back(matrix[r][right]);
        right--;
        if (top <= bottom) {
            for (int c = right; c >= left; c--) res.push_back(matrix[bottom][c]);
            bottom--;
        }
        if (left <= right) {
            for (int r = bottom; r >= top; r--) res.push_back(matrix[r][left]);
            left++;
        }
    }
    return res;
}

// ── Generate Spiral Matrix ─────────────────────────────────────────────────────
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> mat(n, vector<int>(n, 0));
    int top = 0, bottom = n-1, left = 0, right = n-1, num = 1;
    while (top <= bottom && left <= right) {
        for (int c = left; c <= right; c++) mat[top][c] = num++;
        top++;
        for (int r = top; r <= bottom; r++) mat[r][right] = num++;
        right--;
        if (top <= bottom) { for (int c = right; c >= left; c--) mat[bottom][c] = num++; bottom--; }
        if (left <= right) { for (int r = bottom; r >= top; r--) mat[r][left] = num++; left++; }
    }
    return mat;
}

// ── Set Matrix Zeroes ─────────────────────────────────────────────────────────
void setZeroes(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    bool firstRow = false, firstCol = false;
    for (int j = 0; j < n; j++) if (matrix[0][j] == 0) firstRow = true;
    for (int i = 0; i < m; i++) if (matrix[i][0] == 0) firstCol = true;
    // Use first row/col as markers
    for (int i = 1; i < m; i++) for (int j = 1; j < n; j++)
        if (matrix[i][j] == 0) { matrix[i][0] = 0; matrix[0][j] = 0; }
    for (int i = 1; i < m; i++) if (matrix[i][0] == 0)
        for (int j = 1; j < n; j++) matrix[i][j] = 0;
    for (int j = 1; j < n; j++) if (matrix[0][j] == 0)
        for (int i = 1; i < m; i++) matrix[i][j] = 0;
    if (firstRow) for (int j = 0; j < n; j++) matrix[0][j] = 0;
    if (firstCol) for (int i = 0; i < m; i++) matrix[i][0] = 0;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Rotate 90° CW):**
> "Two steps: first transpose (swap matrix[i][j] with matrix[j][i] for all j > i), then reverse each row. Transpose reflects along the main diagonal; reversing each row then rotates. Both steps are O(n²) and in-place."

**Verbal Script (Spiral):**
> "Four boundary pointers: top, bottom, left, right. Process one full layer per outer loop iteration: top row left-to-right (then top++), right column top-to-bottom (then right--), bottom row right-to-left if top ≤ bottom (then bottom--), left column bottom-to-top if left ≤ right (then left++). The guards prevent double-visiting the center row or column for odd-dimension matrices."

**Checklist:**
- [ ] Transpose: `for j = i+1..n` (not 0..n — would undo the swap)
- [ ] Spiral: check `top <= bottom` before bottom row traversal
- [ ] Spiral: check `left <= right` before left column traversal
- [ ] Set zeroes: process first row/col separately (they serve as markers)

---

## 6. Problems

### Problem 1: Rotate Image
**Difficulty:** Medium | **LC:** 48

```cpp
void rotate(vector<vector<int>>& m) {
    int n = m.size();
    for (int i = 0; i < n; i++)
        for (int j = i+1; j < n; j++) swap(m[i][j], m[j][i]); // transpose
    for (int i = 0; i < n; i++) reverse(m[i].begin(), m[i].end()); // reverse rows
}
// Time: O(n²) | Space: O(1)
// 90° CCW: reverse each row first, then transpose
// 180°: rotate() twice, or reverse all rows then reverse each row
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Spiral Matrix
**Difficulty:** Medium | **LC:** 54

```cpp
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> res;
    int t=0, b=matrix.size()-1, l=0, r=matrix[0].size()-1;
    while (t<=b && l<=r) {
        for (int c=l;c<=r;c++) res.push_back(matrix[t][c]); t++;
        for (int row=t;row<=b;row++) res.push_back(matrix[row][r]); r--;
        if (t<=b) { for (int c=r;c>=l;c--) res.push_back(matrix[b][c]); b--; }
        if (l<=r) { for (int row=b;row>=t;row--) res.push_back(matrix[row][l]); l++; }
    }
    return res;
}
// Time: O(m*n) | Space: O(1) excluding output
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Spiral Matrix II
**Difficulty:** Medium | **LC:** 59

```cpp
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> mat(n, vector<int>(n));
    int t=0,b=n-1,l=0,r=n-1,num=1;
    while (t<=b&&l<=r) {
        for (int c=l;c<=r;c++) mat[t][c]=num++; t++;
        for (int row=t;row<=b;row++) mat[row][r]=num++; r--;
        if (t<=b) { for (int c=r;c>=l;c--) mat[b][c]=num++; b--; }
        if (l<=r) { for (int row=b;row>=t;row--) mat[row][l]=num++; l++; }
    }
    return mat;
}
// Time: O(n²) | Space: O(n²) for output
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Set Matrix Zeroes
**Difficulty:** Medium | **LC:** 73

```cpp
void setZeroes(vector<vector<int>>& m) {
    int rows=m.size(), cols=m[0].size();
    bool fr=false, fc=false;
    for (int j=0;j<cols;j++) if (m[0][j]==0) fr=true;
    for (int i=0;i<rows;i++) if (m[i][0]==0) fc=true;
    for (int i=1;i<rows;i++) for (int j=1;j<cols;j++)
        if (m[i][j]==0) { m[i][0]=0; m[0][j]=0; }
    for (int i=1;i<rows;i++) if (m[i][0]==0) for (int j=1;j<cols;j++) m[i][j]=0;
    for (int j=1;j<cols;j++) if (m[0][j]==0) for (int i=1;i<rows;i++) m[i][j]=0;
    if (fr) for (int j=0;j<cols;j++) m[0][j]=0;
    if (fc) for (int i=0;i<rows;i++) m[i][0]=0;
}
// Time: O(m*n) | Space: O(1)
// Trick: first row/col as markers; track if they themselves should be zeroed
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Diagonal Traverse
**Difficulty:** Medium | **LC:** 498

```cpp
vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<int> res;
    for (int d = 0; d < m + n - 1; d++) {
        if (d % 2 == 0) { // going up
            int r = min(d, m-1), c = d - r;
            while (r >= 0 && c < n) res.push_back(mat[r--][c++]);
        } else { // going down
            int c = min(d, n-1), r = d - c;
            while (c >= 0 && r < m) res.push_back(mat[r++][c--]);
        }
    }
    return res;
}
// Time: O(m*n) | Space: O(1) excluding output
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Game of Life
**Difficulty:** Medium | **LC:** 289

**Approach:** Encode next state in the second bit. `0→1`: mark as 2; `1→0`: mark as -1. After applying rules, reconstruct.

```cpp
void gameOfLife(vector<vector<int>>& board) {
    int m = board.size(), n = board[0].size();
    auto countLive = [&](int r, int c) {
        int cnt = 0;
        for (int dr = -1; dr <= 1; dr++) for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int nr = r+dr, nc = c+dc;
            if (nr>=0&&nr<m&&nc>=0&&nc<n && abs(board[nr][nc])==1) cnt++;
        }
        return cnt;
    };
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) {
        int live = countLive(i, j);
        if (board[i][j] == 1 && (live < 2 || live > 3)) board[i][j] = -1; // 1→0
        if (board[i][j] == 0 && live == 3) board[i][j] = 2; // 0→1
    }
    for (int i = 0; i < m; i++) for (int j = 0; j < n; j++)
        board[i][j] = board[i][j] > 0 ? 1 : 0;
}
// Time: O(m*n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Rotate [[1,2],[3,4]] 90° clockwise. Show transpose then reverse.
<details><summary>Reveal</summary>
Transpose (swap [0][1] and [1][0]): [[1,3],[2,4]]. Reverse each row: row0=[1,3]→[3,1], row1=[2,4]→[4,2]. Result: [[3,1],[4,2]]. Verification: original column 0 (1,3) becomes row 0 reversed (3,1) ✓.
</details>

**Drill 2:** Spiral order of [[1,2,3],[4,5,6],[7,8,9]]. Trace the boundary pointers.
<details><summary>Reveal</summary>
t=0,b=2,l=0,r=2. Top row: [1,2,3], t=1. Right col: [6,9], r=1. Bottom row (t=1≤b=2): [8,7], b=1. Left col (l=0≤r=1): [4], l=1. t=1,b=1,l=1,r=1 → Center: [5]. t=1,b=1,l=1,r=1 → top row: [5], t=2 → stop. Result: [1,2,3,6,9,8,7,4,5] ✓.
</details>

**Drill 3:** Set zeroes in [[1,1,1],[1,0,1],[1,1,1]]. What are the markers before zeroing?
<details><summary>Reveal</summary>
fr=false, fc=false. Scan: m[1][1]=0 → m[1][0]=0, m[0][1]=0. Zero inner rows: m[1][1..2]: m[1][1]=0, m[1][2]=0. Zero inner cols: m[0][1]=0 → m[1][1]=0, m[2][1]=0. Apply fr=false (no row 0 zero). Apply fc=false (no col 0 zero). Result: [[1,0,1],[0,0,0],[1,0,1]] ✓.
</details>

**Drill 4:** For diagonal traverse, which direction (up/down) does diagonal d=0 go?
<details><summary>Reveal</summary>
d=0: even → going up (r decreases, c increases). Start: r=min(0,m-1)=0, c=0-0=0. Only one element: mat[0][0]. Then r=-1 < 0 → stop. So diagonal 0 goes "up" and contains just the top-left element. Diagonal 1 (odd, going down) contains mat[0][1] and mat[1][0].
</details>

**Drill 5:** Game of Life: cell (1,1) has value 1 and 3 live neighbors. What happens to it?
<details><summary>Reveal</summary>
Live cell with 2 or 3 live neighbors survives. 3 neighbors → survives → stays 1. No change needed. If it had fewer than 2 or more than 3, it would die (marked as -1). With exactly 3, it lives.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Rotate 90° | O(n²) | O(1) |
| Spiral order | O(m×n) | O(1) |
| Generate spiral | O(n²) | O(n²) output |
| Set matrix zeroes | O(m×n) | O(1) |
| Diagonal traverse | O(m×n) | O(1) |
| Game of Life | O(m×n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: How to rotate 90° counter-clockwise?**
A: Option 1: Reverse each row, then transpose. Option 2: Rotate clockwise three times. Option 3: Transpose then reverse each column (reverse vertically).

**Q: How to rotate 180°?**
A: Reverse the entire matrix row-by-row (reverse the order of rows), then reverse each individual row. Or just call rotate() twice.

**Q: Spiral traversal if the matrix is modified during traversal (infinite spiral)?**
A: Track visited cells with a boolean grid. Direction array `{right, down, left, up}`, turn when hitting boundary or visited cell.

---

## 10. Cross-Pattern Connections

- **P83 (2D Prefix Sum):** Builds on 2D matrix traversal, column-then-row ordering
- **P82 (Prefix Product):** Product of array except self uses left-right sweeps similar to row reversal
- **P84 (Sweep Line):** Matrix diagonal traversal is a form of sweep
- **P62 (Binary Search 2D):** 2D staircase search uses matrix structure
