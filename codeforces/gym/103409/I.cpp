#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int cnt = 0;
        ll ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == '1') {
                if (cnt > 0) {
                    ans += i + 1;
                    --cnt;
                } else {
                    cnt++;
                }
            } else {
                cnt++;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}