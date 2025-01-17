/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
import QtQuick 2.15

import MuseScore.Ui 1.0
import MuseScore.UiComponents 1.0
import MuseScore.NotationScene 1.0

Item {
    id: root

    width: childrenRect.width
    height: childrenRect.height

    ViewModeControlModel {
        id: model
    }

    Component.onCompleted: {
        model.load()
    }

    FlatButton {
        normalStateColor: menu.isOpened ? ui.theme.accentColor : "transparent"

        text: Boolean(model.currentViewMode) ? model.currentViewMode.title : ""
        icon: Boolean(model.currentViewMode) ? model.currentViewMode.icon : IconCode.NONE

        visible: Boolean(model.currentViewMode)

        orientation: Qt.Horizontal

        StyledIconLabel {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter

            iconCode: IconCode.SMALL_ARROW_DOWN
        }

        onClicked: {
            if (menu.isOpened) {
                menu.toggleOpened()
                return
            }

            menu.toggleOpened()
        }

        StyledMenu {
            id: menu

            opensUpward: true
            itemWidth: 220

            model: model.items

            onHandleAction: {
                Qt.callLater(model.selectViewMode, actionCode)
                menu.close()
            }
        }
    }
}
