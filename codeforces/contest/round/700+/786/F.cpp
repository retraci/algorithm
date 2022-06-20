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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1010;

int n, m, q;
string a[N];
int b[N * N];

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int id = (j - 1) * n + i;
            b[id] = a[i][j] == '*';
        }
    }
    int tt = accumulate(b + 1, b + n * m + 1, 0);
    int pc = accumulate(b + 1, b + tt + 1, 0);

    while (q--) {
        int x, y;
        cin >> x >> y;
        int id = (y - 1) * n + x;

        if (b[id] == 0) {
            pc += b[++tt];
            b[id] = 1;
            pc += id <= tt;
        } else {
            b[id] = 0;
            pc -= id <= tt;
            pc -= b[tt--];
        }

        cout << tt - pc << "\n";
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
        cin >> n >> m >> q;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            a[i] = ' ' + a[i];
        }
        solve();
    }

    return 0;
}