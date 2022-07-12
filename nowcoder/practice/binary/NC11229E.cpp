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
const int N = 1e6 + 10;
const int MOD = 998244353;

int n, m;
vector<int> a[N];

int calc(const vector<int> &arr) {
    int res = 0;
    for (int i = 0; i < arr.size(); i++) {
        int cur = arr.end() - lower_bound(arr.begin() + i + 1, arr.end(), m - arr[i]);
        res += cur;
        res %= MOD;
    }

    return res;
}

void solve() {
    vector<int> b;
    for (int i = 1; i <= n; i++) {
        for (int x : a[i]) {
            b.push_back(x);
        }
    }

    sort(b.begin(), b.end());
    for (int i = 1; i <= n; i++) sort(a[i].begin(), a[i].end());

    int ans = calc(b);
    for (int i = 1; i <= n; i++) {
        ans -= calc(a[i]);
        ans %= MOD;
    }

    ans = (ans + MOD) % MOD;
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) {
            int s;
            cin >> s;
            a[i].resize(s);
            for (int j = 0; j < s; j++) cin >> a[i][j];
        }
        solve();
    }

    return 0;
}