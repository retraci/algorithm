#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

#define ll long long

typedef pair<ll, ll> pll;

const int N = 4e5 + 10;
const ll BASE = 131, BASE2 = 233;
const ll MOD = 998244353, MOD2 = 50331653;

int n, m;
string ss[N];
ll p[N], p2[N];
vector<ll> h[N], h2[N];
map<pll, int> mp;

ll get(int id, int L, int R) {
    return (h[id][R] - h[id][L - 1] * p[R - L + 1] % MOD + MOD) % MOD;
}

ll get2(int id, int L, int R) {
    return (h2[id][R] - h2[id][L - 1] * p2[R - L + 1] % MOD2 + MOD2) % MOD2;
}

bool check(int id, int L1, int R1, int L2, int R2) {
    ll h11 = get(id, L1, R1), h12 = get(id, L2, R2);
    ll h21 = get2(id, L1, R1), h22 = get2(id, L2, R2);
    return h11 == h12 && h21 == h22;
}

int get_val(int id, int L, int R) {
    return mp[{get(id, L, R), get2(id, L, R)}];
}

void init() {
    p[0] = p2[0] = 1;
    for (int i = 1; i < N; i++) {
        p[i] = p[i - 1] * BASE % MOD;
        p2[i] = p2[i - 1] * BASE2 % MOD2;
    }

    for (int i = 1; i <= n; i++) {
        string s = ss[i];
        int m = s.size();
        h[i].resize(m + 1);
        h2[i].resize(m + 1);
        for (int j = 1; j <= m; j++) {
            h[i][j] = (h[i][j - 1] * BASE + s[j - 1]) % MOD;
            h2[i][j] = (h2[i][j - 1] * BASE2 + s[j - 1]) % MOD2;
        }
        mp[{h[i][m], h2[i][m]}]++;
    }
}

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

void solve() {
    init();

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        string s = ss[i];
        int m = s.size();
        ans += get_val(i, 1, m) - 1;
    }
    ans /= 2;
    for (int i = 1; i <= n; i++) {
        string s = ss[i];
        int m = s.size();
        int half = m / 2;
        for (int j = 1; j <= half; j++) {
            int lb = j + 1, rb = m - j;
            debug(1, j, rb + 1, m, get(i, 1, j), get(i, rb + 1, m));
            if (check(i, 1, j, rb + 1, m)) {
                ans += get_val(i, lb, rb);
            }
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> ss[i];
    solve();

    return 0;
}