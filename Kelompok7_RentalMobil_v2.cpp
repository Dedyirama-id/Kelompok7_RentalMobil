#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct DataMobil
{
    int kode;
    string jenis;
    int harga;
};

struct FormSewa
{
    int kode;
    string nama;
    int nik;
    string alamat;
    string noTelp;
    int durasi;
};

const float persentaseDiskon = 0.3f;
const int MAX_MOBIL = 10;

DataMobil arrDataMobil[MAX_MOBIL] = {
    {1, "Toyota Avanza", 450000},
    {2, "Honda Jazz", 350000},
    {3, "Toyota Fortuner", 850000},
    {4, "Honda CRV", 500000},
    {5, "Toyota Innova", 750000},
    {6, "Mobil Elf", 700000},
    {7, "Toyota Hiace", 800000},
    {8, "Bus Mini", 650000},
    {9, "Bus Sedang", 900000},
    {10, "Bus Besar", 1000000}};

void menu();
int pilih();
float hitungDiskon(FormSewa &dataSewa);
void writeData(FormSewa &dataSewa);
void invoice(FormSewa &dataSewa);
void sewa(int &pilihan);

int main()
{
    system("cls");
    menu();
    int pilihan = pilih();
    sewa(pilihan);

    return 0;
}

void menu()
{
    cout << "   *RENTAL/SEWA MOBIL DAN TRAVEL AUTO CAR*   " << endl;
    cout << "===================================================" << endl;
    cout << "kode\t| Jenis Mobil\t\t| Harga Sewa / Hari" << endl;
    cout << "===================================================" << endl;
    for (int i = 0; i < MAX_MOBIL; i++)
    {
        cout << arrDataMobil[i].kode << "\t| " << arrDataMobil[i].jenis << ((arrDataMobil[i].jenis.length() < 14) ? "\t\t| " : "\t| ") << "Rp " << arrDataMobil[i].harga << endl;
    }
    cout << "===================================================" << endl;
}

int pilih()
{
    while (true)
    {
        int pilihan;
        cout << "Masukkan kode mobil : ";
        cin >> pilihan;
        if (pilihan > 0 && pilihan <= MAX_MOBIL)
        {
            return pilihan;
        }
        else
        {
            cout << "Kode mobil tidak tersedia" << endl;
        }
    }
}

float hitungDiskon(FormSewa &dataSewa)
{
    return (dataSewa.durasi > 14) ? dataSewa.durasi * arrDataMobil[dataSewa.kode - 1].harga * persentaseDiskon : 0;
}

void writeData(FormSewa &dataSewa)
{
    unsigned int subTotal = dataSewa.durasi * arrDataMobil[dataSewa.kode - 1].harga;
    unsigned int diskon = hitungDiskon(dataSewa);
    unsigned int total = subTotal - diskon;
    unsigned int bayar;
    ofstream outFile;
    outFile.open("history.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << dataSewa.nama << "\t" << dataSewa.nik << "\t"<< dataSewa.alamat << "\t" << dataSewa.noTelp << "\t" << dataSewa.kode << "\t" << arrDataMobil[dataSewa.kode - 1].jenis << "\t" << dataSewa.durasi << "\t" << subTotal << "\t" << diskon << "\t" << total << endl;
        outFile.close();
    }
    else
    {
        cout << "Gagal ketika membuka file" << endl;
    }
}

void invoice(FormSewa &dataSewa)
{
    unsigned int subTotal = dataSewa.durasi * arrDataMobil[dataSewa.kode - 1].harga;
    unsigned int diskon = hitungDiskon(dataSewa);
    unsigned int total = subTotal - diskon;
    unsigned int bayar;
    while (true)
    {
        system("cls");
        cout << "==================================================" << endl;
        cout << "  INVOICE RENTAL/SEWA MOBIL DAN TRAVEL AUTO CAR   " << endl;
        cout << "==================================================" << endl;
        cout << "Nama penyewa\t: " << dataSewa.nama << endl;
        cout << "Kode mobil\t: " << dataSewa.kode << endl;
        cout << "jenis mobil\t: " << arrDataMobil[dataSewa.kode - 1].jenis << endl;
        cout << "Harga sewa\t: Rp " << arrDataMobil[dataSewa.kode - 1].harga << endl;
        cout << "Durasi sewa\t: " << dataSewa.durasi << " Hari" << endl;
        cout << "Subtotal\t: Rp " << subTotal << endl;
        cout << "Diskon\t\t: Rp " << diskon << endl;
        cout << "Total bayar\t: Rp " << total << endl;
        cout << "==================================================" << endl;

        cout << "Jumlah bayar\t: Rp ";
        cin >> bayar;
        if (bayar >= total)
        {
            cout << "Kembalian\t: Rp " << bayar - total << endl;
            cout << "================= Terima kasih! =================" << endl;
            writeData(dataSewa);
            break;
        }
        else
        {
            cout << "Uang yang dibayarkan kurang..." << endl;
            cin.ignore();
            cin.get();
        }
    }
}

void sewa(int &pilihan)
{
    FormSewa dataSewa;
    dataSewa.kode = pilihan;
    cout << "Masukkan nama penyewa: ";
    cin.ignore();
    getline(cin, dataSewa.nama);
    cout << "Masukkan NIK Penyewa: ";
    cin >> dataSewa.nik;
    cin.ignore();
    cout << "Masukkan alamat penyewa: ";
    getline(cin, dataSewa.alamat);
    cout << "Masukkan nomor telepon penyewa: ";
    getline(cin, dataSewa.noTelp);
    while (true)
    {
        cout << "Masukkan durasi sewa (dalam hari, max 90 hari): ";
        cin >> dataSewa.durasi;
        if (dataSewa.durasi > 0 && dataSewa.durasi <= 90)
            break;
        else if (dataSewa.durasi <= 0)
            cout << "!! Durasi sewa minimal 1 hari" << endl;
        else
            cout << "!! Durasi sewa maksimal 90 hari" << endl;
    }
    invoice(dataSewa);
}