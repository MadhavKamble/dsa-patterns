# 🔥 Left Rotate an Array (by 1 and by D places)

> **LeetCode #189** (Right Rotate = Left Rotate by N-D) · **Step 3 — Arrays · P05 & P06**

---

## 🧠 Problem Understanding

**P05:** Rotate array left by 1 position.  
`[1,2,3,4,5]` → `[2,3,4,5,1]`

**P06:** Rotate array left by D positions.  
`[1,2,3,4,5]`, D=2 → `[3,4,5,1,2]`

**Key Observation:** Rotation is equivalent to reversals. This is the key insight for O(1) space.

---

# Part 1 — Rotate by 1 (P05)

## 🥇 Algorithm
1. Save `temp = arr[0]`
2. Shift all elements left: `arr[i] = arr[i+1]` for i from 0 to N-2
3. `arr[N-1] = temp`

**Time:** O(N) · **Space:** O(1)

```cpp
void rotateByOne(vector<int>& arr) {
    int temp = arr[0];
    for (int i = 0; i < arr.size() - 1; i++)
        arr[i] = arr[i + 1];
    arr[arr.size() - 1] = temp;
}
```

---

# Part 2 — Rotate by D (P06)

## 🥉 Brute Force
Rotate by 1, D times. **Time:** O(N×D) · **Space:** O(1)

## 🥈 Better — Extra Array
Copy `arr[D..N-1]` then `arr[0..D-1]` into temp, copy back. **Time:** O(N) · **Space:** O(N)

## 🥇 Optimal — Reversal Algorithm

### Key Observation
> 💡 Left rotate by D = Reverse first D elements + Reverse last N-D elements + Reverse entire array.

```
arr = [1,2,3,4,5,6,7], D=3

Step 1: reverse arr[0..D-1] = [1,2,3] → [3,2,1]   → [3,2,1,4,5,6,7]
Step 2: reverse arr[D..N-1] = [4,5,6,7] → [7,6,5,4] → [3,2,1,7,6,5,4]
Step 3: reverse entire array              → [4,5,6,7,1,2,3]  ✅
```

**Why it works:**
- We want `arr[D..N-1] + arr[0..D-1]`
- Reversing sub-parts and then the whole achieves this

### Dry Run
`arr = [1,2,3,4,5]`, D=2

| Step | Operation | Array |
|------|-----------|-------|
| 1 | reverse [0..1] | [**2,1**,3,4,5] |
| 2 | reverse [2..4] | [2,1,**5,4,3**] |
| 3 | reverse all | [**3,4,5,1,2**] |

**Output:** `[3,4,5,1,2]` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * LEFT ROTATE BY D — Reversal Algorithm
 *
 * KEY INSIGHT: 3 reversals → O(N) time, O(1) space
 * Handle D > N by taking D = D % N
 *
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    void rotateLeft(vector<int>& arr, int d) {
        int n = arr.size();
        d = d % n;                           // handle D >= N
        if (d == 0) return;

        // step 1: reverse first d elements
        reverse(arr.begin(), arr.begin() + d);

        // step 2: reverse remaining n-d elements
        reverse(arr.begin() + d, arr.end());

        // step 3: reverse entire array
        reverse(arr.begin(), arr.end());
    }
};
```

**Right Rotate by D** = Left Rotate by `N-D`:
```cpp
void rotateRight(vector<int>& arr, int d) {
    rotateLeft(arr, arr.size() - d % arr.size());
}
```

---

## 🎤 Interview Explanation Script
> "For rotation by D, the brute force rotates one position D times — O(N×D). Using an extra array is O(N) time but O(N) space."

> "The optimal uses the reversal trick: reverse the first D elements, reverse the rest, then reverse the whole array. Three O(N) passes = O(N) total, O(1) space. The key insight: two sub-reversals followed by a full reversal rearranges the array exactly as needed."

> "Always handle `D = D % N` first — rotating by N is a no-op."

---

## 🧾 Recall Line
> "Reverse first D, reverse rest, reverse all. Three reversals = left rotate by D. D = D%N first."

## 📝 Short Revision Notes
- Always `D = D % N` to handle D ≥ N
- Right rotate by D = left rotate by N-D
- LC 189 asks for right rotation — convert: `d = (n - d % n) % n`
- Reversal algorithm: 3 `std::reverse` calls, each O(N) → total O(N), O(1) space
- Alternative: Juggling algorithm (GCD-based), same complexity

## ⚠️ Common Mistakes
❌ Forgetting `d = d % n` — unnecessary rotations for D ≥ N  
❌ Reversing wrong ranges — be precise with `begin + d`  
❌ Confusing left rotate (elements shift left) vs right rotate

## 🔥 What Interviewer Is Testing
- Reversal trick as a space-optimization technique
- Handling edge cases: D=0, D=N, D>N

## 📚 Related Problems
- [ ] LeetCode #189 — Rotate Array (right rotation)
- [ ] LeetCode #796 — Rotate String

## 🏆 Pattern Category
`Arrays` · `Reversal Trick` · `In-Place`

## ⏱️ 30-Second Revision
> P05 (by 1): save arr[0], shift all left, put saved at end.  
> P06 (by D): `d%=n`, reverse[0..d-1], reverse[d..n-1], reverse all. O(N)/O(1).
