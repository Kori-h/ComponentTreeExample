#ifndef __RENDER_SYSTEM__
#define __RENDER_SYSTEM__

#include "core.hpp"
#include "components.hpp"

namespace core 
{
	class RenderComponent : public Component
	{
		public:
			RenderComponent();

			void init() override;
			void update() override;

		private:
			TransformComponent* p_transform_component;
	};
	
	namespace system
	{
		class RenderSystem
		{
			public:
				static RenderSystem& getInstance();
				void render(void);
				void addToRenderQueue(RenderComponent* component);

			private:
				RenderSystem();
				std::queue<RenderComponent*> render_queue;
		};
	}
}

#endif