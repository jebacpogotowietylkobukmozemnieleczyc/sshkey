import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.0
import com.ean.newton 1.0

ApplicationWindow {
    title: qsTr("Yellow Project")

    statusBar: StatusBar {
    RowLayout {
        Label {
            id: status
            }
        }
    }

    width: 369
    height: 250

    ColumnLayout {
        x: 10
        y: 10

        // Key x


        // Filename
        RowLayout {
            Label {
                text: qsTr("Library:")
            }
            TextField {
                id: filename
                implicitWidth: 200
                onTextChanged: updateStatusBar()
            }
            Button {
                text: qsTr("&Browse...")
                onClicked: filedialog.visible = true
            }
        }

        // mfunction
        RowLayout {
            Label {
                text: qsTr("Funkcja:")
            }
            TextField {
                id: mfunction
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }

        }

        // X
        RowLayout {
            Label {
                text: qsTr("X:")
            }
            TextField {
                id: x
                text: qsTr("1")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }
        }

        // mit
        RowLayout {
            Label {
                text: qsTr("Mit:")
            }
            TextField {
                id:mit
                text: qsTr("100")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }
        }

        // Eps
        RowLayout {
            Label {
                text: qsTr("Eps:")
            }
            TextField {
                id: eps
                text: qsTr("1e-16")
                Layout.fillWidth: true
                onTextChanged: updateStatusBar()
            }
        }

        // Buttons: Generate, Quit
        RowLayout {
            Button {
                id: generate
                text: qsTr("&Calculate")
                onClicked: newton.generateResult(x.text,mit.text,eps.text)
            }
            Button {
                text: qsTr("&Quit")
                onClicked: Qt.quit()
            }
        }

    }

    FileDialog {
        id: filedialog
        title: qsTr("Select a file")
        selectMultiple: false
        selectFolder: false
        nameFilters: [ "All files (*)" ]
        selectedNameFilter: "All files (*)"
        onAccepted: {
            filename.text = fileUrl.toString().replace("file://", "")
        }
    }

    Newton {
        id: newton
        filename: filename.text
        mfunction: mfunction.text
        x: x.text
        mit:mit.text
        eps:eps.text
        onResultGenerated: {
            //if (success) {
                status.text = qsTr('<font color="green">Wynik: </font>'+result+'<br />
                                   <font color="green">fx: </font>'+fx+'<br />
                                   <font color="green">status: </font>'+state+'<br />
                                   <font color="green">i: </font>'+i)
            //} else {
              //  status.text = qsTr('<font color="red">Key generation failed</font>')
            //}
        }
    }

    function updateStatusBar() {
       /*
        if (mfunction.text != confirm.text) {
            status.text = qsTr('<font color="red">Pass phrase does not match.</font>')
            generate.enabled = false
        } else if (mfunction.text.length > 0 && mmfunction.text.length < 5) {
            status.text = qsTr('<font color="red">Pass phrase too short.</font>')
            generate.enabled = false
        } else if (filename.text == "") {
            status.text = qsTr('<font color="red">Enter a filename.</font>')
            generate.enabled = false
        } else {
            status.text = ""
            generate.enabled = true
        }
        */
    }

    Component.onCompleted: updateStatusBar()
}
