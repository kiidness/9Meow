import QtQuick 2.0
import Sailfish.Silica 1.0
import CategoryModel 1.0
Page {
    property var category

    PageHeader {
        title: category.name
        id: header
    }
    // The effective value will be restricted by ApplicationWindow.allowedOrientations
    allowedOrientations: Orientation.All


}
