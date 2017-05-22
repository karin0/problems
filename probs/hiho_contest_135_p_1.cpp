/*
hihoCoder Contest 135 1
WA

*/
#include <cstdio>
using namespace std;

char ways[][15] = {
"816357492",
"618753294",
"492357816",
"294753618",
"672159834",
"834159672",
"276951438",
"438951276"
};

char s[20];
char c;
int ans=-1;
int main() {
    for (int i=0; i<9; i++) {
        scanf("%s", &c);
        s[i]=c;
    }
    for (int i=0; i<8; i++) {
        for (int j=0; j<9; j++) {
            if (s[j]!='0' && s[j]!=ways[i][j]) goto _fail;
        }
        if (ans==-1) {
            ans=i;
        } else {
            printf("Too many\n");
            return 0;
        }
        _fail:;
    }
    printf("%c %c %c\n%c %c %c\n%c %c %c\n", 
            ways[ans][0], ways[ans][1], ways[ans][2],
            ways[ans][3], ways[ans][4], ways[ans][5],
            ways[ans][6], ways[ans][7], ways[ans][8]
            );
    return 0;
}
