// 202009-2
/*

*/

#include <iostream>
#include <cstdio>

using namespace std;

int n, k, t, x1, y1, x2, y2;
int ans1, ans2;

bool inBound(int x, int y) {
	return x>=x1 && x<=x2 && y>=y1 && y<=y2;
}

int main() {
	cin >> n >> k >> t >> x1 >> y1 >> x2 >> y2;
	
	int x, y;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		int flag = 0;
		for (int j = 0; j < t; j++) {
			scanf("%d%d", &x, &y);
			if (inBound(x, y)) {
				if (!flag) flag = 1;
				if (++cnt >= k) flag = 2;
			} else {
				cnt = 0;
			}
		}
		if (flag == 1) ans1++;
		else if (flag == 2) ans1++, ans2++;
	}
	cout << ans1 << endl << ans2 << endl;
	
	return 0;
}
