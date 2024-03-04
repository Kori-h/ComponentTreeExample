#include "components.hpp"

namespace core
{
	TransformComponent::TransformComponent() : Component{ TypeHash<TransformComponent>::value }, position{}, scale{}, rotation{}, velocity{} {};

    void TransformComponent::init()
    {

    }

    void TransformComponent::update()
    {
        position.x += velocity.x;
        position.y += velocity.y;
    }
}