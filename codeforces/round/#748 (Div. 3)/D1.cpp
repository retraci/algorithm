#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 44;

int n;
int va[N], vb[N];

void solve() {
    sort(va, va + n);
    for (int i = 1; i < n; i++) vb[i] = va[i] - va[0];

//    for (int i = 1; i < n; i++) cout << vb[i] << " ";
//    cout << endl;

    int p = 1;
    while (p < n && vb[p] == 0) p++;
    if (p >= n) {
        cout << -1 << endl;
        return;
    }
    int ans = vb[p];
    for (int i = p + 1; i < n; i++) {
        if (vb[i] != 0) ans = __gcd(ans, vb[i]);
    }

    cout << ans << endl;
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
        for (int i = 0; i < n; i++) cin >> va[i];
        solve();
    }

    return 0;
}