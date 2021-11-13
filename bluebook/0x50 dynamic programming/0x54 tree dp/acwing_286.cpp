#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 310;

int n, m;
int w[N];
vector<int> g[N];
int f[N][N];

void add(int a, int b) {
    g[a].push_back(b);
}

void dfs(int root) {

    for (auto to: g[root]) {
        dfs(to);
        for (int j = m - 1; j >= 0; j--) {
            for (int k = 0; k <= j; k++) {
                f[root][j] = max(f[root][j], f[root][j - k] + f[to][k]);
            }
        }
    }

    for (int j = m - 1; j >= 0; j--) f[root][j + 1] = f[root][j] + w[root];
}

void solve() {
    memset(f, 0, sizeof f);
    w[0] = 0;
    m++;
    dfs(0);

    cout << f[0][m] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d%d", &a, &w[i]);
        add(a, i);
    }
    solve();

    return 0;
}