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
  resourcesPath = rootPath.string() + resourcesPath;
}
