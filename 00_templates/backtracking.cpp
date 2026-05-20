/*
 * ============================================================
 * TEMPLATE: Backtracking
 * ============================================================
 * Use when: generate ALL valid combinations/permutations/subsets,
 *           explore decision tree, constraint satisfaction
 * Time: O(2^n) subsets, O(n!) permutations — inherently exponential
 * Space: O(n) recursion depth
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// UNIVERSAL BACKTRACKING SKELETON
// ─────────────────────────────────────────────────────────────
/*
 * void backtrack(state, choices) {
 *     if (isGoalState(state)) {
 *         results.push_back(state);
 *         return;
 *     }
 *     for (each choice in choices) {
 *         if (isValid(choice, state)) {
 *             makeChoice(choice, state);     // CHOOSE
 *             backtrack(state, newChoices);  // EXPLORE
 *             undoChoice(choice, state);     // UNCHOOSE (backtrack)
 *         }
 *     }
 * }
 */

// ─────────────────────────────────────────────────────────────
// VARIANT 1: SUBSETS (include/exclude)
// ─────────────────────────────────────────────────────────────

vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> curr;

    function<void(int)> bt = [&](int start) {
        result.push_back(curr);  // add current subset (even empty)

        for (int i = start; i < (int)nums.size(); i++) {
            curr.push_back(nums[i]);  // CHOOSE: include nums[i]
            bt(i + 1);                // EXPLORE: pick from remaining
            curr.pop_back();          // UNCHOOSE: remove nums[i]
        }
    };

    bt(0);
    return result;
}

// Subsets with duplicates — sort first, skip duplicates at same level
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());  // sort to group duplicates
    vector<vector<int>> result;
    vector<int> curr;

    function<void(int)> bt = [&](int start) {
        result.push_back(curr);

        for (int i = start; i < (int)nums.size(); i++) {
            // skip duplicate at same recursion level
            if (i > start && nums[i] == nums[i - 1]) continue;

            curr.push_back(nums[i]);
            bt(i + 1);
            curr.pop_back();
        }
    };

    bt(0);
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: PERMUTATIONS
// ─────────────────────────────────────────────────────────────

vector<vector<int>> permutations(vector<int>& nums) {
    vector<vector<int>> result;
    vector<bool> used(nums.size(), false);
    vector<int> curr;

    function<void()> bt = [&]() {
        if (curr.size() == nums.size()) {
            result.push_back(curr);
            return;
        }

        for (int i = 0; i < (int)nums.size(); i++) {
            if (used[i]) continue;  // skip already used elements

            used[i] = true;          // CHOOSE
            curr.push_back(nums[i]);
            bt();                    // EXPLORE
            curr.pop_back();         // UNCHOOSE
            used[i] = false;
        }
    };

    bt();
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: COMBINATION SUM (elements can repeat)
// ─────────────────────────────────────────────────────────────

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> curr;

    function<void(int, int)> bt = [&](int start, int remaining) {
        if (remaining == 0) {
            result.push_back(curr);
            return;
        }
        if (remaining < 0) return;  // pruning: exceeded target

        for (int i = start; i < (int)candidates.size(); i++) {
            curr.push_back(candidates[i]);
            bt(i, remaining - candidates[i]);  // i not i+1: can reuse element
            curr.pop_back();
        }
    };

    bt(0, target);
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: GENERATE PARENTHESES
// ─────────────────────────────────────────────────────────────

vector<string> generateParentheses(int n) {
    vector<string> result;
    string curr = "";

    function<void(int, int)> bt = [&](int open, int close) {
        if (curr.size() == 2 * n) {
            result.push_back(curr);
            return;
        }

        // can add '(' if we haven't used all n open parens
        if (open < n) {
            curr += '(';
            bt(open + 1, close);
            curr.pop_back();
        }
        // can add ')' only if there are more open than close
        if (close < open) {
            curr += ')';
            bt(open, close + 1);
            curr.pop_back();
        }
    };

    bt(0, 0);
    return result;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 5: WORD SEARCH IN GRID
// ─────────────────────────────────────────────────────────────

bool wordSearch(vector<vector<char>>& board, string word) {
    int rows = board.size(), cols = board[0].size();
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    function<bool(int, int, int)> bt = [&](int r, int c, int idx) -> bool {
        if (idx == (int)word.size()) return true;  // all chars matched
        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;
        if (board[r][c] != word[idx]) return false;

        char tmp = board[r][c];
        board[r][c] = '#';  // mark as visited

        bool found = false;
        for (int d = 0; d < 4 && !found; d++) {
            found = bt(r + dr[d], c + dc[d], idx + 1);
        }

        board[r][c] = tmp;  // RESTORE — backtrack
        return found;
    };

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (bt(r, c, 0)) return true;
        }
    }
    return false;
}

/*
 * ─────────────────────────────────────────────────────────────
 * PRUNING STRATEGIES (essential for efficiency)
 * ─────────────────────────────────────────────────────────────
 *  1. SORT + skip duplicates: for subsets/combinations with duplicates
 *  2. EARLY TERMINATION: return when remaining < 0 or state is invalid
 *  3. USED ARRAY: track which elements are in current path (permutations)
 *  4. START INDEX: pass start to avoid re-picking earlier elements (subsets)
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Forgetting to UNDO the choice after recursive call (backtrack)
 *  2. Duplicate subsets: not sorting + skipping i > start && same as prev
 *  3. Permutations vs combinations: permutations need used[], combinations need start
 *  4. Grid DFS: not restoring cell value after backtrack
 *  5. Combination sum: pass 'i' not 'i+1' when elements can be reused
 */
