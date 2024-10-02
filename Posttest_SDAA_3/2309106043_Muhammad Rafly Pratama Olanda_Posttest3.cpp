#include <iostream>
using namespace std;

struct Produk {
    int id;
    string nama;
    float harga;
    int stok;
    Produk* next; 
};


Produk* head = nullptr;

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
                delete p;
                cout << "Produk berhasil dihapus!" << endl;
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

void tampilkanMenu() {
    cout << "================================" << endl;
    cout << "Selamat Datang Di Li-NING Store" << endl;
    cout << "================================" << endl;
    cout << "1. Tambah Produk" << endl;
    cout << "2. Ubah Harga Produk" << endl; 
    cout << "3. Hapus Produk" << endl;
    cout << "4. Tampilkan Semua Produk" << endl;
    cout << "0. Keluar" << endl;
}

int main() {
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
