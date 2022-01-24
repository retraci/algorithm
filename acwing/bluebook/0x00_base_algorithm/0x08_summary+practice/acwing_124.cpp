#include <bits/stdc++.h>

using namespace std;

int a, b;
string sa, sb;

void solve() {
    sb = "";
    vector<int> numa, numb;
    for (char ch: sa) {
        if (ch >= '0' && ch <= '9') numa.push_back(ch - '0');
        if (ch >= 'A' && ch <= 'Z') numa.push_back(10 + ch - 'A');
        if (ch >= 'a' && ch <= 'z') numa.push_back(36 + ch - 'a');
    }

    reverse(numa.begin(), numa.end());
    while (!numa.empty()) {
        int r = 0;
        for (int i = numa.size() - 1; i >= 0; i--) {
            int cur = r * a + numa[i];
            numa[i] = cur / b;
            r = cur % b;
        }
        while (!numa.empty() && numa.back() == 0) numa.pop_back();
        numb.push_back(r);
    }

    for (int i = numb.size() - 1; i >= 0; i--) {
        int x = numb[i];
        if (x >= 0 && x <= 9) sb.push_back(x + '0');
        if (x >= 10 && x <= 35) sb.push_back(x - 10 + 'A');
        if (x >= 36 && x <= 61) sb.push_back(x - 36 + 'a');
    }

    cout << a << " " << sa << endl;
    cout << b << " " << sb << endl << endl;
}

int main() {
    freopen("../in.txt", "r", stdin);
    std::ios::sync_with_stdio(false);

    int T;
    cin >> T;
    while (T--) {
        cin >> a >> b >> sa;
        solve();
    }

    return 0;
}