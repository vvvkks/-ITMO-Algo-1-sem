#include <iostream>
#include <fstream>
using namespace std;
int main() {

    ifstream entrance;
    ofstream output;
    entrance.open("isheap.in");
    output.open("isheap.out");

    int n;
    entrance >> n;
    int mas[n + 1];
    for (int i = 1; i <= n; i++) {
        entrance >> mas[i];
    }
    bool pyramid = 1;
    for (int i = 1; i <= n; i++)
    {
        if (2 * i < n && mas[i] > mas[i * 2])
        {

            pyramid = 0;
            break;
        }
        if (i * 2 + 1 < n && mas[i] > mas[i * 2 + 1])
        {

            pyramid = 0;
            break;
        }

    }
    output << (pyramid ? "YES" : "NO");
    delete [] mas;
    entrance.close();
    output.close();
}

