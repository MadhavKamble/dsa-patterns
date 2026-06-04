# 🔥 Rearrange Array in Alternating Positive and Negative Items

> **LeetCode #2149** · **Difficulty:** Medium · **Step 3 — Arrays · P23**

---

## 🧠 Problem Understanding

Rearrange array so positives and negatives alternate, starting with positive. Relative order of positives and negatives must be preserved. Equal count of positives and negatives guaranteed.

**Input:** `[3,1,-2,-5,2,-4]` → **Output:** `[3,-2,1,-5,2,-4]`

---

## 🥉 Brute Force
Separate into two arrays, interleave. **Time:** O(N) · **Space:** O(N)

---

## 🥇 Optimal — Two Pointer Fill

### Key Observation
> 💡 Positives go at even indices (0,2,4,...), negatives at odd indices (1,3,5,...). Use two pointers: `posIdx=0, negIdx=1`.

### Algorithm
1. Create result array of size N
2. `posIdx = 0`, `negIdx = 1`
3. For each element:
   - If `x > 0`: `result[posIdx] = x`, `posIdx += 2`
   - Else: `result[negIdx] = x`, `negIdx += 2`
4. Return result

### Complexity
- **Time:** O(N) · **Space:** O(N)

```cpp
/*
 * REARRANGE ALTERNATING — positives at even indices, negatives at odd
 * Assumes equal counts of positives and negatives
 * Time O(N) | Space O(N)
 */
class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        int posIdx = 0, negIdx = 1;

        for (int x : nums) {
            if (x > 0) {
                result[posIdx] = x;
                posIdx += 2;
            } else {
                result[negIdx] = x;
                negIdx += 2;
            }
        }

        return result;
    }
};
```

**For unequal counts of positives and negatives** (GFG variant):
- Fill alternately until shorter side runs out
- Append remaining elements at end

```cpp
void rearrangeUnequal(vector<int>& arr) {
    vector<int> pos, neg;
    for (int x : arr) (x >= 0 ? pos : neg).push_back(x);

    int i = 0, p = 0, n = 0;
    while (p < pos.size() && n < neg.size())
        arr[i++] = (i % 2 == 0) ? pos[p++] : neg[n++];
    while (p < pos.size()) arr[i++] = pos[p++];
    while (n < neg.size()) arr[i++] = neg[n++];
}
```

---

## 🧾 Recall Line
> "Positives → even indices (0,2,4). Negatives → odd indices (1,3,5). Two write pointers, step by 2."

## 📝 Short Revision Notes
- LC 2149: equal counts guaranteed → clean two-pointer fill
- GFG variant: unequal counts → separate, interleave, append remaining
- O(N) time, O(N) space (can't avoid extra space if order must be preserved)

## ⚠️ Common Mistakes
❌ Assuming equal counts without reading problem constraints  
❌ Not preserving relative order (can't use in-place swap for this)

## 🏆 Pattern Category
`Arrays` · `Two Pointers` · `In-Place Arrangement`

## ⏱️ 30-Second Revision
> `posIdx=0, negIdx=1`. For each x: positive→`result[posIdx], posIdx+=2`; negative→`result[negIdx], negIdx+=2`. O(N)/O(N).
