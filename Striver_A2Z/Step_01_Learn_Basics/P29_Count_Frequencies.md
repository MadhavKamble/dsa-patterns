# 🔥 Count Frequencies of Array Elements

> **GFG Classic** · **Difficulty:** Easy · **Step 1 — Basic Hashing · P29**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given an array of N integers, print the frequency (count of occurrences) of each element.

**Input:** Array of integers (1 ≤ N ≤ 10⁵, 1 ≤ arr[i] ≤ 10⁶)  
**Output:** Each element with its frequency (only once per unique element)

**Simple Example:**
```
Input:  [2, 3, 2, 3, 5]
Output: 2 → 2 times
        3 → 2 times
        5 → 1 time
```

---

## 🥉 Brute Force

### Idea
For each element, count how many times it appears by scanning the whole array. Mark visited to avoid recounting.

### Complexity
- **Time:** O(N²) · **Space:** O(N) for visited array

```cpp
void countFrequencies(vector<int>& arr) {
    int n = arr.size();
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (!visited[j] && arr[j] == arr[i]) {
                count++;
                visited[j] = true;
            }
        }
        cout << arr[i] << " -> " << count << "\n";
    }
}
// Time O(N²), Space O(N)
```

---

## 🥈 Better — Sorting

### Idea
Sort the array. Equal elements group together. One linear scan counts frequencies.

### Complexity
- **Time:** O(N log N) · **Space:** O(1) extra (in-place sort)

```cpp
void countFrequencies(vector<int> arr) {
    sort(arr.begin(), arr.end());
    int i = 0, n = arr.size();
    while (i < n) {
        int count = 1;
        while (i + count < n && arr[i + count] == arr[i]) count++;
        cout << arr[i] << " -> " << count << "\n";
        i += count;
    }
}
```

---

## 🥇 Optimal — Hash Map

### Key Observation

> 💡 Use an `unordered_map<int, int>` to count frequencies in a single O(N) pass.

### Algorithm
1. Create `unordered_map<int, int> freq`
2. For each element `x` in array: `freq[x]++`
3. Iterate over map and print each key-value pair

### Dry Run

**Input:** `[2, 3, 2, 3, 5]`

| Step | Element | freq map |
|------|---------|----------|
| 1 | 2 | {2:1} |
| 2 | 3 | {2:1, 3:1} |
| 3 | 2 | {2:2, 3:1} |
| 4 | 3 | {2:2, 3:2} |
| 5 | 5 | {2:2, 3:2, 5:1} |

**Output:**
```
2 → 2
3 → 2
5 → 1
```

### Complexity
- **Time:** O(N) average — each insertion/lookup O(1) amortized
- **Space:** O(K) — K = number of unique elements

### C++ Code
```cpp
/*
 * PROBLEM: Count frequency of each element in array
 *
 * BRUTE:   O(N²) nested loops
 * BETTER:  O(N log N) sort + linear scan
 * OPTIMAL: O(N) hash map
 *
 * EDGE CASES:
 *   - All elements same: map has one entry
 *   - All elements distinct: map has N entries
 *   - Negative numbers: unordered_map handles them fine
 *
 * COMPLEXITY: Time O(N) | Space O(K) where K = unique elements
 */

class Solution {
public:
    void printFrequency(vector<int>& arr) {
        unordered_map<int, int> freq;

        // count frequencies in one pass
        for (int x : arr) freq[x]++;

        // print each element and its frequency
        for (auto& [element, count] : freq) {
            cout << element << " -> " << count << "\n";
        }
    }

    // Return as map (useful for follow-up problems)
    unordered_map<int, int> getFrequency(vector<int>& arr) {
        unordered_map<int, int> freq;
        for (int x : arr) freq[x]++;
        return freq;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Single pass with `unordered_map<int,int> freq; freq[x]++;` — O(N)."

---

## 📝 Short Revision Notes

- `unordered_map` → O(1) average insert/lookup; `map` → O(log N) but sorted output
- `freq[x]++` works even if key doesn't exist (initializes to 0 first)
- Use `map` if you need sorted output; `unordered_map` for speed
- This pattern is the basis of: two-sum, anagram detection, majority element
- For small value range (e.g., 1–10⁶), can use array instead: `int freq[1000001] = {}`

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "count occurrences"
- "most/least frequent"
- "find duplicate / missing element"
- "two sum, anagram, group by value"

**I should think of:** Hash map frequency count

---

## ⚠️ Common Mistakes

❌ Using `map` (O(log N) per op) when `unordered_map` (O(1)) suffices  
❌ Forgetting that `unordered_map` iteration order is NOT insertion order  
❌ Using `freq[x]` in a conditional check: it auto-inserts 0 and corrupts the map  
❌ For competitive programming: `unordered_map` has worst-case O(N) per op due to hash collisions — use custom hash or `map` in critical sections  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Hash map for frequency counting
- **Reasoning:** Choosing right data structure for O(1) lookup
- **Optimization:** O(N²) → O(N log N) → O(N)

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Hash map | O(N) avg | O(K) | Best general solution |
| Array (value ≤ 10⁶) | O(N) | O(max_val) | Fastest for bounded values |
| Sorting | O(N log N) | O(1) | When sorted output needed |
| Brute force | O(N²) | O(N) | Never in interviews |

---

## 📚 Related Problems

- [ ] LeetCode #347 — Top K Frequent Elements
- [ ] LeetCode #1 — Two Sum (uses freq map)
- [ ] LeetCode #242 — Valid Anagram (char frequency)
- [ ] LeetCode #169 — Majority Element (freq > N/2)
- [ ] Striver Step 1 P30 — Highest/Lowest Frequency Element

---

## 🏆 Pattern Category

`Hashing` · `Arrays` · `Frequency Count`

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Count frequency of each element  
> **Approach:** `unordered_map<int,int> freq; for(x:arr) freq[x]++;`  
> **Key trick:** `freq[x]++` auto-initializes missing keys to 0  
> **Time:** O(N) | **Space:** O(K)  
> **Watch out for:** `map` vs `unordered_map` — use unordered for speed, ordered for sorted output
