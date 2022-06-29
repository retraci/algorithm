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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 55;

int n, m;
pii a[N];

// [L, R)
int rand(int L, int R) {
    return rnd(1e9) / 1e9 * (R - L) + L;
}

int calc() {
    int res = 0;
    for (int i = 1; i <= m; i++) {
        res += a[i].fi + a[i].se;
        if (i <= n) {
            if (a[i].fi == 10) res += a[i + 1].fi + a[i + 1].se;
            else if (a[i].fi + a[i].se == 10) res += a[i + 1].fi;
        }
    }
    return res;
}

// 最大值: exp(dta / t) > rand(0, 1), 最小值: exp(-dta / t) > rand(0, 1)
int SA(double T0, double TE, double apl) {
    int f = calc(), res = f;
    for (double t = T0; t > TE; t *= apl) {
        int ta = rand(1, m + 1), tb = rand(1, m + 1);
        assert(ta >= 1 && ta <= m && tb >= 1 && tb <= m);
        swap(a[ta], a[tb]);
        if (n + (a[n].fi == 10) != m) {
            swap(a[ta], a[tb]);
            continue;
        }
        int nf = calc();

        res = max(res, nf);
        int dta = nf - f;
        if (exp(dta / t) > rand(0, 1)) f = nf;
        else swap(a[ta], a[tb]);
    }

    return res;
}

void solve() {
    double start = clock();
    int ans = 0;
    while ((clock() - start) / CLOCKS_PER_SEC < 0.9) ans = max(ans, SA(1e4, 1e-4, 0.99));
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
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        if (a[n].fi == 10) m = n + 1, cin >> a[n + 1].fi >> a[n + 1].se;
        else m = n;

        solve();
    }

    return 0;
}