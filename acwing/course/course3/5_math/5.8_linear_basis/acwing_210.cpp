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

// region 线性基 (静态)
template<int SZ>
struct LinearBasis {
    using lbt = ll;

    int mxb, isLinCor;
    lbt bas[SZ + 1];
    vector<lbt> B;

    LinearBasis() {}

    void init(int _mxb) {
        mxb = _mxb, isLinCor = 0;
        fill(bas, bas + mxb + 1, 0);
        B.clear();
    }

    void build(const vector<lbt> &a) {
        for (lbt x : a) isLinCor |= !ins(x);
        for (int i = 0; i <= mxb; i++) {
            if (bas[i]) B.push_back(bas[i]);
        }
    }

    bool ins(lbt x) {
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
                return true;
            }
        }
        return false;
    }

    lbt qr_mx() {
        lbt res = 0;
        for (int i = 0; i <= mxb; i++) res ^= bas[i];
        return res;
    }

    lbt kth(lbt k) {
        if (isLinCor) k--;

        lbt res = 0;
        for (lbt b : B) {
            if (k & 1) res ^= b;
            k >>= 1;
        }

        return k == 0 ? res : -1;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 10010;

int n;
ll a[N];
LinearBasis<64> lb;

void solve() {
    int mxb = __lg(*max_element(a + 1, a + n + 1));
    lb.init(mxb);
    lb.build(vector<ll>(a + 1, a + n + 1));

    static char buf[111];
    static int CA = 0;
    sprintf(buf, "Case #%d:", ++CA);
    cout << string(buf) << "\n";
    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;

        cout << lb.kth(k) << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}