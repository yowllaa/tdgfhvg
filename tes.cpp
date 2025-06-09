#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int ROWS = 10;
const int COLS = 10;
const int MAKS_PESERTA = 100;

struct Peserta {
    string nama;
    string email;
    string noTelepon;
    int jumlahTiket;
    string nomorKursi[10];
};

bool kursiTerpakai[ROWS][COLS] = {false};
Peserta daftarPeserta[MAKS_PESERTA];
int jumlahPeserta = 0;

bool hanyaAngka(const string& str) {
    for (char c : str) {
         if (c < '0' || c > '9') return false;
    }
    return true;
}

bool konversiKursi(string kode, int baris, int kolom) {
    if (kode.length() < 2 || kode.length() > 3) return false;

    char huruf = toupper(kode[0]);
    if (huruf < 'A' || huruf > 'J') return false;
    baris = huruf - 'A';

    string angka = kode.substr(1);
    if (!hanyaAngka(angka)) return false;

    kolom = stoi(angka) - 1;
    if (kolom < 0 || kolom >= COLS) return false;

    return true; 
}

void tampilkanKursi() {
    cout << "\n=== Denah Kursi ===\n   ";
    for (int i = 1; i <= COLS; i++) cout << setw(3) << i;
    cout << endl;

    for (int i = 0; i < ROWS; i++) {
        char baris = 'A' + i;
        cout << baris << " ";
        for (int j = 0; j < COLS; j++) {
            cout << " [" << (kursiTerpakai[i][j] ? 'X' : 'O') << "]";
        }
        cout << endl;
    }
}

void cetakTiket(const Peserta& peserta) {
    cout << "\n=== TIKET SEMINAR ===\n";
    cout << "Nama: " << peserta.nama << endl;
    cout << "Email: " << peserta.email << endl;
    cout << "Telepon: " << peserta.noTelepon << endl;
    cout << "Jumlah Tiket: " << peserta.jumlahTiket << endl;
    cout << "Kursi: ";
    for (int i = 0; i < peserta.jumlahTiket; i++) {
        cout << peserta.nomorKursi[i];
        if (i != peserta.jumlahTiket - 1) cout << ", ";
    }
    cout << endl;
    cout << "Harap datang 30 menit sebelum acara dimulai.\n";
}

void bayarTiket(Peserta& peserta) {
    const int hargaPerTiket = 50000;
    int totalBayar = hargaPerTiket * peserta.jumlahTiket;

    cout << "\n=== Pembayaran Tiket ===\n";
    cout << "Nama: " << peserta.nama << endl;
    cout << "Jumlah Tiket: " << peserta.jumlahTiket << endl;
    cout << "Total Bayar: Rp" << totalBayar << endl;

    char konfirmasi;
    cout << "Lanjutkan pembayaran? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        cout << "Pembayaran berhasil!\n";
        cetakTiket(peserta);
    } else {
        
    }
}

void inputData(Peserta* peserta, int index) {
    cout << "\nMasukkan data peserta " << "\n";
    cout << "Nama: ";
    getline(cin >> ws, peserta[index].nama);
    cout << "Email: ";
    getline(cin, peserta[index].email);
    cout << "No. Telepon: ";
    getline(cin, peserta[index].noTelepon);

    do {
        cout << "Jumlah tiket : ";
        cin >> peserta[index].jumlahTiket;
        if (peserta[index].jumlahTiket < 1 || peserta[index].jumlahTiket > 100)
            cout << "Jumlah tidak valid.\n";
    } while (peserta[index].jumlahTiket < 1 || peserta[index].jumlahTiket > 100);

    tampilkanKursi();
    for (int i = 0; i < peserta[index].jumlahTiket; i++) {
        string kode;
        int baris, kolom;
        do {
            cout << "- Kursi ke-" << i + 1 << ": ";
            cin >> kode;
            if (!konversiKursi(kode, baris, kolom)) {
                cout << "Format salah atau di luar jangkauan.\n";
                continue;
            }
            if (kursiTerpakai[baris][kolom]) {
                cout << "Kursi " << kode << " sudah dipesan.\n";
                continue;
            }
            kursiTerpakai[baris][kolom] = true;
            peserta[index].nomorKursi[i] = kode;
            break;
        } while (true);
    }
}

void tampilkanData(Peserta* peserta, int jumlah) {
    cout << "\n=== Daftar Peserta ===\n";
    for (int i = 0; i < jumlah; i++) {
        cout << "\nPeserta ke-" << i + 1 << ":\n";
        cout << "Nama: " << peserta[i].nama << endl;
        cout << "Email: " << peserta[i].email << endl;
        cout << "Telepon: " << peserta[i].noTelepon << endl;
        cout << "Jumlah Tiket: " << peserta[i].jumlahTiket << endl;
        cout << "Kursi: ";
        for (int j = 0; j < peserta[i].jumlahTiket; j++) {
            cout << peserta[i].nomorKursi[j];
            if (j != peserta[i].jumlahTiket - 1) cout << ", ";
        }
        cout << endl;
    }
}

void menuRegistrasi() {
    char lanjut;
    do {
        if (jumlahPeserta >= MAKS_PESERTA) {
            cout << "Kapasitas penuh.\n";
            break;
        }
	if (jumlahPeserta > 0) system("cls");
        inputData(daftarPeserta, jumlahPeserta);
        bayarTiket(daftarPeserta[jumlahPeserta]);
        jumlahPeserta++;

        cout << "Tambah peserta lagi? (y/n): ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');

    tampilkanData(daftarPeserta, jumlahPeserta);
    tampilkanKursi();
}

int main() {
    char kembali;

    do {

        cout << "\n===== SISTEM REGISTRASI SEMINAR =====\n";
        menuRegistrasi();

        cout << "\nKembali ke menu awal? (y/n): ";
        cin >> kembali;
    } while (kembali == 'y' || kembali == 'Y');

    cout << "\nTerima kasih!\n";
    return 0;
}
