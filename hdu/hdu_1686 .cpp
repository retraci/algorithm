// HDU 1686 Oulipo
// KMP
#include <iostream>
#include <string>
using namespace std;

const int maxw = 1e4+10;
const int maxt = 1e6+10;
string a,b;
int len1,len2;
int nxt[maxw];

void getnext() {
	nxt[0] = -1;
	int i = 0, j = -1;
	while(i < len2) {
		if(j!=-1 && b[i]!=b[j]) j = nxt[j];
		else nxt[++i] = ++j;
	}
}

int KMP() {
	int i=0,j=0,sum=0;
	while(i < len1) {
		if(j!=-1 && a[i]!=b[j]) j = nxt[j];
		else {
			i++;
			j++;
		}
		if(j == len2)
			sum++;
	}
	return sum;
}

int main() {
	int n;
	cin >> n;
	while(n--) {
		cin>>b>>a;
		len1 = a.length();
		len2 = b.length();
		getnext();
		cout << KMP() << endl;
	}

	return 0;
}
