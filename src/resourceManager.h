#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <filesystem>

using std::filesystem::path;
using std::filesystem::weakly_canonical;
using std::string;

class ResourceManager {
 private:
  const string resourcesDir = "/resources/";
  std::string execPath;

  string resourcesPath;

  sf::Font font;

  void generateResourcesPath();

  void loadFont();

public:
  ResourceManager(std::string _execPath);

  void loadResources();
  const sf::Font &getFont();
};
