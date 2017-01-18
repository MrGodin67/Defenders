#include "BaseManager.h"
#include "Locator.h"


void BaseManager::Draw(Graphics & gfx, Camera & cam)
{
	for (auto& it : m_bases)
		it.Draw(gfx, cam);
}

void BaseManager::Update(const float & dt)
{
	for (auto& it : m_bases)
		it.Update(dt);
}

void BaseManager::AddBase(Vec2i pos, int imageIndex)
{
	m_bases.emplace_back(Locator::ImageManager->GetImage("bases"), imageIndex, 128.0f, 128.0f, pos,
		15.0f);
}



void BaseManager::OnMouseClick(const Vec2i & mouse)
{
	for (auto& it : m_bases)
	{
		if (it.GetAABB().Contains(mouse))
		{
			m_selectedBase = &it;
			Locator::SoundEngine->Play("newunitsavailable");
		}
	}
}
