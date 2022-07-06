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
int a[N];

bool check(int x) {
    while (x) {
        if (2 * (x % 10) >= 10) return false;
        x /= 10;
    }
    return true;
}

void solve() {
    vector<int> f(1e6 + 1);
    for (int i = 1; i <= n; i++) f[a[i]]++;
    for (int i = 0; i <= 6; i++) {
        int x = pow(10, i);

        for (int j = 0; j <= 1e6; j++) {
            if (j / x % 10 < 9 && j + x <= 1e6) {
                f[j + x] += f[j];
            }
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += f[999999 - a[i]];
        if (check(a[i])) ans--;
    }
    ans /= 2;
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