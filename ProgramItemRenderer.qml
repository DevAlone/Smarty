import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import "/constants.js" as Constants

Rectangle {
    id: root
    width: parent.width
    height: childrenRect.height

    ColumnLayout {
        width: parent.width

        RowLayout {
            Layout.alignment: Qt.AlignHCenter

            Icon {
                path: getItem().iconPath
                Layout.preferredWidth: Constants.itemHeight * 0.5
                Layout.preferredHeight: Constants.itemHeight * 0.5
            }

            Label {
                id: name
                text: getItem().data
                wrapMode: Label.Wrap
                horizontalAlignment: Label.AlignHCenter
            }

            Label {
                text: getItem().path
                visible: text != name.text
                color: "#aeaeae"
                wrapMode: Label.Wrap
                horizontalAlignment: Label.AlignHCenter
            }
            // TODO: show program arguments
        }

        Label {
            Layout.preferredWidth: parent.width
            text: getItem().description
            color: "#999"
            wrapMode: Label.Wrap
            horizontalAlignment: Label.AlignHCenter
            visible: text.length > 0
        }
    }

    function getItem() {
        return model.modelData;
    }
}
