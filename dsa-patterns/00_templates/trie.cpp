/*
 * ============================================================
 * TEMPLATE: Trie (Prefix Tree)
 * ============================================================
 * Use when: store/search a set of strings, prefix matching,
 *           autocomplete, word dictionary with wildcards
 * Time: O(L) per insert/search — L = string length
 * Space: O(N * ALPHABET_SIZE) — N = total chars in all strings
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: STANDARD TRIE (lowercase a-z)
// ─────────────────────────────────────────────────────────────

class Trie {
    struct TrieNode {
        TrieNode* children[26];  // one slot per lowercase letter
        bool isEnd;              // true if a word ends at this node

        TrieNode() : isEnd(false) {
            fill(children, children + 26, nullptr);
        }
    };

    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    // INSERT a word into the trie
    void insert(const string& word) {
        TrieNode* curr = root;

        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) {
                curr->children[idx] = new TrieNode();  // create node if missing
            }
            curr = curr->children[idx];
        }
        curr->isEnd = true;  // mark end of word
    }

    // SEARCH: does exactly this word exist?
    bool search(const string& word) {
        TrieNode* curr = root;

        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) return false;  // path doesn't exist
            curr = curr->children[idx];
        }
        return curr->isEnd;  // path exists, but only a word if isEnd
    }

    // STARTSWITH: does any word start with this prefix?
    bool startsWith(const string& prefix) {
        TrieNode* curr = root;

        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx]) return false;
            curr = curr->children[idx];
        }
        return true;  // all prefix characters found
    }
};

// ─────────────────────────────────────────────────────────────
// VARIANT 2: TRIE WITH WILDCARD SEARCH ('.' matches any char)
// ─────────────────────────────────────────────────────────────

class WildcardTrie {
    struct TrieNode {
        TrieNode* children[26];
        bool isEnd;
        TrieNode() : isEnd(false) { fill(children, children + 26, nullptr); }
    };

    TrieNode* root;

    bool searchHelper(const string& word, int pos, TrieNode* node) {
        if (pos == (int)word.size()) return node->isEnd;

        char c = word[pos];
        if (c == '.') {
            // try all 26 children
            for (int i = 0; i < 26; i++) {
                if (node->children[i] && searchHelper(word, pos + 1, node->children[i])) {
                    return true;
                }
            }
            return false;
        } else {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            return searchHelper(word, pos + 1, node->children[idx]);
        }
    }

public:
    WildcardTrie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx]) curr->children[idx] = new TrieNode();
            curr = curr->children[idx];
        }
        curr->isEnd = true;
    }

    bool search(const string& word) {
        return searchHelper(word, 0, root);
    }
};

// ─────────────────────────────────────────────────────────────
// VARIANT 3: TRIE WITH UNORDERED_MAP (variable alphabet)
// ─────────────────────────────────────────────────────────────

class FlexTrie {
    struct TrieNode {
        unordered_map<char, TrieNode*> children;
        bool isEnd = false;
    };

    TrieNode* root;

public:
    FlexTrie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c)) curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    bool search(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c)) return false;
            curr = curr->children[c];
        }
        return curr->isEnd;
    }
};

// ─────────────────────────────────────────────────────────────
// VARIANT 4: WORD SEARCH II (Trie + Backtracking DFS on grid)
// ─────────────────────────────────────────────────────────────

struct TrieNode {
    TrieNode* children[26];
    string word;  // store full word at end node (empty if not a word end)
    TrieNode() : word("") { fill(children, children + 26, nullptr); }
};

class TrieForWordSearch {
    TrieNode* root;

public:
    TrieForWordSearch() { root = new TrieNode(); }

    void insert(const string& w) {
        TrieNode* curr = root;
        for (char c : w) {
            int idx = c - 'a';
            if (!curr->children[idx]) curr->children[idx] = new TrieNode();
            curr = curr->children[idx];
        }
        curr->word = w;  // store the word at the terminal node
    }

    TrieNode* getRoot() { return root; }
};

void dfs(vector<vector<char>>& board, TrieNode* node, int r, int c,
         vector<string>& result) {
    int rows = board.size(), cols = board[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols) return;

    char ch = board[r][c];
    if (ch == '#' || !node->children[ch - 'a']) return;  // visited or no path

    node = node->children[ch - 'a'];

    if (!node->word.empty()) {
        result.push_back(node->word);
        node->word = "";  // avoid duplicates
    }

    board[r][c] = '#';  // mark visited
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) dfs(board, node, r + dr[d], c + dc[d], result);
    board[r][c] = ch;   // restore
}

/*
 * ─────────────────────────────────────────────────────────────
 * COMPLEXITY
 * ─────────────────────────────────────────────────────────────
 *  Insert/Search/Prefix: O(L) — L = word length
 *  Space: O(N × 26) with array, O(N) with map (but higher constant)
 *
 * ─────────────────────────────────────────────────────────────
 * WHEN TO USE TRIE vs HASHMAP
 * ─────────────────────────────────────────────────────────────
 *  Trie: prefix queries, autocomplete, word with wildcards
 *  HashMap: exact lookup only (faster constant factor)
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Confusing search() (exact word) with startsWith() (prefix)
 *  2. Not marking isEnd=true after insert → search always fails
 *  3. Memory leak: not deleting dynamically allocated TrieNodes
 *  4. Wildcard: must try ALL children for '.', not just one
 *  5. Word Search II: reset word="" after finding to avoid duplicates
 */
