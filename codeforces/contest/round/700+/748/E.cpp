#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int N = 4e5 + 10;

int n, K;
vector<int> g[N];
int du[N];
int vis[N];

void init() {
    for (int i = 1; i <= n; i++) g[i].clear();
    for (int i = 1; i <= n; i++) du[i] = 0, vis[i] = 0;
}

void add(int u, int v) {
    g[u].push_back(v);
    du[v]++;
}

void solve() {
    queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (du[i] <= 1) que.push(i);
    }

    int round = 0;
    while (!que.empty()) {
        if (++round > K) break;
        int sz = que.size();
        while (sz--) {
            int cur = que.front(); que.pop();
            if (vis[cur]) continue;
            vis[cur] = 1;

            for (int v : g[cur]) {
                if (--du[v] <= 1) que.push(v);
            }
        }
    }

    int ans = n;
    for (int i = 1; i <= n; i++) ans -= vis[i];
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> K;
        init();

        for (int i = 1; i <= n - 1; i++) {
            int a, b;
            cin >> a >> b;
            add(a, b), add(b, a);
        }
        solve();
    }

    return 0;
}