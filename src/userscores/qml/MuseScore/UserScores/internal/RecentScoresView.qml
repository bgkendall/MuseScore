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
import QtQuick 2.7
import QtQuick.Controls 2.2

import MuseScore.UiComponents 1.0
import MuseScore.UserScores 1.0

GridView {
    id: root

    property string backgroundColor: ui.theme.backgroundPrimaryColor

    signal openScoreRequested(var scorePath)
    signal addNewScoreRequested()

    readonly property int sideMargin: 30

    clip: true

    cellHeight: 334
    cellWidth: sideMargin + 172 + sideMargin

    boundsBehavior: Flickable.StopAtBounds

    header: Item {
        height: headerTitle.height
        anchors.left: parent.left
        anchors.right: parent.right

        StyledTextLabel {
            id: headerTitle

            anchors.top: parent.top
            anchors.topMargin: 8
            anchors.left: parent.left
            anchors.leftMargin: root.sideMargin

            text: qsTrc("userscores", "New & recent")

            font: ui.theme.tabBoldFont
        }
    }

    ScrollBar.vertical: StyledScrollBar {
        parent: root.parent

        anchors.top: root.top
        anchors.bottom: root.bottom
        anchors.right: parent.right
        anchors.rightMargin: 16

        visible: root.contentHeight > root.height
        z: 1
    }

    delegate: Item {
        height: root.cellHeight
        width: root.cellWidth

        ScoreItem {
            anchors.centerIn: parent

            height: 272
            width: 172

            title: score.title
            thumbnail: score.thumbnail
            isAdd: score.isAddNew
            timeSinceCreation: !isAdd ? score.timeSinceCreation : ""

            onClicked: {
                if (isAdd) {
                    root.addNewScoreRequested()
                } else {
                    root.openScoreRequested(score.path)
                }
            }
        }
    }
}
