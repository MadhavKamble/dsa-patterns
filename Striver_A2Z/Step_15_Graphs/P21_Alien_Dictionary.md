# Alien Dictionary

> **GFG Problem / LeetCode #269** · **Difficulty:** Hard · **Step 15 — Graphs · P21**

---

## Problem Understanding

**What is it asking?**
Given a sorted dictionary of an alien language with `N` words and `K` unique characters, find the order of characters in the alien alphabet.

**Input:** `dict[]` — N words sorted in alien order, `N` = number of words, `K` = number of unique characters
**Output:** String of characters in alien alphabetical order (topological order of the character graph)

**Example:**
```
dict = ["baa", "abcd", "abca", "cab", "cad"]
K = 4 (a, b, c, d)

Compare adjacent pairs:
"baa" vs "abcd": b≠a → b comes after a → a→b
"abcd" vs "abca": d≠a → d comes after a → a→d... wait
  actually first diff: d≠a → in alien order "abcd"<"abca" means d<a → d→a? 
  No: s1="abcd", s2="abca", first diff at index 3: s1[3]='d', s2[3]='a'
  s1 comes before s2 in dict → d comes before a → d→a... 
  Hmm, let me redo:
  "baa" vs "abcd": first diff at 0: b vs a → "baa" < "abcd" → b comes before a → b→a
  "abcd" vs "abca": first diff at 3: d vs a → d comes before a → d→a  
  "abca" vs "cab": first diff at 0: a vs c → a comes before c → a→c
  "cab" vs "cad": first diff at 2: b vs d → b comes before d → b→d

Graph: b→a, d→a, a→c, b→d
Topo sort: b, d, a, c → "bdac"
```

**Key Observations:**
- Compare each pair of **adjacent** words — only adjacent pairs give ordering info
- For each pair, find the **first differing character** — that gives one edge in the graph
- Break after finding the first diff — subsequent characters give no info
- Run topological sort on the character graph to get the alien order
- Edge cases: prefix violation (longer word before shorter, all chars same) → invalid

---

## Optimal Approach — Graph Building + Kahn's Topo Sort

### Key Observation

> Each pair of adjacent words in the sorted dict gives at most one ordering constraint (the first differing character). Build a directed graph on K characters, then topological sort = alien alphabet order.
>
> Characters map to indices: `'a'→0, 'b'→1, ...` → work with integers, convert back at the end.

### Algorithm
1. For each adjacent word pair `(dict[i], dict[i+1])`:
   - Find first index `ptr` where `s1[ptr] != s2[ptr]`
   - Add edge `s1[ptr]-'a' → s2[ptr]-'a'` (s1's char comes before s2's char)
   - Break (only first diff gives info)
2. Run Kahn's topological sort on the K-node character graph
3. Convert topo order indices back to characters

### Dry Run

```
dict = ["baa","abcd","abca","cab","cad"], K=4

Pair 1: "baa" vs "abcd" → 'b'≠'a' at ptr=0 → edge: b→a (1→0)
Pair 2: "abcd" vs "abca" → 'd'≠'a' at ptr=3 → edge: d→a (3→0)
Pair 3: "abca" vs "cab"  → 'a'≠'c' at ptr=0 → edge: a→c (0→2)
Pair 4: "cab" vs "cad"   → 'b'≠'d' at ptr=2 → edge: b→d (1→3)

Graph edges: 1→0, 3→0, 0→2, 1→3
inDegree: 0→2, 1→0, 2→1, 3→1

Queue: [1] (only b has inDegree 0)
Process 1(b): topo=[b], inDegree[0]→1, inDegree[3]→0 → enqueue 3
Process 3(d): topo=[b,d], inDegree[0]→0 → enqueue 0
Process 0(a): topo=[b,d,a], inDegree[2]→0 → enqueue 2
Process 2(c): topo=[b,d,a,c]

Answer: "bdac" ✅
```

### Complexity
- **Time:** O(N × len + K) — N pairs × word length for graph building, K for topo sort
- **Space:** O(K + K²) — adjacency list + inDegree array

---

## Clean C++ Interview Code

```cpp
class Solution{
public:
    vector<int> topoSort(int V, vector<int> adj[]){
        int indegree[V]={0};
        for(int i=0;i<V;i++){
            for(auto it: adj[i]){
                indegree[it]++;
            }
        }
        queue<int> q;
        for(int i=0;i<V;i++){
            if(indegree[i]==0){
                q.push(i);
            }
        }
        vector<int> topo;
        while(!q.empty()){
            int node=q.front();
            topo.push_back(node);
            q.pop();
            for(auto it: adj[node]){
                indegree[it]--;
                if(indegree[it]==0){
                    q.push(it);
                }
            }
        }
        return topo;
    }
    string findOrder(string dict[], int N, int K){
        vector<int> adj[K];
        for(int i=0;i<N-1;i++){
            string s1=dict[i];
            string s2=dict[i+1];
            int len=min(s1.size(),s2.size());
            for(int ptr=0;ptr<len;ptr++){
                if(s1[ptr]!=s2[ptr]){
                    adj[s1[ptr]-'a'].push_back(s2[ptr]-'a');
                    break;
                }
            }
        }
        vector<int> topo=topoSort(K,adj);
        string ans="";
        for(auto it:topo){
            ans=ans+char(it+'a');
        }
        return ans;
    }
};
```

---

## Edge Cases (When No Valid Order Exists)

```
Case 1 — Prefix violation:
dict = ["abc", "ab"]
"abc" comes before "ab" but "ab" is a prefix of "abc"
→ impossible (in any valid ordering, shorter prefix should come first)
Detection: if all chars match and s1.size() > s2.size() → return ""

Case 2 — Cycle:
If the character graph has a cycle → topo.size() < K → return ""
```

```cpp
// With validity checks:
string findOrder(string dict[], int N, int K){
    vector<int> adj[K];
    for(int i=0;i<N-1;i++){
        string s1=dict[i];
        string s2=dict[i+1];
        int len=min(s1.size(),s2.size());
        bool found=false;
        for(int ptr=0;ptr<len;ptr++){
            if(s1[ptr]!=s2[ptr]){
                adj[s1[ptr]-'a'].push_back(s2[ptr]-'a');
                found=true;
                break;
            }
        }
        // prefix violation
        if(!found && s1.size()>s2.size()) return "";
    }
    vector<int> topo=topoSort(K,adj);
    // cycle check
    if(topo.size()!=K) return "";
    string ans="";
    for(auto it:topo) ans+=char(it+'a');
    return ans;
}
```

---

## Interview Explanation Script

> "I compare adjacent word pairs to extract character ordering constraints. For each pair, I find the first position where characters differ — that tells me the first character must come before the second in the alien alphabet. I add that as a directed edge in a graph on K nodes (characters a-z mapped to 0-K-1)."

> "After building the graph, I run Kahn's topological sort. The topo order of the graph = alien alphabetical order. I convert node indices back to characters."

> "Two invalid cases: prefix violation (longer word before its prefix — no ordering constraint can be extracted) and cycles in the character graph (contradictory constraints). Both return empty string."

---

## Recall Line *(10-Second Revision)*

> "Alien Dict: compare adjacent words → first diff char → directed edge. Kahn's topo sort = alien order. O(N×len + K)."

---

## Short Revision Notes

- Only adjacent word pairs give constraints — non-adjacent pairs are redundant
- Only the **first** differing character per pair adds an edge — `break` after finding it
- Characters → int indices: `c-'a'` → node; `node+'a'` → char back
- `topo.size() != K` after Kahn's → cycle → invalid input
- Prefix violation: no diff found AND `s1.size() > s2.size()` → invalid
- `N-1` pairs from `N` words → loop `i=0` to `N-2`

---

## Pattern Recognition Trigger

**When I see:**
- "Find character order from sorted dictionary"
- "Alien language alphabet ordering"
- "Derive ordering from comparisons"

**I should think of:** Build directed graph from constraints → topological sort

---

## Common Mistakes

❌ Comparing non-adjacent word pairs (only adjacent pairs give valid constraints)
❌ Not breaking after first diff char per pair
❌ Looping `i=0` to `N-1` instead of `N-2` → accesses `dict[N]` out of bounds
❌ Forgetting prefix violation check → invalid input passes silently
❌ Forgetting cycle check (`topo.size() != K`)

---

## What Interviewer Is Testing

- **Graph construction from word comparisons** — the insight to compare only adjacent pairs
- **Character-to-index mapping** and back
- **Edge case handling** — prefix violation and cycle
- **Connection to topo sort** — this is Kahn's applied to a non-obvious graph

---

## Related Problems

- [ ] Striver Step 15 P20 — Topological Sort (Kahn's Algorithm)
- [ ] LeetCode #207 — Course Schedule (Kahn's cycle detection)
- [ ] LeetCode #210 — Course Schedule II (return topo order)

---

## Pattern Category

`Graphs` · `Topological Sort` · `Kahn's Algorithm` · `String` · `DAG`

---

## 30-Second Last-Minute Revision

> **Alien Dict:** Compare adjacent words → first diff char gives edge `s1[ptr]→s2[ptr]`.
> Build graph on K nodes (char-'a'). Run Kahn's topo sort.
> `topo.size()!=K` → cycle → return "". Prefix violation → return "".
> Convert indices back: `char(node+'a')`.
> **Time:** O(N×len + K) | **Space:** O(K)
