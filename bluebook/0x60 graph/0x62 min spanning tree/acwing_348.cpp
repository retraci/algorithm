#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <iomanip>
#include <queue>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotAssignable"
using namespace std;

struct Point {
    double x, y, z;
};

const int N = 1010;
const double eps = 1e-5;

int n;
Point ps[N];
double dist[N];
int vis[N];

double get_dist(int id1, int id2) {
    auto &[x1, y1, z1] = ps[id1];
    auto &[x2, y2, z2] = ps[id2];
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

bool check(double mid) {
    double res = 0;

    for (int i = 1; i <= n; i++) dist[i] = 1e18, vis[i] = 0;
    dist[1] = 0;
    for (int i = 1; i <= n; i++) {
        int u = 1;
        double w = 1e18;
        for (int i = 1; i <= n; i++) {
            if (!vis[i] && w > dist[i]) {
                w = dist[i];
                u = i;
            }
        }
        vis[u] = 1;
        res += w;

        for (int v = 1; v <= n; v++) {
            double d = get_dist(u, v);
            double h = fabs(ps[u].z - ps[v].z);
            if (!vis[v] && dist[v] > h - mid * d) {
                dist[v] = h - mid * d;
            }
        }
    }

    return res < 0;
}

void solve() {
    double left = 0, right = 10000000;
    while (left + eps < right) {
        double mid = (left + right) / 2;
        if (check(mid)) right = mid;
        else left = mid;
    }

    cout << fixed << setprecision(3);
    cout << left << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) {
            double x, y, z;
            cin >> x >> y >> z;
            ps[i] = {x, y, z};
        }
        solve();
    }

    return 0;
}

#pragma clang diagnostic pop