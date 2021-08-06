#include <iostream>
#include <array>


// tested x64, c++17

using namespace std;

void greedy_1()
{
    // �Ž����� �ּ� ���� ���ϱ�
    int change = 1260;
    int count = 0;
    array<int, 4> coins = { 500, 100, 50, 10 };

    for (int coin : coins) {
        count += change / coin;
        change %= coin;
    }

    cout << "coin count: " << count << endl;
}


int main()
{
    greedy_1();

    return 0;
}
