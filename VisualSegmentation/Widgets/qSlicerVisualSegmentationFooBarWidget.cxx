/*==============================================================================

  Program: 3D Slicer

  Copyright (c) Kitware Inc.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Jean-Christophe Fillion-Robin, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// FooBar Widgets includes
#include "qSlicerVisualSegmentationFooBarWidget.h"
#include "ui_qSlicerVisualSegmentationFooBarWidget.h"

//-----------------------------------------------------------------------------
/// \ingroup Slicer_QtModules_VisualSegmentation
class qSlicerVisualSegmentationFooBarWidgetPrivate
  : public Ui_qSlicerVisualSegmentationFooBarWidget
{
  Q_DECLARE_PUBLIC(qSlicerVisualSegmentationFooBarWidget);
protected:
  qSlicerVisualSegmentationFooBarWidget* const q_ptr;

public:
  qSlicerVisualSegmentationFooBarWidgetPrivate(
    qSlicerVisualSegmentationFooBarWidget& object);
  virtual void setupUi(qSlicerVisualSegmentationFooBarWidget*);
};

// --------------------------------------------------------------------------
qSlicerVisualSegmentationFooBarWidgetPrivate
::qSlicerVisualSegmentationFooBarWidgetPrivate(
  qSlicerVisualSegmentationFooBarWidget& object)
  : q_ptr(&object)
{
}

// --------------------------------------------------------------------------
void qSlicerVisualSegmentationFooBarWidgetPrivate
::setupUi(qSlicerVisualSegmentationFooBarWidget* widget)
{
  this->Ui_qSlicerVisualSegmentationFooBarWidget::setupUi(widget);
}

//-----------------------------------------------------------------------------
// qSlicerVisualSegmentationFooBarWidget methods

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationFooBarWidget
::qSlicerVisualSegmentationFooBarWidget(QWidget* parentWidget)
  : Superclass( parentWidget )
  , d_ptr( new qSlicerVisualSegmentationFooBarWidgetPrivate(*this) )
{
  Q_D(qSlicerVisualSegmentationFooBarWidget);
  d->setupUi(this);
}

//-----------------------------------------------------------------------------
qSlicerVisualSegmentationFooBarWidget
::~qSlicerVisualSegmentationFooBarWidget()
{
}
