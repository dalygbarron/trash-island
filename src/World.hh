#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>
#include <deque>
#include "src/Chunk.hh"

/**
 * Contains the whole game world wahooooo.
 */
class World {
    public:
        static constexpr int const PATH_SIZE = 48;
        static constexpr uint8_t const PATH_LIMIT = 0xfe;
        uint64_t const seed;
        Dude player;

        /**
         * Creates the world and sets it's seed.
         * @param seed is the seed to use for chunk generation.
         */
        World(uint64_t seed);

        /**
         * Gives you a const pointer to the given chunk, if it does not yet
         * exist then it shall be created.
         * @param pos is the location of the chunk to get.
         * @return the chunk.
         */
        Chunk const &getChunk(Util::Vec pos) const;

        /**
         * Gives you the given tile regardless of what chunk it resides in. If
         * the chunk is not currently in memory it will be loaded.
         * @param pos is the location of the tile to get.
         * @param layer is the layer to get the tile at.
         * @return the value of the tile.
         */
        uint8_t getTile(Util::Vec pos, uint8_t layer) const;

        /**
         * Gives you the pathing value for the given tile in world coordinates.
         * If there is none then you will get a value of 255. 255 is a known
         * non value which means you are outside the map, the highest possible
         * real value is 254.
         * @param pos is the location to get pathing info for.
         * @return the pathing value, which denotes the walking distance from
         *         the given tile to the tile that the player currently
         *         occupies.
         */
        uint8_t getPath(Util::Vec pos) const;

        /**
         * Tells you what the most efficient direction to move in is from the
         * given position. If the position is beyond the bounds of the pathing
         * map though, then you will get back a vector with no direction.
         * @param pos is the position to check out.
         * @return a vector representing the best direction to go in based on
         *         the pathing map, and yes you can assume that every dimension
         *         of the vector will not exceed a magnitude of 1.
         */
        Util::Vec getPathDirection(Util::Vec pos) const;

        /**
         * Adds a message to the game's message history. In future I should
         * make it store messages from like the last 50 turns or something but
         * for now it's just gonna store the 6 you can see.
         * @param c is the message text, it is copied to new storage and
         *        handled from here.
         */
        void addMessage(char const *c);

        /**
         * Const iterator to start of game messages.
         * @return start iterator.
         */
        std::deque<char *>::const_iterator messagesBegin() const;

        /**
         * Const iterator to end of game messages.
         * @return end iterator.
         */
        std::deque<char *>::const_iterator messagesEnd() const;

        /**
         * Updates the world up until the next time that it is the player
         * character's turn.
         */
        void update();

    private:
        mutable std::unordered_map<Util::Vec, Chunk> chunks;
        mutable std::vector<Chunk *> openChunks;
        std::deque<char *> messages;
        uint8_t pathing[PATH_SIZE * PATH_SIZE];

        /**
         * Generates pathing maps centred around the player's current location.
         */
        void generatePath();
};

#endif
