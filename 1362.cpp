#include <iostream>
#include <string>

using namespace std;

int sizes[40][2];
int quantity[10];
bool foundSolution;
int totalOrders;

void calculate(int orderNumber)
{
    if (orderNumber == totalOrders + 1)
    {
        foundSolution = true;
        return;
    }
    if (foundSolution)
        return;

    if (quantity[sizes[orderNumber][0]])
    {
        --quantity[sizes[orderNumber][0]];
        calculate(orderNumber + 1);
        ++quantity[sizes[orderNumber][0]];
    }
    if (quantity[sizes[orderNumber][1]])
    {
        --quantity[sizes[orderNumber][1]];
        calculate(orderNumber + 1);
        ++quantity[sizes[orderNumber][1]];
    }
}

int convertToNumber(string size)
{
    if (size == "XS")
        return 1;
    if (size == "S")
        return 2;
    if (size == "M")
        return 3;
    if (size == "L")
        return 4;
    if (size == "XL")
        return 5;
    return 6;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int testCaseCount;
    int totalShirts;
    string size1, size2;

    cin >> testCaseCount;

    while (testCaseCount--)
    {
        cin >> totalShirts >> totalOrders;
        for (int i = 0; i < 10; ++i)
            quantity[i] = totalShirts / 6;

        for (int i = 1; i <= totalOrders; ++i)
        {
            cin >> size1 >> size2;

            sizes[i][0] = convertToNumber(size1);
            sizes[i][1] = convertToNumber(size2);
        }

        foundSolution = false;
        calculate(1);

        if (foundSolution)
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}