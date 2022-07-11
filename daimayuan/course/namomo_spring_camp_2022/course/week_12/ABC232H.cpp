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

int H, W, A, B;

vector<pii> work(int h, int w, int a, int b) {
    vector<pii> res;

    if (h == 2) {
        for (int j = 1; j <= b - 1; j++) {
            res.push_back({1, j});
            res.push_back({2, j});
        }
        res.push_back({3 - a, b});
        for (int j = b + 1; j <= w; j++) res.push_back({1, j});
        for (int j = w; j >= b + 1; j--) res.push_back({2, j});
        res.push_back({a, b});
    } else if (w == 2 || a == 1 || a == 2 && b == w) {
        res = work(w, h, b, a);
        for (auto &[x, y] : res) swap(x, y);
    } else {
        for (int j = 1; j <= w; j++) res.push_back({1, j});
        auto ret = work(h - 1, w, a - 1, w + 1 - b);
        for (auto &[x, y] : ret) x++, y = w + 1 - y;
        res.insert(res.end(), ret.begin(), ret.end());
    }

    return res;
}

void solve() {
    auto ans = work(H, W, A, B);

    for (auto [x, y] : ans) cout << x << " " << y << "\n";
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
        cin >> H >> W >> A >> B;
        solve();
    }

    return 0;
}