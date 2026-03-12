#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <math.h>
#include <ctime>
#include <iomanip>

using namespace std;


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    time_t timer = time(NULL);
    struct tm* t = gmtime(&timer);
    cout << t->tm_year + 1900 << "-";
    cout << setfill('0') << setw(2) << t->tm_mon + 1 << "-";
    cout << setfill('0') << setw(2) << t->tm_mday << endl;
    return 0;
}