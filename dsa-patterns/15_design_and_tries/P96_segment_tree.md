# P96 — Segment Tree

## 1. First-Timer Explanation

### What Is It?
A **Segment Tree** is a binary tree where each node stores aggregate information (sum, min, max, GCD) about a contiguous array segment. It enables both **point updates** and **range queries** in O(log n) — superior to prefix sums (O(n) update) and linear scan (O(n) query).

### Structure
```
Array: [1, 3, 5, 7, 9, 11]
Segment Tree (sum):

              36 [0..5]
           /              \
       9 [0..2]        27 [3..5]
      /      \         /       \
   4[0..1]  5[2] 16[3..4]  11[5]
   /    \        /    \
  1[0]  3[1]   7[3]  9[4]

Size of tree array: 4*n (to be safe); leaves at indices 2n..2n+n-1 (1-indexed)
```

### Operations
```
Build:  Traverse bottom-up, tree[i] = tree[2i] + tree[2i+1]

Update (point):  Update leaf, propagate up
  tree[pos+n] = val; pos /= 2; tree[pos] = tree[2*pos] + tree[2*pos+1]

Query (range [l, r]):  From leaves outward, combine partial segments
  if l is right child: include tree[l], l = (l+1)/2
  if r is left child:  include tree[r], r = (r-1)/2
```

### Lazy Propagation
```
For range updates (add v to [l, r]):
  Store the pending update in lazy[node]
  Before accessing children: push down lazy to both children
  This enables O(log n) range updates
```

### When to Use
- "Range sum/min/max query with point updates" → Segment tree
- "Range updates with range queries" → Segment tree with lazy propagation
- "Rectangle union area" → Segment tree on compressed y-axis
- "Count inversions" → Merge sort or BIT

---

## 2. Revision Card

**Recognition Signal:** "range query + point update", "range update + range query"

**Core Idea:** Build on array of size 4n. Each node covers a range. Point update: update leaf, propagate up. Range query: combine segments traversing from leaves.

**Trigger Keywords:** segment tree, range query, point update, lazy propagation, interval

**Complexity:** O(n) build, O(log n) query and update

---

## 3. Interview Tell Signs

- "Range sum queries with updates" → Segment tree or Fenwick Tree (BIT)
- "Range minimum/maximum queries" → Segment tree (BIT handles sums better)
- "Range updates AND range queries" → Segment tree with lazy propagation
- "Count of elements in range satisfying condition" → Merge sort tree or segment tree
- "2D range queries with updates" → 2D segment tree

---

## 4. C++ Template

```cpp
#include <vector>
#include <functional>
using namespace std;

// ── Iterative Segment Tree (Sum, Point Update) ────────────────────────────────
class SegTree {
    int n;
    vector<int> tree;
public:
    SegTree(vector<int>& arr) {
        n = arr.size();
        tree.assign(2 * n, 0);
        // Build: put leaves, then compute internal nodes
        for (int i = 0; i < n; i++) tree[n + i] = arr[i];
        for (int i = n - 1; i >= 1; i--) tree[i] = tree[2*i] + tree[2*i+1];
    }
    // Point update: set arr[pos] = val
    void update(int pos, int val) {
        tree[n + pos] = val;
        for (int i = (n + pos) / 2; i >= 1; i /= 2)
            tree[i] = tree[2*i] + tree[2*i+1];
    }
    // Range query: sum of arr[l..r] inclusive
    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
        }
        return res;
    }
};

// ── Recursive Segment Tree with Lazy Propagation (Range Add, Range Sum) ───────
class LazySegTree {
    int n;
    vector<long long> tree, lazy;
    void push(int node, int l, int r) {
        if (lazy[node]) {
            int mid = (l + r) / 2;
            tree[2*node] += lazy[node] * (mid - l + 1);
            lazy[2*node] += lazy[node];
            tree[2*node+1] += lazy[node] * (r - mid);
            lazy[2*node+1] += lazy[node];
            lazy[node] = 0;
        }
    }
    void update(int node, int l, int r, int ql, int qr, long long val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { tree[node] += val*(r-l+1); lazy[node] += val; return; }
        push(node, l, r);
        int mid = (l + r) / 2;
        update(2*node, l, mid, ql, qr, val);
        update(2*node+1, mid+1, r, ql, qr, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
    long long query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        push(node, l, r);
        int mid = (l + r) / 2;
        return query(2*node, l, mid, ql, qr) + query(2*node+1, mid+1, r, ql, qr);
    }
public:
    LazySegTree(int n) : n(n), tree(4*n, 0), lazy(4*n, 0) {}
    void update(int l, int r, long long val) { update(1, 0, n-1, l, r, val); }
    long long query(int l, int r) { return query(1, 0, n-1, l, r); }
};
```

---

## 5. How to Present in Interview

**Verbal Script (Iterative):**
> "I store the tree in an array of size 2n. Leaves are at indices n to 2n-1. Each internal node i covers tree[2i] and tree[2i+1]. For a range query [l,r], I start at the leaves and work inward: if the left boundary is a right child (odd index), include it and move right; if the right boundary is a left child (even index, before decrement), include it and move left. This gives O(log n) per query."

**Verbal Script (Lazy):**
> "For range updates, I use lazy propagation: instead of updating every element in a range, I mark the covering nodes with a pending update. When I need to access children of a marked node, I push the lazy value down first. This ensures correctness while keeping O(log n) per operation."

**Checklist:**
- [ ] Iterative: tree size `2n`; leaves start at index `n`
- [ ] Range query: `l += n, r += n+1` (exclusive right); advance l if odd, decrement r if odd
- [ ] Lazy: always `push()` before accessing children in query/update
- [ ] Lazy push: update children's sums AND their lazy values
- [ ] Clear lazy[node] = 0 after pushing down

---

## 6. Problems

### Problem 1: Range Sum Query — Mutable
**Difficulty:** Medium | **LC:** 307

```cpp
class NumArray {
    int n; vector<int> tree;
    void build(vector<int>& a){n=a.size();tree.resize(2*n);for(int i=0;i<n;i++)tree[n+i]=a[i];for(int i=n-1;i>=1;i--)tree[i]=tree[2*i]+tree[2*i+1];}
public:
    NumArray(vector<int>& a){build(a);}
    void update(int p,int v){tree[n+p]=v;for(int i=(n+p)/2;i>=1;i/=2)tree[i]=tree[2*i]+tree[2*i+1];}
    int sumRange(int l,int r){int res=0;for(l+=n,r+=n+1;l<r;l/=2,r/=2){if(l&1)res+=tree[l++];if(r&1)res+=tree[--r];}return res;}
};
// Time: O(log n) update, O(log n) query | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Count of Smaller Numbers After Self
**Difficulty:** Hard | **LC:** 315

**Approach:** Coordinate compress, use BIT/SegTree to count elements in range.

```cpp
vector<int> countSmaller(vector<int>& nums) {
    vector<int> sorted=nums; sort(sorted.begin(),sorted.end()); sorted.erase(unique(sorted.begin(),sorted.end()),sorted.end());
    auto getIdx=[&](int v){return lower_bound(sorted.begin(),sorted.end(),v)-sorted.begin()+1;};
    int m=sorted.size();
    vector<int> bit(m+1,0),res(nums.size());
    auto update=[&](int i){for(;i<=m;i+=i&(-i))bit[i]++;};
    auto query=[&](int i)->int{int s=0;for(;i>0;i-=i&(-i))s+=bit[i];return s;};
    for(int i=nums.size()-1;i>=0;i--){int idx=getIdx(nums[i]);res[i]=query(idx-1);update(idx);}
    return res;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: The Skyline Problem (Segment Tree Approach)
**Difficulty:** Hard | **LC:** 218

```cpp
// Alternative: coordinate compress + segment tree with lazy propagation
// See P84 for the multiset/sweep approach (simpler to implement in interviews)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Maximum Sum Rectangle (Kadane's 2D)
**Difficulty:** Hard | **LC:** 363

```cpp
// Uses column-pair prefix sums + ordered set binary search (see P83)
// Segment tree not required for this problem
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Falling Squares
**Difficulty:** Hard | **LC:** 699

**Approach:** After each square lands, update [left, right] with max height, query max.

```cpp
vector<int> fallingSquares(vector<vector<int>>& positions) {
    // Coordinate compress
    vector<int> coords;
    for(auto& p:positions){coords.push_back(p[0]);coords.push_back(p[0]+p[1]);}
    sort(coords.begin(),coords.end());coords.erase(unique(coords.begin(),coords.end()),coords.end());
    int n=coords.size();
    auto getIdx=[&](int v){return lower_bound(coords.begin(),coords.end(),v)-coords.begin();};
    // Lazy segment tree (max, range-set update)
    vector<int> tree(4*n,0),lazy(4*n,0);
    function<void(int,int,int,int,int,int)> upd=[&](int node,int l,int r,int ql,int qr,int val){
        if(qr<=l||r<=ql) return;
        if(ql<=l&&r<=qr){tree[node]=max(tree[node],val);lazy[node]=max(lazy[node],val);return;}
        if(lazy[node]){tree[2*node]=max(tree[2*node],lazy[node]);lazy[2*node]=max(lazy[2*node],lazy[node]);tree[2*node+1]=max(tree[2*node+1],lazy[node]);lazy[2*node+1]=max(lazy[2*node+1],lazy[node]);lazy[node]=0;}
        int mid=(l+r)/2;
        upd(2*node,l,mid,ql,qr,val);upd(2*node+1,mid,r,ql,qr,val);
        tree[node]=max(tree[2*node],tree[2*node+1]);
    };
    function<int(int,int,int,int,int)> qry=[&](int node,int l,int r,int ql,int qr)->int{
        if(qr<=l||r<=ql) return 0;
        if(ql<=l&&r<=qr) return tree[node];
        if(lazy[node]){tree[2*node]=max(tree[2*node],lazy[node]);lazy[2*node]=max(lazy[2*node],lazy[node]);tree[2*node+1]=max(tree[2*node+1],lazy[node]);lazy[2*node+1]=max(lazy[2*node+1],lazy[node]);lazy[node]=0;}
        int mid=(l+r)/2;
        return max(qry(2*node,l,mid,ql,qr),qry(2*node+1,mid,r,ql,qr));
    };
    vector<int> res; int maxH=0;
    for(auto& p:positions){
        int l=getIdx(p[0]),r=getIdx(p[0]+p[1]),sz=p[1];
        int curH=qry(1,0,n,l,r)+sz;
        upd(1,0,n,l,r,curH);
        maxH=max(maxH,curH);
        res.push_back(maxH);
    }
    return res;
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: My Calendar II (No Triple Booking)
**Difficulty:** Medium | **LC:** 731

```cpp
class MyCalendarTwo {
    map<int,int> diff; // coordinate difference array
public:
    bool book(int start, int end) {
        diff[start]++; diff[end]--;
        int cur=0;
        for(auto&[_,d]:diff){
            cur+=d;
            if(cur>=3){diff[start]--;diff[end]++;return false;}
        }
        return true;
    }
};
// Time: O(n log n) per booking | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Build segment tree for [1,3,5,7]. What is tree[1] and tree[3]?
<details><summary>Reveal</summary>
n=4. Leaves: tree[4]=1,tree[5]=3,tree[6]=5,tree[7]=7. tree[2]=tree[4]+tree[5]=4. tree[3]=tree[6]+tree[7]=12. tree[1]=tree[2]+tree[3]=16. tree[1]=16 (total sum), tree[3]=12 (sum of indices 2,3) ✓.
</details>

**Drill 2:** Query sum [1,3] in [1,3,5,7]. Trace l and r.
<details><summary>Reveal</summary>
l=1+4=5, r=3+4+1=8. l<r: l=5 is odd→res+=tree[5]=3, l=6. l=6,r=8: l/2=3, r/2=4. l=3,r=4: l=3 is odd→res+=tree[3]=12, l=4. l=4,r=4: l==r→stop. res=3+12=15 ✓ (3+5+7=15).
</details>

**Drill 3:** Point update: set arr[1]=10 in [1,3,5,7]. What nodes change?
<details><summary>Reveal</summary>
tree[5]=10. Parent: i=(4+1)/2=2. tree[2]=tree[4]+tree[5]=1+10=11. i=2/2=1. tree[1]=tree[2]+tree[3]=11+12=23. Nodes changed: tree[5],tree[2],tree[1]. New total sum=23 ✓.
</details>

**Drill 4:** Lazy propagation: why push down before accessing children?
<details><summary>Reveal</summary>
A lazy value at a node means "this range has a pending update not yet applied to children." If we access children without pushing down, they'll have stale values. The push-down ensures children reflect all ancestor updates before we combine them or query them. It's "lazy" because we delay work until necessary (a child is actually accessed).
</details>

**Drill 5:** When would you use a segment tree over a Fenwick Tree (BIT)?
<details><summary>Reveal</summary>
Fenwick Tree: simpler code, O(log n) for point update + prefix sum query. Best for sum queries with point updates. Segment Tree: more flexible — supports range min/max (BIT can't easily), lazy propagation for range updates, and arbitrary commutative-associative operations. Use BIT for sum queries, segment tree for min/max queries or range updates + range queries.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build | O(n) | O(n) |
| Point update | O(log n) | O(1) |
| Range query | O(log n) | O(1) |
| Range update (lazy) | O(log n) | O(1) |
| Range query (lazy) | O(log n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Can a segment tree handle non-commutative operations?**
A: Yes — as long as the operation is associative (you can parenthesize in any order). For range queries, the segment tree combines [l, mid] and [mid+1, r], which requires associativity but not commutativity.

**Q: What operations can lazy propagation support?**
A: Range add (lazy = sum of pending adds), range multiply (multiply and add), range set (override all values). For range min/max queries with range set updates: set the lazy value to the new value. The key is that the lazy operation must compose cleanly when multiple lazy values accumulate at the same node.

**Q: How do you implement a persistent segment tree?**
A: Copy-on-write: instead of modifying nodes in-place, create new nodes along the path from leaf to root. This creates O(log n) new nodes per update and allows querying any historical version. Space: O(n + q * log n) for q updates.

---

## 10. Cross-Pattern Connections

- **P97 (Fenwick Tree):** BIT is simpler for sum queries; segment tree is more general
- **P80 (Difference Arrays):** Difference array = O(1) range update, O(n) query; segment tree = O(log n) both
- **P84 (Sweep Line):** Segment tree on y-axis for rectangle union area computation
- **P79 (Prefix Sum):** Prefix sum = O(n) build, O(1) query, no updates; segment tree supports updates
