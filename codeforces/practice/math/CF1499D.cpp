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

// region 欧拉筛
vector<int> isp, pr, cnt;

void init_prime(int lim) {
    isp = vector<int>(lim + 1, 1);
    cnt.resize(lim + 1);

    isp[0] = isp[1] = 0;
    for (int i = 2; i <= lim; i++) {
        if (isp[i]) {
            pr.push_back(i);
            cnt[i] = 1;
        }

        for (int p : pr) {
            if (p > lim / i) break;

            isp[i * p] = 0;
            cnt[i * p] = cnt[i] + 1;
            if (i % p == 0) {
                cnt[i * p] = cnt[i];
                break;
            }
        }
    }
}
// endregion

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

int c, d, x;

ll calc(int y) {
    if ((y + d) % c) return 0;
    return 1LL << cnt[(y + d) / c];
}

void solve() {
    long long ans = 0;
    for (int g = 1; g <= x / g; g++) {
        if (x % g) continue;
        ans += calc(x / g);
        if (x / g != g) ans += calc(g);
    }

    cout << ans << "\n";
}

void prework() {
    init_prime(2e7);
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
        cin >> c >> d >> x;
        solve();
    }

    return 0;
}