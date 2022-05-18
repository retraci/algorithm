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

int n, s, x;

pii ask(int p) {
    cout << "?" << " " << p << "\n";
    cout.flush();
    int ret, nxt;
    cin >> ret >> nxt;
    return {ret, nxt};
}

void solve() {
    vector<ai3> a(1e3);
    for (int i = 1; i <= 999; i++) {
        int p = rnd(n) + 1;
        if (i == 1) p = s;

        auto [v, nxt] = ask(p);
        a[i] = {v, nxt, p};
    }

    sort(a.begin() + 1, a.end(), [](auto &a, auto &b) {
        return a[0] < b[0];
    });

    int p = s;
    for (int i = 1; i <= 999; i++) {
        if (a[i][0] <= x) p = a[i][2];
    }

    for (int i = 1; i <= 999; i++) {
        if (p == -1) break;

        auto [v, nxt] = ask(p);
        if (v >= x) {
            cout << "!" << " " << v << "\n";
            cout.flush();
            return;
        }

        p = nxt;
    }

    cout << "!" << " " << -1 << "\n";
    cout.flush();
}

void prework() {
}

int main() {
#ifdef LOCAL
//    freopen("../in.txt", "r", stdin);
//    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> s >> x;
        solve();
    }

    return 0;
}