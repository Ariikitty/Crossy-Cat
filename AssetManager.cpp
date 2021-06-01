#include "AssetManager.h"
#include "Components.h"

AssetManager::AssetManager(Manager* man) : manager(man)
{}

AssetManager::~AssetManager()
{}

void AssetManager::CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id, int line)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 64, 64, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.getComponent<SpriteComponent>().animIndex = 0;
	projectile.addComponent<ProjectileComponent>(range, speed, vel, line);
	projectile.addComponent<ColliderComponent>("object");
	projectile.addGroup(Game::groupObjects);
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	textures.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}