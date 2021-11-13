#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 500010;

int n, K, m;
vector<int> g[N];
vector<vector<int>> du;
int va[N];
int cnt[N];

void add(int u, int v) {
    g[u].push_back(v);
    for (int k = 1; k <= K; k++) du[k][v]++;
}

void solve() {
    vector<int> que[n + 1];
    for (int k = 1; k <= K; k++) {
        for (int i = 1; i <= n; i++) {
            if (du[k][i] == 0) que[i].push_back(k);
        }
    }

    for (int i = 1; i <= K * n; i++) {
        int a = va[i];
        int k = que[a][cnt[a]++];
        cout << k << " ";

        for (int v: g[a]) {
            if (--du[k][v] == 0) que[v].push_back(k);
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> K >> m;
    du = vector<vector<int>>(K + 1, vector<int>(n + 1, 0));
    while (m--) {
        int a, b;
        cin >> a >> b;
        add(a, b);
    }
    for (int i = 1; i <= n * K; i++) {
        int a;
        cin >> a;
        va[i] = a;
    }
    solve();

    return 0;
}