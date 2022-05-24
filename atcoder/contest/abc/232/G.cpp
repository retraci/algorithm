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

int n, m;
int a[N], b[N];
pll e[N * 4];
int ne[N * 4], h[3 * N], edm;
vector<int> lsh;
int nl;

void add(int u, int v, ll cost) {
    e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
}

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh = {};
    for (int i = 1; i <= n; i++) lsh.push_back(m - a[i]), lsh.push_back(b[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

ll dij() {
    vector<ll> d(n + nl + 1, 1e18);
    vector<int> vis(n + nl + 1);

    priority_queue<pll> que;
    d[1] = 0;
    que.push({0, 1});
    while (!que.empty()) {
        auto [_, u] = que.top(); que.pop();
        if (vis[u]) continue;
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cost] = e[i];

            if (d[v] > d[u] + cost) {
                d[v] = d[u] + cost;
                que.push({-d[v], v});
            }
        }
    }

    return d[n];
}

void solve() {
    init();

    fill(h, h + n + nl + 1, -1), edm = 0;
    for (int u = 1; u <= nl; u++) {
        int v = (u - 1 + 1) % nl + 1;

        int cost = ((lsh[v - 1] - lsh[u - 1]) % m + m) % m;
        add(n + u, n + v, cost);
    }
    for (int i = 1; i <= n; i++) {
        int ta = get(m - a[i]) + 1, tb = get(b[i]) + 1;
        add(i, n + ta, 0), add(n + tb, i, 0);
    }

    cout << dij() << "\n";
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
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}