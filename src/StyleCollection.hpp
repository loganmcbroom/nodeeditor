#pragma once

#include "../include/nodes/NodeStyle"
#include "../include/nodes/ConnectionStyle"
#include "../include/nodes/FlowViewStyle"

namespace QtNodes
{

class StyleCollection
{
public:

  static
  NodeStyle &
  nodeStyle();

  static
  ConnectionStyle &
  connectionStyle();

  static
  FlowViewStyle &
  flowViewStyle();

public:

  static
  void
  setNodeStyle(NodeStyle);

  static
  void
  setConnectionStyle(ConnectionStyle);

  static
  void
  setFlowViewStyle(FlowViewStyle);

private:

  StyleCollection() = default;

  StyleCollection(StyleCollection const&) = delete;

  StyleCollection&
  operator=(StyleCollection const&) = delete;

  static
  StyleCollection&
  instance();

private:

  NodeStyle _nodeStyle;

  ConnectionStyle _connectionStyle;

  FlowViewStyle _flowViewStyle;
};
}
