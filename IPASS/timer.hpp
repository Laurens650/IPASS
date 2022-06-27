
//          Copyright Laurens Richter
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef TIMER_HPP
#define TIMER_HPP

#include "hwlib.hpp"
#include "MAX7219.hpp"

/// @file

/// \brief
/// timer class
/// \details
/// this function use for displays to make a timer
class timer{
private:
    MAX7219 disp_1;
    MAX7219 disp_2;
    MAX7219 disp_3;
    MAX7219 disp_4;
    hwlib::pin_out & beeper;
    hwlib::pin_in & settings_button;
    hwlib::pin_in & plus_button;
    hwlib::pin_in & min_button;
    hwlib::pin_in & start_button;
    hwlib::pin_in & stop_button;

    enum state_t {START_UP, L_DISP, LM_DISP, RM_DISP, R_DISP, DISPTIME, PAUSED, STOPWATCH};
    state_t state = START_UP;
    int delay = 500;
    std::array<int, 4> disp_time;
    std::array<int, 4> num = {0,0,0,0};

    int big_min = 0;
    int small_min = 0;
    int big_sec = 0;
    int small_sec = 0;
    int sec = 0;

    bool pause = false;
    bool stopwatch = false;


public:
    /// \brief
    /// timer constructor
    /// \details
    /// The constructor initialize 4 displays, 1 beeper and 5 buttons, the display are of the the MAX7219
    timer(MAX7219 disp_1, MAX7219 disp_2, MAX7219 disp_3, MAX7219 disp_4,
          hwlib::pin_out & beeper, hwlib::pin_in & settings_button, hwlib::pin_in & plus_button,
          hwlib::pin_in & min_button, hwlib::pin_in & start_button, hwlib::pin_in & stop_button);

    /// \brief
    /// beep function
    /// \details
    /// The beep function makes the beeper play a small tune
    void beep();

    /// \brief
    /// time function
    /// \details
    /// The time fuction splits seconds in minutes and seconds so each screen can display the right number
    /// Once the function has split the time it returns a array
    std::array<int, 4> time(int seconds);

    /// \brief
    /// disp_screens function
    /// \details
    /// The disp_screens function use the time function and use the array of it to display all the numbers correctly
    void disp_screens(int seconds);

    /// \brief
    /// set_num function
    /// \details
    /// This function sets each number for the displays so it can later be used to display the correct number for the settings
    void set_num(int seconds);

    /// \brief
    /// set_screen_time function
    /// \details
    /// This function converts the seperate numbers back to seconds
    void set_screen_time();

    /// \brief
    /// main function
    /// \details
    /// The main function use a switch statement and a enum to switch between different states of the timer
    /// If you press differnt buttons you can switch between states
    /// With the function you can set the time on the timer, the time is set by changing the number on each display
    /// Once you have set the time you can start the timer and if the timer is running you can also pause it
    /// The timer also has a stopwatch function you can use it when the timer doesn't have any time set or has finished
    void main();
};

#endif // TIMER_HPP
