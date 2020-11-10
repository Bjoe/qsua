import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Page {
    property alias pjSuaDestUri: pjSuaDestUri
    property alias clearButton: clearButton
    property alias callButton: callButton
    property alias confButton: confButton
    property alias listView: listView

    title: qsTr("Calllog")

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        anchors.rightMargin: 20
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.topMargin: 20
        Layout.fillWidth: true

        ListView {
            id: listView
            width: 110
            height: 160
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true

            model: pjSuaCtx.model
        }

        RowLayout {
            id: rowLayout
            Layout.fillHeight: false
            Layout.fillWidth: true

            TextField {
                id: pjSuaDestUri
                Layout.fillWidth: true
                placeholderText: qsTr("sip:0123456478@foo.bar")
            }

            Button {
                id: clearButton
                text: qsTr("Clear")
            }

            Button {
                id: callButton
                text: qsTr("Make call")
            }
            Button {
                id: confButton
                text: qsTr("Confer")
            }
        }
    }
    states: [
        State {
            name: "with text"
            when: pjSuaDestUri.text !== ""
            PropertyChanges {
                target: clearButton
                opacity: 1.0
            }
        },
        State {
            name: "without text"
            when: pjSuaDestUri.text === ""
            PropertyChanges {
                target: clearButton
                opacity: 0.25
            }
            PropertyChanges {
                target: pjSuaDestUri
                focus: true
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

