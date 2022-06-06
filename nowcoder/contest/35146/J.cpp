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
const int N = 410;

int n;
int a[N];

void solve() {
    int mi = 1;
    for (int i = 1; i <= n; i++) {
        if (1LL * a[mi] * i > 1LL * mi * a[i]) mi = i;
    }

    vector<ll> f(n * n + 1, 1e18);
    f[0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n * n; j++) {
            f[j] = min(f[j], f[j - i] + a[i]);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        ll m;
        cin >> m;

        if (m <= n * n) {
            cout << f[m] << "\n";
        } else {
            ll cnt = (m - n * n + mi - 1) / mi;
            ll ans = cnt * a[mi];
            ll rem = m - cnt * mi;
            ans += f[rem];
            cout << ans << "\n";
        }
    }
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
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}