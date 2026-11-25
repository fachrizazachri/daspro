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
        if (tujuan[i] == '\n') {
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

void tampilkanStok(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                   char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                   double harga[], int n) {
    if (n == 0) {
        printf("\nBelum ada data barang.\n");
        return;
    }
    printf("\n%-4s %-8s %-24s %-6s %-8s %-8s %-12s %-8s\n",
           "No", "Kode", "Nama Barang", "Stok", "Satuan", "Minimum",
           "Harga (Rp)", "Status");
    printf("-----------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-4d %-8s %-24s %-6d %-8s %-8d %-12.0f %-8s\n",
               i + 1, kode[i], nama[i], stok[i], satuan[i], stokMin[i],
               harga[i], stok[i] < stokMin[i] ? "MENIPIS" : "Aman");
    }
}

void cariBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                double harga[], int n) {
    char kunci[LEN_NAMA];
    bacaString("Masukkan kode atau nama barang: ", kunci, sizeof(kunci));

    for (int i = 0; i < n; i++) {
        if (bandingString(kode[i], kunci) == 0 ||
            bandingString(nama[i], kunci) == 0) {
            printf("\nBarang ditemukan:\n");
            printf("  Kode     : %s\n", kode[i]);
            printf("  Nama     : %s\n", nama[i]);
            printf("  Stok     : %d %s\n", stok[i], satuan[i]);
            printf("  Minimum  : %d %s\n", stokMin[i], satuan[i]);
            printf("  Harga    : Rp %.0f / %s\n", harga[i], satuan[i]);
            printf("  Status   : %s\n",
                   stok[i] < stokMin[i] ? "MENIPIS (perlu restock)" : "Aman");
            return;
        }
    }
    printf("Barang \"%s\" tidak ditemukan.\n", kunci);
}

int periksaPeringatan(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                      char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                      int n) {
    int jumlah = 0;
    printf("\n=== PERINGATAN STOK ===\n");
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
    if (n == 0)
        return 0.0;
    return stok[n - 1] * harga[n - 1]
         + hitungTotalRekursif(stok, harga, n - 1);
}

int cariIndeksKode(char kode[][LEN_KODE], int n, const char *kunci) {
    for (int i = 0; i < n; i++)
        if (bandingString(kode[i], kunci) == 0)
            return i;
    return -1;
}

void tambahBarang(char kode[][LEN_KODE], char nama[][LEN_NAMA],
                  char satuan[][LEN_SATUAN], int stok[], int stokMin[],
                  double harga[], int *n) {
    if (*n >= MAX_BARANG) {
        printf("Data penuh (maks %d barang).\n", MAX_BARANG);
        return;
    }

    char kodeBaru[LEN_KODE], namaBaru[LEN_NAMA], satuanBaru[LEN_SATUAN];

    bacaString("Kode barang        : ", kodeBaru, sizeof(kodeBaru));
    if (panjangString(kodeBaru) == 0) {
        printf("Kode tidak boleh kosong.\n");
        return;
    }
    if (cariIndeksKode(kode, *n, kodeBaru) != -1) {
        printf("Kode %s sudah dipakai barang lain.\n", kodeBaru);
        return;
    }
    bacaString("Nama barang        : ", namaBaru, sizeof(namaBaru));
    if (panjangString(namaBaru) == 0) {
        printf("Nama tidak boleh kosong.\n");
        return;
    }
    bacaString("Satuan (pcs/rim/..): ", satuanBaru, sizeof(satuanBaru));

    int    stokBaru    = bacaInt("Jumlah stok        : ", 0);
    int    stokMinBaru = bacaInt("Batas minimum      : ", 0);
    double hargaBaru   = bacaDouble("Harga per satuan(Rp): ", 0);

    int i = *n;
    salinString(kode[i], kodeBaru, LEN_KODE);
    salinString(nama[i], namaBaru, LEN_NAMA);
    salinString(satuan[i], satuanBaru, LEN_SATUAN);
    stok[i]    = stokBaru;
    stokMin[i] = stokMinBaru;
    harga[i]   = hargaBaru;
    (*n)++;

    printf("Barang berhasil ditambahkan.\n");
    if (stokBaru < stokMinBaru)
        printf("[!] Peringatan: stok %s sudah di bawah batas minimum!\n", namaBaru);
}

void ubahStok(char kode[][LEN_KODE], char nama[][LEN_NAMA],
              char satuan[][LEN_SATUAN], int stok[], int stokMin[],
              double harga[], int n) {
    tampilkanStok(kode, nama, satuan, stok, stokMin, harga, n);
    if (n == 0) return;

    int no = bacaInt("\nPilih nomor barang: ", 1);
    if (no > n) {
        printf("Nomor tidak ada.\n");
        return;
    }
    stok[no - 1] = bacaInt("Stok baru: ", 0);
    printf("Stok diperbarui.\n");
    if (stok[no - 1] < stokMin[no - 1])
        printf("[!] Peringatan: stok %s di bawah batas minimum!\n", nama[no - 1]);
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
        printf("\n===== STOK PERSEDIAAN BARANG KAMPUS =====\n");
        printf("1. Lihat semua stok\n");
        printf("2. Cari barang\n");
        printf("3. Tambah barang\n");
        printf("4. Ubah stok barang\n");
        printf("5. Cek peringatan stok minimum\n");
        printf("6. Hitung total nilai persediaan\n");
        printf("0. Keluar\n");
        pilihan = bacaInt("Pilih menu: ", 0);

        switch (pilihan) {
            case 1: tampilkanStok(kode, nama, satuan, stok, stokMin, harga, n); break;
            case 2: cariBarang(kode, nama, satuan, stok, stokMin, harga, n);    break;
            case 3: tambahBarang(kode, nama, satuan, stok, stokMin, harga, &n); break;
            case 4: ubahStok(kode, nama, satuan, stok, stokMin, harga, n);      break;
            case 5: periksaPeringatan(kode, nama, satuan, stok, stokMin, n);    break;
            case 6:
                printf("\nTotal nilai seluruh persediaan: Rp %.0f\n",
                       hitungTotalRekursif(stok, harga, n));
                break;
            case 0: printf("Terima kasih.\n"); break;
            default: printf("Menu tidak tersedia.\n");
        }
    } while (pilihan != 0);

    return 0;
}
