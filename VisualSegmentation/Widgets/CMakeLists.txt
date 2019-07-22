project(qSlicer${MODULE_NAME}ModuleWidgets)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "Q_SLICER_MODULE_${MODULE_NAME_UPPER}_WIDGETS_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  ${Slicer_ModuleLogic_INCLUDE_DIRS}
  ${Slicer_ModuleMRML_INCLUDE_DIRS}
  ${MRMLCore_INCLUDE_DIRS}
  ${Slicer_Libs_INCLUDE_DIRS}
  ${Slicer_Base_INCLUDE_DIRS}
  ${Slicer_ModuleLogic_INCLUDE_DIRS}
  ${Slicer_ModuleMRML_INCLUDE_DIRS} 
  ${Slicer_ModuleWidgets_INCLUDE_DIRS} 
  D:/v3r/slicer/Modules/Loadable/Segmentations/EditorEffects
  D:/v3r/slicer-build/Slicer-build/Modules/Loadable/Segmentations/EditorEffects
  D:/v3r/Slicer-build/Slicer-build/lib/Slicer-4.11/qt-loadable-modules/Release/
  #D:/v3r/Slicer-build/Slicer-build/lib/Slicer-4.11/qt-loadable-modules/Release/qSlicerSegmentationsModuleWidgets.lib
  )

set(${KIT}_SRCS
  qSlicer${MODULE_NAME}FooBarWidget.cxx
  qSlicer${MODULE_NAME}FooBarWidget.h
   qVisualSegmentEditorWidget.cxx
  qVisualSegmentEditorWidget.h
qVisualSegmentsTableView.h
qVisualSegmentsTableView.cxx
 
  )

set(${KIT}_MOC_SRCS
  qSlicer${MODULE_NAME}FooBarWidget.h
  qVisualSegmentEditorWidget.h
  qVisualSegmentsTableView.h
  )

set(${KIT}_UI_SRCS
  ../Resources/UI/qSlicer${MODULE_NAME}FooBarWidget.ui
  ../Resources/UI/qVisualSegmentEditorWidget.ui
  ../Resources/UI/qVisualSegmentsTableView.ui
  )

set(${KIT}_RESOURCES
  ../Resources/qSlicer${MODULE_NAME}Module.qrc
  )

set(${KIT}_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleLogic
  qSlicerSegmentationsModuleWidgets
  qSlicerSegmentationsEditorEffects
  )

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleWidgets(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  MOC_SRCS ${${KIT}_MOC_SRCS}
  UI_SRCS ${${KIT}_UI_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  RESOURCES ${${KIT}_RESOURCES}
  WRAP_PYTHONQT
  )
