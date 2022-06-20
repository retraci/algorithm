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
const int N = 110;

int n, d;
vector<int> lsh;
int nl;
int f[2010];

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void solve() {
    vector<int> fs;
    for (int i = 1; i <= n / i; i++) {
        if (n % i == 0) {
            fs.push_back(i);
            if (i != n / i) fs.push_back(n / i);
        }
    }

    lsh = vector<int>(fs);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    fill(f, f + nl + 1, 0);
    f[1] = 1;
    for (int i = 1; i <= nl; i++) {
        int x = lsh[i - 1];
        if (x == 1 || x % d != 0 || x % (1LL * d * d) == 0) continue;

        for (int j = 1; j <= nl; j++) {
            int y = lsh[j - 1];

            if (1LL * x * y <= n && n % (x * y) == 0) {
                int v = get(x * y) + 1;
                f[v] += f[j];
                f[v] = min(2, f[v]);
            }
        }
    }

    cout << (f[nl] >= 2 ? "YES" : "NO") << "\n";
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
        cin >> n >> d;
        solve();
    }

    return 0;
}