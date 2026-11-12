## Mục tiêu
Tìm ra mật khẩu gốc ẩn giấu trong chương trình (Keygenning) thay vì bypass (patching).

## Công cụ
`checksec`, `gdb`, `strings`, `objdump`

## Quá trình phân tích
1. **Kiểm tra bảo mật:** Dùng `checksec ./crackme` phát hiện file có `PIE enabled` và `No canary`. 
2. **Phân tích động:** Chạy `gdb ./crackme`, dùng lệnh `start` để chương trình nạp vào RAM và dừng tại `main`.
3. **Tìm logic:** Dùng `disas main` phát hiện đoạn Assembly nạp mật khẩu:
   ```assembly
   0x...51c8 <+95>:  movabs $0x3165737265766552,%rax
   0x...51d2 <+105>: mov    %rax,-0x79(%rbp)
   ...
   0x...51f7 <+142>: cmp    %al,%dl
   ```
4. Trích xuất: Đặt breakpoint tại lệnh so sánh b *0x...51f7. Chạy chương trình và nhập một mật khẩu sai bất kỳ.

5. Đọc bộ nhớ: Dùng lệnh x/8cb $rbp-0x79 để đọc 8 byte tại vị trí lưu mật khẩu trên Stack. Kết quả trả về dãy hex tương ứng với chuỗi Reverse1.

## Kết quả
Mật khẩu tìm được là: Reverse1