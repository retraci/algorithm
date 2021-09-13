#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

const int N = 310;

int n, m;
int va[N * N];

void solve() {
    vector<PII> vb;
    for (int i = 0; i < n * m; i++) vb.push_back({va[i], i});
    sort(vb.begin(), vb.end());

    vector<PII> vc(n * m);
    for (int i = 0; i < vb.size(); i++) {
        vc[vb[i].second] = {vb[i].first, i};
    }

    int ans = 0;
    int g[n][m];
    memset(g, 0x3f, sizeof g);
    for (int i = 0; i < n * m; i++) {
        int peo = vc[i].first, seat = vc[i].second;
        int x = seat / m, y = seat % m;
        for (int j = 0; j < m; j++) {
            ans += g[x][j] < peo;
        }
        g[x][y] = peo;
    }

    cout << ans << endl;
}


int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n * m; i++) {
            cin >> va[i];
        }
        solve();
    }

    return 0;
}