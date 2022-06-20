#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

const int N = 3e5 + 10;

int n;
char c;
string str;
vector<int> va[N];
vector<int> vb;
int vc[N];
int vis[N];

void init() {
    for (int i = 4; i <= 3e5; i++) {
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) va[i].push_back(j), va[i].push_back(i / j);
        }
    }
}

void print() {
    for (int j = 1; j <= n; j++) cout << vc[j] << " ";
    cout << endl;
}

void solve() {
    vb.clear();
    for (int i = 0; i < n; i++) vc[i + 1] = 0, vis[i + 1] = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] != c) {
            vb.push_back(i + 1);
            vis[i + 1] = 1;
        }
    }
    if (vb.empty()) {
        cout << 0 << endl;
        return;
    }

    for (int k = 2; k <= n; k++) vc[k] = 0;
    for (int x : vb) {
        for (int y : va[x]) {
            vc[y]++;
        }
    }

    for (int k = 2; k <= n; k++) {
//        print();
        if (!vis[k] && vc[k] == 0) {
            cout << 1 << endl;
            cout << k << endl;
            return;
        }
        for (int y : va[k]) {
            vc[y]--;
        }
    }

    cout << 2 << endl;
    cout << n - 1 << " " << n << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    init();

    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> c;
        cin >> str;
        solve();
    }

    return 0;
}