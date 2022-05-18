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
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

ll n, k;

int ask(ll L, ll R) {
    cout << L << " " << R << "\n";
    cout.flush();
    string ret;
    cin >> ret;
    return ret[0] == 'Y';
}

void solve() {
    ll L = 1, R = n;
    while (1) {
        while (R - L + 1 > 50) {
            ll md = L + R >> 1;
            if (ask(L, md)) R = md;
            else L = md + 1;
            L = max(1LL, L - k), R = min(n, R + k);
        }

        ll p = rnd(R - L + 1) + L;
        if (ask(p, p)) return;

        L = max(1LL, L - k), R = min(n, R + k);
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
        cin >> n >> k;
        solve();
    }

    return 0;
}