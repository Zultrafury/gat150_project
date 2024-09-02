#pragma once
#include <box2d/box2d.h>

class Physics
{
public:
    Physics() = default;

    b2WorldId m_worldId = b2_nullWorldId;
    
    bool Initialize()
    {
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = b2Vec2{ 0.0f, 10.0f };
        // have to use "/NODEFAULTLIB:msvcrt.lib" in linker commands to run program
        // physics world cannot be created due to memory access errors??
        //m_worldId = b2CreateWorld(&worldDef);

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

    b2WorldId GetWorldId()
    {
        return m_worldId;
    }
};