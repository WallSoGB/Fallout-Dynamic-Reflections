#pragma once

enum {
	eListCount = -3,
	eListEnd = -2,
	eListInvalid = -1,
};

template <typename T_Data>
class ListNode {
public:
	T_Data* m_item;
	ListNode* m_pkNext;

	ListNode() : m_item(NULL), m_pkNext(NULL) {}
	ListNode(T_Data* _data) : m_item(_data), m_pkNext(NULL) {}

	T_Data* Data() const { return m_item; }
	ListNode* Next() const { return m_pkNext; }

	ListNode* RemoveMe()
	{
		if (m_pkNext)
		{
			ListNode* pNext = m_pkNext;
			m_item = m_pkNext->m_item;
			m_pkNext = m_pkNext->m_pkNext;
			MemoryManager::Deallocate(pNext);
			return this;
		}
		m_item = NULL;
		return NULL;
	}

	ListNode* RemoveNext()
	{
		ListNode* pNext = m_pkNext;
		m_pkNext = m_pkNext->m_pkNext;
		MemoryManager::Deallocate(pNext);
		return m_pkNext;
	}

	ListNode* Append(T_Data* _data)
	{
		ListNode* newNode = (ListNode*)MemoryManager::Allocate(sizeof(ListNode));
		newNode->m_item = _data;
		newNode->m_pkNext = m_pkNext;
		m_pkNext = newNode;
		return newNode;
	}

	ListNode* Insert(T_Data* _data)
	{
		ListNode* newNode = (ListNode*)MemoryManager::Allocate(sizeof(ListNode));
		newNode->m_item = m_item;
		m_item = _data;
		newNode->m_pkNext = m_pkNext;
		m_pkNext = newNode;
		return newNode;
	}
};

template <class T_Data>
class tList {
public:
	typedef ListNode<T_Data> _Node;

	_Node m_listHead;

	template <class Op>
	UInt32 FreeNodes(_Node* node, Op&& compareOp) const
	{
		static UInt32 nodeCount = 0, numFreed = 0, lastNumFreed = 0;
		if (node->m_pkNext)
		{
			nodeCount++;
			FreeNodes(node->m_pkNext, compareOp);
			nodeCount--;
		}
		if (compareOp.Accept(node->m_item))
		{
			node->RemoveMe();
			numFreed++;
		}
		if (!nodeCount)
		{
			lastNumFreed = numFreed;
			numFreed = 0;
		}
		return lastNumFreed;
	}

	_Node* GetLastNode(SInt32* outIdx = NULL) const
	{
		SInt32 index = 0;
		_Node* node = Head();
		while (node->m_pkNext)
		{
			node = node->m_pkNext;
			index++;
		}
		if (outIdx)
			*outIdx = index;
		return node;
	}

	_Node* GetNthNode(SInt32 index) const
	{
		if (index >= 0)
		{
			_Node* node = Head();
			do
			{
				if (!index)
					return node;
				index--;
			} while (node = node->m_pkNext);
		}
		return NULL;
	}

	void Init(T_Data* item = NULL)
	{
		m_listHead.m_item = item;
		m_listHead.m_pkNext = NULL;
	}

	_Node* Head() const { return const_cast<_Node*>(&m_listHead); }

	bool IsEmpty() const { return !m_listHead.m_item && !m_listHead.m_pkNext; }

	class Iterator
	{
		_Node* m_curr;

	public:
		Iterator operator++()
		{
			if (m_curr)
				m_curr = m_curr->m_pkNext;
			return *this;
		}
		bool End() const { return !m_curr || (!m_curr->m_item && !m_curr->m_pkNext); }
		T_Data* operator->() const { return m_curr->m_item; }
		T_Data*& operator*() const { return m_curr->m_item; }
		const Iterator& operator=(const Iterator& rhs)
		{
			m_curr = rhs.m_curr;
			return *this;
		}
		T_Data* Get() const { return m_curr->m_item; }
		void Next()
		{
			if (m_curr)
				m_curr = m_curr->m_pkNext;
		}
		void Find(T_Data* _item)
		{
			while (m_curr)
			{
				if (m_curr->m_item == _item)
					break;
				m_curr = m_curr->m_pkNext;
			}
		}
		bool operator!=(const Iterator& other) const
		{
			return m_curr != other.m_curr;
		}

		bool operator!=(Iterator&& other) const
		{
			return m_curr != other.m_curr;
		}

		Iterator(_Node* node = NULL) : m_curr(node) {}
		Iterator(tList& _list) : m_curr(&_list.m_listHead) {}
		Iterator(tList* _list) : m_curr(&_list->m_listHead) {}
		Iterator(tList& _list, T_Data* _item) : m_curr(&_list.m_listHead) { Find(_item); }
		Iterator(tList* _list, T_Data* _item) : m_curr(&_list->m_listHead) { Find(_item); }
	};

	Iterator Begin() const { return Iterator(Head()); }

	UInt32 Count() const
	{
		if (!m_listHead.m_item)
			return 0;
		_Node* node = Head();
		UInt32 count = 1;
		while (node = node->m_pkNext)
			count++;
		return count;
	};

	bool IsInList(T_Data* item) const
	{
		_Node* node = Head();
		do
		{
			if (node->m_item == item)
				return true;
			node = node->m_pkNext;
		} while (node);
		return false;
	}

	T_Data* GetFirstItem() const
	{
		return m_listHead.m_item;
	}

	T_Data* GetLastItem() const
	{
		return GetLastNode()->m_item;
	}

	T_Data* GetNthItem(SInt32 index) const
	{
		if (eListEnd == index)
			return GetLastNode()->m_item;
		_Node* node = GetNthNode(index);
		return node ? node->m_item : NULL;
	}

	SInt32 AddAt(T_Data* item, SInt32 index)
	{
		if (!item)
			return eListInvalid;
		_Node* node;
		if (!index)
		{
			if (m_listHead.m_item)
				m_listHead.Insert(item);
			else
				m_listHead.m_item = item;
		}
		else if (eListEnd == index)
		{
			node = GetLastNode(&index);
			if (node->m_item)
				node->Append(item);
			else
				node->m_item = item;
		}
		else
		{
			node = GetNthNode(index);
			if (!node)
				return eListInvalid;
			node->Insert(item);
		}
		return index;
	}

	SInt32 Append(T_Data* item)
	{
		SInt32 index = eListInvalid;
		if (item)
		{
			_Node* node = GetLastNode(&index);
			if (node->m_item)
				node->Append(item);
			else
				node->m_item = item;
		}
		return index;
	}

	void Insert(T_Data* item)
	{
		if (item)
		{
			if (m_listHead.m_item)
				m_listHead.Insert(item);
			else
				m_listHead.m_item = item;
		}
	}

	void CopyFrom(tList& sourceList)
	{
		_Node* target = Head(), * source = sourceList.Head();
		RemoveAll();
		if (!source->m_item)
			return;
		target->m_item = source->m_item;
		while (source = source->m_pkNext)
			target = target->Append(source->m_item);
	}

	template <class Op>
	void Visit(Op&& op, _Node* prev = NULL) const
	{
		_Node* curr = prev ? prev->m_pkNext : Head();
		while (curr)
		{
			if (!curr->m_item || !op.Accept(curr->m_item))
				break;
			curr = curr->m_pkNext;
		}
	}

	template <class Op>
	T_Data* Find(Op&& op) const
	{
		_Node* curr = Head();
		T_Data* pItem;
		do
		{
			pItem = curr->m_item;
			if (pItem && op.Accept(pItem))
				return pItem;
			curr = curr->m_pkNext;
		} while (curr);
		return NULL;
	}

	template <class Op>
	Iterator Find(Op&& op, Iterator& prev) const
	{
		Iterator curIt = prev.End() ? Begin() : ++prev;
		while (!curIt.End())
		{
			if (*curIt && op.Accept(*curIt))
				break;
			++curIt;
		}
		return curIt;
	}

	template <class Op>
	UInt32 CountIf(Op&& op) const
	{
		UInt32 count = 0;
		_Node* curr = Head();
		do
		{
			if (curr->m_item && op.Accept(curr->m_item))
				count++;
			curr = curr->m_pkNext;
		} while (curr);
		return count;
	}

	class AcceptAll
	{
	public:
		bool Accept(T_Data* item) { return true; }
	};

	void RemoveAll() const
	{
		_Node* nextNode = Head(), * currNode = nextNode->m_pkNext;
		nextNode->m_item = NULL;
		nextNode->m_pkNext = NULL;
		while (currNode)
		{
			nextNode = currNode->m_pkNext;
			MemoryManager::Deallocate(currNode);
			currNode = nextNode;
		}
	}

	void DeleteAll() const
	{
		_Node* nextNode = Head(), * currNode = nextNode->m_pkNext;
		MemoryManager::Deallocate(nextNode->m_item);
		nextNode->m_item = NULL;
		nextNode->m_pkNext = NULL;
		while (currNode)
		{
			nextNode = currNode->m_pkNext;
			currNode->m_item->~T_Data();
			MemoryManager::Deallocate(currNode->m_item);
			MemoryManager::Deallocate(currNode);
			currNode = nextNode;
		}
	}

	T_Data* RemoveNth(SInt32 idx)
	{
		T_Data* removed = NULL;
		if (idx <= 0)
		{
			removed = m_listHead.m_item;
			m_listHead.RemoveMe();
		}
		else
		{
			_Node* node = Head();
			while (node->m_pkNext && --idx)
				node = node->m_pkNext;
			if (!idx)
			{
				removed = node->m_pkNext->m_item;
				node->RemoveNext();
			}
		}
		return removed;
	};

	UInt32 Remove(T_Data* item)
	{
		UInt32 removed = 0;
		_Node* curr = Head(), * prev = NULL;
		do
		{
			if (curr->m_item == item)
			{
				curr = prev ? prev->RemoveNext() : curr->RemoveMe();
				removed++;
			}
			else
			{
				prev = curr;
				curr = curr->m_pkNext;
			}
		} while (curr);
		return removed;
	}

	T_Data* ReplaceNth(SInt32 index, T_Data* item)
	{
		T_Data* replaced = NULL;
		if (item)
		{
			_Node* node;
			if (eListEnd == index)
				node = GetLastNode();
			else
			{
				node = GetNthNode(index);
				if (!node)
					return NULL;
			}
			replaced = node->m_item;
			node->m_item = item;
		}
		return replaced;
	}

	UInt32 Replace(T_Data* item, T_Data* replace)
	{
		UInt32 replaced = 0;
		_Node* curr = Head();
		do
		{
			if (curr->m_item == item)
			{
				curr->m_item = replace;
				replaced++;
			}
			curr = curr->m_pkNext;
		} while (curr);
		return replaced;
	}

	template <class Op>
	UInt32 RemoveIf(Op&& op)
	{
		return FreeNodes(Head(), op);
	}

	SInt32 GetIndexOf(T_Data* item)
	{
		SInt32 idx = 0;
		_Node* curr = Head();
		do
		{
			if (curr->m_item == item)
				return idx;
			idx++;
			curr = curr->m_pkNext;
		} while (curr);
		return -1;
	}

	template <class Op>
	SInt32 GetIndexOf(Op&& op)
	{
		SInt32 idx = 0;
		_Node* curr = Head();
		do
		{
			if (curr->m_item && op.Accept(curr->m_item))
				return idx;
			idx++;
			curr = curr->m_pkNext;
		} while (curr);
		return -1;
	}

	template <typename F>
	T_Data* FindFirst(F&& func) const
	{
		for (auto iter = Begin(); !iter.End(); ++iter)
		{
			if (*iter && func(*iter))
				return *iter;
		}
		return nullptr;
	}

	template <typename F>
	void ForEach(F&& func) const
	{
		for (auto iter = Begin(); !iter.End(); ++iter)
		{
			if (*iter)
				func(*iter);
		}
	}

	template <typename F>
	bool Contains(F&& func) const
	{
		return FindFirst(func) != nullptr;
	}

	// for use with C++11 range based loops only.
	Iterator begin() const
	{
		return Begin();
	}

	// for use with C++11 range based loops only.
	Iterator end() const
	{
		return Iterator(static_cast<_Node*>(nullptr));
	}
};

ASSERT_SIZE(tList<UInt32>, 0x8);