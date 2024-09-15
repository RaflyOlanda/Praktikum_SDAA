#include <iostream>
using namespace std;

void hanoi(int n, char menarapertama, char menaratujuan, char menaratengah) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari " << menarapertama << " ke " << menaratujuan << endl;
        return;
    }

    hanoi(n - 1, menarapertama, menaratengah, menaratujuan);

    cout << "Pindahkan piringan " << n << " dari " << menarapertama << " ke " << menaratujuan << endl;

    hanoi(n - 1, menaratengah, menaratujuan, menarapertama);
}

int main() {
    cout << "============================" << endl;
    cout << "Program langkah menara Hanoi" << endl;
    cout << "============================" << endl;
    int jumlahpiring = 3; 
    cout << "Langkah pemindahan Menara Hanoi dengan " << jumlahpiring << " piringan:" << endl;
    hanoi(jumlahpiring, 'A', 'C', 'B'); 
    return 0;
}
