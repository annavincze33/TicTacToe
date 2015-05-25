#include "application.hpp"
#include "field.hpp"

int main()
{

    Application app(638,638,"Tic-Tac-Toe");

    Field * a = new Field(0,0,640,640,0,0,0,"");

    app.addWidget(a);
    app.run();


return 0;
}
