/*
 * ============================================================
 * TEMPLATE: Graph BFS (Shortest Path, Topological Sort)
 * ============================================================
 * Use when: unweighted shortest path, level-by-level exploration,
 *           topological ordering, multi-source BFS
 * Time: O(V + E) | Space: O(V)
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────
// VARIANT 1: CLASSIC BFS (unweighted shortest path)
// ─────────────────────────────────────────────────────────────

int bfsShortestPath(int start, int end, vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    q.push(start);
    visited[start] = true;
    int steps = 0;

    while (!q.empty()) {
        int levelSize = q.size();  // snapshot for step counting

        for (int i = 0; i < levelSize; i++) {
            int node = q.front();
            q.pop();

            if (node == end) return steps;  // found target

            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;  // mark BEFORE pushing to avoid duplicates
                    q.push(neighbor);
                }
            }
        }
        steps++;  // completed one level
    }
    return -1;  // unreachable
}

// ─────────────────────────────────────────────────────────────
// VARIANT 2: MULTI-SOURCE BFS (simultaneous expansion from multiple starts)
// ─────────────────────────────────────────────────────────────
// Use when: find distance from NEAREST source (e.g., Rotting Oranges, 01 Matrix)

vector<vector<int>> multiSourceBFS(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    queue<pair<int,int>> q;

    // enqueue ALL sources at time 0
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) {  // source cell (e.g., rotten orange)
                q.push({r, c});
                dist[r][c] = 0;
            }
        }
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                grid[nr][nc] == 1 && dist[nr][nc] == INT_MAX) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return dist;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 3: TOPOLOGICAL SORT (Kahn's Algorithm — BFS-based)
// ─────────────────────────────────────────────────────────────
// Use when: dependency ordering, course schedule, build order
// Key: process nodes with in-degree 0 first

vector<int> topologicalSort(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n);
    vector<int> inDegree(n, 0);

    // build graph and compute in-degrees
    for (auto& e : edges) {
        int from = e[0], to = e[1];
        adj[from].push_back(to);
        inDegree[to]++;  // to has one more prerequisite
    }

    queue<int> q;
    // start with all nodes that have no prerequisites
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) q.push(i);
    }

    vector<int> order;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        order.push_back(node);  // this node is now processed

        // "remove" this node: reduce in-degree of its neighbors
        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);  // neighbor's all prerequisites done
            }
        }
    }

    // if order doesn't contain all nodes → cycle exists → impossible
    if ((int)order.size() != n) return {};  // cycle detected
    return order;
}

// ─────────────────────────────────────────────────────────────
// VARIANT 4: BFS ON GRID (shortest path in grid)
// ─────────────────────────────────────────────────────────────

int shortestPathGrid(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    if (grid[0][0] == 1 || grid[rows-1][cols-1] == 1) return -1;

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<tuple<int,int,int>> q;  // {row, col, distance}

    q.push({0, 0, 1});
    visited[0][0] = true;

    int dr[] = {-1,-1,-1, 0, 0, 1, 1, 1};  // 8 directions for grid paths
    int dc[] = {-1, 0, 1,-1, 1,-1, 0, 1};

    while (!q.empty()) {
        auto [r, c, dist] = q.front();
        q.pop();

        if (r == rows - 1 && c == cols - 1) return dist;

        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                !visited[nr][nc] && grid[nr][nc] == 0) {
                visited[nr][nc] = true;
                q.push({nr, nc, dist + 1});
            }
        }
    }
    return -1;
}

/*
 * ─────────────────────────────────────────────────────────────
 * BFS vs DFS DECISION
 * ─────────────────────────────────────────────────────────────
 *  Use BFS when:
 *    - Need SHORTEST PATH (unweighted)
 *    - Need to process level-by-level
 *    - Multiple starting points (multi-source BFS)
 *    - Topological ordering (Kahn's)
 *
 *  Use DFS when:
 *    - Just need to explore (not shortest path)
 *    - Cycle detection in directed graph
 *    - Recursive tree-like problems
 *    - Backtracking
 *
 * ─────────────────────────────────────────────────────────────
 * COMMON MISTAKES
 * ─────────────────────────────────────────────────────────────
 *  1. Marking visited AFTER popping (should be BEFORE pushing)
 *     → causes same node to be enqueued multiple times
 *  2. Topological sort: forgetting cycle check (order.size() != n)
 *  3. Multi-source BFS: initialize ALL sources at step 0, not one-by-one
 *  4. Grid BFS: 4-directional vs 8-directional — read problem carefully
 */
