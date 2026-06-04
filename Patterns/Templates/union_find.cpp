/*
 * ============================================================
 * TEMPLATE: Union-Find (Disjoint Set Union — DSU)
 * ============================================================
 * Use when: dynamically connect elements, count connected
 *           components, detect cycles in undirected graphs
 * Time: O(α(n)) per operation — effectively O(1) amortized
 *       α = inverse Ackermann function (grows incredibly slowly)
 * Space: O(n)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// CORE IMPLEMENTATION with Path Compression + Union by Rank
// ─────────────────────────────────────────────────────────────

class UnionFind {
    vector<int> parent;  // parent[i] = parent of node i
    vector<int> rank;    // rank[i] = approximate height of subtree at i
    int components;      // number of disjoint sets

public:
    UnionFind(int n) : parent(n), rank(n, 0), components(n) {
        iota(parent.begin(), parent.end(), 0);  // each node is its own parent
    }

    // FIND with path compression: make all nodes on path point to root
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // path compression: flatten tree
        }
        return parent[x];
    }

    // UNION by rank: attach smaller tree under larger tree
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;  // already in same component

        // attach tree with lower rank under tree with higher rank
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;                          // py's root becomes child of px
        if (rank[px] == rank[py]) rank[px]++;     // heights equal: increment rank
        components--;

        return true;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    int numComponents() { return components; }
};

// ─────────────────────────────────────────────────────────────
// VARIANT: WEIGHTED UNION-FIND (track size instead of rank)
// ─────────────────────────────────────────────────────────────

class WeightedUnionFind {
    vector<int> parent, size;

public:
    WeightedUnionFind(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;

        // attach smaller component under larger
        if (size[px] < size[py]) swap(px, py);
        parent[py] = px;
        size[px] += size[py];  // update size of merged component

        return true;
    }

    int componentSize(int x) { return size[find(x)]; }
};

// ─────────────────────────────────────────────────────────────
// EXAMPLE USAGE: Number of Islands using DSU
// ─────────────────────────────────────────────────────────────

int numIslandsDSU(vector<vector<char>>& grid) {
    int rows = grid.size(), cols = grid[0].size();

    // encode 2D position as 1D index
    auto idx = [&](int r, int c) { return r * cols + c; };

    UnionFind uf(rows * cols);
    int landCount = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1') {
                landCount++;
                // connect with right and down neighbors (avoid duplicates)
                if (r + 1 < rows && grid[r+1][c] == '1') uf.unite(idx(r,c), idx(r+1,c));
                if (c + 1 < cols && grid[r][c+1] == '1') uf.unite(idx(r,c), idx(r,c+1));
            }
        }
    }
    // islands = land cells - (unions performed) = landCount - (initial - final components)
    // Simpler: count components that correspond to land
    // (uf.numComponents counts ALL cells; subtract water cells)
    // Better: initialize only land cells, or count differently

    return uf.numComponents() - (rows * cols - landCount);
}

// ─────────────────────────────────────────────────────────────
// EXAMPLE USAGE: Redundant Connection (detect cycle)
// ─────────────────────────────────────────────────────────────

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    UnionFind uf(n + 1);  // nodes are 1-indexed

    for (auto& e : edges) {
        if (!uf.unite(e[0], e[1])) {
            // these two are already connected → this edge creates a cycle
            return e;
        }
    }
    return {};
}

// ─────────────────────────────────────────────────────────────
// EXAMPLE USAGE: Accounts Merge
// ─────────────────────────────────────────────────────────────

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, int> emailToId;  // email → unique id
    unordered_map<string, string> emailToName;  // email → account name
    int id = 0;

    UnionFind uf(accounts.size() * 10 + 10);  // generous size

    for (auto& account : accounts) {
        string name = account[0];
        int firstId = -1;

        for (int i = 1; i < (int)account.size(); i++) {
            if (!emailToId.count(account[i])) {
                emailToId[account[i]] = id++;
                emailToName[account[i]] = name;
            }
            if (firstId == -1) firstId = emailToId[account[i]];
            uf.unite(firstId, emailToId[account[i]]);
        }
    }

    unordered_map<int, vector<string>> components;
    for (auto& [email, eid] : emailToId) {
        components[uf.find(eid)].push_back(email);
    }

    vector<vector<string>> result;
    for (auto& [root, emails] : components) {
        sort(emails.begin(), emails.end());
        emails.insert(emails.begin(), emailToName[emails[0]]);
        result.push_back(emails);
    }
    return result;
}

/*
 * ─────────────────────────────────────────────────────────────
 * WHEN TO USE DSU vs BFS/DFS
 * ─────────────────────────────────────────────────────────────
 *  DSU when:
 *    - Edges are added dynamically (online processing)
 *    - Need to check if two nodes are in same component
 *    - Count/merge components efficiently
 *    - Detect cycle in undirected graph
 *
 *  BFS/DFS when:
 *    - Need actual path between nodes
 *    - Need to process nodes in order
 *    - Graph is given all at once (offline)
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Forgetting path compression → O(n) per operation instead of O(α)
 *  2. Cycle detection: if unite() returns false → already connected → cycle
 *  3. 1-indexed nodes: UnionFind(n+1), not UnionFind(n)
 *  4. Not using rank/size → union by rank keeps tree balanced
 */
