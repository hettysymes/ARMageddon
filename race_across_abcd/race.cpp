#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <tuple>
#include <chrono>

using namespace std;

// Heuristic function: Manhattan distance
int heuristic(int r, int c, int goal_r, int goal_c) {
    return abs(r - goal_r) + abs(c - goal_c);
}

// A* algorithm to find the minimum path sum
int a_star_min_path_sum(const vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, numeric_limits<int>::max()));
    dist[0][0] = grid[0][0];

    // Min-heap priority queue: (f(n), g(n), row, col)
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<>> pq;
    pq.push(make_tuple(grid[0][0] + heuristic(0, 0, rows - 1, cols - 1), grid[0][0], 0, 0));

    // Possible directions of movement: Right, Down, Left, Up
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int goal_r = rows - 1;
    int goal_c = cols - 1;

    while (!pq.empty()) {
        auto [f_value, current_dist, r, c] = pq.top();
        pq.pop();

        // If we reached the goal
        if (r == goal_r && c == goal_c) {
            return current_dist;
        }

        // Explore neighbors
        for (const auto& [dr, dc] : directions) {
            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int new_dist = current_dist + grid[nr][nc];

                // If we found a shorter path
                if (new_dist < dist[nr][nc]) {
                    dist[nr][nc] = new_dist;
                    int new_f_value = new_dist + heuristic(nr, nc, goal_r, goal_c);
                    pq.push(make_tuple(new_f_value, new_dist, nr, nc));
                }
            }
        }
    }

    return dist[goal_r][goal_c];
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 6, 3, 7, 5, 1, 7, 4, 2},
        {1, 3, 8, 1, 3, 7, 3, 6, 7, 2},
        {2, 1, 3, 6, 5, 1, 1, 3, 2, 8},
        {3, 6, 9, 4, 9, 3, 1, 5, 6, 9},
        {7, 4, 6, 3, 4, 1, 7, 1, 1, 1},
        {1, 3, 1, 9, 1, 2, 8, 1, 3, 7},
        {1, 3, 5, 9, 9, 1, 2, 4, 2, 1},
        {3, 1, 2, 5, 4, 2, 1, 6, 3, 9},
        {1, 2, 9, 3, 1, 3, 8, 5, 2, 1},
        {2, 3, 1, 1, 9, 4, 4, 5, 8, 1}
    };

    auto start_time = chrono::high_resolution_clock::now();

    int result = a_star_min_path_sum(grid);

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;

    cout << "Minimum Path Sum using A*: " << result << endl;
    cout << "Time taken: " << elapsed_time.count() << " seconds" << endl;

    return 0;
}
