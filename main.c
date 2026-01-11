#include <stdio.h>
#include <string.h>

#define MAX 30
#define NIM_LEN 20

int jumlah = 0;
char nim[MAX][NIM_LEN];
float nilai[MAX][3];

int faktorial(int n) {
    if (n <= 1) return 1;
    return n * faktorial(n - 1);
}

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

float rataMahasiswa(int i) {
    return (nilai[i][0] + nilai[i][1] + nilai[i][2]) / 3.0f;
}

int cariIndexNIM(const char *cari) {
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(nim[i], cari) == 0) return i;
    }
    return -1;
}

void tampilData() {
    if (jumlah == 0) {
        printf("Data masih kosong.\n");
        return;
    }

    printf("\n%-15s %-8s %-8s %-8s %-10s\n", "NIM", "Tugas", "UTS", "UAS", "Rata-rata");
    printf("-------------------------------------------------------\n");

    for (int i = 0; i < jumlah; i++) {
        printf("%-15s %-8.2f %-8.2f %-8.2f %-10.2f\n",
               nim[i], nilai[i][0], nilai[i][1], nilai[i][2], rataMahasiswa(i));
    }
}

void tambahData() {
    if (jumlah >= MAX) {
        printf("Jumlah mahasiswa sudah mencapai batas maksimum.\n");
        return;
    }

    char inputNIM[NIM_LEN];

    printf("Masukkan NIM: ");
    scanf("%19s", inputNIM);

    if (cariIndexNIM(inputNIM) != -1) {
        printf("NIM sudah terdaftar.\n");
        return;
    }

    strcpy(nim[jumlah], inputNIM);

    printf("Nilai Tugas: ");
    scanf("%f", &nilai[jumlah][0]);
    printf("Nilai UTS  : ");
    scanf("%f", &nilai[jumlah][1]);
    printf("Nilai UAS  : ");
    scanf("%f", &nilai[jumlah][2]);

    jumlah++;
    printf("Data berhasil ditambahkan.\n");
}

void ubahData() {
    if (jumlah == 0) {
        printf("Data masih kosong.\n");
        return;
    }

    char cari[NIM_LEN];
    printf("Masukkan NIM yang akan diubah: ");
    scanf("%19s", cari);

    int idx = cariIndexNIM(cari);
    if (idx == -1) {
        printf("Data tidak ditemukan.\n");
        return;
    }

    printf("Nilai Tugas baru: ");
    scanf("%f", &nilai[idx][0]);
    printf("Nilai UTS baru  : ");
    scanf("%f", &nilai[idx][1]);
    printf("Nilai UAS baru  : ");
    scanf("%f", &nilai[idx][2]);

    printf("Data berhasil diubah.\n");
}

void hapusData() {
    if (jumlah == 0) {
        printf("Data masih kosong.\n");
        return;
    }

    char cari[NIM_LEN];
    printf("Masukkan NIM yang akan dihapus: ");
    scanf("%19s", cari);

    int idx = cariIndexNIM(cari);
    if (idx == -1) {
        printf("Data tidak ditemukan.\n");
        return;
    }

    for (int j = idx; j < jumlah - 1; j++) {
        strcpy(nim[j], nim[j + 1]);
        nilai[j][0] = nilai[j + 1][0];
        nilai[j][1] = nilai[j + 1][1];
        nilai[j][2] = nilai[j + 1][2];
    }

    jumlah--;
    printf("Data berhasil dihapus.\n");
}

void olahNilai() {
    if (jumlah == 0) {
        printf("Data masih kosong.\n");
        return;
    }

    float maxRata = rataMahasiswa(0);
    float minRata = rataMahasiswa(0);
    int idxMax = 0, idxMin = 0;

    float sumTugas = 0, sumUTS = 0, sumUAS = 0;

    for (int i = 0; i < jumlah; i++) {
        float rata = rataMahasiswa(i);

        if (rata > maxRata) {
            maxRata = rata;
            idxMax = i;
        }
        if (rata < minRata) {
            minRata = rata;
            idxMin = i;
        }

        sumTugas += nilai[i][0];
        sumUTS += nilai[i][1];
        sumUAS += nilai[i][2];
    }

    printf("\nRata-rata Tugas: %.2f\n", sumTugas / jumlah);
    printf("Rata-rata UTS  : %.2f\n", sumUTS / jumlah);
    printf("Rata-rata UAS  : %.2f\n", sumUAS / jumlah);

    printf("\nMahasiswa dengan rata-rata tertinggi:\n");
    printf("NIM: %s | %.2f\n", nim[idxMax], maxRata);

    printf("\nMahasiswa dengan rata-rata terendah:\n");
    printf("NIM: %s | %.2f\n", nim[idxMin], minRata);
}

void fiturRekursif() {
    printf("\nFaktorial jumlah mahasiswa (%d) = %d\n", jumlah, faktorial(jumlah));
    printf("Deret Fibonacci:\n");
    for (int i = 0; i < jumlah; i++) {
        printf("%d ", fibonacci(i));
    }
    printf("\n");
}

int main() {
    int pilihan;

    do {
        printf("\n=== MENU PROGRAM ===\n");
        printf("1. Tampilkan data mahasiswa\n");
        printf("2. Tambah data mahasiswa\n");
        printf("3. Ubah nilai mahasiswa\n");
        printf("4. Hapus data mahasiswa\n");
        printf("5. Hitung hasil pengolahan nilai\n");
        printf("6. Fitur rekursif\n");
        printf("7. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tampilData(); break;
            case 2: tambahData(); break;
            case 3: ubahData(); break;
            case 4: hapusData(); break;
            case 5: olahNilai(); break;
            case 6: fiturRekursif(); break;
            case 7: printf("Program selesai.\n"); break;
            default: printf("Pilihan tidak valid.\n"); break;
        }
    } while (pilihan != 7);

    return 0;
}
