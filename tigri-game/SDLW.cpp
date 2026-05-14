#include "SDLW.h"
#include "memtrace.h"

SDL_Renderer* SDLW_Texture::m_renderer;
std::vector<TextureInstance> SDLW_Texture::m_textureInstances;

SDLW_Texture::SDLW_Texture(const char* path)
	: Debuggable("SDLW_Texture")
	, m_path(path)
{
	TextureInstance newInstance(path);
	auto sameInstanceIt = GameUtils::find(m_textureInstances.begin(), m_textureInstances.end(), newInstance);
	if (sameInstanceIt != m_textureInstances.end())
	{
		// update existing instance
		TextureInstance& instanceToUpdate = *sameInstanceIt;
		m_texture = instanceToUpdate.texturePtr;
		instanceToUpdate.counter++;
		std::cout << "Path: " << path << ", increased counter: " << instanceToUpdate.counter << std::endl;
	}
	else
	{
		// add new instance
		SDL_Surface* tmpSurface = IMG_Load(path);
		if (tmpSurface)
		{
			m_texture = SDL_CreateTextureFromSurface(m_renderer, tmpSurface);
			SDL_FreeSurface(tmpSurface);
			newInstance.texturePtr = m_texture;
			m_textureInstances.push_back(newInstance);
		}
		else
		{
			std::cout << "Failed to load surface from path: " << path << std::endl;
			m_texture = nullptr;
		}
		std::cout << "Path: " << path << ", NEW (counter: 1)" << std::endl;
	}
}

SDLW_Texture::~SDLW_Texture()
{
	auto sameInstanceIt = GameUtils::find(m_textureInstances.begin(), m_textureInstances.end(), TextureInstance(m_path));
	if (sameInstanceIt != m_textureInstances.end())
	{
		TextureInstance& sameInstance = *sameInstanceIt;
		sameInstance.counter--;
		if (sameInstance.counter == 0)
		{
			std::cout << "Path: " << m_path << ", DELETED (counter reached 0)" << std::endl;
			if (sameInstance.texturePtr)
				SDL_DestroyTexture(sameInstance.texturePtr);
			m_textureInstances.erase(sameInstanceIt);
		}
		else
		{
			std::cout << "Path: " << m_path << ", decreased counter: " << sameInstance.counter << std::endl;
		}
	}
}