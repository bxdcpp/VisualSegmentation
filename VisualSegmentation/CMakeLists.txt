
#-----------------------------------------------------------------------------
set(MODULE_NAME VisualSegmentation)
set(MODULE_TITLE ${MODULE_NAME})

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

#-----------------------------------------------------------------------------
add_subdirectory(Logic)
add_subdirectory(Widgets)

#-----------------------------------------------------------------------------
set(MODULE_EXPORT_DIRECTIVE "Q_SLICER_QTMODULES_${MODULE_NAME_UPPER}_EXPORT")

# Current_{source,binary} and Slicer_{Libs,Base} already included
set(MODULE_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}/Logic
  ${CMAKE_CURRENT_BINARY_DIR}/Logic
  ${CMAKE_CURRENT_SOURCE_DIR}/Widgets
  ${CMAKE_CURRENT_BINARY_DIR}/Widgets

  ${qSlicerSegmentationsSubjectHierarchyPlugins_INCLUDE_DIRS}
  ${vtkSlicerSegmentationsModuleMRML_INCLUDE_DIRS}
  ${vtkSlicerSegmentationsModuleLogic_INCLUDE_DIRS}
  ${vtkSlicerSegmentationsModuleMRMLDisplayableManager_INCLUDE_DIRS}
  ${qSlicerSegmentationsModuleWidgets_INCLUDE_DIRS}
  ${qSlicerSegmentationsEditorEffects_INCLUDE_DIRS}
  ${qSlicerSubjectHierarchyModuleWidgets_INCLUDE_DIRS}
  ${vtkSlicerTerminologiesModuleLogic_INCLUDE_DIRS}
   D:/v3r/Slicer/Modules/Loadable/Segmentations/SubjectHierarchyPlugins
   D:/v3r/Slicer-build/Slicer-build/Modules/Loadable/Segmentations/SubjectHierarchyPlugins
   D:/v3r/Slicer/Modules/Loadable/Segmentations/EditorEffects
    D:/v3r/Slicer-build/Slicer-build/Modules/Loadable/Segmentations/EditorEffects
  )
  message("ss111111111111111:    ${vtkSlicerSegmentationsModuleMRML_INCLUDE_DIRS}/../")
set(MODULE_SRCS
  qSlicer${MODULE_NAME}Module.cxx
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.cxx
  qSlicer${MODULE_NAME}ModuleWidget.h
  )

set(MODULE_MOC_SRCS
  qSlicer${MODULE_NAME}Module.h
  qSlicer${MODULE_NAME}ModuleWidget.h
  )

set(MODULE_UI_SRCS
  Resources/UI/qSlicer${MODULE_NAME}ModuleWidget.ui
  )

set(MODULE_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  qSlicer${MODULE_NAME}ModuleWidgets
    qSlicerSegmentationsSubjectHierarchyPlugins
   qSlicerSubjectHierarchyModuleWidgets
  vtkSlicerTerminologiesModuleLogic
    qSlicerSegmentationsModuleWidgets
	qSlicerSegmentationsEditorEffects
  )

set(MODULE_RESOURCES
  Resources/qSlicer${MODULE_NAME}Module.qrc
  )

#-----------------------------------------------------------------------------
slicerMacroBuildLoadableModule(
  NAME ${MODULE_NAME}
  TITLE ${MODULE_TITLE}
  EXPORT_DIRECTIVE ${MODULE_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${MODULE_INCLUDE_DIRECTORIES}
  SRCS ${MODULE_SRCS}
  MOC_SRCS ${MODULE_MOC_SRCS}
  UI_SRCS ${MODULE_UI_SRCS}
  TARGET_LIBRARIES ${MODULE_TARGET_LIBRARIES}
  RESOURCES ${MODULE_RESOURCES}
  WITH_GENERIC_TESTS
  )

#-----------------------------------------------------------------------------
if(BUILD_TESTING)
  add_subdirectory(Testing)
endif()
