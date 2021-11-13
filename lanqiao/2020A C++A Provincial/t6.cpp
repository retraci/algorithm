// 解码

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

string str;

void solve() {
    string ans = "";
    int i = 0;
    while (i < str.size()) {
        char ch = str[i];
        int j = i + 1;
        if (j < str.size() && str[j] >= '0' && str[j] <= '9') {
            int rep = str[j] - '0';
            while (rep--) ans += ch;
            i += 2;
        } else {
            ans += ch;
            i++;
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