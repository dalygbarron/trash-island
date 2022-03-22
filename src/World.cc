#include "src/World.hh"
#include <list>

World::World(uint64_t seed): seed(seed), player(Util::Vec(), 0) {

}

Chunk const &World::getChunk(Util::Vec pos) const {
    if (chunks.contains(pos)) {
        Chunk &chunk = chunks.at(pos);
        if (!chunk.hydrated()) {
            chunk.hydrate();
            openChunks.push_back(&chunk);
        }
        return chunks.at(pos);
    }
    chunks.emplace(
        std::piecewise_construct,
        std::make_tuple(pos),
        std::make_tuple(seed, pos)
    );
    Chunk &chunk = chunks.at(pos);
    if (!chunk.hydrated()) {
        chunk.hydrate();
        openChunks.push_back(&chunk);
    }
    return chunk;
}

uint8_t World::getTile(Util::Vec pos, uint8_t layer) const {
    Util::Vec chunkPos = pos / Chunk::SIZE;
    Chunk chunk = getChunk(chunkPos);
    return chunk.getTile(pos - chunkPos * Chunk::SIZE, layer);
}

uint8_t World::getPath(Util::Vec pos) const {
    Util::Vec corner = player.getPos() - Util::Vec(PATH_SIZE / 2);
    Util::Vec pathPos = pos - corner;
    if (
        pathPos.x < 0 || pathPos.y < 0 || pathPos.x >= PATH_SIZE ||
        pathPos.y >= PATH_SIZE
    ) {
        return 0xff;
    }
    return pathing[pathPos.y * PATH_SIZE + pathPos.x];
}

Util::Vec World::getPathDirection(Util::Vec pos) const {
    Util::Vec dir;
    uint8_t lowest = getPath(pos);
    if (lowest == 0xff) return dir;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) continue;
            uint8_t test = getPath(pos + Util::Vec(x, y));
            if (test < lowest) {
                lowest = test;
                dir.x = x;
                dir.y = y;
            }
        }
    }
    return dir;
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
    generatePath();
    Util::Vec chunkPos = player.getPos() / Chunk::SIZE;
    std::vector<Chunk *>::iterator it = openChunks.begin();
    while(it != openChunks.end()) {
        Chunk *c = *it;
        if (
            c->pos.x < chunkPos.x - 1 || c->pos.x > chunkPos.x + 1 ||
            c->pos.y < chunkPos.y - 1 || c->pos.y > chunkPos.y + 1
        ) {
            c->dehydrate();
            it = openChunks.erase(it);
        } else {
            it++;
            for (Dude &d: c->dudes) {
                char const *m = d.update(*this);
                if (m != nullptr) addMessage(m);
            }
        }
    }
}

void World::generatePath() {
    memset(pathing, 0xff, PATH_SIZE * PATH_SIZE);
    std::deque<Util::Vec> points;
    Util::Vec mid = player.getPos();
    Util::Vec corner = mid - Util::Vec(PATH_SIZE / 2);
    points.push_front(mid);
    pathing[(mid.y - corner.y) * PATH_SIZE + mid.x - corner.x] = 0;
    while (!points.empty()) {
        Util::Vec point = points.back();
        points.pop_back();
        int currentIndex = (point.y - corner.y) * PATH_SIZE + point.x -
            corner.x;
        uint8_t current = pathing[currentIndex];
        if (current == 0xfe) continue;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (x == 0 && y == 0) continue;
                Util::Vec checkPoint = point + Util::Vec(x, y);
                if (
                    checkPoint.x < corner.x || checkPoint.y < corner.y ||
                    checkPoint.x >= corner.x + PATH_SIZE ||
                    checkPoint.y >= corner.y + PATH_SIZE
                ) {
                    continue;
                }
                int checkIndex = (checkPoint.y - corner.y) * PATH_SIZE +
                    checkPoint.x - corner.x;
                uint8_t tile = getTile(checkPoint, player.getLayer());
                if (tile == 0 && pathing[checkIndex] > current + 1) {
                    pathing[checkIndex] = current + 1;
                    points.push_front(checkPoint);
                }
            }
        }
    }
}
