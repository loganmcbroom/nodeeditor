cmake_minimum_required( VERSION 3.2 )

project( NodeEditor VERSION 1.0.0 LANGUAGES CXX )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

add_library( NodeEditor STATIC
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
set_target_properties( NodeEditor PROPERTIES CXX_EXTENSIONS OFF )

# Set includes
target_include_directories( NodeEditor
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nodes/internal>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/NodeEditor/internal>
    )

# Used in another script I'm not messing with
target_compile_definitions( NodeEditor
    PUBLIC
	    NODE_EDITOR_STATIC
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

export( 
    EXPORT NodeEditorTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/NodeEditorTargets.cmake"
    NAMESPACE NodeEditor::
    )

# Register package in the User Package Registry
set( CMAKE_EXPORT_PACKAGE_REGISTRY True )
export( PACKAGE NodeEditor )