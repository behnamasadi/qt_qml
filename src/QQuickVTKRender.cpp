#include <vtkActor.h>
#include <vtkConeSource.h>
#include <vtkPointSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickVTKRenderItem.h>
#include <QQuickVTKRenderWindow.h>
#include <QQuickWindow>
#include <QUrl>

/*
https://discourse.vtk.org/t/best-way-to-implement-vtk-9-1-with-qt6-using-qml-and-qt-quick/6958
https://discourse.vtk.org/t/qml-example/7247/4
https://kitware.github.io/vtk-examples/site/CxxHowTo/
https://vtk.org/doc/nightly/html/classQQuickVTKRenderItem.html
https://discourse.vtk.org/t/is-it-possible-to-visualize-the-point-cloud-in-qvtkopenglwidget/8534/4

*/

int main(int argc, char *argv[]) {

  QQuickVTKRenderWindow::setupGraphicsBackend();
  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;

  engine.addImportPath("/home/behnam/usr/lib/qml");
  engine.load(QUrl("qrc:/qml/QQuickVTKRender.qml"));

  QObject *topLevel = engine.rootObjects().value(0);
  QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

  window->show();

  // Fetch the QQuick window using the standard object name set up in the
  // constructor
  QQuickVTKRenderItem *qquickvtkItem =
      topLevel->findChild<QQuickVTKRenderItem *>("ConeView");

  // Create a cone pipeline and add it to the view
  vtkNew<vtkActor> actor;

  vtkNew<vtkPolyDataMapper> mapper;
  vtkNew<vtkConeSource> cone;
  mapper->SetInputConnection(cone->GetOutputPort());

  actor->SetMapper(mapper);
  qquickvtkItem->renderer()->AddActor(actor);
  qquickvtkItem->renderer()->ResetCamera();
  qquickvtkItem->renderer()->SetBackground(0.5, 0.5, 0.7);
  qquickvtkItem->renderer()->SetBackground2(0.7, 0.7, 0.7);
  qquickvtkItem->renderer()->SetGradientBackground(true);
  qquickvtkItem->update();
  app.exec();
}
