// 分巧克力

#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n, K;
int vh[N], vw[N];

bool check(int mid) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int hc = vh[i] / mid, wc = vw[i] / mid;
        cnt += hc * wc;
    }
    return cnt >= K;
}

void solve() {
    int left = 0, right = 100000;
    while (left < right) {
        int mid = left + right + 1 >> 1;
        if (check(mid)) left = mid;
        else right = mid - 1;
    }

    cout << left << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n >> K;
    for (int i = 0; i < n; i++) scanf("%d%d", &vh[i], &vw[i]);
    solve();

    return 0;
}