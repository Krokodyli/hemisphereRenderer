#pragma once

#include "toolbar.h"

class AppToolbar : public Toolbar {
 private:
  Checkbox *drawMeshCheckbox;
  Slider *meridianCountSlider;
  Slider *parallelsCountSlider;

  Slider *lightColorRSlider;
  Slider *lightColorGSlider;
  Slider *lightColorBSlider;

  Checkbox *spiralLightMoveCheckbox;
  Slider *lightZSlider;

  Slider *kdSlider;
  Slider *ksSlider;
  Slider *mSlider;
  Slider *kSlider;

  void makeSlider(Slider **var, Point<float> pos, float min, float curr,
                  float max, SliderType type, std::string label);
  void makeCheckbox(Checkbox **var, Point<float> pos, bool initialState,
                    std::string label);

public:
  AppToolbar(Point<int> position, Point<int> size);
  virtual void setUpControls();
  virtual void setUpEventHandlers(RenderConfig *renderConfig);
};
