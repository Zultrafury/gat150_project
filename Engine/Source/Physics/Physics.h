#pragma once
#include <box2d/box2d.h>
#include <memory>

class Physics
{
public:
    Physics() = default;

    bool Initialize()
    {
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
        m_worldId = b2CreateWorld(&worldDef);

        return true;
    }
    
    void Shutdown()
    {
        b2DestroyWorld(m_worldId);
    }
    
    void Update(float dt)
    {
        b2World_Step(m_worldId, 1.0f / 60.0f, 4);
    }
private:
    b2WorldId m_worldId;
};