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
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2010;

int n;
string g[N];

void solve() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += count(g[i].begin(), g[i].end(), '1');

    int mx = 0;
    for (int j = 1; j <= n; j++) {
        int c = 0;
        for (int i = 1; i <= n; i++) {
            int x = i, y = (j - 1 + i - 1) % n + 1;
            c += g[x][y] == '1';
        }
        mx = max(mx, c);
    }

    int ans = n - mx + cnt - mx;
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> g[i], g[i] = ' ' + g[i];
        solve();
    }

    return 0;
}