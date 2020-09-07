#pragma once

#include <queue>

#include "RGE/Events/Events.hpp"

namespace RGE
{
	class EventQueue
	{
	public:
		EventQueue()
		{

		}

		~EventQueue()
		{
			// Clean up the queue
			for (unsigned int i = 0; i < m_queue.size(); i++)
			{
				delete m_queue.front();
				m_queue.pop();
			}
		}

		void AddEvent(Event* e)
		{
			m_queue.push(e);
		}

		Event* GetNextEvent()
		{
			// Make sure there is an event in the queue
			if (!m_queue.empty())
			{
				Event* e = m_queue.front();
				m_queue.pop();
				return e;
			}
			return nullptr;
		}

	private:
		std::queue<Event*> m_queue;
	};

} // RGE
