import QtQuick 2.0
import Sailfish.Silica 1.0
import "../pages"

ListItem {
    id: categoryItem
    width: listView.width
    Label {
        text: name
    }
    menu: ContextMenu {
        MenuItem {
            text: "Refresh list"
        }
    }

    onClicked: pageStack.push( categoryPage, { category: category }  )
    Component {
        id: categoryPage
        CategoryPage {}
    }
}
