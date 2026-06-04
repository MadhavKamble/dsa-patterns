# 🔥 Pascal's Triangle

> **LeetCode #118, #119, #1** (3 variants) · **Difficulty:** Easy-Medium · **Step 3 — P30**

---

## 🧠 Problem Understanding

Pascal's Triangle: each element = sum of the two elements directly above it. Row `r`, Col `c` = `C(r, c) = r! / (c! * (r-c)!)`.

```
Row 0:     1
Row 1:    1 1
Row 2:   1 2 1
Row 3:  1 3 3 1
Row 4: 1 4 6 4 1
```

**Three variants asked in interviews:**
1. Print entire triangle up to N rows
2. Print Nth row
3. Find element at row R, column C

---

## 🥇 Variant 1 — Print Full Triangle (N rows)

```cpp
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> triangle;
    for (int i = 0; i < numRows; i++) {
        vector<int> row(i + 1, 1);           // all 1s
        for (int j = 1; j < i; j++)
            row[j] = triangle[i-1][j-1] + triangle[i-1][j];
        triangle.push_back(row);
    }
    return triangle;
}
// Time O(N²) | Space O(N²)
```

---

## 🥇 Variant 2 — Print Nth Row Only

### Key Observation
> 💡 Row N has elements `C(N-1, 0), C(N-1, 1), ..., C(N-1, N-1)`.  
> Use the multiplicative formula: `C(n, k) = C(n, k-1) × (n-k+1) / k`  
> Start from `C(n,0)=1`, build incrementally.

```cpp
vector<int> getRow(int rowIndex) {           // 0-indexed
    vector<int> row(rowIndex + 1);
    row[0] = 1;
    for (int k = 1; k <= rowIndex; k++)
        row[k] = (long long)row[k-1] * (rowIndex - k + 1) / k;
    return row;
}
// Time O(N) | Space O(N)
```

---

## 🥇 Variant 3 — Element at Row R, Column C

### Key Observation
> 💡 `element = C(R-1, C-1)` (1-indexed). Use multiplicative formula starting from 1.

```cpp
long long nCr(int n, int r) {
    long long result = 1;
    for (int i = 0; i < r; i++) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}
// Time O(R) | Space O(1)
// C(R-1, C-1) for 1-indexed (R, C)
```

---

## 💻 Clean C++ Code (All 3 Variants)

```cpp
/*
 * PASCAL'S TRIANGLE — 3 variants
 * Core formula: C(n,k) = C(n,k-1) * (n-k+1) / k
 * Multiply THEN divide to avoid intermediate overflow (integer division exact here)
 */
class Solution {
public:
    // Variant 1: Full triangle
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> tri;
        for (int i = 0; i < numRows; i++) {
            vector<int> row(i + 1, 1);
            for (int j = 1; j < i; j++)
                row[j] = tri[i-1][j-1] + tri[i-1][j];
            tri.push_back(row);
        }
        return tri;
    }

    // Variant 2: Just the Nth row (0-indexed)
    vector<int> getRow(int n) {
        vector<int> row = {1};
        for (int k = 1; k <= n; k++) {
            row.push_back((long long)row.back() * (n - k + 1) / k);
        }
        return row;
    }

    // Variant 3: Element at (r, c) 1-indexed
    long long element(int r, int c) {
        return nCr(r - 1, c - 1);
    }

private:
    long long nCr(int n, int r) {
        long long result = 1;
        for (int i = 0; i < r; i++) {
            result = result * (n - i) / (i + 1);
        }
        return result;
    }
};
```

---

## 🧾 Recall Line
> "Pascal's = C(r,c). Build row: `row[k] = row[k-1] * (n-k+1) / k` starting from 1."

## 📝 Short Revision Notes
- Each element = sum of two above = `C(row, col)`
- Multiplicative formula avoids factorial overflow
- Divide after multiply to keep integer arithmetic exact
- `C(n, k) = C(n, k-1) * (n-k+1) / k` — building row incrementally
- Variant 2 needs only O(N) time/space vs O(N²) for full triangle

## ⚠️ Common Mistakes
❌ Using `row[k] = row[k-1] * (n-k) / k` — off by one in numerator  
❌ Dividing before multiplying in integer arithmetic — loses precision  
❌ Not casting to `long long` before multiplication

## 🏆 Pattern Category
`Arrays` · `Math` · `Combinatorics`

## ⏱️ 30-Second Revision
> Full: `row = [1]*i, row[j] = above[j-1]+above[j]`. Nth row: `row[k] = row[k-1]*(n-k+1)/k`. Element: `C(r-1, c-1)`.
