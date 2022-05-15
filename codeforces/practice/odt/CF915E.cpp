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

// region odt
struct Odt {
    using odtt = int;

    int n;
    map<int, odtt> odt;

    Odt() {}

    void init(int _n) {
        n = _n;
        odt[0] = 0, odt[n + 1] = 0;
    }

    void split(int pos) {
        auto [L, v] = *prev(odt.upper_bound(pos));
        odt[pos] = v;
    }

    odtt assign(int L, int R, odtt v) {
        split(L), split(R + 1);

        odtt res = (R - L + 1) * (v == 0);
        auto it = odt.find(L);
        while (it->fi != R + 1) {
            auto [tl, tv] = *it;
            odtt t = (next(it)->fi - tl) * (tv == 0);
            res -= t;
            it = odt.erase(it);
        }
        odt[L] = v;

        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int n, m;
Odt odt;

void solve() {
    odt.init(n);
    while (m--) {
        int L, R, k;
        cin >> L >> R >> k;

        if (k == 2) k = 0;
        n += odt.assign(L, R, k);

        cout << n << "\n";
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
        cin >> n >> m;
        solve();
    }

    return 0;
}