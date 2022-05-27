#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cassert>
#include <random>
#include <cmath>

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
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e6 + 10;

int n, m, tmi, tmx, r;
int a[N];

int get(ll cur, int x) {
    return ((x - tmi - cur) % r + r) % r + tmi;
}

void solve() {
    r = tmx - tmi + 1;
    deque<pii> que;
    for (int i = 1; i <= n; i++) que.push_front({1, a[i]});

    ll cur = 0, tt = n;
    while (m--) {
        int t, k;
        cin >> t >> k;

        cur += t;
        ll ans = 0, s = 0;
        while (!que.empty() && s < k) {
            auto [len, x] = que.front(); que.pop_front();

            int used = min(k - s, 1LL * len);
            s += used, tt -= used;
            if (len > used) {
                int dta = len - used;
                que.push_front({dta, x});
            }
            ans += 1LL * used * get(cur, x);
        }

        if (s < k) ans += 1LL * (k - s) * tmx;
        cout << ans << "\n";

        int tmp = (tmx - tmi + cur) % r + tmi;
        que.push_back({n - tt, tmp}), tt = n;
    }
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
        cin >> n >> m >> tmi >> tmx;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}