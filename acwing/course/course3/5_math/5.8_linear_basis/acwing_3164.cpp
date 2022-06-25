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

// region 线性基
template<int SZ>
struct LinearBasis {
    using lbt = ll;

    int mxb;
    lbt bas[SZ + 1];

    LinearBasis() {}

    void init(int _mxb) {
        mxb = _mxb;
        fill(bas, bas + mxb + 1, 0);
    }

    void ins(lbt x) {
        for (int i = mxb; i >= 0; i--) {
            if (x == 0) break;
            if (~x >> i & 1) continue;

            if (bas[i]) {
                x ^= bas[i];
            } else {
                for (int j = 0; j < i; j++) {
                    if (x >> j & 1) x ^= bas[j];
                }
                for (int j = i + 1; j <= mxb; j++) {
                    if (bas[j] >> i & 1) bas[j] ^= x;
                }
                bas[i] = x;
                break;
            }
        }
    }

    lbt qr() {
        lbt res = 0;
        for (int i = 0; i <= mxb; i++) res ^= bas[i];
        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;

int n;
ll a[N];
LinearBasis<63> lb;

void solve() {
    lb.init(63);
    for (int i = 1; i <= n; i++) lb.ins(a[i]);

    cout << lb.qr() << "\n";
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
        solve();
    }

    return 0;
}