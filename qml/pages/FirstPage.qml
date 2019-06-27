import QtQuick 2.0
import Sailfish.Silica 1.0
import CategoryModel 1.0
import "../delegates"

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
            }
        }

        header: Column {
            width: parent.width
            PageHeader {
                        title: qsTr("Cats breeds")
                    }
        }
        model: CategoryModel { list: categoryList }

        delegate: DelegateCategory { }

        VerticalScrollDecorator {}
    }
    Component.onCompleted: {
        apiClient.updateAllVotes()

    }

}
