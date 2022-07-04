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

const int MOD = 998244353;

int ksm(int a, int b) {
    a %= MOD;
    int res = 1;
    while (b) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int S = 17;
const int N = 1010;

int n;
string s;
int f[S + 1][1 << S];

void init() {
    int num = count(s.begin() + 1, s.end(), '?');
    int d[n + 1][n + 1], p[n + 1][n + 1];
    fill(&d[0][0], &d[n][n] + 1, 0);
    fill(&p[0][0], &p[n][n] + 1, num);

    for (int len = 1; len <= n; len++) {
        for (int L = 1; L + len - 1 <= n; L++) {
            int R = L + len - 1;
            int &cd = d[L][R], &cp = p[L][R];

            if (len != 1) {
                int cnt = (s[L] == '?') + (s[R] == '?');

                cd = d[L + 1][R - 1];
                cp = p[L + 1][R - 1];

                if (cnt == 0) {
                    if (s[L] != s[R]) cp = -1;
                } else if (cnt == 1) {
                    cp -= 1;
                    char ch = s[L] == '?' ? s[R] : s[L];
                    cd |= 1 << (ch - 'a');
                } else {
                    cp -= 1;
                }
            }

            if (cp < 0) continue;
            for (int k = 1; k <= S; k++) {
                f[k][cd] += ksm(k, cp);
                f[k][cd] %= MOD;
            }
        }
    }

    int lim = 1 << S;
    for (int k = 1; k <= S; k++) {
        for (int i = 0; i < S; i++) {
            for (int mask = 0; mask < lim; mask++) {
                if (mask >> i & 1) {
                    f[k][mask] += f[k][mask ^ (1 << i)];
                    f[k][mask] %= MOD;
                }
            }
        }
    }
}

void solve() {
    init();

    int q;
    cin >> q;
    while (q--) {
        static string t;
        cin >> t;

        int mask = 0;
        for (char ch : t) mask |= 1 << (ch - 'a');
        cout << f[t.size()][mask] << "\n";
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
        cin >> n;
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}