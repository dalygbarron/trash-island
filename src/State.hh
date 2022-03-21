#ifndef STATE_H
#define STATE_H

#include "src/Assets.hh"
#include "src/World.hh"

/**
 * A state that the game program can be in. These are designed to be stacked so
 * that one state can return info back to another after receiving user input or
 * whatever.
 */
class State {
    public:
        /**
         * Represents a state transition to be actioned after a state updates,
         * allowing you to modify the stack of game states.
         */
        struct Transition {
            bool remove = false;
            State *add = nullptr;

            /**
             * Default constructor makes a transition that does nothing.
             */
            Transition() = default;

            /**
             * This constructor lets you add a new state to the stack and
             * specify whether this is replacing the current one, or going on
             * top.
             * @param remove is whether to remove the current state before
             *        adding the new one.
             * @param add is the state to add, though you can make this null
             *        if your intention is just to pop the current state.
             */
            Transition(bool remove, State *add);
        };

        /**
         * Constructor that puts in the world object.
         * @param world is the world object for this state. It is a reference
         *        bbecause the state object itself is really only relevant to
         *        one given world.
         */
        State(World &world, Assets &assets);

        /**
         * Does nothing tbh.
         */
        virtual ~State() = default;

        /**
         * called when the user presses a key (though some keypresses can be
         * dropped if the user is being a retard).
         * @param code unicode of the character pressed.
         */
        virtual Transition onKey(int code);

        /**
         * called when the user clicks.
         * @param button is the id of the mouse button that was clicked.
         */
        virtual Transition onClick(int button);

        /**
         * renders the game. assumes that raylib is already in drawing mode.
         */
        virtual void render();

    protected:
        World &world;
        Assets &assets;
};

/**
 * Main state of the 2d view of the game where it is showing everything and
 * awaiting user input.
 */
class Input2DState: public State {
    public:
        /**
         * Constructor that just puts in the stuff that is needed.
         * @param world is the world object.
         */
        Input2DState(World &world, Assets &assets);

        virtual Transition onKey(int code) override;

        virtual Transition onClick(int button) override;

        virtual void render() override;
};

#endif
