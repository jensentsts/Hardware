#include <bits/stdc++.h>
using namespace std;

uint16_t TFTLCD144_RGB888toRGB565(uint32_t RGB888Color){
    uint8_t R = RGB888Color >> 16,
            G = RGB888Color >> 8,
            B = RGB888Color >> 0;
    uint16_t RGB565Color = 0;
    R >>= 3;
    G >>= 2;
    B >>= 3;
    RGB565Color = (R << 11) | (G << 5) | (B << 0);
    return RGB565Color;
}

uint32_t rgb888;
uint32_t r, g, b;

int main(){
    while (true){
        printf("RGB: ");
        cin >> hex;
        cin >> r >> g >> b;
        rgb888 = (r << 16) | (g << 8) | (b << 0);
        printf("565: ");
        cout << "0x" << hex << setiosflags(ios::uppercase) << setfill('0') << setw(4) << TFTLCD144_RGB888toRGB565(rgb888) << endl;
    }
    return 0;
}