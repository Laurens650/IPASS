#include "hwlib.hpp"
#include "timer.hpp"

timer::timer(MAX7219 disp_1, MAX7219 disp_2, MAX7219 disp_3, MAX7219 disp_4,
             hwlib::pin_out &beeper, hwlib::pin_in & settings_button, hwlib::pin_in & plus_button,
             hwlib::pin_in & min_button, hwlib::pin_in & start_button, hwlib::pin_in & stop_button):
    disp_1(disp_1),
    disp_2(disp_2),
    disp_3(disp_3),
    disp_4(disp_4),
    beeper(beeper),
    settings_button(settings_button),
    plus_button(plus_button),
    min_button(min_button),
    start_button(start_button),
    stop_button(stop_button)
{}

void timer::beep() {
    for(int i = 0; i < 3; i++) {
        beeper.write(1);
        hwlib::wait_ms(100);
        beeper.write(0);
        hwlib::wait_ms(100);
    }
    beeper.write(1);
    hwlib::wait_ms(500);
    beeper.write(0);
}

std::array<int, 4> timer::time(int seconds){
    int sec = seconds % 60;
    int min = (seconds - sec) / 60;

    int big_sec = (sec - (sec % 10)) / 10;
    int small_sec = sec % 10;

    int big_min = (min - (min % 10)) / 10;
    int small_min = min % 10;

    std::array<int, 4> time = {big_min, small_min, big_sec, small_sec};
    return  time;
}

void timer::disp_screens(int seconds) {
    disp_time = time(seconds);
    disp_1.display(disp_time[3]);
    disp_2.display(disp_time[2]);
    disp_3.display(disp_time[1]);
    disp_4.display(disp_time[0]);
}

void timer::set_num(int seconds) {
    disp_time = time(seconds);
    num[0] = disp_time[0];
    num[1] = disp_time[1];
    num[2] = disp_time[2];
    num[3] = disp_time[3];
}

void timer::set_screen_time() {
    big_min = (num[0] * 600);
    small_min = (num[1] * 60);
    big_sec = (num[2] * 10);
    small_sec = num[3];
}

void timer::main() {
    for(;;){
        switch (state) {
            case START_UP:{
                disp_screens(0);
                if(settings_button.read() == true){
                    state = L_DISP;
                    hwlib::wait_ms(delay);
                }
                if(start_button.read() == true){
                    state = STOPWATCH;
                    stopwatch = true;
                }
                break;
            }
            case L_DISP:{
                disp_4.display(num[0] + 10);
                if(plus_button.read() == true){
                    num[0]++;
                    if(num[0] > 6){
                        num[0] = 6;
                    }else{
                        disp_4.display(num[0] + 10);
                        hwlib::wait_ms(delay);

                    }
                }
                if(min_button.read() == true){
                    num[0]--;
                    if(num[0] < 0){
                        num[0] = 0;
                    }else {
                        disp_4.display(num[0] + 10);
                        hwlib::wait_ms(delay);
                    }
                }

                if(settings_button.read() == true){
                    disp_4.display(num[0]);
                    set_screen_time();
                    state = LM_DISP;
                    hwlib::wait_ms(delay);
                }
                if(start_button.read() == true){
                    set_screen_time();
                    state = DISPTIME;
                }
                if(stop_button.read() == true){
                    set_num(0);
                    disp_screens(0);
                }
                break;
            }
            case LM_DISP:{
                disp_3.display(num[1] + 10);
                if(num[0] < 6) {
                    if (plus_button.read() == true) {
                        num[1]++;
                        if (num[1] > 9) {
                            num[1] = 9;
                        } else {
                            disp_3.display(num[1] + 10);
                            hwlib::wait_ms(delay);
                        }
                    }
                    if (min_button.read() == true) {
                        num[1]--;
                        if (num[1] < 0) {
                            num[1] = 0;
                        } else {
                            disp_3.display(num[1] + 10);
                            hwlib::wait_ms(delay);
                        }
                    }
                }
                if(settings_button.read() == true){
                    disp_3.display(num[1]);
                    set_screen_time();
                    state = RM_DISP;
                    hwlib::wait_ms(delay);
                }
                if(start_button.read() == true){
                    set_screen_time();
                    state = DISPTIME;
                }
                if(stop_button.read() == true){
                    set_num(0);
                    disp_screens(0);
                }
                break;
            }
            case RM_DISP:{
                disp_2.display(num[2] + 10);
                if(plus_button.read() == true){
                    num[2]++;
                    if(num[2] > 5){
                        num[2] = 5;
                    }else{
                        disp_2.display(num[2] + 10);
                        hwlib::wait_ms(delay);
                    }
                }
                if(min_button.read() == true){
                    num[2]--;
                    if(num[2] < 0){
                        num[2] = 0;
                    }else {
                        disp_2.display(num[2] + 10);
                        hwlib::wait_ms(delay);
                    }
                }
                if(settings_button.read() == true){
                    disp_2.display(num[2]);
                    set_screen_time();
                    state = R_DISP;
                    hwlib::wait_ms(delay);
                }
                if(start_button.read() == true){
                    set_screen_time();
                    state = DISPTIME;
                }
                if(stop_button.read() == true){
                    set_num(0);
                    disp_screens(0);
                }
                break;
            }
            case R_DISP:{
                disp_1.display(num[3] + 10);
                if(plus_button.read() == true){
                    num[3]++;
                    if(num[3] > 9){
                        num[3] = 9;
                    }else{
                        disp_1.display(num[3] + 10);
                        hwlib::wait_ms(delay);
                    }
                }
                if(min_button.read() == true){
                    num[3]--;
                    if(num[3] < 0){
                        num[3] = 0;
                    }else {
                        disp_1.display(num[3] + 10);
                        hwlib::wait_ms(delay);
                    }
                }
                if(settings_button.read() == true){
                    disp_1.display(num[3]);
                    set_screen_time();
                    state = L_DISP;
                    hwlib::wait_ms(delay);
                }
                if(start_button.read() == true){
                    set_screen_time();
                    state = DISPTIME;
                }
                if(stop_button.read() == true){
                    set_num(0);
                    disp_screens(0);
                }
                break;
            }
            case DISPTIME:{
                if(pause == false){
                    sec = big_min + small_min + big_sec + small_sec;
                }
                for(int i = sec; i >= 0; i--){
                    disp_screens(i);
                    if(stop_button.read() == true){
                        state = PAUSED;
                        pause = true;
                        sec = i;
                        break;
                    }
                    hwlib::wait_ms(1000);
                    if(i == 0){
                        beep();
                        set_num(0);
                        set_screen_time();
                        state = START_UP;
                        break;
                    }
                }
            }
            case PAUSED:{
                disp_screens(sec);
                if(start_button.read() == true){
                    if(stopwatch){
                        state = STOPWATCH;
                    }else{
                        state = DISPTIME;
                    }
                }
                if(settings_button.read() == true){
                    pause = false;
                    state = L_DISP;
                    if(stopwatch){
                        set_num(0);
                        set_screen_time();
                        disp_screens(0);
                        stopwatch = false;
                    }else{
                        set_num(sec);
                    }
                    hwlib::wait_ms(delay);
                }
                break;
            }
            case STOPWATCH:{
                for(int i = 0; i < 3600; i++){
                    disp_screens(i);
                    if(stop_button.read() == true){
                        state = PAUSED;
                        pause = true;
                        sec = i;
                        break;
                    }
                    hwlib::wait_ms(1000);
                }
                break;
            }
        }
    }
}
