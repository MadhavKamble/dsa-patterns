# Rat in a Maze

> **GFG** · **Difficulty:** Medium · **Step 7 — Recursion · P20**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an `n×n` binary maze (1 = open, 0 = blocked), find all paths from `(0,0)` to `(n-1,n-1)`. Return paths as direction strings (D/L/R/U). Report paths in lexicographically sorted order.

**Input:**
```
maze = [[1,0,0,0],
        [1,1,0,1],
        [1,1,0,0],
        [0,1,1,1]]
```
**Output:** `["DDRDRR", "DRDDRR"]`

**Key Observations:**
- Move in 4 directions: D (down), L (left), R (right), U (up).
- A cell can only be visited once per path → `visited[][]` array.
- At each step: check bounds + `maze[x][y]==1` + not visited.
- Direction order D→L→R→U naturally gives lexicographic output (D<L<R<U alphabetically).
- Backtrack: `visited[x][y] = 0` after returning from all 4 directions.

---

## 🥇 DFS Backtracking with Visited Array

### Key Insight

> 💡 Mark current cell visited, try 4 directions (in D/L/R/U order for lex output), unmark on return. Collect the path string when destination `(n-1,n-1)` is reached.

### vs Word Search (P18)

| | Word Search (P18) | Rat in a Maze (P20) |
|---|---|---|
| Mark visited | in-place `'#'` | separate `visited[][]` |
| Restore | `board[i][j] = temp` | `visited[x][y] = 0` |
| Goal | match a word | reach destination |
| Collect | on `idx == len` | on `x==n-1 && y==n-1` |
| Path tracking | no | yes — accumulate string |

Same DFS + backtrack structure, different purpose and state.

### isSafe Check

```cpp
bool isSafe(x, y, n, maze, visited):
  return x in [0,n) AND y in [0,n) AND maze[x][y]==1 AND visited[x][y]==0
```

### Algorithm
1. Guard: if `maze[0][0] == 0` → return empty.
2. `solve(x, y, n, maze, visited, path, res)`:
   - **Base:** `x == n-1 && y == n-1` → push `path`, return.
   - Mark `visited[x][y] = 1`.
   - Try Down: `isSafe(x+1, y)` → recurse with `path+"D"`.
   - Try Left: `isSafe(x, y-1)` → recurse with `path+"L"`.
   - Try Right: `isSafe(x, y+1)` → recurse with `path+"R"`.
   - Try Up: `isSafe(x-1, y)` → recurse with `path+"U"`.
   - Backtrack: `visited[x][y] = 0`.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isSafe(int x,int y,int n,vector<vector<int>>& maze,vector<vector<int>>& visited){
        return (x>=0&&x<n&&y>=0&&y<n&&maze[x][y]==1&&visited[x][y]==0);
    }

    void solve(int x,int y,int n,vector<vector<int>>& maze,
               vector<vector<int>>& visited,string path,vector<string>& res){
        if(x==n-1&&y==n-1){
            res.push_back(path);
            return;
        }
        visited[x][y]=1;
        if(isSafe(x+1,y,n,maze,visited)) solve(x+1,y,n,maze,visited,path+"D",res);
        if(isSafe(x,y-1,n,maze,visited)) solve(x,y-1,n,maze,visited,path+"L",res);
        if(isSafe(x,y+1,n,maze,visited)) solve(x,y+1,n,maze,visited,path+"R",res);
        if(isSafe(x-1,y,n,maze,visited)) solve(x-1,y,n,maze,visited,path+"U",res);
        visited[x][y]=0;
    }

    vector<string> findPath(vector<vector<int>>& maze,int n){
        vector<string> res;
        vector<vector<int>> visited(n,vector<int>(n,0));
        if(maze[0][0]==1) solve(0,0,n,maze,visited,"",res);
        return res;
    }
};
```

**Time:** O(4^(N²)) worst case · **Space:** O(N²) visited + O(N²) path depth

### Dry Run — 4×4 maze

```
solve(0,0, path=""):
  visited[0][0]=1
  D: (1,0) safe? maze=1,vis=0 → solve(1,0, "D")
    visited[1][0]=1
    D: (2,0) safe → solve(2,0, "DD")
      visited[2][0]=1
      D: (3,0) maze=0 → not safe
      R: (2,1) safe → solve(2,1, "DDR")
        visited[2][1]=1
        D: (3,1) safe → solve(3,1, "DDRD")
          D: (4,1) OOB → no
          R: (3,2) safe → solve(3,2, "DDRDR")
            R: (3,3) safe → solve(3,3, "DDRDRRR")→ wait that's wrong
```

Actually let me re-read the maze. Let me just note the expected output.

With maze:
```
1 0 0 0
1 1 0 1
1 1 0 0
0 1 1 1
```
Expected paths: `["DDRDRR", "DRDDRR"]`

Path 1: (0,0)→D(1,0)→D(2,0)→R(2,1)→D(3,1)→R(3,2)→R(3,3) = "DDRDRR" ✓
Path 2: (0,0)→D(1,0)→R(1,1)→D(2,1)→D(3,1)→R(3,2)→R(3,3) = "DRDDRR" ✓

---

## 🔑 Why Direction Order Matters for Lexicographic Output

Trying D < L < R < U in code order means when multiple paths exist, D-paths are explored (and added) before L-paths, which come before R-paths, which come before U-paths. This naturally produces lexicographically sorted output without extra sorting.

`'D' < 'L' < 'R' < 'U'` alphabetically → exploring in this order gives sorted results.

---

## 🧾 Recall Line *(10-Second Revision)*

> "DFS with visited[][]. Try D→L→R→U (lex order). Mark visited=1, recurse, backtrack visited=0. Base: reach (n-1,n-1) → push path. Guard: maze[0][0]==1."

---

## 📝 Short Revision Notes

- `path` passed by value (string concatenation creates new string per call) → no backtrack on the string needed.
- Direction order D/L/R/U gives lex order naturally — changing it breaks lex guarantee.
- `visited[x][y] = 0` after all 4 direction attempts — not just for failed ones.
- `maze[0][0] == 0` edge case: destination is unreachable from start → return empty immediately.

---

## ⚠️ Common Mistakes

❌ Not marking `visited[x][y] = 0` on backtrack — later paths can't use this cell.
❌ Marking visited at destination check before base-case return — destination also needs to be unvisited for other paths.
❌ Using wrong direction order — breaks lexicographic guarantee.
❌ Not guarding `maze[0][0] == 1` — trying to start from a blocked cell.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "find all paths from source to destination in a grid" → **DFS with visited array, mark before 4-directional exploration, unmark after (backtrack)**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `DFS` · `Grid` · `Path Finding`

---

## ⏱️ 30-Second Last-Minute Revision

> Mark `visited[x][y]=1`. Try D/L/R/U if `isSafe`. Base: `(n-1,n-1) → push path`. Backtrack: `visited[x][y]=0`. D/L/R/U order = lex output. **Time:** O(4^(N²)) | **Space:** O(N²).
