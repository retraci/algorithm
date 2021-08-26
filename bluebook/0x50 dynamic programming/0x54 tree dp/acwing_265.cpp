#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 6010;

int n;
int w[N];
vector<int> g[N];
int st[N];
int f[N][2];

void add(int a, int b) {
    g[a].push_back(b);
}

void dfs(int root) {
    f[root][0] = 0;
    f[root][1] = w[root];

    for (int to: g[root]) {
        dfs(to);
        f[root][0] = max(f[root][0], f[root][0] + max(f[to][0], f[to][1]));
        f[root][1] = max(f[root][1], f[root][1] + f[to][0]);
    }
}

void solve() {
    int root = 1;
    while (st[root]) root++;
    dfs(root);

    cout << max(f[root][0], f[root][1]) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(b, a);
        st[a] = 1;
    }
    solve();

    return 0;
}