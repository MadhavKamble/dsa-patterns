# P95 — System Design Patterns for Coding Interviews

## 1. First-Timer Explanation

### What Is It?
**Design problems** ask you to implement a class with specific operations and complexity guarantees. They test whether you know which data structures to combine for the required operations. Common patterns: hash map + heap, hash map + ordered set, hash map + doubly linked list, and custom data structures.

### Design Patterns by Operation Profile
```
Need O(1) insert + O(1) lookup + O(1) delete random:
→ Array (for random delete) + Hash map (index lookup)
  Put element at random index, swap with last, pop_back

Need O(1) insert + O(log n) range queries:
→ Ordered set (std::set or multiset)

Need O(1) get/set + O(1) delete minimum:
→ Min-heap + "lazy deletion" (mark deleted, skip in heap)

Need O(1) insert + O(log n) kth largest:
→ Max-heap or order-statistics tree
```

### Insert/Delete/GetRandom O(1)
```
Array: [a, b, c, d]
Map: {a:0, b:1, c:2, d:3}

Delete 'b': 
  1. Swap b with last (d): [a, d, c, b]
  2. Update d's index: map[d] = 1
  3. Remove b from map, pop_back
  4. O(1) total

GetRandom: rand() % arr.size() → array index → O(1)
```

### When to Use
- "Insert/delete/getRandom all O(1)" → hash map + array (swap-with-last)
- "Find median in stream" → two heaps (P43)
- "Kth largest in stream" → min-heap of size k (P42)
- "Hit counter (last N seconds)" → circular buffer or deque
- "Rate limiter" → sliding window counter

---

## 2. Revision Card

**Recognition Signal:** "design a data structure with O(1) X and O(1) Y"

**Core Idea:** Map desired operations to their natural data structures. Combine structures when a single one can't do all ops in required time. Hash map bridges between structures.

**Trigger Keywords:** design, O(1), insert/delete/random, stream, online algorithm

**Complexity:** Depends on target — most design problems aim for O(1) or O(log n) per operation

---

## 3. Interview Tell Signs

- "Insert, delete, getRandom all O(1)" → hash map + array
- "Find median in data stream" → two heaps
- "Kth largest element in stream" → min-heap of size K
- "Snapshot array (versioned array)" → binary search per index
- "Time-based key-value store" → hash map + sorted list per key
- "Online stock span" → monotonic stack (P67)

---

## 4. C++ Template

```cpp
#include <unordered_map>
#include <vector>
#include <map>
#include <random>
using namespace std;

// ── Insert Delete GetRandom O(1) ──────────────────────────────────────────────
class RandomizedSet {
    unordered_map<int,int> mp; // value → index in arr
    vector<int> arr;
public:
    bool insert(int val) {
        if (mp.count(val)) return false;
        arr.push_back(val);
        mp[val] = arr.size() - 1;
        return true;
    }
    bool remove(int val) {
        if (!mp.count(val)) return false;
        int idx = mp[val], last = arr.back();
        arr[idx] = last; mp[last] = idx;
        arr.pop_back(); mp.erase(val);
        return true;
    }
    int getRandom() { return arr[rand() % arr.size()]; }
};

// ── Time-Based Key-Value Store ─────────────────────────────────────────────────
class TimeMap {
    unordered_map<string, map<int,string>> store; // key → {timestamp: value}
public:
    void set(string key, string value, int timestamp) {
        store[key][timestamp] = value;
    }
    string get(string key, int timestamp) {
        if (!store.count(key)) return "";
        auto& m = store[key];
        auto it = m.upper_bound(timestamp); // first timestamp > given
        if (it == m.begin()) return "";     // all timestamps > given
        return (--it)->second;
    }
};

// ── Snapshot Array ────────────────────────────────────────────────────────────
class SnapshotArray {
    vector<map<int,int>> arr; // arr[idx] → {snap_id: value}
    int snapId = 0;
public:
    SnapshotArray(int length) : arr(length) {
        for (auto& m : arr) m[0] = 0; // initialize all to 0 at snap 0
    }
    void set(int index, int val) { arr[index][snapId] = val; }
    int snap() { return snapId++; }
    int get(int index, int snap_id) {
        auto it = arr[index].upper_bound(snap_id);
        return (--it)->second;
    }
};
```

---

## 5. How to Present in Interview

**Verbal Script (RandomizedSet):**
> "To get O(1) random: store elements in an array and random-index into it. To get O(1) delete: swap the target with the last element, update the hash map, and pop_back. The hash map maps values to array indices for O(1) lookup."

**Verbal Script (TimeMap):**
> "Store a sorted map of (timestamp, value) pairs per key. For get, use `upper_bound(timestamp)` to find the first entry after the target, then back up one to get the last entry at or before. This is binary search on timestamps, O(log n) per query."

**Checklist:**
- [ ] RandomizedSet: after swapping, update `mp[last] = idx` (the moved element's new index)
- [ ] RandomizedSet: edge case when removing the last element (last == val, no swap needed but handle gracefully)
- [ ] TimeMap: `upper_bound` returns first > timestamp; decrement to get ≤ timestamp
- [ ] SnapshotArray: use binary search (map's upper_bound) for O(log snaps) get
- [ ] Always check iterator validity after upper_bound → decrement

---

## 6. Problems

### Problem 1: Insert Delete GetRandom O(1)
**Difficulty:** Medium | **LC:** 380

```cpp
class RandomizedSet {
    unordered_map<int,int> mp; vector<int> arr;
public:
    bool insert(int v){if(mp.count(v)) return false;arr.push_back(v);mp[v]=arr.size()-1;return true;}
    bool remove(int v){
        if(!mp.count(v)) return false;
        int idx=mp[v],last=arr.back();
        arr[idx]=last;mp[last]=idx;arr.pop_back();mp.erase(v);return true;
    }
    int getRandom(){return arr[rand()%arr.size()];}
};
// Time: O(1) all operations | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Time Based Key-Value Store
**Difficulty:** Medium | **LC:** 981

```cpp
class TimeMap {
    unordered_map<string,map<int,string>> st;
public:
    void set(string k,string v,int t){st[k][t]=v;}
    string get(string k,int t){
        if(!st.count(k)) return "";
        auto it=st[k].upper_bound(t);
        if(it==st[k].begin()) return "";
        return (--it)->second;
    }
};
// Time: O(log n) get, O(log n) set | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Snapshot Array
**Difficulty:** Medium | **LC:** 1146

```cpp
class SnapshotArray {
    vector<map<int,int>> arr; int sid=0;
public:
    SnapshotArray(int n):arr(n){{for(auto&m:arr)m[0]=0;}}
    void set(int i,int v){arr[i][sid]=v;}
    int snap(){return sid++;}
    int get(int i,int id){auto it=arr[i].upper_bound(id);return(--it)->second;}
};
// Time: O(log snaps) get | Space: O(n + total_sets)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Hit Counter
**Difficulty:** Medium | **LC:** 362

```cpp
class HitCounter {
    queue<int> hits;
public:
    void hit(int t){hits.push(t);}
    int getHits(int t){
        while(!hits.empty()&&hits.front()<=t-300) hits.pop();
        return hits.size();
    }
};
// Time: O(n) worst case getHits | Space: O(n) where n=hits in 300s
// O(1) alternative: circular buffer of size 300
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Find Median from Data Stream
**Difficulty:** Hard | **LC:** 295

```cpp
// Reference: P43 covers this with two-heap approach.
class MedianFinder {
    priority_queue<int> lo;
    priority_queue<int,vector<int>,greater<int>> hi;
public:
    void addNum(int n){
        lo.push(n);
        if(!hi.empty()&&lo.top()>hi.top()){hi.push(lo.top());lo.pop();}
        if(lo.size()>hi.size()+1){hi.push(lo.top());lo.pop();}
        else if(hi.size()>lo.size()){lo.push(hi.top());hi.pop();}
    }
    double findMedian(){
        return lo.size()>hi.size()?lo.top():(lo.top()+(double)hi.top())/2;
    }
};
// Time: O(log n) add, O(1) find | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Min Stack
**Difficulty:** Medium | **LC:** 155

```cpp
// Reference: P66 covers this.
class MinStack {
    stack<pair<int,int>> st; // {value, min_at_this_point}
public:
    void push(int v){st.push({v,st.empty()?v:min(v,st.top().second)});}
    void pop(){st.pop();}
    int top(){return st.top().first;}
    int getMin(){return st.top().second;}
};
// Time: O(1) all | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** RandomizedSet: current state arr=[1,2,3,4], mp={1:0,2:1,3:2,4:3}. Remove 2. Trace.
<details><summary>Reveal</summary>
idx=mp[2]=1. last=arr.back()=4. arr[1]=4 → arr=[1,4,3,4]. mp[4]=1. arr.pop_back() → arr=[1,4,3]. mp.erase(2). Final: arr=[1,4,3], mp={1:0,4:1,3:2} ✓.
</details>

**Drill 2:** TimeMap: set("a","bar",1), set("a","foo",3). get("a",2) and get("a",4)?
<details><summary>Reveal</summary>
store["a"]={1:"bar",3:"foo"}. get("a",2): upper_bound(2)→iterator to (3,"foo"). Decrement→(1,"bar"). Return "bar" ✓. get("a",4): upper_bound(4)→end(). Decrement→(3,"foo"). Return "foo" ✓.
</details>

**Drill 3:** Snapshot Array: set(0,5), snap(), set(0,6), get(0,0).
<details><summary>Reveal</summary>
Initial: arr[0]={0:0}. set(0,5): arr[0]={0:0,0:5}→actually sid=0: arr[0][0]=5 → arr[0]={0:5}. snap(): return 0, sid=1. set(0,6): arr[0][1]=6 → arr[0]={0:5,1:6}. get(0,0): upper_bound(0)→iterator to (1,6). Decrement→(0,5). Return 5 ✓.
</details>

**Drill 4:** When removing from RandomizedSet, what edge case needs special handling?
<details><summary>Reveal</summary>
When the element to remove is the LAST element in the array (idx == arr.size()-1). In this case: last = arr.back() = val (same element). The update mp[last]=idx tries to update mp[val], but we then erase mp[val]. The code still works correctly: arr[idx]=last (no-op since idx points to last), mp[last]=idx (sets index of val, then we erase it), arr.pop_back() removes it. No special case needed — the code handles it uniformly. But verify this edge case mentally during interviews.
</details>

**Drill 5:** Hit counter at timestamp 300: you have hits at 1,100,200,300. getHits(300)?
<details><summary>Reveal</summary>
Window is [300-300+1, 300] = [1, 300] (last 300 seconds inclusive). Hits at 1,100,200,300 are all in this window. getHits(300)=4. Now getHits(301): remove hits at t≤301-300=1, so remove hit at t=1. getHits(301)=3.
</details>

---

## 8. Complexity Cheatsheet

| Design Problem | Get/Query | Insert | Delete | Space |
|----------------|-----------|--------|--------|-------|
| RandomizedSet | O(1) | O(1) | O(1) | O(n) |
| TimeMap | O(log n) | O(log n) | — | O(n) |
| SnapshotArray | O(log snaps) | O(log snaps) | — | O(n) |
| Hit Counter | O(1) circular / O(n) queue | O(1) | O(1) | O(1) / O(n) |
| Median Stream | O(1) | O(log n) | — | O(n) |
| Min Stack | O(1) | O(1) | O(1) | O(n) |

---

## 9. Common Follow-up Questions

**Q: How do you extend RandomizedSet to allow duplicates?**
A: Store each value → list of indices (not single index). For O(1) delete: remove one index from the list, swap with last array element. Use `unordered_map<int, unordered_set<int>>`.

**Q: How do you implement a hit counter with O(1) for everything?**
A: Circular buffer of size 300 (seconds). Store `{timestamp, count}` pairs. On hit: if circular_buffer[t%300].timestamp == t, increment; else reset to (t, 1). On getHits: sum all counts where timestamp > t-300.

**Q: How to handle the TimeMap with very large timestamps?**
A: The `map<int,string>` per key handles arbitrary integers. Binary search (`upper_bound`) is O(log n) where n is the number of set calls for that key. This is already optimal.

---

## 10. Cross-Pattern Connections

- **P76 (LRU Cache):** Hash map + DLL is a design pattern for O(1) operations
- **P94 (LFU Cache):** Most complex cache design; builds on LRU concepts
- **P43 (Median Stream):** Two-heap design pattern for online median
- **P67 (Stock Span):** Stack-based online algorithm; same "design" framing
- **P79 (Prefix Sums):** TimeMap binary search over versions is similar to prefix queries
