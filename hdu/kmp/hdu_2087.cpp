// HDU 2087 ¼ô»¨²¼Ìõ
// KMP
#include <iostream>
#include <string>
using namespace std;

const int maxn = 1010;
string a,b;
int lena,lenb,nxt[maxn];

void get_next() {
	nxt[0] = -1;
	int i=0,j=-1;
	while(i<lenb) {
		if(j==-1 || b[i]==b[j]) nxt[++i] = ++j;
		else j = nxt[j];
	}
}

int KMP() {
	lena = a.length();
	lenb = b.length();
	get_next();
	int i=0,j=0,ans=0;
	while(i<lena) {
		if(j==-1 || a[i]==b[j]) i++,j++;
		else j = nxt[j];

		if(j==lenb) ans++,j=0;
	}

	return ans;
}

int main() {
	while(cin>>a && a[0]!='#') {
		cin >> b;
		cout << KMP() << endl;
	}
	return 0;
}


