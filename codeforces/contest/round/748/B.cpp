#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

string num;
vector<int> va;

bool check1(int x) {
    return x == 0 || x == 2 || x == 5 || x == 7;
}

bool check(int n1, int n2) {
    int sum = n1 * 10 + n2;
    return sum == 0 || sum == 25 || sum == 75 || sum == 50;
}

void solve() {
    va.clear();
    for (int i = 0; i < num.size(); i++) {
        if (check1(num[i] - '0')) va.push_back(i);
    }

    int ans = 100;
    for (int i = 0; i < va.size(); i++) {
        for (int j = i + 1; j < va.size(); j++) {
            int id1 = va[i], id2 = va[j];
            int n1 = num[id1] - '0', n2 = num[id2] - '0';

//            cout << id1 << " " << id2 << " " << n1 << " " << n2 << endl;

            if (check(n1, n2)) {
                ans = min(ans, (int) num.size() - id1 - 2);
            }
        }
    }

    cout << ans << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) {
        cin >> num;
        solve();
    }

    return 0;
}