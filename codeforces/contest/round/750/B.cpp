#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

#define ll long long

int n;
int c1, c0;

void solve() {
    ll ans = c1;
    while (c0--) ans <<= 1;

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
        c1 = 0, c0 = 0;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            c1 += a == 1;
            c0 += a == 0;
        }
        solve();
    }

    return 0;
}