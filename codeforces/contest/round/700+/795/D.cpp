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

// region 区间最值
template<int SZ>
struct ST {
    using stt = ll;

    int n;
    stt stmi[__lg(SZ) + 1][SZ + 10];
    stt stmx[__lg(SZ) + 1][SZ + 10];

    ST() {}

    // [0, n);
    void init(const vector<stt> &a) {
        n = a.size();

        for (int i = 0; i < n; i++) stmi[0][i] = stmx[0][i] = a[i];
        int mxb = __lg(n - 1);
        for (int k = 1; k <= mxb; k++) {
            for (int L = 0; L + (1 << k) - 1 < n; L++) {
                stmi[k][L] = min(stmi[k - 1][L], stmi[k - 1][L + (1 << (k - 1))]);
                stmx[k][L] = max(stmx[k - 1][L], stmx[k - 1][L + (1 << (k - 1))]);
            }
        }
    }

    // [L, R]
    stt get_mi(int L, int R) {
        assert(L <= R && L >= 0 && R < n);

        int k = __lg(R - L + 1);
        return min(stmi[k][L], stmi[k][R - (1 << k) + 1]);
    }

    // [L, R]
    stt get_mx(int L, int R) {
        assert(L <= R && L >= 0 && R < n);

        int k = __lg(R - L + 1);
        return max(stmx[k][L], stmx[k][R - (1 << k) + 1]);
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 2e5 + 10;

int n;
int a[N];
ST<N> st;

void solve() {
    vector<int> lbs(n + 1), rbs(n + 1);

    {
        vector<int> stk;
        for (int i = 1; i <= n; i++) {
            while (!stk.empty() && a[i] >= a[stk.back()]) stk.pop_back();
            int lb = stk.empty() ? 0 : stk.back();
            lbs[i] = lb + 1;
            stk.push_back(i);
        }
    }
    {
        vector<int> stk;
        for (int i = n; i >= 1; i--) {
            while (!stk.empty() && a[i] >= a[stk.back()]) stk.pop_back();
            int rb = stk.empty() ? n + 1 : stk.back();
            rbs[i] = rb - 1;
            stk.push_back(i);
        }
    }

    vector<ll> s(n + 1);
    for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i];
    st.init(s);

    int flag = 0;
    for (int i = 1; i <= n; i++) {
        int L = lbs[i], R = rbs[i];

        ll mi = st.get_mi(L - 1, i - 1);
        ll mx = st.get_mx(i, R);
        ll sum = mx - mi;

        flag |= a[i] < sum;
    }

    cout << (flag ? "NO" : "YES") << "\n";
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