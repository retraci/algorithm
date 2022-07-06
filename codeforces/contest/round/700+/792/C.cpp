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

int n, m;
vector<vector<int>> a;

bool check() {
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            if (a[i][j] < a[i][j - 1]) return false;
        }
    }

    return true;
}

void solve() {
    if (check()) {
        cout << 1 << " " << 1 << "\n";
        return;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            if (a[i][j] >= a[i][j - 1]) continue;

            // swap(j, k)
            int t1 = 0, t2 = 0;
            for (int k = j - 1; k >= 1; k--) {
                if (a[i][j] >= a[i][k - 1] && a[i][j] <= a[i][k + 1]
                    && a[i][k] >= a[i][j - 1] && a[i][k] <= a[i][j + 1]) {
                    t1 = j, t2 = k;

                    for (int v = 1; v <= n; v++) swap(a[v][t1], a[v][t2]);
                    break;
                }
            }

            if (check()) {
                cout << t1 << " " << t2 << "\n";
                return;
            }
            for (int v = 1; v <= n; v++) swap(a[v][t1], a[v][t2]);

            // swap(j - 1, k)
            for (int k = j; k <= m; k++) {
                if (a[i][j - 1] >= a[i][k - 1] && a[i][j - 1] <= a[i][k + 1]
                    && a[i][k] >= a[i][j - 1 - 1] && a[i][k] <= a[i][j - 1 + 1]) {
                    t1 = j - 1, t2 = k;

                    for (int v = 1; v <= n; v++) swap(a[v][t1], a[v][t2]);
                    break;
                }
            }

            if (check()) {
                cout << t1 << " " << t2 << "\n";
                return;
            }

            cout << -1 << "\n";
            return;
        }
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
    cin >> _;
    while (_--) {
        cin >> n >> m;
        a = vector<vector<int>>(n + 1, vector<int>(m + 2));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> a[i][j];
            }
            a[i][m + 1] = 1e9;
        }

        solve();
    }

    return 0;
}