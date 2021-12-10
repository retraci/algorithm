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

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};
const int ix[4] = {-1, -1, 0, 0};
const int iy[4] = {-1, 0, -1, 0};
const string mp = "\\//\\";

const int N = 510;

int n, m;
string g[N];

int dist[N][N];
int vis[N][N];

void solve() {
    memset(dist, 0x3f, sizeof dist);
    memset(vis, 0, sizeof vis);

    deque<pii> que;
    dist[0][0] = 0;
    que.push_back({0, 0});
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop_front();
        if (vis[x][y]) continue;
        vis[x][y] = 1;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k + 4], ny = y + dy[k + 4];
            int a = x + ix[k], b = y + iy[k];

            if (nx >= 0 && nx <= n && ny >= 0 && ny <= m) {
                int w = g[a][b] == mp[k] ? 0 : 1;

                if (dist[nx][ny] > dist[x][y] + w) {
                    dist[nx][ny] = dist[x][y] + w;
                    if (w) que.push_back({nx, ny});
                    else que.push_front({nx, ny});
                }
            }
        }
    }

    if (dist[n][m] == 0x3f3f3f3f) cout << "NO SOLUTION" << "\n";
    else cout << dist[n][m] << "\n";
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
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> g[i];
        solve();
    }

    return 0;
}