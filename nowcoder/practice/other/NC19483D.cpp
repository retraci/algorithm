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

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

int n, m, q;
int a[N];

void get_d(int d[], int len, int cnt) {
    while (cnt--) {
        for (int i = len; i - 1 >= 1; i--) {
            d[i] -= d[i - 1];
            d[i] %= MOD;
        }
    }
}

void get_s(int s[], int len, int cnt) {
    while (cnt--) {
        for (int i = 2; i <= len; i++) {
            s[i] += s[i - 1];
            s[i] %= MOD;
        }
    }
}

int calc(int xi[], int k, int x) {
    int res = 0, bas = 1;
    for (int i = 0; i <= k; i++) {
        res += 1LL * xi[i] * bas % MOD;
        res %= MOD;
        bas = 1LL * bas * x % MOD;
    }
    return res;
}

void get(int y[], int xi[], int k, int L) {
    for (int i = 1; i <= 6; i++) {
        y[i] = calc(xi, k, L + i - 1);
    }
}

void solve() {
    int xi[7], t1[7], t2[7];

    get_d(a, n, 6);
    while (m--) {
        int L, R, k;
        cin >> L >> R >> k;
        for (int i = 0; i <= k; i++) cin >> xi[k - i];

        get(t1, xi, k, 1);
        get(t2, xi, k, R - L + 2);
        get_d(t1, 6, 6);
        get_d(t2, 6, 6);

        for (int i = 1; i <= 6; i++) {
            a[L + i - 1] += t1[i];
            a[L + i - 1] %= MOD;
            a[R + i] -= t2[i];
            a[R + i] %= MOD;
        }
    }
    get_s(a, n, 7);

    while (q--) {
        int L, R;
        cin >> L >> R;

        int t = (a[R] - a[L - 1]) % MOD;
        t = (t + MOD) % MOD;
        cout << t << "\n";
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
        cin >> n >> m >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}