#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 1010;

typedef pair<double, double> PDD;

int n, m;
double x1, y1, x2, y2;
double xs[N], ys[N];
int h, K;

double dist(double a1, double b1, double a2, double b2) {
    return (a1 - a2) * (a1 - a2) + (b1 - b2) * (b1 - b2);
}

bool cmp(PDD &a, PDD &b) {
    return dist(x1, y1, a.first, a.second) < dist(x1, y1, b.first, b.second);
}

void solve() {
    double len = dist(x1, y1, x2, y2);

    vector<PDD> va;
    for (int i = 0; i < n; i++) {
        if (i == h) continue;

        double x, y;
        if (x2 == x1) {
            if (xs[i] == xs[h]) continue;
            double k2 = (ys[h] - ys[i]) / (xs[h] - xs[i]);
            double b2 = ys[h] - k2 * xs[h];

            x = xs[i], y = k2 * x + b2;
        } else {
            double k1 = (y2 - y1) / (x2 - x1);
            double b1 = y2 - k1 * x2;

            if (xs[i] == xs[h]) {
                x = xs[i], y = k1 * x + b1;
            } else {
                double k2 = (ys[h] - ys[i]) / (xs[h] - xs[i]);
                double b2 = ys[h] - k2 * xs[h];

                x = (b2 - b1) / (k1 - k2), y = k1 * x + b1;
            }
        }

//        cout << x << " " << y << endl;

        double d1 = dist(x1, y1, x, y), d2 = dist(x2, y2, x, y);
        if (d1 > len || d2 > len) continue;
        va.push_back({x, y});
    }

    sort(va.begin(), va.end(), cmp);
//    for (auto &vk : va) cout << vk.first << " " << vk.second << endl;

    if (va.size() < K) cout << -1 << endl;
    else cout << va[K - 1].first << " " << va[K - 1].second << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    scanf("%d%d", &n, &m);
    scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
    for (int i = 0; i < n; i++) {
        scanf("%lf%lf", &xs[i], &ys[i]);
    }
    while (m--) {
        scanf("%d%d", &h, &K);
        h--;
        solve();
    }

    return 0;
}