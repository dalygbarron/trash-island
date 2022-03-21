#include "src/Assets.hh"
#include <cstring>

Assets::Assets(Texture font) {
    this->font = font;
    charSize.x = font.width / 16;
    charSize.y = font.height / 16;
    charSrc.width = charSize.x;
    charSrc.height = charSize.y;
    clock = 0;
}

void Assets::update() {
    clock++;
}

void Assets::drawChar(Util::Vec point, uint8_t c, Colour fg, Colour bg) {
    charSrc.x = (c % 16) * charSize.x;
    charSrc.y = (c >> 4) * charSize.y;
    Util::Vec corner = point * charSize;
    DrawRectangle(corner.x, corner.y, charSize.x, charSize.y, bg);
    DrawTextureRec(font, charSrc, corner.toVector2(), fg);
}

void Assets::drawText(Util::Vec point, char const *text, Colour fg, Colour bg) {
    for (int i = 0; text[i]; i++) {
        drawChar(point, text[i], fg, bg);
        point.x++;
    }
}

void Assets::drawMarquee(
    Util::Vec point,
    int width,
    char const *text,
    Colour fg,
    Colour bg
) {
    size_t length = std::strlen(text);
    if (length <= width) {
        bool showingText = true;
        for (int i = 0; i < width; i++) {
            if (showingText && !text[i]) showingText = false;
            drawChar(point, showingText ? text[i] : 0, fg, bg);
            point.x++;
        }
    } else {
        int gap = width >> 3;
        unsigned int cursor = (clock / 3 + gap + length) % (length + gap);
        for (int i = 0; i < width; i++) {
            drawChar(point, (cursor < length) ? text[cursor] : 0, fg, bg);
            cursor++;
            if (cursor >= length + gap) cursor = 0;
            point.x++;
        }
    }
}

void Assets::drawColumn(
    Util::Vec start,
    int height,
    uint8_t startC,
    uint8_t midC,
    uint8_t endC,
    Colour fg,
    Colour bg
) {
    drawChar(start, startC, fg, bg);
    start.y++;
    for (int i = 1; i < height - 1; i++) {
        drawChar(start, midC, fg, bg);
        start.y++;
    }
    drawChar(start, endC, fg, bg);
}

void Assets::drawRect(Util::Rect rect, Colour colour) {
    DrawRectangleRec((rect * charSize).toRectangle(), colour);
}
