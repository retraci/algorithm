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
#define fi first
#define se second

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> ti3;
typedef tuple<ll, ll, ll> tl3;

// 上, 右, 下, 左 | 左上, 右上, 左下, 右下
const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 110;

int n, m;
pii s;
string g[N];

int dist[N][N];

void solve() {
    memset(dist, -1, sizeof dist);
    queue<pii> que;
    dist[s.fi][s.se] = 0;
    que.push(s);
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] == '.') {
                if (dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    que.push({nx, ny});
                }
            }
        }
    }

    cout << *max_element(&dist[1][1], &dist[n][m] + 1) << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> m >> n >> s.se >> s.fi;
        s.fi = n - s.fi + 1;
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}