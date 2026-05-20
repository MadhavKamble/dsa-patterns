# Pattern 37: DP on Sequences (Stock Problems, State Machine DP)

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 121. Best Time to Buy and Sell Stock | Easy | https://leetcode.com/problems/best-time-to-buy-and-sell-stock/ |
| 2 | 122. Best Time to Buy and Sell Stock II | Medium | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/ |
| 3 | 123. Best Time to Buy and Sell Stock III | Hard | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/ |
| 4 | 188. Best Time to Buy and Sell Stock IV | Hard | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/ |
| 5 | 309. Best Time to Buy and Sell Stock with Cooldown | Medium | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/ |
| 6 | 714. Best Time to Buy and Sell Stock with Transaction Fee | Medium | https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**State Machine DP** models sequences where you're in one of several "states" at each step, and transitions between states have costs. The stock problems are the canonical example.

**Stock State Machine:**
At each day, you're in one of two states:
- **Holding stock** (just bought or still holding)
- **Not holding stock** (just sold or never bought)

Transitions:
- Not holding → Buy → Holding (cost = price)
- Holding → Sell → Not holding (gain = price)
- Stay in current state (do nothing)

**General form:**
```
hold[i] = max(hold[i-1], not_hold[i-1] - price[i])  // keep holding or buy today
rest[i] = max(rest[i-1], hold[i-1] + price[i])       // keep resting or sell today
```

**With k transactions limit**: add dimension k to state: `hold[i][k]` and `rest[i][k]`.

**With cooldown**: selling forces a 1-day rest → `rest[i]` depends on `hold[i-1]` but `hold[i]` depends on `rest[i-2]`.

### Visual Walkthrough
```
State Machine for LC 121 (one transaction):
prices = [7, 1, 5, 3, 6, 4]

State: (hold, sold) at each day

Day 0: hold = -7 (buy), sold = 0 (do nothing)
Day 1: hold = max(-7, 0-1) = max(-7, -1) = -1 (buy at 1 is better!)
        sold = max(0, -7+1) = 0 (selling at 1 with buy at 7 = loss, skip)
Day 2: hold = max(-1, 0-5) = -1 (keep holding at 1)
        sold = max(0, -1+5) = 4 (sell at 5, bought at 1, profit=4)
Day 3: hold = max(-1, 4-3) = 1? but can't rebuy after selling in one-transaction...
→ For one transaction: track minPrice separately
   profit = max(0, price[i] - minPrice)

For unlimited transactions (LC 122):
Day 1: hold=-1, sold=0
Day 2: hold=-1, sold=max(0,-1+5)=4
Day 3: hold=max(-1,4-3)=1, sold=max(4,...)=4
...
```

### When TO use this pattern
- Sequential decisions with constraints (at most k transactions, cooldown)
- Any "sequence of buy/sell" optimization
- State transitions along a timeline
- "Maximum profit with constraints" on stock sequence

### When NOT to use this pattern
- No sequential constraint (just find max - min)
- Geometric or combinatorial problems
- Non-temporal data

### Common Beginner Mistakes
- **LC 121**: just track minPrice and max profit — no DP needed
- **LC 122**: greedy works — collect every positive day gain
- **Cooldown**: `hold` depends on `rest[i-2]`, not `rest[i-1]`
- **K transactions**: initialize properly; when k >= n/2, it's equivalent to unlimited

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "buy and sell stock", "at most k transactions", "cooldown", "transaction fee" |
| Core Idea | State machine: held/not-held; transition = buy/sell/hold; track state per day |
| Trigger Keywords | "maximum profit", "stock", "transaction", "cooldown", "fee" |
| Avoid When | Single decision (no sequence), not a temporal problem |
| Time Complexity | O(n) or O(n×k) |
| Space Complexity | O(1) or O(k) rolling |

**Gotchas:**
- LC 122 (unlimited): greedy or simple DP (hold/rest without k limit)
- LC 123 (k=2): two separate (hold, sold) pairs; track buy1, sold1, buy2, sold2
- LC 309 (cooldown): rest[i] = max(rest[i-1], hold[i-1]+price); hold[i] = max(hold[i-1], rest[i-2] - price)
- LC 714 (fee): sell gets price - fee subtracted; same structure as unlimited

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"best time to buy and sell stock"` → stock DP (identify variant by constraints)
- `"at most k transactions"` → k-transaction DP
- `"with cooldown"` → cooldown state machine
- `"with transaction fee"` → subtract fee on sell
- `"unlimited transactions"` → greedy or simple state machine

---

## 4. C++ Template

```cpp
/*
 * Pattern: State Machine DP (Stock Problems)
 * Time: O(n) or O(n*k) | Space: O(1)
 */

// LC 121: ONE TRANSACTION — just track min price
int maxProfit_one(vector<int>& prices) {
    int minPrice = INT_MAX, best = 0;
    for (int p : prices) {
        minPrice = min(minPrice, p);
        best = max(best, p - minPrice);
    }
    return best;
}

// LC 122: UNLIMITED TRANSACTIONS — state machine (or greedy)
int maxProfit_unlimited(vector<int>& prices) {
    int hold = INT_MIN, rest = 0;
    for (int p : prices) {
        int prev_rest = rest;
        rest = max(rest, hold + p);   // sell: rest = hold + price
        hold = max(hold, prev_rest - p);  // buy: hold = rest - price
    }
    return rest;
}

// LC 309: WITH COOLDOWN (can't buy the day after selling)
int maxProfit_cooldown(vector<int>& prices) {
    int hold = INT_MIN, rest = 0, sold = 0;
    for (int p : prices) {
        int prev_hold = hold, prev_rest = rest;
        hold = max(prev_hold, rest - p);  // buy from rest state (not sold)
        rest = max(prev_rest, sold);       // just waiting
        sold = prev_hold + p;             // sell today
    }
    return max(rest, sold);
}

// LC 714: WITH FEE
int maxProfit_fee(vector<int>& prices, int fee) {
    int hold = INT_MIN, rest = 0;
    for (int p : prices) {
        int prev_rest = rest;
        rest = max(rest, hold + p - fee);  // sell: subtract fee
        hold = max(hold, prev_rest - p);
    }
    return rest;
}

// LC 188: AT MOST K TRANSACTIONS
int maxProfit_k(int k, vector<int>& prices) {
    int n = prices.size();
    if (k >= n/2) return maxProfit_unlimited(prices);  // effectively unlimited
    vector<int> hold(k+1, INT_MIN), rest(k+1, 0);
    for (int p : prices)
        for (int t = k; t >= 1; t--) {
            rest[t] = max(rest[t], hold[t] + p);
            hold[t] = max(hold[t], rest[t-1] - p);
        }
    return rest[k];
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll model this as a state machine. At each day, I'm either holding stock or not holding it. Transitions: buy (not-holding → holding, cost = price), sell (holding → not-holding, gain = price), or do nothing. I track two state variables: `hold` = max profit if currently holding, `rest` = max profit if not holding. Update them daily. For the cooldown variant, I need to track an additional 'sold' state, because buying requires two days of not holding after a sell."

### Interview Flow Checklist
- [ ] Identify all possible states (holding, not-holding, cooldown, etc.)
- [ ] Draw state transition diagram
- [ ] For each state: write update formula
- [ ] Process prices left to right; update states simultaneously (use prev values)
- [ ] Return max of final terminal states

---

## 6. Problems

---

### Problem 1: 121. Best Time to Buy and Sell Stock
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
**Optimal C++ Solution:**
```cpp
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX, profit = 0;
    for (int p : prices) {
        minPrice = min(minPrice, p);
        profit = max(profit, p - minPrice);
    }
    return profit;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 122. Best Time to Buy and Sell Stock II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/
**Optimal C++ Solution (greedy):**
```cpp
int maxProfit(vector<int>& prices) {
    int profit = 0;
    for (int i = 1; i < (int)prices.size(); i++)
        if (prices[i] > prices[i-1]) profit += prices[i] - prices[i-1];
    return profit;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 309. Best Time to Buy and Sell Stock with Cooldown
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
**Optimal C++ Solution:**
```cpp
int maxProfit(vector<int>& prices) {
    int hold = INT_MIN, rest = 0, sold = 0;
    for (int p : prices) {
        int ph = hold, pr = rest;
        hold = max(ph, rest - p);  // buy from rest (2+ days after selling)
        rest = max(pr, sold);       // wait
        sold = ph + p;              // sell today (using prev hold)
    }
    return max(rest, sold);
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 714. Best Time to Buy and Sell Stock with Transaction Fee
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/
**Optimal C++ Solution:**
```cpp
int maxProfit(vector<int>& prices, int fee) {
    int hold = INT_MIN, rest = 0;
    for (int p : prices) {
        int pr = rest;
        rest = max(rest, hold + p - fee);
        hold = max(hold, pr - p);
    }
    return rest;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 123. Best Time to Buy and Sell Stock III
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
**Why this pattern fits:** At most 2 transactions → track 4 states (buy1, sell1, buy2, sell2)

**Optimal C++ Solution:**
```cpp
int maxProfit(vector<int>& prices) {
    int buy1 = INT_MIN, sell1 = 0, buy2 = INT_MIN, sell2 = 0;
    for (int p : prices) {
        buy1  = max(buy1,  -p);           // first buy
        sell1 = max(sell1, buy1 + p);     // first sell
        buy2  = max(buy2,  sell1 - p);    // second buy
        sell2 = max(sell2, buy2 + p);     // second sell
    }
    return sell2;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 6: 188. Best Time to Buy and Sell Stock IV
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/
**Optimal C++ Solution:**
```cpp
int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();
    if (k >= n/2) {
        int profit = 0;
        for (int i = 1; i < n; i++) profit += max(0, prices[i]-prices[i-1]);
        return profit;
    }
    vector<int> hold(k+1, INT_MIN), rest(k+1, 0);
    for (int p : prices)
        for (int t = k; t >= 1; t--) {
            rest[t] = max(rest[t], hold[t] + p);
            hold[t] = max(hold[t], rest[t-1] - p);
        }
    return rest[k];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You can buy and sell any number of stocks, but you must sell your current stock before buying another. Also, you must wait at least 2 days after selling before buying again. Maximize profit.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** State machine DP with 2-day cooldown
**Reason:** Extend the cooldown variant: instead of 1-day cooldown, track 2-day cooldown. States: (holding, sold_yesterday, sold_two_days_ago, resting). Or: sold_2day[i] = sold[i-1], sold[i] = hold[i-1] + price, hold[i] = max(hold[i-1], sold_2day[i-1] - price). Generalize for k-day cooldown with k state variables.
</details>

---

**Drill 2:**
> You run a store and can buy and sell a product. You pay storage cost for each unit held per day. Maximize profit over n days.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** State machine DP with daily holding cost
**Reason:** Same as stock with fee, but the fee is per day you hold. Modify hold state: hold[i] = max(hold[i-1] - storage_cost, rest[i-1] - price). The daily storage cost reduces the profit of each holding day.
</details>

---

**Drill 3:**
> You must make exactly k buy-sell transactions (not "at most k"). Maximize profit.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** K-transaction DP with exact count
**Reason:** Same structure as LC 188 but initialize differently. dp[0][rest] = 0 only, all other states = -INF (impossible). At the end, return dp[k][rest] only (not checking smaller k values). If dp[k][rest] < 0, it's impossible.
</details>

---

**Drill 4:**
> You can hold at most M units of stock at a time (not just 1). Maximize profit with at most M units.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Extend stock DP with quantity dimension
**Reason:** State: (day, quantity_held). dp[qty] = max profit currently holding qty units. Transitions: buy x units (reduce buy capacity), sell x units (add to profit). Greedy: always buy max when price is going up, sell all when declining. For M=1, it reduces to standard stock.
</details>

---

**Drill 5:**
> You have two separate stocks A and B. You can hold at most one total at any time (but can choose which to hold). Maximize combined profit.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** State machine DP with stock choice
**Reason:** States: (holding A, holding B, holding nothing). Each day: transitions include buy A, sell A, buy B, sell B, or hold. DP over both price sequences simultaneously. 3 states × n days, O(n) time.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| One transaction (121) | O(n) | O(1) | Track min price |
| Unlimited (122) | O(n) | O(1) | Greedy or 2-state DP |
| With cooldown (309) | O(n) | O(1) | 3-state DP |
| With fee (714) | O(n) | O(1) | Subtract fee on sell |
| At most 2 (123) | O(n) | O(1) | 4 state variables |
| At most k (188) | O(n×k) | O(k) | k+1 hold/rest arrays |

---

## 9. Common Follow-up Questions

1. What if you can hold multiple shares (unlimited)? (Buy/sell quantities scale; greedy still works for unlimited transactions — buy on any upward slope)
2. How does cooldown affect the greedy approach? (Greedy no longer works with cooldown — DP is required because skipping a profitable day might enable a better buy later)
3. Why is k >= n/2 equivalent to unlimited? (With n days, at most n/2 complete buy-sell cycles are possible. If k ≥ n/2, the limit never constrains you → solve as unlimited)
4. Can you reconstruct the actual transactions? (Yes — track which state each transition came from. On each day, record buy/sell/hold decision per state)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Greedy | Unlimited transactions — collect each upward move | 122. Stock II |
| 1D DP | State at each day is 1D (hold/rest) | All stock problems |
| State Machine | Abstract FSM view of transitions | General sequence DP |
| K-transaction limit | Add k dimension to state | 188. Stock IV |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
