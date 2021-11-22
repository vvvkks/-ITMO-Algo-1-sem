#include <fstream>

using namespace std;
string mas[1000];
string support[1000]; // вспомогательный массив
int n, m, k;

void radixSort(int position) {
    char abc = 'a';
    int k = 0;
    for (int i = 0; i < 26; i++) { // min key = 0, max key = 26
        for (int j = 0; j < n; j++) { // первый проход по сортируемуму массиву, где заполняется вспомогательный
            if (mas[j][position] == abc) {
                support[k] = mas[j];
                k++;
            }
        }
        abc++;
    }
    for (int i = 0; i < n; i++) {  // обратный проход, с целью изменения элементов вспомогательного массива, чтобы они указывали на какие индексы ставить значения
        mas[i] = support[i];
    }
}

int main() {
    ifstream entrance("radixsort.in");
    ofstream output("radixsort.out");

    entrance >> n >> m >> k;

    for (int i = 0; i < n; ++i) {
        entrance >> mas[i];
    }

    for (int move = m - 1; move >= m - k; move--) { // передача индекса справа налево
        radixSort(move);
    }

    for (int i = 0; i < n; i++) {
        output << mas[i] << endl;
    }

    entrance.close();
    output.close();
    return 0;
}
