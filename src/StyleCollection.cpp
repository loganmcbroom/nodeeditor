#include "StyleCollection.hpp"

using QtNodes::StyleCollection;
using QtNodes::NodeStyle;
using QtNodes::ConnectionStyle;
using QtNodes::FlowViewStyle;

NodeStyle &
StyleCollection::
nodeStyle()
{
  return instance()._nodeStyle;
}


ConnectionStyle &
StyleCollection::
connectionStyle()
{
  return instance()._connectionStyle;
}


FlowViewStyle &
StyleCollection::
flowViewStyle()
{
  return instance()._flowViewStyle;
}


void
StyleCollection::
setNodeStyle(NodeStyle nodeStyle)
{
  instance()._nodeStyle = nodeStyle;
}


void
StyleCollection::
setConnectionStyle(ConnectionStyle connectionStyle)
{
  instance()._connectionStyle = connectionStyle;
}


void
StyleCollection::
setFlowViewStyle(FlowViewStyle flowViewStyle)
{
  instance()._flowViewStyle = flowViewStyle;
}



StyleCollection&
StyleCollection::
instance()
{
  static StyleCollection collection;

  return collection;
}
