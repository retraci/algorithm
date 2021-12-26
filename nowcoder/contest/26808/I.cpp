#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

struct Node {
    int x, y, c;
    bool operator<(const Node &rhs) const {
        return c > rhs.c;
    };
};

const int N = 1010;

int n, m;
string g[N];
int vis[N][N];

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> g[i];
        g[i] = ' ' + g[i];
    }

    priority_queue<Node> que;
    for (int j = 1; j <= m; j++) {
        int c = g[1][j] == '0';
        que.push({1, j, c});
    }
    while (!que.empty()) {
        auto [x, y, c] = que.top(); que.pop();
        if (vis[x][y]) continue;
        vis[x][y] = 1;
//        cout << x << " " << y << " " << c << "\n";
        if (x == n) {
            cout << c << "\n";
            return 0;
        }

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                int nc = c + (g[nx][ny] == '0');
                que.push({nx, ny, nc});
            }
        }
    }

    return 0;
}