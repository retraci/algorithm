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
const int N = 2e5 + 10;

int n, m;
int a[N];

int work(const vector<int> &v) {
    int mi = 1e9, mx = 0;
    for (int i = 1; i < v.size(); i++) {
        int d = v[i] - v[i - 1] - 1;
        mi = min(mi, d), mx = max(mx, d);
    }

    return min(mi, max((mx - 1) / 2, m - v.back() - 1));
}

void solve() {
    a[0] = 0;
    int mi = 1e9, mip = 0;
    for (int i = 1; i <= n; i++) {
        int d = a[i] - a[i - 1] - 1;

        if (d < mi) {
            mi = d;
            mip = i;
        }
    }

    int ans = mi;
    vector<int> v;
    for (int i = 0; i <= n; i++) {
        if (i == mip) continue;
        v.push_back(a[i]);
    }

    ans = max(ans, work(v));
    v[mip - 1] = a[mip];
    ans = max(ans, work(v));

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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}