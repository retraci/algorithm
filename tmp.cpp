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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};

string s;

void solve() {
    int n = s.size() - 1;
    for (int L = 1; L <= n; L++) {
        for (int R = L; R <= n; R++) {
            string t = s.substr(L, R - L + 1);
            reverse(t.begin(), t.end());
            string cur = s.substr(1, L - 1 - 1 + 1) + t + s.substr(R + 1, n - (R + 1) + 1);
            string rc = string(cur.begin(), cur.end());
            if (cur == rc) {
                cout << L << " " << R << "\n";
                return;
            }
        }
    }
}

void prework() {
//    int T = 100;
//    while (T--) {
//        string s(100, ' ');
//        for (int i = 0; i < 100; i++) s[i] = rnd(26) + 'a';
//        cout << s << "\n";
//    }
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