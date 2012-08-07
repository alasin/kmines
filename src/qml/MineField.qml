/*
    Copyright 2012 Viranch Mehta <viranch.mehta@gmail.com>
  
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.
   
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
   
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 1.1
import org.kde.games.core 0.1 as KgCore

Item {
    id: container

    width: height*(columns+2)/(rows+2)
    height: Math.floor(parent.height/(rows+2))*(rows+2)

    signal cellClicked(int index)

    property int rows
    property int columns
    property int mines
    property int flaggedMines: 0

    property alias cells: cellRepeater

    property real cellSize: width/(columns+2)

    Grid {
        id: grid
        anchors.fill: parent
        rows: parent.rows+2
        columns: parent.columns+2

        Repeater {
            id: cellRepeater
            model: grid.rows*grid.columns

            CellItem {
                width: grid.width/grid.columns
                height: grid.height/grid.rows

                border: getBorderSprite(index)

                onClicked: {
                    var row = Math.floor(index/grid.columns);
                    var column = index%grid.columns;
                    container.cellClicked((row-1)*container.columns + (column-1));
                }
                onFlaggedChanged: {
                    if (flagged) flaggedMines++;
                    else flaggedMines--;
                }
            }
        }
    }

    // index is wrt the inner grid
    function itemAtIndex(index) {
        var row = Math.floor(index/columns);
        var column = index%columns;
        return itemAtRowCol(row, column);
    }

    // row/col are wrt inner grid
    function itemAtRowCol(row, column) {
        // the +1's in row+1 & column+1 are for border cells
        var index = (row+1)*grid.columns + (column+1);
        return cells.itemAt(index);
    }

    function getBorderSprite(index) {
        var row = Math.floor(index/grid.columns);
        var col = index%grid.columns;

        if( row == 0 && col == 0)
        {
            return "border.outsideCorner.nw";
        }
        else if( row == 0 && col == columns+1)
        {
            return "border.outsideCorner.ne";
        }
        else if( row == rows+1 && col == 0 )
        {
            return "border.outsideCorner.sw";
        }
        else if( row == rows+1 && col == columns+1 )
        {
            return "border.outsideCorner.se";
        }
        else if( row == 0 )
        {
            return "border.edge.north";
        }
        else if( row == rows+1 )
        {
            return "border.edge.south";
        }
        else if( col == 0 )
        {
            return "border.edge.west";
        }
        else if( col == columns+1 )
        {
            return "border.edge.east";
        }
        else {
            return "";
        }
    }
}