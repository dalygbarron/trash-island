#include "src/World.hh"

World::World(unsigned int seed): seed(seed) {

}

Chunk const &World::getChunk(Util::Vec pos) const {
    if (chunks.contains(pos)) return chunks.at(pos);
    chunks.emplace(std::piecewise_construct, std::make_tuple(pos), std::make_tuple(seed, pos));
    chunks.at(pos).hydrate();
    return chunks.at(pos);
}

uint8_t World::getTile(Util::Vec pos, uint8_t layer) const {
    Util::Vec chunkPos = pos / Chunk::SIZE;
    Chunk chunk = getChunk(chunkPos);
    return chunk.getTile(pos - chunkPos * Chunk::SIZE, layer);
}

void World::addMessage(char const *c) {
    char *buffer = new char[std::strlen(c) + 1];
    std::strcpy(buffer, c);
    messages.push_front(buffer);
    if (messages.size() > 6) {
        delete[] messages.back();
        messages.pop_back();
    }
}

std::deque<char *>::const_iterator World::messagesBegin() const {
    return messages.begin();
}

std::deque<char *>::const_iterator World::messagesEnd() const {
    return messages.end();
}

void World::update() {
    Util::Vec chunkPos = player.getPos();
    Chunk chunk = getChunk(chunkPos);
}
