#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Textbox.h"
#pragma once

class WelcomeWindow {
    int windowWidth;
    int windowHeight;
public:
    WelcomeWindow(int windowWidth, int windowHeight);
    string Display();
};
