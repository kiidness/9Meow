import QtQuick 2.0
import Sailfish.Silica 1.0
import CategoryModel 1.0

Page {
    id: page

    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listView
        anchors.fill: parent

        PullDownMenu {
            MenuItem {
                text: qsTr("Show Page 2")
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
        }

        header: Column {
            width: parent.width
            PageHeader {
                        title: qsTr("Nested Page")
                    }
            Label {
                text: "test"
            }
            Label {
                text: "aaaaaa"
            }
        }
        delegate: BackgroundItem {
            id: delegate

            Label {
                x: Theme.horizontalPageMargin
                text: qsTr("Item") + " " + index
                anchors.verticalCenter: parent.verticalCenter
                color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
            }
            onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
        }
        model: CategoryModel { list: categoryList }
        VerticalScrollDecorator {}
    }

}
