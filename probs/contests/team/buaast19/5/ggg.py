with open('eee.cpp', 'w') as fp:
    for i in range(10000):
        fp.write('#include <cstdio>\n')

    fp.write('''
    int main() {
        puts("QAQ")
    }''')