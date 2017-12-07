#pragma once
#include <map>
#include "core/tools/Camera.h"

class TilePool {
public:
	using TileHash = __int64;
	using TypeIndex = short;

	class Type {
	public:
		Type() : m_id_(0) {}

		explicit Type(TypeIndex id)
			: m_id_(id) {
		}
		TypeIndex GetId() const {
			return m_id_;
		}
	private:
		TypeIndex m_id_;
	};

	bool HasTile(int tileX, int tileY);
	Type* GetType(int tileX, int tileY);
	size_t Count() const;

	bool LoadConfig(char* path);
	void AddTile(int tileX, int tileY, TypeIndex type);
	void Render(Camera& camera);

private:
	
	void AddTileType(Type& type);

	using TileMap = std::map<TileHash, TypeIndex>;
	using TypeMap = std::map<TypeIndex, Type>;

	TileMap m_tileMap_;
	TypeMap m_typeMap_;

	static TileHash TileHashConvert(int tileX, int tileY);
};
