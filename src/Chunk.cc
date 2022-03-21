#include "src/Chunk.hh"
#include <cmath>

Chunk::Chunk(unsigned int seed, Util::Vec pos): seed(seed), pos(pos) {

}

void Chunk::hydrate() {
    if (tiles != nullptr) {
        // TODO: emit error
        return;
    }
    tiles = new uint8_t[SIZE * SIZE * LAYERS];
    srand(seed);
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            for (int z = 0; z < LAYERS; z++) {
                if (rand() % 2 == 0) {
                    tiles[z * SIZE * SIZE + y * SIZE + x] = rand() & 0xff;
                } else {
                    tiles[z * SIZE * SIZE + y * SIZE + x] = 0;
                }
            }
        }
    }
    // TODO: the rest.
}

void Chunk::dehydrate() {
    if (tiles == nullptr) {
        // TODO: emit error.
        return;
    }
    delete[] tiles;
    tiles = nullptr;
}

uint8_t Chunk::getTile(Util::Vec point, uint8_t layer) const {
    if (tiles == nullptr) return 0;
    return tiles[layer * SIZE * SIZE + point.y * SIZE + point.x];
}
