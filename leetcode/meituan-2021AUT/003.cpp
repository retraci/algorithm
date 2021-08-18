#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int v[N], w[N];
int vv[N];

bool cmp(int a, int b) {
    if (v[a] + 2 * w[a] == v[b] + 2 * w[b]) return a < b;
    return v[a] + 2 * w[a] > v[b] + 2 * w[b];
}

void solve() {
    for (int i = 0; i < n; i++) vv[i] = i;
    sort(vv, vv + n, cmp);
    sort(vv, vv + m);

    for (int i = 0; i < m; i++) {
        printf("%d ", vv[i] + 1);
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &v[i], &w[i]);
    }
    solve();

    return 0;
}