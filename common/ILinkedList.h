#pragma once

// ILink members must be public
template <typename T>
struct ILink
{
	static const UInt32 s_offset;

	ILink <T>* m_pkNext;
	ILink <T>* prev;

	T* GetObj(void) { return (T*)(((uintptr_t)this) - s_offset); }

	static ILink <T>* GetLink(T* obj) { return (ILink <T> *)(((uintptr_t)obj) + s_offset); }

	void	Unlink(void)
	{
		if (m_pkNext)	m_pkNext->prev = prev;
		if (prev)	prev->m_pkNext = m_pkNext;

		m_pkNext = prev = NULL;
	}

	void	LinkBefore(T* obj)
	{
		LinkBefore(GetLink(obj));
	}

	void	LinkAfter(T* obj)
	{
		LinkAfter(GetLink(obj));
	}

	void	LinkBefore(ILink <T>* link)
	{
		link->m_pkNext = this;
		link->prev = prev;

		if (prev)
		{
			prev->m_pkNext = link;
		}

		prev = link;
	}

	void	LinkAfter(ILink <T>* link)
	{
		link->m_pkNext = m_pkNext;
		link->prev = this;

		if (m_pkNext)
		{
			m_pkNext->prev = link;
		}

		m_pkNext = link;
	}
};

template <typename T>
struct ILinkedList
{
	ILink <T>	begin;
	ILink <T>	end;

	void	Reset(void)
	{
		begin.m_pkNext = &end;
		begin.prev = NULL;
		end.m_pkNext = NULL;
		end.prev = &begin;
	}

	void	PushFront(T* obj)
	{
		ILink <T>* objLink = ILink <T>::GetLink(obj);

		objLink->m_pkNext = begin.m_pkNext;
		objLink->prev = &begin;

		if (objLink->m_pkNext)
		{
			objLink->m_pkNext->prev = objLink;
		}

		begin.m_pkNext = objLink;
	}
};

#define ILINK_INIT(baseType, memberName)	template <typename T> const UInt32 ILink <T>::s_offset = offsetof(baseType, memberName)
