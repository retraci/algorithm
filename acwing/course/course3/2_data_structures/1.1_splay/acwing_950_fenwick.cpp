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
#include <random>

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
    int n, sz;
    ll tr[SZ + 10];

    Fenwick() {
        init(SZ);
    }

    void init(int _n, ll v = 0) {
        n = _n, sz = 0;
        fill(tr, tr + n + 1, v);
    }

    int size() {
        return sz;
    }

    void upd(int id, ll x) {
        sz += x;
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }

    int kth(int x) {
        if (x < 1 || x > sz) return 1e9;

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
const int N = 2e5 + 100;
const int BASE = 1e5 + 10;

int n, m;
Fenwick<3 * BASE> fw;

void solve() {
    int cur = 0, cnt = 0;
    while (n--) {
        string op;
        int x;
        cin >> op >> x;

        if (op == "I") {
            if (x >= m) fw.upd(x - cur + BASE, 1);
        }
        if (op == "A") cur += x;
        if (op == "S") {
            cur -= x;
            while (1) {
                int t = fw.kth(1);
                if (t + cur - BASE >= m) break;

                int c = fw.qr(t) - fw.qr(t - 1);
                fw.upd(t, -c);
                cnt += c;
            }
        }
        if (op == "F") {
            int t = fw.kth(fw.size() - x + 1);
            if (t == 1e9) cout << -1 << "\n";
            else  cout << t + cur - BASE << "\n";
        }
    }

    cout << cnt << "\n";
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