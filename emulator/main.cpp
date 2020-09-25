#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <thread>

#include "runtime/runtime.hpp"
#include "std/std.hpp"

#include "commands/c_int_v.hpp"

int main(int argc, char* argv[])
{
    bool debug = false;
    bool nogui = false;
    std::string file;
    std::string code;

    std::string str_screen_factor = "4";
    std::string str_scr_width = "320";
    std::string str_scr_height = "200";

    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-nogui") 
            nogui = true;
        else if (std::string(argv[i]) == "debug") 
            debug = true;
        else if (std::string(argv[i]).substr(0, 5) == "-fac=") 
            str_screen_factor = std::string(argv[i]).substr(5, std::string(argv[i]).size());
        else if (std::string(argv[i]).substr(0, 3) == "-w=") 
            str_scr_width = std::string(argv[i]).substr(3, std::string(argv[i]).size());
        else if (std::string(argv[i]).substr(0, 3) == "-h=") 
            str_scr_height = std::string(argv[i]).substr(3, std::string(argv[i]).size());
        else
            file = argv[i];
    }

    std::cout << str_scr_height << std::endl;
    std::cout << str_scr_width << std::endl;

    if (nogui)
    {
        Runtime runtime = Runtime(0, 0);
        runtime.DEBUG = debug;
        std::fstream bin;
        bin.open(file, std::ios::in | std::ios::binary);

        if (!bin.good())
        {
            std::cout << "error: file \"" << file << "\" not found." << std::endl;

            if (!debug)
                return 1;
        }

        code = std::string((std::istreambuf_iterator<char>(bin)), std::istreambuf_iterator<char>());

        for (int i = 0; i < code.size(); i++)
            runtime.getMemory()->setValue(i, code[i]);

        // for (int* i = &runtime.PROGRAMM_INDEX; *i < runtime.PROGRAMM_CODE.size(); runtime.PROGRAMM_INDEX++)
        //    ppt8_std::run_command(code[*i], &runtime.PROGRAMM_CODE, i, &runtime);

        
        while (runtime.PROGRAMM_INDEX < 65534) {
            ppt8_std::run_command(runtime.getMemory()->getValueFromAddress(runtime.PROGRAMM_INDEX), &runtime.PROGRAMM_INDEX, &runtime);
            runtime.PROGRAMM_INDEX++;
        }

        return 0;
    }

    int emulated_window_width = 320;
    int emulated_window_height = 200;

    int scaling_factor = std::stoi(str_screen_factor);
    emulated_window_width = std::stoi(str_scr_width);
    emulated_window_height = std::stoi(str_scr_height);

    std::cout << "screen-width: " << emulated_window_width << std::endl;
    std::cout << "screen-height: " << emulated_window_height << std::endl;
    std::cout << "screen-scaling: " << scaling_factor << std::endl;

    int window_width = emulated_window_width*scaling_factor;
    int window_height = emulated_window_height*scaling_factor;

    int pixel_size = window_width / emulated_window_width;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "PPT8 Emulator", sf::Style::Titlebar | sf::Style::Close);
    Runtime runtime = Runtime(emulated_window_width, emulated_window_height);

    runtime.DEBUG = debug;
    std::fstream bin;
    bin.open(file, std::ios::in | std::ios::binary);

    if (!bin.good())
    {
        std::cout << "error: file \"" << file << "\" not found." << std::endl;

        if (!debug)
            return 1;
    }

    code = std::string((std::istreambuf_iterator<char>(bin)), std::istreambuf_iterator<char>());

    for (int i = 0; i < code.size(); i++)
        runtime.getMemory()->setValue(i, code[i]);

    // for (int* i = &runtime.PROGRAMM_INDEX; *i < runtime.PROGRAMM_CODE.size(); runtime.PROGRAMM_INDEX++)
    //    ppt8_std::run_command(code[*i], &runtime.PROGRAMM_CODE, i, &runtime);

    sf::Texture texture;
    texture.create(emulated_window_width, emulated_window_height);
    sf::Sprite sprite(texture); // needed to draw the texture on screen

    std::thread t1([](Runtime* runtime) {
        while (runtime->PROGRAMM_INDEX < 65534) {
            if (!runtime->WAIT_FOR_KEY_PRESS)
            {
                ppt8_std::run_command(runtime->getMemory()->getValueFromAddress(runtime->PROGRAMM_INDEX), &runtime->PROGRAMM_INDEX, runtime);
                runtime->PROGRAMM_INDEX++;
            }
        }
    }, &runtime);

    if (!nogui)
    {
        t1.detach();

        while (window.isOpen())
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed)
                {
                    runtime.WAIT_FOR_KEY_PRESS = false;
                    runtime.KEY_IS_PRESSED = true;
                    runtime.SHIFT_PRESSED = event.key.shift;
                    runtime.CTRL_PRESSED = event.key.shift;
                    runtime.INPUT_BUFFER = event.key.code;
                }
            }

            runtime.KEY_IS_PRESSED = false;
            texture.update(runtime.getPixelStates());
            sprite.setScale(scaling_factor, scaling_factor);
            window.draw(sprite);

            window.display();
        }
    }
    else
        t1.join();

    return 0;
}