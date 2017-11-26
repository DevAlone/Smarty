import QtQuick 2.0
import "constants.js" as Constants


Text {
    anchors.centerIn: parent
    font.pointSize: Constants.textItemDataFontSize
    text: model.modelData.data
}
