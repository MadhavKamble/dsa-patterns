# 🔥 Largest Subarray with 0 Sum & Count Subarrays with XOR = K

> **GFG + LeetCode** · **Difficulty:** Hard · **Step 3 — P34 & P35**

---

# P34 — Largest Subarray with 0 Sum

## 🧠 Problem Understanding

Find the length of the **longest subarray** with sum = 0.

**Input:** `[15,-2,2,-8,1,7,10,23]` → **Output:** `5` (subarray `[-2,2,-8,1,7]`)

---

## 🥇 Optimal — Prefix Sum + Hash Map

### Key Observation
> 💡 `sum(i..j) = prefix[j] - prefix[i-1]`. For sum(i..j) = 0, we need `prefix[j] = prefix[i-1]`.
> Store first occurrence of each prefix sum. When same prefix seen again → subarray between those indices has sum 0.

### Algorithm
1. `map<int,int> firstSeen = {0:-1}` (prefix 0 at index -1, before array)
2. `prefix=0, maxLen=0`
3. For `i` from 0 to N-1:
   - `prefix += arr[i]`
   - If `prefix` in map: `maxLen = max(maxLen, i - firstSeen[prefix])`
   - Else: `firstSeen[prefix] = i` (store first occurrence only for maximum length)

### Dry Run
`arr = [15,-2,2,-8,1,7,10,23]`

| i | arr[i] | prefix | In map? | maxLen |
|---|--------|--------|---------|--------|
| — | — | 0 | {0:-1} | 0 |
| 0 | 15 | 15 | no, store | 0 |
| 1 | -2 | 13 | no, store | 0 |
| 2 | 2 | 15 | yes! i-firstSeen[15]=2-0=2 | 2 |
| 3 | -8 | 7 | no, store | 2 |
| 4 | 1 | 8 | no, store | 2 |
| 5 | 7 | 15 | yes! 5-0=**5** | **5** |

**Output:** `5` ✅

### Complexity
- **Time:** O(N) · **Space:** O(N)

```cpp
/*
 * LARGEST SUBARRAY WITH 0 SUM — prefix sum + hash map
 * Key: same prefix value → subarray between those indices has sum 0
 * Store FIRST occurrence for maximum length
 * Time O(N) | Space O(N)
 */
class Solution {
public:
    int maxLen(vector<int>& arr) {
        unordered_map<int, int> firstSeen;
        firstSeen[0] = -1;                    // prefix 0 before array
        int prefix = 0, maxLen = 0;

        for (int i = 0; i < arr.size(); i++) {
            prefix += arr[i];
            if (firstSeen.count(prefix))
                maxLen = max(maxLen, i - firstSeen[prefix]);
            else
                firstSeen[prefix] = i;        // store only first occurrence
        }
        return maxLen;
    }
};
```

---

# P35 — Count Subarrays with XOR = K

## 🧠 Problem Understanding

Count the number of subarrays whose XOR equals K.

**Input:** `arr=[4,2,2,6,4]`, K=6 → **Output:** `4`

---

## 🥇 Optimal — Prefix XOR + Hash Map

### Key Observation
> 💡 Same as prefix sum but with XOR.  
> `XOR(i..j) = prefixXOR[j] ^ prefixXOR[i-1]`  
> We want `XOR(i..j) = K`, i.e., `prefixXOR[j] ^ K = prefixXOR[i-1]`
> → Count how many previous prefixes equal `currentXOR ^ K`

### Algorithm
1. `map<int,int> freq = {0:1}` (XOR prefix 0 has count 1)
2. `xorPref=0, count=0`
3. For each `x`:
   - `xorPref ^= x`
   - `count += freq[xorPref ^ K]` (how many previous prefixes give XOR=K)
   - `freq[xorPref]++`

### Dry Run
`arr=[4,2,2,6,4]`, K=6

| x | xorPref | xorPref^K=xorPref^6 | freq lookup | freq |
|---|---------|---------------------|-------------|------|
| — | 0 | — | — | {0:1} |
| 4 | 4 | 2 | freq[2]=0 | {0:1,4:1} |
| 2 | 6 | 0 | freq[0]=**1** → count=1 | {0:1,4:1,6:1} |
| 2 | 4 | 2 | freq[2]=0 | {0:1,4:2,6:1} |
| 6 | 2 | 4 | freq[4]=**2** → count=3 | {0:1,4:2,6:1,2:1} |
| 4 | 6 | 0 | freq[0]=**1** → count=4 | {0:1,...,6:2} |

**Output:** `4` ✅

### Complexity
- **Time:** O(N) · **Space:** O(N)

```cpp
/*
 * COUNT SUBARRAYS WITH XOR = K — prefix XOR + hash map
 * Want: xorPref[j] ^ xorPref[i-1] = K → look for xorPref[i-1] = xorPref[j]^K
 * Time O(N) | Space O(N)
 */
class Solution {
public:
    int subarraysWithXorK(vector<int>& arr, int k) {
        unordered_map<int, int> freq;
        freq[0] = 1;                      // empty prefix
        int xorPref = 0, count = 0;

        for (int x : arr) {
            xorPref ^= x;
            count += freq[xorPref ^ k];   // prefixes that form XOR=k with current
            freq[xorPref]++;
        }
        return count;
    }
};
```

---

## 🎤 Interview Explanation Script
> "Both problems use the **prefix technique with a hash map**."

> "For zero-sum subarrays: `sum(i..j) = 0` ↔ `prefix[j] == prefix[i-1]`. So I store prefix sums in a map; when I see the same prefix again, the subarray between those indices has sum 0. For maximum length, I store the FIRST occurrence."

> "For XOR subarrays: same idea with XOR instead of sum. `XOR(i..j) = K` ↔ `xorPrefix[j] ^ K == xorPrefix[i-1]`. I count how many previous prefixes equal `currentXOR ^ K`."

---

## 🧾 Recall Lines
> **P34:** `prefix same → zero-sum subarray`. Store first occurrence. Count = `i - firstSeen[prefix]`.  
> **P35:** `freq[xorPref ^ K]` gives count of valid previous prefixes. Initialize `freq[0]=1`.

## 📝 Short Revision Notes
- Both use prefix + hash map pattern
- P34: store index (first occurrence); P35: store frequency
- Both need `map[0] = -1` (P34) or `map[0] = 1` (P35) as initial value
- P35: `a^b=K ↔ a=b^K` (XOR property)

## ⚠️ Common Mistakes
❌ P34: Storing latest occurrence (not first) → gives minimum length, not maximum  
❌ P35: Forgetting `freq[0]=1` → misses subarrays starting from index 0  
❌ Both: Updating map BEFORE using it — in P34 store only if NOT seen; in P35 add count BEFORE updating freq

## 🏆 Pattern Category
`Arrays` · `Prefix Sum/XOR` · `Hashing`

## ⏱️ 30-Second Revision
> P34: prefix sum map. Same prefix → 0-sum subarray. Store first. Length = `i - firstSeen[prefix]`.  
> P35: prefix XOR map `freq[0]=1`. Each step: `count += freq[xorPref^K]`, then `freq[xorPref]++`.
