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
        unsigned int const seed;
        Dude player;

        /**
         * Creates the world and sets it's seed.
         * @param seed is the seed to use for chunk generation.
         */
        World(unsigned int seed);

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
        std::deque<char *> messages;
        uint8_t pathing[Chunk::SIZE * Chunk::SIZE];
};

#endif
