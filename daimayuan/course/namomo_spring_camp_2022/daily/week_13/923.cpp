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
const int N = 1e6 + 10;

int n;
int a[2 * N];
int st[23][2 * N];

int get(int L, int R) {
    int k = __lg(R - L + 1);

    return __gcd(st[k][L], st[k][R - (1 << k) + 1]);
}

void solve() {
    for (int i = 1; i <= n; i++) a[i + n] = a[i];

    for (int i = 1; i <= 2 * n; i++) st[0][i] = a[i];
    for (int k = 1; k <= 22; k++) {
        for (int i = 1; i + (1 << k) - 1 <= 2 * n; i++) {
            st[k][i] = __gcd(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
        }
    }

    int tar = 0;
    for (int i = 1; i <= n; i++) tar = __gcd(tar, a[i]);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int left = i, right = n + i - 1;
        while (left < right) {
            int md = left + right >> 1;
            if (get(i, md) == tar) right = md;
            else left = md + 1;
        }

        ans = max(ans, left - i);
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
//    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}