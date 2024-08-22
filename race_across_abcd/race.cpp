#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <fstream>
#include <string>
 
using namespace std;
using namespace std::chrono;
 
int dijkstra_min_path_sum(const vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    dist[0][0] = grid[0][0];
 
    // Priority queue to store (cost, row, col), with the smallest cost on top
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.emplace(grid[0][0], 0, 0);
 
    // Directions for moving right, down, left, up
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
 
    while (!pq.empty()) {
        auto [current_dist, r, c] = pq.top();
        pq.pop();
 
        if (r == rows - 1 && c == cols - 1) {
            return current_dist; // If we reached the bottom-right corner, return the cost
        }
 
        for (const auto& [dr, dc] : directions) {
            int nr = r + dr;
            int nc = c + dc;
 
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int new_dist = current_dist + grid[nr][nc];
 
                if (new_dist < dist[nr][nc]) {
                    dist[nr][nc] = new_dist;
                    pq.emplace(new_dist, nr, nc);
                }
            }
        }
    }
 
    return dist[rows-1][cols-1];
}
 
int main() {
    std::ifstream file("grid_data.txt");
    std::vector<std::vector<int>> grid;
    std::string line;
    // Check if the file is open
    if (file.is_open()) {
        // Read the file line by line
        while (std::getline(file, line)) {
            std::vector<int> row;
            for (char ch : line) {
                // Convert each character to an integer and add to the row
                row.push_back(ch - '0');
            }
            // Add the row to the matrix
            grid.push_back(row);
        }
        file.close(); // Close the file after reading
    } else {
        std::cerr << "Unable to open file";
        return 1;
    }
    // Example: Printing the matrix to verify the result
    for (const auto& row : grid) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
    auto start = high_resolution_clock::now();
    int result = dijkstra_min_path_sum(grid);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Minimum Path Sum using Dijkstra: " << result << endl;
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
 
    return 0;
}