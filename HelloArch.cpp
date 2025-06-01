// HelloArch.cpp
// Кроссплатформенное приложение:
// - под Windows: печатает "Hello from <архитектура>“ каждую секунду
// - под Raspberry Pi (Linux): то же самое + моргает ACT-LED

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__linux__)
    #include <unistd.h>     
    #include <fcntl.h>      
    #include <sys/utsname.h> 
    #include <cstdio>       
#endif

using namespace std;


// Определяем архитектуру
string detect_arch() {
#if defined(_WIN64) || defined(_M_X64)
    return "x86_64 (Windows)";
#elif defined(_WIN32) || defined(_M_IX86)
    return "x86 (Windows)";
#elif defined(__linux__)
    struct utsname buf;
    if (uname(&buf) == 0) {
        return string(buf.machine) + " (Linux)";
    }
    else {
        return "Unknown Linux arch";
    }
#else
    return "Unknown platform";
#endif
}

#if defined(__linux__)

static const char* LED_TRIGGER_PATH = "/sys/class/leds/ACT/trigger";
static const char* LED_BRIGHTNESS_PATH = "/sys/class/leds/ACT/brightness";

// Переводит ACT-LED в ручной режим (trigger="none")
void led_set_manual_mode() {
    int fd = open(LED_TRIGGER_PATH, O_WRONLY);
    if (fd < 0) {
        perror("Ошибка: не удалось открыть LED_TRIGGER_PATH");
        return;
    }
    if (write(fd, "none", 4) < 0) {
        perror("Ошибка: не удалось записать 'none' в trigger");
    }
    close(fd);
}

// Устанавливает яркость ACT-LED: 0 (off) или 1 (on)
void led_set_value(int val) {
    int fd = open(LED_BRIGHTNESS_PATH, O_WRONLY);
    if (fd < 0) {
        perror("Ошибка: не удалось открыть LED_BRIGHTNESS_PATH");
        return;
    }
    const char* buf = (val ? "1" : "0");
    if (write(fd, buf, 1) < 0) {
        perror("Ошибка: не удалось записать brightness");
    }
    close(fd);
}
#endif 

int main() {
    // Определяем архитектуру (Windows или Linux/ARM)
    string arch = detect_arch();

#if defined(__linux__)
    // Переводим ACT-LED в ручной режим (trigger="none")
    led_set_manual_mode();
#endif

    bool led_state = false;  // текущее состояние ACT-LED

    // Бесконечный цикл: каждую секунду выводим и переключаем ACT-LED (на Pi)
    while (true) {
        cout << "Hello from " << arch << endl;

#if defined(__linux__)
        led_state = !led_state;
        led_set_value(led_state ? 1 : 0);
#endif


        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
