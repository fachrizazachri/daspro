#include <stdio.h>

int cekKode(int kode) {
  if (kode == 101 || kode == 102 || kode == 103)
    return 1;
  else
    return 0;
}

int tambahStok(int stok, int jumlah) {
  return stok + jumlah;
}

int cekPengurangan(int stok, int jumlah) {
  if (jumlah <= stok)
    return 1;
  else
    return 0;
}

int kurangiStok(int stok, int jumlah) {
  return stok - jumlah;
}

int main(void) {
  int stok101 = 50;  
  int stok102 = 30;  
  int stok103 = 20; 

  int kode, pilihan, jumlah, stok;

  printf("=== PENGELOLAAN STOK BARANG ===\n");
  printf("Daftar barang:\n");
  printf("101 - Stok %d\n", stok101);
  printf("102 - Stok %d\n", stok102);
  printf("103 - Stok %d\n\n", stok103);

  printf("Masukkan kode barang : ");
  scanf("%d", &kode);

  if (cekKode(kode) == 0) {
    printf("Kode barang %d tidak ditemukan. Proses dibatalkan.\n", kode);
    return 0;
  }

  switch (kode) {
    case 101: stok = stok101; break;
    case 102: stok = stok102; break;
    default:  stok = stok103; break;
  }

  printf("\nStok barang %d saat ini : %d\n", kode, stok);
  printf("1. Tambah stok\n");
  printf("2. Kurangi stok\n");
  printf("Masukkan pilihan (1-2) : ");
  scanf("%d", &pilihan);

  if (pilihan == 1) {
    printf("Masukkan jumlah stok yang ditambah : ");
    scanf("%d", &jumlah);

    if (jumlah <= 0) {
      printf("Jumlah harus lebih dari 0.\n");
    } else {
      stok = tambahStok(stok, jumlah);
      printf("Stok berhasil ditambah.\n");
      printf("Stok barang %d sekarang : %d\n", kode, stok);
    }
  } else if (pilihan == 2) {
    printf("Masukkan jumlah stok yang dikurangi : ");
    scanf("%d", &jumlah);

    if (jumlah <= 0) {
      printf("Jumlah harus lebih dari 0.\n");
    } else if (cekPengurangan(stok, jumlah) == 0) {
      printf("Gagal! Jumlah pengurangan (%d) melebihi stok tersedia (%d).\n",
             jumlah, stok);
    } else {
      stok = kurangiStok(stok, jumlah);
      printf("Stok berhasil dikurangi.\n");
      printf("Stok barang %d sekarang : %d\n", kode, stok);
    }
  } else {
    printf("Pilihan tidak valid.\n");
  }

  return 0;
} 