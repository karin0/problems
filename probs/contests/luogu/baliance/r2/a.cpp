#include <cstdio>

const int MAXS = 30007;

struct Seg {
    char ch;
    int lcnt;
    bool star;
} ss[MAXS], tt[MAXS];
char s[MAXS], t[MAXS], gch; // rep[MAXS];
int sscnt, ttcnt, glcnt;
bool gstar;
int main() {
    static int tc, kas, i, j;
    scanf("%d", &tc);
    for (kas = 0; kas < tc; ++kas) {
        scanf("%s%s", s, t);
        sscnt = 0, ttcnt = 0; // *** init
        gch = s[0], glcnt = 1, gstar = false;
        for (i = 1; s[i]; ++i) {
            if (s[i] == gch)
                ++glcnt;
            else if (s[i] == '*')
                gstar = true;
            else {
                ss[++sscnt].ch = gch;
                ss[sscnt].lcnt = glcnt;
                ss[sscnt].star = gstar;
                gch = s[i];
                glcnt = 1;
                gstar = false;
            }
        }
        ss[++sscnt].ch = gch;
        ss[sscnt].lcnt = glcnt;
        ss[sscnt].star = gstar;
        gch = t[0], glcnt = 1;
        for (j = 1; t[j]; ++j) {
            if (t[j] == gch)
                ++glcnt;
            else {
                tt[++ttcnt].ch = gch;
                tt[ttcnt].lcnt = glcnt;
                gch = t[j];
                glcnt = 1;
            }
        }
        tt[++ttcnt].ch = gch;
        tt[ttcnt].lcnt = glcnt;
        for (i = j = 0; i <= sscnt && j <= ttcnt; ) {
            if (ss[i].ch == tt[j].ch && (
                    (ss[i].lcnt < tt[j].lcnt && ss[i].star) ||
                    (ss[i].lcnt == tt[j].lcnt))
                    )
                ++i, ++j;
            else {
                break;
            }
        }
        if (i <= sscnt || j <= ttcnt)
            puts("No");
        else
            puts("Yes");
    }

    return 0;
}
