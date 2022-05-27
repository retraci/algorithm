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
const int N = 2e5 + 10;

int n;
pii a[N];
set<pii> st;
vector<pii> lsh;
int nl;

int get(pii x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

vector<int> bfs() {
    vector<int> ans(nl + 1), d(nl + 1, -1), vis(nl + 1);
    queue<pii> que;
    for (int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        int u = get(a[i]);
        vis[u] = 1;

        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            pii p = {nx, ny};
            int v = get(p);
            if (!st.count(p)) que.push({v, v});
        }
    }

    while (!que.empty()) {
        auto [u, from] = que.front(); que.pop();
        auto [x, y] = lsh[u];

        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            int v = get({nx, ny});

            if (d[v] == -1 && vis[v] == 1) {
                d[v] = d[u] + 1;
                ans[v] = from;
                que.push({v, from});
            }
        }
    }

    return ans;
}

void init() {
    for (int i = 1; i <= n; i++) {
        lsh.push_back(a[i]);
        st.insert(a[i]);
    }

    for (int i = 1; i <= n; i++) {
        auto [x, y] = a[i];
        for (int k = 0; k < 4; k++) {
            int nx = x + dir[k][0], ny = y + dir[k][1];
            pii u = {nx, ny};
            lsh.push_back(u);
        }
    }

    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

void solve() {
    init();

    auto ans = bfs();

    for (int i = 1; i <= n; i++) {
        int u = get(a[i]);
        auto [x, y] = lsh[ans[u]];
        cout << x << " " << y << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}