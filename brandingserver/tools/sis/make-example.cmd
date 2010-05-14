@echo off
rem
rem Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
rem All rights reserved.
rem This component and the accompanying materials are made available
rem under the terms of "Eclipse Public License v1.0"
rem which accompanies this distribution, and is available
rem at the URL "http://www.eclipse.org/legal/epl-v10.html".
rem
rem Initial Contributors:
rem Nokia Corporation - initial contribution.
rem
rem Contributors:
rem
rem Description:  Example to make the brand sis file
rem
@echo on

@echo off
call t:\epoc32\tools\makesis brand-example.pkg
call t:\epoc32\tools\signsis brand-example.sis brand.sis rd.cer rd-key.pem
del brand-example.sis
ren brand.sis brand-example.sis
pause
