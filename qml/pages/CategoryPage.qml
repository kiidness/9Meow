import QtQuick 2.0
import Sailfish.Silica 1.0
import CategoryModel 1.0
import CatImageModel 1.0
import "../delegates"
Page {
    property var category
    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All

    SilicaListView {
        id: listViewImage
        anchors.fill: parent

        header: Column {
            width: parent.width
            PageHeader {
                title: category.name
                id: header
                    }
        }
        model: CatImageModel { list: catImageList }


        delegate: ListItem {

            id: imageItem
            width: listView.width
            height : 900
            Rectangle {
                id: container
                anchors.centerIn: parent
                height: 800
                width: parent.width
                border.width: 1
                border.color: "#999"
                Image {
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 800
                    source: url
                    fillMode: Image.PreserveAspectFit
                }

            }


        }

        VerticalScrollDecorator {}
    }
    Component.onCompleted: {
        apiClient.getAllImages(category.id,catImageList)
    }

}