#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void solve() {
    int N, M, x0, y0, x1, y1;
    cin >> N >> M >> x0 >> y0 >> x1 >> y1;
    
    // Điều chỉnh tọa độ về 0-based
    x0--; y0--; x1--; y1--;
    
    vector<vector<int>> maze(N, vector<int>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> maze[i][j];
        }
    }
    
    // Kiểm tra điểm bắt đầu và kết thúc
    if (maze[x0][y0] == 1 || maze[x1][y1] == 1) {
        cout << 0 << endl;
        return;
    }
    
    // Ma trận lưu cha của mỗi ô để truy vết
    vector<vector<pair<int, int>>> parent(N, vector<pair<int, int>>(M, {-1, -1}));
    queue<pair<int, int>> q;
    q.push({x0, y0});
    parent[x0][y0] = {x0, y0}; // Đánh dấu điểm bắt đầu
    
    bool found = false;
    
    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;
        
        // Nếu đến đích
        if (x == x1 && y == y1) {
            found = true;
            break;
        }
        
        // Duyệt 4 hướng
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // Kiểm tra ô hợp lệ và chưa thăm
            if (nx >= 0 && nx < N && ny >= 0 && ny < M && 
                maze[nx][ny] == 0 && parent[nx][ny].first == -1) {
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }
    
    if (!found) {
        cout << 0 << endl;
        return;
    }
    
    // Truy vết đường đi từ đích về đầu
    stack<pair<int, int>> path;
    int x = x1, y = y1;
    while (x != x0 || y != y0) {
        path.push({x, y});
        auto p = parent[x][y];
        x = p.first;
        y = p.second;
    }
    path.push({x0, y0});
    
    // In kết quả
    cout << path.size() << endl;
    while (!path.empty()) {
        auto p = path.top();
        path.pop();
        cout << p.first + 1 << " " << p.second + 1 << endl;
    }
}

int main() {
    solve();
    return 0;
}