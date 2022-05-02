#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;

const int MOD = 1e9 + 7;

ll a1, d1, c1, a2, d2, c2, r1, r2;

ll lcm(ll x, ll y) {
    return x * y / __gcd(x, y);
}

ll work(ll x) {
    if (lcm(x, d1) != d2) return 0;

    return d2 / x * d2 / x % MOD;
}

void solve() {
    r1 = a1 + (c1 - 1) * d1, r2 = a2 + (c2 - 1) * d2;
    if (d1 > d2 || d2 % d1 != 0 || (a2 - a1) % d1 != 0 || a1 > a2 || r1 < r2) {
        cout << 0 << "\n";
        return;
    }
    if (r1 < r2 + d2 || a1 > a2 - d2) {
        cout << -1 << "\n";
        return;
    }

    int ans = 0;
    for (int i = 1; i <= d2 / i; i++) {
        if (d2 % i != 0) continue;

        ans += work(i);
        ans %= MOD;
        if (d2 / i != i) {
            ans += work(d2 / i);
            ans %= MOD;
        }
    }

    cout << ans << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        cin >> a1 >> d1 >> c1;
        cin >> a2 >> d2 >> c2;
        solve();
    }

    return 0;
}