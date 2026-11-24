#include <stdio.h>

#define MAX_BARANG 100
#define LEN_KODE 20
#define LEN_NAMA 50

int stringSama(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

void stringSalin(char tujuan[], const char sumber[]) {
    int i = 0;
    while (sumber[i] != '\0') {
        tujuan[i] = sumber[i];
        i++;
    }
    tujuan[i] = '\0';
}

void bersihkanNewline(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void bersihkanBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int cariBarang(char kode[][LEN_KODE], int jumlah, char kode_cari[]) {
    for (int i = 0; i < jumlah; i++) {
        if (stringSama(kode[i], kode_cari)) {
            return i;
        }
    }
    return -1;
}

void tambahBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                  int harga[], int stok[], int minimum[], int *jumlah) {
    if (*jumlah >= MAX_BARANG) {
        printf("[ERROR] Kapasitas penyimpanan penuh (maksimal %d barang)!\n", MAX_BARANG);
        return;
    }

    char kodeBaru[LEN_KODE];
    char namaBaru[LEN_NAMA];
    int hargaBaru;
    int stokBaru;
    int minimumBaru;

    printf("\n============================================\n");
    printf("         TAMBAH DATA ALAT TULIS\n");
    printf("============================================\n");

    while (1) {
        printf("Masukkan kode barang               : ");
        if (fgets(kodeBaru, sizeof(kodeBaru), stdin) == NULL) continue;
        bersihkanNewline(kodeBaru);

        if (kodeBaru[0] == '\0' || kodeBaru[0] == ' ') {
            printf("[ERROR] Kode barang tidak valid. Silakan coba lagi.\n");
            continue;
        }

        if (cariBarang(kode, *jumlah, kodeBaru) != -1) {
            printf("[ERROR] Kode barang \"%s\" sudah terdaftar! Gunakan kode unik.\n", kodeBaru);
            continue;
        }
        break;
    }

    while (1) {
        printf("Masukkan nama barang               : ");
        if (fgets(namaBaru, sizeof(namaBaru), stdin) == NULL) continue;
        bersihkanNewline(namaBaru);

        if (namaBaru[0] == '\0' || namaBaru[0] == ' ') {
            printf("[ERROR] Nama barang tidak valid. Silakan coba lagi.\n");
            continue;
        }
        break;
    }

    while (1) {
        printf("Masukkan harga barang (Rp)         : ");
        if (scanf("%d", &hargaBaru) == 1 && hargaBaru >= 0) {
            bersihkanBuffer();
            break;
        }
        bersihkanBuffer();
        printf("[ERROR] Harga tidak boleh negatif dan harus berupa angka!\n");
    }

    while (1) {
        printf("Masukkan stok barang               : ");
        if (scanf("%d", &stokBaru) == 1 && stokBaru >= 0) {
            bersihkanBuffer();
            break;
        }
        bersihkanBuffer();
        printf("[ERROR] Stok tidak boleh negatif dan harus berupa angka!\n");
    }

    while (1) {
        printf("Masukkan batas stok minimum        : ");
        if (scanf("%d", &minimumBaru) == 1 && minimumBaru >= 0) {
            bersihkanBuffer();
            break;
        }
        bersihkanBuffer();
        printf("[ERROR] Batas minimum tidak boleh negatif dan harus berupa angka!\n");
    }

    int idx = *jumlah;
    stringSalin(kode[idx], kodeBaru);
    stringSalin(nama[idx], namaBaru);
    harga[idx] = hargaBaru;
    stok[idx] = stokBaru;
    minimum[idx] = minimumBaru;
    (*jumlah)++;

    printf("\n[SUKSES] Barang \"%s\" (%s) berhasil ditambahkan.\n", namaBaru, kodeBaru);
    if (stokBaru < minimumBaru) {
        printf("[PERINGATAN] Stok awal berada di bawah batas minimum!\n");
    }
}

void tampilBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                  int harga[], int stok[], int minimum[], int jumlah) {
    if (jumlah == 0) {
        printf("\nBelum ada data barang!\n");
        return;
    }

    printf("\n=========================================================================\n");
    printf("                          DAFTAR PERSEDIAAN ATK\n");
    printf("=========================================================================\n");
    printf("%-4s %-12s %-24s %-12s %-8s %-10s %-10s\n",
           "No", "Kode", "Nama Barang", "Harga (Rp)", "Stok", "Minimum", "Status");
    printf("-------------------------------------------------------------------------\n");

    for (int i = 0; i < jumlah; i++) {
        printf("%-4d %-12s %-24s %-12d %-8d %-10d %-10s\n",
               i + 1, kode[i], nama[i], harga[i], stok[i], minimum[i],
               stok[i] < minimum[i] ? "MENIPIS" : "Aman");
    }
    printf("-------------------------------------------------------------------------\n");
}

void tampilDetailBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                        int harga[], int stok[], int minimum[], int index) {
    printf("\n====================================\n");
    printf("            DETAIL BARANG\n");
    printf("====================================\n");
    printf("Kode          : %s\n", kode[index]);
    printf("Nama          : %s\n", nama[index]);
    printf("Harga         : Rp%d\n", harga[index]);
    printf("Stok          : %d\n", stok[index]);
    printf("Batas Minimum : %d\n", minimum[index]);
    printf("Status        : %s\n", stok[index] < minimum[index] ? "MENIPIS (Perlu restock)" : "Aman");
    printf("====================================\n");
}

void tambahStok(int *stokBarang, int jumlahTambah) {
    *stokBarang = *stokBarang + jumlahTambah;
}

int kurangiStok(int *stokBarang, int jumlahKurang) {
    if (jumlahKurang > *stokBarang) {
        return 0;
    }
    *stokBarang = *stokBarang - jumlahKurang;
    return 1;
}

void analisisStok(char kode[][LEN_KODE], char nama[][LEN_NAMA], int stok[], int jumlah) {
    if (jumlah == 0) {
        printf("\nBelum ada barang yang terdaftar.\n");
        return;
    }

    int *pStok = stok;
    int max = *pStok;
    int min = *pStok;

    for (int i = 1; i < jumlah; i++) {
        if (*(pStok + i) > max) {
            max = *(pStok + i);
        }
        if (*(pStok + i) < min) {
            min = *(pStok + i);
        }
    }

    printf("\n============================================\n");
    printf("        BARANG DENGAN STOK TERBANYAK (%d)\n", max);
    printf("============================================\n");
    for (int i = 0; i < jumlah; i++) {
        if (*(pStok + i) == max) {
            printf("Kode : %-10s | Nama : %-20s | Stok : %d\n", kode[i], nama[i], *(pStok + i));
        }
    }

    printf("\n============================================\n");
    printf("        BARANG DENGAN STOK TERSEDIKIT (%d)\n", min);
    printf("============================================\n");
    for (int i = 0; i < jumlah; i++) {
        if (*(pStok + i) == min) {
            printf("Kode : %-10s | Nama : %-20s | Stok : %d\n", kode[i], nama[i], *(pStok + i));
        }
    }
}

void periksaPeringatan(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                       int stok[], int minimum[], int jumlah) {
    if (jumlah == 0) {
        printf("\nBelum ada data barang.\n");
        return;
    }

    int count = 0;
    printf("\n=========================================================================\n");
    printf("                  PERINGATAN STOK DI BAWAH BATAS MINIMUM\n");
    printf("=========================================================================\n");

    for (int i = 0; i < jumlah; i++) {
        if (stok[i] < minimum[i]) {
            int selisih = minimum[i] - stok[i];
            printf("[!] Kode: %-8s | Nama: %-20s | Stok: %-4d | Minimum: %-4d | Kurang: %d\n",
                   kode[i], nama[i], stok[i], minimum[i], selisih);
            count++;
        }
    }

    if (count == 0) {
        printf("Semua stok barang dalam kondisi aman (di atas batas minimum).\n");
    } else {
        printf("-------------------------------------------------------------------------\n");
        printf("Total %d barang membutuhkan penambahan stok segera!\n", count);
    }
}

long long hitungTotalRekursif(int stok[], int harga[], int n) {
    if (n <= 0) {
        return 0;
    }
    return ((long long)stok[n - 1] * (long long)harga[n - 1]) + hitungTotalRekursif(stok, harga, n - 1);
}

void isiDataAwal(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                 int harga[], int stok[], int minimum[], int *jumlah) {
    const char kodeContoh[][LEN_KODE] = {"B001", "P001", "S001", "K001", "T001"};
    const char namaContoh[][LEN_NAMA] = {"Buku Tulis", "Pulpen Gel", "Pensil 2B", "Kertas HVS A4", "Tinta Spidol"};
    const int hargaContoh[] = {5000, 3500, 2000, 48000, 15000};
    const int stokContoh[] = {25, 8, 50, 4, 3};
    const int minContoh[] = {10, 15, 20, 10, 5};
    int nContoh = 5;

    for (int i = 0; i < nContoh; i++) {
        stringSalin(kode[*jumlah], kodeContoh[i]);
        stringSalin(nama[*jumlah], namaContoh[i]);
        harga[*jumlah] = hargaContoh[i];
        stok[*jumlah] = stokContoh[i];
        minimum[*jumlah] = minContoh[i];
        (*jumlah)++;
    }
}

int main(void) {
    char kode[MAX_BARANG][LEN_KODE];
    char nama[MAX_BARANG][LEN_NAMA];
    int harga[MAX_BARANG];
    int stok[MAX_BARANG];
    int minimum[MAX_BARANG];
    int jumlah = 0;
    int pilihan;

    isiDataAwal(kode, nama, harga, stok, minimum, &jumlah);

    do {
        printf("\n============================================\n");
        printf("     SISTEM PENGELOLAAN PERSEDIAAN\n");
        printf("             ALAT TULIS KAMPUS\n");
        printf("============================================\n");
        printf("1. Tambah Data Alat Tulis Baru\n");
        printf("2. Tampilkan Seluruh Daftar Alat Tulis\n");
        printf("3. Tambah Stok Barang\n");
        printf("4. Kurangi Stok Barang\n");
        printf("5. Cari Barang Berdasarkan Kode\n");
        printf("6. Tampilkan Barang Stok Terbanyak & Tersedikit\n");
        printf("7. Tampilkan Peringatan Stok di Bawah Batas Minimum\n");
        printf("8. Hitung Total Nilai Persediaan\n");
        printf("0. Keluar\n");
        printf("--------------------------------------------\n");
        printf("Masukkan pilihan menu [0-8]: ");

        if (scanf("%d", &pilihan) != 1) {
            bersihkanBuffer();
            printf("\n[ERROR] Pilihan tidak valid! Masukkan angka 0-8.\n");
            continue;
        }
        bersihkanBuffer();

        switch (pilihan) {
            case 1:
                tambahBarang(kode, nama, harga, stok, minimum, &jumlah);
                break;

            case 2:
                tampilBarang(kode, nama, harga, stok, minimum, jumlah);
                break;

            case 3: {
                if (jumlah == 0) {
                    printf("\nBelum ada data barang!\n");
                    break;
                }
                char kodeCari[LEN_KODE];
                printf("\n--- PENAMBAHAN STOK ---\n");
                printf("Masukkan kode barang yang ingin ditambah stoknya: ");
                if (fgets(kodeCari, sizeof(kodeCari), stdin) == NULL) break;
                bersihkanNewline(kodeCari);

                int idx = cariBarang(kode, jumlah, kodeCari);
                if (idx == -1) {
                    printf("[ERROR] Barang dengan kode \"%s\" tidak ditemukan.\n", kodeCari);
                } else {
                    tampilDetailBarang(kode, nama, harga, stok, minimum, idx);
                    int jumlahTambah;
                    while (1) {
                        printf("Masukkan jumlah penambahan stok: ");
                        if (scanf("%d", &jumlahTambah) == 1 && jumlahTambah > 0) {
                            bersihkanBuffer();
                            break;
                        }
                        bersihkanBuffer();
                        printf("[ERROR] Jumlah penambahan harus berupa angka lebih dari 0!\n");
                    }
                    tambahStok(&stok[idx], jumlahTambah);
                    printf("\n[SUKSES] Stok %s berhasil ditambah. Stok saat ini: %d\n", nama[idx], stok[idx]);
                }
                break;
            }

            case 4: {
                if (jumlah == 0) {
                    printf("\nBelum ada data barang!\n");
                    break;
                }
                char kodeCari[LEN_KODE];
                printf("\n--- PENGURANGAN STOK ---\n");
                printf("Masukkan kode barang yang ingin dikurangi stoknya: ");
                if (fgets(kodeCari, sizeof(kodeCari), stdin) == NULL) break;
                bersihkanNewline(kodeCari);

                int idx = cariBarang(kode, jumlah, kodeCari);
                if (idx == -1) {
                    printf("[ERROR] Barang dengan kode \"%s\" tidak ditemukan.\n", kodeCari);
                } else {
                    tampilDetailBarang(kode, nama, harga, stok, minimum, idx);
                    int jumlahKurang;
                    while (1) {
                        printf("Masukkan jumlah pengurangan stok: ");
                        if (scanf("%d", &jumlahKurang) == 1 && jumlahKurang > 0) {
                            bersihkanBuffer();
                            break;
                        }
                        bersihkanBuffer();
                        printf("[ERROR] Jumlah pengurangan harus berupa angka lebih dari 0!\n");
                    }
                    if (kurangiStok(&stok[idx], jumlahKurang)) {
                        printf("\n[SUKSES] Stok %s berhasil dikurangi. Sisa stok: %d\n", nama[idx], stok[idx]);
                        if (stok[idx] < minimum[idx]) {
                            printf("[PERINGATAN] Stok %s saat ini berada di bawah batas minimum (%d)!\n", nama[idx], minimum[idx]);
                        }
                    } else {
                        printf("\n[ERROR] Pengurangan gagal! Stok tersedia (%d) tidak mencukupi untuk dikurangi %d.\n", stok[idx], jumlahKurang);
                    }
                }
                break;
            }

            case 5: {
                if (jumlah == 0) {
                    printf("\nBelum ada data barang!\n");
                    break;
                }
                char kodeCari[LEN_KODE];
                printf("\nMasukkan kode barang yang dicari: ");
                if (fgets(kodeCari, sizeof(kodeCari), stdin) == NULL) break;
                bersihkanNewline(kodeCari);

                int idx = cariBarang(kode, jumlah, kodeCari);
                if (idx == -1) {
                    printf("[INFO] Barang dengan kode \"%s\" tidak ditemukan.\n", kodeCari);
                } else {
                    tampilDetailBarang(kode, nama, harga, stok, minimum, idx);
                }
                break;
            }

            case 6:
                analisisStok(kode, nama, stok, jumlah);
                break;

            case 7:
                periksaPeringatan(kode, nama, stok, minimum, jumlah);
                break;

            case 8: {
                if (jumlah == 0) {
                    printf("\nBelum ada data barang!\n");
                    break;
                }
                long long totalNilai = hitungTotalRekursif(stok, harga, jumlah);
                printf("\n============================================\n");
                printf("       TOTAL NILAI SELURUH PERSEDIAAN\n");
                printf("============================================\n");
                printf("Total Nilai Persediaan: Rp%lld\n", totalNilai);
                break;
            }

            case 0:
                printf("\nTerima kasih telah menggunakan Sistem Pengelolaan Persediaan ATK!\n");
                break;

            default:
                printf("\n[ERROR] Pilihan menu tidak valid! Silakan pilih menu yang tersedia.\n");
                break;
        }

    } while (pilihan != 0);

    return 0;
}
