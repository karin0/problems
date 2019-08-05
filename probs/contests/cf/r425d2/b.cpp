// WA..
#include <cstdio>
#include <cstring>
const int MAXS = 100020;

bool good[500];
char pattern[MAXS], query[MAXS], good_chars[300];
int main() {
    int q, i, j, res, star_pos, query_len, pattern_len; // 0 - success, 1 - fail, 2 - Meet *
    scanf("%s%s%d", good_chars, pattern, &q);
    for (i = 0; good_chars[i]; ++i)
        good[good_chars[i] - 'a'] = true;
    while (q--) {
        scanf("%s", query);
        for (i = 0, res = 0; ; ++i) {
            if (!pattern[i]) {
                if (query[i])
                    res = 1;
                break;
            }
            if (!query[i]) {
                if (pattern[i] != '*' || pattern[i + 1])
                    res = 1;
                break;
            }
            if (pattern[i] == '*') {
                res = 2;
                star_pos = i;
                break;
            }
            if (pattern[i] == '?') {
                if (!good[query[i] - 'a']) {
                    res = 1;
                    break;
                }
            } else if (pattern[i] != query[i]) {
                res = 1;
                break;
            }
        }
        if (res == 2) {
            query_len = strlen(query);
            pattern_len = strlen(pattern);
            // aba*hhh
            // abapppphhh
            // 0123456789
            // s = 3
            // i = 10 - 7 + 3 + 1
            i = query_len - pattern_len + star_pos + 1;
            if (i < 0)
                res = 1; // ****
            else
                for (j = star_pos + 1; query[i] && pattern[j]; ++i, ++j) {
                    if (pattern[j] == '?') {
                        if (!good[query[i] - 'a']) {
                            res = 1;
                            break;
                        }
                    } else if (pattern[j] != query[i]) {
                        res = 1;
                        break;
                    }
                }
            if (res == 2) {
                for (i = star_pos; i <= query_len - pattern_len + star_pos; ++i)
                    if (good[query[i] - 'a']) {
                        res = 1;
                        break;
                    }
            }
        }
        if (res == 1) {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
    }
    return 0;
}
