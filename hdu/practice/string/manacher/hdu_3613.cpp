// HDU 3613  Best Reward
// manacher
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1e6+10;
int val[26],t;
char a[MAXN],b[MAXN];
int lena,lenb,p[MAXN],ans;
int pre[MAXN],post[MAXN],sum[MAXN];

void manacher() {
	lena = strlen(a);
	lenb = 2*lena+2;

	for(int i=1; i<=lena; i++) {					// 计算前缀和,i表示长度 
		sum[i] = sum[i-1]+val[a[i-1]-'a'];
	}

	b[0] = '$';
	b[1] = '#';
	for(int i=0; i<lena; i++) {
		b[2*i+2] = a[i];
		b[2*i+3] = '#';
	}
	b[lenb] = '*';

	int id=0,mx=0;
	for(int i=2; i<lenb-1; i++) {
		if(mx>i) p[i] = min(mx-i,p[2*id-i]);
		else p[i] = 1;

		for(; b[i+p[i]]==b[i-p[i]]; p[i]++);

		if(i+p[i]>mx) {
			id = i;
			mx = i+p[i];
		}
		
		// t+1表示第几组做标记，不用 menset重置 
		if(i-p[i]==0) pre[p[i]-1] = t+1;					// p[i]-1 为长度
		if(i+p[i]==lenb) post[p[i]-1] = t+1;				// p[i]-1 为长度
	}

	int temp = 0;
	for(int i=1; i<lena; i++) {								// 当长度相加==lena时满足
		if(pre[i]==t+1) temp += sum[i];
		if(post[lena-i]==t+1) temp += sum[lena]-sum[i];
		ans = temp>ans?temp:ans;
		temp = 0;
	}
}

int main() {
	cin >> t;
	while(t--) {
		for(int i=0; i<26; i++) cin >> val[i];
		cin >> a;
		ans = 0;
		manacher();
		cout << ans << endl;
	}

	return 0;
}
