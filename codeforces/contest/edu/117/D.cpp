#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>

using namespace std;

#define ll long long

ll a, b, x;

void solve() {
    while (1) {
        // 判断
        if (a == x || b == x) {
            cout << "YES" << endl;
            return;
        }
        if (x > a && x > b) {
            cout << "NO" << endl;
            return;
        }

        // 缩小范围, (a, b)范围内做k次
        if (a > b) swap(a, b);
        if (a == 0) {
            if (b == x) cout << "YES" << endl;
            else cout << "NO" << endl;
            return;
        }
        if (a < x && x < b && (b - x) % a == 0) {
            cout << "YES" << endl;
            return;
        }
        ll k = floor(1.0 * (b - a) / a);
        b -= k * a;

        // 做一次
        ll d = b - a;
        if (b == d) {
            cout << "NO" << endl;
            return;
        } else {
            b = d;
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b >> x;
        solve();
    }

    return 0;
}