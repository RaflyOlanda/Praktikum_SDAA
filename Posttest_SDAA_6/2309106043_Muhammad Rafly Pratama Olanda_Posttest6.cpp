#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct Produk {
    int id;
    string nama;
    float harga;
    int stok;
    Produk* next;
};

struct ProdukStack {
    Produk* produk;
    ProdukStack* next;
};

struct RiwayatNode {
    Produk* produk;
    RiwayatNode* next;
};

struct QueueNode {
    string namaPembeli;
    int produkId; 
    QueueNode* next;
};


Produk* head = nullptr;
ProdukStack* top = nullptr;
RiwayatNode* riwayatHead = nullptr; 
QueueNode* front = nullptr;
QueueNode* rear = nullptr;


void tampilkanProduk() {
    if (head == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
    } else {
        cout << "Daftar Produk:" << endl;
        Produk* p = head;
        while (p != nullptr) {
            cout << "ID: " << p->id
                 << " | Nama: " << p->nama
                 << " | Harga: " << p->harga
                 << " | Stok: " << p->stok << endl;
            p = p->next;
        }
    }
}

bool cekID(int id) {
    Produk* p = head;
    while (p != nullptr) {
        if (p->id == id) {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool tambahProduk() {
    Produk* p = new Produk();
    cout << "Masukkan ID produk: ";
    cin >> p->id;

    if (cekID(p->id)) {
        cout << "ID produk sudah ada, harap masukkan ID yang berbeda." << endl;
        delete p;
        return false;
    }

    cin.ignore();
    cout << "Masukkan nama produk: ";
    getline(cin, p->nama);
    cout << "Masukkan harga produk: ";
    cin >> p->harga;
    cout << "Masukkan stok produk: ";
    cin >> p->stok;
    p->next = nullptr;

    if (head == nullptr) {
        head = p;
    } else {
        Produk* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = p;
    }

    cout << "Produk berhasil ditambahkan!" << endl;
    return true;
}


void ubahHargaProduk() {
    if (head == nullptr) {
        cout << "Belum ada produk yang tersedia. Tidak dapat mengubah harga." << endl;
        return;
    }

    tampilkanProduk();
    int id;
    cout << "Masukkan ID produk yang harga-nya akan diubah: ";
    cin >> id;

    Produk* p = head;
    while (p != nullptr) {
        if (p->id == id) {
            float* hargaPtr = &p->harga;
            cout << "Masukkan harga baru untuk produk " << p->nama << ": ";
            cin >> *hargaPtr;
            cout << "Harga berhasil diubah!" << endl;
            return;
        }
        p = p->next;
    }
    cout << "Produk dengan ID " << id << " tidak ditemukan." << endl;
}


void pushToStack(Produk* produk) {
    ProdukStack* node = new ProdukStack();
    node->produk = produk;
    node->next = top;
    top = node;

    RiwayatNode* riwayatNode = new RiwayatNode();
    riwayatNode->produk = produk;
    riwayatNode->next = riwayatHead;
    riwayatHead = riwayatNode;
}


void enqueue() {
    string namaPembeli;
    int produkId;

    cout << "Masukkan nama pelanggan: ";
    cin.ignore();
    getline(cin, namaPembeli);

    tampilkanProduk();
    
    cout << "Masukkan ID produk yang dipilih: ";
    cin >> produkId;

    Produk* p = head;
    while (p != nullptr) {
        if (p->id == produkId) {
            if (p->stok > 0) {
                p->stok--;

                QueueNode* node = new QueueNode();
                node->namaPembeli = namaPembeli;
                node->produkId = produkId; 
                node->next = nullptr;

                if (rear == nullptr) {
                    front = rear = node;
                } else {
                    rear->next = node;
                    rear = node;
                }

                cout << "Pelanggan \"" << namaPembeli << "\" berhasil ditambahkan ke antrian untuk produk ID " << produkId << "." << endl;
                return;
            } else {
                cout << "Stok produk tidak cukup!" << endl;
                return;
            }
        }
        p = p->next;
    }

    cout << "Produk dengan ID " << produkId << " tidak ditemukan." << endl;
}


void hapusProduk() {
    if (head == nullptr) {
        cout << "Belum ada produk yang tersedia. Tidak dapat menghapus produk." << endl;
        return;
    }

    tampilkanProduk();
    int id;
    cout << "Masukkan ID produk yang akan dihapus: ";
    cin >> id;

    Produk* p = head;
    Produk* prev = nullptr;

    while (p != nullptr) {
        if (p->id == id) {
            cout << "Data produk yang akan dihapus:" << endl;
            cout << "Apakah Anda yakin ingin menghapus produk ini? (y/n): ";
            char konfirmasi;
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                if (prev == nullptr) {
                    head = p->next;
                } else {
                    prev->next = p->next;
                }
                pushToStack(p);
                cout << "Produk berhasil dihapus dan disimpan ke riwayat penghapusan!" << endl;
                return;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
                return;
            }
        }
        prev = p;
        p = p->next;
    }
    cout << "Produk dengan ID " << id << " tidak ditemukan." << endl;
}


void undoHapusProduk() {
    if (top == nullptr) {
        cout << "Tidak ada produk yang bisa dikembalikan." << endl;
        return;
    }

    Produk* produk = top->produk;
    top = top->next;
    produk->next = nullptr;  

    if (head == nullptr) {
        head = produk;
    } else {
        Produk* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = produk;
    }

    cout << "Produk " << produk->nama << " dikembalikan ke daftar!" << endl;
    
    tampilkanProduk();
}


void dequeue() {
    if (front == nullptr) { 
        cout << "Tidak ada pelanggan di antrian." << endl;
        return;
    }

    Produk* produk = head;
    while (produk != nullptr && produk->id != front->produkId) {
        produk = produk->next;
    }

    if (produk != nullptr) {
        cout << "Pelanggan \"" << front->namaPembeli << "\" telah dilayani untuk produk \"" << produk->nama << "\" dengan harga " << produk->harga << "." << endl;
    } else {
        cout << "Pelanggan \"" << front->namaPembeli << "\" telah dilayani, tetapi produk tidak ditemukan." << endl;
    }

    QueueNode* temp = front;
    front = front->next;
    delete temp; 

    if (front == nullptr) {
        rear = nullptr; 
    }
}

void tampilkanAntrian() {
    if (front == nullptr) {
        cout << "Antrian kosong." << endl;
    } else {
        cout << "Antrian Pelanggan:" << endl;
        QueueNode* temp = front;
        while (temp != nullptr) {
            Produk* produk = head;
            while (produk != nullptr && produk->id != temp->produkId) {
                produk = produk->next;
            }

            if (produk != nullptr) {
                cout << "- " << temp->namaPembeli << " (Pesanan: " << produk->nama << ", Harga: " << produk->harga << ")" << endl;
            } else {
                cout << "- " << temp->namaPembeli << " (Pesanan: Produk tidak ditemukan)" << endl;
            }

            temp = temp->next;
        }
    }
}


Produk* mergeSortAscending(Produk* head) {
    if (!head || !head->next) return head;

    Produk* slow = head;
    Produk* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    Produk* mid = slow->next;
    slow->next = nullptr;

    
    Produk* left = mergeSortAscending(head);
    Produk* right = mergeSortAscending(mid);

    Produk tempNode;
    Produk* curr = &tempNode;
    while (left && right) {
        if (left->harga <= right->harga) {
            curr->next = left;
            left = left->next;
        } else {
            curr->next = right;
            right = right->next;
        }
        curr = curr->next;
    }
    if (left) {
    curr->next = left;
    } else {
    curr->next = right;
    }
    return tempNode.next;
}



Produk* getTail(Produk* head) {
    while (head != nullptr && head->next != nullptr)
        head = head->next;
    return head;
}

Produk* partition(Produk* head, Produk* end, Produk** newHead, Produk** newEnd) {
    Produk* pivot = end;
    Produk* prev = nullptr, *curr = head, *tail = pivot;

    while (curr != pivot) {
        if (curr->harga > pivot->harga) {
            if (*newHead == nullptr)
                *newHead = curr;
            prev = curr;
            curr = curr->next;
        } else {
            if (prev)
                prev->next = curr->next;
            Produk* tmp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = tmp;
        }
    }

    if (*newHead == nullptr)
        *newHead = pivot;

    *newEnd = tail;
    return pivot;
}

Produk* rekursifquicksort(Produk* head, Produk* end) {
    if (!head || head == end)
        return head;

    Produk* newHead = nullptr, *newEnd = nullptr;
    Produk* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        Produk* tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = nullptr;

        newHead = rekursifquicksort(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = rekursifquicksort(pivot->next, newEnd);
    return newHead;
}

Produk* quickSortDescending(Produk* head) {
    return rekursifquicksort(head, getTail(head));
}

void sortAscending() {
    head = mergeSortAscending(head);
    cout << "Produk telah diurutkan secara ascending berdasarkan harga." << endl;
    tampilkanProduk();
}

void sortDescending() {
    head = quickSortDescending(head);
    cout << "Produk telah diurutkan secara descending berdasarkan harga." << endl;
    tampilkanProduk();
}

void sortingID(Produk* head) {
    if (head == nullptr || head->next == nullptr)
        return;

    bool ditukar;
    Produk* ptr;
    Produk* lptr = nullptr;

    do {
        ditukar = false;
        ptr = head;

        while (ptr->next != lptr) {
            if (ptr->id > ptr->next->id) {
                int tempId = ptr->id;
                string tempNama = ptr->nama;
                float tempHarga = ptr->harga;
                int tempStok = ptr->stok;

                ptr->id = ptr->next->id;
                ptr->nama = ptr->next->nama;
                ptr->harga = ptr->next->harga;
                ptr->stok = ptr->next->stok;

                ptr->next->id = tempId;
                ptr->next->nama = tempNama;
                ptr->next->harga = tempHarga;
                ptr->next->stok = tempStok;

                ditukar = true;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (ditukar);
}

int pencarianFibonacci(Produk* head, int idCari) {
    sortingID(head);
    if (head == nullptr) {
        cout << "\nDaftar produk kosong." << endl;
        return -1;
    }
    
    int n = 0;
    Produk* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }
    
    int fibM2 = 0;   
    int fibM1 = 1;   
    int fibM = fibM2 + fibM1;  
    
    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM = fibM2 + fibM1;
    }
    
    int offset = -1;  
    
    while (fibM > 0) {
        int i = min(offset + fibM2, n-1);
        
        temp = head;
        for (int j = 0; j <= i && temp != nullptr; j++) {
            if (j < i) {
                temp = temp->next;
            }
        }
        
        if (temp != nullptr) {
            if (temp->id == idCari) {
                cout << "\nProduk ditemukan!\n";
                cout << "ID: " << temp->id 
                     << "\nNama: " << temp->nama 
                     << "\nHarga: " << temp->harga 
                     << "\nStok: " << temp->stok << endl;
                return i;
            }
            else if (temp->id < idCari) {
                fibM = fibM1;
                fibM1 = fibM2;
                fibM2 = fibM - fibM1;
                offset = i;
            }
            else {
                fibM = fibM2;
                fibM1 = fibM1 - fibM2;
                fibM2 = fibM - fibM1;
            }
        }
    }
    
    cout << "\nProduk dengan ID " << idCari << " tidak ditemukan." << endl;
    return -1;
}

void sortharga() {
    if (head == nullptr || head->next == nullptr)
        return;

    bool swapped;
    Produk* ptr1;
    Produk* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->harga > ptr1->next->harga) {
                swap(ptr1->id, ptr1->next->id);
                swap(ptr1->nama, ptr1->next->nama);
                swap(ptr1->harga, ptr1->next->harga);
                swap(ptr1->stok, ptr1->next->stok);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void jumpSearch(Produk* head, float hargaCari) {
    if (head == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    sortharga();

    int n = 0;
    Produk* temp = head;
    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    temp = head;
    bool ditemukan = false;

    int langkah = sqrt(n);
    if (langkah < 1) langkah = 1;

    Produk* prev = nullptr;
    Produk* current = head;

    while (current != nullptr && current->harga < hargaCari) {
        prev = current;
        
        for (int i = 0; i < langkah && current != nullptr; i++) {
            current = current->next;
        }
    }

    if (prev == nullptr) {
        prev = head;
    }

    float toleransi = 0.01;
    temp = prev;
    
    while (temp != nullptr && (current == nullptr || temp != current)) {
        if (abs(temp->harga - hargaCari) <= toleransi) {
            if (!ditemukan) {
                cout << "\nProduk yang ditemukan dengan harga " << hargaCari << ":" << endl;
                ditemukan = true;
            }
            
            cout << "\n--------------------"
                 << "\nID: " << temp->id 
                 << "\nNama: " << temp->nama 
                 << "\nHarga: "  << temp->harga
                 << "\nStok: " << temp->stok 
                 << "\n--------------------" << endl;
        }
        temp = temp->next;
    }

    if (current != nullptr && abs(current->harga - hargaCari) <= toleransi) {
        if (!ditemukan) {
            cout << "\nProduk yang ditemukan dengan harga " << hargaCari << ":" << endl;
        }
        cout << "\n--------------------"
             << "\nID: " << current->id 
             << "\nNama: " << current->nama 
             << "\nHarga: " << current->harga
             << "\nStok: " << current->stok 
             << "\n--------------------" << endl;
        ditemukan = true;
    }

    if (!ditemukan) {
        cout << "\nTidak ditemukan produk dengan harga "<< hargaCari << endl;
    }
}


void buatTabelPergeseran(string pola, int ukuranPola, int tabelPergeseran[256]) {
    for (int i = 0; i < 256; i++)
        tabelPergeseran[i] = -1;
    
    for (int i = 0; i < ukuranPola; i++)
        tabelPergeseran[(int) pola[i]] = i;
}

void pencarianBoyerMoore(Produk* head, string namaCari) {
    if (head == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    transform(namaCari.begin(), namaCari.end(), namaCari.begin(), ::tolower);
    
    bool ditemukan = false;
    Produk* temp = head;
    
    while (temp != nullptr) {
        string namaTemp = temp->nama;
        transform(namaTemp.begin(), namaTemp.end(), namaTemp.begin(), ::tolower);
        
        int n = namaTemp.length();
        int m = namaCari.length();
        int tabelPergeseran[256];
        
        buatTabelPergeseran(namaCari, m, tabelPergeseran);
        
        int s = 0;
        while (s <= (n - m)) {
            int j = m - 1;
            
            while (j >= 0 && namaCari[j] == namaTemp[s + j])
                j--;
                
            if (j < 0) {
                cout << "\nProduk ditemukan!\n";
                cout << "ID: " << temp->id 
                     << "\nNama: " << temp->nama 
                     << "\nHarga: " << temp->harga 
                     << "\nStok: " << temp->stok << endl;
                ditemukan = true;
                break;
            }
            else {
                s += max(1, j - tabelPergeseran[namaTemp[s + j]]);
            }
        }
        temp = temp->next;
    }
    
    if (!ditemukan) {
        cout << "\nProduk dengan nama '" << namaCari << "' tidak ditemukan." << endl;
    }
}

void cariProdukById() {
    if (head == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }
    
    int idCari;
    cout << "Masukkan ID produk yang dicari: ";
    cin >> idCari;
    
    cout << "\nMenggunakan Pencarian Fibonacci:" << endl;
    pencarianFibonacci(head, idCari);
}

void cariProdukByHarga() {
    if (head == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }
    
    float hargaCari;
    cout << "Masukkan harga produk yang dicari: ";
    cin >> hargaCari;
    
    cout << "\nMenggunakan Pencarian Lompat:" << endl;
    jumpSearch(head, hargaCari);
}

void cariProdukByNama() {
    if (head == nullptr) {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }
    
    string namaCari;
    cout << "Masukkan nama produk yang dicari: ";
    cin.ignore();
    getline(cin, namaCari);
    
    cout << "\nMenggunakan Pencarian Boyer-Moore:" << endl;
    pencarianBoyerMoore(head, namaCari);
}

void tampilkanMenu() {
    cout << "===================================" << endl;
    cout << "Selamat Datang Di Li-NING Store" << endl;
    cout << "===================================" << endl;
    cout << "1. Tambah Produk" << endl;
    cout << "2. Ubah Harga Produk" << endl;
    cout << "3. Hapus Produk" << endl;
    cout << "4. Tampilkan Semua Produk" << endl;
    cout << "5. Undo Hapus Produk (stack)" << endl;
    cout << "6. Tambah Pelanggan (enqueue)" << endl;
    cout << "7. Tampilkan Antrian Pelanggan" << endl;
    cout << "8. Layani Pelanggan (dequeue)" << endl;
    cout << "9. Urutkan Harga Produk (Ascending)" << endl;
    cout << "10. Urutkan Harga Produk (Descending)" << endl;
    cout << "11. Cari Produk berdasarkan ID (Fibonacci Search)" << endl;
    cout << "12. Cari Produk berdasarkan Harga (Jump Search)" << endl;
    cout << "13. Cari Produk berdasarkan Nama (Boyer-Moore)" << endl;
    cout << "0. Keluar" << endl;
    cout << "===================================" << endl;
}


int main() {
    Produk* produk1 = new Produk{1, "Axforce JR", 150000, 10};
Produk* produk2 = new Produk{2, "Axforce Cannon Pro - 4U", 270000, 5};
Produk* produk3 = new Produk{3, "Axforce E-Battle", 250000, 7};
Produk* produk4 = new Produk{4, "Axforce 40 - 4U", 200000, 8}; 
Produk* produk5 = new Produk{5, "Axforce Lightning", 300000, 4}; 

head = produk1; 
produk1->next = produk2; 
produk2->next = produk3; 
produk3->next = produk4; 
produk4->next = produk5; 
produk5->next = nullptr; 
    int pilihan;
    do {
        tampilkanMenu();
        cout << "Pilih opsi: ";
        cin >> pilihan;
        switch (pilihan) {
            case 1:
                tambahProduk();
                break;
            case 2:
                ubahHargaProduk();
                break;
            case 3:
                hapusProduk();
                break;
            case 4:
                tampilkanProduk();
                break;
            case 5:
                undoHapusProduk();
                break;
            case 6: {
                enqueue();
                break;
            }
            case 7:
                tampilkanAntrian();
                break;
            case 8:
                dequeue();
                break;
            case 9:
                sortAscending();
                break;
            case 10:
                sortDescending();
                break;
            case 11:
                cariProdukById();
                break;
            case 12:
                cariProdukByHarga();
                break;
            case 13:
                cariProdukByNama();
                break;
            case 0:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Opsi tidak valid." << endl;
                break;
        }
    } while (pilihan != 0);

    return 0;
}
