#include "pch.h"
#include "Action.h"

namespace Deyo
{
	std::unique_ptr<ActionList> ActionList::s_Instance = std::make_unique<ActionList>();
}