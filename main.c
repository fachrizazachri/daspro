#include <stdio.h>

#define MAX_BARANG 100
#define LEN_KODE   10
#define LEN_NAMA   50
#define LEN_SATUAN 10

int panjangString(const char *teks) {
    int panjang = 0;
    while (teks[panjang] != '\0')
        panjang++;
    return panjang;
}

int bandingString(const char *kiri, const char *kanan) {
    int i = 0;
    while (kiri[i] != '\0' && kanan[i] != '\0') {
        if (kiri[i] != kanan[i])
            return kiri[i] - kanan[i];
        i++;
    }
    return kiri[i] - kanan[i];
}

void salinString(char *tujuan, const char *sumber, int ukuran) {
    int i = 0;
    if (ukuran <= 0)
        return;

    while (i < ukuran - 1 && sumber[i] != '\0') {
        tujuan[i] = sumber[i];
        i++;
    }
    tujuan[i] = '\0';
}

void bersihkanBuffer(void) {
    char c;
    while (scanf("%c", &c) == 1 && c != '\n') {
    }
}

void bacaString(const char *prompt, char *tujuan, int panjang) {
    fputs(prompt, stdout);
    if (fgets(tujuan, panjang, stdin) == NULL) {
        tujuan[0] = '\0';
        return;
    }
    for (int i = 0; i < panjang && tujuan[i] != '\0'; i++) {
        if (tujuan[i] == '\n' || tujuan[i] == '\r') {
            tujuan[i] = '\0';
            break;
        }
    }
}

int bacaInt(const char *prompt, int min) {
    int nilai;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &nilai) == 1 && nilai >= min) {
            bersihkanBuffer();
            return nilai;
        }
        bersihkanBuffer();
        printf("  Input tidak valid (harus angka >= %d). Coba lagi.\n", min);
    }
}

double bacaDouble(const char *prompt, double min) {
    double nilai;
    while (1) {
        printf("%s", prompt);
        if (scanf("%lf", &nilai) == 1 && nilai >= min) {
            bersihkanBuffer();
            return nilai;
        }
        bersihkanBuffer();
        printf("  Input tidak valid (harus angka >= %.0f). Coba lagi.\n", min);
    }
}

int cariIndeksKode(char kode[][LEN_KODE], int n, const char *kunci) {
    for (int i = 0; i < n; i++) {
        if (bandingString(kode[i], kunci) == 0)
            return i;
    }
    return -1;
}

void tampilDetailBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                        char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                        double harga[], int index) {
    printf("\n====================================\n");
    printf("            DETAIL BARANG\n");
    printf("====================================\n");
    printf("Kode          : %s\n", kode[index]);
    printf("Nama          : %s\n", nama[index]);
    printf("Stok          : %d %s\n", stok[index], satuan[index]);
    printf("Batas Minimum : %d %s\n", stokMin[index], satuan[index]);
    printf("Harga         : Rp %.0f / %s\n", harga[index], satuan[index]);
    printf("Status        : %s\n",
           stok[index] < stokMin[index] ? "MENIPIS (perlu restock)" : "Aman");
    printf("====================================\n");
}

void tambahBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                  char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                  double harga[], int *n) {
    if (*n >= MAX_BARANG) {
        printf("[ERROR] Data penuh (maks %d barang).\n", MAX_BARANG);
        return;
    }

    char kodeBaru[LEN_KODE], namaBaru[LEN_NAMA], satuanBaru[LEN_SATUAN];

    printf("\n============================================\n");
    printf("         TAMBAH DATA ALAT TULIS\n");
    printf("============================================\n");

    while (1) {
        bacaString("Kode barang               : ", kodeBaru, sizeof(kodeBaru));
        if (panjangString(kodeBaru) == 0 || kodeBaru[0] == ' ') {
            printf("[ERROR] Kode tidak boleh kosong atau diawali spasi.\n");
            continue;
        }
        if (cariIndeksKode(kode, *n, kodeBaru) != -1) {
            printf("[ERROR] Kode %s sudah terdaftar! Gunakan kode lain.\n", kodeBaru);
            continue;
        }
        break;
    }

    while (1) {
        bacaString("Nama barang               : ", namaBaru, sizeof(namaBaru));
        if (panjangString(namaBaru) == 0 || namaBaru[0] == ' ') {
            printf("[ERROR] Nama tidak boleh kosong atau diawali spasi.\n");
            continue;
        }
        break;
    }

    bacaString("Satuan (pcs/rim/botol/..) : ", satuanBaru, sizeof(satuanBaru));
    if (panjangString(satuanBaru) == 0) {
        salinString(satuanBaru, "pcs", sizeof(satuanBaru));
    }

    int    stokBaru    = bacaInt("Jumlah stok               : ", 0);
    int    stokMinBaru = bacaInt("Batas minimum             : ", 0);
    double hargaBaru   = bacaDouble("Harga per satuan (Rp)     : ", 0);

    int i = *n;
    salinString(kode[i], kodeBaru, LEN_KODE);
    salinString(nama[i], namaBaru, LEN_NAMA);
    salinString(satuan[i], satuanBaru, LEN_SATUAN);
    stok[i]    = stokBaru;
    stokMin[i] = stokMinBaru;
    harga[i]   = hargaBaru;
    (*n)++;

    printf("\n[SUKSES] Barang \"%s\" berhasil ditambahkan.\n", namaBaru);
    if (stokBaru < stokMinBaru)
        printf("[!] Peringatan: stok %s sudah di bawah batas minimum!\n", namaBaru);
}

void tampilkanStok(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                   char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                   double harga[], int n) {
    if (n == 0) {
        printf("\nBelum ada data barang.\n");
        return;
    }
    printf("\n===================================================================================\n");
    printf("                              DAFTAR PERSEDIAAN ATK\n");
    printf("===================================================================================\n");
    printf("%-4s %-8s %-24s %-6s %-8s %-8s %-12s %-8s\n",
           "No", "Kode", "Nama Barang", "Stok", "Satuan", "Minimum",
           "Harga (Rp)", "Status");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d %-8s %-24s %-6d %-8s %-8d %-12.0f %-8s\n",
               i + 1, kode[i], nama[i], stok[i], satuan[i], stokMin[i],
               harga[i], stok[i] < stokMin[i] ? "MENIPIS" : "Aman");
    }
    printf("-----------------------------------------------------------------------------------\n");
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

void cariBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                double harga[], int n) {
    if (n == 0) {
        printf("\nBelum ada data barang.\n");
        return;
    }
    char kunci[LEN_NAMA];
    bacaString("Masukkan kode atau nama barang: ", kunci, sizeof(kunci));

    for (int i = 0; i < n; i++) {
        if (bandingString(kode[i], kunci) == 0 ||
            bandingString(nama[i], kunci) == 0) {
            tampilDetailBarang(kode, nama, satuan, stok, stokMin, harga, i);
            return;
        }
    }
    printf("Barang \"%s\" tidak ditemukan.\n", kunci);
}

void analisisStok(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                  char satuan[][LEN_SATUAN], int stok[], int n) {
    if (n == 0) {
        printf("\nBelum ada barang yang terdaftar.\n");
        return;
    }

    int *pStok = stok;
    int max = *pStok;
    int min = *pStok;

    for (int i = 1; i < n; i++) {
        if (*(pStok + i) > max)
            max = *(pStok + i);
        if (*(pStok + i) < min)
            min = *(pStok + i);
    }

    printf("\n============================================\n");
    printf("     BARANG DENGAN STOK TERBANYAK (%d)\n", max);
    printf("============================================\n");
    for (int i = 0; i < n; i++) {
        if (*(pStok + i) == max) {
            printf("Kode : %-8s | Nama : %-22s | Stok : %d %s\n",
                   kode[i], nama[i], *(pStok + i), satuan[i]);
        }
    }

    printf("\n============================================\n");
    printf("     BARANG DENGAN STOK TERSEDIKIT (%d)\n", min);
    printf("============================================\n");
    for (int i = 0; i < n; i++) {
        if (*(pStok + i) == min) {
            printf("Kode : %-8s | Nama : %-22s | Stok : %d %s\n",
                   kode[i], nama[i], *(pStok + i), satuan[i]);
        }
    }
}

int periksaPeringatan(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                      char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                      int n) {
    if (n == 0) {
        printf("\nBelum ada data barang.\n");
        return 0;
    }

    int jumlah = 0;
    printf("\n=========================================================================\n");
    printf("                 PERINGATAN STOK DI BAWAH BATAS MINIMUM\n");
    printf("=========================================================================\n");
    for (int i = 0; i < n; i++) {
        if (stok[i] < stokMin[i]) {
            printf("[!] %s - %s: stok %d %s (minimum %d) -> perlu restock minimal %d %s\n",
                   kode[i], nama[i], stok[i], satuan[i], stokMin[i],
                   stokMin[i] - stok[i], satuan[i]);
            jumlah++;
        }
    }
    if (jumlah == 0)
        printf("Semua stok barang masih di atas batas minimum.\n");
    else
        printf("Total %d barang berada di bawah batas minimum.\n", jumlah);
    return jumlah;
}

double hitungTotalRekursif(int stok[], double harga[], int n) {
    if (n <= 0)
        return 0.0;
    return (stok[n - 1] * harga[n - 1]) + hitungTotalRekursif(stok, harga, n - 1);
}

void isiDataContoh(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                   char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                   double harga[], int *n) {
    const char  *kodeC[]   = {"ATK-01", "ATK-02", "ATK-03", "LAB-01", "ELK-01", "ELK-02"};
    const char  *namaC[]   = {"Spidol Whiteboard", "Kertas HVS A4", "Tinta Printer",
                              "Jas Lab", "Kabel HDMI", "Lampu Proyektor"};
    const char  *satuanC[] = {"pcs", "rim", "botol", "pcs", "pcs", "pcs"};
    const int    stokC[]   = {40, 6, 3, 15, 8, 1};
    const int    minC[]    = {20, 10, 5, 10, 5, 2};
    const double hargaC[]  = {12000, 55000, 85000, 120000, 65000, 1500000};
    int jumlah = 6;

    for (int i = 0; i < jumlah; i++) {
        salinString(kode[*n], kodeC[i], LEN_KODE);
        salinString(nama[*n], namaC[i], LEN_NAMA);
        salinString(satuan[*n], satuanC[i], LEN_SATUAN);
        stok[*n]    = stokC[i];
        stokMin[*n] = minC[i];
        harga[*n]   = hargaC[i];
        (*n)++;
    }
}

int main(void) {
    char   kode[MAX_BARANG][LEN_KODE];
    char   nama[MAX_BARANG][LEN_NAMA];
    char   satuan[MAX_BARANG][LEN_SATUAN];
    int    stok[MAX_BARANG];
    int    stokMin[MAX_BARANG];
    double harga[MAX_BARANG];
    int    n = 0;
    int    pilihan;

    isiDataContoh(kode, nama, satuan, stok, stokMin, harga, &n);

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

        pilihan = bacaInt("Masukkan pilihan menu [0-8]: ", 0);

        switch (pilihan) {
            case 1:
                tambahBarang(kode, nama, satuan, stok, stokMin, harga, &n);
                break;

            case 2:
                tampilkanStok(kode, nama, satuan, stok, stokMin, harga, n);
                break;

            case 3: {
                if (n == 0) {
                    printf("\nBelum ada data barang.\n");
                    break;
                }
                char kunci[LEN_KODE];
                bacaString("\nMasukkan kode barang yang ingin ditambah stoknya: ", kunci, sizeof(kunci));
                int idx = cariIndeksKode(kode, n, kunci);
                if (idx == -1) {
                    printf("[ERROR] Barang dengan kode \"%s\" tidak ditemukan.\n", kunci);
                } else {
                    tampilDetailBarang(kode, nama, satuan, stok, stokMin, harga, idx);
                    int tambah = bacaInt("Masukkan jumlah penambahan stok: ", 1);
                    tambahStok(&stok[idx], tambah);
                    printf("\n[SUKSES] Stok %s berhasil ditambah. Stok saat ini: %d %s\n",
                           nama[idx], stok[idx], satuan[idx]);
                }
                break;
            }

            case 4: {
                if (n == 0) {
                    printf("\nBelum ada data barang.\n");
                    break;
                }
                char kunci[LEN_KODE];
                bacaString("\nMasukkan kode barang yang ingin dikurangi stoknya: ", kunci, sizeof(kunci));
                int idx = cariIndeksKode(kode, n, kunci);
                if (idx == -1) {
                    printf("[ERROR] Barang dengan kode \"%s\" tidak ditemukan.\n", kunci);
                } else {
                    tampilDetailBarang(kode, nama, satuan, stok, stokMin, harga, idx);
                    int kurang = bacaInt("Masukkan jumlah pengurangan stok: ", 1);
                    if (kurangiStok(&stok[idx], kurang)) {
                        printf("\n[SUKSES] Stok %s berhasil dikurangi. Sisa stok: %d %s\n",
                               nama[idx], stok[idx], satuan[idx]);
                        if (stok[idx] < stokMin[idx]) {
                            printf("[PERINGATAN] Stok %s di bawah batas minimum (%d %s)!\n",
                                   nama[idx], stokMin[idx], satuan[idx]);
                        }
                    } else {
                        printf("\n[ERROR] Pengurangan gagal! Stok tersedia (%d %s) tidak mencukupi untuk dikurangi %d %s.\n",
                               stok[idx], satuan[idx], kurang, satuan[idx]);
                    }
                }
                break;
            }

            case 5:
                cariBarang(kode, nama, satuan, stok, stokMin, harga, n);
                break;

            case 6:
                analisisStok(kode, nama, satuan, stok, n);
                break;

            case 7:
                periksaPeringatan(kode, nama, satuan, stok, stokMin, n);
                break;

            case 8: {
                if (n == 0) {
                    printf("\nBelum ada data barang.\n");
                    break;
                }
                printf("\n============================================\n");
                printf("       TOTAL NILAI SELURUH PERSEDIAAN\n");
                printf("============================================\n");
                printf("Total Nilai Persediaan: Rp %.0f\n",
                       hitungTotalRekursif(stok, harga, n));
                break;
            }

            case 0:
                printf("\nTerima kasih telah menggunakan program!\n");
                break;

            default:
                printf("\nPilihan tidak valid! Silakan coba lagi.\n");
                break;
        }

    } while (pilihan != 0);

    return 0;
}
