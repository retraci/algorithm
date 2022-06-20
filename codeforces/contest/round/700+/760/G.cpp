#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {0, 0, -1, 1, -1, -1, 1, 1, 0};
const int dy[9] = {-1, 1, 0, 0, -1, 1, -1, 1, 0};

struct Node {
    ll rb1, lb2, w;

    bool operator<(const Node &rhs) const {
        return w < rhs.w;
    }
};

const int N = 4e5 + 10;

int n, m, q;
ll va[N], vb[N], vk[N];
int idx[N];

pll vc[N];
ll vs[N];
int tt;

ll sum;
int fa[N];
ll lbs[N], rbs[N], sz[N], cost[N];

ll ans[N];
multiset<Node> st;

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void init() {
    sum = accumulate(va + 1, va + n + 1, 0LL);

    for (int i = 1; i <= n; i++) vc[++tt] = {va[i], 1};
    for (int i = 1; i <= m; i++) vc[++tt] = {vb[i], 0};
    vc[0] = {-1e18, 0}, vc[tt + 1] = {1e18, 0};
    sort(vc + 1, vc + tt + 1);

    for (int i = 1; i <= tt; i++) vs[i] = vs[i - 1] + vc[i].first;
    for (int i = 1; i <= tt; i++) {
        fa[i] = i;
        sz[i] = vc[i].second;
        cost[i] = sz[i] ? vc[i].first : 0;
        lbs[i] = rbs[i] = i;
    }

    for (int i = 1; i <= q; i++) idx[i] = i;
    sort(idx + 1, idx + q + 1, [&](auto &lhs, auto &rhs) {
        return vk[lhs] < vk[rhs];
    });

    for (int i = 1; i <= tt + 1; i++) {
        st.insert({i - 1, i, vc[i].first - vc[i - 1].first});
    }
}

void work(int id) {
    ll k = vk[id];

    while (st.begin()->w <= k) {
        auto [rb1, lb2, w] = *st.begin(); st.erase(st.begin());

        int tx = find(rb1), ty = find(lb2);
        int lb1 = lbs[tx], rb2 = rbs[ty];
        sum -= cost[tx] + cost[ty];

        fa[ty] = tx;
        sz[tx] += sz[ty];
        cost[tx] = vs[rb2] - vs[rb2 - sz[tx]];
        lbs[tx] = lb1, rbs[tx] = rb2;

        sum += cost[tx];
    }

    ans[id] = sum;
}

void solve() {
    init();

    for (int i = 1; i <= q; i++) {
        int id = idx[i];
        work(id);
    }

    for (int i = 1; i <= q; i++) cout << ans[i] << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) cin >> va[i];
    for (int i = 1; i <= m; i++) cin >> vb[i];
    for (int i = 1; i <= q; i++) cin >> vk[i];
    solve();

    return 0;
}