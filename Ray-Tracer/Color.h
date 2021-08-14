#pragma once

#include "Vec3.h"
#include<fstream>
#include<iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

void write_color(std::ofstream& out, Color pixel_color, int samples_pre_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_pre_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

void extractColors (std::vector<Uint32>& colors, Color& pixel_color, int samples_pre_pixel)
{

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_pre_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    colors[0] = (static_cast<Uint32>(256 * clamp(r, 0.0, 0.999)));
    colors[1] = (static_cast<Uint32>(256 * clamp(g, 0.0, 0.999)));
    colors[2] = (static_cast<Uint32>(256 * clamp(b, 0.0, 0.999)));

   // std::cerr << colors[0] << " " << colors[1] << " " << colors[2] << std::endl;
}
