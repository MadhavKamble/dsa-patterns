# P94 — LFU Cache Design

## 1. First-Timer Explanation

### What Is It?
**LFU Cache** (Least Frequently Used) evicts the item that has been accessed the fewest times. When tied by frequency, evict the least recently used among the tied items. This requires tracking frequency counts AND maintaining order within each frequency bucket.

### Data Structure Design
```
Three components:
1. key_to_val:  key → (value, frequency)
2. key_to_freq: key → frequency (redundant with above, often merged)
3. freq_to_keys: frequency → ordered set of keys (doubly linked list or ordered set)
   - Most recently used at one end, LRU at the other
4. min_freq: current minimum frequency (for O(1) eviction)

Get(key):
  1. Look up value
  2. Increment frequency (remove from old freq bucket, add to new)
  3. Update min_freq if old bucket is now empty

Put(key, value):
  1. If key exists: update value, increment frequency (like get)
  2. If new key:
     a. If at capacity: evict LRU from freq_to_keys[min_freq]
     b. Add new key with freq=1
     c. Set min_freq=1
```

### Visual Walkthrough
```
Cap=2. put(1,1), put(2,2), get(1), put(3,3)

After put(1,1): freq_to_keys={1:[1]}, key_freq={1:1}, min_freq=1
After put(2,2): freq_to_keys={1:[1,2]}, key_freq={1:1,2:1}, min_freq=1
get(1): key 1 freq 1→2. freq_to_keys={1:[2],2:[1]}, min_freq=1 (bucket 1 has key 2)
put(3,3): capacity! evict min_freq=1's LRU=key 2. Add key 3.
         freq_to_keys={1:[3],2:[1]}, min_freq=1
```

### When to Use
- "Design LFU Cache with O(1) operations" → three-data-structure approach
- "Find least frequently used element" → frequency + min-heap (O(log n))
- "Frequency-based prioritization" → similar structures

---

## 2. Revision Card

**Recognition Signal:** "LFU", "least frequently used", "evict by frequency"

**Core Idea:** `key→(val, freq)`, `freq→linked_list_of_keys`, `min_freq`. On access: move key from freq bucket to freq+1 bucket. Evict: remove tail of `freq_to_keys[min_freq]`.

**Trigger Keywords:** LFU, frequency, least frequent, eviction policy

**Complexity:** O(1) get, O(1) put (amortized)

---

## 3. Interview Tell Signs

- "Design cache that evicts least frequently used item" → LFU
- "Tie-breaking by recency" → LRU within each frequency bucket
- "Count-based eviction" → LFU (vs. time-based → LRU)
- Contrast: "LRU evicts least RECENTLY used" (time order), "LFU evicts least FREQUENTLY used" (count)

---

## 4. C++ Template

```cpp
#include <unordered_map>
#include <list>
using namespace std;

class LFUCache {
    int cap, minFreq;
    unordered_map<int,pair<int,int>> keyVal; // key → {value, freq}
    unordered_map<int,list<int>> freqKeys;   // freq → list of keys (LRU at front, LFU at back)
    unordered_map<int,list<int>::iterator> keyPos; // key → position in freq list

    void update(int key) {
        int freq = keyVal[key].second;
        // Remove from current frequency list
        freqKeys[freq].erase(keyPos[key]);
        if (freqKeys[freq].empty()) {
            freqKeys.erase(freq);
            if (minFreq == freq) minFreq++;
        }
        // Add to next frequency list (most recent = front)
        freq++;
        keyVal[key].second = freq;
        freqKeys[freq].push_front(key);
        keyPos[key] = freqKeys[freq].begin();
    }

public:
    LFUCache(int capacity) : cap(capacity), minFreq(0) {}

    int get(int key) {
        if (!keyVal.count(key)) return -1;
        update(key);
        return keyVal[key].first;
    }

    void put(int key, int value) {
        if (cap <= 0) return;
        if (keyVal.count(key)) {
            keyVal[key].first = value;
            update(key);
            return;
        }
        if ((int)keyVal.size() == cap) {
            // Evict LFU (LRU among minimum frequency)
            int evict = freqKeys[minFreq].back();
            freqKeys[minFreq].pop_back();
            if (freqKeys[minFreq].empty()) freqKeys.erase(minFreq);
            keyVal.erase(evict);
            keyPos.erase(evict);
        }
        // Insert new key with frequency 1
        keyVal[key] = {value, 1};
        freqKeys[1].push_front(key);
        keyPos[key] = freqKeys[1].begin();
        minFreq = 1;
    }
};
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "LFU needs three maps: key to value/frequency, frequency to ordered list of keys (most recent first), and key to position in the list. On access, I move a key from its current frequency list to the next-higher one. When the minimum frequency list becomes empty, min_freq increments (but only on access, not put). On eviction, I take the tail (LRU) of the minimum frequency list. All O(1) using doubly linked lists and hash maps."

**Checklist:**
- [ ] Track `min_freq` — only increment on access when current bucket empties
- [ ] After eviction, `minFreq` becomes 1 for new inserts (always reset to 1 on put)
- [ ] Use `list<int>` (doubly linked) + iterator map for O(1) arbitrary removal
- [ ] Check capacity > 0 (edge case for 0-capacity cache)
- [ ] When evicting and inserting at same time, evict first, then insert

---

## 6. Problems

### Problem 1: LFU Cache
**Difficulty:** Hard | **LC:** 460

```cpp
// Full implementation above in template section.
// Time: O(1) get and put | Space: O(capacity)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: LRU Cache (review from P76)
**Difficulty:** Medium | **LC:** 146

```cpp
// Reference: P76 covers LRU Cache in detail.
// Key difference: LRU uses one DLL ordered by recency; LFU uses multiple DLLs per frequency.
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: First Unique Character in a String
**Difficulty:** Easy | **LC:** 387

**Approach:** Frequency count then first pass for count==1.

```cpp
int firstUniqChar(string s) {
    vector<int> freq(26,0);
    for(char c:s) freq[c-'a']++;
    for(int i=0;i<(int)s.size();i++) if(freq[s[i]-'a']==1) return i;
    return -1;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Top K Frequent Elements
**Difficulty:** Medium | **LC:** 347

**Approach:** Bucket sort by frequency (same idea as LFU bucket grouping).

```cpp
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int,int> freq;
    for(int n:nums) freq[n]++;
    int n=nums.size();
    vector<vector<int>> bucket(n+1);
    for(auto&[num,f]:freq) bucket[f].push_back(num);
    vector<int> res;
    for(int i=n;i>=1&&(int)res.size()<k;i--)
        for(int x:bucket[i]) if((int)res.size()<k) res.push_back(x);
    return res;
}
// Time: O(n) | Space: O(n)
// Alternative: min-heap of size k → O(n log k)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: All O(1) Data Structure
**Difficulty:** Hard | **LC:** 432

**Approach:** Doubly linked list of frequency buckets + hash maps.

```cpp
class AllOne {
    struct Bucket { int count; set<string> keys; };
    list<Bucket> lst; // sorted by count ascending
    unordered_map<string,list<Bucket>::iterator> mp;

    list<Bucket>::iterator addBucket(list<Bucket>::iterator pos, int count) {
        return lst.insert(pos, {count, {}});
    }
public:
    void inc(string key) {
        if (!mp.count(key)) {
            if (lst.empty() || lst.begin()->count != 1)
                lst.push_front({1, {}});
            lst.begin()->keys.insert(key);
            mp[key] = lst.begin();
        } else {
            auto cur = mp[key]; auto nxt = next(cur);
            if (nxt == lst.end() || nxt->count != cur->count + 1)
                nxt = addBucket(nxt, cur->count + 1);
            nxt->keys.insert(key); mp[key] = nxt;
            cur->keys.erase(key);
            if (cur->keys.empty()) lst.erase(cur);
        }
    }
    void dec(string key) {
        auto cur = mp[key];
        if (cur->count == 1) { mp.erase(key); }
        else {
            auto prv = cur; --prv;
            if (cur == lst.begin() || prv->count != cur->count - 1)
                prv = addBucket(cur, cur->count - 1);
            prv->keys.insert(key); mp[key] = prv;
        }
        cur->keys.erase(key);
        if (cur->keys.empty()) lst.erase(cur);
    }
    string getMaxKey() { return lst.empty() ? "" : *lst.back().keys.begin(); }
    string getMinKey() { return lst.empty() ? "" : *lst.front().keys.begin(); }
};
// Time: O(1) amortized all operations
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Design Twitter
**Difficulty:** Medium | **LC:** 355

```cpp
class Twitter {
    int ts=0;
    unordered_map<int,vector<pair<int,int>>> tweets; // userId→[(ts,tweetId)]
    unordered_map<int,set<int>> following; // userId→followees
public:
    void postTweet(int userId,int tweetId){tweets[userId].push_back({ts++,tweetId});}
    vector<int> getNewsFeed(int userId){
        priority_queue<tuple<int,int,int,int>> pq; // (ts,tweetId,uid,idx)
        following[userId].insert(userId);
        for(int uid:following[userId]){
            auto&v=tweets[uid];
            if(!v.empty()) pq.push({v.back().first,v.back().second,uid,(int)v.size()-1});
        }
        vector<int> res;
        while(!pq.empty()&&(int)res.size()<10){
            auto[t,tid,uid,idx]=pq.top();pq.pop();
            res.push_back(tid);
            if(idx>0) pq.push({tweets[uid][idx-1].first,tweets[uid][idx-1].second,uid,idx-1});
        }
        return res;
    }
    void follow(int f,int e){following[f].insert(e);}
    void unfollow(int f,int e){following[f].erase(e);}
};
// Time: O(F*T + K log F) for getNewsFeed | Space: O(users + tweets)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** LFU Cap=2: put(1,1), put(2,2), get(1), put(3,3), get(2), get(3). What gets evicted when put(3,3) is called?
<details><summary>Reveal</summary>
After put(1,1): freq={1:1}, freqKeys={1:[1]}, minFreq=1. After put(2,2): freqKeys={1:[2,1]}(2 most recent). get(1): 1→freq2. freqKeys={1:[2],2:[1]}, minFreq=1. put(3,3): cap full! evict minFreq=1's LRU = key 2 (it's the only one and also the LRU in that bucket). freqKeys={1:[3],2:[1]}, minFreq=1. get(2): returns -1 (evicted). get(3): 3→freq2. freqKeys={2:[3,1]}, minFreq=2. Result: evicted key 2 ✓.
</details>

**Drill 2:** How does LFU differ from LRU in eviction policy?
<details><summary>Reveal</summary>
LRU: evicts the key that was accessed least RECENTLY (time since last access). LFU: evicts the key accessed least FREQUENTLY (total count). LRU forgets the past entirely after eviction; LFU rewards keys that are accessed many times. LFU is better for frequently-reused data; LRU is better for sequentially accessed data where old items won't be needed again.
</details>

**Drill 3:** Top K frequent elements in [1,1,1,2,2,3], k=2. Bucket sort approach.
<details><summary>Reveal</summary>
freq: {1:3, 2:2, 3:1}. Buckets: bucket[3]=[1], bucket[2]=[2], bucket[1]=[3]. Scan from high to low: bucket[3]→add 1(res=[1], size 1 < k=2). bucket[2]→add 2(res=[1,2], size=k). Stop. Result: [1,2] ✓.
</details>

**Drill 4:** Why is the `minFreq` always reset to 1 on `put()` for a new key?
<details><summary>Reveal</summary>
Every new key starts with frequency 1 (it's been accessed exactly once on insertion). Since 1 is the lowest possible frequency and we just added a key there, the minimum frequency is now at most 1. It might be lower if a key with frequency 0 existed (impossible), so it's exactly 1. Setting `minFreq=1` ensures the next eviction correctly targets frequency-1 keys, which includes this freshly inserted key (a natural LFU property: old, unaccessed keys get evicted before popular ones).
</details>

**Drill 5:** Design Twitter: why use a max-heap instead of iterating through all tweets?
<details><summary>Reveal</summary>
Each user can have many tweets, and there can be many followees. Iterating through all tweets is O(total tweets) which can be huge. The max-heap holds at most one pointer per followee (starting from their most recent tweet). We extract the global maximum timestamp, then push the next tweet from that same user. This is the K-way merge pattern — O(10 * log F) where F is the number of followees, much better than O(total tweets).
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| LFU get | O(1) | O(capacity) |
| LFU put | O(1) | O(capacity) |
| Top K frequent (bucket sort) | O(n) | O(n) |
| Top K frequent (heap) | O(n log k) | O(n + k) |
| All O(1) data structure | O(1) amortized | O(n) |
| Design Twitter getNewsFeed | O(F*T + 10 log F) | O(users + tweets) |

---

## 9. Common Follow-up Questions

**Q: What if frequency can be reset (e.g., cache cleared periodically)?**
A: Periodically clear all freq counts and reset min_freq=1. Or use a timestamp-weighted frequency that decays over time (time-decayed LFU).

**Q: LFU vs LRU: which is better in practice?**
A: LRU is simpler and works well for most workloads. LFU is better when some items are accessed much more frequently than others (e.g., popular web pages vs. one-time requests). Real caches often use approximations like clock algorithm (approximate LRU) or TinyLFU.

**Q: How would you implement a thread-safe LFU cache?**
A: Wrap all operations with a `mutex`. For better concurrency, use segment locking (lock only the affected frequency buckets) or a lock-free approach with atomic operations.

---

## 10. Cross-Pattern Connections

- **P76 (LRU Cache):** LFU contains an LRU policy within each frequency bucket — LFU builds on LRU
- **P66 (Frequency Stack):** Similar frequency-tracking structure; frequency stack uses max-freq
- **P42 (Top-K Elements):** Top-K frequent uses min-heap or bucket sort on frequencies
- **P45 (Task Scheduling):** Both involve scheduling/eviction based on frequency or recency
