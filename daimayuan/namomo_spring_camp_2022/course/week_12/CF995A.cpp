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
using node = pair<int, pii>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 111;

int n, m;
int a[5][N];
pii b[N];
vector<node> ans;

pii get_nxt(pii u) {
    auto [x, y] = u;
    if (x == 2) {
        if (y == m) return {3, m};
        else return {2, y + 1};
    } else {
        if (y == 1) return {2, 1};
        else return {3, y - 1};
    }
}

bool check(int i, pii u) {
    auto [x, y] = u;
    auto [nx, ny] = b[i];
    if (ny == y && abs(x - nx) == 1) return true;
    return false;
}

bool work() {
    int flag = 0;
    for (int i = 2; i <= 3; i++) {
        for (int j = 1; j <= m; j++) {
            if (!a[i][j]) continue;

            if (check(a[i][j], {i, j})) {
                flag = 1;
                ans.push_back({a[i][j], b[a[i][j]]});

                a[i][j] = 0;
            } else {
                auto nxt = get_nxt({i, j});
                auto [nx, ny] = nxt;
                if (!a[nx][ny]) {
                    flag = 1;
                    ans.push_back({a[i][j], nxt});

                    a[nx][ny] = a[i][j];
                    a[i][j] = 0;
                }
            }
        }
    }

    return flag;
}

void solve() {
    for (int j = 1; j <= m; j++) {
        if (a[1][j]) b[a[1][j]] = {1, j};
        if (a[4][j]) b[a[4][j]] = {4, j};
    }

    while (work());

    for (int i = 2; i <= 3; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j]) {
                cout << -1 << "\n";
                return;
            }
        }
    }

    cout << ans.size() << "\n";
    for (auto [id, pos] : ans) {
        auto [x, y] = pos;

        cout << id << " " << x << " " << y << "\n";
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
        cin >> m >> n;
        for (int i = 1; i <= 4; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
        }
        solve();
    }

    return 0;
}