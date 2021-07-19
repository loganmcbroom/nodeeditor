cmake_minimum_required( VERSION 3.15 )

project( NodeEditor VERSION 1.0.0 LANGUAGES CXX )

# I don't know why these can't be set as target properties of NodeEditor, but it doesn't invoke automoc
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

add_library( NodeEditor STATIC
    # Headers listed for automoc
    include/nodes/internal/Compiler.hpp
    include/nodes/internal/Connection.hpp
    include/nodes/internal/ConnectionGeometry.hpp
    include/nodes/internal/ConnectionGraphicsObject.hpp
    include/nodes/internal/ConnectionState.hpp
    include/nodes/internal/ConnectionStyle.hpp
    include/nodes/internal/DataModelRegistry.hpp
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

    resources/NodeEditor.qrc
    )
add_library( NodeEditor::NodeEditor ALIAS NodeEditor )

target_compile_features( NodeEditor PUBLIC cxx_std_17 )
set_target_properties( NodeEditor PROPERTIES 
    CXX_EXTENSIONS OFF
    #CMAKE_AUTOMOC ON
    #CMAKE_AUTORCC ON
    #CMAKE_AUTOUIC ON
    #DEBUG_POSTFIX d
    )

# Set includes
target_include_directories( NodeEditor
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nodes/internal>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nodes/internal>
    )

#==================================================================================================
# Link Libraries
#==================================================================================================

find_package( Qt5 5.3 COMPONENTS
    Core
    Widgets
    Gui
	OpenGL
	Concurrent
    )
target_link_libraries( NodeEditor PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::OpenGL
	Qt5::Concurrent
    )


#==================================================================================================
# Installation
#==================================================================================================

include( GNUInstallDirs )
set( INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/NodeEditor )

# Copy include folder into install folder
install( DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )

# Create export target, but don't install yet
install(    
    TARGETS NodeEditor
    EXPORT NodeEditorTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

# Export the target to a script
install( 
    EXPORT NodeEditorTargets
    FILE NodeEditorTargets.cmake
    NAMESPACE NodeEditor::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/NodeEditor
)

# Create a ConfigVersion.cmake file
include( CMakePackageConfigHelpers )
write_basic_package_version_file(
    NodeEditorConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

# Generate Config file
configure_package_config_file( 
    ${CMAKE_CURRENT_LIST_DIR}/cmake/NodeEditorConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/NodeEditorConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
    )

# Install the config and configversion
install( 
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/NodeEditorConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/NodeEditorConfigVersion.cmake
    DESTINATION     
        ${INSTALL_CONFIGDIR}
    )


#==================================================================================================
# Export from the build tree
#==================================================================================================

#export( 
#    EXPORT NodeEditorTargets
#    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/NodeEditorTargets.cmake"
#    NAMESPACE NodeEditor::
#    )

# Register package in the User Package Registry
#set( CMAKE_EXPORT_PACKAGE_REGISTRY True )
#export( PACKAGE NodeEditor )