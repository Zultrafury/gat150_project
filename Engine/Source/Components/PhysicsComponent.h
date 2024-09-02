#pragma once
#include <memory>
#include <SDL_render.h>
#include "Component.h"
#include "Physics/Physics.h"
#include <box2d/box2d.h>

class PhysicsComponent : public Component<PhysicsComponent>
{
public:
    std::unique_ptr<Physics> m_physics;
    b2BodyId body;

    PhysicsComponent(std::unique_ptr<Physics> phys)
    {
        b2BodyDef bodydef;
        bodydef.type = b2_dynamicBody; //this will be a dynamic body
        bodydef.position = {0, 20}; //set the starting position
        bodydef.rotation = b2MakeRot(0); //set the starting angle
        
        body = b2CreateBody(phys->GetWorldId(),&bodydef);
    }

    virtual void Draw(SDL_Renderer* renderer, int x, int y, double rotation, double scale)
    {
        
    }
    virtual void Update(SDL_Renderer* renderer, int* x, int* y, double& rotation, double& scale)
    {
        
    }

    Component* Clone() override
    {
        return new PhysicsComponent(*this);
    }
};
