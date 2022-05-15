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
using ai4 = array<int, 4>;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;

int n, m, k;
int a[N];
ai3 qs[N];
vector<int> v;
int bl;
int f[N], g[N];

int get(int i) {
    return (i - 1) / bl + 1;
}

void solve() {
    for (int i = 0; i < (1 << 14); i++) {
        if (__builtin_popcount(i) == k) v.push_back(i);
    }

    memset(g, 0, sizeof g);
    for (int i = 1; i <= n; i++) {
        for (int x : v) g[x ^ a[i]]++;
        f[i] = g[a[i + 1]];
    }

    bl = sqrt(n);
    sort(qs + 1, qs + m + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[2] < b[2] : a[2] > b[2];
    });

    vector<ai4> qs2[n + 1];
    vector<ll> ans(m + 1);
    int cl = 1, cr = 0;
    for (int i = 1; i <= m; i++) {
        auto [qid, L, R] = qs[i];

        if (cl < L) qs2[cr].push_back({qid, cl, L - 1, -1});
        while (cl < L) ans[qid] += f[cl - 1] + !k, cl++;
        if (cl > L) qs2[cr].push_back({qid, L, cl - 1, 1});
        while (cl > L) ans[qid] -= f[cl - 2] + !k, cl--;
        if (cr > R) qs2[cl - 1].push_back({qid, R + 1, cr, 1});
        while (cr > R) ans[qid] -= f[cr - 1], cr--;
        if (cr < R) qs2[cl - 1].push_back({qid, cr + 1, R, -1});
        while (cr < R) ans[qid] += f[cr], cr++;
    }

    memset(g, 0, sizeof g);
    for (int i = 1; i <= n; i++) {
        for (int x : v) g[x ^ a[i]]++;
        for (auto [qid, L, R, sign] : qs2[i]) {
            for (int j = L; j <= R; j++) {
                ans[qid] += sign * g[a[j]];
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        auto [qid, L, R] = qs[i];
        int pqid = qs[i - 1][0];

        ans[qid] += ans[pqid];
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << "\n";
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
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {i, L, R};
        }
        solve();
    }

    return 0;
}