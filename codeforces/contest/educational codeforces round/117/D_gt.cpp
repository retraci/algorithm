#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

ll a, b, x;

bool gcd(ll c, ll d) {
    if (c == x || d == x) return 1;
    if (d == 0) return 0;
    if (c > d && c > x && (c - x) % d == 0) return 1;
    return gcd(d, c % d);
}

void solve() {
    if (gcd(a, b)) cout << "YES" << endl;
    else cout << "NO" << endl;
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