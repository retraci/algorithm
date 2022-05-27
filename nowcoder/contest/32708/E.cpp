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

int n, m;
int a[N];
ai3 qs[N];
int cnt[2][N], bl;
ll cur;

void add(int x, int ty) {
    cnt[ty][x]--;
    cur -= cnt[!ty][x];
}

void del(int x, int ty) {
    cnt[ty][x]++;
    cur += cnt[!ty][x];
}

void solve() {
    bl = sqrt(n);

    sort(qs + 1, qs + m + 1, [&](auto &a, auto &b) {
        int bid1 = a[1] / bl, bid2 = b[1] / bl;
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[2] > b[2] : a[2] < b[2];
    });

    vector<ll> ans(m + 1);
    for (int i = 1; i <= n; i++) cnt[1][a[i]]++;
    int cl = 1, cr = 0;
    for (int i = 1; i <= m; i++) {
        auto [qid, L, R] = qs[i];

        while (cl < L) del(a[cl++], 0);
        while (cl > L) add(a[--cl], 0);
        while (cr > R) del(a[cr--], 1);
        while (cr < R) add(a[++cr], 1);

        ans[qid] = 1LL * L * (n - R + 1) - cur;
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        cin >> m;
        for (int i = 1; i <= m; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {i, L, R};
        }
        solve();
    }

    return 0;
}