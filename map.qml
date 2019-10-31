import QtQuick 2.5
import QtPositioning 5.7
import QtLocation 5.7
import QtQuick.Controls 1.4

Rectangle {

    id: root
    width: 900
    height: 700

    visible: true

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
        // specify plugin parameters if necessary
        // PluginParameter {
        //     name:
        //     value:
        // }

    }

    Rectangle {

        anchors.fill: parent

        Map {
            id : map
            anchors.fill: parent
            zoomLevel: 10
            plugin: mapPlugin

            center: QtPositioning.coordinate(48.866667,2.333333)

            MapItemView {
                model: myModel
                delegate: routeDelegate
                Component.onCompleted: {
                            console.debug("Loaded first MapItemView")
                }
                Component.onDestruction: {
                             console.debug("Unloaded first MapItemView")
                }

            }

            Component {
                id: routeDelegate

                MapQuickItem {

                    id: marker
                    coordinate: QtPositioning.coordinate(model.latitude,model.longitude)

                    anchorPoint.x: image.width/6
                    anchorPoint.y: image.height

                    sourceItem: Column {
                         Image { id: image; width : 50 ; height: 50 ;  opacity: 0.7 ; source: "position.png" }
                         Text { text: "(" + model.latitude + "  ,  " + model.longitude + ")"; font.bold: true }

                    }

                    Component.onCompleted: {
                        console.debug("add image")
                        map.addMapItem(marker)
                        console.debug(myModel.columnCount())
                        update()
                    }
                }

            }


        }
    }
}

