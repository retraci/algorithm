#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

string str;

void solve() {
    int cur = 0;
    for (char ch : str) {
        if (cur == 0 && ch == 'h') cur++;
        else if (cur == 1 && ch == 'e') cur++;
        else if (cur == 2 && ch == 'l') cur++;
        else if (cur == 3 && ch == 'l') cur++;
        else if (cur == 4 && ch == 'o') cur++;
    }

    cout << (cur == 5 ? "YES" : "NO") << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> str;
    solve();

    return 0;
}