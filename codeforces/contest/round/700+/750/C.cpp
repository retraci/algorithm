#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n;
string s;

void solve() {
    int ans = INF;
    for (int i = 0; i < 26; i++) {
        int ch = i + 'a';
        int left = 0, right = n - 1, cnt = 0, flag = 0;
        while (left < right) {
            // 相等
            if (s[left] == s[right]) {
                left++, right--;
                continue;
            }
            // 不相等就删一个
            if (s[left] != ch && s[right] != ch) {
                flag = 1;
                break;
            }
            if (s[left] == ch) {
                cnt++, left++;
            } else if (s[right] == ch) {
                cnt++, right--;
            }
        }
        if (!flag) ans = min(ans, cnt);
    }

    cout << (ans == INF ? -1 : ans) << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> n >> s;
        solve();
    }

    return 0;
}