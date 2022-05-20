#include <iostream>
#include <cmath>

using namespace std;

int main() {
    string A, B;
    cin >> A >> B;
    int m = A.length()+1;
    int n = B.length()+1;
    int k = 1;
    cin >> k;
    int** arr = new int*[m];
    for (int i = 0; i < m; i++) {
        arr[i] = new int[2];
    }

    for (int i = 0; i < m; i++){
        arr[i][0] = i * k;
    }

    for (int i = 1; i < n; i++)
    {
        arr[0][1] = i * k;
        for (int j = 1; j < m; j++)
        {
            arr[j][1] = min(min(k + arr[j - 1][1], k + arr[j][0]), arr[j - 1][0] + abs((int(A[j-1]) - int(B[i-1]))));
        }

        for (int i = 0; i < m; i++)
        {
            arr[i][0] = arr[i][1];
        }
    }

    cout << arr[m - 1][1]<<endl;

    return 0;
}