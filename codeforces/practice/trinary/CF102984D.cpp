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
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 5e5 + 10;

int n, q;
int a[N];
vector<int> b;
int id[N], lbs[N], rbs[N];

ll gao(int k) {
    return 1LL * k * (k + 1) / 2;
}

ll calc(int L, int R) {
    int bid1 = id[L], bid2 = id[R];
    if (bid1 == bid2) {
        int sz = R - L + 1;
        return gao(sz);
    } else {
        int sz1 = rbs[bid1] - L + 1, sz2 = R - lbs[bid2] + 1;
        ll ans = b[bid2 - 1] - b[bid1];
        ans += gao(sz1) + gao(sz2);
        return ans;
    }
}

ll calc(int lb, int rb, int md) {
    return max(calc(lb, md), calc(md, rb));
}

void solve() {
    b.push_back(0);
    for (int i = 1; i <= n; i++) {
        int j = i + 1;
        while (j <= n && a[j] >= a[j - 1]) j++;

        int bid = b.size();
        for (int k = i; k < j; k++) id[k] = bid;
        lbs[bid] = i, rbs[bid] = j - 1;
        b.push_back(j - i);

        i = j - 1;
    }
    for (int i = 1; i < b.size(); i++) b[i] = b[i - 1] + gao(b[i]);

    while (q--) {
        int L, R;
        cin >> L >> R;

        int left = 1, right = n;
        while (left + 10 < right) {
            int mdl = (2 * left + right) / 3;
            int mdr = (left + 2 * right) / 3;
            ll v1 = calc(L, R, mdl), v2 = calc(L, R, mdr);
            if (v1 > v2) left = mdl;
            else right = mdr;
        }

        ll ans = 1e18;
        for (int k = left; k <= right; k++) ans = min(ans, calc(L, R, k));
        cout << ans << "\n";
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
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}