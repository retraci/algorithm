#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2010;

int n, m;
int va[N], cnt[N];
int ans[N][N];

void init() {
    for (int i = 1; i <= n; i++) ans[0][i] = va[i];
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) cnt[i] = 0;
        for (int i = 1; i <= n; i++) cnt[ans[k - 1][i]]++;
        for (int i = 1; i <= n; i++) ans[k][i] = cnt[ans[k - 1][i]];
    }

//    for (int k = 0; k <= 4; k++) {
//        for (int i = 1; i <= n; i++) {
//            cout << ans[k][i] << " ";
//        }
//        cout << endl;
//    }
}

void solve() {
    init();
    cin >> m;
    while (m--) {
        int x, k;
        cin >> x >> k;
        if (k >= n) k = n;
        cout << ans[k][x] << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}