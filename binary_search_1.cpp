#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>


// tested x64, c++17

using namespace std;

int SequantialSearch(string& target, vector<string>& data)
{
    int index = -1;
    for (string& d : data) {
        index += 1;

        if (d == target)
            return index;
    }
    return -1;
}

void TestSequantialSearch()
{
    vector<string> data = {
        "가", "나", "다", "라", "마", "바"
    };

    for (string& d : data)
        cout << d << ' ';

    cout << endl <<"찾을 문자열 입력: ";

    string target;
    cin >> target;

    cout << SequantialSearch(target, data) << endl;
}


int BinarySearch1(vector<int>& data, int target, int begin, int end)
{
    if (begin > end)
        return -1;

    int mid = (begin + end) / 2;

    if (data[mid] == target)
        return mid;
    else if (data[mid] > target)
        return BinarySearch1(data, target, begin, mid - 1);
    else
        return BinarySearch1(data, target, mid + 1, end);
}

int BinarySearch2(vector<int>& data, int target, int begin, int end)
{
    while (begin <= end) {
        int mid = (begin + end) / 2;

        if (data[mid] == target)
            return mid;
        else if (data[mid] > target)
            end = mid - 1;
        else
            begin = mid + 1;
    }
    return -1;
}

void TestBinarySearch()
{
    vector<int> data = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };

    for (int num : data)
        cout << num << ' ';
    cout << endl << "숫자 입력: ";

    int target;
    cin >> target;

    cout << BinarySearch1(data, target, 0, (int)data.size() - 1) << endl;
    cout << BinarySearch2(data, target, 0, (int)data.size() - 1) << endl;
}

void QuizBinarySearch()
{
    // find order parts
    random_device rd;
    default_random_engine eng(rd());
    uniform_int_distribution<int> dist(1, 200);

    vector<int> all_parts;
    for (int i = 0; i < 100; ++i)
        all_parts.push_back(dist(eng));

    sort(all_parts.begin(), all_parts.end());

    for (int part : all_parts)
        cout << part << " ";

    vector<int> order_parts;
    for (int i = 0; i < 10; ++i)
        order_parts.push_back(dist(eng));

    for (int order : order_parts) {
        int result = BinarySearch2(all_parts, order, 0, (int)all_parts.size() - 1);
        cout << endl << "order part " << order << ": " << (result != -1 ? "yes" : "no");
    }
}


int main()
{
    TestSequantialSearch();
    TestBinarySearch();
    QuizBinarySearch();

    return 0;
}

