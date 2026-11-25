#include <stdio.h>

#define MAX_BARANG 10

long hitungTotalNilaiRekursif(int harga[], int stok[], int jumlahBarang, int indeks) {
    if (indeks >= jumlahBarang) {
        return 0;
    }
    long nilaiBarangIni = (long)harga[indeks] * (long)stok[indeks];
    return nilaiBarangIni + hitungTotalNilaiRekursif(harga, stok, jumlahBarang, indeks + 1);
}

void periksaStokBarang(int id[], char nama[][30], int stok[], int batasMin[], int jumlahBarang) {
    int i;
    printf("\n=== PEMERIKSAAN STOK ALAT TULIS KAMPUS ===\n");
    printf("%-5s %-22s %-8s %-10s %-12s\n", "ID", "Nama Barang", "Stok", "Batas Min", "Status");
    printf("----------------------------------------------------------------\n");
    for (i = 0; i < jumlahBarang; i++) {
        printf("%-5d %-22s %-8d %-10d ", id[i], nama[i], stok[i], batasMin[i]);
        if (stok[i] < batasMin[i]) {
            printf("KRITIS (<Min)\n");
        } else {
            printf("AMAN\n");
        }
    }
}

void peringatanStokMinimum(int id[], char nama[][30], int stok[], int batasMin[], int jumlahBarang) {
    int i;
    int adaPeringatan = 0;
    printf("\n=== PERINGATAN STOK DI BAWAH BATAS MINIMUM ===\n");
    for (i = 0; i < jumlahBarang; i++) {
        if (stok[i] < batasMin[i]) {
            printf("[PERINGATAN] %s (ID: %d): Stok saat ini %d, di bawah batas minimum %d! Segera restok.\n",
                   nama[i], id[i], stok[i], batasMin[i]);
            adaPeringatan = 1;
        }
    }
    if (adaPeringatan == 0) {
        printf("Semua stok alat tulis aman (tidak ada yang di bawah batas minimum).\n");
    }
}

int main() {
    int jumlahBarang = 5;
    int id[MAX_BARANG]       = {101, 102, 103, 104, 105};
    char nama[MAX_BARANG][30] = {
        "Pulpen_Biru",
        "Buku_Tulis_A5",
        "Pensil_2B",
        "Spidol_Boardmarker",
        "Kertas_HVS_A4"
    };
    int harga[MAX_BARANG]    = {3000, 5000, 2500, 12000, 45000};
    int stok[MAX_BARANG]     = {8, 25, 4, 15, 3};
    int batasMin[MAX_BARANG] = {10, 10, 10, 8, 5};

    int pilihan = -1;
    int pilihId, stokBaru, ditemukan, i;
    long totalNilai;

    while (pilihan != 0) {
        printf("\n=== SISTEM STOK ALAT TULIS KAMPUS ===\n");
        printf("1. Periksa Stok Barang\n");
        printf("2. Cek Peringatan Stok Minimum\n");
        printf("3. Hitung Total Nilai Persediaan (Rekursi)\n");
        printf("4. Update Stok Barang\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");

        if (scanf("%d", &pilihan) != 1) {
            printf("Input tidak valid! Masukkan angka.\n");
            return 1;
        }

        if (pilihan == 1) {
            periksaStokBarang(id, nama, stok, batasMin, jumlahBarang);
        } else if (pilihan == 2) {
            peringatanStokMinimum(id, nama, stok, batasMin, jumlahBarang);
        } else if (pilihan == 3) {
            totalNilai = hitungTotalNilaiRekursif(harga, stok, jumlahBarang, 0);
            printf("\n=== TOTAL NILAI SELURUH PERSEDIAAN ===\n");
            printf("Total nilai persediaan alat tulis: Rp %ld\n", totalNilai);
        } else if (pilihan == 4) {
            printf("\nMasukkan ID barang yang ingin diubah stoknya: ");
            scanf("%d", &pilihId);
            ditemukan = 0;
            for (i = 0; i < jumlahBarang; i++) {
                if (id[i] == pilihId) {
                    printf("Stok lama %s: %d. Masukkan stok baru: ", nama[i], stok[i]);
                    scanf("%d", &stokBaru);
                    if (stokBaru >= 0) {
                        stok[i] = stokBaru;
                        printf("Stok berhasil diperbarui.\n");
                        if (stok[i] < batasMin[i]) {
                            printf("[PERINGATAN] Stok %s sekarang di bawah batas minimum (%d)!\n",
                                   nama[i], batasMin[i]);
                        }
                    } else {
                        printf("Stok tidak boleh negatif.\n");
                    }
                    ditemukan = 1;
                    break;
                }
            }
            if (ditemukan == 0) {
                printf("Barang dengan ID %d tidak ditemukan.\n", pilihId);
            }
        } else if (pilihan == 0) {
            printf("Keluar dari program. Terima kasih!\n");
        } else {
            printf("Pilihan tidak tersedia.\n");
        }
    }

    return 0;
}
