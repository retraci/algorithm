// 迷宫
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

struct Status {
    int x, y;
    string path;
};

const int dx[4] = {1,0,0,-1};
const int dy[4] = {0,-1,1,0};
const char dir[4] = {'D', 'L', 'R', 'U'};

int n = 30, m = 50;
string g[35];
int vis[35][55];

bool vaild(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void solve() {
//    for (int i = 0; i < n; i++) cout << g[i] << endl;
    int step = 0x3f3f3f3f;
    string path;

    Status s;
    s.x = 0, s.y = 0; s.path = "";
    queue<Status> que;
    que.push(s);
    while (que.size()) {
        int sz = que.size();
        for (int i = 0; i < sz; i++) {
            Status cur = que.front(); que.pop();

            if (cur.x == n - 1 && cur.y == m - 1) {
//                cout << 1;
                if (step > cur.path.size()) {
                    step = cur.path.size();
                    path = cur.path;
                }
                if (step == cur.path.size()) {
                    path = min(path, cur.path);
                }
                continue;
            }

            if (vis[cur.x][cur.y]) continue;
            vis[cur.x][cur.y] = 1;

//            cout << cur.x << " " << cur.y << endl;

            for (int k = 0; k < 4; k++) {
                int nx = cur.x + dx[k], ny = cur.y + dy[k];

                if (vaild(nx, ny) && !vis[nx][ny] && g[nx][ny] == '0') {
                    Status ns;
                    ns.x = nx, ns.y = ny, ns.path = cur.path;
                    ns.path.push_back(dir[k]);
                    que.push(ns);
                }
            }
        }
    }

    cout << path << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    for (int i = 0; i < n; i++) getline(cin, g[i]);
    solve();

    return 0;
}