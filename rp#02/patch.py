with open("hello", "r+b") as f:
	addr = 0x11d4
	f.seek(addr)
	f.write(b"\x90\x90")
print("Da patch thanh cong! ./hello /random/ de kiem tra")
