# P64 — Monotonic Stack

## 1. First-Timer Explanation

### What Is It?
A **monotonic stack** maintains elements in a strictly increasing or decreasing order. When a new element breaks the monotone property, we pop elements from the stack (processing them with the new element as their "next greater/smaller" answer) until the stack is monotone again, then push the new element.

### Analogy
Imagine a stack of bowling balls sorted by size (smallest on top). When a new ball arrives that's bigger than the top, you remove the top ones one by one, recording that this big ball is the "next bigger ball" for each removed ball, until you find a ball bigger than the new arrival (or the stack is empty). Then place the new ball on top.

### Visual Walkthrough — Next Greater Element
```
nums = [4, 1, 2, 3]
Find next greater element for each position.

Stack (stores indices): []

i=0, nums[0]=4: empty stack, push 0 → stack=[0]
i=1, nums[1]=1: 1 < 4 (stack top), push 1 → stack=[0,1]
i=2, nums[2]=2: 2 > 1 → pop 1, result[1]=2; 2 < 4 → push 2 → stack=[0,2]
i=3, nums[3]=3: 3 > 2 → pop 2, result[2]=3; 3 < 4 → push 3 → stack=[0,3]

End: remaining in stack (0,3) → no next greater → result[-1]
Final result: [-1, 2, 3, -1]
```

### Key Patterns
- **Next Greater Element:** Monotone DECREASING stack (larger elements stay at bottom)
- **Next Smaller Element:** Monotone INCREASING stack
- **Largest Rectangle / Trapping Rain Water:** Uses spans between popped elements

### When to Use
- "Next greater/smaller element for each position"
- "Largest rectangle in histogram"
- "Trap rainwater"
- "Stock span problem"
- Any problem requiring O(n) instead of O(n²) "nearest boundary" computation

### Common Mistakes
1. Pushing values vs indices — for span/width calculations, push indices
2. Wrong stack type (increasing vs decreasing)
3. Forgetting to handle remaining elements in stack after the loop
4. Daily temperatures: result = i - stack.top(), not nums[i] - nums[stack.top()]

---

## 2. Revision Card

**Recognition Signal:** "next greater/smaller", "nearest larger/smaller to left/right", "maximum area/width"

**Core Idea:** Maintain stack in monotone order. When new element breaks order, pop and process (the new element is the answer for the popped element). Push new element.

**Trigger Keywords:** next greater, span, largest rectangle, trap water, daily temperatures, visible buildings

**Complexity:** O(n) time (each element pushed/popped at most once), O(n) space

---

## 3. Interview Tell Signs

- "Find next larger element" → decreasing monotonic stack
- "Find previous smaller element" → increasing monotonic stack (scan right to left)
- "Largest rectangle under histogram" → monotonic stack with width calculation
- "Stock span problem" → stack of (price, count) pairs

---

## 4. C++ Template

```cpp
#include <stack>
#include <vector>
using namespace std;

// ── Next Greater Element (decreasing stack) ───────────────────────────────────
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, -1);
    stack<int> stk; // stores indices, decreasing values
    
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && nums[stk.top()] < nums[i]) {
            res[stk.top()] = nums[i]; // nums[i] is the next greater for stk.top()
            stk.pop();
        }
        stk.push(i);
    }
    return res; // remaining in stack: -1 (no next greater)
}

// ── Largest Rectangle in Histogram ───────────────────────────────────────────
int largestRectangleArea(vector<int>& heights) {
    stack<int> stk; // increasing stack of indices
    int maxArea = 0, n = heights.size();
    
    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i]; // sentinel 0 at end
        while (!stk.empty() && heights[stk.top()] > h) {
            int height = heights[stk.pop(), stk.empty() ? -1 : stk.top()]; // WRONG
            // Correct:
            int top = stk.top(); stk.pop();
            int width = stk.empty() ? i : i - stk.top() - 1;
            maxArea = max(maxArea, heights[top] * width);
        }
        stk.push(i);
    }
    return maxArea;
}
```

**Corrected Histogram Template:**
```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> stk;
    int maxArea = 0, n = heights.size();
    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
        while (!stk.empty() && heights[stk.top()] > h) {
            int top = stk.top(); stk.pop();
            int width = stk.empty() ? i : i - stk.top() - 1;
            maxArea = max(maxArea, heights[top] * width);
        }
        stk.push(i);
    }
    return maxArea;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Monotonic stack processes 'nearest boundary' queries in O(n). For next greater element, I maintain a decreasing stack of indices. For each new element: while the stack top's value is less than current, pop it — current is its next greater. Then push current. Elements remaining after the loop have no next greater → -1. Each element is pushed and popped at most once → O(n) total."

**Checklist:**
- [ ] Store indices (not values) when width/span calculations are needed
- [ ] Determine stack type: decreasing for NGE, increasing for NSE
- [ ] Handle remaining stack elements after loop
- [ ] For histogram: sentinel 0 at end flushes the stack
- [ ] Width formula: `i - stk.top() - 1` (between previous boundary and current)

---

## 6. Problems

### Problem 1: Next Greater Element I
**Difficulty:** Easy | **LC:** 496

```cpp
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    unordered_map<int,int> nextGreater;
    stack<int> stk;
    for (int x : nums2) {
        while (!stk.empty() && stk.top() < x) {
            nextGreater[stk.top()] = x; stk.pop();
        }
        stk.push(x);
    }
    vector<int> res;
    for (int x : nums1) res.push_back(nextGreater.count(x) ? nextGreater[x] : -1);
    return res;
}
// Time: O(m+n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Daily Temperatures
**Difficulty:** Medium | **LC:** 739

```cpp
vector<int> dailyTemperatures(vector<int>& T) {
    int n = T.size();
    vector<int> res(n, 0);
    stack<int> stk; // indices, decreasing temperatures
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && T[stk.top()] < T[i]) {
            res[stk.top()] = i - stk.top(); stk.pop();
        }
        stk.push(i);
    }
    return res;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Largest Rectangle in Histogram
**Difficulty:** Hard | **LC:** 84

```cpp
int largestRectangleArea(vector<int>& heights) {
    stack<int> stk;
    int maxArea = 0, n = heights.size();
    for (int i = 0; i <= n; i++) {
        int h = (i == n) ? 0 : heights[i];
        while (!stk.empty() && heights[stk.top()] > h) {
            int top = stk.top(); stk.pop();
            int width = stk.empty() ? i : i - stk.top() - 1;
            maxArea = max(maxArea, heights[top] * width);
        }
        stk.push(i);
    }
    return maxArea;
}
// Time: O(n) | Space: O(n)
// Key: width = i - stk.top() - 1 (distance between two boundaries)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Trapping Rain Water
**Difficulty:** Hard | **LC:** 42

**Approach (Stack):** Maintain increasing stack. When a taller bar is found, water is trapped between the valley.

```cpp
int trap(vector<int>& height) {
    stack<int> stk; // indices, decreasing heights (stack = valley walls)
    int water = 0;
    for (int i = 0; i < (int)height.size(); i++) {
        while (!stk.empty() && height[stk.top()] < height[i]) {
            int bottom = stk.top(); stk.pop();
            if (stk.empty()) break;
            int width = i - stk.top() - 1;
            int waterHeight = min(height[stk.top()], height[i]) - height[bottom];
            water += width * waterHeight;
        }
        stk.push(i);
    }
    return water;
}
// Time: O(n) | Space: O(n)
// Alternative O(1) space: two-pointer (see P79)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Sum of Subarray Minimums
**Difficulty:** Medium | **LC:** 907

**Approach:** For each element, find its "span" as the minimum: previous smaller on left, next smaller on right. Contribution = element × left_span × right_span.

```cpp
int sumSubarrayMins(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    int n = arr.size();
    vector<int> left(n), right(n);
    
    // Previous smaller element
    stack<int> stk;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) stk.pop();
        left[i] = stk.empty() ? i + 1 : i - stk.top();
        stk.push(i);
    }
    
    // Next smaller or equal element
    while (!stk.empty()) stk.pop();
    for (int i = n-1; i >= 0; i--) {
        while (!stk.empty() && arr[stk.top()] > arr[i]) stk.pop();
        right[i] = stk.empty() ? n - i : stk.top() - i;
        stk.push(i);
    }
    
    long long ans = 0;
    for (int i = 0; i < n; i++)
        ans = (ans + (long long)arr[i] * left[i] * right[i]) % MOD;
    return ans;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Maximal Rectangle (Binary Matrix)
**Difficulty:** Hard | **LC:** 85

**Approach:** Build histogram for each row, then apply largest rectangle in histogram.

```cpp
int maximalRectangle(vector<vector<char>>& matrix) {
    if (matrix.empty()) return 0;
    int cols = matrix[0].size();
    vector<int> heights(cols, 0);
    int maxArea = 0;
    
    auto largestRect = [&]() {
        stack<int> stk;
        int area = 0;
        for (int i = 0; i <= cols; i++) {
            int h = (i == cols) ? 0 : heights[i];
            while (!stk.empty() && heights[stk.top()] > h) {
                int top = stk.top(); stk.pop();
                int w = stk.empty() ? i : i - stk.top() - 1;
                area = max(area, heights[top] * w);
            }
            stk.push(i);
        }
        return area;
    };
    
    for (auto& row : matrix) {
        for (int c = 0; c < cols; c++)
            heights[c] = (row[c] == '0') ? 0 : heights[c] + 1;
        maxArea = max(maxArea, largestRect());
    }
    return maxArea;
}
// Time: O(rows * cols) | Space: O(cols)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** NGE for [2,1,2,4,3]. Trace the stack.
<details><summary>Reveal</summary>
i=0: push 0, stack=[0(2)]. i=1: 1<2, push 1, stack=[0(2),1(1)]. i=2: 2>1 → pop 1, res[1]=2; 2≤2, push 2, stack=[0(2),2(2)]. i=3: 4>2 → pop 2, res[2]=4; 4>2 → pop 0, res[0]=4; push 3, stack=[3(4)]. i=4: 3<4, push 4, stack=[3(4),4(3)]. End: res[3]=-1, res[4]=-1. Result: [4,2,4,-1,-1].
</details>

**Drill 2:** Histogram largest rectangle [2,1,5,6,2,3]. The pop at i=4 (h=2) pops index 3 (h=6) and index 2 (h=5). What widths?
<details><summary>Reveal</summary>
Pop index 3 (h=6): stack top after pop = 2 (h=5). Width = 4-2-1=1. Area=6. Pop index 2 (h=5): stack top after pop = 1 (h=1). Width = 4-1-1=2. Area=10. These are the rectangles of height 6 (width 1) and height 5 (width 2).
</details>

**Drill 3:** Why push index 0 (a sentinel?) into the histogram stack?
<details><summary>Reveal</summary>
When stack is empty after popping, the bar extends all the way to the left boundary (width = i). Using the formula `width = stk.empty() ? i : i - stk.top() - 1` handles this. No explicit left sentinel needed.
</details>

**Drill 4:** Trapping rain water [4,2,0,3,2,5]. How much water is trapped?
<details><summary>Reveal</summary>
Use two-pointer: left boundary [4,...], right boundary [...,5]. Water at each position = min(max_left, max_right) - height. Water = (min(4,5)-2)+(min(4,5)-0)+(min(4,5)-3)+(min(4,5)-2) = 2+4+1+2 = 9.
</details>

**Drill 5:** Sum of subarray minimums: arr=[3,1,2,4]. For element arr[1]=1, what is its left span and right span?
<details><summary>Reveal</summary>
Left span: distance to previous smaller element. No smaller to the left → left span = i+1 = 2 (subarrays starting from index 0 or 1). Right span: distance to next smaller element. No smaller to the right → right span = n-i = 3. Contribution = 1 × 2 × 3 = 6. (Subarrays [3,1],[1],[1,2],[1,2,4],[3,1,2],[3,1,2,4] — 1 is min in all of these.)
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Next Greater Element | O(n) | O(n) |
| Daily Temperatures | O(n) | O(n) |
| Largest Rectangle | O(n) | O(n) |
| Trapping Rain Water (stack) | O(n) | O(n) |
| Sum of Subarray Minimums | O(n) | O(n) |
| Maximal Rectangle | O(R×C) | O(C) |

---

## 9. Common Follow-up Questions

**Q: What's the O(1) space solution for trapping rain water?**
A: Two pointers. Left and right move toward each other. The side with the smaller boundary height determines the water at that position: `water += min(maxL, maxR) - height[ptr]`.

**Q: Next greater element in a CIRCULAR array?**
A: Run the same algorithm twice (on doubled array, or use modular index). Each element gets two chances to be "defeated" by a larger element.

**Q: Can monotonic stack solve range queries?**
A: Partially — it computes "nearest boundary" queries efficiently. For arbitrary range min/max queries, use sparse table or segment tree.

---

## 10. Cross-Pattern Connections

- **P65 (Expression Evaluation):** Stack used differently — for operators and operands
- **P55 (Greedy Strings):** Remove K Digits uses monotonic stack
- **P79 (Prefix Sums):** Trapping rain water also solvable with prefix max arrays
- **P85 (Maximal Rectangle):** This pattern extended to 2D
- **P42 (Heap/Top-K):** Both process elements with a data structure; stack for boundary, heap for priority
