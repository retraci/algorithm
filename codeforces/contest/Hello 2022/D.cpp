#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<ll, ll, ll> tl3;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 510;

int n;
ll g[N][N];
ll dist[N][N];
int vis[N][N];

void dij() {
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            vis[i][j] = 0;
            dist[i][j] = 1e18;
        }
    }

    priority_queue<tl3> que;
    dist[0][0] = 0;
    que.push({0, 0, 0});
    while (!que.empty()) {
        auto [d, x, y] = que.top(); que.pop(); d = -d;
        if (vis[x][y]) continue;
//        cout << "#" << x << " " << y << "\n";
        vis[x][y] = 1;

        for (int k = 0; k < 4; k++) {
            int nx = (x + dx[k] + 2 * n) % (2 * n);
            int ny = (y + dy[k] + 2 * n) % (2 * n);

//            cout << nx << " " << ny << "\n";

            if (dist[nx][ny] > dist[x][y] + g[nx][ny]) {
                dist[nx][ny] = dist[x][y] + g[nx][ny];
                que.push({-dist[nx][ny], nx, ny});
            }
        }
    }
}

void solve() {
    dij();
    cout << dist[2 * n - 1][2 * n - 1] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < 2 * n; i++) {
            for (int j = 0; j < 2 * n; j++) {
                cin >> g[i][j];
            }
        }
        solve();
    }

    return 0;
}