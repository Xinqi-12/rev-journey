# Thanh ghi (Registers)
rax, rbx, rcx, rdx      : Thanh ghi da dung (tinh toan, luu bien)
rax                     : Thuong luu gia tri return
rsp                     : Tro den dinh Stack
rbp                     : Tro den day Stack hien tai
rip                     : Tro den dong code tiep theo
rdi,    rsi,    rdx,    : Tham so theo thu tu
rcx,    r8,     r9
# Assembly co ban
mov dest, src   : Gan gia tri dest = src
lea dest, [src] : Load dia chi hieu dung
push src        : Day gia tri len dinh Stack    (rsp - 8 byte)
pop dest        : Lay gia tri tu dinh Stack     (rsp + 8 byte)
call func       : Goi ham
ret             : Quay lai ham goi
cmp a, b        : So sanh a voi b (a - b)
jmp, je, jne    : Nhay khong dk/ == / !=

# Muc tieu - Vo hieu kiem tra mat khau file hello
Cong cu         : objdump, grep, python
Qua trinh       : Tim dia chi lenh je (0x11d4), thay no chiem 2 byte, dung python ghi de "\x90\x90>
Ket qua         : ./hello /random/ in "Correct!" toi ghi note 2 vay duoc khong
