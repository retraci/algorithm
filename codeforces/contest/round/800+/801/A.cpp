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
const int N = 44;

int n, m;
int a[N][N];

pii calc(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2) + 1, dy = abs(y1 - y2) + 1;
    return {dx, dy};
}

void solve() {
    int mx = -2e9, x, y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (mx < a[i][j]) {
                mx = a[i][j], x = i, y = j;
            }
        }
    }

    auto [dx1, dy1] = calc(x, y, 1, 1);
    auto [dx2, dy2] = calc(x, y, 1, m);
    auto [dx3, dy3] = calc(x, y, n, 1);
    auto [dx4, dy4] = calc(x, y, n, m);

    int mxx = max({dx1, dx2, dx3, dx4});
    int mxy = max({dy1, dy2, dy3, dy4});
    int ans = mxx * mxy;
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
    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cin >> a[i][j];
        }
        solve();
    }

    return 0;
}