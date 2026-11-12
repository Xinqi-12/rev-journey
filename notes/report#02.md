# Report 02 - Assembly cơ bản và Patching Binary

## Mục tiêu
- Hiểu được các thanh ghi cơ bản trong kiến trúc x86-64.
- Nắm được các lệnh Assembly nền tảng (`mov`, `push`, `pop`, `call`, `cmp`, `jmp`...).
- Thực hành kỹ thuật "Patching Binary" để vô hiệu hóa kiểm tra mật khẩu của chương trình `hello`.

## Công cụ
`objdump`, `grep`, `python3`

## Tóm tắt kiến thức (Cheat Sheet)

### 1. Thanh ghi (Registers)
| Thanh ghi | Chức năng |
| :--- | :--- |
| `rax, rbx, rcx, rdx` | Thanh ghi đa dụng (tính toán, lưu biến). Riêng `rax` thường lưu (return value). |
| `rsp` | Stack Pointer: Trỏ đến đỉnh Stack. Khi `push`, `rsp` - 8 byte. Khi `pop`, `rsp` + 8 byte. |
| `rbp` | Base Pointer: Trỏ đến đáy Stack của hàm hiện tại. |
| `rip` | Instruction Pointer: Trỏ đến dòng code tiếp theo. |
| `rdi, rsi, rdx, rcx, r8, r9` | 6 tham số đầu tiên cho hàm (theo thứ tự). |

### 2. Lệnh Assembly cơ bản
| Lệnh | Chức năng |
| :--- | :--- |
| `mov dest, src` | Gán giá trị `dest = src`. |
| `lea dest, [src]` | Load địa chỉ hiệu dụng. |
| `push src` | Đẩy giá trị vào đỉnh Stack (`rsp - 8`). |
| `pop dest` | Lấy giá trị từ đỉnh Stack ra (`rsp + 8`). |
| `call func` | Gọi hàm. |
| `ret` | Quay lại hàm gọi. |
| `cmp a, b` | So sánh a với b (thực chất là phép trừ `a - b`, nếu bằng nhau thì bật cờ ZF). |
| `jmp, je, jne` | Nhảy không điều kiện / Nhảy nếu bằng (ZF=1) / Nhảy nếu không bằng (ZF=0). |

## Quá trình thực hiện

**Bước 1: Phân tích tĩnh**
Sử dụng `objdump -d -M intel hello` để xem mã Assembly. Tìm hàm `main` và xác định lệnh `je` (Jump if Equal) nằm tại địa chỉ `0x11d4` và chiếm **2 byte** (mã máy là `74 11`).

**Bước 2: Kỹ thuật Patching**
Để vô hiệu hóa ta thay thế 2 byte mã máy của lệnh `je` bằng 2 byte `\x90` (`NOP` - No Operation).
*Lưu ý:* Phải mở file ở chế độ `"r+b"` (đọc và ghi nhị phân) để không làm hỏng cấu trúc file ELF.

Đoạn script Python thực hiện:
```python
with open("hello", "r+b") as f:
    f.seek(0x11d4)        # Di chuyển đến địa chỉ lệnh je
    f.write(b"\x90\x90")  # Ghi đè bằng 2 lệnh NOP
```
**Bước 3: Kiểm tra**
Chạy lệnh ./hello /random/ để kiểm tra kết quả. Dù nhập sai mật khẩu, chương trình vẫn in ra "Correct! You found the secret."