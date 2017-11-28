import QtQuick 2.0
import QtQuick.Layouts 1.3
import "constants.js" as Constants

Item {
    id: textItemViewRoot
    anchors.fill: parent

    RowLayout {
        anchors.centerIn: parent
        Image {
            source: model.modelData.iconPath.length > 0 ?"image://file/" + model.modelData.iconPath : ""
            Layout.preferredWidth: textItemViewRoot.height * 0.5
            Layout.preferredHeight: textItemViewRoot.height * 0.5
        }

        Text {
            id: textItem
            font.pointSize: Constants.textItemDataFontSize
            text: model.modelData.data
        }

    }
}

