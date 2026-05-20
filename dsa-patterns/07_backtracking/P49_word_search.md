# P49 — Word Search and Grid Backtracking

## 1. First-Timer Explanation

### What Is It?
**Grid backtracking** extends DFS on a matrix to search for patterns (words) or enumerate valid paths. The key twist: you must temporarily "mark" visited cells during DFS to avoid revisiting, then restore them when backtracking. This pattern covers single-word search, multi-word search via Trie, and path enumeration.

### Analogy
Finding a path through a maze by drawing your path in pencil. When you hit a dead end, erase (backtrack) and try another direction. The pencil mark prevents you from walking in circles. The erase ensures you can try other paths that reuse the same tiles.

### Visual Walkthrough — Word Search "SEE"
```
Board:          Word: "SEE"
A B C E
S F C S
A D E E

Start DFS from (1,0)='S':
  (1,0)='S' → matches S, mark '#'
  Try (0,0)='A' → no match 'E', skip
  Try (2,0)='A' → no match, skip
  Try (1,1)='F' → no match, skip
  
Start DFS from (0,3)='E':
  (0,3) → 'E', not 'S', skip

Start DFS from (1,3)='S':
  (1,3)='S', matches S, mark '#'
  Try (0,3)='E' → matches E, mark '#'
    Try (0,2)='C' → no match, skip
    Try (1,3)='#' → already visited, skip
    [no 'E' found] → backtrack, restore (0,3)='E'
  Try (2,3)='E' → matches E, mark '#'
    Try (1,3)='#' → skip (marked)
    Try (2,2)='E' → matches E → Found! Return true
```

### When to Use
- "Does this word exist in the grid?"
- "Find all words from dictionary in grid"
- "Count/enumerate paths in grid satisfying pattern"
- "Longest path visiting each cell once"

### When NOT to Use
- Single-cell lookups → just scan
- Grid with no revisiting constraints → simple BFS/DFS

### Common Mistakes
1. Forgetting to restore the cell after backtracking
2. Checking bounds after accessing (should check BEFORE)
3. Not handling the "already visited" case (could revisit same cell)
4. For Word Search II: not pruning Trie branches that lead nowhere

---

## 2. Revision Card

**Recognition Signal:** "find word in grid", "path in grid", "grid backtracking"

**Core Idea:** DFS from each cell. Check character match + in-bounds + not visited. Mark cell (overwrite or use visited array), recurse 4 directions, restore on backtrack.

**Trigger Keywords:** word search, path, grid, board, revisit, visited

**Complexity:**
| Problem | Time | Space |
|---------|------|-------|
| Word Search (one word) | O(R×C × 4^L) | O(L) |
| Word Search II (Trie) | O(R×C × 4^L + W×L) | O(W×L) |

---

## 3. Interview Tell Signs

- "Does board contain word" → DFS from each start, mark+restore
- "Find all words in board" → Trie + DFS (Word Search II pattern)
- "Longest path in grid visiting each cell once" → DFS + backtracking with path length tracking
- "Count unique paths avoiding obstacles" → DP usually better than backtracking for counting

---

## 4. C++ Template

```cpp
#include <vector>
#include <string>
using namespace std;

// ── Single Word Search ───────────────────────────────────────────────────────
bool exist(vector<vector<char>>& board, string word) {
    int rows = board.size(), cols = board[0].size();
    int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
    
    function<bool(int,int,int)> dfs = [&](int r, int c, int idx) -> bool {
        if (idx == (int)word.size()) return true;
        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
        if (board[r][c] != word[idx]) return false;
        
        char tmp = board[r][c];
        board[r][c] = '#'; // mark visited
        
        bool found = false;
        for (auto& d : dirs)
            if (dfs(r + d[0], c + d[1], idx + 1)) { found = true; break; }
        
        board[r][c] = tmp; // restore
        return found;
    };
    
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (dfs(r, c, 0)) return true;
    return false;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I'll try starting the word at every cell in the board. From a starting cell, I do DFS: check if current cell matches current character, mark it visited by overwriting with '#', recurse in 4 directions, then restore the character. If I reach the end of the word, return true. The temporary mark prevents revisiting within the same path."

**Checklist:**
- [ ] Loop over all cells as potential starts
- [ ] DFS: check bounds + match before recursing
- [ ] Mark with '#', recurse, restore after
- [ ] Early termination: return true immediately when found
- [ ] For Word Search II: build Trie first, DFS follows Trie paths

---

## 6. Problems

### Problem 1: Word Search
**Difficulty:** Medium | **LC:** 79

**Approach:** DFS from each cell with backtracking mark/restore.

```cpp
bool exist(vector<vector<char>>& board, string word) {
    int rows = board.size(), cols = board[0].size();
    function<bool(int,int,int)> dfs = [&](int r, int c, int idx) -> bool {
        if (idx == (int)word.size()) return true;
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[idx]) return false;
        char tmp = board[r][c]; board[r][c] = '#';
        bool res = dfs(r+1,c,idx+1)||dfs(r-1,c,idx+1)||dfs(r,c+1,idx+1)||dfs(r,c-1,idx+1);
        board[r][c] = tmp;
        return res;
    };
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (dfs(r, c, 0)) return true;
    return false;
}
// Time: O(R*C * 4^L) | Space: O(L)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Word Search II (Find All Words)
**Difficulty:** Hard | **LC:** 212

**Approach:** Build Trie from word list. DFS on board following Trie. Add word to result when Trie node has a word.

```cpp
struct TrieNode {
    TrieNode* ch[26] = {};
    string word; // non-empty if this node ends a word
};

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    // Build Trie
    TrieNode* root = new TrieNode();
    for (auto& w : words) {
        TrieNode* cur = root;
        for (char c : w) {
            if (!cur->ch[c-'a']) cur->ch[c-'a'] = new TrieNode();
            cur = cur->ch[c-'a'];
        }
        cur->word = w;
    }
    
    int rows = board.size(), cols = board[0].size();
    vector<string> res;
    
    function<void(int,int,TrieNode*)> dfs = [&](int r, int c, TrieNode* node) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        char ch = board[r][c];
        if (ch == '#' || !node->ch[ch-'a']) return;
        
        TrieNode* next = node->ch[ch-'a'];
        if (!next->word.empty()) {
            res.push_back(next->word);
            next->word = ""; // avoid duplicates
        }
        
        board[r][c] = '#';
        dfs(r+1,c,next); dfs(r-1,c,next); dfs(r,c+1,next); dfs(r,c-1,next);
        board[r][c] = ch;
    };
    
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            dfs(r, c, root);
    return res;
}
// Time: O(R*C * 4^L) with Trie pruning | Space: O(W*L) Trie
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Unique Paths III
**Difficulty:** Hard | **LC:** 980

**Approach:** Backtracking: visit all non-obstacle cells exactly once, count paths from start to end.

```cpp
int uniquePathsIII(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    int startR, startC, empty = 0, count = 0;
    
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] != -1) empty++; // count non-obstacle cells
            if (grid[r][c] == 1) { startR = r; startC = c; }
        }
    
    function<void(int,int,int)> dfs = [&](int r, int c, int visited) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == -1) return;
        if (grid[r][c] == 2) {
            if (visited == empty) count++; // visited all non-obstacle cells
            return;
        }
        int tmp = grid[r][c];
        grid[r][c] = -1; // mark
        dfs(r+1,c,visited+1); dfs(r-1,c,visited+1);
        dfs(r,c+1,visited+1); dfs(r,c-1,visited+1);
        grid[r][c] = tmp; // restore
    };
    
    dfs(startR, startC, 1);
    return count;
}
// Time: O(4^(R*C)) | Space: O(R*C) stack
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Robot Room Cleaner
**Difficulty:** Hard | **LC:** 489

**Approach:** Spiral backtracking. Track visited cells by virtual coordinates. Robot can only move/turn.

```cpp
// API: robot.move(), robot.turnRight(), robot.turnLeft(), robot.clean()
void cleanRoom(Robot& robot) {
    set<pair<int,int>> visited;
    int dirs[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}; // up,right,down,left
    
    function<void(int,int,int)> dfs = [&](int r, int c, int dir) {
        robot.clean();
        visited.insert({r,c});
        
        for (int i = 0; i < 4; i++) {
            int nd = (dir + i) % 4;
            int nr = r + dirs[nd][0], nc = c + dirs[nd][1];
            if (!visited.count({nr,nc}) && robot.move()) {
                dfs(nr, nc, nd);
                // backtrack: turn around, move back, turn back
                robot.turnRight(); robot.turnRight();
                robot.move();
                robot.turnRight(); robot.turnRight();
            }
            robot.turnRight(); // try next direction
        }
    };
    
    dfs(0, 0, 0);
}
// Time: O(N) where N = number of cells | Space: O(N)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Word search: you temporarily set `board[r][c] = '#'`. What happens if you forget to restore it?
<details><summary>Reveal</summary>
The cell becomes permanently unusable for other starting positions or other DFS paths. You'd get wrong answers — some words that exist in the board would be reported as missing because the cells they need were incorrectly marked.
</details>

**Drill 2:** Why is Word Search II faster with a Trie than searching for each word separately?
<details><summary>Reveal</summary>
Without Trie: O(W × R×C × 4^L) — one DFS per word. With Trie: O(R×C × 4^L) — all words searched in a single DFS. The Trie branches prune impossible paths early (if no word starts with "XQ", DFS stops immediately at cells matching 'X' when next is 'Q').
</details>

**Drill 3:** For Unique Paths III, what's the base case and how do you count "all cells visited"?
<details><summary>Reveal</summary>
Base case: reach the end cell (value=2). Count all non-obstacle cells (value ≠ -1) upfront as `empty`. Pass a `visited` counter that increments with each step. If visited == empty when reaching the end, it's a valid path.
</details>

**Drill 4:** Robot Room Cleaner: why is backtracking harder here than regular grid DFS?
<details><summary>Reveal</summary>
You can't teleport back — you must physically drive the robot back. Backtracking means: turn 180°, move back, turn 180° again to restore orientation. The virtual coordinate system tracks where you are without the robot having global coordinates.
</details>

**Drill 5:** Pruning: in Word Search, if only 1 'A' exists in the board but word has 2 'A's, what optimization avoids wasted work?
<details><summary>Reveal</summary>
Count character frequencies in the board and word. If word needs more of any character than the board has, return false immediately before any DFS. O(R×C + L) check eliminates impossible cases.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Word Search I | O(R×C × 4^L) | O(L) |
| Word Search II | O(R×C × 4^L) with pruning | O(ΣW_i) Trie |
| Unique Paths III | O(4^(R×C)) | O(R×C) |
| Robot Cleaner | O(N × 4) | O(N) |

---

## 9. Common Follow-up Questions

**Q: What if the word can be matched along any direction (diagonal too)?**
A: Change `dirs` to 8-directional: add `{1,1},{1,-1},{-1,1},{-1,-1}`.

**Q: What if the word can only be placed horizontally or vertically (no turning)?**
A: Fix the direction at the first step. Only recurse in the chosen direction.

**Q: Word Search with wildcards ('.' matches any character)?**
A: In the DFS match condition, change `board[r][c] != word[idx]` to `board[r][c] != word[idx] && word[idx] != '.'`.

**Q: How do you optimize for repeated DFS calls from the same starting cell?**
A: Memoization (if state is fully captured by (r, c, word_index, visited_bitmask)) — but the bitmask makes this O(R×C × 2^(R×C)) which is worse unless grid is tiny.

---

## 10. Cross-Pattern Connections

- **P48 (N-Queens):** Same backtracking skeleton with constraint checking
- **P18 (DFS Connected Components):** Grid DFS without backtracking (no restore needed — permanent marking)
- **P86 (Trie):** Word Search II relies on Trie for multi-word pruning
- **P46 (Subsets):** Both build solutions incrementally, backtrack when stuck
- **P19 (BFS):** BFS finds shortest word path; DFS/backtracking finds existence or all paths
