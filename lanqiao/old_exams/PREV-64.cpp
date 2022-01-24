// 试题 历届试题 成绩分析

#include <bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10;

int n;
int vv[N];

void solve() {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += vv[i];

    cout << *max_element(vv, vv + n) << endl;
    cout << *min_element(vv, vv + n) << endl;
    printf("%.2lf\n", sum / n);
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> vv[i];
    solve();

    return 0;
}