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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n, m;
int a[N];
vector<int> b[M];
int g[M], ans;

void merge(int x, int y) {
    for (int id : b[x]) {
        if (a[id - 1] == y) ans--;
        if (a[id + 1] == y) ans--;
    }

    for (int id : b[x]) {
        a[id] = y;
        b[y].push_back(id);
    }
    b[x] = {};
}

void solve() {
    iota(g, g + (int) 1e6 + 1, 0);
    for (int i = 1; i <= n; i++) {
        b[a[i]].push_back(i);
    }

    ans = 1;
    for (int i = 2; i <= n; i++) {
        if (a[i] != a[i - 1]) ans++;
    }
    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int x, y;
            cin >> x >> y;
            if (g[x] == g[y]) continue;

            if (b[g[x]].size() > b[g[y]].size()) swap(g[x], g[y]);
            merge(g[x], g[y]);
        }
        if (op == 2) cout << ans << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}