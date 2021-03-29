#include <iostream>
using namespace std;

void oldStyle(int f)
{
    if(f <= 9)
    { cout << 22 + f << " march (Orthodox oldstyle)\n"; }
    else if (f > 9)
    { cout << f - 9 << " april (Orthodox oldstyle)\n"; }
}

void newStyle(int f, int year)
{
    if(year >= 1900)
    {
        if(((f - 9) + 13) > 30)
        {
            cout << ((f - 9) + 13) - 30 << " may (Orthodox newstyle)\n";
        }
        else
        {
            cout << ((f - 9) + 13) << " april (Orthodox newstyle)\n";
        }
    }
    else
    { }
}

void ortodox()
{
    int a, b, c, d, e, f, year, M = 15, N = 6;
    char ch;
    do
    {
    system("clear");
    cout << "Enter year: ";
    cin >> year;
    a = year % 19;
    b = year % 4;
    c = year % 7;
    d = ((19 * a) + M) % 30;
    e = ((2 * b) + (4 * c) + (6 * d) + N) % 7;
    f = d + e;
    oldStyle(f);
    newStyle(f, year);
    cout << "Repeat? (y/n): ";
    cin >> ch;
    }
    while(ch != 'n');
}

void catholic()
{
    int a, b, c, d, e, k, p, q, M, N, year;
    char ch;
    do
    {
    system("clear");
    cout << "Enter year: ";
    cin >> year;
    a = year % 19;
    b = year % 4;
    c = year % 7;
    k = year / 100;
    p = (13 + (8 * k)) / 25;
    q = k / 4;
    M = (15 - p + k - q) % 30;
    N = (4 + k - q) % 7;
    d = ((19 * a) + M) % 30;
    e = ((2 * b) + (4 * c) + (6 * d) + N) % 7;
    if(d == 29 && e == 6)
        { cout << 19 << " april (Catholic)\n"; }
    else if((d == 28 && e == 6) && ((11 * M + 11) % 30 < 19))
        { cout << 18 << " april (Catholic)\n"; }
    else
    {
        if((22 + d + e) < 31)
            { cout << 22 + d + e << " march (Catholic)\n"; }
        else if((22 + d + e) > 31)
            { cout << d + e - 9 << " april (Catholic)\n"; }
    }
    cout << "Repeat? (y/n): ";
    cin >> ch;
    }
    while(ch != 'n');
}

int main()
{
    char ch, ans;
    do
    {
        cout << "Ortodox or Catholic? (o/c): ";
        cin >> ch;
        switch(ch)
        {
            case 'o': ortodox(); break;
            case 'c': catholic(); break;
            default: break;
        }
        cout << "Continue typing? (y/n): ";
        cin >> ans;
    }
    while(ans != 'n');
    return 0;
}
