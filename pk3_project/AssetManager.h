#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <SFML/Graphics.hpp>

#include <map>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

template <class AssetT>
class AssetManager //a class that supports reading textures, sounds, etc.
{
	std::map<std::string, AssetT> m_asset; //container storing asset
	std::string error_text = "Failed loading asset : "; //error text to display

public:
	AssetManager();
	~AssetManager();

	void LoadAsset(const std::string& asset_id, const std::string& asset_path); //loading the asset from the directory
	AssetT &GetAsset(const std::string& asset_id); //get asset

	template<typename AssetT>
	friend std::ostream& operator<<(std::ostream& out, const AssetManager<AssetT>& node); //operator that shows error text in console
};

#pragma region Constructors

template <class AssetT>
AssetManager<AssetT>::AssetManager() {}

template <class AssetT>
AssetManager<AssetT>::~AssetManager() {}

#pragma endregion

#pragma region  Class methods

template <class AssetT>
void AssetManager<AssetT>::LoadAsset(const std::string& asset_id, const std::string& asset_path)
{
	AssetT as_T;

	if (!as_T.loadFromFile(asset_path)) //if cannot load file
	{	
		AssetManager tmp_error;
		std::cerr << tmp_error << asset_id << std::endl; //show error
	}
	else //add to container
	{
		this->m_asset[asset_id] = as_T;
	}
}

template<class AssetT>
AssetT & AssetManager<AssetT>::GetAsset(const std::string& asset_id)
{
	return this->m_asset.at(asset_id); //get asset
}

#pragma endregion

#pragma Operators

template <class AssetT>
inline std::ostream& operator<<(std::ostream& os, const AssetManager<AssetT>& n)
{
	return os << n.error_text; //error text to std::ostream
}

#pragma endregion

#endif