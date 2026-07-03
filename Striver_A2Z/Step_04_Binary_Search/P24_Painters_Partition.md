# 🔥 Painter's Partition Problem

> **Striver / GFG** · **Difficulty:** Hard · **Step 4 — Binary Search · P24**

---

## 🧠 Problem Understanding

**What is it asking?**
`boards[i]` = length of board `i`. `k` painters each paint a **contiguous** block of boards, taking 1 unit of time per unit length. Minimize the **maximum time** taken (i.e. minimize the largest painter's workload).

**Input:** `boards = [10, 20, 30, 40]`, `k = 2` → **Output:** `60` (`[10,20,30] | [40]` → max(60,40)=60)

**Key Observation:**
- Identical to **Split Array Largest Sum** and **Book Allocation** — minimize the maximum contiguous block sum over `k` groups.
- Search over the **time limit**; larger limit → fewer painters needed (monotonic).
- Search space: `low = max(boards)`, `high = sum(boards)`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Time Limit

For `time = max(boards) ... sum(boards)`, count painters needed; return the first needing `≤ k`. **Time:** O(sum · n).

---

### 🥇 Optimal — Binary Search on the Time Limit

> 💡 `countPainters(time)` greedily assigns boards to the current painter until adding one exceeds `time`, then starts a new painter. If painters `> k`, time is too small → go right; else record and go left.

```cpp
class Solution {
public:
    int countPainters(vector<int>& boards,int time){
        int painters=1;
        long long boardsPainter=0;
        for(int i=0;i<boards.size();i++){
            if(boardsPainter+boards[i]<=time){
                boardsPainter+=boards[i];
            }else{
                painters++;
                boardsPainter=boards[i];
            }
        }
        return painters;
    }
    int findLargestMinDistance(vector<int>& boards,int k){
        int low=*max_element(boards.begin(),boards.end());
        int high=accumulate(boards.begin(),boards.end(),0);
        int result=high;
        while(low<=high){
            int mid=(low+high)/2;
            int painters=countPainters(boards,mid);
            if(painters>k){
                low=mid+1;
            }else{
                result=mid;
                high=mid-1;
            }
        }
        return result;
    }
};
```

**Time:** O(n · log(sum(boards))) · **Space:** O(1).

### Dry Run
`boards = [10, 20, 30, 40]`, `k = 2`, search `[40, 100]`

| low | high | mid | painters at ≤mid | >2? | result | Action |
|-----|------|-----|-------------------|-----|--------|--------|
| 40 | 100 | 70 | [10,20,30],[40] → 2 | ❌ | 70 | high=69 |
| 40 | 69 | 54 | [10,20],[30],[40] → 3 | ✅ | 70 | low=55 |
| 55 | 69 | 62 | [10,20,30],[40] → 2 | ❌ | 62 | high=61 |
| 55 | 61 | 58 | [10,20],[30],[40] → 3 | ✅ | 62 | low=59 |
| 59 | 61 | 60 | [10,20,30],[40] → 2 | ❌ | 60 | high=59 |
| 59 | 59 | 59 | [10,20],[30],[40] → 3 | ✅ | 60 | low=60 |
| 60 | 59 | — | — | — | 60 | **return 60** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on time `[max, sum]`. `countPainters>k` → go right, else record & go left. Same as Book Allocation / Split Array."

---

## 📝 Short Revision Notes

- **Same problem** as Book Allocation (P22) and Split Array Largest Sum (P23).
- `low = max(boards)`, `high = sum(boards)`.
- `painters > k` → time too small → `low = mid+1`; else store `result` and shrink.
- Contiguous assignment validates the greedy painter count.

---

## ⚠️ Common Mistakes

❌ Treating painters as able to paint non-contiguous boards.
❌ Wrong search bounds (`low` must be `max(boards)`).
❌ Off-by-one in the feasibility direction (`> k` vs `>= k`).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "k painters/workers, contiguous blocks, minimize the max workload" → **binary search on answer** (= Split Array / Book Allocation).

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Minimize Maximum` · `Greedy Partition`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS time `[max, sum]`.** Greedy `countPainters`; `>k` → right, else record & left. Identical to Book Allocation. `O(n·log sum)`.
