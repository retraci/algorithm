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
using ull = unsigned long long;
using pii = pair<int, int>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region kmp
// s 下标从 1 开始
vector<int> get_ne(const string &s) {
    int n = s.size() - 1;
    vector<int> ne(n + 1, 0);
    for (int i = 2, j = 0; i <= n; i++) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) j++;
        ne[i] = j;
    }

    return ne;
}

// t 里面 出现 s
int qr(const string &t, const string &s) {
    vector<int> ne = get_ne(s);
    int n = t.size() - 1, m = s.size() - 1;
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && t[i] != s[j + 1]) j = ne[j];
        if (t[i] == s[j + 1]) j++;

        if (j == m) {
            cout << i - m << " ";
            j = ne[j];
        }
    }

    return -1;
}
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

ll a, b;
string s;

void solve() {
    string t = s.substr(s.find('.') + 1);
    reverse(t.begin(), t.end());
    t = ' ' + t;
    auto ne = get_ne(t);

    int n = t.size() - 1;
    ll ans = -1e18;
    for (int i = 1; i <= n; i++) {
        ll T = i - ne[i];
        ll tmp = a * i - b * T;
        ans = max(ans, tmp);
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
//    cin >> _;
    while (_--) {
        cin >> a >> b;
        cin >> s;
        solve();
    }

    return 0;
}