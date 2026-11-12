# Report 03 - Làm quen với GDB và Runtime Patching

## Mục tiêu
- Hiểu và sử dụng thành thạo các lệnh cơ bản của GDB (GNU Debugger).
- Quan sát sự thay đổi của thanh ghi trong quá trình thực thi.
- Thực hiện kỹ thuật "Runtime Patching" (thay đổi thanh ghi trực tiếp trong lúc chương trình đang chạy) để bypass kiểm tra mật khẩu.

## Công cụ
`gdb`, `objdump`, `gcc`

## Tóm tắt các lệnh GDB cơ bản
| Lệnh | Chức năng |
| :--- | :--- |
| `gdb ./hello` | Khởi động GDB với file thực thi `hello` |
| `b <tên_hàm>` hoặc `b *<địa_chỉ>` | Đặt breakpoint (điểm dừng) |
| `r <tham_số>` | Chạy chương trình với tham số |
| `i r` | Xem toàn bộ thanh ghi |
| `i r eax` | Xem giá trị thanh ghi cụ thể |
| `x/s <địa_chỉ>` | Xem chuỗi (string) tại địa chỉ |
| `x/4x <địa_chỉ>` | Xem 4 byte dưới dạng hex |
| `si` | Chạy 1 lệnh Assembly (bước vào hàm) |
| `ni` | Chạy qua 1 lệnh (không bước vào hàm con) |
| `c` | Tiếp tục chạy chương trình |
| `q` | Thoát GDB |

## Quá trình thực hành

**Bước 1: Khởi động và đặt breakpoint**
Khởi động GDB với file `hello`, đặt breakpoint tại hàm `check` và chạy chương trình với một mật khẩu sai:
```gdb
gdb ./hello
b check
r wrong
```
**Bước 2: Quan sát thanh ghi**
Sau khi chương trình dừng lại tại hàm check, quan sát giá trị thanh ghi eax (thanh ghi chứa kết quả trả về của hàm strcmp):
```
gdb
i r eax
```
Kết quả trả về là 0x25 (tương đương 37 trong hệ thập phân). Vì 37 != 0, chương trình sẽ hiểu đây là mật khẩu sai.

**Bước 3: Runtime Patching (Bypass)**
Tại thời điểm chương trình đang dừng (ngay trước lệnh test %eax,%eax), sử dụng lệnh set để thay đổi giá trị thanh ghi eax thành 0 (giả lập kết quả strcmp trả về đúng):
```
gdb
set $eax = 0
```
Sau đó, tiếp tục chạy chương trình:
```
gdb
c
```
Dù nhập sai mật khẩu, chương trình vẫn in ra "Correct! You found the secret."