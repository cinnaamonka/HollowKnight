#pragma once
#include <vector>
#include <typeinfo>
template <typename T>
class BaseManager
{

public:
	BaseManager()
	{
	};
	BaseManager(const BaseManager&) = delete;
	BaseManager& operator=(const BaseManager&) = delete;
	BaseManager(BaseManager&&) = delete;
	BaseManager& operator=(BaseManager&&) = delete;
	virtual ~BaseManager()
	{
		for (const T* item : m_pItems)
		{
			delete item;
		}
	};

	void AddItem(T* pItem)
	{
		m_pItems.push_back(pItem);
	};

	virtual void Update()
	{

	};

	virtual void Draw() const
	{
		for (const T* pItem : m_pItems)
		{
			pItem->Draw();
		}
	};

	size_t Size() const
	{
		return m_pItems.size();
	};
	bool HitItem(const Rectf& rect)
	{
		if (m_pItems.empty())
			return false;

		for (T* item : m_pItems)
		{
			if (item->IsOverlapping(rect) && !item->IsDestroyed())
			{
				std::swap(item, m_pItems.back());

				return true;
			}
		}

		return false;
	};

	const std::vector<T*>& GetItems() const
	{
		return m_pItems;
	}
protected:

	std::vector<T*> m_pItems;

};


