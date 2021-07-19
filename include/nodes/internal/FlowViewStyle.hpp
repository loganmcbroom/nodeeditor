#pragma once

#include <QtGui/QColor>

#include "Style.hpp"

namespace QtNodes
{

class FlowViewStyle : public Style
{
public:

  FlowViewStyle();

  FlowViewStyle(QString jsonText);

public:

  static void setStyle(QString jsonText);
  static FlowViewStyle & style();

private:

  void loadJsonText(QString jsonText) override;

  void loadJsonFile(QString fileName) override;

  void loadJsonFromByteArray(QByteArray const &byteArray) override;

public:

  QColor BackgroundColor;
  QColor FineGridColor;
  QColor CoarseGridColor;
};
}
