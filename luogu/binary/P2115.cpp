// luogu_P2115
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int N;
int M[100010];

double a[100010],suml[100010],sumr[100010],minl[100010],minr[100010];

bool check(double k) {
	memset(minl,0x7fffffff,sizeof(minl));
	memset(minr,0x7fffffff,sizeof(minr));

	for(int i=1; i<=N; i++) a[i] = M[i]-k;

	for(int i=1; i<=N; i++) suml[i] = suml[i-1]+a[i];
	for(int i=N; i>=1; i--) sumr[i] = sumr[i+1]+a[i];

	for(int i=1; i<=N; i++) minl[i] = minl[i-1]<suml[i]?minl[i-1]:suml[i];
	for(int i=N; i>=1; i--) minr[i] = minr[i+1]<sumr[i]?minr[i+1]:sumr[i];

	for(int i=1; i<=N-2; i++) {
		if(minl[i]+minr[i+2]<=0) return true;
	}
	return false;
}

int main() {
	cin >> N;
	for(int i=1; i<=N; i++) {
		cin >> M[i];
	}

	double l = 0,r = 1e4;
	double mid;
	while(r-l > 1e-5) {
		mid = (l+r)/2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	printf("%.3lf",mid);

	return 0;
}
