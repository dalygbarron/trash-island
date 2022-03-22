#include "src/Chunk.hh"
#include <cmath>

Chunk::Chunk(uint64_t seed, Util::Vec pos): seed(seed), pos(pos) {

}

bool Chunk::hydrated() const {
    return tiles != nullptr;
}

void Chunk::hydrate() {
    if (tiles != nullptr) {
        std::cerr << "fuckup in hydrate." << std::endl;
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
                    if (rand() % 100 == 0) {
                        Dude dude(pos * SIZE + Util::Vec(x, y), z);
                        dudes.push_back(dude);
                    }
                }
            }
        }
    }
    // TODO: the rest.
}

void Chunk::dehydrate() {
    if (tiles == nullptr) {
        std::cerr << "fuckup in dehydrate." << std::endl;
        return;
    }
    delete[] tiles;
    tiles = nullptr;
    dudes.clear();
    dudes.shrink_to_fit();
}

uint8_t Chunk::getTile(Util::Vec point, uint8_t layer) const {
    if (tiles == nullptr) return 0;
    return tiles[layer * SIZE * SIZE + point.y * SIZE + point.x];
}
