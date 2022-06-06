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
#include <cassert>
#include <random>
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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int M = 1e5 + 10;

ll n;
ll f[M], s[M];

void solve() {
    ll x = sqrtl(n);

    ll ans = 0;
    for (ll i = 1; i * i <= x; i++) {
        ll L = i * i, R = (i + 1) * (i + 1) - 1;
        R = min(x, R);
        ans += (R - L + 1) * s[i];
    }

    cout << ans << "\n";
}

void prework() {
    f[1] = 1, s[1] = 1;
    for (int i = 1; i <= 1e5; i++) {
        ll t = sqrtl(i);
        f[i] = s[t];
        s[i] = s[i - 1] + f[i];
    }
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
        cin >> n;
        solve();
    }

    return 0;
}