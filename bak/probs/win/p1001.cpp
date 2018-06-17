#include <iostream>
#include <cstring>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int n, maxcash=0, maxtotal=0;
    char maxer[30];
    cin >> n;
    for (int i=0; i<n; i++) {
        char name[30];
        int qm, py, lw;
        char gb, xb;
        // 姓名，期末平均成绩，班级评议成绩，是否是学生干部，是否是西部省份学生，以及发表的论文数
        cin >> name >> qm >> py >> gb >> xb >> lw;
        int cash = 0;
        if (py>80&&gb=='Y') cash+=850;
        if (qm>80) {
            if (lw>=1) cash+=8000;
            if (qm>85) {
                if (py>80) cash+=4000;
                if (xb=='Y') cash+=1000;
                if (qm>90) cash+=2000; 
            }
        }
        maxtotal += cash;
        if (cash>maxcash) {
            maxcash = cash;
            strcpy(maxer, name); // New usage
        }
    }
    cout << maxer << endl << maxcash << endl << maxtotal;
    return 0;
}