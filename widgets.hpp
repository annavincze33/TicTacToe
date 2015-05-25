#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace genv;
using namespace std;

class Widget {
    protected:
        int x, y, size_x, size_y, sr, sg, sb;
        bool _isFocused;

    public:
        string szoveg;
        string radio1, radio2, radio3;
        Widget( int _x, int _y, int _size_x, int _size_y, int _sr, int _sg, int _sb, string _szoveg );
        Widget( int _x, int _y, int _size_x, int _size_y, string _radio1, string _radio2, string _radio3);
        virtual bool selected( int mouse_x, int mouse_y ) const;
        virtual void draw(int mouse_x, int mouse_y,event ev);
        virtual void handle( genv::event ev );
        virtual void kepbeolvaso(canvas& kep, string kepnev, int& width, int& height);
        virtual void set_number(event ev);
        void set_focus(bool focus); // fókusz beállítása
        bool isFocused() const { return _isFocused; }
};

#endif

