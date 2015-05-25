#include "application.hpp"
#include "graphics.hpp"

using namespace genv;

Application::Application( int _SX, int _SY, std::string _name ) : SX(_SX), SY(_SY), name(_name) {
    isExiting = false;
    focused = -1;
}

void Application::addWidget( Widget *w ) {
    widgets.push_back( w );
}

void Application::run() {
    gout.open( SX, SY );
    gout.set_title( name );

    event ev;
    while( gin>>ev && !isExiting ) {

        if( ev.keycode == key_escape )
            isExiting = true;

        /// Fókusz kezelése
        if( ev.keycode == key_tab && widgets.size() > 0 )   // Tab hatására változik a fókusz
            focused = ( focused + 1 ) % widgets.size();     // körbe jár a már létező widgeteken

        if( ev.type == ev_mouse && ev.button==btn_left  ) { // Bal egér klikk a kiválasztás  (csak bal klikk-kor figyelnek az elemek)
            focused = -1;                                   // Ha semleges helyre történt a klikkelés (nincs ott semmi), akkor megszüntetjük a fókuszt
            for( size_t i=0; i<widgets.size(); i++ ) {      // Minden widget-re megvizsgáljuk, hogy ő van-e választva vagy sem
                if( widgets[i]->selected(ev.pos_x, ev.pos_y) ) {
                        focused = i;
                }
            }
        }

        for( size_t i=0; i<widgets.size(); ++i )            // közöljük a widgetekkel, hogy melyikük van fókuszban
            widgets[i]->set_focus( focused == (int)i );

        /// Eseménykezelés
        //if( focused != -1)                                // csak a fókuszban lévő widget kapja meg az eseményeket
        //    widgets[focused]->handle( ev );

        for( size_t i=0; i<widgets.size(); ++i )            // a vektorban található összes vezérlõ megkapja az eseményeket
            widgets[i]->handle( ev );                       // eseménykezelés widget szinten

        /// Vizualizálás
        //gout << move_to(0, 0) << color(0,0,0) << box(SX, SY);// képernyő törlése
        for( size_t i=0; i<widgets.size(); ++i )
        widgets[i]->draw(ev.pos_x,ev.pos_y,ev);              // képernyő újra rajzolása
        gout << refresh;                                    // képernyő frissítése

    }
}

void Application::shutdown() {
    isExiting = true;                                       // kilépés inicializálása
}
