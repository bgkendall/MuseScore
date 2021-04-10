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

#ifndef __TEXTLINEBASE_H__
#define __TEXTLINEBASE_H__

#include "line.h"
#include "style.h"
#include "property.h"

namespace Ms {
enum class Align : char;
class TextLineBase;
class Element;
class Text;

//---------------------------------------------------------
//   @@ TextLineBaseSegment
//---------------------------------------------------------

class TextLineBaseSegment : public LineSegment
{
protected:
    Text* _text;
    Text* _endText;
    QPointF points[6];
    int npoints;
    qreal lineLength;
    bool twoLines { false };

public:
    TextLineBaseSegment(Spanner*, Score* s, ElementFlags f = ElementFlag::NOTHING);
    TextLineBaseSegment(const TextLineBaseSegment&);
    ~TextLineBaseSegment();

    TextLineBase* textLineBase() const { return (TextLineBase*)spanner(); }
    virtual void draw(mu::draw::Painter*) const override;

    virtual void layout() override;
    virtual void setSelected(bool f) override;

    virtual void spatiumChanged(qreal /*oldValue*/, qreal /*newValue*/) override;

    virtual Element* propertyDelegate(Pid) override;

    virtual Shape shape() const override;

    virtual bool setProperty(Pid id, const QVariant& v) override;
};

//---------------------------------------------------------
//   HookType
//---------------------------------------------------------

enum class HookType : char {
    NONE, HOOK_90, HOOK_45, HOOK_90T, ARROW_OPEN
};

//---------------------------------------------------------
//   @@ TextLineBase
//---------------------------------------------------------

class TextLineBase : public SLine
{
    enum class LineType : char {
        CRESCENDO, DECRESCENDO
    };

    M_PROPERTY(bool,      lineVisible,           setLineVisible)
    M_PROPERTY2(HookType, beginHookType,         setBeginHookType,          HookType::NONE)
    M_PROPERTY2(HookType, endHookType,           setEndHookType,            HookType::NONE)
    M_PROPERTY(Spatium,   beginHookHeight,       setBeginHookHeight)
    M_PROPERTY(Spatium,   endHookHeight,         setEndHookHeight)

    M_PROPERTY(PlaceText, beginTextPlace,        setBeginTextPlace)
    M_PROPERTY(QString,   beginText,             setBeginText)
    M_PROPERTY(Align,     beginTextAlign,        setBeginTextAlign)
    M_PROPERTY(QString,   beginFontFamily,       setBeginFontFamily)
    M_PROPERTY(qreal,     beginFontSize,         setBeginFontSize)
    M_PROPERTY(FontStyle, beginFontStyle,        setBeginFontStyle)
    M_PROPERTY(QPointF,   beginTextOffset,       setBeginTextOffset)

    M_PROPERTY(PlaceText, continueTextPlace,     setContinueTextPlace)
    M_PROPERTY(QString,   continueText,          setContinueText)
    M_PROPERTY(Align,     continueTextAlign,     setContinueTextAlign)
    M_PROPERTY(QString,   continueFontFamily,    setContinueFontFamily)
    M_PROPERTY(qreal,     continueFontSize,      setContinueFontSize)
    M_PROPERTY(FontStyle, continueFontStyle,     setContinueFontStyle)
    M_PROPERTY(QPointF,   continueTextOffset,    setContinueTextOffset)

    M_PROPERTY(PlaceText, endTextPlace,          setEndTextPlace)
    M_PROPERTY(QString,   endText,               setEndText)
    M_PROPERTY(Align,     endTextAlign,          setEndTextAlign)
    M_PROPERTY(QString,   endFontFamily,         setEndFontFamily)
    M_PROPERTY(qreal,     endFontSize,           setEndFontSize)
    M_PROPERTY(FontStyle, endFontStyle,          setEndFontStyle)
    M_PROPERTY(QPointF,   endTextOffset,         setEndTextOffset)

protected:
    friend class TextLineBaseSegment;

public:
    TextLineBase(Score* s, ElementFlags = ElementFlag::NOTHING);

    virtual void write(XmlWriter& xml) const override;
    virtual void read(XmlReader&) override;

    virtual void writeProperties(XmlWriter& xml) const override;
    virtual bool readProperties(XmlReader& node) override;

    virtual void spatiumChanged(qreal /*oldValue*/, qreal /*newValue*/) override;

    virtual QVariant getProperty(Pid id) const override;
    virtual bool setProperty(Pid propertyId, const QVariant&) override;
    virtual Pid propertyId(const QStringRef& xmlName) const override;
};
}     // namespace Ms
Q_DECLARE_METATYPE(Ms::HookType);

#endif
