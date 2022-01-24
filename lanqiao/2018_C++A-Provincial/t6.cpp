// 航班时间

#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll calc() {
    int h1, m1, s1, h2, m2, s2, d = 0;
    scanf("%d:%d:%d %d:%d:%d", &h1, &m1, &s1, &h2, &m2, &s2);
    int ch = getchar();
    if (ch != '\n') scanf("(+%d)", &d);

    ll res =  (h2 * 60 * 60 + m2 * 60 + s2)
            - (h1 * 60 * 60 + m1 * 60 + s1)
            + 24 * 60 * 60 * d;

    return res;
}

void solve() {
    int T;
    cin >> T;
    while (T--) {
        ll time = (calc() + calc()) / 2;
        int s = time % 60;
        int m = (time / 60) % 60;
        int h = time / 60 / 60;

        printf("%02d:%02d:%02d\n", h, m, s);
    }
}

int main() {
    freopen("../in.txt", "r", stdin);

    solve();

    return 0;
}