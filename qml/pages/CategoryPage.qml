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

        PullDownMenu {
            MenuItem {
                onClicked: apiClient.getAllImages(category.id,catImageList)
                text: qsTr("Refresh")
            }
        }

        PushUpMenu {

            MenuItem {
                onClicked: apiClient.getMoreImages(category.id,catImageList)
                text: qsTr("Load More")
            }
        }
        header:
            PageHeader {
                title: category.name
                id: header
            }

        model: CatImageModel { list: catImageList }


        delegate: ListItem {

            id: imageItem
            width: listView.width
            height : 950
            Rectangle {
                id: container
                height: 800
                width: parent.width
                border.width: 1
                border.color: "#999"
                Image {
                    id: catImage
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 800
                    source: url
                    fillMode: Image.PreserveAspectCrop
                }
                Grid {
                    id: row
                    anchors.top: catImage.bottom
                    width: parent.width
                    columns: 3

                    Button {
                        id: upvoteBtn
                        text: "▲"
                        width: parent.width / 4
                        onClicked: apiClient.postVote(name, 1)
                        enabled: !isvoted
                    }
                    Label {
                        text: vote
                        width: parent.width / 2
                        horizontalAlignment: "AlignHCenter"
                        verticalAlignment: "AlignVCenter"
                    }
                    Button {
                        id: downvoteBtn
                        text: "▼"
                        width: parent.width / 4
                        onClicked: apiClient.postVote(name, 0)
                        enabled: !isvoted
                    }

                }
            }


        }

        VerticalScrollDecorator {}
    }
    Component.onCompleted: {
        apiClient.updateAllVotes()
        apiClient.getAllImages(category.id,catImageList)

    }

}
