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
const int N = 3e5 + 10;
const int MOD = 998244353;

int n;
int a[N];

void solve() {
    vector<int> stk1, stk2;
    vector<int> f(n + 1, 0), fmx(n + 1), fmi(n + 1);
    f[0] = 1;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        fmx[i] = fmi[i] = f[i - 1];
        while (!stk1.empty() && a[stk1.back()] <= a[i]) {
            int id = stk1.back(); stk1.pop_back();
            fmx[i] += fmx[id];
            fmx[i] %= MOD;
            cur -= 1LL * fmx[id] * a[id] % MOD;
            cur %= MOD;
        }
        while (!stk2.empty() && a[stk2.back()] >= a[i]) {
            int id = stk2.back(); stk2.pop_back();
            fmi[i] += fmi[id];
            fmi[i] %= MOD;
            cur += 1LL * fmi[id] * a[id] % MOD;
            cur %= MOD;
        }

        cur += 1LL * fmx[i] * a[i] % MOD;
        cur %= MOD;
        cur -= 1LL * fmi[i] * a[i] % MOD;
        cur %= MOD;
        f[i] = cur;

        stk1.push_back(i), stk2.push_back(i);
    }

    int ans = (f[n] + MOD) % MOD;
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