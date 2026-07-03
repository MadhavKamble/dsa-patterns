# 🔥 Find the Smallest Divisor Given a Threshold

> **LeetCode #1283** · **Difficulty:** Medium · **Step 4 — Binary Search · P18**

---

## 🧠 Problem Understanding

**What is it asking?**
Pick a positive integer divisor `d`. Divide every element by `d`, take the **ceiling**, and sum. Find the **smallest `d`** whose sum is `≤ threshold`.

**Input:** `nums = [1, 2, 5, 9]`, `threshold = 6` → **Output:** `5`
**Input:** `nums = [44, 22, 33, 11, 1]`, `threshold = 5` → **Output:** `44`

**Key Observation:**
- We search over **divisor** (a value).
- **Monotonic:** larger `d` → each `ceil(num/d)` shrinks → total sum decreases. Feasibility flips once.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Divisor

For `d = 1 ... max(nums)`, compute the sum; return the first `d` with sum `≤ threshold`. **Time:** O(max(nums) · n).

---

### 🥇 Optimal — Binary Search on Divisor

> 💡 Search `[1, max(nums)]`. If the sum at `mid` is within `threshold`, it's a candidate → try a smaller divisor; otherwise increase it.

```cpp
class Solution {
public:
    bool isValid(vector<int>& nums,int threshold,int d){
        long long sum=0;
        for(int num:nums){
            sum+=(num+d-1)/d;
        }
        return sum<=threshold;
    }
    int smallestDivisor(vector<int>& nums,int threshold){
        int low=1;
        int high=*max_element(nums.begin(),nums.end());
        int ans=high;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(isValid(nums,threshold,mid)){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;
    }
};
```

**Time:** O(n · log(max(nums))) · **Space:** O(1).

### Dry Run
`nums = [1, 2, 5, 9]`, `threshold = 6`, search `[1, 9]`

| low | high | mid | sum = Σceil(num/mid) | ≤6? | ans | Action |
|-----|------|-----|----------------------|-----|-----|--------|
| 1 | 9 | 5 | 1+1+1+2 = 5 | ✅ | 5 | high=4 |
| 1 | 4 | 2 | 1+1+3+5 = 10 | ❌ | 5 | low=3 |
| 3 | 4 | 3 | 1+1+2+3 = 7 | ❌ | 5 | low=4 |
| 4 | 4 | 4 | 1+1+2+3 = 7 | ❌ | 5 | low=5 |
| 5 | 4 | — | — | — | 5 | **return 5** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on divisor `[1, max]`. `sum = Σceil(num/d)`. `sum<=threshold` → smaller d, else larger."

---

## 📝 Short Revision Notes

- Same shape as Koko (P16) — divisor plays the role of speed, sum plays the role of hours.
- `ceil(num/d) = (num + d - 1) / d`.
- Search space `[1, max(nums)]`; at `d = max`, every ceil is 1, so sum = n (smallest possible).
- Sum in `long long` for safety.

---

## ⚠️ Common Mistakes

❌ Floating-point `ceil` → precision issues; use integer form.
❌ Upper bound below `max(nums)` → may miss the valid divisor.
❌ Reversing the feasibility direction (sum increases with `d`) — it **decreases**.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "smallest divisor so the ceil-sum ≤ limit" → **binary search on answer** (twin of Koko).

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Feasibility Predicate`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS divisor `[1, max]`.** `sum=Σceil(num/d)`. `sum<=threshold` → shrink d; else grow. Minimize. `O(n·log max)`.
