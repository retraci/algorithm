#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

string str;

void solve() {
    if (str.size() <= 0 || !(str[0] >= 'a' && str[0] <= 'z' || str[0] >= 'A' && str[0] <= 'Z')) {
        puts("Wrong");
        return;
    }

    int flag = 0;
    for (int i = 1; i < str.size(); i++) {
        if (!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= '0' && str[i] <= '9')) {
            flag = 0;
            break;
        }
        if (str[i] >= '0' && str[i] <= '9') flag = 1;
    }

    if (flag) puts("Accept");
    else puts("Wrong");
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) {
        cin >> str;
        solve();
    }

    return 0;
}