#include "App.h"
#include <cstdlib>
#include <time.h>

int main()
{
    srand(time(0));

    // Go to Constant.h for configuration
    constant::loadFont();
    App app;
    app.run();
    return 0;
}