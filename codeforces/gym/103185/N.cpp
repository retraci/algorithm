#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;

    int rem = stoi(s.substr(1, s.size() - 4)) * 100 + stoi(s.substr(s.size() - 2, 2));
    while (n--) {
        cin >> s;
        int tmp = stoi(s.substr(1, s.size() - 4)) * 100 + stoi(s.substr(s.size() - 2, 2));
        rem += tmp;
        if (rem % 100 != 0) ans++;
    }
    cout << ans << "\n";
    return 0;
}