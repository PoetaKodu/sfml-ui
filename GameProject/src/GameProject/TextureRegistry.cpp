#include "GameProjectPCH.hpp"

#include <GameProject/TextureRegistry.hpp>

namespace gameproject
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextureAsset TextureRegistryM::provide(const std::string & assetName_, const std::string & fileName_)
	{
		// Check if texture is already loaded:
		if (auto result = this->get(assetName_))
			return result; // return the texture.
		
		// Otherwise load it:
		// Assign and return.
		return (m_textures[assetName_] = this->loadTextureFromFile(fileName_));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextureAsset TextureRegistryM::load(const std::string & assetName_, const std::string & fileName_)
	{
		// Otherwise load it:
		// Assign and return.
		return (m_textures[assetName_] = this->loadTextureFromFile(fileName_));
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextureAsset TextureRegistryM::get(const std::string & assetName_)
	{
		auto it = m_textures.find(assetName_);
		// Check if texture was found
		if (it != m_textures.end())
			return it->second;
		return nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void TextureRegistryM::update(double deltaTime_, const IUpdatable::TimePoint & frameTime_)
	{
		if (frameTime_ - m_lastCleanup > cxCleanupInterval)
		{
			m_lastCleanup = frameTime_;

			// TODO: perform cleanup.
			for (auto it = m_textures.begin(); it != m_textures.end(); )
			{
				// Check if specified texture's use_count is <= 1 (that means it is stored only inside texture registry)
				if (it->second.use_count() <= 1)
					m_textures.erase(it);
				else
					++it;
			}

		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	TextureAsset TextureRegistryM::loadTextureFromFile(const std::string & fileName_) const
	{
		TextureAsset result = std::make_shared<sf::Texture>();
		// Try loading from the texture:
		if (result->loadFromFile(fileName_)){
			return result;
		}
		else
			return nullptr;
	}
}