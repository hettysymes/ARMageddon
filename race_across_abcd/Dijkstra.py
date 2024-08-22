import heapq
import time

def read_data_grid(file_path):
    with open(file_path, 'r') as file:
        grid = []
        for line in file:
            # Convert each character to an integer
            grid.append([int(char) for char in line.strip()])
    return grid

def dijkstra_min_path_sum(grid):
    rows, cols = len(grid), len(grid[0])
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # Right, Down, Left, Up
    dist = [[float('inf')] * cols for _ in range(rows)]
    dist[0][0] = grid[0][0]
    pq = [(grid[0][0], 0, 0)]  # (cost, row, col)
    while pq:
        current_dist, r, c = heapq.heappop(pq)
        if r == rows - 1 and c == cols - 1:
            return current_dist
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            if 0 <= nr < rows and 0 <= nc < cols: 
                new_dist = current_dist + grid[nr][nc]
                if new_dist < dist[nr][nc]:
                    dist[nr][nc] = new_dist
                    heapq.heappush(pq, (new_dist, nr, nc))
    return dist[rows-1][cols-1]

# Read the grid from the file
# file_path = '/Users/jaecho01/ARMageddon/race_across_abcd/grid_data.txt'
file_path = '/Users/jaecho01/ARMageddon/race_across_abcd/data_grid.txt' # Change the file path
grid = read_data_grid(file_path)

start_time = time.time()
result = dijkstra_min_path_sum(grid)
end_time = time.time()

print("Minimum Path Sum using Dijkstra:", result)
print(f"Time taken: {end_time - start_time:.6f} seconds")