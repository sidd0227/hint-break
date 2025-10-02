#include <iostream>
#include <array>
#include <windows.h>

int main () {
    std::array <uint8_t, 11> shell = { 0x0F, 0x1A, 0x24, 0x4C, 0x30, 0xC0, 0x0F, 0x1B, 0x24, 0x4C, 0xC3 };

    auto mem = VirtualAlloc(0, 0x1000, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    std::memcpy(mem, shell.data(), shell.size());

    using fn = int (__fastcall*)();
    fn func = reinterpret_cast<fn>(mem);
    func ();

    return 0;
}