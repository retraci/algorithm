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
#include <unordered_set>
#include <unordered_map>
#include <bitset>
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;

void solve() {
}

void work1(vector<int> a) {
    int ans = 0;
    int lst = 100;
    for (int x: a) {
        ans += abs(lst - x);
        lst = x;
    }
    cout << ans << "\n\n";
}

void work2(vector<int> a) {
    int ans = 0;
    int lst = 100;
    while (!a.empty()) {
        int mi = 1e9;
        int id = -1;
        for (int i = 0; i < a.size(); i++) {
            if (abs(lst - a[i]) < mi) {
                mi = abs(lst - a[i]);
                id = i;
            }
        }
        debug(id, a[id], mi);

        ans += mi;
        lst = a[id];
        a.erase(a.begin() + id);
    }
    cout << ans << "\n\n";
}

void work3(vector<int> a) {
    int ans = 0;
    int lst = 100;
    sort(a.begin(), a.end());
    int s = lower_bound(a.begin(), a.end(), lst) - a.begin();
    for (int i = s; i < a.size(); i++) {
        ans += abs(a[i] - lst);
        lst = a[i];
        cout << a[i] << " ";
    }
    for (int i = s - 1; i >= 0; i--) {
        ans += abs(a[i] - lst);
        lst = a[i];
        cout << a[i] << " ";
    }
    cout << "\n";
    cout << ans << "\n\n";
}

void prework() {
//    vector<int> a = {55, 58, 39, 18, 90, 160, 150, 38, 184};
//    cout << a.size() << "\n";
//
//    work1(a);
//    work2(a);
//    work3(a);

cout << 22 * (1.75 * 1.75) << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }

//    Semaphore wait = 1;    // 等待互斥, 当对面方向有人过桥就等待
//    Semaphore mutex1 = 1;  // 东方向互斥信号量
//    Semaphore mutex2 = 1;  // 西方向互斥信号量
//
//    int count1 = 0;       // 东方向要过桥人数, 要过桥+1, 已经过桥-1
//    int count2 = 0;       // 西方向要过桥人数, 要过桥+1, 已经过桥-1
//
//    to_east {
//            P(mutex1);
//            if (count1 == 0) P(wait);
//            count1++;
//            V(mutex1);
//
//            东方向人过桥();
//
//            P(mutex1);
//            count1--;
//            if (count1 == 0) V(wait);
//            V(mutex1);
//    }
//
//    to_west {
//            P(mutex2);
//            if (count2 == 0) P(wait);
//            count2++;
//            V(mutex2);
//
//            西方向人过桥();
//
//            P(mutex2);
//            count2--;
//            if (count2 == 0) V(wait);
//            V(mutex2);
//    }

    return 0;
}