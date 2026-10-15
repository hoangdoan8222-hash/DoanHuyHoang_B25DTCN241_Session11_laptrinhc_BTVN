#include <stdio.h>

struct WarehouseShelf {
    int shelf_id;
    float max_capacity;
    float current_weight;
    int is_cold_storage;
    int item_count;
};

struct PalletItem {
    int pallet_id;
    float weight;
    float required_temp;
};

int add_pallet_to_shelf(struct WarehouseShelf *shelf,
                        struct PalletItem pallet) {
    float new_weight;

    if (shelf == NULL || pallet.weight <= 0.0f) {
        printf("[LOI] Du lieu pallet hoac ke kho khong hop le!\n");
        return 0;
    }

    if (shelf->is_cold_storage == 1) {
        if (pallet.required_temp < -18.0f ||
            pallet.required_temp > 5.0f) {
            printf("[LOI] Nhiet do %.1f degC khong phu hop voi kho lanh!\n",
                   pallet.required_temp);
            return 0;
        }
    }

    new_weight = shelf->current_weight + pallet.weight;

    if (new_weight > shelf->max_capacity) {
        printf("[LOI] Qua tai trong ke kho! "
               "(Du kien: %.1f kg > Toi da: %.1f kg)\n",
               new_weight, shelf->max_capacity);
        return 0;
    }

    shelf->current_weight = new_weight;
    shelf->item_count++;

    printf("[THANH CONG] Nhap kho pallet #%d (%.1f kg) vao ke #%d.\n",
           pallet.pallet_id, pallet.weight, shelf->shelf_id);

    return 1;
}

int main(void) {
    struct WarehouseShelf shelf1 = {101, 500.0f, 420.0f, 1, 3};
    struct PalletItem p1 = {2001, 50.0f, -10.0f};
    struct PalletItem p2 = {2002, 50.0f, 0.0f};

    printf("=== CHUONG TRINH QUAN LY KHO WAREHOUSE LOGISTICS ===\n");
    printf("Ke kho #%d | Tai trong: %.1f/%.1f kg | "
           "Loai: Kho lanh | So luong: %d\n\n",
           shelf1.shelf_id,
           shelf1.current_weight,
           shelf1.max_capacity,
           shelf1.item_count);

    printf("--- Thao tac 1: Nhap Pallet #%d "
           "(50.0 kg, -10.0 degC) ---\n", p1.pallet_id);

    add_pallet_to_shelf(&shelf1, p1);

    printf("-> Trang thai ke kho: Tai trong = %.1f kg | So luong = %d\n\n",
           shelf1.current_weight, shelf1.item_count);

    printf("--- Thao tac 2: Nhap Pallet #%d "
           "(50.0 kg, 0.0 degC) ---\n", p2.pallet_id);

    add_pallet_to_shelf(&shelf1, p2);

    printf("-> Trang thai ke kho sau thao tac 2: "
           "Tai trong = %.1f kg | So luong = %d\n",
           shelf1.current_weight, shelf1.item_count);

    return 0;
}

