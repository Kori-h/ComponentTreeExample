#include "core.hpp"

namespace core
{
    Component::Component(size_t id) : p_parent(nullptr), active(false), id(id)
    {

    }

    void Component::init()
    {

    }

    void Component::update()
    {

    }

    Object::Object() : active(false), p_objects(), p_components()
    {

    }

    void Object::init()
    {

    }

    void Object::update()
    {
        for (Component* p_component : p_components)
        {
            if (p_component->active)
            {
                p_component->update();
            }
        }
    }

    void updateObject(Object* p_root)
    {
        if (p_root == nullptr)
        {
            std::cerr << __func__ << " : Null pointer detected" << std::endl;
            return;
        }

        int update_count{};

        std::stack<Object*> stack;
        stack.push(p_root);

        while (stack.empty() == false)
        {
            Object* current = stack.top();
            stack.pop();

            for (Object* p_object : current->p_objects)
            {
                stack.push(p_object);
            }

            if (current->active)
            {
                current->update();
            }

            ++update_count;
        }

        std::cout << "Update : " << update_count << " objects have been updated." << std::endl;
    }

    void deleteObject(Object* p_root)
    {
        if (p_root == nullptr)
        {
            std::cerr << __func__ << " : Null pointer detected" << std::endl;
            return;
        }

        int object_delete_count{};
        int component_delete_count{};

        std::stack<Object*> stack;
        stack.push(p_root);

        while (stack.empty() == false)
        {
            Object* p_current = stack.top();
            stack.pop();

            for (Object* p_object : p_current->p_objects)
            {
                stack.push(p_object);
            }

            for (Component* p_component : p_current->p_components)
            {
                delete p_component;
                ++component_delete_count;
            }

            delete p_current;
            ++object_delete_count;
        }

        std::cout << "Free : " << object_delete_count << " objects and " << component_delete_count << " components have been deleted." << std::endl;
    }
}