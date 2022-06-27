#include "hwlib.hpp"
#include "MAX7219.hpp"
#include <typeinfo>

MAX7219::MAX7219(hwlib::spi_bus_bit_banged_sclk_mosi_miso &spi, hwlib::pin_out &cs, uint8_t bright):
    spi(spi),
    cs(cs)
{brightness = bright;}

void MAX7219::setPixel(uint8_t d_upper, uint8_t d_lower) {
    auto bus = spi.transaction(cs);
    std::array<uint8_t, 2> tmp = {d_upper, d_lower};
    bus.write(tmp);
}

void MAX7219::clear() {
    setPixel(0x09, 0x00);
    setPixel(0x0A, brightness);
    setPixel(0x0B, 0x07);
    setPixel(0x0C, 0x01);
    setPixel(0x0F, 0x00);
    for(uint8_t col = 1; col < 9; col++){
        setPixel(col, 0x00);
    }
}

void MAX7219::display(unsigned int num) {
    clear();
    if(num > 20){
        hwlib::cout << "over limit" << hwlib::endl;
    }else{
        for(uint8_t col = 1; col < 9; col++){
            setPixel(col, numbers[num][col - 1]);
        }
    }
}


