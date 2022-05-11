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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;
const int MOD = 998244353;

int n, k;
int a[N];

void solve() {
    vector<int> f(n + 1, 0);
    iota(f.begin(), f.end(), 0);
    for (int i = 1; i <= n; i++) {
        if (a[i] == -1) continue;

        if (a[i] > 0) {
            if (i + k > n) {
                cout << 0 << "\n";
                return;
            }
            f[i + k] = 1;
        } else {
            if (i + k <= n) f[i + k] = k + 1;
        }
    }

    ll ans = 1;
    for (int i = 1; i <= n; i++) {
        ans = 1LL * ans * f[i] % MOD;
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
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}