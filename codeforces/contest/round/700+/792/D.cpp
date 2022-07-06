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
const int N = 2e5 + 10;

int n, k;
int a[N];

void solve() {
    vector<int> ord(n + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin() + 1, ord.end(), [&](auto &lhs, auto &rhs) {
        return a[lhs] + lhs < a[rhs] + rhs;
    });

    vector<int> vis(n + 1);
    for (int i = 1; i <= n - k; i++) {
        int id = ord[i];
        vis[id] = 1;
    }

    ll ans = 0, cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) ans += cnt + a[i];
        else cnt++;
    }
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
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}