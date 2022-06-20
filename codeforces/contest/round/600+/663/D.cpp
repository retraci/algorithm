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
const int N = 1e6 + 10;

int n, m;
string g[N];

bool check(int m1, int m2, int rs) {
    if (rs == 2) {
        int b1 = m1 >> 0 & 1, b2 = m2 >> 0 & 1;
        int b3 = m1 >> 1 & 1, b4 = m2 >> 1 & 1;
        return (b1 + b2 + b3 + b4) & 1;
    } else {
        int b1 = m1 >> 0 & 1, b2 = m2 >> 0 & 1;
        int b3 = m1 >> 1 & 1, b4 = m2 >> 1 & 1;
        int b5 = m1 >> 2 & 1, b6 = m2 >> 2 & 1;

        return (b1 + b2 + b3 + b4) & 1 && (b3 + b4 + b5 + b6) & 1;
    }
}

int calc(int u, int v, int rs) {
    int res = 0;
    for (int i = 0; i < rs; i++) {
        int b1 = u >> i & 1, b2 = v >> i & 1;
        res += b1 ^ b2;
    }
    return res;
}

void solve() {
    if (n >= 4) {
        cout << -1 << "\n";
        return;
    }
    if (n == 1) {
        cout << 0 << "\n";
        return;
    }

    vector<int> a(m + 1);
    for (int j = 1; j <= m; j++) {
        int x = 0;
        for (int i = 1; i <= n; i++) {
            x = (x << 1) + g[i][j] - '0';
        }
        a[j] = x;
    }

    int lim = 1 << n;
    int f[m + 1][lim];
    memset(f, 0x3f, sizeof f);
    for (int mask = 0; mask < lim; mask++) f[1][mask] = calc(a[1], mask, n);
    for (int j = 2; j <= m; j++) {
        for (int mask = 0; mask < lim; mask++) {
            for (int pre = 0; pre < lim; pre++) {
                if (check(mask, pre, n)) f[j][mask] = min(f[j][mask], f[j - 1][pre] + calc(a[j], mask, n));
            }
        }
    }

    cout << *min_element(&f[m][0], &f[m][lim]) << "\n";
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
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}