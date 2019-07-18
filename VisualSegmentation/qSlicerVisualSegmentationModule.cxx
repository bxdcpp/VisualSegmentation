/*==============================================================================

  Program: 3D Slicer

  Portions (c) Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

==============================================================================*/

// VisualSegmentation Logic includes
#include <vtkSlicerVisualSegmentationLogic.h> 

// VisualSegmentation includes
#include "qSlicerVisualSegmentationModule.h"
#include "qSlicerVisualSegmentationModuleWidget.h"

// Subject Hierarchy includes
#include "qSlicerSubjectHierarchyPluginHandler.h"
#include "qSlicerSubjectHierarchySegmentationsPlugin.h"
#include "qSlicerSubjectHierarchySegmentsPlugin.h"
#include <qSlicerApplication.h>
#include <qSlicerModuleManager.h>
#include <qSlicerSubjectHierarchyScriptedPlugin.h>
#include <vtkSlicerSegmentationsModuleLogic.h>
#include <PythonQt.h>
#include <vtkMRMLSegmentEditorNode.h>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerVisualSegmentationModulePrivate
{
public:
  qSlicerVisualSegmentationModulePrivate();
};

//-----------------------------------------------------------------------------
// qSlicerVisualSegmentationModulePrivate methods

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationModulePrivate::qSlicerVisualSegmentationModulePrivate()
{
}

//-----------------------------------------------------------------------------
// qSlicerVisualSegmentationModule methods

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationModule::qSlicerVisualSegmentationModule(QObject* _parent)
  : Superclass(_parent)
  , d_ptr(new qSlicerVisualSegmentationModulePrivate)
{
}

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationModule::~qSlicerVisualSegmentationModule()
{
}

//-----------------------------------------------------------------------------
QString qSlicerVisualSegmentationModule::helpText() const
{
  return "This is a loadable module that can be bundled in an extension";
}

//-----------------------------------------------------------------------------
QString qSlicerVisualSegmentationModule::acknowledgementText() const
{
  return "This work was partially funded by NIH grant NXNNXXNNNNNN-NNXN";
}

//-----------------------------------------------------------------------------
QStringList qSlicerVisualSegmentationModule::contributors() const
{
  QStringList moduleContributors;
  moduleContributors << QString("John Doe (AnyWare Corp.)");
  return moduleContributors;
}

//-----------------------------------------------------------------------------
QIcon qSlicerVisualSegmentationModule::icon() const
{
  return QIcon(":/Icons/VisualSegmentation.png");
}

//-----------------------------------------------------------------------------
QStringList qSlicerVisualSegmentationModule::categories() const
{
  return QStringList() << "Visual3D";
}

//-----------------------------------------------------------------------------
QStringList qSlicerVisualSegmentationModule::dependencies() const
{
  return QStringList() << "Segmentations" << "SubjectHierarchy";
}

//-----------------------------------------------------------------------------
void qSlicerVisualSegmentationModule::setup()
{
  this->Superclass::setup();
  // Register subject hierarchy plugins
  qSlicerSubjectHierarchyScriptedPlugin* scriptedPlugin = new qSlicerSubjectHierarchyScriptedPlugin();
  //qSlicerAbstractCoreModule* Module = qSlicerCoreApplication::application()->moduleManager()->module("Segmentations");
  //vtkSlicerSegmentationsModuleLogic* segLogic = vtkSlicerSegmentationsModuleLogic::SafeDownCast(Module->logic());
#ifdef Slicer_USE_PYTHONQT
  if (!qSlicerCoreApplication::testAttribute(qSlicerCoreApplication::AA_DisablePython))
  {
	  PythonQt::init();
	  PythonQtObjectPtr context = PythonQt::self()->getMainModule();
	  QVariant result = context.evalScript(QString("import SubjectHierarchyPlugins;SubjectHierarchyPlugins.SegmentEditorSubjectHierarchyPlugin.filePath"));
	  std::cout << "str:::" << result.toString().toStdString() << endl;
	  QString path = "D:/v3r/Slicer/Modules/Scripted/SegmentEditor/SubjectHierarchyPlugins/SegmentEditorSubjectHierarchyPlugin.py";
	  scriptedPlugin->setPythonSource(path);
  }
#endif

}

//-----------------------------------------------------------------------------
qSlicerAbstractModuleRepresentation* qSlicerVisualSegmentationModule
::createWidgetRepresentation()
{
  return new qSlicerVisualSegmentationModuleWidget;
}

//-----------------------------------------------------------------------------
vtkMRMLAbstractLogic* qSlicerVisualSegmentationModule::createLogic()
{
  return vtkSlicerVisualSegmentationLogic::New();
}