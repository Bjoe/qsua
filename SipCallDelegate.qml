import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.11

Item {
    id: rootDelegate
    height: rootLayout.implicitHeight + 20
    width: listView.width

    signal clicked(string remoteUri)

    ColumnLayout {
        id: rootLayout
        anchors.fill: parent

        Text {
            Layout.fillWidth: true

            id: uriTxt
            text: model.display

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    rootDelegate.clicked(model.display)
                }
            }
        }
        RowLayout {
            Text {
                Layout.fillWidth: true
                id: txtState
                text: model.state
            }
            Image {
                id: acceptButton
                visible: false
                source: "assets/call_start.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        model.callObj.accept();
                    }
                }
            }
            Image {
                id: declineButton
                visible: false
                source: "assets/call_stop.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        model.callObj.decline();
                    }
                }
            }
            Image {
                id: hangupButton
                visible: false
                source: "assets/call_stop.png"
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        model.callObj.hangup();
                    }
                }
            }
        }
    }

    states: [
        State {
            when: model.state === "INCOMING"
            PropertyChanges { target: acceptButton; visible: true }
            PropertyChanges { target: declineButton; visible: true }
        },
        State {
            when: model.state === "CALLING"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "CONNECTING"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "EARLY"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "CONFIRMED"
            PropertyChanges { target: hangupButton; visible: true }
        },
        State {
            when: model.state === "DISCONNCTD"
            PropertyChanges { target: acceptButton; visible: false }
            PropertyChanges { target: declineButton; visible: false }
            PropertyChanges { target: hangupButton; visible: false }
        }

    ]
}
