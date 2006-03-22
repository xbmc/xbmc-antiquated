#pragma once
#include "guiwindow.h"

class CGUIWindowSettingsUICalibration :
      public CGUIWindow
{
public:
  CGUIWindowSettingsUICalibration(void);
  virtual ~CGUIWindowSettingsUICalibration(void);
  virtual bool OnMessage(CGUIMessage& message);
  virtual bool OnAction(const CAction &action);
  virtual void Render();
  virtual void ResetControls();

protected:
  int m_control;
};
