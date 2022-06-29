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
const int N = 22;

int n, m;
int a[N];

using sat = double;

// [L, R)
int rand(int L, int R) {
    return rnd(1e9) / 1e9 * (R - L) + L;
}

sat calc() {
    static int s[N];

    fill(s + 1, s + m + 1, 0);
    for (int i = 1; i <= n; i++) {
        int k = 1;
        for (int j = 2; j <= m; j++) {
            if (s[j] <= s[k]) k = j;
        }
        s[k] += a[i];
    }

    sat avg = 0;
    for (int i = 1; i <= m; i++) avg += 1.0 * s[i] / m;

    sat res = 0;
    for (int i = 1; i <= m; i++) {
        res += (s[i] - avg) * (s[i] - avg);
    }
    res = sqrt(res / m);

    return res;
}

// 最大值: exp(dta / t) > rand(0, 1), 最小值: exp(-dta / t) > rand(0, 1)
sat SA(double T0, double TE, double apl) {
    sat f = calc(), res = f;
    for (double t = T0; t > TE; t *= apl) {
        int ta = rand(1, n + 1), tb = rand(1, n + 1);
        assert(ta >= 1 && ta <= n && tb >= 1 && tb <= n);
        swap(a[ta], a[tb]);
        sat nf = calc();

        res = min(res, nf);
        sat dta = nf - f;
        if (exp(-dta / t) > rand(0, 1)) f = nf;
        else swap(a[ta], a[tb]);
    }

    return res;
}

void solve() {
    double ans = 1e18;
    const double start = clock();
    while ((clock() - start) / CLOCKS_PER_SEC < 0.8) ans = min(ans, SA(1e4, 1e-4, 0.99));

    cout << fixed << setprecision(2) << ans << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}