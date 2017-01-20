#include "BaseManager.h"
#include "Locator.h"


void BaseManager::Draw(Graphics & gfx, Camera & cam)
{
	for (auto& it : m_bases)
		it->Draw(gfx, cam);
}

void BaseManager::Update(const float & dt)
{
	for (auto& it : m_bases)
		it->Update(dt);
}

void BaseManager::AddBase(Base* base)
{
	auto& it = std::find(m_bases.begin(), m_bases.end(), base);
	if(it == m_bases.end())
	  m_bases.push_back(base); 
}



void BaseManager::OnMouseClick(const Vec2i & mouse)
{
	for (auto& it : m_bases)
	{
		if (it->GetRect().Contains(mouse))
		{
			m_selectedBase = it;
			Locator::SoundEngine->Play("newunitsavailable");
		}
	}
}
