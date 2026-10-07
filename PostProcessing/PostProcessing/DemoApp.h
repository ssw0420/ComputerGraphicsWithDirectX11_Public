#pragma once

#include <algorithm>
#include <iostream>
#include <memory>

#include "Application.h"

namespace ssw
{
	class DemoApp : public Application
	{
	public:
		DemoApp();

		virtual bool Initialize() override;
		virtual void Render() override;
	};
}