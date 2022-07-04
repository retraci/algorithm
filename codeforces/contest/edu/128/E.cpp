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

int n;
string s[2];

void solve() {
    int pre[n + 1][2], suf[n + 1][2];

    int lb = 1, rb = n;
    for (int i = 1; i <= n; i++) {
        if (s[0][i] == '*' || s[1][i] == '*') {
            lb = i;
            break;
        }
    }
    for (int i = n; i >= 1; i--) {
        if (s[0][i] == '*' || s[1][i] == '*') {
            rb = i;
            break;
        }
    }

    pre[lb][0] = pre[lb][1] = 0;
    for (int i = lb + 1; i <= n; i++) {
        for (int k = 0; k <= 1; k++) {
            pre[i][k] = min(pre[i - 1][k ^ 1] + 2, pre[i - 1][k] + 1 + (s[k ^ 1][i - 1] == '*'));
        }
    }
    suf[rb][0] = suf[rb][1] = 0;
    for (int i = rb - 1; i >= 1; i--) {
        for (int k = 0; k <= 1; k++) {
            suf[i][k] = min(suf[i + 1][k ^ 1] + 2, suf[i + 1][k] + 1 + (s[k ^ 1][i + 1] == '*'));
        }
    }

    int ans = 1e9;
    for (int i = lb; i <= rb; i++) {
        for (int k = 0; k <= 1; k++) {
            int t = pre[i][k] + suf[i][k] + (s[k ^ 1][i] == '*');
            ans = min(ans, t);
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
        cin >> s[0] >> s[1];
        s[0] = ' ' + s[0], s[1] = ' ' + s[1];
        solve();
    }

    return 0;
}