import QtQuick 2.9
import QtQuick.Layouts 1.3
import "/constants.js" as Constants

Item {
    id: textItemViewRoot

    width: parent.width
    height: childrenRect.height

    RowLayout {
        anchors.centerIn: parent

        Icon {
            path: model.modelData.iconPath
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
