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
const int N = 3e5 + 10;

int n;
int a[N];

ll calc(int x) {
    static int dta[N];

    for (int i = 1; i <= n; i++) dta[i] = x - a[i];
    int c1 = 0;
    for (int i = 1; i <= n; i++) c1 += dta[i] & 1;
    ll d1 = 2 * c1 - 1;

    ll sum = accumulate(dta + 1, dta + n + 1, 0LL);
    ll c = sum / 3, r = sum % 3;
    ll d2 = 2 * c;
    if (r == 1) d2++;
    else if (r == 2) d2 += 2;

    return max(d1, d2);
}

void solve() {
    int mx = *max_element(a + 1, a + n + 1);
    ll ans = min(calc(mx), calc(mx + 1));
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