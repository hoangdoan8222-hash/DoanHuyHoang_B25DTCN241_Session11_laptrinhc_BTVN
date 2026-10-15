
#include <stdio.h>

typedef struct {
    char ma_kien_hang[20];
    float trong_luong;
    float nhiet_do_yeu_cau;
} PalletItem;

typedef struct {
    char ma_ke[20];
    float trong_luong_hien_tai;
    float tai_trong_toi_da;
    int la_kho_lanh;
} WarehouseShelf;

int kiem_tra_nhap_kho(WarehouseShelf ke, PalletItem kien) {
    if (ke.trong_luong_hien_tai + kien.trong_luong > ke.tai_trong_toi_da) {
        return 0;
    }

    if (ke.la_kho_lanh == 1) {
        if (kien.nhiet_do_yeu_cau >= -18.0 &&
            kien.nhiet_do_yeu_cau <= 5.0) {
            return 1;
        } else {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    WarehouseShelf ke_lanh = {"KE-COLD-01", 350.0, 500.0, 1};

    PalletItem kien_hop_le = {"PL-001", 100.0, -10.0};
    PalletItem kien_sai_nhiet_do = {"PL-002", 80.0, 25.0};
    PalletItem kien_qua_tai = {"PL-003", 200.0, -10.0};

    int ket_qua;

    printf("=== HE THONG KIEM DINH NHAP KHO ===\n");

    printf("\nTEST CASE 1: Kien hang hop le\n");
    ket_qua = kiem_tra_nhap_kho(ke_lanh, kien_hop_le);
    printf("Ma kien: %s\n", kien_hop_le.ma_kien_hang);
    printf("Trong luong: %.1f kg\n", kien_hop_le.trong_luong);
    printf("Nhiet do: %.1f C\n", kien_hop_le.nhiet_do_yeu_cau);
    printf("Tong tai trong: %.1f kg\n",
           ke_lanh.trong_luong_hien_tai + kien_hop_le.trong_luong);

    if (ket_qua == 1) {
        printf("KET QUA: CHO PHEP NHAP KHO!\n");
    } else {
        printf("KET QUA: TU CHOI NHAP KHO!\n");
    }

    printf("\nTEST CASE 2: Kien hang sai nhiet do\n");
    ket_qua = kiem_tra_nhap_kho(ke_lanh, kien_sai_nhiet_do);
    printf("Ma kien: %s\n", kien_sai_nhiet_do.ma_kien_hang);
    printf("Trong luong: %.1f kg\n", kien_sai_nhiet_do.trong_luong);
    printf("Nhiet do: %.1f C\n", kien_sai_nhiet_do.nhiet_do_yeu_cau);

    if (ket_qua == 1) {
        printf("KET QUA: CHO PHEP NHAP KHO!\n");
    } else {
        printf("KET QUA: TU CHOI NHAP KHO!\n");
    }

    printf("\nTEST CASE 3: Kien hang vuot tai trong\n");
    ket_qua = kiem_tra_nhap_kho(ke_lanh, kien_qua_tai);
    printf("Ma kien: %s\n", kien_qua_tai.ma_kien_hang);
    printf("Trong luong: %.1f kg\n", kien_qua_tai.trong_luong);
    printf("Tong tai trong: %.1f kg\n",
           ke_lanh.trong_luong_hien_tai + kien_qua_tai.trong_luong);

    if (ket_qua == 1) {
        printf("KET QUA: CHO PHEP NHAP KHO!\n");
    } else {
        printf("KET QUA: TU CHOI NHAP KHO!\n");
    }

    return 0;
}

