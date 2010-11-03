/*
* Copyright (c) 2006-2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Import manager handles the reading, parsing and writing of
*                Brand data.
*
*/


#include <s32file.h>
#include <cbsfactory.h>
#include <mbsupdater.h>
#include <bamdesca.h>

#include "cbsimportmanager.h"
#include "cbsimportxmlparser.h"
#include "cbsimportfilereader.h"
#include "cbsimportstoragemanager.h"
#include "cbsimportconstants.h"
#include "importlogwriter.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CBSImportManager::NewL
// ---------------------------------------------------------------------------
//
CBSImportManager* CBSImportManager::NewL()
    {
    CBSImportManager* self = NewLC();
    CleanupStack::Pop();
    return self;
    }

// ---------------------------------------------------------------------------
// CBSImportManager::NewLC
// ---------------------------------------------------------------------------
//
CBSImportManager* CBSImportManager::NewLC()
    {
    CBSImportManager* self = new (ELeave) CBSImportManager();
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// CBSImportManager::ConstructL
// ---------------------------------------------------------------------------
//
void CBSImportManager::ConstructL()
    {
    // Open filesystem handle
    User::LeaveIfError( iFs.Connect() );
    }
    
// ---------------------------------------------------------------------------
// CBSImportManager::~CBSImportManager
// ---------------------------------------------------------------------------
//
CBSImportManager::~CBSImportManager()
    {
    iFs.Close();
    }

// ---------------------------------------------------------------------------
// CBSImportManager::CBSImportManager
// ---------------------------------------------------------------------------
//
CBSImportManager::CBSImportManager()
    {
    }

// ---------------------------------------------------------------------------
// CBSImportManager::ImportFileL
// ---------------------------------------------------------------------------
//
void CBSImportManager::ImportFileL( const TDesC& aSrcFile )
    {
    // Read XML File
    IMPORT_DP( D_IMPORT_LIT("Reading XML file: %S"), &aSrcFile );
    
    CBSImportFileReader* reader = CBSImportFileReader::NewLC( ETrue );
    CMDXMLDocument* document = reader->ReadXMLFileL( iFs, aSrcFile );
    CleanupStack::PopAndDestroy(reader);
    IMPORT_DP( D_IMPORT_LIT("Reading done") );
	
	CleanupStack::PushL(document);

    // Parse XML file
    IMPORT_DP( D_IMPORT_LIT("Parsing XML content...") );
    CBSImportStorageManager* storage = CBSImportStorageManager::NewLC();
    
    CBSImportXMLParser* parser = CBSImportXMLParser::NewLC( storage );
    parser->ParseDocumentL( *document );  
        
    CleanupStack::PopAndDestroy( parser );
    IMPORT_DP( D_IMPORT_LIT("Parsing done.") );

    // Write output files
    IMPORT_DP( D_IMPORT_LIT("Writing Branding files...") );
    storage->WriteDataToServerL();
    IMPORT_DP( D_IMPORT_LIT("Writing done.") );

    // Cleanup
    CleanupStack::PopAndDestroy( 2 , document ); // storage , document
    }

// ---------------------------------------------------------------------------
// CBSImportManager::ImportFileL
// ---------------------------------------------------------------------------
//
void CBSImportManager::ImportFileL( const MDesCArray& aSrcFiles )
    {
    // Read XML Files
    CBSImportStorageManager* storage = CBSImportStorageManager::NewLC();
    CBSImportXMLParser* parser = CBSImportXMLParser::NewLC( storage );
    CBSImportFileReader* reader = CBSImportFileReader::NewLC( ETrue );

    TInt count = aSrcFiles.MdcaCount();
    for( TInt i = 0; i < count; i++ )
        {
        TPtrC file( aSrcFiles.MdcaPoint( i ) );
        IMPORT_DP( D_IMPORT_LIT("Reading XML file: %S"), &file );
        CMDXMLDocument* document = reader->ReadXMLFileL( iFs, file );
        IMPORT_DP( D_IMPORT_LIT("Reading done") );
        CleanupStack::PushL(document);

        // Parse XML file
        IMPORT_DP(D_IMPORT_LIT("Parsing XML content..."));
        parser->ParseDocumentL(*document);  
        IMPORT_DP( D_IMPORT_LIT("Parsing done.") );
		CleanupStack::PopAndDestroy(document);
        }
    
    CleanupStack::PopAndDestroy( 2, parser ); // reader, parser
    
    // Write output files
    IMPORT_DP( D_IMPORT_LIT("Writing branding data to server...") );
    storage->WriteDataToServerL();
    IMPORT_DP( D_IMPORT_LIT("Writing done.") );

    // Cleanup
    CleanupStack::PopAndDestroy( storage );
    }

// End of file
