# 🔥 Stock Buy and Sell (Best Time to Buy and Sell Stock)

> **LeetCode #121** · **Difficulty:** Easy · **Step 3 — Arrays · P22**

---

## 🧠 Problem Understanding

Given prices on each day, find the maximum profit by buying on one day and selling on a **later** day.

**Input:** `[7,1,5,3,6,4]` → **Output:** `5` (buy at 1, sell at 6)  
**Input:** `[7,6,4,3,1]` → **Output:** `0` (prices only fall, no profit)

**Key Observation:** To maximize profit, we want to buy at the **minimum price seen so far** and sell at the current price.

---

## 🥉 Brute Force
Check all `(i,j)` pairs with `i < j`. **Time:** O(N²)

---

## 🥇 Optimal — Track Minimum So Far

### Algorithm
1. `minPrice = prices[0]`, `maxProfit = 0`
2. For each `price`:
   - `maxProfit = max(maxProfit, price - minPrice)` (sell today)
   - `minPrice = min(minPrice, price)` (update buy candidate)

### Dry Run
`prices = [7, 1, 5, 3, 6, 4]`

| i | price | minPrice | profit = price-min | maxProfit |
|---|-------|----------|--------------------|-----------|
| 0 | 7 | 7 | 0 | 0 |
| 1 | 1 | **1** | 0 | 0 |
| 2 | 5 | 1 | 4 | 4 |
| 3 | 3 | 1 | 2 | 4 |
| 4 | 6 | 1 | **5** | **5** |
| 5 | 4 | 1 | 3 | 5 |

**Output:** `5` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * STOCK BUY SELL — track minimum price seen so far
 * At each price: profit = current price - min so far
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = prices[0];
        int maxProfit = 0;

        for (int price : prices) {
            maxProfit = max(maxProfit, price - minPrice);  // sell today
            minPrice = min(minPrice, price);               // update best buy
        }

        return maxProfit;
    }
};
```

---

## 🎤 Interview Explanation Script
> "At each day, the maximum profit if we sell today is `price - minimum price seen so far`. I scan left to right, tracking both the running minimum price and the maximum profit seen. This is O(N) time, O(1) space."

> "This is essentially Kadane's algorithm in disguise: if prices[i] - prices[j] < 0 for the best j we've seen, we update our buy point."

---

## 🧾 Recall Line
> "Track `minPrice` seen so far. Each day: `profit = price - minPrice`. Update `maxProfit` and `minPrice`."

## 📝 Short Revision Notes
- Must buy before sell (i < j) — so we update `minPrice` AFTER checking profit... actually order matters: check profit first OR update min first (both work since `minPrice` represents minimum BEFORE current day)
- Return 0 if no profit possible (all falling prices)
- Extension: unlimited transactions (LC 122) → sum all increases
- Extension: K transactions (LC 188) → DP

## ⚠️ Common Mistakes
❌ `minPrice = min(minPrice, price)` BEFORE `profit = price - minPrice` — same result but logically: compute profit with OLD min, then update min  
❌ Returning `maxProfit` even if negative — initialize `maxProfit = 0` (no trade = 0 profit)

## 📚 Related Problems
- [ ] LeetCode #121 — Best Time to Buy and Sell Stock I
- [ ] LeetCode #122 — Stock II (unlimited transactions)
- [ ] LeetCode #123 — Stock III (at most 2 transactions)
- [ ] LeetCode #188 — Stock IV (at most K transactions)

## 🏆 Pattern Category
`Arrays` · `Greedy` · `Linear Scan`

## ⏱️ 30-Second Revision
> `minPrice=prices[0], maxProfit=0`. For each price: `maxProfit=max(maxProfit, price-minPrice)`. `minPrice=min(minPrice, price)`. Return maxProfit.
