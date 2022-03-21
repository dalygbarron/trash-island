#include "src/State.hh"
#include <iostream>

Input2DState::Input2DState(World &world, Assets &assets):
    State(world, assets) {

}

State::Transition Input2DState::onKey(int code) {
    char const *m = nullptr;
    if (code == KEY_K) m = world.player.move(Util::Vec(0, -1), world);
    else if (code == KEY_J) m = world.player.move(Util::Vec(0, 1), world);
    else if (code == KEY_H) m = world.player.move(Util::Vec(-1, 0), world);
    else if (code == KEY_L) m = world.player.move(Util::Vec(1, 0), world);
    else if (code == KEY_Y) m = world.player.move(Util::Vec(-1, -1), world);
    else if (code == KEY_U) m = world.player.move(Util::Vec(1, -1), world);
    else if (code == KEY_B) m = world.player.move(Util::Vec(-1, 1), world);
    else if (code == KEY_N) m = world.player.move(Util::Vec(1, 1), world);
    else if (code == KEY_D) m = world.player.info(world);
    if (m != nullptr) world.addMessage(m);
    return Transition();
}

State::Transition Input2DState::onClick(int button) {
    std::cout << "button: " << button << std::endl;
    return Transition();
}

void Input2DState::render() {
    Util::Vec corner = world.player.getPos() - Util::Vec(64, 16);
    for (int x = 0; x < 128; x++) {
        for (int y = 0; y < 32; y++) {
            Util::Vec point(x, y);
            assets.drawChar(
                point,
                world.getTile(corner + point, world.player.getLayer()),
                GREEN,
                DARKGREEN
            );
        }
    }
    assets.drawChar(
        world.player.getPos() - corner,
        0x01,
        RED,
        BLACK
    );
    int i = 0;
    for (auto it = world.messagesBegin(); it != world.messagesEnd(); ++it) {
        assets.drawMarquee(
            Util::Vec(0, 37 - i),
            96,
            *it,
            WHITE,
            Assets::MENU_BG
        );
        i++;
    }
    for (; i < 6; i++) {
        assets.drawMarquee(
            Util::Vec(0, 37 - i),
            96,
            "",
            WHITE,
            Assets::MENU_BG
        );
    }
    assets.drawColumn(
        Util::Vec(96, 32),
        6,
        0xd2,
        0xba,
        0xd0,
        WHITE,
        Assets::MENU_BG
    );
    assets.drawMarquee(
        Util::Vec(97, 32),
        31,
        "\x03""29/39 \x04""40/128 $120",
        WHITE,
        Assets::MENU_BG
    );
    assets.drawMarquee(
        Util::Vec(97, 33),
        31,
        "10PM 18\xf8""C",
        WHITE,
        Assets::MENU_BG
    );
    assets.drawText(Util::Vec(97, 34), "Status: ", WHITE, Assets::MENU_BG);
    assets.drawMarquee(
        Util::Vec(105, 34),
        23,
        "AIDS, Hungry, Pissed, and Gothic",
        WHITE,
        Assets::MENU_BG
    );
    assets.drawMarquee(Util::Vec(97, 35), 31, "", WHITE, Assets::MENU_BG);
    assets.drawMarquee(Util::Vec(97, 36), 31, "", WHITE, Assets::MENU_BG);
    assets.drawMarquee(Util::Vec(97, 37), 31, "", WHITE, Assets::MENU_BG);
    assets.drawText(Util::Vec(), "Input", WHITE, Assets::MENU_BG);
}
