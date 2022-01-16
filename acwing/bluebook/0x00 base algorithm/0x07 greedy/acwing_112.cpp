#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

#define ll long long

struct Node {
    double left, right;
    bool operator < (const Node &n1) const {
        return right < n1.right;
    }
};

const int N = 1010;
const double eps = 1e-8;

int n;
ll d;
ll vx[N], vy[N];
Node va[N];

void solve() {
    for (int i = 0; i < n; i++) {
        ll x = vx[i], y = vy[i];

        if (y > d) {
            cout << -1 << endl;
            return;
        }

        double len = sqrt(d*d - y*y);
        va[i].left = x - len;
        va[i].right = x + len;
    }
    sort(va, va + n);

    int ans = 1;
    double cur = va[0].right;
    for (int i = 1; i < n; i++) {
        if (va[i].left <= cur) continue;
        ans++;
        cur = va[i].right;
    }

    cout << ans << endl;
}

int main() {
    cin >> n >> d;
    for (int i = 0; i < n; i++) scanf("%lld%lld", &vx[i], &vy[i]);
    solve();

    return 0;
}

