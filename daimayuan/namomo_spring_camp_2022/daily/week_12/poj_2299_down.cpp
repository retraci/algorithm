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
#include <bitset>
#include <cassert>
#include <cmath>

using namespace std;

// region fenwick
template<int SZ>
struct Fenwick {
    int n;
    int tr[SZ + 10];

    Fenwick() {}

    void init(int _n, int v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, int x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    int qr(int id) {
        int res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
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
const int N = 500010;

int n;
int a[N];
Fenwick<N> fw;
vector<int> lsh;
int nl;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh.clear();
    for (int i = 1; i <= n; i++) lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) a[i] = get(a[i]) + 1;
}

void solve() {
    init();
    fw.init(n);

    long long ans = 0;
    for (int i = n; i >= 1; i--) {
        ans += fw.qr(a[i] - 1);
        fw.upd(a[i], 1);
    }
    cout << ans << "\n";
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
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}