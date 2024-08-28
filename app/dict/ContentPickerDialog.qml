/*
 *
 * Copyright 2014 Canonical Ltd.
 *
 * This file is part of shorts-app.
 *
 * shorts-app is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * shorts-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.2
import Ubuntu.Components.Popups 1.0 as Popups
import Ubuntu.Content 1.1
import Ubuntu.Components 1.1
import Ubuntu.Components.ListItems 1.0 as ListItem

Page {
    id: picker
    visible: false

    property var pickerParent

    ContentPeerPicker {
        visible: parent.visible

        // Type of handler: Source, Destination, or Share
        handler: ContentHandler.Source
        // well know content type
        contentType: ContentType.All

        onPeerSelected: {
            peer.selectionType = ContentTransfer.Multiple;
            pickerParent.activeTransfer = peer.request();
            pageStack.pop();
        }

        onCancelPressed: {
            pageStack.pop();
            pageStack.pop();
        }
    }
}
