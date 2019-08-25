#include <cstdio>
 
char str[10];
int main()
{
	*reinterpret_cast<long long*>(str) = 7528443412579576937ll;
	std::puts(str);
	return 0;
}
