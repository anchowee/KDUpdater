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

#include "kdupdaterufuncompressor_p.h"

#include <QFileInfo>
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
    if( argc != 2 )
    {
        std::cerr << "Usage: " << argv[0] <<
               " <Compressed-File-Name>\n "
               "Extracts the compressed file into "
               "the current working directory" << std::endl;
        return EXIT_FAILURE;
    }

    const QFileInfo fileInfo(QFile::decodeName(argv[1]));

    qDebug("Compressed file = %s", argv[1]);

    KDUpdater::UFUncompressor uncompressor;
    uncompressor.setFileName( fileInfo.absoluteFilePath() );
    uncompressor.setDestination( QLatin1String( "." ) );
    if ( !uncompressor.uncompress() ) {
        std::cerr << "Extracting " << argv[1] << " failed: "
                  << qPrintable(uncompressor.errorString()) << std::endl;
        return EXIT_FAILURE;
    }

    std::cerr << "Extracted " << argv[1] << std::endl;
    return EXIT_SUCCESS;
}
