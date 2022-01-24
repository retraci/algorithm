#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;

int n, m;
int va[N], vb[N], vc[N];
int vis[N];

void solve() {
    for (int i = 1; i <= n; i++) vis[i] = 0;
    for (int i = 1; i <= m; i++) vis[vb[i]] = 1;

    int id = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            id = i;
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i == id) continue;
        cout << i << " " << id << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            cin >> va[i] >> vb[i] >> vc[i];
        }
        solve();
    }

    return 0;
}