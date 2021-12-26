#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

#define ll long long

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};

const int N = 2e5 + 10;
const double eps = 1e-11;

double x;

void solve() {
    double ans = 0;
    double fac = 1;
    for (double k = 0; ; k++) {
        fac *= k + 1;
        double up = x * k + (x - 1);
        double down = fac * pow(x, k + 1);
        double cur = (k + 1) * up / down;
        if (cur < eps) break;
        ans += cur;
    }

    cout << fixed << setprecision(9);
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> x;
    solve();

    return 0;
}