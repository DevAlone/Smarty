import QtQuick 2.9

Image {
    property string path: ""
    onPathChanged: source = path.length > 0 ? "image://file/" + path : ""
    visible: path.length > 0
}
