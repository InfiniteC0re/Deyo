#pragma once
#include "KeyCodes.h"

#include <vector>
#include <memory>

namespace Deyo
{
	using ActionSlot = int16_t;
	enum ActionSlot_ : ActionSlot
	{
		ActionSlot_None = -1,
		ActionSlot_0,
		ActionSlot_1,
		ActionSlot_2,
		ActionSlot_3,
		ActionSlot_4,
		ActionSlot_5,
		ActionSlot_6,
		ActionSlot_7,
		ActionSlot_8,
		ActionSlot_9,
		ActionSlot_10,
		ActionSlot_11,
		ActionSlot_12,
		ActionSlot_13,
		ActionSlot_14,
		ActionSlot_15,
		ActionSlot_16,
		ActionSlot_17,
		ActionSlot_18,
		ActionSlot_19,
		ActionSlot_20,
		ActionSlot_21,
		ActionSlot_22,
		ActionSlot_23,
		ActionSlot_24,
		ActionSlot_25,
		ActionSlot_26,
		ActionSlot_27,
		ActionSlot_28,
		ActionSlot_29,
		ActionSlot_30,
		ActionSlot_31,
		ActionSlot_Last,
	};
	constexpr ActionSlot ActionSlot_Count = ActionSlot_Last;

	class ActionList
	{
	public:
		ActionList() = default;
		inline static void BindKey(ActionSlot slot, Key key) { s_Instance->m_ActionKeys[slot].push_back(key); };
		inline static ActionSlot GetSlot(Key key) { return s_Instance->GetSlot_Impl(key); };
	
	private:
		ActionSlot GetSlot_Impl(Key key) const
		{
			for (ActionSlot i = 0; i < ActionSlot_Count; i++)
			{
				auto action = m_ActionKeys[i];
				auto it = std::find(action.begin(), action.end(), key);
				if (it != action.end()) return i;
			}

			return ActionSlot_None;
		}

	private:
		static Scope<ActionList> s_Instance;
		std::vector<Key> m_ActionKeys[ActionSlot_Count];
	};
}