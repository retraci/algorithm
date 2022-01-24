// 产生后台数据
/*

*/

#include <bits/stdc++.h>

using namespace std;

const int offset = 50010;
const int maxn = 50010;

int n, m, K;
int a[maxn];

void printArray() {
	for (int i = 1; i <= n; ++i) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int maxbit(int l, int r) {
	int d = 1;
	int p = 10;
	for(int i = l; i <= r; ++i) {
		while(a[i] >= p) {
			p *= 10;
			++d;
		}
	}
	return d;
}

void radixsort1(int l, int r) {
	int d = maxbit(l, r);
	int tmp[n];
	int count[10];
	int i, j, k;
	int radix = 1;
	for(i = 1; i <= d; i++) {
		for(j = 0; j < 10; j++)
			count[j] = 0;
		for(j = l; j <= r; j++) {
			k = (a[j] / radix) % 10;
			count[k]++;
		}
		for(j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j];

		for(j = r; j >= l; j--) {
			k = (a[j] / radix) % 10;
			tmp[count[k] - 1] = a[j];
			count[k]--;
		}
		int q;
		for(q = 0,j = l; j <= r; j++,q++)
			a[j] = tmp[q];
		radix = radix * 10;
	}
}

void radixsort2(int l, int r) {
	int d = maxbit(l, r);
	int tmp[n];
	int count[10];
	int i, j, k;
	int radix = 1;
	for(i = 1; i <= d; i++) {
		for(j = 0; j < 10; j++)
			count[j] = 0;
		for(j = l; j <= r; j++) {
			k = (a[j] / radix) % 10;
			count[k]++;
		}
		for(j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j];

		for(j = r; j >= l; j--) {
			k = (a[j] / radix) % 10;
			tmp[count[k] - 1] = a[j];
			count[k]--;
		}
		int q;
		for(q = 0,j = r; j >= l; j--,q++)
			a[j] = tmp[q];
		radix = radix * 10;
	}
}

void solve() {
	int L, R;
	string op;
	while (m--) {
		scanf("%d%d", &L, &R);
		cin >> op;

		if (op == "down") {
			radixsort2(L, R);
		} else {
			radixsort1(L, R);
//			printArray();
		}
	}

	cout << a[K] << endl;
}

int main() {
	cin >> n >> m >> K;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	solve();

	return 0;
}
