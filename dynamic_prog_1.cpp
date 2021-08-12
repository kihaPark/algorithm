#include <iostream>
#include <array>


// tested x64, c++17

using namespace std;

int Fibonacci1(int x)
{
    // fibonacci numbers: 1, 1, 2, 3, 5, 8, 13 ...
    if (x == 1 || x == 2)
        return 1;

    return Fibonacci1(x - 1) + Fibonacci1(x - 2);
}

array<int, 50> mem = { 0, };

int Fibonacci2(int pos)
{
    // memoization, top-down
    cout << "f(" << pos << ") " << endl;

    if (pos == 1 || pos == 2)
        return 1;

    if (mem[pos] != 0) {
        cout << mem[pos] << endl;
        return mem[pos];
    }

    mem[pos] = Fibonacci2(pos - 1) + Fibonacci2(pos - 2);
    return mem[pos];
}

int Fibonacci3(int pos)
{
    // for loop, bottom-up
    mem[1] = 1;
    mem[2] = 1;

    for (int i = 3; i <= pos; ++i)
        mem[i] = mem[i - 1] + mem[i - 2];

    return mem[pos];
}

void TestFibonacci()
{
    cout << Fibonacci1(4) << endl;

    mem.fill(0);
    cout << Fibonacci2(10) << endl;

    mem.fill(0);
    cout << Fibonacci3(10) << endl;
}


void QuizBottomUP()
{
    cout << "숫자 입력: ";
    int n = 0;
    cin >> n;

    mem.fill(0);
    mem[1] = 1;
    mem[2] = 3;

    for (int i = 3; i <= n; ++i)
        mem[i] = (mem[i - 1] + 2 * mem[i - 2]) % 796796;

    for (int i = 1; i <= n; ++i)
        cout << mem[i] << ' ';
}


int main()
{
    TestFibonacci();
    QuizBottomUP();

    return 0;
}

