#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

ll n, m, K;

void solve() {
    K -= 2;

    // 不合理
    if (K < 0) {
        cout << "NO" << endl;
        return;
    }

    // 不需要连边
    if (n == 1) {
        if (m == 0 && K >= 0) cout << "YES" << endl;
        else cout << "NO" << endl;
        return;
    }

    // 无法连边
    if (K <= 0) {
        cout << "NO" << endl;
        return;
    }

    // 边太多
    if (m > n * (n - 1) / 2) {
        cout << "NO" << endl;
        return;
    }

    // K == 1 必须完全图
    if (K == 1) {
        if (n * (n - 1) / 2 == m) cout << "YES" << endl;
        else cout << "NO" << endl;
    } else {
        if (n - 1 <= m) cout << "YES" << endl;
        else cout << "NO" << endl;
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
        cin >> n >> m >> K;
        solve();
    }

    return 0;
}