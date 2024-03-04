#ifndef __CORE__
#define __CORE__

#include <queue>
#include <iostream>
#include <vector>
#include <stack>

namespace core
{
    #define UNIQUE_HASH_ID static_cast<size_t>(__COUNTER__)

    class Object; // Forward declaration

    template <typename T>
    struct TypeHash
    {
        static constexpr size_t value = UNIQUE_HASH_ID;
    };

    struct Vector2D
    {
        float x;
        float y;
    };

    class Node
    {
        public:
            Node() = default;
            ~Node() = default;

            virtual void init() = 0;
            virtual void update() = 0;

            Node(Node const&) = delete;
            Node& operator=(Node const&) = delete;
            Node(Node&&) = delete;
            Node& operator=(Node&&) = delete;
    };

    class Component : public Node
    {
        public:
            Object* p_parent;
            bool active;
            size_t id;

            Component(size_t id);

            void init() override;
            void update() override;     
    };

    class Object : public Node
    {
        public:
            bool active;
            Object* p_parent;
            std::vector<Object*> p_objects;
            std::vector<Component*> p_components;

            Object();     

            void init() override;
            void update() override;

            template <typename T>
            std::enable_if_t<std::is_base_of<Object, T>::value, T*> createObject()
            {
                T* p_object = new T();
                p_object->active = true;
                p_object->p_parent = this;
                p_object->init();
                p_objects.push_back(static_cast<Object*>(p_object));
                return p_object;
            }

            template <typename T>
            std::enable_if_t<std::is_base_of<Object, T>::value, T*> getObject(size_t index)
            {
                if (index < p_objects.size())
                {
                    T* p_object = p_objects[index];
                    return static_cast<T*>(p_object);
                }
                else
                {
                    return nullptr;
                }
            }

            template <typename T>
            std::enable_if_t<std::is_base_of<Component, T>::value, T*> createComponent()
            {
                T* p_component = new T();
                p_component->active = true;
                p_component->p_parent = this;
                p_component->init();
                p_components.push_back(static_cast<Component*>(p_component));
                return p_component;
            }

            template <typename T>
            std::enable_if_t<std::is_base_of<Component, T>::value, T*> getComponent()
            {
                size_t hash = TypeHash<T>::value;

                for (Component* p_component : p_components)
                {
                    if (p_component->id == hash)
                    {
                        return static_cast<T*>(p_component);
                    }
                }

                return nullptr;
            }
    };

    void updateObject(Object* p_root);
    void deleteObject(Object* p_root);
}
#endif