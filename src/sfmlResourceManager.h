#pragma once

#include <SFML/Graphics/Font.hpp>
#include "resourceManager.h"
#include "sfmlBitmap.h"

class SFMLResourceManager : public ResourceManager {
 private:
  sf::Font font;

  virtual void loadFont();

  virtual Bitmap *loadBitmap(std::string path, Point<int> expectedSize);
public:
  SFMLResourceManager(std::string _execPath);
  const sf::Font &getFont();
};
