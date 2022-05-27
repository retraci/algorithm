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
const int M = 1e6 + 10;

int n, m;
int a[N];
ai3 qs[M];
int cnt[N], bl, cur;

void add(int x) {
    cur -= cnt[x] / 2;
    cnt[x]++;
    cur += cnt[x] / 2;
}

void del(int x) {
    cur -= cnt[x] / 2;
    cnt[x]--;
    cur += cnt[x] / 2;
}

int get(int i) {
    return (i - 1) / bl + 1;
}

void solve() {
    bl = sqrt(n);
    sort(qs + 1, qs + m + 1, [](auto &a, auto &b) {
        int bid1 = get(a[0]), bid2 = get(b[0]);
        if (bid1 != bid2) return bid1 < bid2;
        return bid1 & 1 ? a[1] < b[1] : a[1] > b[1];
    });

    vector<int> ans(m + 1);
    int cl = 1, cr = 0;
    for (int i = 1; i <= m; i++) {
        auto [L, R, qid] = qs[i];

        while (cl < L) del(a[cl++]);
        while (cl > L) add(a[--cl]);
        while (cr > R) del(a[cr--]);
        while (cr < R) add(a[++cr]);

        ans[qid] = cur;
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
            qs[i] = {L, R, i};
        }
        solve();
    }

    return 0;
}