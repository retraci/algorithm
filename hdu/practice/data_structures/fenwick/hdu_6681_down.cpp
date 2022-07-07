#include <bits/stdc++.h>

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
mt19937 mrnd(std::random_device{}());

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

    void init(int _n) {
        n = _n;
        fill(tr, tr + n + 1, 0);
    }

    void upd(int id, fwt x) {
        assert(id > 0);
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    int kth(fwt x) {
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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;

int n;
ai3 a[N];
Fenwick<N> fw;
vector<int> lsh;
int nl;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh.clear();
    for (int i = 1; i <= n; i++) {
        int x = a[i][0], y = a[i][1], d = a[i][2];

        lsh.push_back(x);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

void solve() {
    init();

    vector<int> b, down, up;
    for (int i = 1; i <= n; i++) {
        int x = a[i][0], y = a[i][1], d = a[i][2];

        if (d == 'L' || d == 'R') b.push_back(i);
        else if (d == 'U') up.push_back(i);
        else down.push_back(i);
    }

    ll ans = 0;
    {
        sort(b.begin(), b.end(), [&](int &lhs, int &rhs) {
            return a[lhs][1] < a[rhs][1];
        });
        sort(down.begin(), down.end(), [&](int &lhs, int &rhs) {
            return a[lhs][1] < a[rhs][1];
        });

        fw.init(nl + 1);
        int u = 0;
        for (auto oj : down) {
            while (u < b.size() && a[b[u]][1] <= a[oj][1]) {
                int x = a[b[u]][0], y = a[b[u]][1], d = a[b[u]][2];
                int nx = get(x) + 1;

                if (d == 'L') {
                    fw.upd(1, 1), fw.upd(nx + 1, -1);
                } else {
                    fw.upd(nx, 1), fw.upd(nl + 1, -1);
                }

                u++;
            }

            int nx = get(a[oj][0]) + 1;
            ans += fw.qr(nx);
        }
    }

    {
        sort(b.begin(), b.end(), [&](int &lhs, int &rhs) {
            return a[lhs][1] > a[rhs][1];
        });
        sort(up.begin(), up.end(), [&](int &lhs, int &rhs) {
            return a[lhs][1] > a[rhs][1];
        });

        fw.init(nl + 1);
        int u = 0;
        for (auto oj : up) {
            while (u < b.size() && a[b[u]][1] >= a[oj][1]) {
                int x = a[b[u]][0], y = a[b[u]][1], d = a[b[u]][2];
                int nx = get(x) + 1;

                if (d == 'L') {
                    fw.upd(1, 1), fw.upd(nx + 1, -1);
                } else {
                    fw.upd(nx, 1), fw.upd(nl + 1, -1);
                }

                u++;
            }

            int nx = get(a[oj][0]) + 1;
            ans += fw.qr(nx);
        }
    }

    cout << ans + 1 << "\n";
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
    cin >> _;
    while (_--) {
        int _n, _m;
        cin >> _n >> _m >> n;
        for (int i = 1; i <= n; i++) {
            int x, y;
            char d;
            cin >> x >> y >> d;
            a[i] = {x, y, d};
        }
        solve();
    }

    return 0;
}