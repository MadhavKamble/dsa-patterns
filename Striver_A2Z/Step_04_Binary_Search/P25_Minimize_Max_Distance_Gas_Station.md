# 🔥 Minimize Maximum Distance Between Gas Stations

> **Striver / GFG** · **Difficulty:** Hard · **Step 4 — Binary Search · P25**

---

## 🧠 Problem Understanding

**What is it asking?**
`arr` is a **sorted** array of gas-station positions. Add `k` **new** stations (anywhere, including non-integer positions) to **minimize the maximum gap** between adjacent stations. Return that minimized maximum gap (a real number).

**Input:** `arr = [1, 2, 3, 4, 5]`, `k = 4` → **Output:** `0.5`

**Key Observation:**
- We binary-search on a **real-valued answer** (the maximum allowed gap `dist`).
- **Monotonic:** a larger allowed `dist` needs **fewer** new stations. So `stationsNeeded(dist) > k` means `dist` is too small.
- For each existing gap `g`, stations needed inside it = `floor(g / dist)` (with a `-1` correction when it divides exactly).

---

## 🎯 Interview Progression

### 🥉 Brute Force — Place One Station at a Time

Maintain how many stations sit in each gap; `k` times, insert into the gap with the current largest section length. Answer = largest section afterward. **Time:** O(k · n).

### 🥈 Better — Max-Heap

Use a priority queue keyed by current section length to always split the largest gap. **Time:** O(n log n + k log n).

---

### 🥇 Optimal — Binary Search on the Answer (Real-Valued)

> 💡 Search `dist ∈ (0, maxGap]`. `numberOfGasStationsRequired(dist)` sums `floor(gap/dist)` per gap. If it needs `> k`, `dist` is too small → raise `low`; else lower `high`. Iterate until the window is within `1e-6`.

```cpp
class Solution {
public:
    int numberOfGasStationsRequired(long double dist,vector<int>& arr){
        int n=arr.size();
        int cnt=0;
        for(int i=1;i<n;i++){
            int numberInBetween=(arr[i]-arr[i-1])/dist;
            if((arr[i]-arr[i-1])==(dist*numberInBetween)){
                numberInBetween--;
            }
            cnt+=numberInBetween;
        }
        return cnt;
    }
    long double minimiseMaxDistance(vector<int>& arr,int k){
        int n=arr.size();
        long double low=0,high=0;
        for(int i=0;i<n-1;i++){
            high=max(high,(long double)(arr[i+1]-arr[i]));
        }
        long double diff=1e-6;
        while(high-low>diff){
            long double mid=(low+high)/2.0;
            int cnt=numberOfGasStationsRequired(mid,arr);
            if(cnt>k) low=mid;
            else high=mid;
        }
        return high;
    }
};
```

**Time:** O(n · log(maxGap / 1e-6)) · **Space:** O(1).

### Dry Run (intuition)
`arr = [1,2,3,4,5]`, `k = 4`. Every adjacent gap is 1. To halve the max gap to `0.5`, each of the 4 gaps needs `floor(1/0.5)-1 = 1` station → 4 total = `k`. Binary search converges to **0.5**.

---

## 🎤 Interview Explanation Script

> "The answer is a continuous value, so I binary-search on the maximum allowed gap. For a candidate `dist`, the stations needed in a gap `g` is `floor(g/dist)` — with a `-1` when `g` is an exact multiple, since a station exactly on the boundary isn't needed. If total needed exceeds `k`, `dist` is too tight and I raise the lower bound; otherwise I tighten the upper bound. I stop once the interval is within `1e-6`."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Real-valued BS on max gap `(0, maxGap]`. Stations in gap = `floor(g/dist)`. `cnt>k` → `low=mid`, else `high=mid`. Stop at `1e-6`."

---

## 📝 Short Revision Notes

- Answer is a **real number** → loop on precision `high - low > 1e-6`, not `low <= high`.
- Feasibility is reversed vs integer templates: `cnt > k` → too small → `low = mid` (no ±1 since it's continuous).
- `high` starts as the largest existing gap; `low` starts at 0.
- Better non-BS approach exists (max-heap, O(n log n + k log n)); BS trades a precision factor for O(1) space.

---

## ⚠️ Common Mistakes

❌ Using `low <= high` with integer-style `mid±1` on a real-valued search.
❌ Forgetting the exact-divisibility `-1` correction in the station count.
❌ Setting `high` too small (must be the maximum initial gap).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "minimize the maximum gap/distance with real-valued answer", "insert k points" → **binary search on a real answer**.

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Real-Valued Search` · `Minimize Maximum`

---

## ⏱️ 30-Second Last-Minute Revision

> **Real-valued BS on max gap.** Stations in gap `g` = `floor(g/dist)` (−1 if exact). `cnt>k` → `low=mid`, else `high=mid`. Stop at `1e-6`. Return `high`.
