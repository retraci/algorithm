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

int n, k;
string s;

void solve() {
    vector<int> a;
    for (int i = 1; i <= n; i++) {
        if (s[i] == '1') a.push_back(i);
    }

    if (!a.empty() && n - a.back() <= k) {
        swap(s[a.back()], s[n]);
        k -= n - a.back();
        a.pop_back();
    }
    if (!a.empty() && a[0] - 1 <= k) {
        swap(s[a[0]], s[1]);
        k -= a[0] - 1;
        a.pop_back();
    }

    int ans = 0;
    for (int i = 2; i <= n - 1; i++) {
        ans += s[i] == '1' ? 11 : 0;
    }
    ans += s[1] == '1' ? 10 : 0;
    ans += s[n] == '1' ? 1 : 0;
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}