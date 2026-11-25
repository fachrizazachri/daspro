# Materi Presentasi — Sistem Pengelolaan Persediaan ATK

Dokumen ini menjadi panduan presentasi dan live coding untuk menjelaskan `main.c`. Program mengelola persediaan alat tulis kampus: menambah dan mencari barang, mengubah stok, melihat peringatan, menganalisis stok, serta menghitung nilai persediaan.

## Urutan presentasi

1. **Abri** — gambaran program dan menu utama.
2. **Fachriza** — menambahkan barang baru.
3. **Jesy** — menampilkan, mencari, dan melihat detail barang.
4. **Feyza** — menambah atau mengurangi stok.
5. **Benny** — menganalisis stok terbanyak dan tersedikit.
6. **Azura** — peringatan stok minimum dan perhitungan nilai persediaan rekursif.

Urutan ini mengikuti alur pemakaian program. Jika pembagian tugas kelompok berbeda, bagian per nama dapat ditukar tanpa mengubah urutan demo.

---

## Abri — Alur program dan menu utama

### Materi

Fungsi `main` menjadi pengendali program. Pertama, program menyiapkan array untuk menyimpan kode, nama, harga, stok, dan batas minimum setiap barang. Variabel `jumlah` mencatat berapa barang yang sudah terisi. Fungsi `isiDataAwal` mengisi beberapa contoh barang agar fitur bisa langsung didemonstrasikan.

Menu berjalan di dalam `do-while`, sehingga ditampilkan berulang kali sampai pengguna memilih `0`. Nilai `pilihan` diproses oleh `switch`; setiap `case` memanggil fungsi yang menangani fitur terkait. Setelah input angka, `bersihkanBuffer` membuang sisa karakter di stdin agar pembacaan input berikutnya tidak terganggu.

### Naskah singkat

> “Program ini adalah sistem persediaan ATK berbasis menu. Data barang disimpan di beberapa array dengan indeks yang saling berpasangan. Fungsi `main` menampilkan menu, membaca pilihan, lalu meneruskan pekerjaan ke fungsi yang sesuai. Perulangan berhenti saat pengguna memilih menu nol.”

### Live coding

1. Tunjukkan deklarasi array dan `jumlah` di `main`.
2. Tunjukkan pemanggilan `isiDataAwal`.
3. Ubah satu teks menu atau tambahkan penjelasan singkat pada salah satu `case`.
4. Jelaskan bahwa `break` mencegah program melanjutkan ke `case` berikutnya.

### Pertanyaan yang mungkin muncul

- **Mengapa memakai `do-while`?** Menu perlu muncul minimal sekali sebelum pilihan dibaca.
- **Apa gunanya `jumlah`?** Menandai bagian array yang berisi data, sehingga perulangan tidak memeriksa semua kapasitas 100 slot.
- **Mengapa ada `bersihkanBuffer` setelah `scanf`?** `scanf` menyisakan newline; newline itu perlu dibuang sebelum `fgets` membaca input teks.

---

## Fachriza — Menambah data barang

### Materi

Fungsi `tambahBarang` menerima array data dan alamat variabel `jumlah`. Sebelum meminta input, program memeriksa apakah kapasitas `MAX_BARANG` sudah penuh. Kode barang harus terisi dan unik; pemeriksaan keunikan menggunakan `cariBarang`. Nama juga tidak boleh kosong. Harga, stok, dan batas minimum dibaca sebagai bilangan bulat yang tidak negatif.

Setelah input lolos validasi, data disimpan pada indeks `*jumlah`. Kode dan nama disalin ke array karakter menggunakan `stringSalin`, sedangkan harga, stok, dan minimum dimasukkan ke array integer. Terakhir, `(*jumlah)++` menambah jumlah data aktif. Tanda `*` menunjukkan bahwa fungsi mengubah nilai `jumlah` milik pemanggil.

### Naskah singkat

> “Fitur tambah barang mengumpulkan lima informasi: kode, nama, harga, stok, dan batas minimum. Validasi mencegah kode kosong atau duplikat serta angka negatif. Setelah valid, semua atribut disimpan pada indeks yang sama agar tetap menjadi satu data barang.”

### Live coding

1. Tunjukkan pengecekan kapasitas dan validasi kode.
2. Tunjukkan validasi angka dengan `scanf` dan syarat `>= 0`.
3. Tunjukkan penyimpanan ke indeks `idx = *jumlah` dan kenaikan `(*jumlah)++`.
4. Saat demo, tambahkan barang dengan kode unik; ulangi dengan kode yang sudah ada untuk memperlihatkan penolakan duplikat.

### Pertanyaan yang mungkin muncul

- **Mengapa `jumlah` dikirim dengan pointer?** Agar fungsi dapat memperbarui jumlah barang yang terlihat oleh `main`.
- **Mengapa kode harus unik?** Agar pencarian berdasarkan kode tidak ambigu.
- **Mengapa batas minimum boleh nol?** Nol adalah nilai valid jika barang tidak memerlukan batas stok minimum.

---

## Jesy — Daftar barang, pencarian, dan detail

### Materi

`tampilBarang` menampilkan seluruh data aktif dari indeks `0` sampai `jumlah - 1`. Status dihitung saat ditampilkan: jika `stok[i] < minimum[i]`, statusnya “MENIPIS”; jika tidak, statusnya “Aman”. Jika `jumlah` nol, fungsi memberi pesan bahwa belum ada data.

`cariBarang` membandingkan kode yang dicari dengan kode pada setiap indeks. Perbandingan dilakukan oleh `stringSama`, yang memeriksa karakter demi karakter sampai terminator string `\0`. Fungsi mengembalikan indeks jika cocok, atau `-1` jika kode tidak ditemukan. `tampilDetailBarang` menggunakan indeks hasil pencarian untuk menampilkan satu barang.

### Naskah singkat

> “Daftar menelusuri data yang sudah terisi dan menghitung status stok saat itu juga. Pencarian memakai kode barang dan menghasilkan indeks. Nilai indeks ini kemudian dipakai untuk menampilkan detail tanpa mencari ulang.”

### Live coding

1. Tunjukkan perulangan `for` di `tampilBarang`.
2. Telusuri kondisi status stok minimum.
3. Tunjukkan nilai `return i` saat kode cocok dan `return -1` saat tidak ditemukan.
4. Demo satu kode yang ada dan satu kode yang tidak ada.

### Pertanyaan yang mungkin muncul

- **Mengapa fungsi pencarian mengembalikan indeks?** Indeks dapat dipakai fungsi lain untuk membaca atau mengubah atribut barang yang sama.
- **Apa arti `\0`?** Penanda akhir pada string C.
- **Apakah pencarian peka huruf besar-kecil?** Ya. Perbandingan karakter saat ini membedakan huruf besar dan kecil.

---

## Feyza — Menambah dan mengurangi stok

### Materi

Menu tambah dan kurangi stok terlebih dahulu meminta kode, lalu memanggil `cariBarang`. Jika barang ditemukan, program meminta jumlah perubahan yang harus lebih dari nol. `tambahStok` menerima alamat stok dan menambahkan nilainya langsung. `kurangiStok` juga menerima pointer, tetapi terlebih dahulu memastikan jumlah pengurangan tidak melebihi stok yang tersedia.

Hasil `kurangiStok` berupa `1` jika berhasil dan `0` jika gagal. Setelah perubahan berhasil, program menampilkan stok terkini. Pengurangan juga memeriksa apakah stok baru berada di bawah minimum dan menampilkan peringatan bila perlu.

### Naskah singkat

> “Perubahan stok dilakukan pada barang yang dipilih berdasarkan kode. Fungsi menerima alamat elemen stok, sehingga perubahan langsung tersimpan di array utama. Pengurangan ditolak jika jumlahnya melebihi stok yang tersedia.”

### Live coding

1. Tunjukkan pemanggilan `tambahStok(&stok[idx], jumlahTambah)`.
2. Jelaskan bahwa `&stok[idx]` adalah alamat elemen stok, lalu tunjukkan perubahan nilai melalui `*stokBarang`.
3. Tunjukkan pemeriksaan `jumlahKurang > *stokBarang` pada `kurangiStok`.
4. Demo tambah stok, pengurangan yang berhasil, dan pengurangan melebihi stok.

### Pertanyaan yang mungkin muncul

- **Mengapa parameter stok berupa pointer?** Supaya fungsi mengubah data asli dalam array, bukan salinan lokal.
- **Apa yang terjadi jika stok tidak cukup?** Fungsi mengembalikan `0`; stok tidak diubah dan program menampilkan pesan gagal.
- **Apakah perubahan stok tersimpan setelah program ditutup?** Belum; data hanya disimpan selama program berjalan.

---

## Benny — Analisis stok tertinggi dan terendah

### Materi

`analisisStok` mencari nilai stok maksimum dan minimum. Jika tidak ada barang, fungsi berhenti setelah menampilkan pesan. Jika data tersedia, pointer `pStok` menunjuk ke elemen pertama array stok. Perulangan membaca nilai berikutnya menggunakan `*(pStok + i)` dan memperbarui `max` atau `min`.

Setelah menemukan kedua nilai, fungsi menelusuri array sekali lagi untuk menampilkan semua barang yang memiliki stok sama dengan maksimum atau minimum. Karena itu, jika beberapa barang seri, semuanya ikut ditampilkan.

### Naskah singkat

> “Analisis stok memakai dua tahap: pertama mencari nilai stok paling tinggi dan paling rendah, lalu menampilkan barang yang memiliki nilai tersebut. Pointer digunakan untuk mengakses elemen array stok, dan nilai seri tetap ditampilkan semua.”

### Live coding

1. Tunjukkan inisialisasi `max` dan `min` dari stok pertama.
2. Telusuri perulangan pembaruan maksimum dan minimum.
3. Tunjukkan dua perulangan output, termasuk dukungan untuk nilai seri.
4. Demo menu analisis dengan data contoh.

### Pertanyaan yang mungkin muncul

- **Mengapa `max` dan `min` dimulai dari elemen pertama?** Agar perbandingan memakai nilai stok yang benar-benar ada, bukan asumsi seperti nol.
- **Apa maksud `*(pStok + i)`?** Mengakses nilai elemen ke-`i` dari alamat awal array.
- **Bagaimana jika stok semua barang sama?** Barang-barang itu akan tampil sebagai stok terbanyak sekaligus tersedikit.

---

## Azura — Peringatan minimum dan total nilai persediaan

### Materi

`periksaPeringatan` menelusuri barang dan membandingkan stok dengan batas minimum. Untuk setiap barang dengan `stok[i] < minimum[i]`, program menghitung kekurangan `minimum[i] - stok[i]` dan menampilkannya. Variabel `count` menghitung jumlah barang yang perlu ditambah stoknya. Jika nilainya nol, program menampilkan bahwa semua stok aman.

`hitungTotalRekursif` menghitung nilai persediaan dengan menjumlahkan `stok[n - 1] * harga[n - 1]` dan memanggil dirinya untuk `n - 1`. Kondisi dasar `n <= 0` mengembalikan nol agar rekursi berhenti. Konversi ke `long long` dilakukan sebelum perkalian agar hasil punya jangkauan lebih besar daripada `int`.

### Naskah singkat

> “Peringatan membandingkan stok dengan minimum dan menghitung berapa unit yang masih kurang. Fitur total nilai menghitung nilai setiap jenis barang, yaitu stok dikali harga, lalu menjumlahkannya secara rekursif sampai seluruh data selesai.”

### Live coding

1. Tunjukkan kondisi `stok[i] < minimum[i]` dan cara menghitung selisih.
2. Tunjukkan kondisi dasar `n <= 0` pada fungsi rekursif.
3. Uraikan satu contoh kecil: untuk `n = 2`, fungsi menghitung barang kedua lalu memanggil dirinya untuk barang pertama.
4. Demo peringatan stok dan total nilai persediaan.

### Pertanyaan yang mungkin muncul

- **Mengapa rekursi perlu kondisi dasar?** Tanpanya pemanggilan fungsi tidak berhenti.
- **Apa rumus total nilai persediaan?** Jumlah dari `stok[i] × harga[i]` untuk setiap barang.
- **Apakah barang dengan stok di bawah minimum otomatis ditambah?** Tidak. Program hanya memberi peringatan; perubahan stok dilakukan lewat menu tambah stok.

---

## Skenario demo bersama

Gunakan alur ini agar setiap fitur saling tersambung:

1. **Abri:** jalankan program dan jelaskan menu.
2. **Fachriza:** tampilkan daftar awal, lalu tambahkan barang baru dengan kode unik.
3. **Jesy:** tampilkan daftar lagi, cari barang yang baru ditambahkan, lalu cari kode yang tidak ada.
4. **Feyza:** tambahkan stok barang; kurangi stok barang lain hingga di bawah minimum; coba juga pengurangan melebihi stok.
5. **Benny:** tampilkan barang dengan stok terbanyak dan tersedikit.
6. **Azura:** tampilkan peringatan minimum dan hitung total nilai persediaan.
7. **Abri:** pilih `0` untuk keluar.

## Ringkasan konsep C yang dibahas

- Array paralel untuk menyimpan atribut barang pada indeks yang sama.
- Fungsi dengan parameter array, nilai balik, dan pointer.
- Perulangan `for`, `while`, dan `do-while`.
- Percabangan `if-else` dan `switch-case`.
- String C dan terminator `\0`.
- Validasi input dengan `scanf` dan pembacaan teks dengan `fgets`.
- Pointer untuk mengubah nilai asli dan mengakses elemen array.
- Rekursi dengan kondisi dasar.
