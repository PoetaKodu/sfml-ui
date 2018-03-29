#pragma once

#include GAMEPROJECT_PCH

#include <GameProject/Interfaces/Updatable.hpp>
#include <GameProject/Core/Memory.hpp>

namespace gameproject
{	

using TextureAsset = SharedPtr<sf::Texture>;

/// <summary>
/// Holds and manages every texture.
/// </summary>
/// <remarks>
/// <para>M at the end stands for "Module"</para>
/// </remarks>
class TextureRegistryM final
	: public IUpdatable
{
	// Aliases:
	using CleanupIntervalType	= std::chrono::milliseconds;
public:
	// Constants:

	static constexpr CleanupIntervalType cxCleanupInterval{ 5000 };

	// Aliases:

	using RegistryType	= std::map<std::string, TextureAsset>;
		
	// Methods:
		
	/// <summary>
	/// Initializes a new instance of the <see cref="TextureRegistryM"/> class.
	/// </summary>
	TextureRegistryM();

	/// <summary>
	/// Provides texture with specified name.
	/// </summary>
	/// <param name="assetName_">Name of the asset.</param>
	/// <param name="fileName_">Name of the file.</param>
	/// <returns>Shared pointer to the resource - a texture - or null if failed.</returns>
	TextureAsset provide(const std::string & assetName_, const std::string & fileName_ = "");
				
	/// <summary>
	/// Loads texture with the specified file name and maps it using asset name as a key.
	/// </summary>
	/// <param name="assetName_">Name of the asset - a map key.</param>
	/// <param name="fileName_">Name of the file.</param>
	/// <returns>Shared pointer to the resource - a texture - or null if failed.</returns>
	TextureAsset load(const std::string & assetName_, const std::string & fileName_);
		
	/// <summary>
	/// Returns texture with the specified asset name.
	/// </summary>
	/// <param name="assetName_">Name of the asset.</param>
	/// <returns>Shared pointer to the resource - a texture - or null if not exist.</returns>
	TextureAsset get(const std::string & assetName_);
		
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="deltaTime_">Time that passed since previous frame.</param>
	/// <param name="frameTime_">The frame start time.</param>
	virtual void update(double deltaTime_, const IUpdatable::TimePoint & frameTime_) override;

	/// <summary>
	/// Returns cref to texture map.
	/// </summary>
	/// <returns>Returns cref to texture map.</returns>
	const RegistryType &getTextures() const {
		return m_textures;
	}
private:
	// Methods:
		
	/// <summary>
	/// Loads the texture from file.
	/// </summary>
	/// <param name="fileName_">Name of the file.</param>
	/// <returns>Shared pointer to the resource - a texture - or null if failed.</returns>
	TextureAsset loadTextureFromFile(const std::string & fileName_) const;

	// Members:

	RegistryType			m_textures;
	IUpdatable::TimePoint	m_lastCleanup;
};

}