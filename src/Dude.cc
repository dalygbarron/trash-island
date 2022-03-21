#include "src/Dude.hh"
#include <cstring>
#include "src/World.hh"

char Dude::messageBuffer[];

Util::Vec Dude::getPos() const {
    return pos;
}

uint8_t Dude::getLayer() const {
    return layer;
}

char const *Dude::move(Util::Vec direction, World const &world) {
    uint8_t tile = world.getTile(pos + direction.sign(), layer);
    if (tile != 0) {
        sprintf(messageBuffer, "You bump into a %c.", tile);
        return messageBuffer;
    }
    pos += direction.sign();
    return nullptr;
}

char const *Dude::info(World const &world) {
    sprintf(
        messageBuffer,
        "(%d, %d, %d)",
        world.player.pos.x,
        world.player.pos.y,
        world.player.layer
    );
    return messageBuffer;
}

char const *Dude::update(World const &world) {
    return "The dude does nothing because he is lazy.";
}
