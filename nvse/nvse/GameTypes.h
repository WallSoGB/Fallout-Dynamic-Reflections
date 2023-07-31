#pragma once

#include <list>
#include "Utilities.h"
#include "NiTypes.h"
#include <functional>
#include "BSString.hpp"
#include "BSSimpleList.hpp"
#include "BSSimpleArray.hpp"
#include "DList.hpp"

#if RUNTIME
TESForm *__stdcall LookupFormByID(UInt32 refID);
#else
typedef TESForm *(*_LookupFormByID)(UInt32 id);
extern const _LookupFormByID LookupFormByID;
#endif

template <class Node, class Info>
class Visitor
{
	const Node *m_pHead;

	template <class Op>
	UInt32 FreeNodes(Node *node, Op &compareOp) const
	{
		static UInt32 nodeCount = 0;
		static UInt32 numFreed = 0;
		static Node *lastNode = NULL;
		static bool bRemovedNext = false;

		UInt32 returnCount;

		if (node->Next())
		{
			nodeCount++;
			FreeNodes(node->Next(), compareOp);
			nodeCount--;
		}

		if (compareOp.Accept(node->Info()))
		{
			if (nodeCount)
				node->Delete();
			else
				node->DeleteHead(lastNode);
			numFreed++;
			bRemovedNext = true;
		}
		else
		{
			if (bRemovedNext)
				node->SetNext(lastNode);
			bRemovedNext = false;
			lastNode = node;
		}

		returnCount = numFreed;

		if (!nodeCount) //reset vars after recursing back to head
		{
			numFreed = 0;
			lastNode = NULL;
			bRemovedNext = false;
		}

		return returnCount;
	}

	class AcceptAll
	{
	public:
		bool Accept(Info *info)
		{
			return true;
		}
	};

	class AcceptEqual
	{
		const Info *m_toMatch;

	public:
		AcceptEqual(const Info *info) : m_toMatch(info) {}
		bool Accept(const Info *info)
		{
			return info == m_toMatch;
		}
	};

	class AcceptStriCmp
	{
		const char *m_toMatch;

	public:
		AcceptStriCmp(const char *info) : m_toMatch(info) {}
		bool Accept(const char *info)
		{
			if (m_toMatch && info)
				return _stricmp(info, m_toMatch) ? false : true;
			return false;
		}
	};

public:
	Visitor(const Node *pHead) : m_pHead(pHead) {}

	UInt32 Count() const
	{
		UInt32 count = 0;
		const Node *pCur = m_pHead;
		while (pCur && pCur->Info() != NULL)
		{
			++count;
			pCur = pCur->Next();
		}
		return count;
	}

	Info *GetNthInfo(UInt32 n) const
	{
		UInt32 count = 0;
		const Node *pCur = m_pHead;
		while (pCur && count < n && pCur->Info() != NULL)
		{
			++count;
			pCur = pCur->Next();
		}
		return (count == n && pCur) ? pCur->Info() : NULL;
	}

	template <class Op>
	void Visit(Op &&op) const
	{
		const Node *pCur = m_pHead;
		bool bContinue = true;
		while (pCur && pCur->Info() && bContinue)
		{
			bContinue = op.Accept(pCur->Info());
			if (bContinue)
			{
				pCur = pCur->Next();
			}
		}
	}

	template <class Op>
	const Node *Find(Op &&op, const Node *prev = NULL) const
	{
		const Node *pCur;
		if (!prev)
			pCur = m_pHead;
		else
			pCur = prev->m_pkNext;
		bool bFound = false;
		while (pCur && !bFound)
		{
			if (!pCur->Info())
				pCur = pCur->Next();
			else
			{
				bFound = op.Accept(pCur->Info());
				if (!bFound)
					pCur = pCur->Next();
			}
		}

		return pCur;
	}

	Node *FindInfo(const Info *toMatch)
	{
		return Find(AcceptEqual(toMatch));
	}

	template <class Op>
	UInt32 CountIf(Op &&op) const
	{
		UInt32 count = 0;
		const Node *pCur = m_pHead;
		while (pCur)
		{
			if (pCur->Info() && op.Accept(pCur->Info()))
				count++;
			pCur = pCur->Next();
		}
		return count;
	}

	const Node *GetLastNode() const
	{
		const Node *pCur = m_pHead;
		while (pCur && pCur->Next())
			pCur = pCur->Next();
		return pCur;
	}

	void RemoveAll() const
	{
		FreeNodes(const_cast<Node *>(m_pHead), AcceptAll());
	}

	template <class Op>
	UInt32 RemoveIf(Op &&op)
	{
		return FreeNodes(const_cast<Node *>(m_pHead), op);
	}

	bool Remove(const Info *toRemove)
	{
		return RemoveIf(AcceptEqual(toRemove)) ? true : false;
	}

	bool RemoveString(const char *toRemove)
	{
		return RemoveIf(AcceptStriCmp(toRemove)) ? true : false;
	}

	void Append(Node *newNode)
	{
		Node *lastNode = const_cast<Node *>(GetLastNode());
		if (lastNode == m_pHead && !m_pHead->Info())
			lastNode->DeleteHead(newNode);
		else
			lastNode->SetNext(newNode);
	}

	template <class Op>
	UInt32 GetIndexOf(Op &&op)
	{
		UInt32 idx = 0;
		const Node *pCur = m_pHead;
		while (pCur && pCur->Info() && !op.Accept(pCur->Info()))
		{
			idx++;
			pCur = pCur->Next();
		}

		if (pCur && pCur->Info())
			return idx;
		else
			return -1;
	}
};
