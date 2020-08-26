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
    int grid_width = 40;
    int grid_height = 10;

    int emulated_window_width = grid_width*8;
    int emulated_window_height = grid_height*20;

    int window_width = emulated_window_width*4;
    int window_height = emulated_window_height*4;

    int pixel_size = window_width / emulated_window_width;

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "PPT8 Emulator", sf::Style::Titlebar | sf::Style::Close);
    Runtime runtime = Runtime(emulated_window_width, emulated_window_height, &window);

    bool debug = false;
    std::string file;
    std::string code;

    if (argc == 2)
    {
        if (argv[1] != "debug")
            file = argv[1];
        else
        {
            std::cout << "error: syntax for \"debug\"-mode: ppt8e debug <binary>" << std::endl;
            return 1;
        }
    }
    else if (argc == 3)
    {
        debug = true;
        file = argv[2];
    }
    else
    {
        std::cout << "error: syntax: ppt8e [debug] <binary>" << std::endl;
        return 1;
    }

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

    std::thread([](Runtime* runtime) {
        while (runtime->PROGRAMM_INDEX < 65534) {
            if (!runtime->WAIT_FOR_KEY_PRESS)
            {
                ppt8_std::run_command(runtime->getMemory()->getValueFromAddress(runtime->PROGRAMM_INDEX), &runtime->PROGRAMM_INDEX, runtime);
                runtime->PROGRAMM_INDEX++;
            }
        }
    }, &runtime).detach();

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
        sprite.setScale(4, 4);
        window.draw(sprite);

        window.display();
    }

    return 0;
}