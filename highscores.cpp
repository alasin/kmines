/*
 * Copyright (c) 2002 Nicolas HADACEK (hadacek@kde.org)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "highscores.h"

#include <kurl.h>
#include <klocale.h>
#include <kapplication.h>
#include <kconfig.h>

#include "version.h"
#include "defines.h"


namespace KExtHighscore
{

ExtManager::ExtManager()
    : Manager(Level::NbLevels)
{
    setWWHighscores(HOMEPAGE, VERSION);
    showStatistics(true);
    const uint RANGE[16] = {    1, 3120, 3180, 3240, 3300, 3360, 3420, 3480,
                             3510, 3540, 3550, 3560, 3570, 3580, 3590, 3600  };
    QMemArray<uint> s;
    s.duplicate(RANGE, 16);
    setScoreHistogram(s, true);

    ScoreItem *scoreItem = new ScoreItem;
    scoreItem->setPrettyFormat(Item::MinuteTime);
    setScoreItem("score", scoreItem);

    MeanScoreItem *meanScoreItem = new MeanScoreItem;
    meanScoreItem->setPrettyFormat(Item::MinuteTime);
    setPlayerItem("mean score", meanScoreItem);

    BestScoreItem *bestScoreItem = new BestScoreItem;
    bestScoreItem->setPrettyFormat(Item::MinuteTime);
    setPlayerItem("best score", bestScoreItem);

    Item *item = new Item((uint)0, i18n("Clicks"), Qt::AlignRight);
    setScoreItem("nb_actions", item);
}

QString ExtManager::gameTypeLabel(uint gameType, LabelType type) const
{
    const Level::Data &data = Level::data((Level::Type)gameType);
    switch (type) {
    case Icon:
    case Standard: return data.label;
    case I18N:     return i18n(data.i18nLabel);
    case WW:       return data.wwLabel;
    }
    return QString::null;
};

void ExtManager::convertLegacy(uint gameType)
{
    QString group;
    switch ((Level::Type)gameType) {
    case Level::Easy:     group = "Easy level"; break;
    case Level::Normal:   group = "Normal level"; break;
    case Level::Expert:   group = "Expert level"; break;
    case Level::NbLevels: Q_ASSERT(false);
    }

    KConfigGroupSaver cg(kapp->config(), group);
    QString name = cg.config()->readEntry("Name", QString::null);
    if ( name.isNull() ) return;
    if ( name.isEmpty() ) name = i18n("anonymous");
    uint minutes = cg.config()->readUnsignedNumEntry("Min", 0);
    uint seconds = cg.config()->readUnsignedNumEntry("Sec", 0);
    int score = 3600 - (minutes*60 + seconds);
    if ( score<=0 ) return;
    Score s(Won);
    s.setData("score", score);
    s.setData("name", name);
    submitLegacyScore(s);
}

bool ExtManager::isStrictlyLess(const Score &s1, const Score &s2) const
{
    if ( s1.score()==s2.score() )
        return s1.data("nb_actions").toUInt()>s2.data("nb_actions").toUInt();
    return Manager::isStrictlyLess(s1, s2);
}

};
