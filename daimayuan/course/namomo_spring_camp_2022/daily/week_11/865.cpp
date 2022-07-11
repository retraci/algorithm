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

// region fenwick
template<int SZ>
struct Fenwick {
    int n;
    ll tr[SZ + 10];

    Fenwick() {}

    void init(int _n, ll v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }

    int kth(int x) {
        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && tr[pos + (1 << i)] < x) {
                pos += 1 << i;
                x -= tr[pos];
            }
        }

        return pos + 1;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;

int n, m;
Fenwick<N> fw1, fw2;

void solve() {
    fw1.init(n), fw2.init(n);
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        int op, L, R;
        cin >> op >> L >> R;

        if (op == 1) {
            fw1.upd(L, 1), fw2.upd(R, 1);
            cnt++;
        }
        if (op == 2) {
            int c1 = fw1.qr(n) - fw1.qr(R);
            int c2 = fw2.qr(L - 1);
            cout << cnt - c1 - c2 << "\n";
        }
    }
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
        solve();
    }

    return 0;
}