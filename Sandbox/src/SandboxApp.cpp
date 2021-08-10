#include <Lilith.h>

class Sandbox : public Lilith::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Lilith::Application* Lilith::CreateApplication()
{
	return new Sandbox();
}