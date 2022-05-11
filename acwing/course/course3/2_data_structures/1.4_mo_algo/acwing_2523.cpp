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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;

int n, m;
int a[N];
ai3 qs[N];
int bl;
ll cur;
int cnt[N];
vector<int> lsh;
int nl;

void add(int x) {
    cnt[x]++;
    cur = max(cur, 1LL * cnt[x] * lsh[x - 1]);
}

void del(int x) {
    cnt[x]--;
}

int get(int i) {
    return (i - 1) / bl + 1;
}

int get_lsh(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) a[i] = get_lsh(a[i]) + 1;
}

void solve() {
    init();

    bl = sqrt(n);
    sort(qs + 1, qs + m + 1, [](auto &a, auto &b) {
        int bid1 = get(a[1]), bid2 = get(b[1]);
        if (bid1 != bid2) return bid1 < bid2;
        return a[2] < b[2];
    });

    vector<int> lbs(n + 1), rbs(n + 1);
    for (int i = 1; i <= n / bl; i++) {
        lbs[i] = (i - 1) * bl + 1;
        rbs[i] = i * bl;
    }

    vector<int> tmp(n + 1, 0);
    fill(cnt, cnt + n + 1, 0), cur = 0;
    vector<ll> ans(m + 1);
    int cl = 1, cr = 0, lst = 0;
    for (int i = 1; i <= m; i++) {
        auto [qid, L, R] = qs[i];

        if (get(L) == get(R)) {
            ll mx = 0;
            for (int j = L; j <= R; j++) {
                tmp[a[j]]++;
                mx = max(mx, 1LL * tmp[a[j]] * lsh[a[j] - 1]);
            }
            for (int j = L; j <= R; j++) tmp[a[j]]--;
            ans[qid] = mx;
            continue;
        }

        if (get(L) != lst) {
            for (int j = cl; j <= cr; j++) cnt[a[j]] = 0;
            int rb = rbs[get(L)];
            cl = rb + 1, cr = rb;
            cur = 0;
            lst = get(L);
        }

        while (cr < R) add(a[++cr]);
        ll bak = cur;
        for (int j = cl - 1; j >= L; j--) add(a[j]);
        ans[qid] = cur;
        for (int j = cl - 1; j >= L; j--) del(a[j]);
        cur = bak;
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int L, R;
            cin >> L >> R;

            qs[i] = {i, L, R};
        }

        solve();
    }

    return 0;
}