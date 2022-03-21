#ifndef ASSETS_H
#define ASSETS_H

#include <cstdint>
#include <raylib.h>
#include "src/Util.hh"
#include "src/const.hh"

/**
 * Stores pictures and crap.
 */
class Assets {
    public:
        static constexpr Colour const MENU_BG = (Colour){0, 0x0a, 0x3b, 0xff};

        /**
         * Creates the assets object by passing in the font that it shall use.
         * @param font is the font texture that it will use.
         */
        Assets(Texture font);

        /**
         * This should be called periodically so that animated rendering can
         * animate.
         */
        void update();

        /**
         * Draw the given character on the screen at the given point (in
         * character sized coordinates).
         * @param point is where to draw on the screen.
         * @param c is the character.
         * @param fg is the colour of the character.
         * @param bg is the colour to put behind the character.
         */
        void drawChar(Util::Vec point, uint8_t c, Colour fg, Colour bg);

        /**
         * Draw the given string of text starting from the given point with no
         * text wrapping or anything of that sort.
         * @param point is the start point of the text.
         * @param text is the text to write.
         * @param fg is the colour to draw the text characters with.
         * @param bg is the colour to draw behind the text.
         */
        void drawText(Util::Vec point, char const *text, Colour fg, Colour bg);

        /**
         * Draws text and background colour that takes up a specific amount of
         * space, and if the text is too big to fit into the alloted space, it
         * scrolls it over time rather than going onto multiple lines.
         * @param point is where the text starts.
         * @param width is the number of characters that can be shown at once.
         * @param text is the text to write.
         * @param fg is the colour to give to the text characters.
         * @param bg is the colour to draw behind the text.
         */
        void drawMarquee(
            Util::Vec point,
            int width,
            char const *text,
            Colour fg,
            Colour bg
        );

        /**
         * Draws a vertical column with a given height.
         * @param start is the top of the column in characters.
         * @param height is the height of the column.
         * @param startC is the character to use for the start point.
         * @param midC is the character to use for the middle of the line.
         * @param endC is the character to use for the end of the line.
         * @param fg is the colour to draw the characters with.
         * @param bg is the colour to draw behind the characters.
         */
        void drawColumn(
            Util::Vec start,
            int height,
            uint8_t startC,
            uint8_t midC,
            uint8_t endC,
            Colour fg,
            Colour bg
        );

        /**
         * Fills a rectangle with a colou.
         * @param rect is the rectangle to fill.
         * @param colour is the colour to fill it with.
         */
        void drawRect(Util::Rect rect, Colour colour);

    private:
        Texture font;
        Util::Vec charSize;
        Rectangle charSrc;
        unsigned int clock;
};

#endif
