#ifdef QT_QML_DEBUG
#include <QtQuick>


#endif

#include <sailfishapp.h>

#include "category.h"
#include "categorylist.h"
#include "categorymodel.h"
#include "catimage.h"
#include "catimagelist.h"
#include "catimagemodel.h"
#include "apiclient.h"
#include <QTextStream>
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

    qmlRegisterType<CatImageModel>("CatImageModel", 1, 0, "CatImageModel" );
    qmlRegisterUncreatableType<CatImageList>("CatImageModel", 1, 0, "CatImageList", QStringLiteral("Don't define CatImageList in QML!") );
    qmlRegisterUncreatableType<CatImage>("CatImageModel", 1, 0, "CatImage", QStringLiteral("Don't define CatImage in QML!") );
    // https://doc.qt.io/qt-5/qsortfilterproxymodel.html#details
    // POUR LE TRI ^
    CategoryList categoryList;
    CatImageList catImageList;
    QList<Vote*> votes;
    //
    ApiClient apiClient;
    apiClient.getAllCategory(&categoryList);
    apiClient.getAllVotes(&votes);
    //



    view->rootContext()->setContextProperty("categoryList", &categoryList);
    view->rootContext()->setContextProperty("catImageList", &catImageList);
    view->rootContext()->setContextProperty("apiClient", &apiClient);

    view->setSource(SailfishApp::pathTo("qml/9Meow.qml"));
    view->show();

    return app->exec();
}
