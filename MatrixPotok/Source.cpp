#include <iostream>
#include <vector>
#include <Windows.h>
#define SIZE 2
using namespace std;
int A[SIZE][SIZE] = { {1, 2}, {3, 4} };
int B[SIZE][SIZE] = { {5, 6}, {7, 8} };
vector<int> tempA;
vector<int> tempB;
int res[SIZE][SIZE];
DWORD WINAPI func1(void* data) 
{
    int* mas = (int*)data;
    int i = mas[0], j = mas[1];
    tempA.push_back(A[i][0] * B[0][j]);
    return 0;
}
DWORD WINAPI func2(void* data) 
{
    int* mas = (int*)data;
    int i = mas[0], j = mas[1];
    tempB.push_back(A[i][1] * B[1][j]);
    return 0;
}
DWORD WINAPI func3(void* data) 
{
    int* mas = (int*)data;
    int i = mas[0], j = mas[1];
    res[i][j] = tempA[tempA.size() - 1] + tempB[tempB.size() - 1];
    return 0;
}
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));
    HANDLE thread[SIZE];
    HANDLE thread2[SIZE];
    HANDLE thread3[SIZE];
    DWORD thrId[SIZE];
    DWORD thrId2[SIZE];
    DWORD thrId3[SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) 
        {
            int mas[2] = { i, j };
            thread[i] = CreateThread(NULL, 0, &func1, mas, 0, &thrId[i]);
            Sleep(1);
            thread2[i] = CreateThread(NULL, 0, &func2, mas, 0, &thrId2[i]);
            Sleep(1);
            thread3[i] = CreateThread(NULL, 0, &func3, mas, 0, &thrId3[i]);
            Sleep(1);
        }
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            cout << res[i][j] << " | ";
        cout << endl;
    }
}