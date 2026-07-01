# Accounts Merge

> **LeetCode #721** · **Difficulty:** Medium · **Step 15 — Graphs · P42**

---

## Problem Understanding

**What is it asking?**
Given `accounts[][]` where `accounts[i][0]` is the person's name and `accounts[i][1..]` are their emails, **merge accounts that share at least one email**. Return merged accounts with emails sorted, each list starting with the name.

**Input:** `accounts[][]` — list of `[name, email1, email2, ...]`
**Output:** Merged accounts — `[name, sorted_emails...]` for each merged group

**Example:**
```
accounts = [
  ["John","a@gmail.com","b@gmail.com"],
  ["John","b@gmail.com","c@gmail.com"],
  ["Mary","d@gmail.com"]
]

account 0 and 1 share "b@gmail.com" → merge
account 2 is separate

Output: [
  ["John","a@gmail.com","b@gmail.com","c@gmail.com"],
  ["Mary","d@gmail.com"]
]
```

**Key Observations:**
- DSU nodes = **account indices** (0 to n-1), NOT emails
- Email is the bridge: if two accounts share an email → union their indices
- `mapMailNode` maps `email → first account index` that owned it
- After all unions: group emails by their ultimate parent account index
- Name comes from `accounts[i][0]` where `i` is the root of the component
- Emails must be sorted alphabetically within each account

---

## Three-Phase Algorithm

```
Phase 1 — Union accounts sharing emails:
  For each account i, for each email:
    If email not seen → record mapMailNode[email] = i
    If email seen    → unionBySize(i, mapMailNode[email])

Phase 2 — Group emails by component root:
  For each (email, accountIndex) in mapMailNode:
    root = findUPar(accountIndex)
    mergedMail[root].push_back(email)

Phase 3 — Build answer:
  For each i where mergedMail[i] is non-empty:
    sort mergedMail[i]
    prepend accounts[i][0] (name of the root account)
    add to ans
```

---

## Why Account Indices as DSU Nodes (Not Emails)?

```
Option A — Email as DSU nodes:
  Need to map each unique email string to a node ID
  Requires two maps + extra bookkeeping

Option B — Account index as DSU node (used here):
  n accounts → n DSU nodes (0 to n-1), already indexed
  Email → account connection via mapMailNode
  Simpler: one map, union on index match

Account index approach is cleaner: the name is already at accounts[i][0],
and DSU naturally tracks which accounts merged.
```

---

## Dry Run

**accounts = [["John","a","b"],["John","b","c"],["Mary","d"]]** (n=3)

```
Phase 1:
  i=0, "a": not in map → mapMailNode["a"]=0
  i=0, "b": not in map → mapMailNode["b"]=0
  i=1, "b": in map (0) → union(1,0). parent=[0,0,2] (0 is root, size[0]=2)
  i=1, "c": not in map → mapMailNode["c"]=1
  i=2, "d": not in map → mapMailNode["d"]=2

mapMailNode: {a:0, b:0, c:1, d:2}

Phase 2 — group by root:
  "a" → findUPar(0)=0 → mergedMail[0]=["a"]
  "b" → findUPar(0)=0 → mergedMail[0]=["a","b"]
  "c" → findUPar(1)=0 → mergedMail[0]=["a","b","c"]  ← 1's root is 0
  "d" → findUPar(2)=2 → mergedMail[2]=["d"]

Phase 3 — build answer:
  i=0: mergedMail[0]=["a","b","c"] → sort → ["a","b","c"]
       name=accounts[0][0]="John"
       temp=["John","a","b","c"] → push to ans
  i=1: mergedMail[1] empty → skip
  i=2: mergedMail[2]=["d"] → sort → ["d"]
       name=accounts[2][0]="Mary"
       temp=["Mary","d"] → push to ans

ans=[["John","a","b","c"],["Mary","d"]] ✅
```

### Complexity
- **Time:** O(N×M×α(N) + N×M×log(M)) — N accounts, M emails per account; sort dominates
- **Space:** O(N×M) — map + mergedMail arrays

---

## Clean C++ Interview Code

```cpp
class DisjointSet {
public:
    vector<int> parent,size;
    DisjointSet(int n) {
        parent.resize(n+1);
        size.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
            size[i]=1;
        }
    }
    int findUPar(int node) {
        if(node==parent[node])
            return node;
        parent[node]=findUPar(parent[node]);
        return parent[node];
    }
    void unionBySize(int u, int v) {
        int ulp_u=findUPar(u);
        int ulp_v=findUPar(v);
        if(ulp_u==ulp_v) return;
        if(size[ulp_u]<size[ulp_v]){
            parent[ulp_u]=ulp_v;
            size[ulp_v]+=size[ulp_u];
        }else{
            parent[ulp_v]=ulp_u;
            size[ulp_u]+=size[ulp_v];
        }
    }
};

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n=accounts.size();
        DisjointSet ds(n);
        unordered_map<string,int> mapMailNode;
        for(int i=0;i<n;i++){
            for(int j=1;j<accounts[i].size();j++){
                string mail=accounts[i][j];
                if(mapMailNode.find(mail)==mapMailNode.end()){
                    mapMailNode[mail]=i;
                }else{
                    ds.unionBySize(i,mapMailNode[mail]);
                }
            }
        }
        vector<string> mergedMail[n];
        for(auto it: mapMailNode){
            string mail=it.first;
            int node=ds.findUPar(it.second);
            mergedMail[node].push_back(mail);
        }
        vector<vector<string>> ans;
        for(int i=0;i<n;i++){
            if(mergedMail[i].empty()) continue;
            sort(mergedMail[i].begin(),mergedMail[i].end());
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            for(auto &mail: mergedMail[i]){
                temp.push_back(mail);
            }
            ans.push_back(temp);
        }
        sort(ans.begin(),ans.end());
        return ans;
    }
};
```

> **`findUPar` style note:** Written as two lines (`parent[node]=findUPar(parent[node]); return parent[node];`) instead of the usual one-liner (`return parent[node]=findUPar(parent[node])`). Both are identical — same path compression.

---

## Key Data Structures

```
mapMailNode: unordered_map<string, int>
  email → first account index that owns it
  Used to detect shared emails and trigger union

mergedMail[n]: vector<string>[n]
  mergedMail[i] = all emails whose component root is i
  Only non-empty for root accounts after merging

Why accounts[i][0] for the name (not accounts[root][0])?
  i IS the root (we only process non-empty mergedMail[i])
  The root's name is accounts[root][0] → accounts[i][0] ✓
```

---

## Interview Explanation Script

> "I treat each account index as a DSU node. I scan every email in every account — if I've seen an email before, its two accounts must be the same person, so I union their indices."

> "After all unions, I scan `mapMailNode` and group each email under its account's ultimate parent (the component root). Then for each non-empty group, I sort the emails, prepend the name from `accounts[root][0]`, and add to the answer."

> "The key insight: DSU nodes are account indices — not emails. The email is just the trigger for the union. This avoids mapping emails to integer IDs."

---

## Recall Line *(10-Second Revision)*

> "Accounts merge: DSU on account indices. mapMailNode[email]=accountIdx. Shared email → union. Group emails by findUPar. Sort + prepend name."

---

## Short Revision Notes

- DSU nodes = account indices (0 to n-1), not emails — simpler mapping
- `j` starts at `1` in inner loop — skip `accounts[i][0]` (the name)
- `mapMailNode.find(mail)==mapMailNode.end()` → first time seeing email → record; else → union
- `mergedMail[node]` where `node=findUPar(it.second)` — push email under the root
- Name retrieval: `accounts[i][0]` where `i` is the non-empty `mergedMail` index = the root
- Final `sort(ans...)` — problem may require sorted outer list too

---

## Pattern Recognition Trigger

**When I see:**
- "Merge groups that share a common element"
- "Cluster items connected through a shared property"
- "Group accounts/people who have at least one thing in common"

**I should think of:** DSU where nodes = groups, shared element = trigger for union

---

## Common Mistakes

❌ DSU on email strings instead of account indices — needs extra ID mapping
❌ `j=0` in inner loop — accidentally treating the name as an email
❌ Using `mapMailNode[email]` (creates entry) instead of `find()` — silent bug
❌ Getting name from wrong index: always use `accounts[root][0]`, not some arbitrary account
❌ Forgetting to sort emails within each account

---

## What Interviewer Is Testing

- **DSU on non-trivial nodes** — account index, not the email string
- **Email as union trigger** — indirect connectivity
- **Phase separation:** union first, then group, then build answer
- **Sort requirement:** both within each account and final output

---

## Related Problems

- [ ] Striver Step 15 P39 — DSU Theory
- [ ] Striver Step 15 P41 — Network Connected (same DSU style)
- [ ] LeetCode #547 — Number of Provinces (component counting)
- [ ] LeetCode #684 — Redundant Connection

---

## Pattern Category

`Graphs` · `DSU` · `String` · `Hash Map` · `Grouping`

---

## 30-Second Last-Minute Revision

> **Accounts Merge:** DSU on account indices (0..n-1).
> Phase 1: for each email — first time → `mapMailNode[email]=i`; repeat → `union(i, mapMailNode[email])`.
> Phase 2: for each (email, idx) → `mergedMail[findUPar(idx)].push_back(email)`.
> Phase 3: for non-empty `mergedMail[i]` → sort emails, prepend `accounts[i][0]`, push to ans.
> **Key:** nodes = account indices. Email is just the union trigger.
