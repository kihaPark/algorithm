#include <iostream>
#include <vector>
#include <array>


// tested x64, c++17

using namespace std;

bool IsPrimeNumber(int num)
{
    for (int i = 2; i <= (int)sqrt(num); ++i) {
        if (num % i == 0)
            return false;
    }
    return true;
}

void TestPrimeNumber()
{
    const int MAX_CNT = 5;
    array<int, MAX_CNT> nums = { 4, 7, 10, 11, 13 };
    for (int num : nums)
        cout << num << (IsPrimeNumber(num) ? " : prime num" : " : X") << endl;
}


void TestEratos(int num = 10)
{
    // 에라토스테네스의 체
    // 2 ~ num, find prime number
    if (num <= 1)
        return;

    vector<bool> primeNums(num + 1, true); // except 0, 1

    for (int i = 2; i * i <= num; ++i) {
        if (!primeNums[i])
            continue;

        for (int j = i * i; j <= num; j += i)
            primeNums[j] = false;
    }

    cout << "prime number: ";
    for (int i = 2; i <= num; i++) {
        if (primeNums[i])
            cout << i << ' ';
    }
    cout << endl;
}


void TestPartialSum()
{
    // two pointers algorithm
    const int FIND_FIVE = 5;
    const int MAX_CNT = 5;
    array<int, MAX_CNT> nums = { 1, 2, 3, 2, 5 };

    int begin = 0, end = 0;
    int found = 0, partialSum = 0;

    while (true) {
        if (partialSum == FIND_FIVE)
            found += 1;

        if (partialSum >= FIND_FIVE)
            partialSum -= nums[begin++];
        else if (end == MAX_CNT)
            break;
        else
            partialSum += nums[end++];
    }

    /*for (; begin < MAX_CNT; ++begin) {
        while (partialSum < FIND_FIVE && end < MAX_CNT) {
            partialSum += nums[end];
            end += 1;
        }

        if (partialSum == FIND_FIVE)
            found += 1;

        partialSum -= nums[begin];
    }*/

    cout << "partial sum count: " << found << endl;
}


void TestPrefixSum()
{
    const int MAX_CNT = 5;
    array<int, MAX_CNT> nums = { 10, 20, 30, 40, 50 };
    array<int, MAX_CNT> acc = { 0, };

    acc[0] = nums[0];
    for (int i = 1; i < MAX_CNT; ++i)
        acc[i] = acc[i - 1] + nums[i];

    for (int num : acc)
        cout << num << ' ';
    cout << endl;

    // 0 ~ 2 index prefix sum
    cout << acc[2] << endl;

    // 2 ~ 3 index prefix sum
    cout << acc[3] - acc[2 - 1] << endl;
}


int main()
{
    TestPrimeNumber();
    TestEratos();
    TestPartialSum();
    TestPrefixSum();

    return 0;
}

