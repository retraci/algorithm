#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct Node {
    int to, cost;
};

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n;
vector<Node> g[N];
int du[N];
int d[N], f[N];

void add(int a, int b, int c) {
    g[a].push_back({b, c});
    du[b]++;
}

void dfs_d(int x, int fa) {
    if (du[x] == 1) {
        d[x] = INF;
        return;
    }

    for (auto &[to, cost]: g[x]) {
        if (to == fa) continue;
        dfs_d(to, x);
        d[x] += min(d[to], cost);
    }
}

void dfs_f(int x, int fa) {
    for (auto &[to, cost]: g[x]) {
        if (to == fa) continue;
        if (du[to] == 1) {
            int left = 0, right = min(cost, f[x] - min(cost, d[to]));
            f[to] = left + right;
        } else {
            int left = d[to], right = min(cost, f[x] - min(cost, d[to]));
            f[to] = left + right;
            dfs_f(to, x);
        }
    }
}

void solve() {
    memset(d, 0, sizeof d);
    int root = 1;
    while (root <= n && du[root] == 1) root++;
    if (root > n) {
        cout << g[1][0].cost << endl;
        return;
    }
    dfs_d(root, -1);

    f[root] = d[root];
    dfs_f(root, -1);

    cout << *max_element(f + 1, f + 1 + n) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        for (int i = 0; i < N; i++) g[i].clear();
        memset(du, 0, sizeof du);

        scanf("%d", &n);
        for (int i = 0; i < n - 1; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c), add(b, a, c);
        }
        solve();
    }

    return 0;
}