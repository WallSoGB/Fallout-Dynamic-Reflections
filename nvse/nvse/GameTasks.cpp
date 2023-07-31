#include "GameTasks.h"
#include "GameAPI.h"
#include "GameForms.h"
#include "GameObjects.h"
#include "Hooks_Gameplay.h"

// IOManager** g_ioManager = (IOManager**)0x00B33A10;

#if 0
bool IOManager::IsInQueue(TESObjectREFR *refr) 
{
	for (LockFreeQueue< NiPointer<IOTask> >::Node *node = taskQueue->head->next; node; node = node->next) 
	{
		QueuedReference *qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;

		if (qr->refr == refr)
			return true;
	}

	return false;
}

void IOManager::DumpQueuedTasks()
{
#if 0
	_MESSAGE("Dumping queued tasks:");
	for (LockFreeQueue< NiPointer<IOTask> >::Node *node = taskQueue->head->next; node; node = node->next)
	{
		QueuedReference* qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;
		else if (qr->refr)
		{
			Console_Print("\t%s (%08x)", GetFullName(qr->refr), qr->refr->refID);
			_MESSAGE("\t%s (%08x)", GetFullName(qr->refr), qr->refr->refID);
		}
		else
			_MESSAGE("NULL reference");
	}
#endif

}

IOManager* IOManager::GetSingleton()
{
	return *g_ioManager;
}
#endif