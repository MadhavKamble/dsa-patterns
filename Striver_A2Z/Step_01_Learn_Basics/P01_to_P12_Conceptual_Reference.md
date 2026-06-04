# Step 1 — Conceptual Reference (P01–P12)

> These topics are **learning prerequisites**, not LeetCode problems.  
> Use this as a quick-revision reference before your interview.

---

## P01 — User Input / Output (C++)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;           // read integer
    cout << n << "\n";  // print (prefer \n over endl — faster)

    string s;
    cin >> s;           // reads single word
    getline(cin, s);    // reads full line with spaces

    return 0;
}
```

**Key points:**
- `cin >> ` skips whitespace; `getline` reads until newline
- Always use `"\n"` not `endl` in competitive programming (endl flushes buffer = slow)
- `ios_base::sync_with_stdio(false); cin.tie(NULL);` for fast I/O

---

## P02 — Data Types

| Type | Size | Range |
|------|------|-------|
| `int` | 4 bytes | –2.1B to +2.1B (±2×10⁹) |
| `long long` | 8 bytes | ±9.2×10¹⁸ |
| `float` | 4 bytes | ~7 decimal digits |
| `double` | 8 bytes | ~15 decimal digits |
| `char` | 1 byte | –128 to 127 |
| `bool` | 1 byte | 0 or 1 |

**Interview rule:** When values can exceed 2×10⁹ → use `long long`. When multiplying two ints → cast to `(long long)` first.

```cpp
long long result = (long long)a * b;  // prevents overflow
```

---

## P03 — If-Else Statements

```cpp
if (n % 2 == 0) cout << "Even";
else cout << "Odd";

// Ternary
string res = (n > 0) ? "positive" : "non-positive";
```

---

## P04 — Switch Statement

```cpp
switch (day) {
    case 1: cout << "Monday"; break;
    case 2: cout << "Tuesday"; break;
    default: cout << "Other"; break;
}
```

**Interview note:** Switch works on `int`, `char`, `enum` — NOT on `string` or `float`.

---

## P05 — Arrays and Strings

```cpp
int arr[5] = {1, 2, 3, 4, 5};      // fixed size
vector<int> v = {1, 2, 3, 4, 5};   // dynamic (prefer this)

string s = "hello";
s.length();     // 5
s[0];           // 'h'
s.substr(1, 3); // "ell" — start index, length
```

---

## P06 & P07 — For Loops and While Loops

```cpp
// Range-based for (C++11)
for (int x : arr) cout << x;

// Index-based
for (int i = 0; i < n; i++) { ... }

// While
int i = 0;
while (i < n) { ...; i++; }

// Do-while (executes at least once)
do { ...; i++; } while (i < n);
```

---

## P08 — Functions: Pass by Value vs Pass by Reference

```cpp
void byValue(int x) { x = 100; }   // original unchanged

void byRef(int &x) { x = 100; }    // original changes

void byPointer(int *x) { *x = 100; } // original changes

int main() {
    int a = 5;
    byValue(a);   // a = 5 still
    byRef(a);     // a = 100 now
}
```

**Interview rule:** Use `const &` for read-only large objects (avoids copy, prevents mutation).

```cpp
void process(const vector<int> &v) { ... }
```

---

## P09 — Time Complexity Basics

| Complexity | Name | Example |
|------------|------|---------|
| O(1) | Constant | Array access, hash lookup |
| O(log N) | Logarithmic | Binary search |
| O(N) | Linear | Single loop |
| O(N log N) | Linearithmic | Merge sort, heap sort |
| O(N²) | Quadratic | Nested loops |
| O(2ᴺ) | Exponential | Brute-force subsets |
| O(N!) | Factorial | Permutations |

**Constraint → complexity guide (for competitive programming):**

| N | Max allowed complexity |
|---|----------------------|
| N ≤ 10 | O(N!) |
| N ≤ 20 | O(2ᴺ) |
| N ≤ 500 | O(N³) |
| N ≤ 5000 | O(N²) |
| N ≤ 10⁶ | O(N log N) |
| N ≤ 10⁸ | O(N) |
| N ≤ 10¹⁸ | O(log N) |

---

## P10 — Pattern Printing (Build Logical Thinking)

The goal: build 2D loop intuition. Every pattern = outer loop (rows) + inner loop (cols) + condition.

```cpp
// Right triangle of stars (n=4)
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++) cout << "* ";
    cout << "\n";
}

// Inverted triangle
for (int i = n; i >= 1; i--) {
    for (int j = 1; j <= i; j++) cout << "* ";
    cout << "\n";
}

// Pyramid
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n - i; j++) cout << " ";   // spaces
    for (int j = 1; j <= 2*i - 1; j++) cout << "*"; // stars
    cout << "\n";
}

// Diamond = pyramid + inverted pyramid
```

**Key insight:** For row `i`, print `f(i)` spaces and `g(i)` stars — find the formula.

---

## P11 — C++ STL (Standard Template Library)

### Containers

```cpp
// Vector — dynamic array
vector<int> v;
v.push_back(5);     // O(1) amortized
v.pop_back();       // O(1)
v.size();           // O(1)
sort(v.begin(), v.end());  // O(N log N)

// Stack — LIFO
stack<int> st;
st.push(5);
st.top();
st.pop();

// Queue — FIFO
queue<int> q;
q.push(5);
q.front();
q.pop();

// Priority Queue (Max Heap by default)
priority_queue<int> pq;
priority_queue<int, vector<int>, greater<int>> minpq; // min heap

// Map — sorted key-value (BST under the hood)
map<string, int> mp;
mp["apple"] = 3;

// Unordered Map — hash map O(1) avg
unordered_map<int, int> ump;

// Set — sorted unique elements
set<int> s;
s.insert(5);
s.find(5);   // O(log N)
s.erase(5);

// Unordered Set — hash set O(1) avg
unordered_set<int> us;

// Pair
pair<int, int> p = {1, 2};
p.first; p.second;
```

### Algorithms

```cpp
sort(v.begin(), v.end());                         // ascending
sort(v.begin(), v.end(), greater<int>());          // descending
reverse(v.begin(), v.end());
*max_element(v.begin(), v.end());
*min_element(v.begin(), v.end());
accumulate(v.begin(), v.end(), 0);                 // sum
lower_bound(v.begin(), v.end(), x);               // first >= x
upper_bound(v.begin(), v.end(), x);               // first > x
binary_search(v.begin(), v.end(), x);             // true/false
```

---

## P12 — Java Collections (reference)

| C++ | Java equivalent |
|-----|----------------|
| `vector<int>` | `ArrayList<Integer>` |
| `map<K,V>` | `TreeMap<K,V>` |
| `unordered_map<K,V>` | `HashMap<K,V>` |
| `set<int>` | `TreeSet<Integer>` |
| `unordered_set<int>` | `HashSet<Integer>` |
| `priority_queue` | `PriorityQueue` |
| `stack` | `Deque<Integer>` (use as stack) |
| `queue` | `LinkedList<Integer>` |

---

## Quick Interview Cheat Sheet

| Need | Use |
|------|-----|
| Fast lookup | `unordered_map` / `unordered_set` |
| Sorted order | `map` / `set` |
| Max element fast | `priority_queue` (max heap) |
| Min element fast | `priority_queue<int, vector<int>, greater<int>>` |
| Sliding window | `deque` |
| BFS | `queue` |
| DFS | `stack` or recursion |
| Frequency count | `unordered_map<int,int>` |
