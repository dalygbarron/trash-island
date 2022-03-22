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
    else if (code == KEY_PERIOD) m = "You wait a moment";
    else return Transition();
    if (m != nullptr) {
        world.addMessage(m);
    }
    world.update();
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
            uint8_t pathing = world.getPath(corner + point);
            Colour colour{0, pathing, (uint8_t)(pathing * 8), 0xff};
            assets.drawChar(
                point,
                world.getTile(corner + point, world.player.getLayer()),
                GREEN,
                colour
            );
        }
    }
    Util::Vec chunkPos = world.player.getPos() / Chunk::SIZE;
    for (int x = chunkPos.x - 1; x <= chunkPos.x + 1; x++) {
        for (int y = chunkPos.y - 1; y <= chunkPos.y + 1; y++) {
            Chunk const &chunk = world.getChunk(Util::Vec(x, y));
            std::vector<Dude>::const_iterator it = chunk.dudes.begin();
            while (it != chunk.dudes.end()) {
                Dude const &dude = *it;
                assets.drawChar(dude.getPos() - corner, 0x01, RED, BLANK);
                it++;
            }
        }
    }
    assets.drawChar(world.player.getPos() - corner, 0x01, BLUE, BLANK);
    assets.drawGameUI(world);
    assets.drawText(Util::Vec(), "Input", WHITE, Assets::MENU_BG);
}
