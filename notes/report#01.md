# Report 01 - Làm quen với Binary và định dạng ELF

## Mục tiêu
- Hiểu bản chất file thực thi (binary) và cấu trúc định dạng ELF trên Linux.
- Biết các section quan trọng trong file ELF.
- Phân biệt Static Analysis (phân tích tĩnh) và Dynamic Analysis (phân tích động).

## Công cụ
`file`, `strings`, `readelf`, `objdump`, `gcc`

## Tóm tắt kiến thức

### 1. Khái niệm cơ bản
| Khái niệm | Giải thích |
| :--- | :--- |
| **Binary** | File thực thi chứa mã máy (machine code) mà CPU hiểu và thực thi trực tiếp. |
| **ELF** | (Executable and Linkable Format) Định dạng file thực thi chuẩn trên Linux (tương tự PE trên Windows). |

### 2. Các section quan trọng trong ELF
| Section | Chức năng |
| :--- | :--- |
| `.text` | Chứa mã máy (code) của chương trình. |
| `.data` | Chứa biến toàn cục đã được khởi tạo. |
| `.bss` | Chứa biến toàn cục chưa khởi tạo. |
| `.rodata` | Chứa hằng số, chuỗi (string literal) - thường bị lộ khi dùng `strings`. |

### 3. Phân loại phân tích
| Loại | Công cụ | Cách hoạt động |
| :--- | :--- | :--- |
| **Static Analysis** | Ghidra, IDA, `objdump`, `strings` | Đọc và phân tích mã tĩnh mà không chạy chương trình. |
| **Dynamic Analysis** | `gdb`, `strace`, `ltrace` | Chạy chương trình và quan sát hành vi, bộ nhớ, thanh ghi. |

## Quá trình thực hiện
1. **Viết và biên dịch:** Tạo file `hello.c` chứa chuỗi `secret` và logic kiểm tra mật khẩu. Biên dịch bằng `gcc -O0 -o hello hello.c`.
2. **Kiểm tra định dạng:** Dùng `file hello` để xác nhận đây là file ELF 64-bit.
3. **Phân tích tĩnh:** 
   - Dùng `readelf -S hello` để xem danh sách các section.
   - Dùng `strings hello | grep REV` để quét chuỗi. Phát hiện chuỗi `secret` bị lộ ra ngoài trong section `.rodata`.
4. **Phân tích động:** Chạy `./hello` và nhập thử để kiểm tra luồng hoạt động.
