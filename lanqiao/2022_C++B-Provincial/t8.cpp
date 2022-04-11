#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

#define ll long long

const int N = 5e4 + 10;

int n, m;
int ax[N], ay[N], ar[N];
int bx[N], by[N], br[N];

int to[3 * N], h[2 * N], ne[3 * N], edm;

void add(int u, int v) {
    to[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

bool check(int i1, int i2) {
    ll dx = ax[i1] - ax[i2], dy = ay[i1] - ay[i2];
    ll d = dx * dx + dy * dy;
    return d <= 1LL * ar[i1] * ar[i1];
}

bool check2(int i, int j) {
    ll dx = bx[i] - ax[j], dy = by[i] - ay[j];
    ll d = dx * dx + dy * dy;
    return d <= 1LL * br[i] * br[i];
}

void init() {
    memset(h, -1, sizeof h);
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int b1 = check(i, j), b2 = check(j, i);
            if (b1) add(i, j);
            if (b2) add(j, i);
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (check2(i, j)) add(n + i, j);
        }
    }
}

void solve() {
    init();

    queue<int> que;
    vector<int> vis(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        que.push(n + i);
    }
    while (!que.empty()) {
        int u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = to[i];
            if (vis[v]) continue;
            que.push(v);
            vis[v] = 1;
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) ans += vis[i];
    cout << ans;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> ax[i] >> ay[i] >> ar[i];
    for (int i = 1; i <= m; i++) cin >> bx[i] >> by[i] >> br[i];
    solve();

    return 0;
}
