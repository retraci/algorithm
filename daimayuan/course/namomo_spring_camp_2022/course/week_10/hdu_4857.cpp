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

const int N = 30010;
const int M = 100010;

int n, m;
int h[N], ne[M], e[M], edm;
int deg[N];

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void solve() {
    priority_queue<int> que;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 0) que.push(i);
    }

    vector<int> ans;
    while (!que.empty()) {
        int u = que.top(); que.pop();
        ans.push_back(u);

        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];

            if (--deg[v] == 0) que.push(v);
        }
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size() - 1; i++) cout << ans[i] << " ";
    cout << ans.back() << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n >> m;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(v, u);
            deg[u]++;
        }
        solve();
    }

    return 0;
}