#ifndef __COMPONENTS__
#define __COMPONENTS__

#include "core.hpp"

namespace core
{
    class TransformComponent : public Component
    {
        public:
            Vector2D position;
            Vector2D scale;
            float rotation;
            Vector2D velocity;

            TransformComponent();

            void init() override;
            void update() override;
    };
}
#endif