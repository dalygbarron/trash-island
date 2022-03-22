#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>
#include <vector>
#include "src/Util.hh"
#include "src/Dude.hh"

/**
 * Can store a 3d chunk of the world, and can delete it when it's not needed
 * and then regenerate it again later.
 */
class Chunk {
    public:
        static constexpr int const LAYERS = 1;
        static constexpr int const SIZE = 96;

        uint64_t const seed;
        Util::Vec const pos;
        std::vector<Dude> dudes;

        /**
         * Constructor to set seed and pos because it makes no sense for these
         * things to change when the chunk will also store errata that are
         * unique to these things.
         * @param seed is the random seed.
         * @param pos is the location in multiples of chunk size.
         */
        Chunk(uint64_t seed, Util::Vec pos);

        /**
         * Tells you if the chunk is currently hydrated.
         * @return true iff it is.
         */
        bool hydrated() const;

        /**
         * Generates the actual chunk data.
         * @param seed is the random seed to generate with.
         */
        void hydrate();

        /**
         * Unload's the chunk's data from memory.
         */
        void dehydrate();

        /**
         * Gives you the tile at the given point relative to the chunk. If the
         * chunk is not hydrated then this returns 0 every time.
         * @param point is the point relative to the chunk to get the tile at.
         * @param layer is the z layer to get the tile at.
         * @return the code of the tile.
         */
        uint8_t getTile(Util::Vec point, uint8_t layer) const;

    private:
        uint8_t *tiles = nullptr;
};

#endif
