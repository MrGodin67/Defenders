#include "SoundEffect.h"

bool SoundEffect::IsPlaying(const size_t& index)
{
	return sounds[index].IsPlaying();
}
