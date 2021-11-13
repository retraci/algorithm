#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

typedef pair<double, double> pdd;

const int N = 1010;
const double eps = 1e-8;

double X, Y;
int n;
pdd ps[N];
int fa[N];
double us[N], ds[N], ls[N], rs[N];

double calc(pdd &p1, pdd &p2) {
    auto &[x1, y1] = p1;
    auto &[x2, y2] = p2;
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool check(double mid) {
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        auto &[x, y] = ps[i];
        us[i] = x - mid, ds[i] = x + mid;
        ls[i] = y - mid, rs[i] = y + mid;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            double d = calc(ps[i], ps[j]);
            if (2.0 * mid > d) {
                int tx = find(i), ty = find(j);

//                cout << i << " " << j << endl;

                fa[tx] = ty;
                us[ty] = min(us[ty], us[tx]);
                ds[ty] = max(ds[ty], ds[tx]);
                ls[ty] = min(ls[ty], ls[tx]);
                rs[ty] = max(rs[ty], rs[tx]);

//                cout << us[ty] << " " << ds[ty] << " " << ls[ty] << " " << rs[ty] << endl;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        int tx = find(i);
        if (us[tx] < 0 && ds[tx] > X) return false;
        if (ls[tx] < 0 && rs[tx] > Y) return false;
        if (us[tx] < 0 && ls[tx] < 0) return false;
        if (ds[tx] > X && rs[tx] > Y) return false;
    }

    return true;
}

void solve() {
//    check(2.5);

    double left = 0, right = 1000000;
    while (left + eps < right) {
        double mid = (left + right) / 2;
        if (check(mid)) left = mid;
        else right = mid;
    }

    cout << fixed << setprecision(6);
    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> X >> Y >> n;
    for (int i = 1; i <= n; i++) {
        double x, y;
        cin >> x >> y;
        ps[i] = {x, y};
    }
    solve();

    return 0;
}