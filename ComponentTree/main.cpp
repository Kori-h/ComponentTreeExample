#include <crtdbg.h>
#include "components.hpp"
#include "render_system.hpp"

core::Object* p_root;

int main(void) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // Root
    p_root = new core::Object();
  
    core::Object* obj = p_root->createObject<core::Object>();
    
    obj->createComponent<core::TransformComponent>();
    obj->createComponent<core::RenderComponent>();

    for (size_t i = 0; i < 3; i++)
    {
        core::Object* obj2 = obj->createObject<core::Object>();
        obj2->createComponent<core::TransformComponent>();
        obj2->createComponent<core::RenderComponent>(); 
    }

    for (size_t j = 0; j < 3; j++)
    {
        core::Object* obj3 = obj->getObject<core::Object>(2)->createObject<core::Object>();
        obj3->createComponent<core::TransformComponent>();
        obj3->createComponent<core::RenderComponent>();
    }

    std::cout << "Init : 8 objects and 14 components have been created." << std::endl;

    // Game loop
    size_t frames{5}, count{};
    while (count++ < frames)
    {
        std::cout << "Update : Frame " << count << std::endl;

        // Update game logic
        updateObject(p_root);

        // Render game object
        core::system::RenderSystem::getInstance().render();
    }

	deleteObject(p_root);
}