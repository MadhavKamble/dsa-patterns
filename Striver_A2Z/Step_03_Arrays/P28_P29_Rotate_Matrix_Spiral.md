# 🔥 Rotate Matrix 90° & Spiral Order Traversal

> **LeetCode #48 & #54** · **Difficulty:** Medium · **Step 3 — P28 & P29**

---

# P28 — Rotate Matrix by 90 Degrees (Clockwise)

## 🧠 Problem Understanding

Rotate an N×N matrix 90 degrees **clockwise** in-place.

**Input:**
```
[[1,2,3],      [[7,4,1],
 [4,5,6],  →   [8,5,2],
 [7,8,9]]       [9,6,3]]
```

---

## 🥇 Optimal — Transpose + Reverse Rows

### Key Observation
> 💡 Clockwise 90° = **Transpose** (flip along main diagonal) + **Reverse each row**  
> Anti-clockwise 90° = Transpose + Reverse each column

```
Original:   Transpose:   Reverse rows:
1 2 3       1 4 7        7 4 1
4 5 6  →    2 5 8   →    8 5 2
7 8 9       3 6 9        9 6 3
```

### Algorithm
1. Transpose: `swap(matrix[i][j], matrix[j][i])` for `i < j`
2. Reverse each row

### Complexity
- **Time:** O(N²) · **Space:** O(1)

```cpp
/*
 * ROTATE MATRIX 90° CLOCKWISE
 * Step 1: Transpose (swap matrix[i][j] with matrix[j][i] for i<j)
 * Step 2: Reverse each row
 * Time O(N²) | Space O(1)
 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // transpose (upper triangle ↔ lower triangle)
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                swap(matrix[i][j], matrix[j][i]);

        // reverse each row
        for (int i = 0; i < n; i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};
```

---

# P29 — Print Matrix in Spiral Order

## 🧠 Problem Understanding

Traverse an M×N matrix in spiral order (clockwise from outside to inside).

**Input:**
```
[[1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]]
```
**Output:** `[1,2,3,6,9,8,7,4,5]`

---

## 🥇 Optimal — Layer by Layer (4 Boundaries)

### Key Observation
> 💡 Maintain 4 boundaries: `top, bottom, left, right`. Process top row, right col, bottom row (reversed), left col (reversed). Shrink boundaries after each side.

### Algorithm
1. `top=0, bottom=M-1, left=0, right=N-1`
2. While `top <= bottom` and `left <= right`:
   - Traverse top row left→right, then `top++`
   - Traverse right col top→bottom, then `right--`
   - If `top <= bottom`: traverse bottom row right→left, then `bottom--`
   - If `left <= right`: traverse left col bottom→top, then `left++`

### Dry Run (3×3 matrix)
```
top=0,bot=2,l=0,r=2:
  Top row:    1,2,3        top→1
  Right col:  6,9          right→1
  Bottom row: 8,7          bot→1
  Left col:   4            left→1
top=1,bot=1,l=1,r=1:
  Top row:    5            done
```
**Output:** `[1,2,3,6,9,8,7,4,5]` ✅

### Complexity
- **Time:** O(M×N) · **Space:** O(1) extra (output not counted)

```cpp
/*
 * SPIRAL ORDER — 4-boundary shrinking
 * Process: top row → right col → bottom row → left col → shrink bounds
 * Guard: check top<=bottom and left<=right before bottom row and left col
 * Time O(M*N) | Space O(1)
 */
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            // top row: left → right
            for (int j = left; j <= right; j++) result.push_back(matrix[top][j]);
            top++;

            // right col: top → bottom
            for (int i = top; i <= bottom; i++) result.push_back(matrix[i][right]);
            right--;

            // bottom row: right → left (only if rows remain)
            if (top <= bottom) {
                for (int j = right; j >= left; j--) result.push_back(matrix[bottom][j]);
                bottom--;
            }

            // left col: bottom → top (only if cols remain)
            if (left <= right) {
                for (int i = bottom; i >= top; i--) result.push_back(matrix[i][left]);
                left++;
            }
        }

        return result;
    }
};
```

---

## 🎤 Interview Explanation Script
> **P28:** "Rotating 90° clockwise decomposes into: transpose (flip along main diagonal by swapping `matrix[i][j]` with `matrix[j][i]`) followed by reversing each row. Both steps are O(N²) and in-place."

> **P29:** "I use 4 boundary pointers: top, bottom, left, right. Each iteration I traverse the outermost layer: top row, right column, bottom row (if exists), left column (if exists). Then I shrink all 4 boundaries inward and repeat."

---

## 🧾 Recall Lines
> **P28:** Transpose (swap `[i][j]` ↔ `[j][i]`) then reverse each row = 90° clockwise.  
> **P29:** 4 boundaries shrink inward. Top row → right col → bottom row (guard) → left col (guard).

## 📝 Short Revision Notes
**P28:**
- Anti-clockwise: reverse each row first, then transpose
- For non-square matrix: can't do in-place — use extra space

**P29:**
- Guard conditions on bottom row and left col prevent double-counting single rows/cols
- Works for both M×N and M=N matrices

## ⚠️ Common Mistakes
**P28:** Transposing full matrix (including lower triangle) swaps elements back  
**P29:** Missing guard checks → elements counted twice for single-row/single-col remaining

## 📚 Related Problems
- [ ] LeetCode #48 — Rotate Image
- [ ] LeetCode #54 — Spiral Matrix
- [ ] LeetCode #59 — Spiral Matrix II (fill matrix in spiral)

## 🏆 Pattern Category
`Arrays` · `Matrix` · `Two Pointers`

## ⏱️ 30-Second Revision
> P28: Transpose (swap i<j pairs) + reverse each row. O(N²)/O(1).  
> P29: 4 boundaries, process each side, shrink, guard bottom/left. O(MN)/O(1).
