// 四平方和

#include <bits/stdc++.h>

using namespace std;

int n;

void solve() {
    for (int a = 0; a < 5000; a++) {
        int lefa = n - a * a;
        if (lefa < 0) break;
        for (int b = a; b < 5000; b++) {
            int lefb = lefa - b * b;
            if (lefb < 0) break;
            for (int c = b; c < 5000; c++) {
                int lefc = lefb - c * c;
//                cout << a << " " << b <<  " " << c << " " << lefc << endl;

                if (lefc < 0) break;

                int d = sqrt(lefc);
                if (d < c) break;

                if (d * d == lefc) {
                    printf("%d %d %d %d\n", a, b, c, d);
                    return;
                }
            }
        }
    }
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> n;
    solve();

    return 0;
}