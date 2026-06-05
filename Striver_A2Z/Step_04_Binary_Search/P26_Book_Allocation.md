# 🔥 Book Allocation Problem

> **GFG Classic** · **Difficulty:** Hard · **Step 4 — Binary Search · P26**

---

## 🧠 Problem Understanding

**What is it asking?**
Allocate N books to M students. Each student must get at least 1 book, and books must be **contiguous** (each student gets a range of books). Minimize the **maximum pages** any student has to read.

**Input:** `books = [12, 34, 67, 90]`, `students = 2` → **Output:** `113`
(Allocate [12,34,67] to student 1 = 113 pages, [90] to student 2 = 90 pages. Max = 113.)

**Input:** `books = [10, 20, 30, 40]`, `students = 2` → **Output:** `60`
([10,20,30]=60, [40]=40. Max=60. Alternative: [10,20]=30, [30,40]=70. Max=70. First is better.)

**Constraints:** N ≥ M (enough books for each student), `1 ≤ M ≤ N ≤ 10⁵`, pages up to 10⁸

**Key Observations:**
- Impossible if `N < M` (not enough books)
- Search space: max pages ∈ [max(books), sum(books)]
- More pages allowed → easier to fit M students (monotone)
- Feasibility: greedy — assign books to current student until limit exceeded → new student

**Simple Example:**
```
books=[12,34,67,90], M=2
Binary search on answer X (max pages allowed per student):
X=113: [12,34,67]=113 ≤113, [90]=90 ≤113 → 2 students ✓
X=112: [12,34,67]=113 > 112, so [12,34]=46, [67,90]=157 > 112 → 3 students ✗... actually:
        student1: 12+34=46, 46+67=113>112 → stop, student1=[12,34]. student2: 67, 67+90=157>112 → 3 students ✗
Answer: 113
```

---

## 🥉 Brute Force Approach

Try every possible max from max(books) to sum(books). **Time:** O(sum × N) — too slow.

---

## 🥇 Optimal Approach — Binary Search on Max Pages

### Key Observation

> 💡 **Monotone:** Larger max pages → fewer students needed. Binary search for **minimum max pages** that allows exactly M students.
>
> **Search space:** `[max(books), sum(books)]`

### Algorithm
1. If `N < M`: return -1
2. `lo = max(books)`, `hi = sum(books)`
3. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - If `studentsNeeded(books, mid) <= M`: `hi = mid`
   - Else: `lo = mid + 1`
4. Return `lo`

### `studentsNeeded(books, maxPages)`:
1. `students = 1`, `currentPages = 0`
2. For each book:
   - If `currentPages + book > maxPages`: `students++`, `currentPages = 0`
   - `currentPages += book`
3. Return `students`

### Dry Run

**Input:** `books = [12, 34, 67, 90]`, `M = 2`
`lo = 90`, `hi = 203`

| lo | hi | mid | studentsNeeded(mid) | ≤2? | Action |
|----|-----|-----|---------------------|-----|--------|
| 90 | 203 | 146 | 12+34+67=113≤146, 90≤146 → 2 | ✅ | hi=146 |
| 90 | 146 | 118 | 12+34+67=113≤118, 90≤118 → 2 | ✅ | hi=118 |
| 90 | 118 | 104 | 12+34+67=113>104→new; 67+90=157>104→new; total=3 | ❌ | lo=105 |

Wait let me redo: mid=104

books=[12,34,67,90]:
- 12 ≤ 104, curr=12
- 12+34=46 ≤ 104, curr=46
- 46+67=113 > 104 → new student, curr=67, students=2
- 67+90=157 > 104 → new student, curr=90, students=3

studentsNeeded=3 > 2 → lo=105

| lo | hi | mid | studentsNeeded | ≤2? | Action |
|----|-----|-----|---------------|-----|--------|
| 105 | 118 | 111 | [12+34+67]=113>111→[12+34]=46, [67]=67, [90]=90 → 3 stud | ❌ | lo=112 |
| 112 | 118 | 115 | [12+34+67]=113≤115, [90]→ 2 stud | ✅ | hi=115 |
| 112 | 115 | 113 | [12+34+67]=113≤113, [90]→ 2 stud | ✅ | hi=113 |
| 112 | 113 | 112 | 113>112→3 stud | ❌ | lo=113 |
| lo=113==hi=113 → **return 113** ✅ |

### Complexity
- **Time:** O(N × log(sum(books)))
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "I binary search on the answer — the maximum pages any student reads."

> "The minimum possible is `max(books)` (the heaviest single book must fit). The maximum is `sum(books)` (one student reads everything)."

> "For feasibility at limit X: greedily assign books to the current student. When adding the next book would exceed X, start a new student. Count total students needed and compare to M."

> "Since we want to minimize the maximum, I use `lo < hi` with `hi = mid` when feasible."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * BOOK ALLOCATION — binary search on maximum pages
 *
 * PROBLEM UNDERSTANDING:
 *   Allocate N books contiguously to M students. Minimize maximum pages.
 *
 * KEY OBSERVATION:
 *   More max pages allowed → fewer students needed (monotone).
 *   Binary search for MINIMUM max pages where students needed ≤ M.
 *
 * FEASIBILITY: greedy — fill current student, overflow → new student.
 *
 * COMPLEXITY: Time O(N log sum) | Space O(1)
 */
class Solution {
private:
    int studentsNeeded(vector<int>& books, long long maxPages) {
        int students = 1;
        long long currentPages = 0;

        for (int book : books) {
            if (book > maxPages) return INT_MAX;  // single book exceeds limit
            if (currentPages + book > maxPages) {
                students++;
                currentPages = 0;
            }
            currentPages += book;
        }
        return students;
    }

public:
    int findPages(vector<int>& books, int m) {
        int n = books.size();
        if (n < m) return -1;  // not enough books

        long long lo = *max_element(books.begin(), books.end());
        long long hi = accumulate(books.begin(), books.end(), 0LL);

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (studentsNeeded(books, mid) <= m)
                hi = mid;        // valid, try fewer pages
            else
                lo = mid + 1;    // need more pages per student
        }

        return (int)lo;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS [max(books), sum(books)]. Greedy count students at limit mid. studentsNeeded≤M → hi=mid. Else lo=mid+1."

---

## 📝 Short Revision Notes

- Impossible: `N < M` → return -1
- `lo = max(books)` — must fit any single book
- Greedy: fill current student, new student when overflow
- Same template as P23 (Ship Packages) — identical code structure
- LC #410 (Split Array Largest Sum) is the same problem

---

## ⚠️ Common Mistakes

❌ Not handling `N < M` (impossible case)  
❌ `lo = 1` — must be at least max(books)  
❌ Integer overflow: sum of books up to 10⁵ × 10⁸ = 10¹³ → use `long long`  

---

## 📚 Related Problems

- [ ] GFG — Book Allocation Problem
- [ ] LeetCode #410 — Split Array Largest Sum (identical)
- [ ] LeetCode #1011 — Capacity to Ship Packages (P23 — same template)
- [ ] Striver Step 4 P27 — Split Array Largest Sum

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Greedy` · `Minimize Maximum`

---

## ⏱️ 30-Second Last-Minute Revision

> BS [max(books), sum(books)]. Greedy studentsNeeded. studentsNeeded≤M → hi=mid. Else lo=mid+1. Return lo. Check N≥M.
