import QtQuick 2.0

HomeForm {

    listView.delegate: SipCallDelegate {
        onClicked: {
                console.log("SipCallDelegate clicked " + remoteUri)
                pjSuaDestUri.text = remoteUri
            }
    }

    clearButton.onClicked: {
        console.log("clear")
        pjSuaDestUri.clear()
    }

    callButton.onClicked: {
        console.log("makecall clicked " + pjSuaDestUri.text)
        pjSuaCtx.onMakeCall(pjSuaDestUri.text)
        pjSuaDestUri.clear()
    }

    confButton.onClicked: {
        console.log("conference")
        pjSuaCtx.onConference()
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
