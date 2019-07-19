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

// Qt includes
#include <QDebug>
#include <QMessageBox>
// SlicerQt includes
#include "qSlicerVisualSegmentationModuleWidget.h"
#include "ui_qSlicerVisualSegmentationModuleWidget.h"
#include "qVisualSegmentEditorWidget.h"



#include <qSlicerApplication.h>
#include <vtkSmartPointer.h>
#include <vtkMRMLSliceCompositeNode.h>
#include <vtkMRMLScene.h>
#include <qSlicerLayoutManager.h>
#include <vtkMRMLSegmentEditorNode.h>
#include <qSlicerSegmentEditorEffectFactory.h>
//#include <qMRMLSegmentEditorWidget.h>
#include <vtkMRMLSegmentationNode.h>

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_ExtensionTemplate
class qSlicerVisualSegmentationModuleWidgetPrivate: public Ui_qSlicerVisualSegmentationModuleWidget
{
public:
  qSlicerVisualSegmentationModuleWidgetPrivate();
  vtkMRMLSegmentEditorNode* m_ParameterSetNode;
  qVisualSegmentEditorWidget* SegmentEditorWidget;
};

//-----------------------------------------------------------------------------
// qSlicerVisualSegmentationModuleWidgetPrivate methods

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationModuleWidgetPrivate::qSlicerVisualSegmentationModuleWidgetPrivate()
{
	m_ParameterSetNode = nullptr;
}

//-----------------------------------------------------------------------------
// qSlicerVisualSegmentationModuleWidget methods

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationModuleWidget::qSlicerVisualSegmentationModuleWidget(QWidget* _parent)
  : Superclass( _parent )
  , d_ptr( new qSlicerVisualSegmentationModuleWidgetPrivate )
{
}

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationModuleWidget::~qSlicerVisualSegmentationModuleWidget()
{
}

//-----------------------------------------------------------------------------
void qSlicerVisualSegmentationModuleWidget::setup()
{
  Q_D(qSlicerVisualSegmentationModuleWidget);
  d->setupUi(this);
  this->Superclass::setup();
  d->SegmentEditorWidget = new qVisualSegmentEditorWidget();
   selectParameterNode();
   setDefaultSegmentation();
  this->layout()->addWidget(d->SegmentEditorWidget);
  vtkMRMLScene* newScene = qSlicerApplication::application()->mrmlScene();
  QObject::connect(qSlicerSegmentEditorEffectFactory::instance(), SIGNAL(effectRegistered(QString)), this, SLOT(editorEffectRegistered()));
  d->SegmentEditorWidget->setMaximumNumberOfUndoStates(10);
  vtkMRMLScene* scene = d->SegmentEditorWidget->mrmlScene();

  //if (newScene == d->SegmentEditorWidget->mrmlScene())
  //{
	 // return;
  //}
  d->SegmentEditorWidget->setMRMLScene(newScene);

  this->qvtkReconnect(scene, newScene, vtkMRMLScene::StartCloseEvent,
	  this, SLOT(onSceneStartClose()));

  this->qvtkReconnect(scene, newScene, vtkMRMLScene::EndImportEvent,
	  this, SLOT(onSceneEndImport()));

  this->qvtkReconnect(scene, newScene, vtkMRMLScene::EndCloseEvent,
	  this, SLOT(onSceneEndClose()));

}


void qSlicerVisualSegmentationModuleWidget::editorEffectRegistered()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);
	d->SegmentEditorWidget->updateEffectList();
}

void qSlicerVisualSegmentationModuleWidget::selectParameterNode()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);

	std::string segmentEditorSingletonTag = "SegmentEditor";

	vtkMRMLScene* scene = qSlicerApplication::application()->mrmlScene();
	if (scene)
	{
		vtkMRMLNode* node = scene->GetSingletonNode(segmentEditorSingletonTag.c_str(), "vtkMRMLSegmentEditorNode");
		vtkMRMLSegmentEditorNode* segmentEditorNode = vtkMRMLSegmentEditorNode::SafeDownCast(node);
		if (segmentEditorNode == nullptr)
		{
			std::cout << "make update" << endl;
			vtkSmartPointer<vtkMRMLSegmentEditorNode> segEditorNode = vtkSmartPointer<vtkMRMLSegmentEditorNode>::New();
			segEditorNode->SetSingletonTag(segmentEditorSingletonTag.c_str());
			vtkMRMLNode* segNode = scene->AddNode(segEditorNode);
			segmentEditorNode = vtkMRMLSegmentEditorNode::SafeDownCast(segNode);
			if (segmentEditorNode)
			{
				std::cout << "set 11111111" << endl;
				d->SegmentEditorWidget->setMRMLSegmentEditorNode(segmentEditorNode);
				d->SegmentEditorWidget->updateWidgetFromMRML();
			}

		}
		if (segmentEditorNode == d->m_ParameterSetNode)
			return;
		d->m_ParameterSetNode = segmentEditorNode;
		d->SegmentEditorWidget->setMRMLSegmentEditorNode(segmentEditorNode);
	}
}

vtkMRMLSliceCompositeNode* qSlicerVisualSegmentationModuleWidget::getCompositeNode(QString layoutName)
{
	Q_D(qSlicerVisualSegmentationModuleWidget);

	vtkMRMLScene* scene = qSlicerApplication::application()->mrmlScene();
	int count = scene->GetNumberOfNodesByClass("vtkMRMLSliceCompositeNode");
	std::cout << "173" <<std::to_string(count) << endl;
	for (int i = 0; i < count; i++)
	{
		std::cout << "173" << std::to_string(i) << endl;
		vtkMRMLNode* node = scene->GetNthNodeByClass(i, "vtkMRMLSliceCompositeNode");
		vtkMRMLSliceCompositeNode* compNode = vtkMRMLSliceCompositeNode::SafeDownCast(node);
		if (!layoutName.isEmpty() && compNode->GetLayoutName() != layoutName)
		{
			continue;
		}
		return compNode;
	}

	return nullptr;
}

std::string  qSlicerVisualSegmentationModuleWidget::getDefaultMasterVolumeNodeID()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);

	qSlicerLayoutManager* layoutManager = qSlicerApplication::application()->layoutManager();
	// Use first background volume node in any of the displayed layouts
	for (QString slicerName : layoutManager->sliceViewNames())
	{
		vtkMRMLSliceCompositeNode* compositeNode = getCompositeNode(slicerName);
		if (compositeNode->GetBackgroundVolumeID() != nullptr)
		{
			return compositeNode->GetBackgroundVolumeID();;
		}
	}
	//Use first background volume node in any of the displayed layouts
	for (QString slicerName : layoutManager->sliceViewNames())
	{

		vtkMRMLSliceCompositeNode* compositeNode = getCompositeNode(slicerName);
		if (compositeNode->GetForegroundVolumeID() != nullptr)
		{
			return compositeNode->GetForegroundVolumeID();;
		}
	}

	return "";
}

void  qSlicerVisualSegmentationModuleWidget::enter()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);

	if (d->SegmentEditorWidget->turnOffLightboxes())
	{
		QMessageBox::warning(nullptr, QString::fromLocal8Bit("Segment Editor"), QString::fromLocal8Bit("Segment Editor is not compatible with slice viewers in light box mode.\nViews are being reset."));
	}
	// Allow switching between effectsand selected segment using keyboard shortcuts
	d->SegmentEditorWidget->installKeyboardShortcuts();
	// Set parameter set node if absent
	this->selectParameterNode();
	d->SegmentEditorWidget->updateWidgetFromMRML();
	vtkMRMLScene* scene = qSlicerApplication::application()->mrmlScene();
	// If no segmentation node exists then create one so that the user does not have to create one manually
	if (d->SegmentEditorWidget->segmentationNodeID().isEmpty())
	{
		vtkMRMLNode* node = scene->GetFirstNode(nullptr, "vtkMRMLSegmentEditorNode");
		vtkMRMLSegmentEditorNode* segmentEditorNode = vtkMRMLSegmentEditorNode::SafeDownCast(node);
		if (segmentEditorNode == nullptr)
		{
			vtkMRMLNode* newNode = scene->AddNewNodeByClass("vtkMRMLSegmentEditorNode");
			segmentEditorNode = vtkMRMLSegmentEditorNode::SafeDownCast(newNode);
		}
		d->SegmentEditorWidget->setSegmentationNode(segmentEditorNode);
		if (d->SegmentEditorWidget->masterVolumeNodeID().isEmpty())
		{
			
			std::string nodeId = getDefaultMasterVolumeNodeID();
			if (!nodeId.empty())
			{
				std::cout << "id:::" << nodeId << endl;
				d->SegmentEditorWidget->setMasterVolumeNodeID(QString::fromStdString(nodeId));
			}

		}
	}
	this->Superclass::enter();
}

void qSlicerVisualSegmentationModuleWidget::exit()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);

	d->SegmentEditorWidget->setActiveEffect(nullptr);
	d->SegmentEditorWidget->uninstallKeyboardShortcuts();
	d->SegmentEditorWidget->removeViewObservations();
	this->Superclass::exit();
}

void qSlicerVisualSegmentationModuleWidget::onSceneStartClose()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);
	d->m_ParameterSetNode = nullptr;
	d->SegmentEditorWidget->setSegmentationNode(nullptr);
	d->SegmentEditorWidget->removeViewObservations();
}

void qSlicerVisualSegmentationModuleWidget::onSceneEndClose()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);
	if (Superclass::isEntered())
	{
		selectParameterNode();
		d->SegmentEditorWidget->updateWidgetFromMRML();
	}
	
}

void qSlicerVisualSegmentationModuleWidget::onSceneEndImport()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);
	if (Superclass::isEntered())
	{
		selectParameterNode();
		d->SegmentEditorWidget->updateWidgetFromMRML();
	}
	
}

void qSlicerVisualSegmentationModuleWidget::cleanup()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);
	d->SegmentEditorWidget->removeViewObservations();
	QObject::disconnect(qSlicerSegmentEditorEffectFactory::instance(), SIGNAL(effectRegistered(QString)), this, SLOT(editorEffectRegistered()));
}

void qSlicerVisualSegmentationModuleWidget::setDefaultSegmentation()
{
	Q_D(qSlicerVisualSegmentationModuleWidget);
	vtkMRMLNode* node = d->SegmentEditorWidget->segmentationNode();
	vtkMRMLSegmentationNode* segmentationNode = vtkMRMLSegmentationNode::SafeDownCast(node);
	if (segmentationNode == nullptr)
	{
		vtkMRMLNode *segNode = 	qSlicerApplication::application()->mrmlScene()->AddNewNodeByClass("vtkMRMLSegmentationNode");
	}
}