#ifndef DUDE_H
#define DUDE_H

#include <vector>
#include "src/Util.hh"
#include "src/Item.hh"

// Forward declaration of World.
class World;

/**
 * An active agent in the game world that can perform all the same actions that
 * the player can.
 */
class Dude {
    public:
        /**
         * Creates the dude and sets their position.
         * @param pos is the position to give the dude.
         * @param layer is the layer to put them at.
         */
        Dude(Util::Vec pos, uint8_t layer);

        /**
         * Gives you the dude's position.
         * @return the position.
         */
        Util::Vec getPos() const;

        /**
         * Gives you the z layer that the dude is on.
         * @return the z layer.
         */
        uint8_t getLayer() const;

        /**
         * Returns an info message about this dude for your pleasure.
         * @param world is used for something I guess.
         * @return a pointer to a temporary buffer with the text.
         */
        char const *info(World const &world);

        /**
         * Causes the dude to move and potentially attack if there is osmething
         * in the way.
         * @param direction is the direction to move. only the signs matter
         *        magnitude is ignored.
         * @param world is the world they are moving in.
         * @return temporary buffer with any messages or null.
         */
        char const *move(Util::Vec direction, World const &world);

        /**
         * Makes the ai make the dude take some kind of move, and returns the
         * message generated by said move.
         * @return the message on a buffer, you need to save this text
         *         somewhere else after you receive it because soon after it
         *         will be gone. Also this can be null if nothing message
         *         worthy happened.
         */
        char const *update(World const &world);

    private:
        static char messageBuffer[1024];
        static uint8_t pathBuffer[3][3];
        char const *name = nullptr;
        Util::Vec pos;
        uint8_t layer = 0;
        uint8_t type = 0;
        uint8_t hp = 1;
        uint8_t xp = 0;
        uint8_t level = 1;
        uint8_t strength = 1;
        uint8_t dexterity = 1;
        uint8_t intelligence = 1;
        uint8_t endurance = 1;
        Item *head = nullptr;
        Item *body = nullptr;
        Item *leftHand = nullptr;
        Item *rightHand = nullptr;
        Item *legs = nullptr;
        Item *feet = nullptr;
        Item *iventory[10];
};

#endif
