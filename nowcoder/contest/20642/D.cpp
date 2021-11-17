#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <cmath>

using namespace std;

const double eps = 1e-8;

double n, p1, v1, p2, v2;

bool check(double mid) {
    double x1 = mid * v1, x2 = mid * v2;
    double len_l = p1, len_r = n - p2;
    double t1 = p1 + max((x1 - len_l) / 2, x1 - 2 * len_l);
    double t2 = p2 - max((x2 - len_r) / 2, x2 - 2 * len_r);

    // 1, 2 都跑不出 左右
    if (len_l > x1 && len_r > x2) return false;

    // 1 跑不完 左边
    if (x1 < len_l) {
        // 2 跑不出 右边
        if (x2 < 2 * len_r) return false;
        if (t2 <= 0) return true;
        return false;
    }
    // 2 跑不完 右边
    if (x2 < len_r) {
        // 1 跑不出 左边
        if (x1 < 2 * len_l) return false;
        if (t1 >= n) return true;
        return false;
    }

//    cout << mid << " " << x1 << " " << x2 << " ";
//    cout << t1 << " " << t2 << endl;

    return t1 + eps >= t2;
}

void solve() {
    double left = 0, right = 1e18;
    while (left + eps < right) {
        double mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid;
    }

    double ans = left;
    swap(p1, p2);
    swap(v1, v2);

    left = 0, right = 1e18;
    while (left + eps < right) {
        double mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid;
    }
    ans = min(ans, left);

    cout << fixed << setprecision(9);
    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> p1 >> v1 >> p2 >> v2;
        solve();
    }

    return 0;
}