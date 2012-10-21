/****************************************************************************
** Copyright (C) 2001-2012 Klaralvdalens Datakonsult AB.  All rights reserved.
**
** This file is part of the KD Tools library.
**
** Licensees holding valid commercial KD Tools licenses may use this file in
** accordance with the KD Tools Commercial License Agreement provided with
** the Software.
**
**
** This file may be distributed and/or modified under the terms of the GNU
** Lesser General Public License version 2 and version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE.LGPL included.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** Contact info@kdab.net if any conditions of this licensing are not
** clear to you.
**
**********************************************************************/

#ifndef __KDTOOLS_GUI_KDPROPERTYEDITOR_H__
#define __KDTOOLS_GUI_KDPROPERTYEDITOR_H__

#include <KDToolsCore/kdtoolsglobal.h>
#include <KDToolsCore/pimpl_ptr.h>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
class QModelIndex;
class QObject;
class QWidget;
QT_END_NAMESPACE

class KDPropertyInterface;

class KDTOOLSGUI_EXPORT KDPropertyEditor {
public:
  virtual ~KDPropertyEditor();
  virtual QWidget *createEditor(QWidget *parent, const QObject *target, const char *receiver) = 0;
  virtual void setEditorData(QWidget *editor, const QModelIndex& index ) = 0;
  virtual void setModelData(QWidget *editor, QAbstractItemModel* model,
			    const QModelIndex& index ) = 0;
};

class KDTOOLSGUI_EXPORT KDPropertyEditorFactory {
public:
    static KDPropertyEditorFactory* defaultFactory();

    KDPropertyEditorFactory();
    virtual ~KDPropertyEditorFactory();

    void addPropertyEditorType( const QString& type, KDPropertyEditor* editor );
    KDPropertyEditor* editor( const QString& type );
private:
    class Private;
    kdtools::pimpl_ptr<Private>  d;
};

template <typename T>
class KDPropertyEditorRegistrator {
public:
  explicit KDPropertyEditorRegistrator( const QString& type ) {
    KDPropertyEditorFactory::defaultFactory()->addPropertyEditorType( type, new T );
  }
};

#define REGISTER_KDPROPERTYEDITOR( classname ) \
  static KDPropertyEditorRegistrator<classname> registrator_##classname( QLatin1String( #classname ) );

#endif /* __KDTOOLS_GUI_KDPROPERTYEDITOR_H__ */

