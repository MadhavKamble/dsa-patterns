/*
 * ============================================================
 * TEMPLATE: Dynamic Programming
 * ============================================================
 * Use when: problem has OVERLAPPING SUBPROBLEMS and
 *           OPTIMAL SUBSTRUCTURE
 * Recognition: "count ways", "min/max cost", "can we achieve X",
 *              "longest/shortest subsequence"
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: 1D DP — Fibonacci Style
// ─────────────────────────────────────────────────────────────
// dp[i] depends only on dp[i-1] and/or dp[i-2]

int climbStairs(int n) {
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;  // dp[1]=1, dp[2]=2

    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2;  // can reach step i from i-1 or i-2
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: 1D DP — Kadane's (max subarray)
// ─────────────────────────────────────────────────────────────
// Decision at each element: extend existing subarray OR start fresh

int maxSubarray(vector<int>& nums) {
    int curr = nums[0];    // max subarray ending at current position
    int best = nums[0];    // global answer

    for (int i = 1; i < (int)nums.size(); i++) {
        // extend if curr is positive, else start fresh from nums[i]
        curr = max(nums[i], curr + nums[i]);
        best = max(best, curr);
    }
    return best;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: 1D DP — Unbounded Knapsack (Coin Change)
// ─────────────────────────────────────────────────────────────
// dp[i] = min coins to make amount i; each coin usable unlimited times

int coinChange(vector<int>& coins, int amount) {
    // dp[i] = minimum coins to make amount i
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;  // 0 coins needed to make amount 0

    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return (dp[amount] == INT_MAX) ? -1 : dp[amount];
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: 2D DP — 0/1 Knapsack (Subset Sum)
// ─────────────────────────────────────────────────────────────
// dp[i][j] = can we make sum j using first i elements?
// OPTIMIZED: use 1D rolling array

bool canPartition(vector<int>& nums) {
    int total = 0;
    for (int x : nums) total += x;
    if (total % 2 != 0) return false;  // odd total → can't split equally

    int target = total / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;  // sum 0 is always achievable (take nothing)

    for (int num : nums) {
        // iterate RIGHT TO LEFT to avoid using same element twice
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
            // dp[j]: can we make j without using num?  (dp[j] unchanged)
            // dp[j-num]: can we make j by including num?
        }
    }
    return dp[target];
}

// ─────────────────────────────────────────────────────────────
// VARIANT 5: 2D DP — LCS / Edit Distance
// ─────────────────────────────────────────────────────────────

int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    // dp[i][j] = LCS of text1[0..i-1] and text2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;  // characters match: extend LCS
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);  // skip one char
            }
        }
    }
    return dp[m][n];
}

int editDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    // dp[i][j] = min ops to convert word1[0..i-1] to word2[0..j-1]
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // base cases: converting to/from empty string
    for (int i = 0; i <= m; i++) dp[i][0] = i;  // delete all chars of word1
    for (int j = 0; j <= n; j++) dp[0][j] = j;  // insert all chars of word2

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i-1] == word2[j-1]) {
                dp[i][j] = dp[i-1][j-1];  // no operation needed
            } else {
                dp[i][j] = 1 + min({
                    dp[i-1][j],    // delete from word1
                    dp[i][j-1],    // insert into word1
                    dp[i-1][j-1]   // replace
                });
            }
        }
    }
    return dp[m][n];
}

// ─────────────────────────────────────────────────────────────
// VARIANT 6: 2D DP — Grid Path (Unique Paths)
// ─────────────────────────────────────────────────────────────

int uniquePaths(int m, int n) {
    // dp[i][j] = ways to reach cell (i,j) from (0,0)
    vector<vector<int>> dp(m, vector<int>(n, 1));
    // first row and column have exactly 1 way (only right or only down)

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];  // from above + from left
        }
    }
    return dp[m-1][n-1];
}

// ─────────────────────────────────────────────────────────────
// VARIANT 7: LIS — Longest Increasing Subsequence
// ─────────────────────────────────────────────────────────────

int lengthOfLIS(vector<int>& nums) {
    // tails[i] = smallest tail element of all LIS of length i+1
    vector<int> tails;

    for (int num : nums) {
        // find first tail >= num: replace it with num (patience sort)
        auto it = lower_bound(tails.begin(), tails.end(), num);

        if (it == tails.end()) {
            tails.push_back(num);  // num extends the longest sequence
        } else {
            *it = num;  // replace: makes future extensions easier
        }
    }
    return tails.size();  // tails.size() = length of LIS
}

/*
 * ─────────────────────────────────────────────────────────────
 * DP PROBLEM-SOLVING FRAMEWORK
 * ─────────────────────────────────────────────────────────────
 *
 *  STEP 1: Define dp[i] or dp[i][j] clearly in English
 *  STEP 2: Write the recurrence relation
 *  STEP 3: Identify base cases
 *  STEP 4: Determine traversal order (forward? backward? row-by-row?)
 *  STEP 5: Extract final answer from dp table
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. 0/1 knapsack: iterate j from target DOWN to num (not up)
 *     Iterating up means you can use same item multiple times
 *  2. Unbounded knapsack: iterate j UP (reusing items is OK)
 *  3. LCS: 1-indexed vs 0-indexed — dp size is (m+1) x (n+1)
 *  4. Kadane: initialize curr and best to nums[0], not 0
 *     (handles all-negative arrays)
 *  5. LIS binary search: use lower_bound for strict increasing
 *     use upper_bound for non-decreasing
 */
