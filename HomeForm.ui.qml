import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Page {
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

            delegate: SipCallDelegate {
                onClicked: {
                    console.log("SipCallDelegate clicked " + remoteUri)
                    pjSuaDestUri.text = remoteUri
                }
            }
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
                onClicked: {
                    pjSuaDestUri.clear()
                }
            }

            Button {
                id: callButton
                text: qsTr("Make call")
                onClicked: {
                    pjSuaCtx.onMakeCall(pjSuaDestUri.text)
                    pjSuaDestUri.clear()
                }
            }
            Button {
                id: confButton
                text: qsTr("Confer")
                onClicked: {
                    pjSuaCtx.onConference()
                }
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
