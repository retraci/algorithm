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

// region 普通平衡树(fenwick)
template<int SZ>
struct Fenwick {
    int n;
    ll tr[SZ + 10];

    Fenwick() {
        init(SZ);
    }

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

    int get_rk(int x) {
        return qr(x - 1) + 1;
    }

    int get_pre(int x) {
        return kth(qr(x - 1));
    }

    int get_nxt(int x) {
        return kth(qr(x) + 1);
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;

int n;
pii a[N];
int nl;
vector<int> lsh;
Fenwick<2 * N> fw;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) {
        auto [op, x] = a[i];
        if (op == 4) continue;
        lsh.push_back(x);
    }

    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) {
        auto &[op, x] = a[i];
        if (op == 4) continue;
        x = get(x) + 1;
    }
}

void solve() {
    init();

    fw.init(nl);
    for (int i = 1; i <= n; i++) {
        auto [op, x] = a[i];

        if (op == 1) fw.upd(x, 1);
        if (op == 2) fw.upd(x, -1);
        if (op == 3) cout << fw.get_rk(x) << "\n";
        if (op == 4) cout << lsh[fw.kth(x) - 1] << "\n";
        if (op == 5) cout << lsh[fw.get_pre(x) - 1] << "\n";
        if (op == 6) cout << lsh[fw.get_nxt(x) - 1] << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}