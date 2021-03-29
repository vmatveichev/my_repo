#include <iostream>
using namespace std;
int main()
{
    int i = 1;
    int a = ++i + i++;
    cout << "a = " << a << endl;
}
