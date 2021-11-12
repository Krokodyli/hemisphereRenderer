#include "sfmlResourceManager.h"

SFMLResourceManager::SFMLResourceManager(std::string _execPath)
  : ResourceManager(_execPath) { }

const sf::Font &SFMLResourceManager::getFont() {
  return font;
}

void SFMLResourceManager::loadFont() {
  font.loadFromFile(resourcesPath + fontPath);
}

Bitmap *SFMLResourceManager::loadBitmap(std::string path,
                                        Point<int> expectedSize) {
  sf::Image image;
  if(!image.loadFromFile(path)
     || ((int)image.getSize().x != expectedSize.x
         || (int)image.getSize().y != expectedSize.y))
    return nullptr;
  else
    return new SFMLBitmap(image);
}
