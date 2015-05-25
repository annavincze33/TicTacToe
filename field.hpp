#ifndef FIELD_HPP_INCLUDED
#define FIELD_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "application.hpp"

#include<sstream>
#include<iostream>
#include <string>
#include <vector>

using namespace std;
using namespace genv;

class Field : public Widget
{
protected:

    bool click=false;
    vector<int>doboz;
    int doboz_x;
    int doboz_y;
    bool start=true;
    bool piros=true;
    int sum=0;
    bool full=false;
    canvas c;
    bool redwin=false;
    bool greenwin=false;

public:
    Field (int _x, int _y, int _size_x, int _size_y, int _sr, int _sg, int _sb, string _szoveg);
    virtual void draw(int mouse_x, int mouse_y,event ev ) ;



};
#endif

