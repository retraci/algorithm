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
using ai4 = array<int, 4>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int n, m, k;
ai4 a[11];

void solve() {
    if (~(n * m) & 1) {
        cout << n * m << "\n";
        return;
    }

    int flag = 0;
    for (int i = 1; i <= k; i++) {
        auto [x1, y1, x2, y2] = a[i];
        if (x1 == x2 && y1 == y2) continue;
        if (~(x1 + y1) & 1 && ~(x2 + y2) & 1) flag = 1;
    }
    cout << (flag ? n * m : n * m + 1) << "\n";
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
        cin >> n >> m >> k;
        for (int i = 1; i <= k; i++) {
            for (int j = 0; j < 4; j++) cin >> a[i][j];
        }
        solve();
    }

    return 0;
}