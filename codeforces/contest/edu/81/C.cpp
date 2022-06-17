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
const int N = 1e5 + 10;

string s, t;
int nxt[N][26];

void solve() {
    vector<int> lst(26, -1);
    for (int i = s.size() - 1; i >= 1; i--) {
        for (int j = 0; j < 26; j++) nxt[i][j] = lst[j];
        lst[s[i] - 'a'] = i;
    }
    for (int j = 0; j < 26; j++) nxt[0][j] = lst[j];

    int j = 1, ans = 0;
    while (j <= t.size() - 1) {
        if (nxt[0][t[j] - 'a'] == -1) {
            cout << -1 << "\n";
            return;
        }

        ans++;
        int u = 0;
        while (j <= t.size() - 1 && nxt[u][t[j] - 'a'] != -1) {
            u = nxt[u][t[j] - 'a'];
            j++;
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
        cin >> s >> t;
        s = ' ' + s; t = ' ' + t;
        solve();
    }

    return 0;
}