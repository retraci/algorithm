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
const int M = 1e5 + 10;

int n;
int a[N];
int h[N], ne[M * 2], e[M * 2], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

double work() {
    vector<double> b;
    for (int u = 1; u <= n; u++) {
        vector<int> tmp;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            tmp.push_back(a[v]);
        }
        sort(tmp.rbegin(), tmp.rend());
        b.push_back((a[u] + tmp[0]) / 2.0);
        if (tmp.size() >= 2) b.push_back((a[u] + tmp[0] + tmp[1]) / 3.0);
    }

    return *max_element(b.begin(), b.end());
}

void solve() {
    double ans = work();
    for (int i = 1; i <= n; i++) a[i] = -a[i];
    ans = max(ans, work());

    ans = ans * ans / 4;
    cout << fixed << setprecision(6);
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
        cin >> n;
        fill(h, h + n + 1, -1), edm = 0;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int j = 1; j <= n - 1; j++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}