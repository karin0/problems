#include <cstdio>
#include <cstring>

using namespace std;

struct bi {
    int nums[50];
};

bi make(char* n) {
    bi ans;
	memset(ans.nums, 0, sizeof(ans.nums)); // forgetten
    int numlen=strlen(n);

	int m=1, c=1;
	for (int i=numlen-1; i>=0; i--) {
		ans.nums[c] += m*(n[i]-'0');
		if (m==1000) {
			m=1;
			c++;
			continue;
		}
		m *= 10;
	}
	ans.nums[0]=c; // forgetten
	return ans;
}

void show(bi a) {
	for (int i=a.nums[0]; i>0; i--) {
		printf("%d", a.nums[i]);
	}
}

int main(){
    char n[10];
    scanf("%s", n);
    bi ans = make(n);
	show(ans);
    return 0;
}