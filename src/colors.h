#ifndef COLORS_H
#define COLORS_H

#define LIGHTBLUE(...)  "\033[1;36m" __VA_ARGS__ "\033[0m"
#define LIGHTBLUEOPEN   "\033[1;36m"
#define LIGHTBLUECLOSE  "\033[0m"
#define BLUE(...)       "\033[0;36m" __VA_ARGS__ "\033[0m"
#define BLUEOPEN        "\033[0;36m"
#define BLUECLOSE       "\033[0m"

#define LIGHTGREEN(...) "\033[1;32m" __VA_ARGS__ "\033[0m"
#define LIGHTGREENOPEN  "\033[1;32m"
#define LIGHTGREENCLOSE "\033[0m"
#define GREEN(...)      "\033[0;32m" __VA_ARGS__ "\033[0m"
#define GREENOPEN       "\033[0;32m"
#define GREENCLOSE      "\033[0m"

#define LIGHTRED(...)   "\033[1;31m" __VA_ARGS__ "\033[0m"
#define LIGHTREDOPEN    "\033[1;31m"
#define LIGHTREDCLOSE   "\033[0m"
#define RED(...)        "\033[0;31m" __VA_ARGS__ "\033[0m"
#define REDOPEN         "\033[0;31m"
#define REDCLOSE        "\033[0m"

#define LIGHTPURPLE(...)   "\033[1;35m" __VA_ARGS__ "\033[0m"
#define LIGHTPURPLEOPEN    "\033[1;35m"
#define LIGHTPURPLECLOSE   "\033[0m"
#define PURPLE(...)        "\033[0;35m" __VA_ARGS__ "\033[0m"
#define PURPLEOPEN         "\033[0;35m"
#define PURPLECLOSE        "\033[0m"

#define PURPLEBACKGROUND(...)        "\033[45m" __VA_ARGS__ "\033[0m"
#define PURPLEBACKGROUNDOPEN         "\033[45m"
#define PURPLEBACKGROUNDCLOSE        "\033[0m"

#define COLORCLOSE      "\033[0m"


#endif // !COLORS_H

/*

    Black \033[0;30m



    Yellow \033[0;33m

    Blue \033[0;34m

    Purple \033[0;35m

    Cyan \033[0;36m

    White \033[0;37m

*/
