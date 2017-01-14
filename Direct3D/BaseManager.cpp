#include "BaseManager.h"

BaseManager::BaseManager(std::wstring imageFile, float clipWidth, float clipHeight)
{
	m_images = std::make_unique<SpriteSheet>(imageFile, clipWidth, clipHeight);
	assert(m_images);
}

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
	m_bases.emplace_back(m_images.get(), imageIndex, 128.0f, 128.0f, pos,
		15.0f);
}

SpriteSheet * BaseManager::Images()
{
	return m_images.get();
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
