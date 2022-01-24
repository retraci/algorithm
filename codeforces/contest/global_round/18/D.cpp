#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;

int n, m;
int vu[N], vv[N], vc[N];
int va[N], vb[N], vs[N];

int fa[2 * N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x != y) {
        fa[x] = y;
        return true;
    }
    return false;
}

void solve() {
    iota(fa + 1, fa + 2 * n + 1, 1);

    for (int i = 1; i <= n - 1; i++) {
        int u = vu[i], v = vv[i], c = vc[i];
        if (c == -1) continue;
        int cnt = __builtin_popcount(c);

        if (cnt & 1) {
            unite(u, v + n);
            unite(u + n, v);
        } else {
            unite(u, v);
            unite(u + n, v + n);
        }
    }

    for (int i = 1; i <= m; i++) {
        int a = va[i], b = vb[i], s = vs[i];

        if (s & 1) {
            unite(a, b + n);
            unite(a + n, b);
        } else {
            unite(a, b);
            unite(a + n, b + n);
        }
    }

    for (int i = 1; i <= n - 1; i++) {
        int u = vu[i], v = vv[i], c = vc[i];
        if (c != -1) continue;

        int tx1 = find(u), tx2 = find(u + n);
        int ty1 = find(v), ty2 = find(v + n);
        if (tx1 == ty2 || tx2 == ty1) {
            vc[i] = 1;
        } else if (tx1 == ty1 || tx2 == ty2) {
            vc[i] = 0;
        } else {
            vc[i] = 1;

            unite(u, v + n);
            unite(u + n, v);
        }
    }

    int valid = 1;
    for (int i = 1; i <= n; i++) {
        int tx1 = find(i), tx2 = find(i + n);
        if (tx1 == tx2) valid = 0;
    }
    if (!valid) {
        cout << "NO" << "\n";
    } else {
        cout << "YES" << "\n";
        for (int i = 1; i <= n - 1; i++) {
            int u = vu[i], v = vv[i], c = vc[i];
            cout << u << " " << v << " " << c << "\n";
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n - 1; i++) cin >> vu[i] >> vv[i] >> vc[i];
        for (int i = 1; i <= m; i++) cin >> va[i] >> vb[i] >> vs[i];
        solve();
    }

    return 0;
}