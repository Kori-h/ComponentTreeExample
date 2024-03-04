#include "render_system.hpp"

namespace core 
{
	RenderComponent::RenderComponent() : Component{ TypeHash<RenderComponent>::value }, p_transform_component(nullptr) 
	{

	}

	void RenderComponent::init()
	{
		p_transform_component = p_parent->getComponent<TransformComponent>();

		if (p_transform_component == nullptr) 
		{
			std::cerr << __func__ << " : Null pointer detected" << std::endl;
			active = false;
		}
	}

	void RenderComponent::update()
	{
		system::RenderSystem::getInstance().addToRenderQueue(this);
	}

	namespace system
	{
		RenderSystem::RenderSystem() : render_queue() 
		{
		
		}

		RenderSystem& RenderSystem::getInstance()
		{
			static RenderSystem instance;
			return instance;
		}

		void RenderSystem::render(void)
		{
			int render_count{};

			while (render_queue.empty() == false)
			{
				// RenderComponent* p_component = render_queue.front();
				render_queue.pop();
				++render_count;
			}

			std::cout << "RenderSystem : " << render_count << " objects have been rendered." << std::endl;
		}

		void RenderSystem::addToRenderQueue(RenderComponent* component)
		{
			render_queue.push(component);
		}
	}
}
