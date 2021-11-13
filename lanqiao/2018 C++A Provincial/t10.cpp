// 付账问题

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 5e5 + 10;

int n, S;
double va[N];
double bs[N];

void solve() {
    double avg = 1.0 * S / n;

    sort(va, va + n);
    double cur = avg;
    for (int i = 0; i < n; i++) {
        if (va[i] < cur) {
            bs[i] = va[i];

            double lef = cur - va[i];
            cur += lef / (n - i - 1);
        } else {
            bs[i] = cur;
        }
    }

    double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (bs[i] - avg) * (bs[i] - avg);
    }
    ans /= n;
    ans = sqrt(ans);

    printf("%.4lf\n", ans);
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> S;
    for (int i = 0; i < n; i++) scanf("%lf", &va[i]);
    solve();

    return 0;
}