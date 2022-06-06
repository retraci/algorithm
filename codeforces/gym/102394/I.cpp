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
mt19937 mrnd(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int MOD = 1e9 + 7;

int n;
int a[N];

void solve() {
    if (a[1] != 0 || a[n] != n - 1) {
        cout << 0 << "\n";
        return;
    }

    for (int i = 2; i <= n; i++) {
        if (a[i] < a[i - 1]) {
            cout << 0 << "\n";
            return;
        }
    }

    int ans = 1, sz = 0;
    for (int i = 2; i <= n; i++) {
        if (a[i] == a[i - 1]) {
            if (sz == 0) {
                cout << 0 << "\n";
                return;
            }
            ans = 1LL * ans * sz % MOD;
            sz--;
        } else {
            ans *= 2;
            ans %= MOD;

            sz += a[i] - a[i - 1] - 1;
        }
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}