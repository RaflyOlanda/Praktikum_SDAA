#include <iostream>
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


void tampilkanMenu() {
    cout << "================================" << endl;
    cout << "Selamat Datang Di Li-NING Store" << endl;
    cout << "================================" << endl;
    cout << "1. Tambah Produk" << endl;
    cout << "2. Ubah Harga Produk" << endl;
    cout << "3. Hapus Produk" << endl;
    cout << "4. Tampilkan Semua Produk" << endl;
    cout << "5. Undo Hapus Produk (stack)" << endl;
    cout << "6. Tambah Pelanggan ke Antrian(enqueue)" << endl;
    cout << "7. Tampilkan Antrian Pelanggan" << endl;
    cout << "8. Layani Pelanggan (dequeue)" << endl;
    cout << "0. Keluar" << endl;
    cout << "================================" << endl;
}


int main() {
    Produk* produk1 = new Produk{1, "Axforce JR", 150000, 10};
    Produk* produk2 = new Produk{2, "Axforce Cannon Pro - 4U", 200000, 5};
    Produk* produk3 = new Produk{3, "Axforce E-Battle", 250000, 7};

    head = produk1; 
    produk1->next = produk2; 
    produk2->next = produk3; 
    produk3->next = nullptr; 
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
