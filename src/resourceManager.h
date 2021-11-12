#pragma once

#include <string>
#include <filesystem>
#include <unordered_map>
#include "point.h"
#include "bitmap.h"

class ResourceManager {
 protected:
  std::string execPath;

  const std::string resourcesDir = "resources/";
  std::string resourcesPath;

  const std::string fontPath = "font.ttf";

  const std::string texturesDir = "textures/";
  std::unordered_map<std::string, Bitmap*> textures;

  const std::string normalMapsDir = "normalMaps/";
  std::unordered_map<std::string, Bitmap *> normalMaps;

  void generateResourcesPath();

  virtual void loadFont();

  std::unordered_map<std::string, Bitmap *>
    loadAllImagesWithSize(std::string dir, Point<int> expectedSize);

  virtual Bitmap *loadBitmap(std::string path, Point<int> expectedSize) = 0;

 public:
  ResourceManager(std::string _execPath);
  virtual ~ResourceManager();

  void loadResources(Point<int> expectedTexturesSize);

  std::unordered_map<std::string, Bitmap *> getTextures();
  std::unordered_map<std::string, Bitmap *> getNormalMaps();
};
