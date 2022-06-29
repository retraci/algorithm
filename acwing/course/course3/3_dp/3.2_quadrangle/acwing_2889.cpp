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
const int N = 5010;

int n;
int a[N];
int f[N][N], p[N][N];

void solve() {
    for (int i = 1; i <= n; i++) a[i] += a[i - 1];

    for (int i = 1; i <= n; i++) p[i][i] = i;
    for (int len = 2; len <= n; len++) {
        for (int L = 1; L + len - 1 <= n; L++) {
            int R = L + len - 1;
            f[L][R] = 1e9;
            for (int k = p[L][R - 1]; k <= p[L + 1][R]; k++) {
                if (f[L][R] > f[L][k] + f[k + 1][R] + a[R] - a[L - 1]) {
                    f[L][R] = f[L][k] + f[k + 1][R] + a[R] - a[L - 1];
                    p[L][R] = k;
                }
            }
        }
    }

    cout << f[1][n] << "\n";
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