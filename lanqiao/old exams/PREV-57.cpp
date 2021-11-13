// 试题 历届试题 子串分值和

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 1e5 + 10;

string str;
int ne[N][26];

void solve() {
    int n = str.size();

    memset(ne, -1, sizeof ne);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < 26; j++) {
            ne[i][j] = ne[i + 1][j];
        }
        int tmp = str[i] - 'a';
        ne[i][tmp] = i;
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            if (ne[i][j] == -1) continue;
            ans += n - ne[i][j];
        }
    }

    cout << ans << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);

    cin >> str;
    solve();

    return 0;
}