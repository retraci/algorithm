#include <bits/stdc++.h>

using namespace std;

const int N = 1e4;

int n;
int lens[10];
char g[N][N];

void print(int x, int y, int n) {
    if (n == 1) {
        g[x][y] = 'X';
        return;
    }

    print(x, y, n - 1);
    print(x + 2*lens[n - 1], y, n - 1);
    print(x, y + 2*lens[n - 1], n - 1);
    print(x + 2*lens[n - 1], y + 2*lens[n - 1], n - 1);
    print(x + lens[n - 1], y + lens[n - 1], n - 1);
}

void solve() {
    lens[1] = 1;
    for (int i = 2; i < 10; i++) lens[i] = 3 * lens[i - 1];

    int sz = lens[n];
    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            g[i][j] = '0';
        }
    }

    print(0, 0, n);

    for (int i = 0; i < sz; i++) {
        for (int j = 0; j < sz; j++) {
            char ch = g[i][j];
            if (g[i][j] == '0') ch = ' ';
            cout << ch;
        }
        cout << endl;
    }
    puts("-");
}

int main() {
    freopen("../in.txt", "r", stdin);

    while (cin >> n && n >= 1) {
        solve();
    }

    return 0;
}