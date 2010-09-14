FINAL :
	echo Copying test DLL to z\sys\bin
	copy %epocroot%epoc32\release\winscw\udeb\pr_prfwtestprotocol.dll 	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
 	copy %epocroot%epoc32\release\winscw\udeb\prfwtestcaseutils.lib	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
	copy %epocroot%epoc32\release\winscw\udeb\prfwtestcaseutils.dll 	 %epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
	copy %epocroot%epoc32\release\winscw\udeb\t_presenceall.dll 	      %epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
	copy %epocroot%epoc32\release\winscw\udeb\t_utils.dll 								%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
	copy %epocroot%epoc32\release\winscw\udeb\t_presenceauthorization.dll 	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_presencegrantrequestmngt.dll 	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_presencewatcherlistmngt.dll 	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_presencegroupmembermngt.dll 	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_presencegrouplistmngt.dll 	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_presencewatching.dll 				%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_presencepublishing.dll 		%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_sessionmng.dll 					%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_rootservices.dll 				%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
  copy %epocroot%epoc32\release\winscw\udeb\t_presenceblocking.dll 		%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
	copy %epocroot%epoc32\release\winscw\udeb\prfwtestprocessmaster.exe 	%epocroot%epoc32\release\winscw\UDEB\z\sys\bin /y
	
MAKMAKE FREEZE LIB CLEANLIB RESOURCE RELEASABLES CLEAN BLD SAVESPACE :