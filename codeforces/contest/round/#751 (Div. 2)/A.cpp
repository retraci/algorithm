#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

string s;

void solve() {
    char mi = *min_element(s.begin(), s.end());
    cout << mi << " ";
    int cnt = 0;
    for (char ch : s) {
        if (ch == mi && cnt == 0) {
            cnt++;
            continue;
        }
        cout << ch;
    }
    cout << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> s;
        solve();
    }

    return 0;
}