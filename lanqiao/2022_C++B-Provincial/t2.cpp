#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <bitset>
#include <unordered_map>

using namespace std;

const int month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int ans = 0;
    for (int i = 1; i <= 12; i++) {
        for (int j = 1; j <= month[i]; j++) {
            string m = to_string(i);
            string d = to_string(j);
            if (m.size() == 1) m = "0" + m;
            if (d.size() == 1) d = "0" + d;
            string s = "2022" + m + d;

            int flag = 0;
            for (int k = 2; k < s.size(); k++) {
                if (s[k] - s[k - 1] == 1 && s[k] - s[k - 1] == s[k - 1] - s[k - 2]) flag = 1;
            }
//            if (flag) cout << s << "\n";
            ans += flag;
        }
    }
    cout << ans << "\n";

    return 0;
}
