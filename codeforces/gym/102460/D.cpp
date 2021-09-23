#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const string s1 = "bubble", s2 = "tapioka";

string ss[3];
int vis[3];

void solve() {
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
        if (ss[i] == s1 || ss[i] == s2) vis[i] = 1, cnt++;
    }

    if (cnt == 3) {
        cout << "nothing" << endl;
    } else {
        for (int i = 0; i < 3; i++) {
            if (!vis[i]) cout << ss[i] << " ";
        }
        cout << endl;
    }
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false);
    for (int i = 0; i < 3; i++) cin >> ss[i];
    solve();

    return 0;
}