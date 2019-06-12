#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "category.h"
#include "categorylist.h"
#include "categorymodel.h"
#include "apiclient.h"

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/9Meow.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).

    QGuiApplication* app = SailfishApp::application(argc, argv);
    QQuickView *view  = SailfishApp::createView();

    // Check if overwriting bindings with static javascript assignement
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    qmlRegisterType<CategoryModel>("CategoryModel", 1, 0, "CategoryModel" );
    qmlRegisterUncreatableType<CategoryList>("CategoryModel", 1, 0, "CategoryList", QStringLiteral("Don't define CategoryList in QML!") );
    qmlRegisterUncreatableType<Category>("CategoryModel", 1, 0, "Category", QStringLiteral("Don't define Category in QML!") );


    //
    ApiClient apiClient;
    apiClient.getAllCategory();
    //

    CategoryList categoryList;

    view->rootContext()->setContextProperty("categoryList", &categoryList);

    view->setSource(SailfishApp::pathTo("qml/9Meow.qml"));
    view->show();

    return app->exec();
}
