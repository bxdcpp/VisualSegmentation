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

#ifndef __qSlicerVisualSegmentationModuleWidget_h
#define __qSlicerVisualSegmentationModuleWidget_h

// SlicerQt includes
#include "qSlicerAbstractModuleWidget.h"

#include "qSlicerVisualSegmentationModuleExport.h"

class qSlicerVisualSegmentationModuleWidgetPrivate;
class vtkMRMLNode;
class vtkMRMLSliceCompositeNode;

/// \ingroup Slicer_QtModules_ExtensionTemplate
class Q_SLICER_QTMODULES_VISUALSEGMENTATION_EXPORT qSlicerVisualSegmentationModuleWidget :
  public qSlicerAbstractModuleWidget
{
  Q_OBJECT

public:

  typedef qSlicerAbstractModuleWidget Superclass;
  qSlicerVisualSegmentationModuleWidget(QWidget *parent=0);
  virtual ~qSlicerVisualSegmentationModuleWidget();

  void selectParameterNode();
  vtkMRMLSliceCompositeNode* getCompositeNode(QString layoutName);

  std::string getDefaultMasterVolumeNodeID();
  void enter() override;
  void exit() override;



public slots:
	void editorEffectRegistered();
	void onSceneStartClose();
	void onSceneEndClose();
	void onSceneEndImport();

	void cleanup();

	void setDefaultSegmentation();

protected:
  QScopedPointer<qSlicerVisualSegmentationModuleWidgetPrivate> d_ptr;

  virtual void setup();

private:
  Q_DECLARE_PRIVATE(qSlicerVisualSegmentationModuleWidget);
  Q_DISABLE_COPY(qSlicerVisualSegmentationModuleWidget);
};

#endif
