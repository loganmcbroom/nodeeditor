cmake_minimum_required(VERSION 3.2)

project(NodeEditor CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DEBUG_POSTFIX d)

# Find the QtWidgets library
find_package(Qt5 5.3 COMPONENTS
    Core
    Widgets
    Gui
	OpenGL
	Concurrent
    )

set(CMAKE_AUTOMOC ON)

add_library( nodes
    include/nodes/internal/Compiler.hpp
    include/nodes/internal/Connection.hpp
    include/nodes/internal/ConnectionGeometry.hpp
    include/nodes/internal/ConnectionGraphicsObject.hpp
    include/nodes/internal/ConnectionState.hpp
    include/nodes/internal/ConnectionStyle.hpp
    include/nodes/internal/DataModelRegistry.hpp
    include/nodes/internal/Export.hpp
    include/nodes/internal/FlowScene.hpp
    include/nodes/internal/FlowView.hpp
    include/nodes/internal/FlowViewStyle.hpp
    include/nodes/internal/memory.hpp
    include/nodes/internal/Node.hpp
    include/nodes/internal/NodeData.hpp
    include/nodes/internal/NodeDataModel.hpp
    include/nodes/internal/NodeGeometry.hpp
    include/nodes/internal/NodeGraphicsObject.hpp
    include/nodes/internal/NodePainterDelegate.hpp
    include/nodes/internal/NodeState.hpp
    include/nodes/internal/NodeStyle.hpp
    include/nodes/internal/OperatingSystem.hpp
    include/nodes/internal/PortType.hpp
    include/nodes/internal/QStringStdHash.hpp
    include/nodes/internal/QUuidStdHash.hpp
    include/nodes/internal/Serializable.hpp
    include/nodes/internal/Style.hpp
    include/nodes/internal/StyleCollection.hpp
    include/nodes/internal/TypeConverter.hpp

    src/Connection.cpp
    src/ConnectionBlurEffect.cpp
    src/ConnectionGeometry.cpp
    src/ConnectionGraphicsObject.cpp
    src/ConnectionPainter.cpp
    src/ConnectionState.cpp
    src/ConnectionStyle.cpp
    src/DataModelRegistry.cpp
    src/FlowScene.cpp
    src/FlowView.cpp
    src/FlowViewStyle.cpp
    src/Node.cpp
    src/NodeConnectionInteraction.cpp
    src/NodeDataModel.cpp
    src/NodeGeometry.cpp
    src/NodeGraphicsObject.cpp
    src/NodePainter.cpp
    src/NodeState.cpp
    src/NodeStyle.cpp
    src/Properties.cpp
    src/StyleCollection.cpp

    resources/convert.png
    resources/DefaultStyle.json
    )
add_library(NodeEditor::NodeEditor ALIAS nodes)

target_link_libraries(nodes PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL
	Qt5::Concurrent
    )

target_include_directories(nodes
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nodes/internal>
    )

target_compile_definitions(nodes
  PUBLIC
	NODE_EDITOR_STATIC
    )

set_target_properties(nodes
  PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

# Copy lib to top level /lib folder
IF( CMAKE_BUILD_TYPE MATCHES Release )
    configure_file( ${CMAKE_BINARY_DIR}/lib/nodes.lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/nodes.lib COPYONLY )
ENDIF( CMAKE_BUILD_TYPE MATCHES Release )
IF( CMAKE_BUILD_TYPE MATCHES Debug )
    configure_file( ${CMAKE_BINARY_DIR}/lib/nodesd.lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/nodesd.lib COPYONLY )
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)