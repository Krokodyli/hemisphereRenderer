#include "resourceManager.h"
#include <filesystem>
#include <iostream>

ResourceManager::ResourceManager(std::string _execPath)
  : execPath(_execPath) {
  generateResourcesPath();
}

ResourceManager::~ResourceManager() { }

void ResourceManager::loadResources(Point<int> expectedTexturesSize) {
  loadFont();
  textures = loadAllImagesWithSize(resourcesPath + texturesDir,
                                   expectedTexturesSize);

  normalMaps = loadAllImagesWithSize(resourcesPath + normalMapsDir,
                                     expectedTexturesSize);
}

std::unordered_map<std::string, Bitmap *> ResourceManager::getTextures() {
  return textures;
}

std::unordered_map<std::string, Bitmap *> ResourceManager::getNormalMaps() {
  return normalMaps;
}

void ResourceManager::generateResourcesPath() {
  std::filesystem::path rootPath = std::filesystem::current_path();
  std::filesystem::path p = execPath;
  rootPath /= p.parent_path();
  rootPath = std::filesystem::weakly_canonical(rootPath);
  resourcesPath = rootPath.string() + "/" + resourcesDir;
}

void ResourceManager::loadFont() { }

std::unordered_map<std::string, Bitmap *>
ResourceManager::loadAllImagesWithSize(std::string dir,
                                       Point<int> expectedSize) {

  std::unordered_map<std::string, Bitmap*> dict;

  std::cout << "loading files for dir: " << dir << "\n";

  const std::filesystem::path dirPath(dir);
  if(!std::filesystem::exists(dirPath))
    return dict;

  for(auto const &dirEntry : std::filesystem::directory_iterator(dirPath)) {
    if(!dirEntry.is_regular_file())
      continue;

    std::cout << "Found " << dirEntry.path().string() << "\n";

    auto bitmapPath = std::filesystem::absolute(dirEntry.path());
    Bitmap *bitmap = loadBitmap(bitmapPath, expectedSize);
    if(bitmap != nullptr) {
      std::cout << "Added " << dirEntry.path().string() << "\n";
      dict[bitmapPath.filename()] = bitmap;
    }
  }

  return dict;
}
