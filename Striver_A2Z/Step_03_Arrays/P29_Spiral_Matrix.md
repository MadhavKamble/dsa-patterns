# 🔥 Print the Matrix in Spiral Order

> **LeetCode #54** · **Difficulty:** Medium · **Step 3 — Arrays · P29**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an M×N matrix, return all its elements in **spiral order** — traversing the outermost layer clockwise, then the next inner layer, and so on.

**Input:**
```
[[1,  2,  3,  4],
 [5,  6,  7,  8],
 [9,  10, 11, 12]]
```
**Output:** `[1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7]`

**Constraints:** `1 ≤ M, N ≤ 10`

**Key Observations:**
- Spiral = top row → right column → bottom row (reversed) → left column (reversed) → shrink boundaries → repeat
- Need 4 boundary pointers: `top`, `bottom`, `left`, `right`
- Must guard against processing a single row or column twice when boundaries cross

**Simple Example (3×3):**
```
1 2 3
4 5 6      → [1,2,3, 6,9, 8,7, 4, 5]
7 8 9
```

---

## 🥉 Brute Force Approach

### Idea
Use a visited matrix. Simulate the spiral direction (right → down → left → up → repeat), change direction when hitting a wall or visited cell.

### Complexity
- **Time:** O(M × N)
- **Space:** O(M × N) — visited array

### C++ Code
```cpp
// BRUTE FORCE: direction simulation with visited array
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<int> result;
    int dr[] = {0, 1, 0, -1};   // right, down, left, up
    int dc[] = {1, 0, -1, 0};
    int r = 0, c = 0, dir = 0;

    for (int i = 0; i < m * n; i++) {
        result.push_back(matrix[r][c]);
        visited[r][c] = true;
        int nr = r + dr[dir], nc = c + dc[dir];
        if (nr < 0 || nr >= m || nc < 0 || nc >= n || visited[nr][nc]) {
            dir = (dir + 1) % 4;    // change direction
            nr = r + dr[dir]; nc = c + dc[dir];
        }
        r = nr; c = nc;
    }
    return result;
}
```

---

## 🥇 Optimal Approach — Four Boundary Pointers

### Key Observation

> 💡 Maintain four shrinking boundaries: `top`, `bottom`, `left`, `right`. In each iteration, process one full "layer":
> 1. **Top row:** left → right, then `top++`
> 2. **Right column:** top → bottom, then `right--`
> 3. **Bottom row** (if `top <= bottom`): right → left, then `bottom--`
> 4. **Left column** (if `left <= right`): bottom → top, then `left++`
>
> The guards on steps 3 and 4 prevent double-counting when a single row or column remains.

### Algorithm
1. `top=0, bottom=M-1, left=0, right=N-1`
2. While `top <= bottom` AND `left <= right`:
   - Traverse top row: `j` from `left` to `right`, then `top++`
   - Traverse right column: `i` from `top` to `bottom`, then `right--`
   - If `top <= bottom`: traverse bottom row: `j` from `right` to `left`, then `bottom--`
   - If `left <= right`: traverse left column: `i` from `bottom` to `top`, then `left++`

### Dry Run

**Input:**
```
 1  2  3  4
 5  6  7  8
 9 10 11 12
```
M=3, N=4, `top=0, bot=2, left=0, right=3`

**Iteration 1:**
- Top row (left→right): `1,2,3,4` → `top=1`
- Right col (top→bot): `8,12` → `right=2`
- Bottom row (guard: `top=1 ≤ bot=2` ✅, right→left): `11,10,9` → `bot=1`
- Left col (guard: `left=0 ≤ right=2` ✅, bot→top): `5` → `left=1`

Result so far: `[1,2,3,4,8,12,11,10,9,5]`

**Iteration 2:** `top=1, bot=1, left=1, right=2`
- Top row: `6,7` → `top=2`
- Right col (top=2 > bot=1): nothing → `right=1`
- Guard `top=2 > bot=1` ❌ — skip bottom row
- Guard `left=1 ≤ right=1` ✅ — Left col (bot=1 to top=2-1=1): nothing since `bot < top`... → `left=2`

Wait, let me redo iteration 2 more carefully:

`top=1, bot=1, left=1, right=2`
- Top row (j=1..2): `6, 7` → `top=2`
- Right col (i=2..1, i.e., top=2 > bot=1): no elements → `right=1`
- Guard `top=2 > bot=1` ❌ — skip bottom row
- Guard `left=1 ≤ right=1` ✅ — Left col (i=bot=1 downto top=2): since `bot=1 < top=2`, no elements → `left=2`

Now `left=2 > right=1` → loop ends.

Final: `[1,2,3,4,8,12,11,10,9,5,6,7]` ✅

### Complexity
- **Time:** O(M × N) — every element is visited exactly once
- **Space:** O(1) extra (output not counted)

---

## 🎤 Interview Explanation Script

> "The brute force simulates the spiral with direction vectors and a visited array — O(M×N) space."

> "The optimal approach uses four boundary pointers: top, bottom, left, right. In each round, I traverse the outermost layer: top row, right column, bottom row, left column — then shrink all four boundaries inward."

> "The critical detail: before traversing the bottom row and left column, I check if the boundaries haven't crossed. This prevents double-counting when a single row or column remains in the center."

> "Every element is added exactly once, so time is O(M×N) and space is O(1) extra."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * SPIRAL MATRIX — four shrinking boundary pointers
 *
 * PROBLEM UNDERSTANDING:
 *   Traverse M×N matrix in clockwise spiral order.
 *
 * EDGE CASES:
 *   - Single row: top==bottom, only traverse once (no bottom row pass)
 *   - Single column: left==right, only traverse once (no right col pass)
 *   - 1×1: single element
 *
 * KEY: Guards on bottom row (top<=bottom) and left col (left<=right)
 *      prevent double-counting the middle row/column.
 *
 * COMPLEXITY: Time O(M*N) | Space O(1) extra
 */
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {
            // 1. traverse top row: left → right
            for (int j = left; j <= right; j++)
                result.push_back(matrix[top][j]);
            top++;

            // 2. traverse right column: top → bottom
            for (int i = top; i <= bottom; i++)
                result.push_back(matrix[i][right]);
            right--;

            // 3. traverse bottom row: right → left (guard: rows still remain)
            if (top <= bottom) {
                for (int j = right; j >= left; j--)
                    result.push_back(matrix[bottom][j]);
                bottom--;
            }

            // 4. traverse left column: bottom → top (guard: cols still remain)
            if (left <= right) {
                for (int i = bottom; i >= top; i--)
                    result.push_back(matrix[i][left]);
                left++;
            }
        }

        return result;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "4 boundaries. Top row → right col → bottom row (guard top≤bot) → left col (guard left≤right). Shrink after each."

---

## 📝 Short Revision Notes

- Process order: top row, right col, bottom row, left col
- Increment/decrement boundaries immediately after each traversal
- Guards prevent double-adding middle row/col for odd-dimension matrices
- `top++` before traversing right col — right col range is now `[top, bottom]` after shrink
- Works for rectangular (M×N) matrices — no square requirement

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Spiral traversal", "layer by layer"
- "Print matrix in order", "simulate a path"
- "Shrinking boundaries"

**I should think of:** Four boundary pointers with guard conditions

---

## ⚠️ Common Mistakes

❌ Missing guard `if (top <= bottom)` before bottom row — double-counts middle row  
❌ Missing guard `if (left <= right)` before left col — double-counts middle col  
❌ Updating boundaries in wrong order (e.g., `top++` after right col instead of after top row)  
❌ Off-by-one in loop bounds: `j <= right` not `j < right`  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Layer-by-layer boundary shrinking
- **Reasoning:** Why guards are needed for non-square or odd-dimension matrices
- **Attention to detail:** Getting all four traversal directions and boundary updates correct

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Boundary pointers (optimal) | O(MN) | O(1) | Best — clean and general |
| Direction simulation + visited | O(MN) | O(MN) | More intuitive, more space |
| Recursive layer peeling | O(MN) | O(min(M,N)) stack | Elegant but stack overhead |

---

## 📚 Related Problems

- [ ] LeetCode #54 — Spiral Matrix
- [ ] LeetCode #59 — Spiral Matrix II (fill matrix in spiral order)
- [ ] LeetCode #885 — Spiral Matrix III
- [ ] Striver Step 3 P28 — Rotate Matrix 90°

---

## 🏆 Pattern Category

`Arrays` · `Matrix` · `Simulation` · `Two Pointers`

---

## 🎯 Difficulty Analysis

**Rating:** Medium

**Why challenging:** The four-direction traversal with correct boundary updates and edge-case guards requires careful bookkeeping. The common mistake (double-counting middle rows/columns) is subtle.

---

## 📈 Progression Insight

**Harder variant:** LC #59 — Spiral Matrix II: fill a matrix with 1..N² in spiral order. Same boundary logic, just writing instead of reading.

**Pattern application:** The boundary-shrinking idea generalizes to "peeling" problems: onion layers, game of life, Conway's Game of Life boundaries.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Traverse M×N matrix in spiral order  
> **Approach:** 4 boundaries (top/bot/left/right). Top row→right col→bottom row (if top≤bot)→left col (if left≤right). Shrink after each side.  
> **Key trick:** Guards prevent double-counting single middle row/col  
> **Time:** O(MN) | **Space:** O(1) extra  
> **Watch out for:** `top++` after top row, NOT after right col
