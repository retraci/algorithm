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

// region 普通方程
template<int N, int M>
struct Gauss {
    using gst = double;
    const gst eps = 1e-9;

    gst mat[N + 10][M + 10];

    Gauss() {}

    // r 为方程个数, c 为未知数个数; 返回: 自由元个数, 无解返回 -1
    // mat[1 ~ c]: 增广矩阵, c + 1 位置为常数
    pair<int, vector<gst>> work(int r, int c) {
        int row = 1;
        for (int col = 1; col <= c; col++) {
            for (int i = row; i <= r; i++) {
                if (fabs(mat[i][col]) > eps) {
                    swap(mat[i], mat[row]);
                    break;
                }
            }
            if (fabs(mat[row][col]) < eps) break;

            for (int i = 1; i <= r; i++) {
                if (i != row && fabs(mat[i][col]) > eps) {
                    gst rate = mat[i][col] / mat[row][col];
                    for (int j = c + 1; j >= col; j--) {
                        mat[i][j] -= mat[row][j] * rate;
                    }
                }
            }
            row++;
        }

        if (row <= r) {
            for (int i = row; i <= r; i++) {
                if (fabs(mat[i][c + 1]) > eps) return {-1, {}};
            }
            return {r - row + 1, {}};
        }

        vector<gst> res(c + 1);
        for (int i = 1; i <= c; i++) res[i] = mat[i][c + 1] /= mat[i][i];
        return {0, res};
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 15;

int n;
double a[N][N];
Gauss<N, N + 1> gauss;

void solve() {
    for (int i = 1; i <= n; i++) {
        double s = 0;
        for (int j = 1; j <= n; j++) {
            gauss.mat[i][j] = -2 * (a[i][j] - a[i + 1][j]);
            s += a[i + 1][j] * a[i + 1][j] - a[i][j] * a[i][j];
        }
        gauss.mat[i][n + 1] = s;
    }

    auto [cnt, ans] = gauss.work(n, n);
    assert(cnt == 0);

    for (int i = 1; i <= n; i++) {
        cout << fixed << setprecision(3) << ans[i] << " \n"[i == n];
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
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
            }
        }
        solve();
    }

    return 0;
}