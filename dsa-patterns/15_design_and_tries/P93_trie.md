# P93 — Trie (Prefix Tree)

## 1. First-Timer Explanation

### What Is It?
A **Trie** (prefix tree) is a tree where each path from root to a node represents a string prefix. All strings sharing a prefix share the same path. It enables O(L) insert, search, and prefix queries where L = string length — much faster than hash map for prefix operations.

### Visual Walkthrough
```
Insert: "cat", "can", "car", "do", "dog"

root
├── c
│   └── a
│       ├── t (end)
│       ├── n (end)
│       └── r (end)
└── d
    └── o (end)
        └── g (end)

Search "can": root→c→a→n→isEnd=true ✓
StartsWith "ca": root→c→a, node exists ✓
Search "cab": root→c→a→b, no 'b' child → false
```

### Node Structure
```cpp
struct TrieNode {
    TrieNode* children[26] = {};   // null = no child
    bool isEnd = false;
};
```

### When to Use
- "Insert and search words" → Trie
- "Find all words with prefix" → Trie traversal from prefix node
- "Word search (grid + dictionary)" → Trie + DFS (P49)
- "Auto-complete" → Trie + collect all words from prefix node
- "XOR maximum" → Binary Trie (insert bits from MSB; greedily pick opposite bit)

### Common Mistakes
1. Not checking if `node == nullptr` before accessing `node->children`
2. `isEnd` only marks complete words — don't return true just because you reached a node
3. Delete: just clear `isEnd` (lazy deletion); true deletion requires checking all children are empty
4. Case sensitivity: usually lowercase only (index = c - 'a')

---

## 2. Revision Card

**Recognition Signal:** "prefix search", "word dictionary", "startsWith", "autocomplete"

**Core Idea:** Tree with 26 children per node (for lowercase). Navigate character by character. `isEnd` marks complete word. Missing child = prefix not present.

**Trigger Keywords:** prefix, trie, dictionary, autocomplete, word search, XOR trie

**Complexity:** O(L) insert/search/prefix; O(N×L) space for N words of average length L

---

## 3. Interview Tell Signs

- "Implement a data structure with insert, search, startsWith" → Trie
- "Find word in a grid with dictionary of allowed words" → Trie + DFS backtracking
- "Auto-complete: all words starting with prefix" → Trie traversal from prefix node
- "Maximum XOR of two numbers" → Binary trie (P72 also covers this with bitmask)
- "Word break / word break II" → Trie + DP or BFS

---

## 4. C++ Template

```cpp
#include <string>
#include <vector>
using namespace std;

// ── Trie Node ─────────────────────────────────────────────────────────────────
struct TrieNode {
    TrieNode* ch[26] = {};
    bool isEnd = false;
    int count = 0; // number of words with this prefix (optional)
};

// ── Trie Class ────────────────────────────────────────────────────────────────
class Trie {
    TrieNode* root;
public:
    Trie() : root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->ch[c-'a']) node->ch[c-'a'] = new TrieNode();
            node = node->ch[c-'a'];
            node->count++;
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!node->ch[c-'a']) return false;
            node = node->ch[c-'a'];
        }
        return node->isEnd;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->ch[c-'a']) return false;
            node = node->ch[c-'a'];
        }
        return true; // node exists = prefix exists
    }

    // Collect all words with given prefix
    void collect(TrieNode* node, string& path, vector<string>& res) {
        if (node->isEnd) res.push_back(path);
        for (int i = 0; i < 26; i++) {
            if (node->ch[i]) {
                path.push_back('a' + i);
                collect(node->ch[i], path, res);
                path.pop_back();
            }
        }
    }

    vector<string> wordsWithPrefix(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            if (!node->ch[c-'a']) return {};
            node = node->ch[c-'a'];
        }
        string path = prefix;
        vector<string> res;
        collect(node, path, res);
        return res;
    }
};

// ── Word Dictionary (with wildcard '.' matching) ──────────────────────────────
class WordDictionary {
    TrieNode* root;
    bool dfs(TrieNode* node, const string& word, int i) {
        if (!node) return false;
        if (i == (int)word.size()) return node->isEnd;
        if (word[i] != '.') return dfs(node->ch[word[i]-'a'], word, i+1);
        for (int k = 0; k < 26; k++)
            if (dfs(node->ch[k], word, i+1)) return true;
        return false;
    }
public:
    WordDictionary() : root(new TrieNode()) {}
    void addWord(string word) {
        TrieNode* n = root;
        for (char c:word) { if(!n->ch[c-'a']) n->ch[c-'a']=new TrieNode(); n=n->ch[c-'a']; }
        n->isEnd=true;
    }
    bool search(string word) { return dfs(root, word, 0); }
};
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "A Trie has nodes with 26 children (for lowercase) and an `isEnd` flag. Insert: navigate the path character by character, creating nodes as needed, set `isEnd` at the end. Search: navigate the path; return `isEnd` of the final node. StartsWith: navigate the path; return true if we reach the end without hitting a null child. All operations are O(L) where L = string length."

**Checklist:**
- [ ] Always check `node->ch[c-'a'] != nullptr` before accessing
- [ ] `search` must check `node->isEnd`, not just node existence
- [ ] `startsWith` just checks node existence (any prefix)
- [ ] Wildcard search: DFS through all 26 children when `'.'` encountered
- [ ] Word search grid: Trie + backtracking DFS; clear word in trie when found (optimization)

---

## 6. Problems

### Problem 1: Implement Trie (Prefix Tree)
**Difficulty:** Medium | **LC:** 208

```cpp
class Trie {
    struct Node { Node* ch[26]={}; bool end=false; };
    Node* root;
public:
    Trie():root(new Node()){}
    void insert(string w){Node* n=root; for(char c:w){if(!n->ch[c-'a'])n->ch[c-'a']=new Node();n=n->ch[c-'a'];}n->end=true;}
    bool search(string w){Node* n=root; for(char c:w){if(!n->ch[c-'a'])return false;n=n->ch[c-'a'];}return n->end;}
    bool startsWith(string p){Node* n=root; for(char c:p){if(!n->ch[c-'a'])return false;n=n->ch[c-'a'];}return true;}
};
// Time: O(L) per operation | Space: O(N*L) total
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Design Add and Search Words Data Structure
**Difficulty:** Medium | **LC:** 211

```cpp
class WordDictionary {
    struct Node{Node*ch[26]={};bool end=false;};
    Node* root;
    bool dfs(Node* n,const string& w,int i){
        if(!n) return false;
        if(i==(int)w.size()) return n->end;
        if(w[i]!='.') return dfs(n->ch[w[i]-'a'],w,i+1);
        for(int k=0;k<26;k++) if(dfs(n->ch[k],w,i+1)) return true;
        return false;
    }
public:
    WordDictionary():root(new Node()){}
    void addWord(string w){Node*n=root;for(char c:w){if(!n->ch[c-'a'])n->ch[c-'a']=new Node();n=n->ch[c-'a'];}n->end=true;}
    bool search(string w){return dfs(root,w,0);}
};
// Time: O(L) insert; O(26^L) worst case search with '.'; O(L) average
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Word Search II
**Difficulty:** Hard | **LC:** 212

```cpp
// Build trie from words, then DFS from each cell
// See P49 for full solution — uses Trie + DFS
vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    struct Node{Node*ch[26]={};string word="";};
    Node* root=new Node();
    for(auto& w:words){Node*n=root;for(char c:w){if(!n->ch[c-'a'])n->ch[c-'a']=new Node();n=n->ch[c-'a'];}n->word=w;}
    int m=board.size(),n=board[0].size();
    vector<string> res;
    function<void(int,int,Node*)> dfs=[&](int r,int c,Node* node){
        if(r<0||r>=m||c<0||c>=n||board[r][c]=='#') return;
        char ch=board[r][c]; Node* next=node->ch[ch-'a'];
        if(!next) return;
        if(!next->word.empty()){res.push_back(next->word);next->word="";}
        board[r][c]='#';
        dfs(r+1,c,next);dfs(r-1,c,next);dfs(r,c+1,next);dfs(r,c-1,next);
        board[r][c]=ch;
    };
    for(int i=0;i<m;i++) for(int j=0;j<n;j++) dfs(i,j,root);
    return res;
}
// Time: O(M*N*4^L) where L=max word length | Space: O(total word chars)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Replace Words
**Difficulty:** Medium | **LC:** 648

```cpp
string replaceWords(vector<string>& dictionary, string sentence) {
    struct Node{Node*ch[26]={};bool end=false;};
    Node*root=new Node();
    for(auto& w:dictionary){Node*n=root;for(char c:w){if(!n->ch[c-'a'])n->ch[c-'a']=new Node();n=n->ch[c-'a'];}n->end=true;}
    stringstream ss(sentence); string word, res="";
    while(ss>>word){
        Node*n=root; string root_w="";
        bool found=false;
        for(char c:word){
            if(!n->ch[c-'a']){break;}
            n=n->ch[c-'a']; root_w+=c;
            if(n->end){found=true;break;}
        }
        if(!res.empty()) res+=" ";
        res+=found?root_w:word;
    }
    return res;
}
// Time: O(D*L + S) D=dict size, L=avg word len, S=sentence length
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Maximum XOR of Two Numbers in an Array (Binary Trie)
**Difficulty:** Medium | **LC:** 421

```cpp
int findMaximumXOR(vector<int>& nums) {
    struct Node{Node*ch[2]={};};
    Node* root=new Node();
    auto insert=[&](int n){Node*node=root;for(int i=31;i>=0;i--){int b=(n>>i)&1;if(!node->ch[b])node->ch[b]=new Node();node=node->ch[b];}};
    for(int n:nums) insert(n);
    int res=0;
    for(int n:nums){
        Node* node=root; int xorVal=0;
        for(int i=31;i>=0;i--){
            int b=(n>>i)&1, want=1-b;
            if(node->ch[want]){xorVal+=(1<<i);node=node->ch[want];}
            else node=node->ch[b];
        }
        res=max(res,xorVal);
    }
    return res;
}
// Time: O(32n) = O(n) | Space: O(32n) = O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Implement Magic Dictionary
**Difficulty:** Medium | **LC:** 676

**Approach:** For search(word), try replacing each character and check if result is in the Trie.

```cpp
class MagicDictionary {
    unordered_set<string> words;
public:
    void buildDict(vector<string>& dictionary){ for(auto&w:dictionary) words.insert(w); }
    bool search(string searchWord){
        for(int i=0;i<(int)searchWord.size();i++){
            char orig=searchWord[i];
            for(char c='a';c<='z';c++){
                if(c==orig) continue;
                searchWord[i]=c;
                if(words.count(searchWord)) return true;
            }
            searchWord[i]=orig;
        }
        return false;
    }
};
// Time: O(n*26) per search | Space: O(total word chars)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Insert "apple" and "app" into a Trie. What does search("app") return?
<details><summary>Reveal</summary>
After inserting "apple": path a→p→p→l→e (isEnd=true at 'e'). After inserting "app": path a→p→p (isEnd=true at second 'p'). search("app"): navigate a→p→p. node exists, node.isEnd=true → return true ✓. Note: the same path is shared; we just mark isEnd at 'p' as well.
</details>

**Drill 2:** startsWith("app") after inserting ["apple","apply"]. What does it return?
<details><summary>Reveal</summary>
Both words create the path a→p→p. startsWith("app"): navigate a→p→p. Node exists → return true. The isEnd flag doesn't matter for startsWith — we just check node existence.
</details>

**Drill 3:** WordDictionary: add "bad" and "dad". Search ".ad". Trace the DFS.
<details><summary>Reveal</summary>
i=0, word[0]='.'. Try all 26 children of root. Only 'b' and 'd' children exist. Try 'b'(k=1): dfs(node_b, ".ad", 1). word[1]='a': go to node_b's 'a' child. word[2]='d': go to 'a' child's 'd' child. i=3=|word|, node.end=true → return true. Found ✓.
</details>

**Drill 4:** Binary Trie: insert [3,10,5,25,2,8]. For number 5 (binary 00101), what is the maximum XOR found?
<details><summary>Reveal</summary>
5=00000101 (32 bits). At each bit, we want the opposite. For bit 31 down to 5: all numbers are 0 at high bits. At bit 4: 5 has 0, want 1. 25=11001 has 1 at bit 4. xorVal += 16. Follow 25's path. At bit 3: 5 has 0, want 1. 25 has 1. xorVal+=8. At bit 2: 5 has 1, want 0. 25 has 0. xorVal+=4. At bit 1: 5 has 0, want 1. 25 has 0, no 1 → use 0. At bit 0: 5 has 1, want 0. 25 has 1 → use 1. xorVal = 16+8+4=28. 5^25=28 ✓.
</details>

**Drill 5:** Replace words in "the cattle was rattled by the battery" with dict=["cat","bat","rat"]. What is the result?
<details><summary>Reveal</summary>
Build trie: "cat"→end at t, "bat"→end at t, "rat"→end at t. Words: "the"→no prefix match→"the". "cattle"→c→a→t(end!)→found root "cat". "was"→no match→"was". "rattled"→r→a→t(end!)→"rat". "by"→no match→"by". "the"→"the". "battery"→b→a→t(end!)→"bat". Result: "the cat was rat by the bat" ✓.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Insert word | O(L) | O(L) per word |
| Search word | O(L) | O(1) |
| StartsWith prefix | O(L) | O(1) |
| Collect all words with prefix | O(L + output) | O(output) |
| Word search grid | O(M×N×4^L) | O(total dict chars) |
| Max XOR (binary trie) | O(32n) | O(32n) |

---

## 9. Common Follow-up Questions

**Q: How do you delete a word from a Trie?**
A: Lazy deletion: just set `isEnd = false`. For true deletion, recursively delete nodes bottom-up if they have no children and `isEnd == false`. This requires either parent tracking or a post-order recursive approach.

**Q: How would you implement autocomplete returning the top K suggestions?**
A: Navigate to the prefix node, then collect all words via DFS. If words have associated counts (search frequencies), use a min-heap of size K to maintain top K. Or sort by frequency during collection.

**Q: Can a Trie handle unicode or large alphabets?**
A: Replace the fixed 26-child array with `unordered_map<char, TrieNode*>`. This trades O(26) per node to O(actual_children) per node, reducing space at the cost of hash map overhead.

---

## 10. Cross-Pattern Connections

- **P49 (Word Search):** Word Search II is the canonical Trie + backtracking problem
- **P86 (KMP):** Aho-Corasick extends Trie with failure links (like KMP's LPS) for multi-pattern matching
- **P72 (Bit Tricks):** Binary Trie for max XOR; bitmask approach is the non-trie alternative
- **P93 → P94 (LFU Cache):** Both involve designing data structures with specific complexity guarantees
