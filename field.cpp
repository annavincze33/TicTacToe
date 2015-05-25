#include "widgets.hpp"
#include "field.hpp"
#include "graphics.hpp"
#include "application.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace genv;
using namespace std;

Field :: Field( int _x, int _y, int _size_x, int _size_y, int _sr, int _sg, int _sb, string _szoveg)
    : Widget ( _x, _y, _size_x, _size_y, _sr, _sg, _sb, _szoveg )
{
    x=_x;
    y=_y;
    sr=_sr;
    sg=_sg;
    sb=_sb;
    size_x=_size_x;
    size_y=_size_y;
    szoveg=_szoveg;

}

void Field::draw(int mouse_x, int mouse_y,event ev)
{

    if (start)
    {
        c.open(size_x,size_y);
        c << move_to(0,0) << color(0,0,0) << box(size_x,size_y);
        gout<<stamp(c,0,0);

        for (int i=0; i<40; i++)
        {
            for (int j=0; j<40; j++)
            {
                gout<<move_to(j*16,i*16)<<color(255,255,255)<<box(14,14);
                doboz.push_back(j);
            }
        }
        start=false;
        for (int i=0; i<doboz.size(); i++)
        {
            doboz[i]=0;
        }
    }
    if(ev.type==ev_mouse && ev.button==-btn_left)
    {
        click=true;
    }
    //cout<<doboz.size()<<endl;
    //for(int i=0;i<doboz.size();i++) cout<<doboz[i]<<endl;
    if(ev.type==ev_mouse && click && piros &&full==false)
    {
        doboz_x=mouse_x/16;
        doboz_y=mouse_y/16;
        if (doboz[doboz_x*40+doboz_y]==0)
        {
            gout<<move_to(doboz_x*16,doboz_y*16)<<color(255,0,0)<<box(14,14);
            doboz[doboz_x*40+doboz_y]=1;
            sum++;
            piros=false;
        }

        click=false;
    }
    if(ev.type==ev_mouse && click && piros==false&&full==false)
    {
        doboz_x=mouse_x/16;
        doboz_y=mouse_y/16;

        if (doboz[doboz_x*40+doboz_y]==0)
        {
            gout<<move_to(doboz_x*16,doboz_y*16)<<color(0,255,0)<<box(14,14);
            doboz[doboz_x*40+doboz_y]=-1;
            sum++;
            piros=true;
        }

        click=false;
    }
    //cout<<doboz_x<<" "<<doboz_y<<endl;
    for(int i=0; i<=doboz.size(); i++)
    {
        if((doboz[i]+doboz[i+1]+doboz[i+2]+doboz[i+3]+doboz[i+4])==5)
        {
            //cout<<"Piros fuggoleges"<<endl;
            redwin=true;
        }
        if((doboz[i]+doboz[i+1]+doboz[i+2]+doboz[i+3]+doboz[i+4])==-5)
        {
            //cout<<"Zold fuggoleges"<<endl;
            greenwin=true;
        }
        if((doboz[i]+doboz[i+40]+doboz[i+80]+doboz[i+120]+doboz[i+160])==5)
        {
            //cout<<"Piros vizszint"<<endl;
            redwin=true;
        }
        if((doboz[i]+doboz[i+40]+doboz[i+80]+doboz[i+120]+doboz[i+160])==-5)
        {
            cout<<"Zold vizszint"<<endl;
            greenwin=true;
        }
        if((doboz[i]+doboz[i+41]+doboz[i+82]+doboz[i+123]+doboz[i+164])==5)
        {
            //cout<<"Piros atlo"<<endl;
            redwin=true;
        }
        if((doboz[i]+doboz[i+41]+doboz[i+82]+doboz[i+123]+doboz[i+164])==-5)
        {
            //cout<<"Zold atlo"<<endl;
            greenwin=true;
        }
        if((doboz[i]+doboz[i+39]+doboz[i+78]+doboz[i+117]+doboz[i+156])==5)
        {
            //cout<<"Piros atlo"<<endl;
            redwin=true;
        }
        if((doboz[i]+doboz[i+39]+doboz[i+78]+doboz[i+117]+doboz[i+156])==-5)
        {
            //cout<<"Zold atlo"<<endl;
            greenwin=true;
        }
    }
    if(sum==1600)
    {
        full=true;
        //cout<<"Betelt a palya"<<endl;
        c.open(size_x,size_y);
        c << move_to(0,0) << color(0,0,0) << box(size_x,size_y)
          <<move_to(size_x/2-50,size_y/2-20) << color(255,0,0) << text("Betelt a palya!")
          <<move_to(size_x/2-80,size_y/2) << color(255,0,0) << text("Új játék jobb gombbal.");
        gout << stamp(c,0,0);

        if(ev.type==ev_mouse && ev.button==btn_right)
        {
            start=true;
            sum=0;
        }
    }
    if(redwin)
    {
        c.open(size_x,size_y);
        c << move_to(0,0) << color(0,0,0) << box(size_x,size_y)
          <<move_to(size_x/2-50,size_y/2-20) << color(255,0,0) << text("Nyert a piros!")
          <<move_to(size_x/2-80,size_y/2) << color(255,0,0) << text("Új játék jobb gombbal.");
        gout << stamp(c,0,0);
        if(ev.type==ev_mouse && ev.button==btn_right)
        {
            start=true;
            redwin=false;
        }
    }
    if(greenwin)
    {
        c.open(size_x,size_y);
        c << move_to(0,0) << color(0,0,0) << box(size_x,size_y)
          <<move_to(size_x/2-50,size_y/2-20) << color(0,255,0) << text("Nyert a zöld.")
          <<move_to(size_x/2-80,size_y/2) << color(0,255,0) << text("Új játék jobb gombbal.");
        gout << stamp(c,0,0);
        if(ev.type==ev_mouse && ev.button==btn_right)
        {
            start=true;
            greenwin=false;
        }
    }
}
