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
using ull = unsigned long long;
using pii = pair<int, int>;
using ai3 = array<int, 3>;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n;
ll a[N];
ll ans;

ll work(ll p) {
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        ll r = a[i] % p;
        res += min(r, p - r);
    }
    return res;
}

void solve() {
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];

    ans = 1e18;
    ll s = a[n];
    for (int i = 2; i <= s / i; i++) {
        if (s % i == 0) {
            while (s % i == 0) s /= i;
            ans = min(ans, work(i));
        }
    }
    if (s > 1) ans = min(ans, work(s));

    cout << (ans == 1e18 ? -1 : ans) << "\n";
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