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
const int MOD = 1e9 + 7;

string s;

void solve() {
    int n = s.size() - 1;
    vector<int> f(n + 1);
    for (int i = 1; i <= n; i++) {
        int flag = 0;
        for (int j = i - 1; j >= 1; j--) {
            f[i] += f[j - 1];
            f[i] %= MOD;
            if (s[i] == s[j]) {
                flag = 1;
                break;
            }
        }
        f[i] = (f[i] + !flag) % MOD;
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += f[i];
        ans %= MOD;
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}