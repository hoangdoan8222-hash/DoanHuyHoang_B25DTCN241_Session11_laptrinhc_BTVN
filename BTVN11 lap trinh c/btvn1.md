# BÁO CÁO DEBUG: HỆ THỐNG KIỂM ĐỊNH AN TOÀN KHO HÀNG

## 1. Mục tiêu bài tập

- Đọc hiểu mã nguồn C có sẵn và phát hiện lỗi logic.
- Phân tích luồng thực thi của chương trình.
- Sửa lỗi toán tử logic và lỗi kiểm tra tải trọng tích lũy.
- Kiểm thử chương trình theo đúng quy tắc an toàn kho vận.

## 2. Phân tích lỗi logic

### 2.1. Lỗi 1: Sai toán tử logic khi kiểm tra nhiệt độ kho lạnh

**Dòng code bị lỗi:**

```c
if (item.temp_celsius < -18.0 && item.temp_celsius > 5.0)
```

**Nguyên nhân:**

Toán tử `&&` yêu cầu cả hai điều kiện phải đúng cùng lúc. Tuy nhiên, một nhiệt độ không thể vừa nhỏ hơn -18°C vừa lớn hơn 5°C. Vì vậy, điều kiện này luôn sai và chương trình bỏ qua các trường hợp nhiệt độ vượt ngoài giới hạn cho phép.

**Cách sửa:**

```c
if (item.temp_celsius < -18.0 || item.temp_celsius > 5.0)
```

Sử dụng toán tử `||` để kiểm tra nhiệt độ nhỏ hơn -18°C hoặc lớn hơn 5°C. Khi vi phạm một trong hai giới hạn, kiện hàng sẽ bị từ chối.

### 2.2. Lỗi 2: Không kiểm tra tổng tải trọng của kệ

**Dòng code bị lỗi:**

```c
if (item.weight_kg > MAX_SHELF_WEIGHT)
```

**Nguyên nhân:**

Chương trình chỉ kiểm tra trọng lượng của kiện hàng mới mà không tính đến trọng lượng hàng hóa đang có trên kệ. Điều này khiến hệ thống chấp nhận kiện hàng dù tổng tải trọng sau khi nhập vượt quá 500 kg.

Ví dụ:

- Tải trọng hiện tại: 400 kg.
- Trọng lượng kiện hàng mới: 150 kg.
- Tổng tải trọng: 400 + 150 = 550 kg.

Tổng tải trọng 550 kg vượt quá giới hạn 500 kg nhưng chương trình cũ vẫn có thể duyệt nhập kho.

**Cách sửa:**

```c
if (shelf.current_weight_kg + item.weight_kg > MAX_SHELF_WEIGHT)
```

Điều kiện mới kiểm tra tổng tải trọng sau khi nhập hàng. Nếu tổng tải trọng lớn hơn 500 kg, hệ thống sẽ từ chối nhập kho. Tổng tải trọng bằng đúng 500 kg vẫn được chấp nhận.

## 3. Truy vết luồng thực thi (Trace Code)

Dữ liệu đầu vào:

| Thuộc tính | Giá trị |
|---|---|
| Mã kệ | 101 |
| Loại kho | Kho lạnh |
| Tải trọng hiện tại | 400 kg |
| Mã kiện hàng | 5001 |
| Trọng lượng kiện hàng | 150 kg |
| Nhiệt độ bảo quản | 12°C |
| Tải trọng tối đa | 500 kg |

### Luồng chạy của chương trình cũ

**Bước 1: Kiểm tra nhiệt độ**

Điều kiện:

```c
12.0 < -18.0 && 12.0 > 5.0
```

Kết quả: Sai.

Chương trình không phát hiện nhiệt độ 12°C vượt quá giới hạn cho phép của kho lạnh.

**Bước 2: Kiểm tra tải trọng**

Điều kiện cũ:

```c
150.0 > 500.0
```

Kết quả: Sai.

Chương trình không tính tổng tải trọng 400 + 150 = 550 kg nên bỏ qua lỗi quá tải.

**Bước 3: Trả về kết quả**

Do cả hai điều kiện kiểm tra đều không phát hiện lỗi, hàm trả về `1`. Chương trình in thông báo duyệt nhập kho dù kiện hàng vi phạm cả hai quy tắc an toàn.

### Luồng chạy sau khi sửa

1. Kiểm tra nhiệt độ: phát hiện 12°C lớn hơn 5°C.
2. Hàm in thông báo lỗi kho lạnh và trả về `0`.
3. Chương trình in kết quả từ chối nhập kho.

Lưu ý: Hàm trả về ngay khi phát hiện lỗi đầu tiên nên trong lần chạy này chưa in thông báo quá tải. Điều kiện kiểm tra tổng tải trọng vẫn được sửa đúng và có thể kiểm thử riêng.

## 4. Các trường hợp kiểm thử (Test Cases)

| Test case | Tải trọng hiện tại | Trọng lượng mới | Nhiệt độ | Kết quả chương trình cũ | Kết quả mong đợi |
|---|---:|---:|---:|---|---|
| TC01: Vi phạm nhiệt độ và quá tải | 400 kg | 150 kg | 12°C | Duyệt | Từ chối |
| TC02: Vi phạm nhiệt độ kho lạnh | 100 kg | 50 kg | 10°C | Duyệt | Từ chối |
| TC03: Vượt tải trọng kệ | 400 kg | 120 kg | 2°C | Duyệt | Từ chối |
| TC04: Tổng tải trọng đúng 500 kg | 400 kg | 100 kg | 2°C | Duyệt | Duyệt |
| TC05: Nhiệt độ tại giới hạn dưới | 100 kg | 50 kg | -18°C | Duyệt | Duyệt |
| TC06: Nhiệt độ tại giới hạn trên | 100 kg | 50 kg | 5°C | Duyệt | Duyệt |

Tất cả test case trên đều sử dụng kệ kho lạnh.

## 5. Source code sau khi sửa

Mã nguồn hoàn chỉnh được lưu trong file `main.c`.

Hai lỗi logic đã được sửa:

- Thay `&&` bằng `||` trong điều kiện kiểm tra nhiệt độ.
- Thay việc chỉ kiểm tra `item.weight_kg` bằng việc kiểm tra tổng `shelf.current_weight_kg + item.weight_kg`.

Chương trình vẫn giữ nguyên cấu trúc chính, các kiểu dữ liệu `PalletItem`, `WarehouseShelf` và hàm `kiem_tra_an_toan_nhap_kho`.

## 6. Kết quả mong đợi sau khi sửa

Với dữ liệu ban đầu, chương trình sẽ in thông báo tương tự:

text
[LOI KHO LANH] Nhiet do bao quan 12.0 C khong dat chuan (-18 C den 5 C)!
=> KET QUA: [TU CHOI] Vi pham quy dinh an toan luu kho!


Kết quả đúng theo nghiệp vụ là từ chối nhập kiện hàng vì nhiệt độ bảo quản không phù hợp với kho lạnh.

## 7. Biên dịch và chạy chương trình

Sử dụng GCC để biên dịch:

bash
gcc -Wall -Wextra -std=c89 main.c -o main


Chạy chương trình trên Windows:

bash
main.exe

Chạy chương trình trên Linux/macOS:

bash
./main


## 8. Cấu trúc thư mục nộp bài

text
HW1_Warehouse_Debug/
├── main.c
└── README.md


## 9. Kết luận

Qua quá trình phân tích và sửa lỗi, chương trình đã khắc phục được hai lỗi logic nghiêm trọng trong kiểm định an toàn kho hàng.

Thứ nhất, điều kiện kiểm tra nhiệt độ kho lạnh đã được sửa để phát hiện đúng các trường hợp nằm ngoài khoảng từ -18°C đến 5°C.

Thứ hai, điều kiện kiểm tra tải trọng đã tính đến tổng trọng lượng hàng hóa hiện có và kiện hàng mới, đảm bảo tổng tải trọng không vượt quá 500 kg.

Sau khi sửa, chương trình đáp ứng các quy tắc nghiệp vụ đã đề ra và có thể được biên dịch bằng GCC.
