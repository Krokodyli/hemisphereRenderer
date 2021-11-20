#pragma once

#include "color.h"
#include "point.h"
#include <string>

class ButtonTheme {
 public:
  const Color fillColor = Color(255, 255, 255);
  const Color fontColor = Color(0, 0, 0);
  const int fontSize = 12;
  const Point<float> textOffset = Point<float>(4, 1);
};

class SliderTheme {
 public:
  const Point<float> indicatorSize = Point<float>(10, 20);
  const Point<float> barSize = Point<float>(100, 5);
  const Color indicatorColor = Color(255, 255, 255);
  const Color barColor = Color(255, 255, 255);
  const Point<float> labelOffset = Point<float>(120, -5);
  const int fontSize = 12;
  const Color fontColor = Color(255, 255, 255);
};

class CheckboxTheme {
public:
  const float size = 20;
  const Point<float> labelOffset = Point<float>(30, 4);
  const Color boxColor = Color(255, 255, 255);
  const Color crossColor = Color(0, 0, 0);
  const int fontSize = 12;
  const Color fontColor = Color(255, 255, 255);
};

class SelectboxTheme {
 public:
  const Color fontColor = Color(255, 255, 255);
  const Point<float> labelOffset = Point<float>(0, -20);
  const int fontSize = 12;
  const Point<float> buttonSize = Point<float>(15, 15);
  const float buttonGap = 10;
  const float textWidth = 150;
  const unsigned int maxStringSize = 21;
  const ButtonTheme *buttonTheme = new ButtonTheme();
};

struct AppConsts {
  const Point<int> windowSize = Point<int>(1200, 900);
  const std::string appTitle = "Hemisphere renderer";

  const Point<int> toolbarPos = Point<int>(0, 0);
  const Point<int> toolbarSize = Point<int>(300, 900);

  const Point<int> canvasPos = Point<int>(300, 0);
  const Point<int> canvasSize = Point<int>(900, 900);
  const Color canvasColor = Color(0, 0, 0);

  const int framerateLimit = 30;

  const bool showFPS = true;
  const Point<float> fpsLabelPosition = Point<float>(1170, 0);
  const int fpsLabelFontSize = 20;
  const Color fpsLabelColor = Color(255, 0, 0);

  const Point<float> toolbarControlsOffset = Point<float>(20, 20);

  const int meshRadius = 320;
  const Point<int> meshPos = Point<int>(750, 450);
  const Point<int> relativeMeshPos = Point<int>(450, 450);
  const int meshZPos = 0;
  const Color meshEdgesColor = Color(255, 255, 255);

  const Point<int> textureExpectedSize = Point<int>(1008, 1008);

  const float spiralMovePeriodTime = 3.0;
  const float spiralMovePeriodDistance = 200;
  const float spiralMoveRange = 1200;
  const std::string spiralSliderLabel = "Toggle light spiral move";

  const int minMeridianCount = 4;
  const int defaultMeridianCount = 32;
  const int maxMeridianCount = 32;
  const std::string meridianCountLabel = "Meridian count";

  const int minParallelCount = 1;
  const int defaultParallelCount = 1;
  const int maxParallelCount = 8;
  const std::string parallelCountLabel = "Parallel count";

  const float minKD = 0;
  const float defaultKD = 0.5;
  const float maxKD = 1;
  const std::string kdLabel = "KD factor";

  const float minKS = 0;
  const float defaultKS = 0.5;
  const float maxKS = 1;
  const std::string ksLabel = "KS factor";

  const int minM = 1;
  const int defaultM = 50;
  const int maxM = 100;
  const std::string mLabel = "M factor";

  const float minK = 0;
  const float defaultK = 0.5;
  const float maxK = 1;
  const std::string kLabel = "K factor";

  const bool defaultApproximateColoringMode = false;
  const std::string approxColoringLabel = "Approximate coloring mode";

  const Color defaultLightColor = Color(255, 255, 255);
  const float minLightZPos = 320 * 1.5;
  const float defaultLightZPos = 320 * 5;
  const float maxLightZPos = 320 * 10;
  const std::string lightZPosLabel = "Light Z pos";

  const std::string lightColorRLabel = "Light color R";
  const std::string lightColorGLabel = "Light color G";
  const std::string lightColorBLabel = "Light color B";

  const bool defaultRenderMeshMode = true;
  const std::string renderMeshModeLabel = "Toggle mesh drawing";

  const bool defaultSpiralMoveMode = true;

  const Color defaultTextureColor = Color(255, 255, 255);
  const Color defaultNormalMapColor = Color(0, 0, 0);

  const Point<float> verticesGrabTolerance = Point<float>(3, 3);

  const std::string textureSelectboxLabel = "Texture";
  const std::string normalMapSelectboxLabel = "Normal map";

  const float toolbarSmallGap = 40;
  const float toolbarBigGap = 70;

  const ButtonTheme *buttonTheme = new ButtonTheme();
  const CheckboxTheme *checkboxTheme = new CheckboxTheme();
  const SliderTheme *sliderTheme = new SliderTheme();
  const SelectboxTheme *selectboxTheme = new SelectboxTheme();
};
