// 试题 历届试题 成绩统计

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

int n;
int vv[N];

void solve() {
    double a = 0, b = 0;

    for (int i = 0; i < n; i++) {
        if (vv[i] >= 85) a++;
        if (vv[i] >= 60) b++;
    }

    a = a / n * 100; b = b / n * 100;

    printf("%.0lf", b); cout << "%" << endl;
    printf("%.0lf", a); cout << "%" << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> vv[i];
    solve();

    return 0;
}