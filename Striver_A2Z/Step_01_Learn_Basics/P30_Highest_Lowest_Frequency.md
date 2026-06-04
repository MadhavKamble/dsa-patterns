# 🔥 Find the Highest / Lowest Frequency Element

> **GFG Classic** · **Difficulty:** Easy · **Step 1 — Basic Hashing · P30**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given an array of N integers, find:
- The element with the **highest** frequency
- The element with the **lowest** frequency

**Input:** Array of integers (1 ≤ N ≤ 10⁵)  
**Output:** Element(s) with max and min frequency

**Key Observations:**
- Multiple elements may share max/min frequency
- Need two passes: one to build freq map, one to scan for max/min

**Simple Example:**
```
Input:  [1, 2, 3, 1, 2, 1]
Frequencies: {1:3, 2:2, 3:1}
Highest frequency: 1 (appears 3 times)
Lowest frequency:  3 (appears 1 time)
```

---

## 🥉 Brute Force

### Idea
For each unique element, count its occurrences. Track max and min.

### Complexity
- **Time:** O(N²) · **Space:** O(1)

```cpp
void highLowFrequency(vector<int>& arr) {
    int n = arr.size();
    vector<bool> visited(n, false);
    int maxFreq = 0, minFreq = INT_MAX;
    int maxElem = -1, minElem = -1;

    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        int count = 1;
        for (int j = i+1; j < n; j++) {
            if (!visited[j] && arr[j] == arr[i]) {
                count++; visited[j] = true;
            }
        }
        if (count > maxFreq) { maxFreq = count; maxElem = arr[i]; }
        if (count < minFreq) { minFreq = count; minElem = arr[i]; }
    }
    cout << "Max freq: " << maxElem << " (" << maxFreq << ")\n";
    cout << "Min freq: " << minElem << " (" << minFreq << ")\n";
}
```

---

## 🥇 Optimal — Hash Map + Single Scan

### Key Observation

> 💡 Build frequency map in one pass. Then find max/min in one scan of the map.  
> Total: O(N) time, O(K) space.

### Algorithm
1. Build `unordered_map<int,int> freq` in O(N)
2. Initialize `maxFreq = 0, minFreq = INT_MAX`
3. Scan map: update max/min element tracking
4. Print result

### Dry Run

**Input:** `[1, 2, 3, 1, 2, 1, 4, 4]`

**Step 1 — Build freq map:**

| Element | Count |
|---------|-------|
| 1 | 3 |
| 2 | 2 |
| 3 | 1 |
| 4 | 2 |

**Step 2 — Scan for max/min:**

| Element | Freq | maxFreq | maxElem | minFreq | minElem |
|---------|------|---------|---------|---------|---------|
| 1 | 3 | 3 | 1 | 3 | 1 |
| 2 | 2 | 3 | 1 | 2 | 2 |
| 3 | 1 | 3 | 1 | 1 | 3 |
| 4 | 2 | 3 | 1 | 1 | 3 |

**Output:** Highest = 1 (×3), Lowest = 3 (×1) ✅

### Complexity
- **Time:** O(N)
- **Space:** O(K) — K unique elements

### C++ Code
```cpp
/*
 * PROBLEM: Find elements with highest and lowest frequency
 *
 * APPROACH: Build freq map, then scan for max/min
 *
 * EDGE CASES:
 *   - All same: max freq = N, min freq = N (same element)
 *   - All distinct: max freq = 1, min freq = 1
 *   - Multiple elements tied for max/min: return any (or all)
 *
 * COMPLEXITY: Time O(N) | Space O(K)
 */

class Solution {
public:
    void findHighLowFrequency(vector<int>& arr) {
        unordered_map<int, int> freq;

        // pass 1: build frequency map
        for (int x : arr) freq[x]++;

        int maxFreq = 0, minFreq = INT_MAX;
        int maxElem = -1, minElem = -1;

        // pass 2: find max and min frequency elements
        for (auto& [element, count] : freq) {
            if (count > maxFreq) {
                maxFreq = count;
                maxElem = element;
            }
            if (count < minFreq) {
                minFreq = count;
                minElem = element;
            }
        }

        cout << "Highest frequency: " << maxElem
             << " (appears " << maxFreq << " times)\n";
        cout << "Lowest frequency:  " << minElem
             << " (appears " << minFreq << " times)\n";
    }

    // LeetCode-style: return {maxElem, minElem}
    pair<int,int> highLow(vector<int>& arr) {
        unordered_map<int, int> freq;
        for (int x : arr) freq[x]++;

        int maxFreq = 0, minFreq = INT_MAX;
        int maxElem = -1, minElem = -1;

        for (auto& [elem, cnt] : freq) {
            if (cnt > maxFreq) { maxFreq = cnt; maxElem = elem; }
            if (cnt < minFreq) { minFreq = cnt; minElem = elem; }
        }

        return {maxElem, minElem};
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Build freq map → single scan for max/min count. O(N) total."

---

## 📝 Short Revision Notes

- Two-pass: build map O(N), then scan map O(K) — total O(N)
- Initialize: `maxFreq=0`, `minFreq=INT_MAX`
- Ties: problem may ask for "any" or "all" — clarify with interviewer
- Extension: Top-K frequent elements (LeetCode 347) → use heap or bucket sort
- `auto& [elem, cnt]` is C++17 structured binding — clean way to iterate map

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "most/least frequent element"
- "top K frequent"
- "element appearing more/less than N/k times"

**I should think of:** Frequency map → scan / heap / bucket sort

---

## ⚠️ Common Mistakes

❌ Comparing frequencies directly from array without map → O(N²)  
❌ Initializing `minFreq = 0` instead of `INT_MAX` → never updates  
❌ Not handling ties (multiple elements with same max/min freq)  
❌ Confusing element with frequency when printing results  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Frequency map pattern
- **Reasoning:** Two-pass approach, correct initialization
- **Follow-up:** Can you return all elements tied for max/min? (Collect in a vector)

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Hash map (optimal) | O(N) | O(K) | Best |
| Sort + scan | O(N log N) | O(1) | Sorted order side benefit |
| Brute force | O(N²) | O(1) | Never |

**Extension — Top K frequent (LeetCode 347):**
- Min-heap of size K: O(N log K) time
- Bucket sort: O(N) time — bucket[freq] = [elements]

---

## 📚 Related Problems

- [ ] LeetCode #347 — Top K Frequent Elements
- [ ] LeetCode #692 — Top K Frequent Words
- [ ] LeetCode #169 — Majority Element (freq > N/2, use Boyer-Moore)
- [ ] LeetCode #229 — Majority Element II (freq > N/3)
- [ ] Striver Step 1 P29 — Count Frequencies (prerequisite)

---

## 🏆 Pattern Category

`Hashing` · `Frequency Count` · `Arrays`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why:** Direct application of frequency map. The pattern is used in almost every DSA interview.

---

## 📈 Progression Insight

**Harder variant:** Top K frequent elements → use min-heap (O(N log K)) or bucket sort (O(N))  
**Even harder:** Majority element (freq > N/k) → Boyer-Moore voting algorithm  
**Advanced:** Frequency of frequencies → histogram of the frequency map

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Find highest and lowest frequency elements  
> **Approach:** `unordered_map` freq count in O(N). Scan map tracking max/min.  
> **Key trick:** `maxFreq=0` (start low), `minFreq=INT_MAX` (start high)  
> **Time:** O(N) | **Space:** O(K)  
> **Watch out for:** Ties — multiple elements may share max or min frequency
