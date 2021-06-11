#pragma once

#include <QObject>

#include "NodeData.hpp"
#include "memory.hpp"

#include <functional>

namespace QtNodes
{

class TypeConverter : public QObject
{ Q_OBJECT
public:
	virtual void operator()( std::shared_ptr<NodeData> data ) = 0;
    virtual std::shared_ptr<TypeConverter> createNew() = 0;
	virtual void cancel() {} // Called when conversion should be stopped

Q_SIGNALS:
	void finished( std::shared_ptr<NodeData> );
};

using SharedTypeConverter = std::shared_ptr<TypeConverter>;

// data-type-in, data-type-out
using TypeConverterId =
  std::pair<NodeDataType, NodeDataType>;

}
