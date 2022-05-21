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
const int N = 1e5 + 10;

int h, w, n;
int sx, sy, tx, ty;
pii a[N];
map<int, vector<int>> rs, cs;

void solve() {
    for (int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        rs[x].push_back(y);
        cs[y].push_back(x);
    }

    for (auto &[r, vec] : rs) sort(vec.begin(), vec.end());
    for (auto &[c, vec] : cs) sort(vec.begin(), vec.end());

    set<pii> vis;
    queue<ai3> que;
    que.push({sx, sy, 0});
    vis.insert({sx, sy});
    while (!que.empty()) {
        auto [x, y, d] = que.front(); que.pop();
        if (x == tx && y == ty) {
            cout << d << "\n";
            return;
        }

        {
            auto it = lower_bound(rs[x].begin(), rs[x].end(), y);

            if (it != rs[x].end()) {
                int nx = x, ny = *it - 1;
                if (!vis.count({nx, ny})) {
                    vis.insert({nx, ny});
                    que.push({nx, ny, d + 1});
                }
            }
            if (it != rs[x].begin()) {
                it = prev(it);
                int nx = x, ny = *it + 1;
                if (!vis.count({nx, ny})) {
                    vis.insert({nx, ny});
                    que.push({nx, ny, d + 1});
                }
            }
        }

        {
            auto it = lower_bound(cs[y].begin(), cs[y].end(), x);

            if (it != cs[y].end()) {
                int nx = *it - 1, ny = y;
                if (!vis.count({nx, ny})) {
                    vis.insert({nx, ny});
                    que.push({nx, ny, d + 1});
                }
            }
            if (it != cs[y].begin()) {
                it = prev(it);
                int nx = *it + 1, ny = y;
                if (!vis.count({nx, ny})) {
                    vis.insert({nx, ny});
                    que.push({nx, ny, d + 1});
                }
            }
        }
    }

    cout << -1 << "\n";
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
        cin >> h >> w >> n;
        cin >> sx >> sy >> tx >> ty;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}