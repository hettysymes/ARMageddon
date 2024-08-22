import heapq
import time
 
def heuristic(r, c, goal_r, goal_c):
    return abs(r - goal_r) + abs(c - goal_c)
 
def a_star_min_path_sum(grid):
    rows, cols = len(grid), len(grid[0])
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # Right, Down, Left, Up
    goal_r, goal_c = rows - 1, cols - 1
    dist = [[float('inf')] * cols for _ in range(rows)]
    dist[0][0] = grid[0][0]
    pq = [(grid[0][0] + heuristic(0, 0, goal_r, goal_c), grid[0][0], 0, 0)]  # (f(n), g(n), row, col)
    
    while pq:
        _, current_dist, r, c = heapq.heappop(pq)
        
        if r == goal_r and c == goal_c:
            return current_dist
        
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < rows and 0 <= nc < cols:
                new_dist = current_dist + grid[nr][nc]
                
                if new_dist < dist[nr][nc]:
                    dist[nr][nc] = new_dist
                    f_value = new_dist + heuristic(nr, nc, goal_r, goal_c)
                    heapq.heappush(pq, (f_value, new_dist, nr, nc))
    
    return dist[goal_r][goal_c]
 
 
grid = [
    [1, 1, 6, 3, 7, 5, 1, 7, 4, 2],
    [1, 3, 8, 1, 3, 7, 3, 6, 7, 2],
    [2, 1, 3, 6, 5, 1, 1, 3, 2, 8],
    [3, 6, 9, 4, 9, 3, 1, 5, 6, 9],
    [7, 4, 6, 3, 4, 1, 7, 1, 1, 1],
    [1, 3, 1, 9, 1, 2, 8, 1, 3, 7],
    [1, 3, 5, 9, 9, 1, 2, 4, 2, 1],
    [3, 1, 2, 5, 4, 2, 1, 6, 3, 9],
    [1, 2, 9, 3, 1, 3, 8, 5, 2, 1],
    [2, 3, 1, 1, 9, 4, 4, 5, 8, 1]
]

start_time = time.time()

result = a_star_min_path_sum(grid)

end_time = time.time()

elapsed_time = end_time - start_time
print("Minimum Path Sum using A*:", result)
print(f"Time taken: {elapsed_time:.6f} seconds")