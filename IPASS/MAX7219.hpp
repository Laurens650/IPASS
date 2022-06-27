#ifndef MAX7219_HPP
#define MAX7219_HPP

#include "hwlib.hpp"

/// @file

/// \brief
/// MAX7219 for Led matrix
/// \details
/// This class is a class you can use for a 8x8 ledmatrix
class MAX7219{
private:
    hwlib::spi_bus_bit_banged_sclk_mosi_miso & spi;
    hwlib::pin_out & cs;
    uint8_t brightness;
    uint8_t numbers[20][8] = {{0x00, 0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E, 0x00},  // 0
                              {0x00, 0x00, 0x42, 0x7F, 0x7F, 0x40, 0x00, 0x00},  // 1
                              {0x00, 0x62, 0x73, 0x59, 0x49, 0x6F, 0x66, 0x00},  // 2
                              {0x00, 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00},  // 3
                              {0x18, 0x1C, 0x16, 0x53, 0x7F, 0x7F, 0x50, 0x00},  // 4
                              {0x00, 0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00},  // 5
                              {0x00, 0x3C, 0x7E, 0x4B, 0x49, 0x79, 0x30, 0x00},  // 6
                              {0x00, 0x03, 0x03, 0x71, 0x79, 0x0F, 0x07, 0x00},  // 7
                              {0x00, 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00},  // 8
                              {0x00, 0x06, 0x4F, 0x49, 0x69, 0x3F, 0x1E, 0x00},  // 9
                              {0xFF, 0xC1, 0x80, 0xBE, 0xBE, 0x80, 0xC1, 0xFF},  // 0 inverted
                              {0xFF, 0xFF, 0xBD, 0x80, 0x80, 0xBF, 0xFF, 0xFF},  // 1 inverted
                              {0xFF, 0x9D, 0x8C, 0xA6, 0xB6, 0x90, 0x99, 0xFF},  // 2 inverted
                              {0xFF, 0xDD, 0x9C, 0xB6, 0xB6, 0x80, 0xC9, 0xFF},  // 3 inverted
                              {0xE7, 0xE3, 0xE9, 0xAC, 0x80, 0x80, 0xAF, 0xFF},  // 4 inverted
                              {0xFF, 0xD8, 0x98, 0xBA, 0xBA, 0x82, 0xC2, 0xFF},  // 5 inverted
                              {0xFF, 0xC3, 0x81, 0xB4, 0xB6, 0x86, 0xCF, 0xFF},  // 6 inverted
                              {0xFF, 0xFC, 0xFC, 0x8E, 0x86, 0xF0, 0xF8, 0xFF},  // 7 inverted
                              {0xFF, 0xC9, 0x80, 0xB6, 0xB6, 0x80, 0xC9, 0xFF},  // 8 inverted
                              {0xFF, 0xF9, 0xB0, 0xB6, 0x96, 0xC0, 0xE1, 0xFF}}; // 9 inverted
public:
    /// \brief
    /// MAX7219 constructor
    /// \details
    /// In the constructor you initialize the spi bus and the cs pin, you can also declare the brightness
    MAX7219(hwlib::spi_bus_bit_banged_sclk_mosi_miso & spi, hwlib::pin_out & cs, uint8_t bright);

    /// \brief
    /// setPixel function
    /// \details
    /// In the setPixel function you pass along two variables the first one can be a command or a digit for a collumn
    /// The second variable you can say what the command needs to do or
    /// you can give the hex number of a entire line of 8 pixels.
    void setPixel(uint8_t d_upper, uint8_t d_lower);

    /// \brief
    /// clear function
    /// \details
    /// This function use the setPixel function, it set' the brightness and scan limit,
    /// after that it sets all the pixels to off.
    void clear();

    /// \brief
    /// display function
    /// \details
    /// The display function requires a number to be given to it, once you have given the function a number
    /// it draws it on the led matrix.
    /// To draw the number it reads a raw array and it reads the according number of it.
    void display(unsigned int num);
};

#endif // MAX7219_HPP