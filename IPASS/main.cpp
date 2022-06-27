#include "hwlib.hpp"
#include "MAX7219.hpp"
#include "timer.hpp"
#include <array>

int main(int argc, char **argv){
    WDT->WDT_MR = WDT_MR_WDDIS;

    auto din_1 = hwlib::target::pin_out(hwlib::target::pins::d13);
    auto cs = hwlib::target::pin_out(hwlib::target::pins::d12);
    auto clk = hwlib::target::pin_out(hwlib::target::pins::d11);
    auto din_2 = hwlib::target::pin_out(hwlib::target::pins::d10);
    auto din_3 = hwlib::target::pin_out(hwlib::target::pins::d9);
    auto din_4 = hwlib::target::pin_out(hwlib::target::pins::d8);

    auto beeper = hwlib::target::pin_out(hwlib::target::pins::d7);
    auto settings_button = hwlib::target::pin_in(hwlib::target::pins::d6);
    auto plus_button = hwlib::target::pin_in(hwlib::target::pins::d5);
    auto min_button = hwlib::target::pin_in(hwlib::target::pins::d4);
    auto start_button = hwlib::target::pin_in(hwlib::target::pins::d3);
    auto stop_button = hwlib::target::pin_in(hwlib::target::pins::d2);

    auto spi_1 = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din_1, hwlib::pin_in_dummy);
    auto spi_2 = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din_2, hwlib::pin_in_dummy);
    auto spi_3 = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din_3, hwlib::pin_in_dummy);
    auto spi_4 = hwlib::spi_bus_bit_banged_sclk_mosi_miso(clk, din_4, hwlib::pin_in_dummy);

    MAX7219 disp_1(spi_1, cs, 0x01);
    MAX7219 disp_2(spi_2, cs, 0x01);
    MAX7219 disp_3(spi_3, cs, 0x01);
    MAX7219 disp_4(spi_4, cs, 0x01);
    timer Timer(disp_1, disp_2, disp_3, disp_4, beeper, settings_button,
                plus_button, min_button, start_button, stop_button);

    Timer.main();
}
