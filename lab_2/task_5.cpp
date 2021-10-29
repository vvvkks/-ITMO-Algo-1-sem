#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int> &a, int low, int high, int k) {

    int i = low;
    int j = high;
    int pivot = a[(i + j) / 2];
    while (i <= j) {
        while (a[i] < pivot)i++;

        while (a[j] > pivot)j--;

        if (i <= j) {
            swap(a[i++], a[j--]);


        }
    }

    if (low <= j && k <= j) quickSort(a, low, j, k);
    if  (i <= high && k >= i) quickSort(a, i, high, k);


}


int main() {
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);

    int n, k, A, B, C;
    cin>>n>>k>>A>>B>>C;
    vector<int> a(n);
    cin>>a[0]>>a[1];
    for(int i=2; i<n; i++) {
        a[i] = A*a[i-2] + B*a[i-1] + C;
    }
    quickSort(a, 0, n-1, k-1);
    cout << a[k-1];
}
