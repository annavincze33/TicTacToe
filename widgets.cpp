#include "widgets.hpp"
#include "graphics.hpp"

using namespace genv;
using namespace std;

Widget::Widget( ) {}
Widget::Widget( int _x, int _y, int _size_x, int _size_y, int _sr, int _sg, int _sb, string _szoveg )
{
    x = _x;
    y = _y;
    size_x = _size_x;
    size_y = _size_y;
    sr=_sr;
    sg=_sg;
    sb=_sb;
    szoveg=_szoveg;
}

bool Widget::selected( int mouse_x, int mouse_y ) const
{
    return mouse_x>x && mouse_x<(x+size_x+21) && mouse_y>y && mouse_y<(y+size_y);
}

void Widget::draw(int mouse_x, int mouse_y,event ev)
{
}

void Widget::handle(event ev)
{
}

void Widget::kepbeolvaso (canvas& kep,string kepnev, int& width, int& height)
{
    unsigned short cr, cg, cb;
    ifstream bef(kepnev.c_str());
    if(bef.fail())
    {
        cout << "Hiba! Nem talalhato a file."<<endl;
        exit(1);
    }
    else
    {
        bef >> width >> height;
        kep.open(width,height);
        for(int i=0; i<height; ++i)
        {
            for(int j=0; j<width; ++j)
            {
                bef >> cr >> cg >> cb;
                kep << move_to(j,i) << color(cr,cg,cb) << dot;
            }
        }
    }
}

void Widget::set_number(event ev)
{
}

void Widget::set_focus(bool focus)
{
    _isFocused = focus;
}
