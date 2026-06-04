/*
 * ============================================================
 * TEMPLATE: Graph DFS
 * ============================================================
 * Use when: count connected components, detect cycles,
 *           flood fill, path existence, topological order
 * Time: O(V + E) | Space: O(V) for visited + O(V) call stack
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: DFS ON ADJACENCY LIST (undirected/directed)
// ─────────────────────────────────────────────────────────────

int n;  // number of nodes
vector<vector<int>> adj;  // adjacency list
vector<bool> visited;

void dfs(int node) {
    visited[node] = true;  // mark before exploring to prevent revisits

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor);  // recurse into unvisited neighbors
        }
    }
    // postorder processing here if needed
}

// Count connected components
int countComponents(int numNodes, vector<vector<int>>& edges) {
    adj.assign(numNodes, {});
    visited.assign(numNodes, false);

    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);  // bidirectional for undirected
    }

    int components = 0;
    for (int i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            dfs(i);     // explores entire component
            components++;
        }
    }
    return components;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: DFS ON GRID (2D island problems)
// ─────────────────────────────────────────────────────────────

int rows, cols;
vector<vector<char>> grid;
// 4 directions: up, down, left, right
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void dfsGrid(int r, int c) {
    // boundary and validity check FIRST
    if (r < 0 || r >= rows || c < 0 || c >= cols) return;
    if (grid[r][c] != '1') return;  // not land (already visited or water)

    grid[r][c] = '0';  // mark visited by changing cell value (in-place)
                       // avoids separate visited array

    // explore all 4 directions
    for (int d = 0; d < 4; d++) {
        dfsGrid(r + dr[d], c + dc[d]);
    }
}

int numIslands(vector<vector<char>>& g) {
    rows = g.size();
    cols = g[0].size();
    grid = g;  // work on a copy if original must be preserved

    int islands = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1') {
                dfsGrid(r, c);  // sink entire island
                islands++;
            }
        }
    }
    return islands;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: CYCLE DETECTION IN DIRECTED GRAPH
// ─────────────────────────────────────────────────────────────
// Uses 3-color marking: WHITE(0)=unvisited, GRAY(1)=in-stack, BLACK(2)=done
// If we reach a GRAY node, we found a back edge = cycle

vector<int> color;  // 0=unvisited, 1=in stack, 2=done

bool dfsCycle(int node, vector<vector<int>>& graph) {
    color[node] = 1;  // mark as IN PROGRESS (on current path)

    for (int neighbor : graph[node]) {
        if (color[neighbor] == 1) return true;   // back edge → cycle!
        if (color[neighbor] == 0) {               // unvisited
            if (dfsCycle(neighbor, graph)) return true;
        }
        // color[neighbor] == 2: already fully explored, safe to skip
    }

    color[node] = 2;  // mark as FULLY DONE
    return false;
}

bool hasCycle(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    for (auto& p : prerequisites) {
        graph[p[1]].push_back(p[0]);  // p[1] is prerequisite of p[0]
    }

    color.assign(numCourses, 0);

    for (int i = 0; i < numCourses; i++) {
        if (color[i] == 0 && dfsCycle(i, graph)) {
            return true;
        }
    }
    return false;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: ITERATIVE DFS (avoid stack overflow on large graphs)
// ─────────────────────────────────────────────────────────────

void iterativeDFS(int start, vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> vis(n, false);
    stack<int> stk;

    stk.push(start);
    vis[start] = true;

    while (!stk.empty()) {
        int node = stk.top();
        stk.pop();

        // process node here
        for (int neighbor : graph[node]) {
            if (!vis[neighbor]) {
                vis[neighbor] = true;
                stk.push(neighbor);
            }
        }
    }
}

/*
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Grid DFS: boundary check must come BEFORE value check
 *  2. Cycle detection: must use 3 colors (not just visited bool)
 *     A visited bool can't distinguish "in stack" from "done"
 *  3. Forgetting to mark visited BEFORE pushing to stack (causes duplicates)
 *  4. For undirected graphs: don't visit parent again (pass parent param)
 *  5. Modifying grid in-place: OK if grid is a copy, destructive otherwise
 */
