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
const int N = 3010;

int n, k;
int a[N];

void solve() {
    ll tc = count(a + 1, a + n + 1, 0);
    ll ts = accumulate(a + 1, a + n + 1, 0LL);

    if (ts + tc * -k > 0 || ts + tc * k < 0) {
        cout << -1 << "\n";
        return;
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ll cnt = 0, sum = 0;
        for (int j = i; j <= n; j++) {
            cnt += a[j] == 0;
            sum += a[j];

            ll lb = max(-k * cnt, -ts - (k * (tc - cnt)));
            ll rb = min(k * cnt, -ts - (-k * (tc - cnt)));
            ans = max({ans, abs(sum + lb), abs(sum + rb)});
        }
    }

    ans++;
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
//    cin >> _;
    while (_--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}