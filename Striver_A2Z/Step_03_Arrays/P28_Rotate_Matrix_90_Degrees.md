# 🔥 Rotate Matrix by 90 Degrees (Clockwise)

> **LeetCode #48** · **Difficulty:** Medium · **Step 3 — Arrays · P28**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an N×N matrix, rotate it **90 degrees clockwise in-place**.

**Input:**
```
[[1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]]
```
**Output:**
```
[[7, 4, 1],
 [8, 5, 2],
 [9, 6, 3]]
```

**Constraints:** N×N matrix, `1 ≤ N ≤ 20`, in-place required (O(1) extra space)

**Key Observations:**
- Element at `(i, j)` moves to `(j, N-1-i)` after 90° clockwise rotation
- This can be decomposed: **Transpose** (flip along main diagonal) → **Reverse each row**
- Transpose: `(i,j)` ↔ `(j,i)`
- After transpose + row-reverse: `(i,j) → (j,i) → (j, N-1-i)` ✓

**Simple Example:**
```
Original:    Transpose:   Reverse rows:
1 2 3        1 4 7        7 4 1
4 5 6   →    2 5 8   →    8 5 2
7 8 9        3 6 9        9 6 3
```

---

## 🥉 Brute Force Approach

### Idea
Create a new N×N matrix. For each cell `(i, j)` in original, place it at `(j, N-1-i)` in the new matrix. Copy back.

### Algorithm
1. Create `temp[N][N]`
2. For each `(i, j)`: `temp[j][N-1-i] = matrix[i][j]`
3. Copy `temp` back to `matrix`

### Complexity
- **Time:** O(N²)
- **Space:** O(N²) — extra matrix

### C++ Code
```cpp
// BRUTE FORCE: extra matrix, direct mapping
void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> temp(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[j][n - 1 - i] = matrix[i][j];
    matrix = temp;
}
```

---

## 🥇 Optimal Approach — Transpose + Reverse Rows

### Key Observation

> 💡 **Clockwise 90°** = **Transpose** (swap `matrix[i][j]` with `matrix[j][i]` for all `i < j`) **+ Reverse each row**
>
> - Transpose: `(i,j)` → `(j,i)`
> - Reverse row: `(j,i)` → `(j, N-1-i)` ✓
>
> **Anti-clockwise 90°** = **Reverse each row** + **Transpose** (reverse the order of operations)

### Proof:
After 90° clockwise rotation, element at `(i, j)` ends up at `(j, N-1-i)`:
- Transpose: `matrix[i][j]` → `matrix[j][i]`
- Reverse row `j`: `matrix[j][i]` → `matrix[j][N-1-i]` ✓

### Algorithm
1. **Transpose:** For `i` from `0` to `N-2`, for `j` from `i+1` to `N-1`: `swap(matrix[i][j], matrix[j][i])`
2. **Reverse each row:** For each row `i`: `reverse(matrix[i].begin(), matrix[i].end())`

### Dry Run

**Input:**
```
1 2 3
4 5 6
7 8 9
```

**Step 1 — Transpose** (swap upper triangle with lower):
```
swap(matrix[0][1], matrix[1][0]) → 2↔4
swap(matrix[0][2], matrix[2][0]) → 3↔7
swap(matrix[1][2], matrix[2][1]) → 6↔8
```
After transpose:
```
1 4 7
2 5 8
3 6 9
```

**Step 2 — Reverse each row:**
```
Row 0: [1,4,7] → [7,4,1]
Row 1: [2,5,8] → [8,5,2]
Row 2: [3,6,9] → [9,6,3]
```

**Output:**
```
7 4 1
8 5 2
9 6 3
```
✅

### Complexity
- **Time:** O(N²) — N²/2 swaps for transpose + N²/2 element reversals
- **Space:** O(1) — all in-place

### Why is this optimal?
We must read and write every cell at least once (Ω(N²) lower bound). The transpose+reverse approach achieves this exactly with O(1) extra space — optimal.

---

## 🎤 Interview Explanation Script

> "The brute force uses an extra N×N matrix and directly maps each element to its rotated position. That's O(N²) space."

> "The in-place approach decomposes the rotation into two simpler operations. First, I transpose the matrix — swap every `matrix[i][j]` with `matrix[j][i]` for i < j. Then I reverse each row."

> "Proof: after rotation, element `(i,j)` should be at `(j, N-1-i)`. Transpose takes `(i,j)` to `(j,i)`. Reversing row `j` takes `(j,i)` to `(j, N-1-i)`. Exactly right."

> "For anti-clockwise rotation: reverse each row first, then transpose. The operations are swapped."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * ROTATE IMAGE 90° CLOCKWISE — Transpose + Reverse Rows
 *
 * PROBLEM UNDERSTANDING:
 *   Rotate N×N matrix clockwise 90° in-place.
 *
 * EDGE CASES:
 *   - 1×1 matrix: no change needed
 *   - 2×2 matrix: one swap per pair
 *
 * KEY OBSERVATION:
 *   Clockwise 90° = Transpose then reverse each row
 *   Anti-clockwise 90° = Reverse each row then transpose
 *
 * WHY: Element (i,j) → after transpose → (j,i) → after row-reverse → (j, N-1-i) ✓
 *
 * COMPLEXITY: Time O(N²) | Space O(1)
 */
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // step 1: transpose — swap elements across the main diagonal
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)    // j starts at i+1 to avoid double-swapping
                swap(matrix[i][j], matrix[j][i]);

        // step 2: reverse each row
        for (int i = 0; i < n; i++)
            reverse(matrix[i].begin(), matrix[i].end());
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Clockwise 90° = Transpose (swap [i][j]↔[j][i] for j>i) then reverse each row."

---

## 📝 Short Revision Notes

- Transpose: swap `matrix[i][j]` with `matrix[j][i]` for all `i < j` (upper triangle only)
- Reverse rows: `std::reverse` on each row
- Anti-clockwise = reverse each row → then transpose
- 180° rotation = reverse each row + reverse matrix (flip vertically)
- Works only for square (N×N) matrices in-place; non-square needs O(M×N) space
- j starts at `i+1`, not 0 — starting at 0 would undo previous swaps

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Rotate matrix 90°, 180°, 270°"
- "In-place matrix transformation"

**I should think of:**
- 90° CW: Transpose + reverse rows
- 90° CCW: Reverse rows + transpose
- 180°: Reverse rows + reverse columns (or just reverse the full matrix twice)

---

## ⚠️ Common Mistakes

❌ Transposing full matrix (j from 0 to N-1) — double-swapping reverts changes  
❌ Reversing columns instead of rows — gives anti-clockwise instead of clockwise  
❌ Applying to non-square matrix in-place (not possible without extra space)  
❌ Confusing step order: transpose THEN reverse (not reverse then transpose) for clockwise  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Decomposing a complex transformation into two simpler in-place operations
- **Reasoning:** Why transpose + reverse = 90° clockwise (coordinate mapping proof)
- **Optimization:** O(N²) space → O(1) space

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Transpose + reverse rows | O(N²) | O(1) | Best |
| Extra matrix | O(N²) | O(N²) | Simpler but wasteful |
| Layer-by-layer rotation | O(N²) | O(1) | Also valid, more code |

**Layer-by-layer (for reference):**
```cpp
// Rotate each layer from outside in
for (int layer = 0; layer < n/2; layer++) {
    int first = layer, last = n - 1 - layer;
    for (int i = first; i < last; i++) {
        int offset = i - first;
        int top = matrix[first][i];
        matrix[first][i] = matrix[last-offset][first];     // left→top
        matrix[last-offset][first] = matrix[last][last-offset]; // bottom→left
        matrix[last][last-offset] = matrix[i][last];       // right→bottom
        matrix[i][last] = top;                             // top→right
    }
}
```

---

## 📚 Related Problems

- [ ] LeetCode #48 — Rotate Image
- [ ] LeetCode #54 — Spiral Matrix (P29)
- [ ] LeetCode #189 — Rotate Array (1D rotation)
- [ ] LeetCode #867 — Transpose Matrix

---

## 🏆 Pattern Category

`Arrays` · `Matrix` · `In-Place Transformation`

---

## 🎯 Difficulty Analysis

**Rating:** Medium

**Why challenging:** The brute force is obvious. The insight — decomposing into transpose + reverse — requires seeing the coordinate mapping `(i,j) → (j, N-1-i)` and recognizing that transpose achieves the first step and row-reversal achieves the second.

---

## 📈 Progression Insight

**Harder variant:** Rotate non-square M×N matrix — needs O(M×N) space (can't transpose in-place)

**Follow-up:** Rotate by arbitrary angle θ → affine transformation (graphics/ML)

**Pattern application:** The decomposition idea (complex op = sequence of simple ops) appears in: FFT, string rotation (reversal trick), matrix exponentiation

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Rotate N×N matrix 90° clockwise in-place  
> **Approach:** Step 1: Transpose (`swap(mat[i][j], mat[j][i])` for j > i). Step 2: Reverse each row.  
> **Key trick:** `(i,j) → transpose → (j,i) → row reverse → (j, N-1-i)` = clockwise 90°  
> **Time:** O(N²) | **Space:** O(1)  
> **Watch out for:** j starts at `i+1` in transpose; reversing rows not columns
