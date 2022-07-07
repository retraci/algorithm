#include <bits/stdc++.h>

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
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;

int n;
ai3 a[N];
Dsu<N> dsu;

void solve() {
    vector<ai3> b, c;
    for (int i = 1; i <= n; i++) {
        auto [col, L, R] = a[i];

        if (col) b.push_back({i, L, R});
        else c.push_back({i, L, R});
    }

    sort(b.begin(), b.end(), [](auto &a, auto &b) {
        return a[2] < b[2];
    });
    sort(c.begin(), c.end(), [](auto &a, auto &b) {
        return a[1] < b[1];
    });

    dsu.init(n);
    priority_queue<pii> pq;
    for (int i = 0, j = 0; i < b.size(); i++) {
        while (j < c.size() && b[i][2] >= c[j][1]) {
            pq.push({c[j][2], c[j][0]});
            j++;
        }

        int flag = 0;
        pii tmp;
        while (!pq.empty() && pq.top().fi >= b[i][1]) {
            if (!flag) {
                flag = 1;
                tmp = pq.top();
            }

            dsu.unite(pq.top().se, b[i][0]);
            pq.pop();
        }
        if (flag) pq.push(tmp);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) ans += i == dsu.find(i);
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
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int c, L, R;
            cin >> c >> L >> R;
            a[i] = {c, L, R};
        }
        solve();
    }

    return 0;
}