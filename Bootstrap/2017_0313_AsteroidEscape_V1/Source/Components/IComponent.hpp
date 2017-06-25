#pragma once

namespace aie {
	class Renderer2D;
}

/**
*	@brief Interface for all components.
*/
class IComponent {
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	// Not pure virtual functions because not all components MUST draw and render (i.e. a wall)
	virtual void Update(float dt) {};
	virtual void Render(aie::Renderer2D* a_r2d) {};
};