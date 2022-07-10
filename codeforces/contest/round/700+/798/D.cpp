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
const int N = 1010;

int n, m;
string a[N];

void solve() {
    vector<int> mx(4, -1e9);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 'W') continue;

            mx[0] = max(mx[0], -i + -j);
            mx[1] = max(mx[1], -i + j);
            mx[2] = max(mx[2], i + -j);
            mx[3] = max(mx[3], i + j);
        }
    }

    int ans = 1e9, x, y;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int cur = max({
                mx[0] + i + j,
                mx[1] + i + -j,
                mx[2] + -i + j,
                mx[3] + -i + -j
            });

            if (ans > cur) {
                ans = cur, x = i, y = j;
            }
        }
    }

    cout << x << " " << y << "\n";
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
            cin >> a[i];
            a[i] = ' ' + a[i];
        }
        solve();
    }

    return 0;
}