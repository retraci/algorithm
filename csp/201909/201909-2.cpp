// 201909-2
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int maxn = 1010;

int mark[maxn];
int cnt;
int sum;

int main() {
	int n, m;
	vector<int> a;

	cin >> n;
	for(int i = 0; i < n; i++) {
		scanf("%d", &m);

		int temp;
		a.clear();
		while(m--) {
			scanf("%d", &temp);
			a.push_back(temp);
		}

		for(int j = 1; j < a.size(); j++) {
			if(a[j] > 0) {
				if(a[j] != a[0]) {
					mark[i] = 1;
					a[0] = a[j];
				}
			} else if(a[j] <= 0) {
				a[0] += a[j];
			}
		}
		//cout << a[0] << endl;
		sum += a[0];
	}

	int x = 0;
	for(int i = 0; i < n; i++) {
		cnt += mark[i];
		if(mark[i] && mark[(i+1)%n] && mark[(i+2)%n]) x++;
	}

	printf("%d %d %d\n", sum, cnt, x);

	return 0;
}
