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

// region 区间gcd
template<int SZ>
struct ST {
    using stt = int;

    int n;
    stt st[__lg(SZ) + 1][SZ + 10];

    ST() {}

    // [0, n);
    void init(const vector<stt> &a) {
        n = a.size();

        for (int i = 0; i < n; i++) st[0][i] = a[i];
        int mxb = __lg(n - 1);
        for (int k = 1; k <= mxb; k++) {
            for (int L = 0; L + (1 << k) - 1 < n; L++) {
                st[k][L] = __gcd(st[k - 1][L], st[k - 1][L + (1 << (k - 1))]);
            }
        }
    }

    // [L, R]
    stt qr(int L, int R) {
        assert(L <= R && L >= 0 && R < n);

        int k = __lg(R - L + 1);
        return __gcd(st[k][L], st[k][R - (1 << k) + 1]);
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 2e5 + 10;

int n, q;
int a[N], b[N];
ST<N> st1, st2;

void solve() {
    vector<int> d1(n + 2), d2(n + 2);
    for (int i = 1; i <= n; i++) {
        d1[i] = a[i] - a[i - 1];
        d2[i] = b[i] - b[i - 1];
    }
    st1.init(d1), st2.init(d2);

    while (q--) {
        int x1, x2, y1, y2;
        cin >> y1 >> y2 >> x1 >> x2;

        int ans = a[y1] + b[x1];
        if (x1 + 1 <= x2) ans = __gcd(ans, st2.get(x1 + 1, x2));
        if (y1 + 1 <= y2) ans = __gcd(ans, st1.get(y1 + 1, y2));
        ans = abs(ans);

        cout << ans << "\n";
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
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        solve();
    }

    return 0;
}