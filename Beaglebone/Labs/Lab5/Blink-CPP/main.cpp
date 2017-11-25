/*
MIT License

Copyright (c) 2017 Chris McArthur, prince.chrismc(at)gmail(dot)com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <iostream>
#include <fstream>
#include <thread>

using namespace std::literals;

int main()
{
    std::cout << "Hello World from Blink!" << std::endl;

    std::cout << std::endl << "setting up gpio P9_15!" << std::endl;

    // Activate the GPIO pin controlling the LED
    std::ofstream gpio_setup("/sys/class/gpio/export");
    gpio_setup << "48";
    gpio_setup.close();

    // Set GPIO to an output
    std::ofstream gpio48_dir("/sys/class/gpio/gpio48/direction");
    gpio_setup << "out";
    gpio_setup.close();


    std::ofstream gpio48_value("/sys/class/gpio/gpio48/value");
    for (/*no init*/;/*no cond*/;/*no incr*/)
    {
       gpio48_value << "1"; // turn it on
       std::this_thread::sleep_for(1s);
       gpio48_value << "0"; // turn it off
    }

    return 0;
}
