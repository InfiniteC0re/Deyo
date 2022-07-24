#include "pch.h"
#include "Action.h"

#include <Deyo/Core/Core.h>

namespace Deyo
{
	Scope<ActionList> ActionList::s_Instance = CreateScope<ActionList>();
}