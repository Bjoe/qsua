import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Page {
    property alias pjSuaDestUri: pjSuaDestUri
    property alias listView: listView
    property alias clearButton: clearButton
    property alias callButton: callButton
    property alias confButton: confButton

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

                Image {
                    id: image
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    source: "assets/gtk_close.png"
                    anchors.rightMargin: 15

                    MouseArea {
                        id: clearButton
                        anchors.fill: parent
                    }
                }
            }

            Image {
                id: image1
                source: "assets/call_start.png"
                sourceSize.height: 30
                sourceSize.width: 30
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: callButton
                    anchors.fill: parent
                }
            }
            Image {
                id: image2
                source: "assets/conference_call.png"
                sourceSize.height: 30
                sourceSize.width: 30
                fillMode: Image.PreserveAspectFit

                MouseArea {
                    id: confButton
                    anchors.fill: parent
                }
            }


        }
    }
    states: [
        State {
            name: "with text"
            when: pjSuaDestUri.text !== ""
            PropertyChanges {
                target: image
                opacity: 1
            }
        },
        State {
            name: "without text"
            when: pjSuaDestUri.text === ""
            PropertyChanges {
                target: image
                opacity: 0.2
            }
        }
    ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:6}D{i:8}D{i:10}
}
##^##*/

