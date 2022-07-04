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

int n;
string s;
int s1;

bool check(int md) {
    int c0 = 0, c1 = 0, mx = 0, L = 1;
    for (int i = 1; i <= n; i++) {
        c0 += s[i] == '0', c1 += s[i] == '1';
        while (c0 > md) {
            c0 -= s[L] == '0', c1 -= s[L] == '1';
            L++;
        }

        mx = max(mx, c1);
    }

    return s1 - mx <= md;
}

void solve() {
    s1 = count(s.begin(), s.end(), '1');
    n = s.size() - 1;
    int left = 0, right = n;
    while (left < right) {
        int md = left + right >> 1;
        if (check(md)) right = md;
        else left = md + 1;
    }

    cout << left << "\n";
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
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}