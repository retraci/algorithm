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
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = int;

    int n;
    fwt tr[SZ + 10];

    Fenwick() {}

    void init(int _n, fwt v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = max(tr[i], x);
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = max(res, tr[i]);
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
const int N = 1e5 + 10;

int n;
int a[N], b[N];
Fenwick<N> fw;

void solve() {
    vector<int> id(n + 1);
    for (int i = 1; i <= n; i++) id[b[i]] = i;

    vector<int> f(n + 1);
    fw.init(n);
    for (int i = 1; i <= n; i++) {
        for (int x = max(1, a[i] - 4); x <= min(n, a[i] + 4); x++) {
            int j = id[x];

            f[j] = fw.qr(j - 1) + 1;
        }
        for (int x = max(1, a[i] - 4); x <= min(n, a[i] + 4); x++) {
            int j = id[x];

            fw.upd(j, f[j]);
        }
    }

    cout << *max_element(f.begin() + 1, f.end()) << "\n";
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
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}