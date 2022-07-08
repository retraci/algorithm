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
const int N = 210;

int n;
string s;
int p[N];

ll lcm(ll x, ll y) {
    return x * y / __gcd(x, y);
}

void solve() {
    ll ans = 1;
    vector<int> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;

        deque<char> tmp;
        int j = i;
        while (!vis[j]) {
            vis[j] = 1;
            tmp.push_back(s[j]);

            j = p[j];
        }

        deque<char> cur = tmp;
        int cnt = 0;
        while (1) {
            cnt++;
            cur.push_back(cur.front()), cur.pop_front();
            if (cur == tmp) break;
        }

        ans = lcm(ans, cnt);
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
        cin >> s;
        s = ' ' + s;
        for (int i = 1; i <= n; i++) cin >> p[i];
        solve();
    }

    return 0;
}