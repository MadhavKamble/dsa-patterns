# P97 — Fenwick Tree (Binary Indexed Tree)

## 1. First-Timer Explanation

### What Is It?
**Fenwick Tree** (Binary Indexed Tree / BIT) computes prefix sums in O(log n) with O(log n) point updates. It's simpler and faster in practice than a segment tree for cumulative sum queries. The key insight: each index i in the BIT is responsible for a range of `lowbit(i) = i & (-i)` elements.

### How It Works
```
For array [1, 2, 3, 4, 5, 6, 7, 8]:

BIT index: 1  2  3  4  5  6  7  8
lowbit:    1  2  1  4  1  2  1  8
Range:    [1][1,2][3][1,4][5][5,6][7][1,8]

bit[4] covers sum of arr[1..4]
bit[6] covers sum of arr[5..6]
bit[8] covers sum of arr[1..8]

Prefix sum of [1..6]:
  Query(6): bit[6]+bit[4] (6→4: 6 & (-6)=2, 6-2=4→4 & (-4)=4, 4-4=0→done)
  = sum[5..6] + sum[1..4]
```

### Update and Query
```
Update(i, delta):  Add delta to bit[i], bit[i + lowbit(i)], ...
  i += i & (-i)  until i > n

Query(i):  Sum of arr[1..i]
  res += bit[i]; i -= i & (-i)  until i <= 0

Range sum [l, r] = Query(r) - Query(l-1)
```

### When to Use
- "Point update + prefix sum query" → BIT (simpler than segment tree)
- "Count elements less than x (with updates)" → coordinate compress + BIT
- "Count inversions" → BIT / merge sort
- "Rank of element in sorted order" → BIT
- "Range update + point query" → BIT with difference array trick

---

## 2. Revision Card

**Recognition Signal:** "prefix sum with updates", "count smaller/larger elements", "inversions"

**Core Idea:** `bit[i]` covers a range of `lowbit(i)` elements. Update: propagate forward (`i += i & -i`). Query: accumulate backward (`i -= i & -i`).

**Trigger Keywords:** BIT, Fenwick tree, prefix sum updates, inversions, rank

**Complexity:** O(log n) update and query, O(n log n) build, O(n) space

---

## 3. Interview Tell Signs

- "Mutable prefix sum queries" → BIT (simpler to code than segment tree)
- "Count of elements smaller than current in suffix" → BIT from right to left
- "Count inversions in array" → merge sort or BIT
- "Rank query: how many elements ≤ x?" → coordinate compress + BIT
- "Number of ships in rectangle (offline)" → 2D BIT

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── Fenwick Tree (1-indexed) ──────────────────────────────────────────────────
class BIT {
    int n;
    vector<int> bit;
public:
    BIT(int n) : n(n), bit(n + 1, 0) {}

    // Point update: add delta to position i (1-indexed)
    void update(int i, int delta) {
        for (; i <= n; i += i & (-i)) bit[i] += delta;
    }

    // Prefix sum: sum of [1..i]
    int query(int i) {
        int res = 0;
        for (; i > 0; i -= i & (-i)) res += bit[i];
        return res;
    }

    // Range sum: sum of [l..r]
    int query(int l, int r) { return query(r) - query(l - 1); }
};

// ── Build BIT from Array ──────────────────────────────────────────────────────
BIT buildBIT(vector<int>& arr) {
    int n = arr.size();
    BIT bit(n);
    for (int i = 0; i < n; i++) bit.update(i + 1, arr[i]); // 1-indexed
    return bit;
}

// ── Count Inversions ──────────────────────────────────────────────────────────
long long countInversions(vector<int>& arr) {
    vector<int> sorted = arr; sort(sorted.begin(), sorted.end());
    sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
    auto compress = [&](int v) { return lower_bound(sorted.begin(), sorted.end(), v) - sorted.begin() + 1; };
    int m = sorted.size();
    BIT bit(m);
    long long inv = 0;
    for (int i = arr.size() - 1; i >= 0; i--) {
        int idx = compress(arr[i]);
        inv += bit.query(idx - 1); // count elements already processed that are < arr[i]
        bit.update(idx, 1);
    }
    return inv;
}

// ── Range Update, Point Query (Difference BIT) ────────────────────────────────
class DiffBIT {
    BIT bit;
    int n;
public:
    DiffBIT(int n) : bit(n), n(n) {}
    // Add delta to all elements in [l, r]
    void rangeUpdate(int l, int r, int delta) {
        bit.update(l, delta);
        if (r + 1 <= n) bit.update(r + 1, -delta);
    }
    // Query actual value at position i
    int pointQuery(int i) { return bit.query(i); }
};
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Fenwick Tree is a 1-indexed array where `bit[i]` stores the sum of elements from `i - lowbit(i) + 1` to `i`, where `lowbit(i) = i & (-i)`. To update position i: add delta to bit[i], then propagate to the next responsible node by `i += lowbit(i)`. To query prefix sum [1..i]: accumulate bit[i], then jump to the previous responsible node by `i -= lowbit(i)`. Both operations take O(log n) steps."

**Checklist:**
- [ ] BIT is 1-indexed (index 0 is unused or causes infinite loop in update)
- [ ] Update: `i += i & (-i)` (forward propagation, stop at n)
- [ ] Query: `i -= i & (-i)` (backward accumulation, stop at 0)
- [ ] Range query: `query(r) - query(l-1)`
- [ ] Coordinate compress before using BIT with large/negative values

---

## 6. Problems

### Problem 1: Range Sum Query — Mutable
**Difficulty:** Medium | **LC:** 307

```cpp
class NumArray {
    int n; vector<int> bit, arr;
    void update(int i,int d){for(;i<=n;i+=i&(-i))bit[i]+=d;}
    int query(int i){int s=0;for(;i>0;i-=i&(-i))s+=bit[i];return s;}
public:
    NumArray(vector<int>&a):n(a.size()),bit(a.size()+1,0),arr(a){
        for(int i=0;i<n;i++) update(i+1,a[i]);
    }
    void update(int i,int v){update(i+1,v-arr[i]);arr[i]=v;}
    int sumRange(int l,int r){return query(r+1)-query(l);}
};
// Time: O(log n) both | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Count of Smaller Numbers After Self
**Difficulty:** Hard | **LC:** 315

```cpp
vector<int> countSmaller(vector<int>& nums) {
    vector<int> sorted=nums;sort(sorted.begin(),sorted.end());sorted.erase(unique(sorted.begin(),sorted.end()),sorted.end());
    int m=sorted.size();vector<int> bit(m+2,0),res(nums.size());
    auto compress=[&](int v){return(int)(lower_bound(sorted.begin(),sorted.end(),v)-sorted.begin())+1;};
    auto upd=[&](int i){for(;i<=m;i+=i&(-i))bit[i]++;};
    auto qry=[&](int i)->int{int s=0;for(;i>0;i-=i&(-i))s+=bit[i];return s;};
    for(int i=nums.size()-1;i>=0;i--){int idx=compress(nums[i]);res[i]=qry(idx-1);upd(idx);}
    return res;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Count of Range Sum
**Difficulty:** Hard | **LC:** 327

**Approach:** Prefix sums + merge sort or BIT with coordinate compression.

```cpp
int countRangeSum(vector<int>& nums, int lower, int upper) {
    int n=nums.size(); vector<long long> pre(n+1,0);
    for(int i=0;i<n;i++) pre[i+1]=pre[i]+nums[i];
    // Count pairs (i,j) where lower <= pre[j]-pre[i] <= upper
    // i.e., pre[j]-upper <= pre[i] <= pre[j]-lower
    long long res=0;
    function<void(int,int)> mergeSort=[&](int l,int r){
        if(r-l<=1) return;
        int mid=(l+r)/2;
        mergeSort(l,mid); mergeSort(mid,r);
        int j=mid,k=mid;
        for(int i=l;i<mid;i++){
            while(j<r&&pre[j]-pre[i]<lower) j++;
            while(k<r&&pre[k]-pre[i]<=upper) k++;
            res+=k-j;
        }
        inplace_merge(pre.begin()+l,pre.begin()+mid,pre.begin()+r);
    };
    mergeSort(0,n+1);
    return res;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Reverse Pairs
**Difficulty:** Hard | **LC:** 493

**Approach:** Modified merge sort — count (i,j) pairs where i<j and nums[i]>2*nums[j].

```cpp
long long reversePairs(vector<int>& nums) {
    long long cnt=0;
    function<void(int,int)> ms=[&](int l,int r){
        if(r-l<=1) return;
        int mid=(l+r)/2;
        ms(l,mid); ms(mid,r);
        int j=mid;
        for(int i=l;i<mid;i++){
            while(j<r&&(long long)nums[i]>2LL*nums[j]) j++;
            cnt+=j-mid;
        }
        inplace_merge(nums.begin()+l,nums.begin()+mid,nums.begin()+r);
    };
    ms(0,nums.size());
    return cnt;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Queue Reconstruction by Height
**Difficulty:** Medium | **LC:** 406

**Approach:** Sort by height desc (then k asc). Insert each person at position k.

```cpp
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    sort(people.begin(),people.end(),[](auto& a,auto& b){
        return a[0]>b[0]||(a[0]==b[0]&&a[1]<b[1]);
    });
    vector<vector<int>> res;
    for(auto& p:people) res.insert(res.begin()+p[1],p);
    return res;
}
// Time: O(n²) due to insert | Space: O(n)
// O(n log n) with BIT: find k-th available position
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Number of Longest Increasing Subsequences
**Difficulty:** Medium | **LC:** 673

```cpp
int findNumberOfLIS(vector<int>& nums) {
    int n=nums.size(),maxLen=0,res=0;
    vector<int> len(n,1),cnt(n,1);
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(nums[j]<nums[i]){
                if(len[j]+1>len[i]){len[i]=len[j]+1;cnt[i]=cnt[j];}
                else if(len[j]+1==len[i]) cnt[i]+=cnt[j];
            }
        }
        maxLen=max(maxLen,len[i]);
    }
    for(int i=0;i<n;i++) if(len[i]==maxLen) res+=cnt[i];
    return res;
}
// Time: O(n²) | Space: O(n)
// O(n log n) with BIT: store (maxLen, count) pairs per length in BIT
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** BIT update for i=6 (n=8). Which indices are updated?
<details><summary>Reveal</summary>
i=6: bit[6] += delta. i += i&(-i)=6&(-6)=2. i=8: bit[8] += delta. i=8+8=16>8 → stop. Indices updated: [6, 8] ✓.
</details>

**Drill 2:** BIT query for prefix sum [1..6]. Which indices are summed?
<details><summary>Reveal</summary>
i=6: res+=bit[6]. i-=i&(-i)=6-2=4. res+=bit[4]. i-=4&(-4)=4-4=0→stop. Sum = bit[6]+bit[4] = sum[5..6] + sum[1..4] ✓.
</details>

**Drill 3:** Count inversions in [3,1,2]. Trace right-to-left BIT queries.
<details><summary>Reveal</summary>
sorted=[1,2,3]. Compress: 3→3, 1→1, 2→2. i=2(val=2): compress=2. query(1)=0 (nothing before). update(2,1). i=1(val=1): compress=1. query(0)=0. update(1,1). i=0(val=3): compress=3. query(2)=bit[2]+bit[0]=1+0=1 (elements smaller than 3 that came after=2→count 1 inversion: (3,2)... wait, we process right to left so "came after" means to the right). inv=0+0+query(2)=query at 3's compress-1=2 → bit[2] which was updated for 1 and 2. bit[2]=sum of [1..2] in BIT. After updates: bit[1]=1(value 1), bit[2]=1+1=2(values 1 and 2). query(2)=2. Inversions: (3,1) and (3,2). inv=2 ✓.
</details>

**Drill 4:** Range update, point query: add 5 to [2,4]. What BIT indices change?
<details><summary>Reveal</summary>
DiffBIT: update(2, +5) and update(5, -5) (assuming r+1=5 ≤ n). In the underlying BIT: update at index 2 propagates to indices 2,4,... update at index 5 propagates to 5,6,8,... Point query at i=3: prefix sum of diff BIT [1..3] = diff[1]+diff[2]+diff[3] = 0+5+0 = 5. Query at i=5: prefix sum = 0+5+0+0+(-5)=0 (outside the range). ✓
</details>

**Drill 5:** Why is the Fenwick Tree 1-indexed and what happens if you use index 0?
<details><summary>Reveal</summary>
If i=0: update would execute `i += i & (-i) = 0 & 0 = 0` → infinite loop. The lowbit of 0 is 0, so i never advances. 1-indexed avoids this: lowbit(1)=1, lowbit(2)=2, etc. — all positive. Also, in query, i-=lowbit(i) reduces i by at least 1 each step (since lowbit ≥ 1 for i ≥ 1), guaranteeing termination.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build BIT | O(n log n) | O(n) |
| Point update | O(log n) | O(1) |
| Prefix query | O(log n) | O(1) |
| Range query | O(log n) | O(1) |
| Count inversions | O(n log n) | O(n) |
| 2D BIT (matrix updates) | O(log²n) | O(n²) |

---

## 9. Common Follow-up Questions

**Q: Can BIT support range updates?**
A: Yes, using a "difference BIT": `update(l, delta)` and `update(r+1, -delta)`. Point query becomes a prefix sum query. For both range update AND range query, use two BITs with the formula `sum[l..r] = BIT1.query(r)*r - BIT2.query(r) - (BIT1.query(l-1)*(l-1) - BIT2.query(l-1))`.

**Q: How do you build a BIT in O(n) instead of O(n log n)?**
A: Direct construction: for each i from 1 to n, set `bit[i] += arr[i]`. Then `j = i + (i & -i)`. If `j ≤ n`, `bit[j] += bit[i]`. This propagates each element's contribution exactly once.

**Q: When to prefer BIT over Segment Tree?**
A: BIT: simpler code, smaller constant factor, suffix for prefix sum queries. Segment Tree: supports min/max queries, range updates with range queries (lazy propagation), arbitrary associative operations. For sum queries with point updates, prefer BIT.

---

## 10. Cross-Pattern Connections

- **P96 (Segment Tree):** Segment tree = more powerful; BIT = simpler for sums; both O(log n)
- **P79 (Prefix Sums):** Prefix sum = O(1) query, no update; BIT = O(log n) both
- **P80 (Difference Arrays):** Difference array = O(1) update, O(n) point query; difference BIT = O(log n) both
- **P43 (Merge Sort):** Count inversions via merge sort is an alternative to BIT approach
