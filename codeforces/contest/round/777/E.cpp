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

int n;
int p[N], a[N];
int nxt[32][N];

void solve() {
    int mx = *max_element(a + 1, a + n + 1);
    int sz = unordered_set<int>(p + 1, p + n + 1).size();
    int r = sz == n ? 0 : (mx - n) / (n - sz);

    int mxb = __lg(r);
    for (int i = 1; i <= n; i++) nxt[0][i] = p[i];
    for (int k = 1; k <= mxb; k++) {
        for (int u = 1; u <= n; u++) {
            nxt[k][u] = nxt[k - 1][nxt[k - 1][u]];
        }
    }

    vector<int> dist(n + 1);
    for (int u = 1; u <= n; u++) {
        int i = u;
        for (int k = mxb; k >= 0; k--) {
            if (r >> k & 1) i = nxt[k][i];
        }
        dist[u] = i;
    }

    set<int> st;
    for (int i = 1; i <= n; i++) st.insert(i);

    vector<int> ans(n + 1), vis(n + 1);
    for (int i = 1; i <= n; i++) {
        if (vis[dist[i]]) continue;
        vis[dist[i]] = 1;

        ans[i] = a[dist[i]];
        st.erase(ans[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (ans[i]) continue;

        ans[i] = *st.lower_bound(a[dist[i]]);
        st.erase(ans[i]);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << " ";
    cout << "\n";
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
        for (int i = 1; i <= n; i++) cin >> p[i];
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}