#include "resourceManager.h"

ResourceManager::ResourceManager(std::string _execPath)
  : execPath(_execPath) {
  generateResourcesPath();
}

void ResourceManager::generateResourcesPath() {
  path rootPath = std::filesystem::current_path();
  path p = execPath;
  rootPath /= p.parent_path();
  rootPath = std::filesystem::weakly_canonical(rootPath);
  resourcesPath = rootPath.string() + resourcesDir;
}

void ResourceManager::loadResources() {
  loadFont();
}

const sf::Font &ResourceManager::getFont() {
  return font;
}

void ResourceManager::loadFont() {
  font.loadFromFile(resourcesPath + "font.ttf");
}
