#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

// vecto di chuyen
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

// Ham kiem tra valid de di chuyen
bool isValid(int x, int y, int n, int m, const vector<vector<int>>& maze, const vector<vector<bool>>& visited) {
    return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y];
}

// BFS 
vector<pair<int, int>> solveMazeBFS(const vector<vector<int>>& maze, int n, int m, int startX, int startY, int endX, int endY) {
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = true;
    
    while (!q.empty()) {
        pair<int, int> current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;
        
        // Neu den duoc diem dich
        if (x == endX && y == endY) {
            // Tai thiet lap duong
            vector<pair<int, int>> path;
            int currX = endX;
            int currY = endY;
            
            while (currX != startX || currY != startY) {
                path.push_back({currX, currY});
                pair<int, int> prev = parent[currX][currY];
                currX = prev.first;
                currY = prev.second;
            }
            
            path.push_back({startX, startY});
            reverse(path.begin(), path.end());
            
            return path;
        }
        
        // Thu cac duong
        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            
            if (isValid(newX, newY, n, m, maze, visited)) {
                visited[newX][newY] = true;
                parent[newX][newY] = {x, y};
                q.push({newX, newY});
            }
        }
    }
    
    // Khong tim thay duong
    return {};
}

// DFS
// vector<pair<int, int>> solveMazeDFS(const vector<vector<int>>& maze, int n, int m, int startX, int startY, int endX, int endY) {
//     vector<vector<bool>> visited(n, vector<bool>(m, false));
//     vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, {-1, -1}));
    
//     stack<pair<int, int>> s;
//     s.push({startX, startY});
//     visited[startX][startY] = true;
    
//     while (!s.empty()) {
//         pair<int, int> current = s.top();
//         s.pop();
//         int x = current.first;
//         int y = current.second;
        
//         // Neu cham duoc diem dich
//         if (x == endX && y == endY) {
//             // Tai thiet lap duong
//             vector<pair<int, int>> path;
//             int currX = endX;
//             int currY = endY;
            
//             while (currX != startX || currY != startY) {
//                 path.push_back({currX, currY});
//                 pair<int, int> prev = parent[currX][currY];
//                 currX = prev.first;
//                 currY = prev.second;
//             }
            
//             path.push_back({startX, startY});
//             reverse(path.begin(), path.end());
            
//             return path;
//         }
        
//         // Thu cac huong
//         for (int i = 0; i < 4; i++) {
//             int newX = x + dx[i];
//             int newY = y + dy[i];
            
//             if (isValid(newX, newY, n, m, maze, visited)) {
//                 visited[newX][newY] = true;
//                 parent[newX][newY] = {x, y};
//                 s.push({newX, newY});
//             }
//         }
//     }
    
//     // Khong ton tai duong
//     return {};
// }

int main() {
    int n, m, startX, startY, endX, endY;
    cin >> n >> m >> startX >> startY >> endX >> endY;
    
    vector<vector<int>> maze(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maze[i][j];
        }
    }
    
    // BFS
    vector<pair<int, int>> path = solveMazeBFS(maze, n, m, startX, startY, endX, endY);
    
    if (!path.empty()) {
        cout << path.size() << endl; // So luong buoc
        for (const auto& cell : path) {
            cout << cell.first << " " << cell.second << endl;
        }
    } else {
        cout << 0 << endl; // Khong co duong ton tai
    }
    
    
    return 0;
}