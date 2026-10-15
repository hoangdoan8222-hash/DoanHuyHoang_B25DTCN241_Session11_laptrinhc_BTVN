#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#define SO_NGAY_GIAM_GIA 30
#define TY_LE_GIAM_GIA 0.10

struct LoHang {
    int ma_lo;
    int so_luong;
    double don_gia;
    int so_ngay;
};

int nhap_so_nguyen(const char thong_bao[]) {
    char dong[100];
    char *ket_thuc;
    long gia_tri;

    while (1) {
        printf("%s", thong_bao);

        if (fgets(dong, sizeof(dong), stdin) == NULL) {
            exit(EXIT_FAILURE);
        }

        errno = 0;
        gia_tri = strtol(dong, &ket_thuc, 10);

        while (*ket_thuc == ' ' || *ket_thuc == '\t' ||
               *ket_thuc == '\n' || *ket_thuc == '\r') {
            ket_thuc++;
        }

        if (ket_thuc == dong || *ket_thuc != '\0' ||
            errno == ERANGE || gia_tri < INT_MIN ||
            gia_tri > INT_MAX) {
            printf("Loi: Vui long nhap mot so nguyen hop le!\n");
            continue;
        }

        return (int)gia_tri;
    }
}

double nhap_so_thuc(const char thong_bao[]) {
    char dong[100];
    char *ket_thuc;
    double gia_tri;

    while (1) {
        printf("%s", thong_bao);

        if (fgets(dong, sizeof(dong), stdin) == NULL) {
            exit(EXIT_FAILURE);
        }

        errno = 0;
        gia_tri = strtod(dong, &ket_thuc);

        while (*ket_thuc == ' ' || *ket_thuc == '\t' ||
               *ket_thuc == '\n' || *ket_thuc == '\r') {
            ket_thuc++;
        }

        if (ket_thuc == dong || *ket_thuc != '\0' ||
            errno == ERANGE || !isfinite(gia_tri)) {
            printf("Loi: Vui long nhap mot so thuc hop le!\n");
            continue;
        }

        return gia_tri;
    }
}

struct LoHang nhap_du_lieu_lo_hang(void) {
    struct LoHang lo_hang;

    printf("\n=== NHAP THONG TIN LO HANG ===\n");

    do {
        lo_hang.ma_lo = nhap_so_nguyen("Nhap ma lo hang: ");

        if (lo_hang.ma_lo <= 0) {
            printf("Loi: Ma lo hang phai lon hon 0!\n");
        }
    } while (lo_hang.ma_lo <= 0);

    do {
        lo_hang.so_luong = nhap_so_nguyen("Nhap so luong kien hang: ");

        if (lo_hang.so_luong <= 0) {
            printf("Loi: So luong kien hang phai lon hon 0. Vui long thu lai!\n");
        }
    } while (lo_hang.so_luong <= 0);

    do {
        lo_hang.don_gia = nhap_so_thuc(
            "Nhap don gia moi kien moi ngay (VNÐ): ");

        if (lo_hang.don_gia < 0.0) {
            printf("Loi: Don gia khong duoc am!\n");
        }
    } while (lo_hang.don_gia < 0.0);

    do {
        lo_hang.so_ngay = nhap_so_nguyen("Nhap so ngay luu kho: ");

        if (lo_hang.so_ngay < 0) {
            printf("Loi: So ngay luu kho khong duoc am!\n");
        }
    } while (lo_hang.so_ngay < 0);

    return lo_hang;
}

double tinh_phi_luu_kho(struct LoHang lo_hang,
                        double *ty_le_chiet_khau) {
    double phi_goc;

    phi_goc = (double)lo_hang.so_luong *
              lo_hang.don_gia *
              (double)lo_hang.so_ngay;

    *ty_le_chiet_khau = 0.0;

    /* Chi giam gia khi thoi gian luu kho lon hon 30 ngay */
    if (lo_hang.so_ngay > SO_NGAY_GIAM_GIA) {
        *ty_le_chiet_khau = TY_LE_GIAM_GIA;
    }

    return phi_goc * (1.0 - *ty_le_chiet_khau);
}

void hien_thi_ket_qua(struct LoHang lo_hang,
                      double ty_le_chiet_khau,
                      double tong_phi) {
    printf("\n--- THONG TIN LO HANG %d ---\n", lo_hang.ma_lo);
    printf("So luong: %d kien\n", lo_hang.so_luong);
    printf("Don gia: %.2f VNÐ/kien/ngay\n", lo_hang.don_gia);
    printf("Thoi gian: %d ngay\n", lo_hang.so_ngay);
    printf("Ty le chiet khau: %.0f%%\n",
           ty_le_chiet_khau * 100.0);
    printf("Tong phi luu kho: %.2f VNÐ\n", tong_phi);
}

void hien_thi_menu(void) {
    printf("\n========== WAREHOUSE LOGISTICS ==========\n");
    printf("1. Tinh phi luu kho don hang\n");
    printf("0. Thoat chuong trinh\n");
    printf("=========================================\n");
}

int main(void) {
    int lua_chon;
    int tiep_tuc = 1;
    struct LoHang lo_hang;
    double ty_le_chiet_khau;
    double tong_phi;

    do {
        hien_thi_menu();
        lua_chon = nhap_so_nguyen("Nhap lua chon cua ban: ");

        switch (lua_chon) {
            case 1:
                lo_hang = nhap_du_lieu_lo_hang();

                tong_phi = tinh_phi_luu_kho(
                    lo_hang, &ty_le_chiet_khau);

                if (!isfinite(tong_phi)) {
                    printf("Loi: Tong phi vuot qua gioi han tinh toan!\n");
                    break;
                }

                hien_thi_ket_qua(
                    lo_hang, ty_le_chiet_khau, tong_phi);
                break;

            case 0:
                printf("Cam on ban da su dung he thong!\n");
                tiep_tuc = 0;
                break;

            default:
                printf("Loi: Lua chon khong hop le! Vui long chon 1 hoac 0.\n");
                break;
        }
    } while (tiep_tuc);

    return 0;
}

