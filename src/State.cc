#include "src/State.hh"

State::Transition::Transition(bool remove, State *add) {
    this->remove = remove;
    this->add = add;
}

State::State(World &world, Assets &assets): world(world), assets(assets) {

}

State::Transition State::onKey(int code) {
    return Transition();
}

State::Transition State::onClick(int button) {
    return Transition();
}

void State::render() {

}
