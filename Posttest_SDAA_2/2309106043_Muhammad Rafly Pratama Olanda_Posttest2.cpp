#include <iostream>
using namespace std;

struct Produk {
    int id;
    string nama;
    float harga;
    int stok;
};

Produk produkList[50];
int jumlahProduk = 0;


void tampilkanProduk() {
    if (jumlahProduk == 0) { 
        cout << "Tidak ada produk yang tersedia." << endl;
    } else {
        cout << "Daftar Produk:" << endl;
        for (int i = 0; i < jumlahProduk; i++) {
            Produk* p = &produkList[i]; // Pointer menunjuk ke produk
            cout << "ID: " << p->id
                 << " | Nama: " << p->nama
                 << " | Harga: " << p->harga
                 << " | Stok: " << p->stok << endl;
        }
    }
}


bool cekID(int id) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (produkList[i].id == id) {
            return true; 
        }
    }
    return false; 
}


bool tambahProduk() {
    if (jumlahProduk >= 50) { 
        cout << "Stok produk sudah penuh!" << endl;
        return false;
    }

    Produk p;
    cout << "Masukkan ID produk: ";
    cin >> p.id;

    if (cekID(p.id)) {
        cout << "ID produk sudah ada, harap masukkan ID yang berbeda." << endl;
        return false;
    }

    cin.ignore(); 
    cout << "Masukkan nama produk: ";
    getline(cin, p.nama);
    cout << "Masukkan harga produk: ";
    cin >> p.harga;
    cout << "Masukkan stok produk: ";
    cin >> p.stok;

    produkList[jumlahProduk] = p; 
    jumlahProduk++;

    cout << "Produk berhasil ditambahkan!" << endl;
    return true;
}


void ubahHargaProduk() {
    if (jumlahProduk == 0) { 
        cout << "Belum ada produk yang tersedia. Tidak dapat mengubah harga." << endl;
        return;
    }

    tampilkanProduk();
    int id;
    cout << "Masukkan ID produk yang harga-nya akan diubah: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < jumlahProduk; i++) {
        if (produkList[i].id == id) {
            float* hargaPtr = &produkList[i].harga; // Pointer ke harga produk
            cout << "Masukkan harga baru untuk produk " << produkList[i].nama << ": ";
            cin >> *hargaPtr;
            cout << "Harga berhasil diubah!" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Produk dengan ID " << id << " tidak ditemukan." << endl;
    }
}


void hapusProduk() {
    if (jumlahProduk == 0) { 
        cout << "Belum ada produk yang tersedia. Tidak dapat menghapus produk." << endl;
        return;
    }

    tampilkanProduk();
    int id;
    cout << "Masukkan ID produk yang akan dihapus: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < jumlahProduk; i++) {
        if (produkList[i].id == id) {
            cout << "Data produk yang akan dihapus:" << endl;
            cout << "Apakah Anda yakin ingin menghapus produk ini? (y/n): ";
            char konfirmasi;
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
                for (int j = i; j < jumlahProduk - 1; j++) {
                    produkList[j] = produkList[j + 1];
                }
                jumlahProduk--;
                cout << "Produk berhasil dihapus!" << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Produk dengan ID " << id << " tidak ditemukan." << endl;
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
