#pragma once
#include "entities.h"

class RedEnemy : public BaseEnemy {
public:
    RedEnemy(b2World& world, b2Vec2 position);
    ~RedEnemy();

    void update() override;

    void onBeginContact(b2Fixture* self, b2Fixture* other) override;
    void onEndContact(b2Fixture* self, b2Fixture* other) override;

};
