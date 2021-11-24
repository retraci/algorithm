// HDU 2594 Simpsons’Hidden Talents
// KMP
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 1e6+10;
int nxt[MAXN];
string s1,s2,s;

void get_next() {
	int len = s.length();
	nxt[0] = -1;
	int i=0,j=-1;
	while(i<len) {
		if(j!=-1 && s[i]!=s[j]) j = nxt[j];
		else nxt[++i] = ++j;
	}
}

int main() {
	while(cin >> s1 >> s2) {
		s = s1+s2;
		get_next();
		int len = nxt[s.length()];
		if(len==0) cout << 0 << endl;
		else {
			// 有可能整段都是回文 
			int i=0;
			for(i=0; i<len && i<s1.length() && i<s2.length() ; i++) cout << s[i];
			cout << " " << i << endl;
		}
	}

	return 0;
}


